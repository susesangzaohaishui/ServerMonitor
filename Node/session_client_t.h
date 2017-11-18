#pragma once

#include <string>
using namespace std;

#include "globaldefine.h"

namespace dahlia
{
    class client_repar_t;
    class session_client_t
    {
    public:
        static session_client_t* instence();
        static void recv_data(int dwLinkAd, int  sockfd, int  dwBufSize, void*  pBuffer);
        static void status(int dwLinkAd, int sockfd, int dwBufSize, void* pBuffer);
        void    set_observer(client_repar_t* instence, const string& process_name_, unsigned int pid_);

        //发送心跳消息
        void heart();
        //注册进程信息
        void register_process();
        //发送网络数据
        void send_buff(char* buff, int size);

    private:
        client_repar_t* _daemon_instence;
        string          _process_name;
        unsigned int    _pid;
    private:
        session_client_t();
        ~session_client_t(void);
        session_client_t (const session_client_t&);
        const session_client_t &operator = (const session_client_t&);
    };

}