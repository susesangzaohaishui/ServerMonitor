#include "daemon_instence_t.h"

#include "back_repar_t.h"
#include "session_server_t.h"
#include "aqueue_manager_t.h"


dahlia::daemon_instence_t::daemon_instence_t( void ):
_process_mgr(NULL)
{
    //初始化
    init();
}

dahlia::daemon_instence_t::~daemon_instence_t( void )
{

}

void dahlia::daemon_instence_t::on_proc_hearts( const nodemsg_heart* heart )
{
    if (_process_mgr)
    {
        nodemsg_heart* pHeart = new nodemsg_heart;
        memcpy(pHeart, heart, sizeof(nodemsg_heart));

        _aqueue_mgr->send_long_buff(
            _process_mgr->get_id(), 
            HEARTS_TYPE, pHeart,
            sizeof(nodemsg_heart));
    }

}

void dahlia::daemon_instence_t::on_proc_register( const nodemsg_register* regist_)
{
    if (_process_mgr)
    {
        nodemsg_register* pRegist = new nodemsg_register;
        memcpy(pRegist, regist_, sizeof(nodemsg_register));

        _aqueue_mgr->send_long_buff(
            _process_mgr->get_id(), 
            REGISTER_TYPE, pRegist,
            sizeof(nodemsg_register));
    }
}

void dahlia::daemon_instence_t::init()
{
    //异步对象管理实例
    _aqueue_mgr = new aqueue_manager_t(2, 0);

    //进程监控管理对象
    _process_mgr = new back_repar_t("process_mgr_aobj", _aqueue_mgr);
    _aqueue_mgr->attach_obj(_process_mgr);

    //服务实例
    _heart_server = session_server_t::instence();
    _heart_server->set_observer(this);
}
