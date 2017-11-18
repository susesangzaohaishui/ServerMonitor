#include "process_mgr_t.h"
#include "dahlia_utils.h"
#include "globaldefine.h"
#include "redis_client_t.h"
#include "stringutil.h"
#include "nbclock.h"

dahlia::process_mgr_t::process_mgr_t( redis_client_t* redis_mgr_ ):
_redis_mgr(redis_mgr_),
_reboot_flag(false)
{
    _local_ip = get_local_ip_s();
    _redis_mgr->clear_monitor(_local_ip);//清理对应席位的监视数据
}

dahlia::process_mgr_t::~process_mgr_t( void )
{
    map<string , process_node_t*>::iterator pIt = _nodes.begin();
    for ( ; pIt != _nodes.end(); ++pIt)
    {
        delete pIt->second;
    }
}

void dahlia::process_mgr_t::register_node( const string& path, int npid , bool timeout_reboot_, int check_tick_)
{
    //查看是否有相同的进程名称
    map<string , process_node_t*>::iterator pIt = _nodes.find(path);//path,pid,nodeinfo
    if (pIt != _nodes.end())
    {
        //查看之前是否有同名的进程,但是进程ID不一样，如果有则杀死
        if ( pIt->second->_pid != npid)
        {
            pIt->second->termate();
        }

        //更新时间
        pIt->second->update_time();
        pIt->second->_pid = npid;
        pIt->second->_process_name = path;
        pIt->second->_timeout_reboot = timeout_reboot_;
        pIt->second->_heart_check_tick = check_tick_;
        pIt->second->_be_reload = true;
    }
    else
    {
        //生成节点
        _nodes[path] = new process_node_t(_redis_mgr, path, npid, timeout_reboot_, check_tick_);
    }

}

void dahlia::process_mgr_t::heart( const string& path, int npid )
{
    //跟新上报时间
    map<string , process_node_t* >::iterator pIt = _nodes.find(path);//path,pid,nodeinfo
    if (pIt != _nodes.end())
    {
        //更新时间
        if (npid ==  pIt->second->_pid)
        {
            pIt->second->update_time();
        }
    }
}

