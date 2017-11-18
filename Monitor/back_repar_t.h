#pragma once

#include "aqueue_obj_t.h"
#include "globaldefine.h"

namespace dahlia
{
    class redis_client_t;
    class process_mgr_t;
    class back_repar_t : public aqueue_obj_t
    {
    public:
        back_repar_t(const string& obj_id_, aqueue_manager_t* mgr_);
        virtual ~back_repar_t(void);

        virtual void on_time(int id);  

        virtual void on_attach();  

        virtual void on_detach();  

        virtual void on_msg(int cmd_, int lparm_, long wparam_);  

        void on_proc_client(const string& key_);
        void on_proc_client( const opreate_process* process_ );
    private:
        //处理心跳
        void proc_heart(const nodemsg_heart* pmsg);
        //处理注册信息
        void proc_register(const nodemsg_register* regis);
        //注册节点
        void register_node(const string& path, int npid);

        //定时检测
        void proc_check();

        //停止进程
        void proc_stop(const string& path);

        //启动进程
        void proc_start(const string& path);

        //删除进程信息
        void proc_del(const string& path);

    private:
        back_repar_t (const back_repar_t&);
        const back_repar_t &operator = (const back_repar_t&);
    private:
        redis_client_t* _redis_mgr;
        process_mgr_t*  _process_mgr;
    };
}