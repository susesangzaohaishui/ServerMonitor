#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <set>

using namespace std;

/*  Define integer types needed for event interface                          */
#if defined NET_HAVE_SOLARIS || defined NET_HAVE_OPENVMS
#   include <inttypes.h>
#elif defined _MSC_VER && _MSC_VER < 1600
#   ifndef int32_t
typedef __int32 int32_t;
#   endif
#   ifndef uint16_t
typedef unsigned __int16 uint16_t;
#   endif
#else
#   include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
    //判断是否启动了多实例
    bool is_signal_instence();

    //通过pid获取进程句柄
    HANDLE get_process_handle(unsigned int pid_);

    //通过进程名称获取进程pid
    bool   get_processes_by_pname(const string& pname_, set<int>& );

    //获取本进程的路径
    std::string get_app_path();

    //获取本进程名称
    std::string get_app_name();

    //获取当前进程的pid
    unsigned int get_current_pid();

    //获取当前进程内存
    unsigned int get_process_memroy(unsigned int pid_);
    unsigned int get_process_memroy_handle(HANDLE handle);

    //通过进程名称和进程ID杀死进程
    bool kill_process(const string& pname_, unsigned int npid);

    //获取本机的一个ip地址
    string get_local_ip_s();

    //获取本地的所有ip地址列表
    void get_host_ip_list(vector<string>& v_host_ip);

    //通过pid获取文件路径及名称
    bool get_exe_path_by_pid(int npid, string& sPath);

    /*判断窗口是否有断言窗口,第二个参数代表是否截图*/
    bool  contions_assert_wnds(int pid_, bool bSave, const string& path);
#ifdef __cplusplus
}
#endif

