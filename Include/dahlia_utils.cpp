#include "dahlia_utils.h"
#include "stringutil.h"
#include <TlHelp32.h>
#include <algorithm>
#include <string.h>
#include "tchar.h"
#include "psapi.h"
#include "wnd_screen_t.h"

#pragma comment(lib, "Psapi.lib")

HANDLE get_process_handle( unsigned int pid_ )
{
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
}

bool get_processes_by_pname( const string& pname_, set<int>& pids)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (INVALID_HANDLE_VALUE == snapshot)
    {
        return false;
    }

    PROCESSENTRY32 pe = {sizeof(pe)};
    BOOL fok = true;
    for (fok = Process32First(snapshot, &pe); fok; fok = Process32Next(snapshot, &pe))
    {
        std::wstring wName = string2wstring(pname_);
        if (!_tcscmp(pe.szExeFile, wName.c_str()))
        {
            pids.insert(pe.th32ProcessID);
        }
    }
    CloseHandle(snapshot);
    return true;
}
std::string get_app_path()
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

//获取进程的完整路径和exe名称
std::string get_app_name()
{
    char szBuf[1024] = {0};
    std::string strpath;
#ifdef WIN32
    // 在Windows平台采用的获取函数
    GetModuleFileNameA(NULL,szBuf,sizeof(szBuf));
    strpath = szBuf;
#endif
    return strpath;
}

unsigned int get_current_pid()
{
    return GetCurrentProcessId();
}

bool is_signal_instence()
{
    HANDLE mutex_ = CreateMutex(NULL, FALSE, L"Sample009ProcessMonitor");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle(mutex_);
        mutex_ = NULL;
        return FALSE;
    }
    return TRUE;
}

//获取对应进程的id的内存情况
unsigned int get_process_memroy( unsigned int pid_ )
{
   HANDLE handle = get_process_handle(pid_);
   if (INVALID_HANDLE_VALUE == handle)
   {
       return -1;
   }

  int nTick = get_process_memroy_handle(handle);
  CloseHandle(handle);
  return nTick;
}

unsigned int get_process_memroy_handle(HANDLE handle)
{
    if (INVALID_HANDLE_VALUE == handle)
    {
        return -1;
    }

    PROCESS_MEMORY_COUNTERS pcounter;
    pcounter.cb = sizeof(PROCESS_MEMORY_COUNTERS);
    unsigned int nCount = -1;
    if (GetProcessMemoryInfo(handle, &pcounter, sizeof(PROCESS_MEMORY_COUNTERS)))
    {
        nCount = pcounter.WorkingSetSize / 1024.0;
    }
   
    return nCount;
}

bool kill_process( const string& pname_, unsigned int npid )
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (INVALID_HANDLE_VALUE == snapshot)
    {
        return false;
    }

    PROCESSENTRY32 pe = {sizeof(pe)};
    BOOL fok = true;
    for (fok = Process32First(snapshot, &pe); fok; fok = Process32Next(snapshot, &pe))
    {
        std::wstring wName = string2wstring(pname_);
        if (!_tcscmp(pe.szExeFile, wName.c_str()) &&
            npid == pe.th32ProcessID)
        {
            HANDLE pHandle = get_process_handle(npid);
           BOOL ret =  ::TerminateProcess(pHandle, 0);
            CloseHandle(pHandle);
            return ret;
        }
    }
    CloseHandle(snapshot);
    return true;
}

std::string get_local_ip_s()
{
    vector<string> v_ip;
    get_host_ip_list(v_ip);
    if (!v_ip.empty())
    {
        return v_ip[0];
    }

    return "127.0.0.1";
}

