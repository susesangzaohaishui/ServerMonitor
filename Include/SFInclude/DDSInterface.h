#pragma once

#include <string>
using namespace std;


#ifdef DDS_EXPORTS
	#define DDS_API extern "C" __declspec(dllexport)
#else
	#define DDS_API extern "C" __declspec(dllimport)
#endif

//8 bytes struct member alignment
#pragma pack( push, enter_include1 )
#pragma pack(8)

#ifndef CALLBACK
	#define CALLBACK __stdcall
#endif

//////////////////////////////////////////////////////////////////////

//字符串
typedef string							DDS_STRING;

//组件编号
typedef unsigned long					DDS_COMPONENT_NUMBER;

//////////////////////////////////////////////////////////////////////

//数据接收回调函数原型
//ucFuncCallMode		(输入)	回调函数调用模式
//								0: 异步调用(总线调用回调函数的线程与总线接收数据的线程不是同一个)
//								1: 同步调用(总线调用回调函数的线程与总线接收数据的线程为同一个)
//								3: 阻塞接受(用户主动调用接口，阻塞接受数据)
//								其它：预留参数值
//domainName			(输入)域名称
//topicName				(输入)主题名称
//componentNumber		(输入)组件编号
//pBuf					(输入)数据缓冲区
//ulBufSize				(输入)数据缓冲区长度
//pStatusBuf			(输入)状态缓冲区
//ulStatusBufSize		(输入)状态缓冲区长度
typedef void (CALLBACK* DDS_PFN_RECV_DATA)(unsigned char				ucFuncCallMode, 
										   DDS_STRING					domainName, 
										   DDS_STRING					topicName, 
										   const DDS_COMPONENT_NUMBER	&componentNumber, 
										   const char					*pBuf, 
										   unsigned long				ulBufSize, 
										   const char					*pStatusBuf, 
										   unsigned long				ulStatusBufSize);

//////////////////////////////////////////////////////////////////////
//
// 返回值说明：
// 除非特别说明，接口函数均返回 bool 类型，true 表示成功，false 表示失败
//
// 错误信息管理说明：
// 框架调用接口函数失败时，可通过 FrameGetLastError、 FrameGetErrorMsg 及 FrameGetLastErrorMsg 获取错误信息
// 组件调用接口函数失败时，可通过 ComponentGetLastError、 ComponentGetErrorMsg 及 ComponentGetLastErrorMsg 获取错误信息
//
//////////////////////////////////////////////////////////////////////

//组件标识
struct sComponentKey
{
	//域名称
	DDS_STRING				m_strDomainName;

	//组件编号
	DDS_COMPONENT_NUMBER	m_componentNumber;


	sComponentKey() : m_strDomainName(""), m_componentNumber(0)
	{
	}

	sComponentKey(DDS_STRING strDomainName, 
		DDS_COMPONENT_NUMBER componentNumber) : 
		m_strDomainName(strDomainName), m_componentNumber(componentNumber)
	{
	}

	sComponentKey(const sComponentKey& r)
	{
		*this = r;
	}

	sComponentKey& operator=(const sComponentKey& r)
	{
		if (this == &r)
		{
			return (*this);
		}

		m_strDomainName		= r.m_strDomainName;
		m_componentNumber	= r.m_componentNumber;

		return (*this);
	}

	bool operator==(const sComponentKey& r) const
	{
		if (m_strDomainName	== r.m_strDomainName &&
			m_componentNumber == r.m_componentNumber)
		{
			return true;
		} else {
			return false;
		}
	}

	bool operator<(const sComponentKey& r) const
	{
		//第一维
		if (m_strDomainName	< r.m_strDomainName)
		{
			return true;
		} else if (m_strDomainName > r.m_strDomainName) {
			return false;
		} else {
			//第二维
			if (m_componentNumber < r.m_componentNumber)
			{
				return true;
			} else if (m_componentNumber > r.m_componentNumber) {
				return false;
			} else {
				return false;
			}
		}
	}
};

//////////////////////////////////////////////////////////////////////
//
//框架使用的总线接口
//
//////////////////////////////////////////////////////////////////////

//框架初始化总线
//strLocalAppName			(输入)本地应用(进程)名称，最长不超过32字节
//strLocalSeatName			(输入)本地席位(主机)名称，最长不超过32字节
//strInterfaceType			(输入)接口描述字符串，最长不超过32字节
//ucHighVersion				(输入)高版本号
//ucLowVersion				(输入)低版本号
DDS_API 
bool FrameInitBus(DDS_STRING strLocalAppName, 
				  DDS_STRING strLocalSeatName = "",	
				  DDS_STRING strInterfaceType = "WS_ES_8CA_IDOMAIN_1", 
				  unsigned char ucHighVersion = 0, 
				  unsigned char ucLowVersion = 1);

//框架退出总线
DDS_API 
bool FrameExitBus(void);

//////////////////////////////////////////////////////////////////////

//框架加入域
//说明：需要时，可通过不同参数多次调用本接口，将同一框架加入多个域
//strDomainName				(输入)域名称，最长不超过32字节
DDS_API 
bool FrameJoinDomain(DDS_STRING strDomainName);

//框架离开域
//strDomainName				(输入)域名称，最长不超过32字节
DDS_API 
bool FrameLeaveDomain(DDS_STRING strDomainName);

//////////////////////////////////////////////////////////////////////

//获取最新错误号
//strDomainName				(输入)域名称，最长不超过32字节
DDS_API 
unsigned long FrameGetLastError(DDS_STRING strDomainName);

