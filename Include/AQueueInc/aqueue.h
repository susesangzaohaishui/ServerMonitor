

#ifndef __AQUEUE_H_INCLUDED__
#define __AQUEUE_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#if !defined WINCE
#include <errno.h>
#endif
#include <stddef.h>
#include <stdio.h>
#include "aqueue_msg.h"
#include "i_aqueue_callback.h"

/*
	@AUTHOR:AdamZhao
*/
//简易异步消息队列的实现(改造自Zeromq)
//暂时还有很多地方不稳定，待后续更新，注意参数信息越界,未做过多保护
//使用时请谨慎，避免多个线程之间有资源交集降低使用效率

//初衷与提升：
//1、是哪个线程的东西就在哪个线程中处理，保证线程之间没有数据竞争，从而提高整体效率; 
//2、保证线程内部的顺序执行，没有系统同步和中断;
//3、通过IO复用来管理多个线程间的消息传递，从而形成多个线程的消息主动推送能力；
//4、使用无锁队列，提高数据队列的传输速度（内存优化（尽量减少分配与释放的频率），原子操作优化(队列原子无锁操作)）；
//

#if defined _WIN32
#   if defined DLL_EXPORT
#       define AQUEUE_EXPORT __declspec(dllexport)
#   else
#       define AQUEUE_EXPORT __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define AQUEUE_EXPORT __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define AQUEUE_EXPORT __attribute__ ((visibility("default")))
#   else
#       define AQUEUE_EXPORT
#   endif
#endif

#define AQUEUE_IO_THREADS       1
#define AQUEUE_IO_THREADS_DFLT  1
#define AQUEUE_ASYNOBJ_ID_MIN   1
#define AQUEUE_ASYNOBJ_ID_MAX   100

//建议线程类型，实际都是全功能的
//不做强制定义
enum thread_type
{
		e_msg,//建议消息为主任务的线程
		e_timer,//建议定时器为主任务的线程
		e_other = -1//建议全功能选取
};

//创建上下文
AQUEUE_EXPORT void *aqueue_ctx_new (void);

//根据用户输入线程数创建上下文,（以消息为主线的线程，和以定时器为主线的线程(建议)）
AQUEUE_EXPORT void *aqueue_init (int io_msg_threads, int io_timer_threads);

//启动线程
AQUEUE_EXPORT int  aqueue_start(void *context);

//销毁上下文
AQUEUE_EXPORT int  aqueue_ctx_destroy (void *context);

//将对象附加到某一线程中去
AQUEUE_EXPORT int  aqueue_attach_asynobject(const char* oid, i_asynobj_events* sink_, void *context, thread_type t_type = e_msg);

//分离对象
AQUEUE_EXPORT int  aqueue_dettach_asynobject(const char* oid, void *context);

//向某对象发送消息
AQUEUE_EXPORT int  aqueue_send_msg(const char* oid, aqueue::aqueue_msg_t* msg, void *context,bool exigence = false);

//为某对象注册定时器
AQUEUE_EXPORT int  aqueue_register_timer(const char* oid, int timeout_, int id_, void *context);

//删除定时器
AQUEUE_EXPORT int  aqueue_unregister_timer(const char* oid, int id_, void *context);

//发送同步消息
AQUEUE_EXPORT int syn_send_msg( const char* oid, aqueue::aqueue_msg_t* msg, void *context );

#undef AQUEUE_EXPORT

#ifdef __cplusplus
}
#endif

#endif

