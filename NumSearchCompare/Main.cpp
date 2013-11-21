#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "BinarySearch.h"
#include "HashSearchFva.h"
#include "Base.h"

using namespace std;


LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;
double time;

void test(int count)
{
    DataItem *p = NULL;
    DataItem *pRes = NULL;

    p = (DataItem *)malloc(sizeof(DataItem) * count);

    memset(p, 0, sizeof(DataItem) * count);

    for(int i = 0; i < count; ++i){
        (p + i)->id = i + 1;
    }

    cout << endl << "==== " << count << " ====" << endl;

    QueryPerformanceCounter(&nBeginTime);
    for(int i = 1; i <= count; ++i){
        AddDataItem_B(p + i);
    }
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart - nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    printf("BinarySearch:Add:%d:[%.7f]  [pre=%.7f]\n", count, time * 1000000, time * 1000000/count);


    QueryPerformanceCounter(&nBeginTime);
    for(int i = 1; i <= count; ++i){
        AddDataItem_H(p + i);
    }
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart - nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    printf("HashSearch:Add:%d:[%.7f]  [pre=%.7f] coll=%d\n", count, time * 1000000, time * 1000000/count, CollCounter);


    QueryPerformanceCounter(&nBeginTime);
    for(int i = 1; i <= count; ++i){
        pRes = GetDataItem_B((p + i)->id);
        ASSERT(pRes->id == (p + i)->id);
    }
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart - nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    printf("BinarySearch:Get:%d:[%.7f]  [pre=%.7f]\n", count, time * 1000000, time * 1000000/count);

    QueryPerformanceCounter(&nBeginTime);
    for(int i = 1; i <= count; ++i){
        pRes = GetDataItem_H((p + i)->id);
        ASSERT(pRes->id == (p + i)->id);
    }
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart - nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    printf("HashSearch:Get:%d:[%.7f]  [pre=%.7f] coll=%d, raio=%.4f\n", count, time * 1000000, time * 1000000/count, 
        CollCounter, CollCounter * 100.0/count);


    free(p);
    ResetData_B();
    ResetData_H();
}


int main()
{
    
    QueryPerformanceFrequency(&nFreq);

    test(100);
    test(1000);
    test(10000);
    test(100000);
    test(1000000);

    int i;
    cin >> i;
    return 0;
}