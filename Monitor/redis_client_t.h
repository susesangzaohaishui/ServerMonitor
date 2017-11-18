#pragma once

#include <map>
#include <string>
#include "globaldefine.h"
#include <stdint.h>

using namespace std;

namespace acl
{
    class IDataService;
};


namespace dahlia
{
    class nb_mutex_t;
    class back_repar_t;
    class redis_client_t
    {
    public:
        redis_client_t(void);
        ~redis_client_t(void);

        //初始化redis
        bool init_redis();

        static redis_client_t* instence();

        //设置消息接收处理的观察者
        void   set_observer(back_repar_t* );

        //连接redis
        bool connect_redis();

        //加载配置
        bool load_config();

        //通过本地配置获取
        bool load_config_fromlocal();

        //发布消息
        void publish_msg( const char* channel,const char* szMsg );
        
        //清理一个频道
        bool clear_channels(const string& channel);

        //将进程信息推送到redis（path）
        bool send_process_state(const string& key, const redis_process_state& hearts );

        //处理客户端操作
        static void on_proc_client(const string& key_);

        bool querry_Buff(const string& key, char** buff, unsigned int& len);

        void clear_monitor(const std::string& s_ip);

        void set_log(  
           const string& s_ip,//ip
            const string& s_process,//进程名称
            LOG_TYPE log_state,//进程状态
           const string& s_info,//信息,自动重启，手动重启，断言，
            int     n_type,//扩展数据流类型
            const string& s_data_exten);//扩展数据

        void set_log(const montior_log_redis&);

    public:
        uint64_t	_last_con_tick;//最近一次连接时间
        static string		_service_ip;    //服务IP
        static int			_service_port;  //服务端口
    public:
        acl::IDataService*  _redis_instence;
        nb_mutex_t*		    _redis_reg_lock;//创建实例锁
        back_repar_t*       _reper_observer;
    private:
        redis_client_t (const redis_client_t&);
        const redis_client_t &operator = (const redis_client_t&);
    };
}
