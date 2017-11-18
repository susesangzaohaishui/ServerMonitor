#include "session_server_t.h"
#include "daemon_instence_t.h"
#include "GlobalDefine.h"
#include "net_nb.h"
#include "msg_define.hpp"
#pragma comment(lib, "ws2_32.lib")

dahlia::session_server_t::session_server_t( ):
    _daemon_instence(NULL)
{
    //启动监控服务器
    net::i_linkinfo_t linkinfo;
    //开启网络检测
    linkinfo.m_bIsCheckNet = 0;
    //节点打开
    linkinfo.m_bIsOpen = 1;
    //检测网络的时间
    linkinfo.m_NetCheckTimeOut = 1000;
    //本地网络端口
    linkinfo.m_nHostPort = 65543;
    //节点ID
    linkinfo.m_nLinkId = 12;
    //类型为Tcp服务器
    linkinfo.m_nLinkType = net::LT_TCP_SERVER;
    //检测本地端口
    strcpy_s(linkinfo.m_strHostIp, "127.0.0.1");
    //重连时间
    linkinfo.m_reconTime = 3000;

    net_init(linkinfo, recv_data, status);
}

dahlia::session_server_t::~session_server_t( void )
{

}

dahlia::session_server_t* dahlia::session_server_t::instence()
{
    static dahlia::session_server_t server;
    return &server;
}

void dahlia::session_server_t::recv_data( int dwLinkAd, int sockfd, int dwBufSize, void* pBuffer )
{
    if (dahlia::session_server_t::instence() &&
        dahlia::session_server_t::instence()->_daemon_instence)
    {
        //解析数据
        if (dwBufSize >= sizeof(nodemsg_header_t))
        {
            net::net_msg_header* pNetHeader = (net::net_msg_header*)pBuffer;
            int nDataLen = dwBufSize - (sizeof(net::net_msg_header) + sizeof(net::net_msg_end));
            nodemsg_header_t* pHeader = (nodemsg_header_t*)((char*)pBuffer + sizeof(net::net_msg_header));
            switch (pHeader->type)
            {
                case HEARTS_TYPE://心跳消息
                    {
                        //判断数据长度
                        nodemsg_heart* pHeart = (nodemsg_heart*)pHeader;
                        //数据长度一致才做处理
                        if (nDataLen == sizeof(nodemsg_heart)&&
                            (sizeof(nodemsg_heart) - sizeof(nodemsg_header_t)) ==
                            pHeart->header.data_len) 
                        {
                            //向处理线程发送心跳消息
                            dahlia::session_server_t::instence()->_daemon_instence->on_proc_hearts(pHeart);
                        }
                    }
                    break;
                case REGISTER_TYPE://注册消息
                    {
                        //判断数据长度
                        nodemsg_register* pRegister = (nodemsg_register*)pHeader;
                        //数据长度一致才做处理
                        if (nDataLen == sizeof(nodemsg_register)&&
                            (sizeof(nodemsg_register) - sizeof(nodemsg_header_t)) ==
                            pRegister->header.data_len) 
                        {
                            //向处理线程发送心跳消息
                            dahlia::session_server_t::instence()->_daemon_instence->on_proc_register(pRegister);
                        }
                    }
                    break;
            }
        }
    }
}

void dahlia::session_server_t::status( int dwLinkAd, int sockfd, int dwBufSize, void* pBuffer )
{
    if (dahlia::session_server_t::instence() &&
        dahlia::session_server_t::instence()->_daemon_instence)
    {
        //连接断开为1
        //连接超时也为1
        //连接上为0
        //有客户端来连接也为0
    }
}

void dahlia::session_server_t::set_observer( daemon_instence_t* instence )
{
    _daemon_instence = instence;
}
