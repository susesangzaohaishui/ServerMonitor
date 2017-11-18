#include "dahlia_utils.h"
#include <Windows.h>
#include <assert.h>
#include "daemon_client_t.h"
#include <iostream>
using namespace std;

//ºÏ≤‚≥Ã–Ú±¿¿£
long __stdcall callback(EXCEPTION_POINTERS*excp)
{

    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char* argv[])
{
   // SetUnhandledExceptionFilter(callback);

    //≈–∂œ «∑Ò «µ•¿˝
    dahlia::daemon_client_t* client = new dahlia::daemon_client_t;
    int iCount = 0;
    vector<string> tt;
    char* p = NULL;
    while (1)
    {
        if (iCount > 10)
        {
            //assert(false);
            *(tt.begin()) = "24";
            //cout<<p;
        }
        ++iCount;
        Sleep(1000);
    }
    return 0;
}

