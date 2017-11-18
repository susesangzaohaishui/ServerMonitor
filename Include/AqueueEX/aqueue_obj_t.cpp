#include "aqueue_obj_t.h"
#include "aqueue_manager_t.h"

dahlia::aqueue_obj_t::aqueue_obj_t( const string& obj_id_, aqueue_manager_t* mgr_ ):
    _obj_id(obj_id_),
    _aobj_mgr(mgr_) 

{

}

dahlia::aqueue_obj_t::~aqueue_obj_t( void )
{

}

std::string dahlia::aqueue_obj_t::get_id()
{
    return _obj_id;
}

dahlia::aqueue_manager_t* dahlia::aqueue_obj_t::get_mgr()
{
    return _aobj_mgr;
}

void dahlia::aqueue_obj_t::add_timer( int tmid, int tmout )
{
    if (_aobj_mgr)
    {
        _aobj_mgr->regist_timer(get_id(), tmid, tmout);
    }
}

void dahlia::aqueue_obj_t::attach_event()
{
    on_attach();
}

void dahlia::aqueue_obj_t::dettach_event()
{
    on_detach();
}

void dahlia::aqueue_obj_t::timer_event( int id_ )
{
    on_time(id_);
}

void dahlia::aqueue_obj_t::msg_event( aqueue::aqueue_msg_t* msg )
{
    if (msg)
    {
        switch (msg->type)
        {
        case aqueue::aqueue_msg_t::common_msg:
            {
                //如果是命令消息
                on_msg(msg->msg_id,
                    msg->body.msg_common.lparam,
                    msg->body.msg_common.wparam);
            }
            break;
        case aqueue::aqueue_msg_t::short_msg:
            {
                //如果是短包消息
                on_msg(msg->msg_id,
                    (int)msg->body.msg_short.msg_buf,
                    msg->body.msg_short.msg_len);
            }
            break;
        case aqueue::aqueue_msg_t::long_msg:
            {
                //如果是长包消息
                on_msg(msg->msg_id,
                    (int)msg->body.msg_long.msg_buf,
                    msg->body.msg_long.msg_len);
            }
            break;
        }
    }
}
