#include "client_repar_t.h"
#include "session_client_t.h"
#include "dahlia_utils.h"
#define PROCESS_LIVE_TIMER 10

dahlia::client_repar_t::client_repar_t( const string& obj_id_, aqueue_manager_t* mgr_ ):
    aqueue_obj_t(obj_id_, mgr_)
{
   
}

dahlia::client_repar_t::~client_repar_t( void )
{

}

void dahlia::client_repar_t::on_time( int id )
{
    if (PROCESS_LIVE_TIMER == id)
    {
        if (_session)
        {
           _session->heart();
        }
        add_timer(PROCESS_LIVE_TIMER, 4000);
    }
}

void dahlia::client_repar_t::on_attach()
{
    //定时发送心跳消息
    add_timer(PROCESS_LIVE_TIMER, 4000);

    _session = session_client_t::instence();
    _session->set_observer(this, get_app_name(), get_current_pid());
}

void dahlia::client_repar_t::on_detach()
{

}

void dahlia::client_repar_t::on_msg( int cmd_, int lparm_, long wparam_ )
{

}
