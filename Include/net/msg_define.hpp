#ifndef __NET_MSG_HPP_INCLUDED__
#define __NET_MSG_HPP_INCLUDED__
namespace net
{
	//队列消息
	enum
	{
        queue_msg_net_data,     //网络消息
		 queue_msg_send_data      //发送网络数据
	};

	struct queue_msg_header
	{
		union
		{
			struct {
				int    linkid;
				int    fd;
				int    buflen;
			}msg_send;
		};
	};

	struct net_msg_header
	{
		unsigned short  start_code   ;   //  起始代码
		unsigned short  msg_len  ;      //  数据长度
		unsigned short  src_addr  ;     //  源地址
		unsigned short  dst_addr  ;     //  目的地址
		unsigned short  cmd_order ;     //  命令号
		unsigned short  cmd_code   ;    //  命令码
		unsigned short  version     ;   //  版本号
		unsigned char   attribute   ;   //  属性
		unsigned char   msg_seq ;       //  报文序号
		unsigned short  frame_number  ;  //  总包数
		unsigned short  frame_seq;      //  当前包号
		net_msg_header()
		{
            memset(this, 0, sizeof(net_msg_header));
			start_code = 0x7e7e;
		}
	};

	struct net_msg_end
	{
		net_msg_end()
		{
			crc = 0;
			end = 0x0A0D;
		}
		unsigned short crc;
		unsigned short end;
	};
}
#endif