void dahlia::process_mgr_t::check()
{
    redis_process_state state_;
    int nmemry_count_ = -1;
    strcpy_s(state_.ip, _local_ip.c_str());

    //循环检查节点信息
    uint64_t last_ticket_ = nbclock::now_us() / 1000.0;

    //如果节点小于0，则推送监视器的心跳信息
    if (_nodes.size() <= 0)
    {
        //发送进程状态
        if (_redis_mgr)
        {
            string  sKey = _local_ip;
            sKey    += "_";
            sKey    += "monitor";
            state_.state =  STATE_MONITOR_HEART;
            _redis_mgr->send_process_state(sKey, state_);
        }
    }

    map<string , process_node_t*>::iterator pIt = _nodes.begin();
    for ( ; pIt != _nodes.end(); ++pIt)
    {
        string  sKey = _local_ip;
        sKey    += "_";
        sKey    += num2str(pIt->second->_pid);
       double dis_time =  (last_ticket_ - pIt->second->_lastupdate_ticket);

        strcpy_s(state_.ppath, pIt->second->_process_name.c_str());
        state_.pid = pIt->second->_pid;

        //检测重启中状态
        if (pIt->second->_heart_check_tick == -1)
        {
            //状态为重启中
            //准备进程状态数据,推送redis,设置为重启中
            state_.state = STATE_REBOOTING;
            state_.memcount = nmemry_count_;
            pIt->second->_state = STATE_REBOOTING;

            //如果重启超时，则继续重启
            if (dis_time > 60000)
            {
                 pIt->second->reboot();
            }

            if (_redis_mgr)
            {
                _redis_mgr->send_process_state(sKey, state_);
            }
            continue;
        }

        bool reload_ = false;
      
        //如果心跳超时，并且没有在重启中的状态
        if (fabs(dis_time)> 
            pIt->second->_heart_check_tick &&
            pIt->second->_heart_check_tick != -1)//_heart_check_tick为-1表示为重启中状态
        {
            //状态为未上报，检查进程状态,
            //如果进程已经死了就判断重启标志，进行重启
            //如果状态为活着，根据重启策略进行重启
            //上报异常状态
            if (!pIt->second->check(nmemry_count_))//判断进程存活状态
            {
                if (pIt->second->_be_reload)//如果标识为进程死亡则重启
                {
                    reload_ = true;
                }

                //放在设置状态之前，只有在状态转换的时候打印日志
                if (_redis_mgr && 
                    reload_)
                {
                    _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), AUTO_START, "自动重启", -1, "");
                }

                state_.state = STATE_STOP;
                pIt->second->_state = STATE_STOP;
                //准备进程状态数据,推送redis
            }
            else
            {

                if (pIt->second->_timeout_reboot&&
                    pIt->second->_heart_check_tick != -1)//如果进程活着，标识为心跳超时则重启,标识为重启状态
                {
                    reload_ = true;
                    if (_redis_mgr && 
                        reload_)
                    {
                        _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), HEART_OUTTM, "心跳超时", -1, "");
                    }
                } 
                else
                {
                    //判断是否有断言窗口
                    if (pIt->second->contins_assert_wnd())
                    {
                        //放在设置状态之前，只有在状态转换的时候打印日志
                        reload_ = true;
                        if (_redis_mgr && 
                            reload_)
                        {
                            _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), ASSERTING_, "断言", -1, "");
                        }


                        state_.state = STATE_ASSERTING;
                        pIt->second->_state = STATE_ASSERTING;
                    }
                    else
                    {
                        //放在设置状态之前，只有在状态转换的时候打印日志
                        if (_redis_mgr && 
                            pIt->second->_state != STATE_OUT_TIME)
                        {
                            _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), HEART_OUTTM, "心跳超时", -1, "");
                        }

                        state_.state = STATE_OUT_TIME;
                        pIt->second->_state = STATE_OUT_TIME;
                    }
                }
                
               
                //准备进程状态数据,推送redis
            }
            state_.memcount = nmemry_count_;
        }
        else
        {
            if (!pIt->second->check(nmemry_count_))//判断进程存活状态
            {
                if (pIt->second->_be_reload)//如果标识为进程死亡则重启
                {
                    reload_ = true;
                }

                //放在设置状态之前，只有在状态转换的时候打印日志
                if (_redis_mgr && !reload_)
                {
                    _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), AUTO_DIE, "进程终止", -1, "");
                }

                state_.state = STATE_STOP;
                pIt->second->_state = STATE_STOP;
                //准备进程状态数据,推送redis
            }
            else
            {
                //判断是否有断言窗口
                if (pIt->second->contins_assert_wnd())
                {
                    //放在设置状态之前，只有在状态转换的时候打印日志


                    reload_ = true;
                    if (_redis_mgr &&reload_)
                    {
                        _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), ASSERTING_, "断言", -1, "");
                    }

                    state_.state = STATE_ASSERTING;
                    pIt->second->_state = STATE_ASSERTING;
                }
                else
                {
                    state_.state = STATE_RUNNING;
                    pIt->second->_state = STATE_RUNNING;
                }
                 //准备进程状态数据,推送redis
            }
            state_.memcount = nmemry_count_;
        }

        //发送进程状态
        if (_redis_mgr)
        {
            _redis_mgr->send_process_state(sKey, state_);
        }

        if (reload_)//标识重启
        {
            pIt->second->reboot();
        }
    }
} 

void dahlia::process_mgr_t::stop( const string& path/*, int npid */)
{
    //停止进程，设置进程不重启标识
    //跟新上报时间
    map<string , process_node_t* >::iterator pIt = _nodes.find(path);//path,pid,nodeinfo
    if (pIt != _nodes.end())
    {
        //更新时间
            pIt->second->stop();

            if (_redis_mgr)
            {
                _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), UNAUTO_DIE_, "手动关闭进程", -1, "");
            }
    }
}

void dahlia::process_mgr_t::start( const string& path/*, int npid*/ )
{
    map<string , process_node_t* >::iterator pIt = _nodes.find(path);//path,pid,nodeinfo
    if (pIt != _nodes.end())
    {
        //更新时间
            pIt->second->reboot();

            if (_redis_mgr)
            {
                _redis_mgr->set_log(_local_ip, pIt->second->get_processname(), UNAUTO_START, "手动重启", -1, "");
            }
    }
    else
    {
        //生成节点（之前没有注册过的，但是客户端有请求启动了的）
        process_node_t* pNode = new process_node_t(_redis_mgr, path, -1, false, 15000); 
        _nodes[path] = pNode;
        //通过名称杀死进程
        pNode->kill_by_path(path);
        pNode->reboot();

        if (_redis_mgr)
        {
            _redis_mgr->set_log(_local_ip, pNode->get_processname(), UNAUTO_START, "手动重启", -1, "");
        }
    }
}

void dahlia::process_mgr_t::del( const string& path/*, int npid*/ )
{
    map<string , process_node_t* >::iterator pIt = _nodes.find(path);//path,pid,nodeinfo
    if (pIt != _nodes.end())
    {
        //更新时间
       // pIt->second->stop();
        delete pIt->second;
        _nodes.erase(pIt);
    }
}
