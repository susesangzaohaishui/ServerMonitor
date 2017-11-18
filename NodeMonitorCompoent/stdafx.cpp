// stdafx.cpp : 只包括标准包含文件的源文件
// ActionMagServerComponent.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用


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
