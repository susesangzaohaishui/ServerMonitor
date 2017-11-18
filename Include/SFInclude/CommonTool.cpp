/********************************************************************
	创建日期:	2016/06/25
	文 件 名:	CommonTool
	扩 展 名:	cpp
	作    者:	zz
	
	说    明:	公共函数实现文件,这里需要按照不同的平台调用不同的API
*********************************************************************/

#include "CommonTool.h"

#ifdef WIN32
#include <Windows.h>
#endif

namespace CommonTool
{
	std::string GetAppPath()
	{
		char szBuf[1024] = {0};
		std::string strpath;
#ifdef WIN32
		// 在Windows平台采用的获取函数
		GetModuleFileNameA(NULL,szBuf,sizeof(szBuf));
		strpath = szBuf;
		strpath = strpath.substr(0, strpath.rfind('\\'));
#endif
		return strpath;
	}

	std::string GetAppName()
	{
		char szBuf[1024] = {0};
		std::string strpath;
#ifdef WIN32
		// 在Windows平台采用的获取函数
		GetModuleFileNameA(NULL,szBuf,sizeof(szBuf));
		strpath = szBuf;
		strpath = strpath.substr(strpath.rfind('\\') + 1);
		strpath = strpath.substr(0,strpath.length() - 4);
#endif
		
		return strpath;
	}
}