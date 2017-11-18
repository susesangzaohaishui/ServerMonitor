#ifndef HEADER_STRING_UTIL_H
#define HEADER_STRING_UTIL_H

#include <string>
#include <xstring>
#include <windows.h>
using namespace std;

string ConvertUtf8ToGBK(const std::string& strUtf8);

string ConvertGBKToUtf8(const std::string& strGBK);

void formatUrl(std::string& url, std::string& key, std::string& value);

string num2str(double l);

double str2num(string s);

string wchar2string(const std::wstring&);

std::wstring string2wstring(const string& );

long toSeconds(const SYSTEMTIME& tm_);

SYSTEMTIME toSystemTimes( long seconds );
std::string CovertSysTime( SYSTEMTIME _TIME );
#endif