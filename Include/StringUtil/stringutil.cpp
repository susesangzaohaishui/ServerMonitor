//#include "stdafx.h"
#include <string>
#include <windows.h>
#include "stringutil.h"
#include  <time.h>
#include <sstream>
#include <ATLComTime.h>

std::string ConvertUtf8ToGBK(const std::string& strUtf8) 
{
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8.data(), -1, NULL,0);
	unsigned short * wszGBK = new unsigned short[len+1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8.data(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK=new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte (CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL,NULL);

	string sresult  = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
	return sresult;
}


std::string ConvertGBKToUtf8(const std::string& strGBK)
{
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK.data(), -1, NULL,0);
	unsigned short * wszUtf8 = new unsigned short[len+1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK.data(), -1, (LPWSTR)wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8=new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);

	string sresult = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
	return sresult;
}

void formatUrl(std::string& url, std::string& key, std::string& value)
{
	// 检查url是不是以"/"结尾，如果是则删除最后一个"/"
	if('/' == url[url.size()-1])
	{
		std::string newUrl = url.substr(0,url.size()-1);
		url = newUrl;
	}

	// url中已经有"?"了，直接加参数
	if(-1!=url.find('?'))
	{
		url.append("&");
	}
	else
	{
		url.append("?");
	}
	url.append(key);
	url.append("=");
	url.append(value);
}

std::string num2str(double l)
{
	stringstream ss;
	ss<<l;
	return ss.str();
}

double str2num(std::string s)
{
	double num;
	stringstream ss(s);
	ss>>num;
	return num;
}

std::string wchar2string( const std::wstring& )
{
    return "";
}

std::wstring string2wstring( const string& str)
{
    string sTmp = str;
    int nLen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)sTmp.c_str(), -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[nLen +1];
    memset(wszUtf8, 0, nLen * 2+ 2);
    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)sTmp.c_str(), -1, (LPWSTR)wszUtf8, nLen);
    std::wstring res = wszUtf8;
    delete[] wszUtf8;
    return res;
}

long toSeconds( const SYSTEMTIME& tm_ )
{
    tm Ltm  ={ tm_.wSecond, 
        tm_.wMinute, 
        tm_.wHour, 
        tm_.wDay, 
        tm_.wMonth - 1,
        tm_.wYear - 1900,
        tm_.wDayOfWeek ,
        0,
        0
    };
    time_t tmL = mktime(&Ltm);
    return tmL;
}
SYSTEMTIME toSystemTimes( long seconds )
{
    SYSTEMTIME sysTime;
    COleDateTime datatime(seconds);
    sysTime.wYear = datatime.GetYear();
    sysTime.wMonth = datatime.GetMonth();
    sysTime.wDay = datatime.GetDay();
    sysTime.wHour = datatime.GetHour();
    sysTime.wSecond= datatime.GetSecond();
    sysTime.wMinute = datatime.GetMinute();

    return sysTime;
}

std::string CovertSysTime( SYSTEMTIME _TIME )
{
    char szTime[128];
    sprintf(szTime,"%04d-%02d-%02d %02d:%02d:%02d",_TIME.wYear,_TIME.wMonth,_TIME.wDay,_TIME.wHour,_TIME.wMinute,_TIME.wSecond);

    return string(szTime);
}