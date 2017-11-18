#pragma once

#include <string>
#include <vector>
#include <map>
#include <google/protobuf/message.h>
#include "hiredis.h"

using namespace std;
#pragma pack(8)
namespace acl
{
    //发布订阅结构定义
	typedef struct subpubInfo 
	{
		string channel;//订阅频道
		string message;//消息
	}subpub;

	/************************************************************************/
	/*@brief 收到订阅信息后回调函数
	/*@param[in] rcvChannel 单个或多个订阅的频道
	/*@param[in] rcvmessage 收到的订阅消息
	/*@return true 操作成功 false 操作失败
	/************************************************************************/	
	typedef int (redisSubscribeCallback)(string rcvChannel,string rcvMessage);	

//数据服务接口
class  __declspec(dllexport) IDataService
{
public:

	/**
	/*@brief 连接是否成功
	/*@author liyongchao
	/*@version V1.00
	/*@return true 连接成功 false 连接失败
	*/
	virtual bool IsConnected()=0;

	/**
	/*@brief 重新连接
	/*@author liyongchao
	/*@version V1.00
	/*@return true 连接成功 false 连接失败
	*/
	virtual bool ReConnected()=0;

	/**
	/*@brief 获取最近一次错误信息
	/*@author liyongchao
	/*@version V1.00
	/*@return 错误信息
	*/
	virtual string GetLastError()=0;

	/**
	/*@brief 判断存储键是否存在
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_key 存储键
	/*@param[in] type 存储键类型
	/*@return bool 若存在返回true，否则返回false
	*/
	virtual bool ExistKey(const char *s_category,const char* s_key)=0;

	/**
	/*@brief 获取键
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key_pattern 存储键模式
	/*@param[out] v_key_list 存储键列表
	/*@return true 获取成功 false 获取失败
	*/
	virtual bool GetKeys(const char *s_category,const char *s_key_pattern,vector<string>& v_key_list)=0;

	/**
	/*@brief 根据存储键删除值
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key 存储键
	/*@return true 删除成功 false 删除失败
	*/
	virtual bool DeleteKey(const char *s_category,const char *s_key)=0;

	/**
	/*@brief 根据存储键模式删除值
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key_pattern 存储键模式
	/*@return true 删除成功 false 删除失败
	*/
	virtual bool DeleteKeys(const char *s_category,const char *s_key_pattern)=0;

	/**
	/*@brief 设置或更新字符串
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key 存储键
	/*@param[in] s_value 待设置的字符串
	/*@return true 操作成功 false 操作失败
	*/	
	virtual bool SetString(const char *s_category,const char *s_key,const char* s_value)=0;

	/**
	/*@brief 获取字符串
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key 存储键
	/*@param[out] s_value 获取的字符串
	/*@return true 操作成功 false 操作失败
	*/	
	virtual bool GetString(const char *s_category,const char *s_key,std::string& s_value)=0;

	/**
	/*@brief 设置或更新对象
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key 存储键
	/*@param[in] p_message 待设置的对象
	/*@return true 操作成功 false 操作失败
    */	
	virtual bool SetMessage(const char *s_category,const char *s_key,::google::protobuf::Message* p_message)=0;

	/**
	/*@brief 根据数据类别和存储键获取对象
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_category 数据类别
	/*@param[in] s_key 存储键
	/*@param[out] p_message 返回的对象
	/*@return true 操作成功 false 操作失败
   */
	virtual bool GetMessage(const char *s_category,const char *s_key, ::google::protobuf::Message* p_message)=0;

	/**
	/*@brief 设置或更新二进制流
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_key 存储键
	/*@param[in] s_buffer 二进制流
	/*@param[in] i_size 字节数
	/*@return bool 若存储成功后返回true，否则返回false
	*/
	virtual bool SetBuffer(const char* s_category,const char* s_key,const char* s_buffer,unsigned int i_size)=0;

	/**
	/*@brief 获取二进制流
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_key 存储键
	/*@param[in] s_buffer 二进制流
    /*@param[in] i_size 字节数
	/*@return bool 若提取成功后返回true，否则返回false
    */
	virtual bool GetBuffer(const char* s_category,const char* s_key,char*& s_buffer,unsigned int& i_size)=0;

	/**
	/*@brief 注册订阅频道的回调函数
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_channel 订阅的频道
	/*@param[in] redisSubCalBk 回调函数
	/*@return true 注册成功 false 注册失败 
	*/
	virtual bool RegistCalBakFuc(const string& s_channel,redisSubscribeCallback *redisSubCalBk)=0;

	/**
	/*@brief 根据频道发布消息
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_channel 发布的频道
	/*@param[in] s_pubInfo 发布的消息
	/*@return int 订阅该频道的个数，-1表示发布失败
   */
	virtual int PublishMessage(const char * s_channel,const char* s_pubInfo)=0;

	/**
	/*@brief 订阅消息，一定要在注册完回调函数后再使用！
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] v_channel 订阅的频道名称
	/*@return string true 操作成功 false 操作失败
	*/
	virtual bool SubscribeMessage(const vector<char*>& v_channel)=0;

	/**
	/*@brief 依据特定范式订阅频道，一般订阅多个频道
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] s_psubPattern 订阅的范式
	/*@param[in] redisSubCalBk 对应的回调函数
	/*@return string true 操作成功 false 操作失败
   */
	virtual bool PsubscribeMessage(const char* s_psubPattern)=0;

	/**
	/*@brief 清空数据库
	/*@author liyongchao
	/*@version V1.00
	/*@return true 清空成功 false 清空失败
   */
	virtual bool FlushDB()=0;

	/**
	/*@brief 备份内存数据至磁盘
	/*@author liyongchao
	/*@version V1.00
	/*@return true 备份成功 false 备份失败
	*/
	virtual bool SaveDB()=0;

	/**
	/*@brief 订阅消息，一定要在注册完回调函数后再使用！
	/*@author liyongchao
	/*@version V1.00
	/*@param[in] v_channel 订阅的频道名称
	/*@return string true 操作成功 false 操作失败
	*/
	virtual bool SubscribeMessage(const vector<string>& v_channel)=0;

	//************************************
	// Method:    getRedisConnection 获取Redis连接
	// FullName:  acl::IDataService::getRedisConnection
	// Access:    virtual public 
	// Returns:   bool 若连接为空或有错误，返回false
	// Qualifier:
	// Parameter: redisContext * & conn 出参，若连接非空且无错误，则返回连接
	//************************************
	virtual bool getRedisConnection(redisContext*& conn) = 0;

	//订阅消息
	virtual void SubscribeMessageNew(const vector<string>& v_channel) = 0;
};
    
/************************************************************************/
/*@brief 创建数据服务接口指针
/*@author liyongchao
/*@version V1.00
/*@param[in] s_ip 数据库IP地址
/*@param[in] port 数据库端口号 
/*@return 数据服务接口指针
/************************************************************************/
__declspec(dllexport) IDataService* ICreateDataService(const char* s_ip,const int port);

/************************************************************************/
/*@brief 创建数据发布订阅接口指针
/*@author liyongchao
/*@version V1.00
/*@param[in] s_ip 数据库IP地址
/*@param[in] port 数据库端口号 
/*@return 数据服务接口指针
/************************************************************************/
__declspec(dllexport) IDataService* ICreatePubSubService(const char* s_ip,const int port);

}
#pragma pack()
