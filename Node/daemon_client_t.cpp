#include "daemon_client_t.h"
#include "aqueue_manager_t.h"
#include "client_repar_t.h"
#include "dahlia_utils.h"
#include <atlstr.h>

dahlia::daemon_client_t::daemon_client_t( void )
{
    _aqueue_mgr = new aqueue_manager_t(2, 0);
    _repar       = new client_repar_t("client_repar_t_obj_id", _aqueue_mgr);
    _aqueue_mgr->attach_obj(_repar);
}

dahlia::daemon_client_t::~daemon_client_t( void )
{

}

bool dahlia::daemon_client_t::create_monitor()
{
    //创建监视进程
    string s_path = get_app_path();
    string s_exe = s_path;
    s_exe += "\\Monitor.exe";

    STARTUPINFO startup_info_;
    PROCESS_INFORMATION process_info_;
    ZeroMemory(&startup_info_, sizeof(STARTUPINFOA ));
    //ZeroMemory(&process_info_, sizeof(LPPROCESS_INFORMATION ));


    //int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)_process_name.data(), -1, NULL,0);
    //WCHAR * wszGBK = new WCHAR[len+1];
    //memset(wszGBK, 0, len * 2 + 2);
    //MultiByteToWideChar(CP_ACP, 0, (LPCSTR)_process_name.data(), -1, (LPWSTR)wszGBK, len);

    //LPWSTR sCmd = wszGBK;
    CString strC(/*ConvertGBKToUtf8*/(s_exe).c_str());
    CString swork_path_(s_path.c_str());
    //创建进程
    if(CreateProcess(
        NULL,
        strC.GetBuffer(),
        NULL,
        NULL,
        false,
        0,
        NULL,
        swork_path_.GetBuffer(),
        &startup_info_,
        &process_info_
        ))
    {
        CloseHandle(process_info_.hProcess);
        CloseHandle(process_info_.hThread);
        return true;
    }

    ////将进程信息存储到数据库中
    //delete []wszGBK;
    return false;
}
