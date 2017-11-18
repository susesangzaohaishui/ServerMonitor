#ifndef __MONTT__GLOBAL_DEFINE_HH___II
#define __MONTT__GLOBAL_DEFINE_HH___II

#include <string.h>
#include <string>
using namespace std;

#pragma pack(push , enter_includeglobal)
#pragma pack(1)

enum MSG_TYPE
{
    //心跳类型
    HEARTS_TYPE,
    //注册类型
    REGISTER_TYPE,
    //注销进程（删除节点，杀死进程）
    DELPROCESS_TYPE,
    //停止进程(只杀死进程，不清理注册信息)
    STOPPROCESS_TYPE,
    //启动进程(如果是重启，则需要向前台发送删除老进程信息，如果是直接启动则无需)
    STARTPROCESS_TYPE,
};

enum PROCESS_STATE
{
    STATE_UNKNUWN,  //未知
    STATE_RUNNING,      //挂掉
    STATE_ASSERTING,//有断言
    STATE_STOP,     //停止中
    STATE_LOCAL_OUT_TIME,//本地检测超时
    STATE_OUT_TIME, //心跳超时
    STATE_REBOOTING, //重启中
    STATE_MONITOR_HEART,//监视器心跳
};

enum BACK_MSG_TYPE
{
    DELETE_BACK_MSG,//删除消息回执
};

enum OPREATE_STATE
{
    FAILED_OPREATE = -1,
    OK_OPREATE
};

//数据包头
typedef struct  nodemsg_header_t
{
    MSG_TYPE type;//数据类型
    int      data_len;//数据长度
};

//心跳消息
typedef struct nodemsg_heart
{
    nodemsg_header_t header;//消息头
    unsigned int     pid;//进程ID
    char     ppath[1024];   //进程路径

    nodemsg_heart()
    {
        header.type = HEARTS_TYPE;
        header.data_len = sizeof(nodemsg_heart) - sizeof(nodemsg_header_t);
    }
};

//注册消息
typedef struct nodemsg_register
{
    nodemsg_header_t header;//消息头
    char     ppath[1024];   //进程路径
    unsigned int pid;       //进程Pid
    unsigned int timeout_reboot;//0超时不重启,其他重启
    unsigned int heart_check_tick;//心跳超时检测的时间

    nodemsg_register()
    {
        header.type = REGISTER_TYPE;
        header.data_len = sizeof(nodemsg_register) - sizeof(nodemsg_header_t);
        timeout_reboot = 0;
        heart_check_tick = 9000;
    }
};

//前台《-》监视器

//上行
//进程状态上报
typedef struct redis_process_state 
{
     char           ppath[1024];    //进程路径
     char           ip[32];         //监视器ip
     unsigned int   pid;            //进程Pid
     unsigned int   memcount;       //进程内存
     PROCESS_STATE  state;          //进程状态
     redis_process_state()
     {
        state = STATE_UNKNUWN;
        memset(this, 0, sizeof(redis_process_state));
     }
};

//监控回执
typedef struct  monitor_back
{
    char            ppath[1024];    //进程路径
    BACK_MSG_TYPE   opreatetye;     //回执类型
    OPREATE_STATE   opreate_result; //执行状态
};

//日志信息
enum LOG_TYPE
{
    AUTO_START,//自动重启
    UNAUTO_START,//手动重启
    ASSERTING_,//断言
    HEART_OUTTM,//心跳超时
    UNAUTO_DIE_,//手动关闭
    AUTO_DIE,//非手动进程关闭
    
};
typedef struct  montior_log_redis
{
    string s_ip;//ip
    string s_process;//进程名称
    LOG_TYPE log_state;//进程状态
    long    s_time;//时间
    string s_info;//信息,自动重启，手动重启，断言，
    int     n_type;//扩展数据流类型
    string  s_data_exten;//扩展数据
};

//下行
//进程操作
typedef struct  opreate_process
{
    char           ppath[1024];     //进程路径
    char           ip[32];         //监视器ip
    MSG_TYPE       msgtype;         //消息类型
    opreate_process()
    {
        memset(this, 0, sizeof(opreate_process));
    }
};



#pragma  pack(pop , enter_includeglobal)

#endif