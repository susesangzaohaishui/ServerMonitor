#ifndef __NET_I_LINKINFO_INCLUDED__
#define __NET_I_LINKINFO_INCLUDED__
#include <string.h>
namespace net
{
	enum
	{
		LT_TCP_CLIENT   =   0,
		LT_TCP_SERVER   =   1,
		LT_UDP          =   2
	};
	struct i_linkinfo_t
	{
        int              m_nLinkId;
        int              m_bIsOpen;
        int              m_nLinkType;
        int              m_bIsCheckNet;
        int              m_NetCheckTimeOut;
        int              m_reconTime;
        char             m_strHostIp[64];
        char             m_strRemoteIp[64];
        int              m_nRemotePort;
        int		         m_nHostPort;
		i_linkinfo_t()
		{
			memset(this, 0, sizeof(i_linkinfo_t));
			m_bIsOpen      = 1;
			m_bIsCheckNet  = 1;
			m_reconTime    = 3000;
		}
	};
}
#endif
