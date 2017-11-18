#pragma once

namespace dahlia
{
    class daemon_instence_t;
    class session_server_t
    {
    public:
        static session_server_t* instence();

        static void recv_data(int dwLinkAd, int  sockfd, int  dwBufSize, void*  pBuffer);
        static void status(int dwLinkAd, int sockfd, int dwBufSize, void* pBuffer);
        void    set_observer(daemon_instence_t* instence);
    private:
        daemon_instence_t* _daemon_instence;
    private:
        session_server_t();
        ~session_server_t(void);
        session_server_t (const session_server_t&);
        const session_server_t &operator = (const session_server_t&);
    };

}