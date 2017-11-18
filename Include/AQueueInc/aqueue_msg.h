#ifndef __AQUEUE_MSG_H_INCLUDED__
#define __AQUEUE_MSG_H_INCLUDED__

#define USE_MSG

namespace aqueue
{

    struct aqueue_msg_t
	{
		int msg_id;
		enum msg_type_t
		{
			common_msg,
#if defined(USE_MSG)
			short_msg,
			long_msg
#endif
		}type;
		union 
		{
			struct 
			{
				long wparam;
				long lparam;
			}msg_common;

#if defined(USE_MSG)
			struct 
			{
				int  msg_len;
				char msg_buf[512];
			}msg_short;

			struct
			{
				int   msg_len;
				char* msg_buf;
			}msg_long;
#endif
		}body;
	};
}

#endif
