// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include <cstdio>


#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN32)

#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    printf("cache library call into\n");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif