#pragma once
#include "globaldefine.h"
namespace dahlia
{
    class session_server_t;
    class aqueue_manager_t;
    class aqueue_obj_t;
    class daemon_instence_t
    {
    public:
        daemon_instence_t(void);
        ~daemon_instence_t(void);
        //处理心跳
        void on_proc_hearts(const nodemsg_heart* heart);
        //处理注册信息
        void on_proc_register(const nodemsg_register* );
    private:
        void init();
    private:
        //服务实例
        session_server_t*   _heart_server;
        //异步对象管理实例
        aqueue_manager_t*   _aqueue_mgr;
        //进程监控管理对象
        aqueue_obj_t*       _process_mgr;
    private:
        daemon_instence_t (const daemon_instence_t&);
        const daemon_instence_t &operator = (const daemon_instence_t&);
    };
}