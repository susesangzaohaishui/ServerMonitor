#pragma once

#include <string>
#include <map>
#include "process_node_t.h"

using namespace std;

namespace dahlia
{
    class redis_client_t;
    class process_mgr_t
    {
    public:
        process_mgr_t(redis_client_t* redis_mgr_);
        ~process_mgr_t(void);

        //注册节点
        void register_node(const string& path, int npid, bool timeout_reboot_, int check_tick_);

        //处理心跳
        void heart(const string& path, int npid);

        //定时检测
        void check();

        //停止进程
        void stop(const string& path/*, int npid*/);

        //启动进程
        void start(const string& path/*, int npid*/);

        //删除进程信息
        void del(const string& path/*, int npid*/);
    public:
        string          _local_ip;//本地ip地址
    private:
        process_mgr_t (const process_mgr_t&);
        const process_mgr_t &operator = (const process_mgr_t&);
    private:
        redis_client_t* _redis_mgr;
        map<string , process_node_t* > _nodes;//path,pid,nodeinfo
        bool            _reboot_flag;//长期没有上报心跳的处理方式true为重启,false为不重启
    };
}