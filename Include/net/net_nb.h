#ifndef AMQ_NET_H
#define AMQ_NET_H
#include "i_linkinfo_t.h"

#if defined _WIN32
#   if defined NET_STATIC
#       define NET_EXPORT
#   elif defined DLL_EXPORT
#       define NET_EXPORT __declspec(dllexport)
#   else
#       define NET_EXPORT __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define NET_EXPORT __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define NET_EXPORT __attribute__ ((visibility("default")))
#   else
#       define NET_EXPORT
#   endif
#endif


typedef void (*PFN_RECV_DATA)(int       dwLinkAd,
							   int          sockfd,
                               int       dwBufSize,
							   void*        pBuffer
							   );

typedef void (*PFN_NET_STATUS)(int     dwLinkAd,
								 int        sockfd,
                                 int     dwBufSize,
								 void*      pBuffer
								 );

extern "C"
{
	 bool  NET_EXPORT net_init(
		 net::i_linkinfo_t& linkinfo,
		 PFN_RECV_DATA pRecvFunc,
		 PFN_NET_STATUS pStatusFunc
		 );

     void  NET_EXPORT net_asyn_send( int nLinkId,
		 int    sockfd,
         int    nLength,
		 char*  pBuffer);

	 void  NET_EXPORT net_sutdown();
}

#endif // AMQ_NET_H
