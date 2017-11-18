#include "back_repar_t.h"
#include "redis_client_t.h"
#include "process_mgr_t.h"
#include "aqueue_manager_t.h"
#define PROCESS_LIVE_TIMER 10
#define REDIS_CONNECT_STATE 11

dahlia::back_repar_t::back_repar_t( 
    const string& obj_id_, 
    aqueue_manager_t* mgr_ ):
aqueue_obj_t(obj_id_, mgr_)
{
    _redis_mgr = redis_client_t::instence();
    _redis_mgr->set_observer(this);
    
    //_redis_mgr->init_redis();
    _process_mgr = new process_mgr_t(_redis_mgr);
}

dahlia::back_repar_t::~back_repar_t( void )
{
}

void dahlia::back_repar_t::on_attach()
{
    //检测进程存活情况
    add_timer(PROCESS_LIVE_TIMER, 4000);

    //检测redis连接情况
    add_timer(REDIS_CONNECT_STATE, 15000);

}

void dahlia::back_repar_t::on_detach()
{

}

void dahlia::back_repar_t::on_msg( int cmd_, int lparm_, long wparam_ )
{
    switch (cmd_)
    {
        //心跳类型
    case HEARTS_TYPE:
        {
            nodemsg_heart* pmsg = (nodemsg_heart*)lparm_;
            if (pmsg)
            {
                proc_heart(pmsg);
                delete pmsg;
            }
        }
        break;
        //注册类型
    case REGISTER_TYPE:
        {
            nodemsg_register* pmsg = (nodemsg_register*)lparm_;
            if (pmsg)
            {
                proc_register(pmsg);
                delete pmsg;
            }
        }
        break;
        //删除进程
    case DELPROCESS_TYPE:
        {
            opreate_process* pmsg = (opreate_process*)lparm_;
            if (pmsg)
            {
                proc_del(pmsg->ppath);
                delete pmsg;
            }
        }
        break;
        //停止进程(只杀死进程，不清理注册信息)
    case  STOPPROCESS_TYPE:
        {
            opreate_process* pmsg = (opreate_process*)lparm_;
            if (pmsg)
            {
                proc_stop(pmsg->ppath);
                delete pmsg;
            }
        }
        break;
        //启动进程(如果是重启，则需要向前台发送删除老进程信息，如果是直接启动则无需)
    case  STARTPROCESS_TYPE:
        {
            opreate_process* pmsg = (opreate_process*)lparm_;
            if (pmsg)
            {
                proc_start(pmsg->ppath);
                delete pmsg;
            }
        }
        break;
    }
}
void dahlia::back_repar_t::on_time( int id )
{
    switch (id)
    {
        //心跳类型
    case PROCESS_LIVE_TIMER:
        {
            proc_check();

            //检测进程存活情况
            add_timer(PROCESS_LIVE_TIMER, 5000);
        }
        break;
        //注册类型
    case REDIS_CONNECT_STATE:
        {
            //检测redis连接情况
            if (_redis_mgr)
            {
                _redis_mgr->connect_redis();
            }
            add_timer(REDIS_CONNECT_STATE, 15000);
        }
        break;
    }
}

void dahlia::back_repar_t::proc_heart( const nodemsg_heart* pmsg )
{
    if (!pmsg &&
        _process_mgr)
    {
        return;
    }

    _process_mgr->heart(pmsg->ppath, pmsg->pid);
}

void dahlia::back_repar_t::proc_register( const nodemsg_register* regis )
{
    if (!regis&&
        _process_mgr)
    {
        return;
    }

    bool breload_ = regis->timeout_reboot == 0 ? false : true; 
    _process_mgr->register_node(regis->ppath, regis->pid, breload_, regis->heart_check_tick);
}

void dahlia::back_repar_t::proc_check()
{
    if (!_process_mgr)
    {
        return;
    }
    _process_mgr->check();

}

void dahlia::back_repar_t::proc_stop( const string& path )
{
    if (!_process_mgr)
    {
        return;
    }
    _process_mgr->stop(path);
}

void dahlia::back_repar_t::proc_start( const string& path )
{
    if (!_process_mgr)
    {
        return;
    }
    _process_mgr->start(path);
}

void dahlia::back_repar_t::proc_del( const string& path)
{
    if (!_process_mgr)
    {
        return;
    }
    _process_mgr->del(path);
}

void dahlia::back_repar_t::on_proc_client( const opreate_process* process_ )
{
    if (process_ &&
        get_mgr())
    {
    }
    switch (process_->msgtype)
    {
    case  DELPROCESS_TYPE:
    case  STOPPROCESS_TYPE:
    case  STARTPROCESS_TYPE:
        {   
            get_mgr()->send_long_buff(get_id(), process_->msgtype, process_, sizeof(opreate_process));
        }
        break;
    }
}

void dahlia::back_repar_t::on_proc_client( const string& key_ )
{
    //获取数据
  

    char* buf = NULL;

    unsigned int nLen = sizeof(opreate_process);
    if(_redis_mgr->querry_Buff(key_, &buf, nLen))
    {
        if (buf)
        {
            opreate_process* process = new opreate_process;
            memcpy(process, buf, nLen);
            //查看是否操作本席位的监视器
            if (_process_mgr->_local_ip == process->ip)
            {
                on_proc_client(process);
            }
            delete[] buf;
        }
       
    }


}
