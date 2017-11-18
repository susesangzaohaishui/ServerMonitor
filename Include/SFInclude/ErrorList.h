/********************************************************************
	创建日期:	2016/06/25
	文 件 名:	ErrorList
	扩 展 名:	h
	作    者:	zz
	
	说    明:	本文件定义了服务框架所有的错误类型
*********************************************************************/

#ifndef __ERRORLIST_H__
#define __ERRORLIST_H__

const int ERRORINFO_SUCCESS = 0;
const int ERRORINFO_INVALID_CONFIG = 1;
const int ERRORINFO_INVALID_LICENSE = 2;
const int ERRORINFO_INVALID_PARAMETER = 3;
const int ERRORINFO_LOAD_INITCOM_FAILED = 4;
const int ERRORINFO_LOAD_COM_FAILED = 5;
const int ERRORINFO_POST_THREAD_FAILED = 6;
const int ERRORINFO_POST_MSG_FAILED = 7;
const int ERRORINFO_LOAD_LIBRARY_FAILED = 8;
const int ERRORINFO_INIT_LOG_FAILED = 9;

#endif