#pragma once

#include <string>
#include <stdint.h>
#include "globaldefine.h"
using namespace std;

namespace dahlia
{
    class redis_client_t;
    class process_node_t
    {
    public:
        process_node_t(redis_client_t* redis_mgr_, 
            const string& spath_,
            int pid_, 
            bool timeout_reboot_,
            unsigned int check_time
            );
        ~process_node_t(void);
        //更新时间
        void update_time();
        //进程当前状态
        bool check(int& mem);
        //重启进程
        bool reboot();
        //停止进程
        void stop();
        //终止进程
        bool termate();
        //检测窗口是否包含断言窗口
        bool  contins_assert_wnd();

        string get_path();
        string get_processname();
        std::string get_processname(const string& spath_);
    public:
        bool kill_by_path(const string& spath_);
    private:

    public:
        string          _process_name;//进程路径加名称
        unsigned int    _pid;//pid
        bool            _be_reload;//是否加载
        bool            _timeout_reboot;
        uint64_t        _lastupdate_ticket;//最近更新时间
        int             _heart_check_tick;//心跳超时检测
        PROCESS_STATE   _state;
    private:
        process_node_t (const process_node_t&);
        const process_node_t &operator = (const process_node_t&);
        //启动进程,创建进程
        bool start();
    private:
        redis_client_t* _redis_mgr;
    };
}