void get_host_ip_list(vector<string>& v_host_ip)
{
    char szHostName[125];
    char strTmp[100];
    if (gethostname(szHostName, sizeof(szHostName)) == 0)
    {
        struct hostent *pHost = NULL;
        //const char* strHostName = "localhost";

        pHost = gethostbyname(szHostName);

        for (int i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
        {
            sprintf_s(strTmp,sizeof(strTmp),"%u.%u.%u.%u",
                (unsigned int)((unsigned char*)pHost->h_addr_list[i])[0],(unsigned int)((unsigned char*)pHost->h_addr_list[i])[1],\
                (unsigned int)((unsigned char*)pHost->h_addr_list[i])[2], (unsigned int)((unsigned char*)pHost->h_addr_list[i])[3]);

            v_host_ip.push_back(string(strTmp));
        }
    }
}

bool get_exe_path_by_pid( int npid, string& sPath )
{
    char szBuf[1024] = {0};
    std::string strpath;

   HANDLE handle = get_process_handle(npid);
   if (INVALID_HANDLE_VALUE == handle)
   {
       return false;
   }
   DWORD dLen = sizeof(szBuf);
   bool flag = QueryFullProcessImageNameA(handle, 0 ,szBuf, &dLen);
   sPath = szBuf;

   CloseHandle(handle);
   return flag;
}

typedef struct enum_hand_arg 
{
    std::vector<HWND> *vec_hands;
    int process_id;
}enum_hand_arg, *l_enum_hand_arg;

BOOL CALLBACK lp_enum_func(HWND hwnd, LPARAM lparam)
{
    enum_hand_arg* p_args = (l_enum_hand_arg)lparam;
    DWORD process_id;
    GetWindowThreadProcessId(hwnd, &process_id);

    if (process_id == p_args->process_id)
    {
        p_args->vec_hands->push_back(hwnd);
    }
    return TRUE;
}

//通过Pid获取窗口
static void get_wnds_process_by_pid(int pid_, std::vector<HWND>& vec_hands)
{
    enum_hand_arg wi;
    wi.process_id = pid_;
    wi.vec_hands = &vec_hands;
    EnumWindows(lp_enum_func, (LPARAM)&wi);
}

bool is_assert(const string& s_wind)
{
    if (s_wind == "Microsoft Visual C++ Debug Library")
    {
        return true;
    }
    else if (s_wind == "Libary")
    {
        return false;
    }
    return false;
}

//保存位图信息
//bool save_bit_map(const CBitmap& bitmap)
//{
//    HDC hDc;//设备描述列表
//    int nBitsl;//当前分辨率下每分辨率的所占字节
//    WORD wBitCount;//位图中图像像素所占字节
//    //定义调色板大小，位图中像素字节，位图文件
//}

//static  bool create_assert_bitmap(HWND hwnd)
//{
//    RECT rect;
//    //获取窗口的矩形区域
//    if(GetWindowRect(hwnd, &rect))
//    {
//      /*  CBitmap bmp;
//        CDC* pDeskDc = GetDesktopWindow()->GetDC();
//        CDC memDc;
//        memDc.CreateCompatibleDC(pDeskDc);
//        CRect rectDesk;
//        GetDesktopWindow()->GetClientRect(pDeskDc);
//
//        bmp.CreateCompatibleBitmap(pDeskDc, rectDesk);
//
//        save_bit_map(bmp);*/
//
//        CRect replot;
//        ScreenToClient(hwnd, &rect)；
//
//
//        return true;
//    }
//
//    return false;
//}



//判断窗口是否有断言窗口
bool  contions_assert_wnds(int pid_, bool bSave, const string& path)
{
    std::vector<HWND> vec_hands;
    get_wnds_process_by_pid(pid_ , vec_hands);

    std::vector<HWND>::iterator it = vec_hands.begin();
    for(; it != vec_hands.end(); ++it)
    {
        if (*it != NULL)
        {
            char text[1024] = {0};
            ::GetWindowTextA(*it, text, sizeof(text));
            RECT rect_;
            ::GetWindowRect(*it, &rect_);
              if (is_assert(text))
            {
                if (bSave)//标识截图
                {
                    wnd_screen_t screen;
                    screen.init(*it, rect_.right - rect_.left, rect_.bottom - rect_.top);
                    screen.set_screen(rect_.left,
                        rect_.top,
                        rect_.right - rect_.left,
                        rect_.bottom - rect_.top
                        );
                    screen.save(path);
                }
                return true;
            }
        }
    }

    return false;
}

