#pragma once

#ifdef ACTCTRL_BASE_EXPORTS
#define ACTCTRL_BASE_API __declspec(dllexport)
#else
#define ACTCTRL_BASE_API __declspec(dllimport)
#endif

namespace dahlia
{
    class aqueue_manager_t;
    class client_repar_t;
    class ACTCTRL_BASE_API daemon_client_t
    {
    public:
        daemon_client_t(void);
        ~daemon_client_t(void);

        bool  create_monitor();
    private:

        aqueue_manager_t*   _aqueue_mgr;
        client_repar_t*     _repar;
    };

}