//获取错误文本描述
//strDomainName				(输入)域名称，最长不超过32字节
//ulErrorNumber				(输入)错误号，最长不超过32字节
//strErrorText				(输出)错误文本描述
DDS_API 
bool FrameGetErrorMsg(DDS_STRING strDomainName, 
					  unsigned long ulErrorNumber, 
					  DDS_STRING &strErrorText);

//获取最新错误文本描述
//strDomainName				(输入)域名称，最长不超过32字节
//strErrorText				(输出)错误文本描述
DDS_API 
bool FrameGetLastErrorMsg(DDS_STRING strDomainName, 
						  DDS_STRING &strErrorText);


//////////////////////////////////////////////////////////////////////
//
//组件使用的总线接口
//
//////////////////////////////////////////////////////////////////////

//组件加入域
//说明：需要时，可通过不同参数多次调用本接口，将同一组件加入多个域
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
DDS_API 
bool ComponentJoinDomain(DDS_STRING strDomainName, 
						 DDS_STRING strComponentName);

//组件离开域
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
DDS_API 
bool ComponentLeaveDomain(DDS_STRING strDomainName, 
						  DDS_STRING strComponentName);

//////////////////////////////////////////////////////////////////////

//注册组件
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
//componentNumber			(输出)组件编号
DDS_API 
bool RegisterComponent(DDS_STRING strDomainName, 
					   DDS_STRING strComponentName, 
					   DDS_COMPONENT_NUMBER &componentNumber);

//注销组件
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
//componentNumber			(输入)组件编号
DDS_API 
bool UnregisterComponent(DDS_STRING strDomainName, 
						 DDS_STRING strComponentName, 
						 const DDS_COMPONENT_NUMBER &componentNumber);

//////////////////////////////////////////////////////////////////////

//组件打开主题对象
//componentKey				(输入)组件标识
//strTopicName				(输入)主题名称，最长不超过32字节
DDS_API 
bool OpenTopic(const sComponentKey &componentKey, 
			   DDS_STRING strTopicName);

//组件关闭主题对象
//componentKey				(输入)组件标识
//strTopicName				(输入)主题名称，最长不超过32字节
DDS_API 
bool CloseTopic(const sComponentKey &componentKey, 
				DDS_STRING strTopicName);

//////////////////////////////////////////////////////////////////////

//组件发布主题
//componentKey				(输入)组件标识
//strTopicName				(输入)主题名称，最长不超过32字节
DDS_API 
bool PublishTopic(const sComponentKey &componentKey, 
				  DDS_STRING strTopicName);

//组件取消发布主题
//componentKey				(输入)组件标识
//strTopicName				(输入)主题名称，最长不超过32字节
DDS_API 
bool UnpublishTopic(const sComponentKey &componentKey, 
					DDS_STRING strTopicName);

//组件订阅主题
//componentKey				(输入)组件标识
//strTopicName				(输入)主题名称
DDS_API 
bool SubscribeTopic(const sComponentKey &componentKey, 
					DDS_STRING strTopicName);

//组件取消订阅主题
//componentKey				(输入)组件标识
//strTopicName				(输入)主题名称，最长不超过32字节
DDS_API 
bool UnsubscribeTopic(const sComponentKey &componentKey, 
					  DDS_STRING strTopicName);

//////////////////////////////////////////////////////////////////////

//发送主题数据
//componentKey				(输入)组件标识，最长不超过32字节
//strTopicName				(输入)主题名称，最长不超过32字节
//pSendBuf					(输入)数据缓冲区
//ulSendSize				(输入)数据长度
//ucMode					(输入)发送模式
//								0 异步发送(总线异步线程完成实际的数据发送)
//								1 同步发送(数据送入底层操作系统缓存后返回)
//								其它：预留参数值
DDS_API 
bool SendData(const sComponentKey &componentKey,
			  DDS_STRING strTopicName, 
			  char *pSendBuf, 
			  unsigned long ulSendSize, 
			  unsigned char ucMode = 1);

//注册节点数据接收回调函数
//componentKey				(输入)组件标识
//pFunc						(输入)回调函数指针
//ucFuncCallMode			(输入)回调函数调用模式
//  	   						0: 异步调用(总线调用回调函数的线程与总线接收数据的线程不是同一个)
//								1: 同步调用(总线调用回调函数的线程与总线接收数据的线程为同一个)
//								其它：预留参数值
DDS_API 
bool RegRecvNodeDataCallbackFunc(const sComponentKey &componentKey, 
								 DDS_PFN_RECV_DATA pFunc, 
								 unsigned char ucFuncCallMode = 1);

//注销节点数据接收回调函数
//componentKey				(输入)组件标识
//pFunc						(输入)回调函数指针
DDS_API 
bool UnregRecvNodeDataCallbackFunc(const sComponentKey &componentKey,
								   DDS_PFN_RECV_DATA pFunc);

//////////////////////////////////////////////////////////////////////

//获取最新错误号
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
DDS_API 
unsigned long ComponentGetLastError(DDS_STRING strDomainName,  
									DDS_STRING strComponentName);

//获取错误文本描述
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
//ulErrorNumber				(输入)错误号
//strErrorText				(输出)错误文本描述
DDS_API 
bool ComponentGetErrorMsg(DDS_STRING strDomainName,  
						  DDS_STRING strComponentName, 
						  unsigned long ulErrorNumber, 
						  DDS_STRING &strErrorText);

//获取最新错误文本描述
//strDomainName				(输入)域名称，最长不超过32字节
//strComponentName			(输入)组件名称，最长不超过32字节
//strErrorText				(输出)错误文本描述
DDS_API 
bool ComponentGetLastErrorMsg(DDS_STRING strDomainName,  
							  DDS_STRING strComponentName, 
							  DDS_STRING &strErrorText);

//////////////////////////////////////////////////////////////////////

#pragma pack( pop, enter_include1 )
