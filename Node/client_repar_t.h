#pragma once
#include "aqueue_obj_t.h"
#include "globaldefine.h"

namespace dahlia
{
    class session_client_t;
    class client_repar_t : public aqueue_obj_t
    {
    public:
        client_repar_t(const string& obj_id_, aqueue_manager_t* mgr_);
        virtual ~client_repar_t(void);

        virtual void on_time(int id);  

        virtual void on_attach();  

        virtual void on_detach();  

        virtual void on_msg(int cmd_, int lparm_, long wparam_);  
    private:
        session_client_t* _session;
    private:
        client_repar_t (const client_repar_t&);
        const client_repar_t &operator = (const client_repar_t&);
    };

}