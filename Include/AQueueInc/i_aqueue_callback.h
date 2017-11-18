#ifndef __AQUEUE_I_CALLBACK_HPP_INCLUDED__
#define __AQUEUE_I_CALLBACK_HPP_INCLUDED__
//异步对象回调接口
class i_asynobj_events
{
public:
	//对象附加成功事件（在附加成功的线程执行）
	virtual void attach_event () = 0;

	//对象线程分离成功事件（在附加的线程中执行，以免资源释放跨线程）
	virtual void dettach_event () = 0;

	//定时事件
	virtual void timer_event (int id_) = 0;

	//消息事件
    virtual void msg_event(aqueue::aqueue_msg_t* msg) = 0;
};
#endif
