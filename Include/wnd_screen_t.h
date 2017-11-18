#pragma once

#include <Windows.h>
#include <string>

using namespace std;

//通过窗口句柄获取界面
class wnd_screen_t
{
public:
    wnd_screen_t(void);
    ~wnd_screen_t(void);
    void init(HWND h_wnd_, int w = 0, int h = 0, int color_deep_ = 16);
    void set_screen(int x, int y, int w, int h );
    void save(const string& spath);
public:
    char*   _buff;//便于网络传输的数据
    int     _buf_len;//数据长度
private:
    int     _scr_width;
    int     _src_height;
    int     _dw_len_1;
    int     _dw_len_2;
    char*   _h_dib;
    HDC     _hmdc;
    HDC     _hdc;
    HDC     _hhh;
    HBITMAP _h_bmp_screen;
    HBITMAP _hold_bmp;
    HWND    _m_h_wnd;
};

