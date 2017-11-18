/************************************************************************/
/* 异步对象操作类																									*/
/************************************************************************/
#pragma once

#include "aqueue.h"
#include <iostream>

using namespace std;

namespace dahlia
{
    class aqueue_obj_t;

    class   aqueue_manager_t
    {
    public:
        aqueue_manager_t(int _msg_count, int _timer_count);
        virtual ~aqueue_manager_t(void);

        //向异步对象发送消息
        int send_cmd(const string& id,  int _msg_id, int _lparam, long _wparam);

        //向异步对象发送Buff(小于512字节)
        int send_short_buff(const string& id,  int _msg_id, const void* _buff, long _length);

        //发送堆上分配的长字节数据(记得对数据的释放)
        int send_long_buff(const string& id,  int _msg_id, const void* _buff, long _length);

        //注册定时器
        int regist_timer(const string& id, int _timer_id, int _time_out);

        //取消定时器
        int unregist_timer(const string& id,  int _timer_id);

        //附加对象到线程 
        int attach_obj(aqueue_obj_t* _obj, thread_type _type = e_msg);

        //分离线程
        int detch_obj(const string& id);

    private:
        void*       _ctx;//上下文对象
        int		    _msgs;//消息线程
        int         _timers;//定时器线程
    private:
        aqueue_manager_t (const aqueue_manager_t&);
        const aqueue_manager_t &operator = (const aqueue_manager_t&);
    };
}