#include <tchar.h> 
#include <windows.h>

#include <TlHelp32.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <Psapi.h>
#include <ctime>
using namespace std;

#define UNICODE
#define _UNICODE

int main(int argv, char** argc)
{
    char pProcName[100] = {0};
    int sleepTime = 1000 * 1;
    if(argv >= 2){
        _snprintf(pProcName, sizeof(pProcName), argc[1]);

        if(argv == 3){
            sleepTime = stoi(argc[2]);
        }
    }else{
        _snprintf(pProcName, sizeof(pProcName), "runapp_sbhb.exe");
    }

    int nLen = strlen(pProcName) + 1;
    int nwLen = MultiByteToWideChar(CP_ACP, 0, pProcName, nLen, NULL, 0);
    TCHAR lpszFile[256];
    MultiByteToWideChar(CP_ACP, 0, pProcName, nLen, lpszFile, nwLen);
    _tprintf(_T("Process Name: %s\n"), lpszFile);

    // 给系统所有进程拍一个快照
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE){
        cout<<"获取系统进程快照失败！"<<endl;
        return -1;
    }
    PROCESSENTRY32 pe32 = {sizeof(PROCESSENTRY32)};

    HANDLE hHandleTar = 0;
    BOOL bMore = Process32First(hProcessSnap, &pe32);
    while(bMore){
        //_tprintf(_T("%s\n"), pe32.szExeFile);
        //cout<<"进程ID："<< pe32.th32ProcessID << endl;
        if (_tcscmp(pe32.szExeFile, lpszFile) == 0){
            hHandleTar = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); // 通过进程id获取句柄
            break;
        }
        bMore = Process32Next(hProcessSnap, &pe32);
    }
    CloseHandle(hProcessSnap);

    if(hHandleTar){
        cout << "找到了指定的进程,现在开始监控:" << endl;

        static ofstream outFile;
        char outFileName[_MAX_PATH] = {0};
        _snprintf(outFileName, sizeof(outFileName), "%s.txt", pProcName);
        outFile.open(outFileName, std::ofstream::out | std::ofstream::app);

        PROCESS_MEMORY_COUNTERS pmc;
        pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);

        int idx = 0;
        while(true){
            static struct tm *local;
            static time_t GLogTimer;
            static clock_t GLogClock;
            GLogTimer = time(NULL);
            clock_t curClock = clock();
            local = localtime(&GLogTimer);

            TCHAR path[_MAX_PATH + 1]= {0};
            TCHAR fname[_MAX_FNAME];  
            TCHAR    drive[_MAX_DRIVE];  
            TCHAR    dir[_MAX_DIR];  
            TCHAR    ext[_MAX_EXT];  
            GetModuleFileNameEx(hHandleTar, NULL, path, MAX_PATH+1);

            _wsplitpath(path, drive, dir, fname, ext );
            TCHAR curProcName[_MAX_PATH] = {0};
            _snwprintf(curProcName, sizeof(curProcName), _T("%s%s"), fname, ext);
           
            if(_tcscmp(lpszFile, curProcName) == 0){
                GetProcessMemoryInfo(hHandleTar, &pmc, sizeof(pmc));

                cout << "idx=" << idx << ", size=" << pmc.WorkingSetSize / 1024 << ", peak:" << pmc.PeakWorkingSetSize
                    << ",PagefileUsage=" << (pmc.PagefileUsage / 1024) 
                    << ",QuotaPagedPoolUsage=" << (pmc.QuotaPagedPoolUsage / 1024) <<endl;
                outFile <<  "[" << local->tm_year + 1900 << "-" << local->tm_mon + 1 << "-" << local->tm_mday << " " 
                    << local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << "]]idx=" 
                    << idx << ", size=" << pmc.WorkingSetSize / 1024 << ", peak:" << pmc.PeakWorkingSetSize
                    << ",PagefileUsage=" << (pmc.PagefileUsage / 1024) 
                    << ",QuotaPagedPoolUsage=" << (pmc.QuotaPagedPoolUsage / 1024)<<endl;
            }else{
                break;
            }

            Sleep(sleepTime);
        }

        outFile.close();
        CloseHandle(hHandleTar);
    }else{
        cout << "没有找到指定的进程." << endl;
    }

    cout << "end." << endl;
    int i;
    cin >> i;

    return 0;
}