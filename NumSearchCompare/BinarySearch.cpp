#include "BinarySearch.h"
#include <cstring>
#include <cstdlib>

DataItem **GDataItemList_B = NULL;
int GDataItemCapacity_B = 0;
int GDataItemCounter_B = 0;
const int ITEMCOUNTBUFF_B = 1000;


//在DataItem数组中查找id为target的元素，若没有找到此元素，*pos返回target应该插入的位置
//@param pArr 指向DataItem数组的指针
//@param low 查找的起始位置
//@param high 查找的终止位置
//@param target 等查找的值
//@param pos 若没有找到，返回target应该插入的位置
//@return 找到数据: >=0    没有找到数据:-1
int BinarySearch(DataItem **pArr, int low, int high, int target, int *pos)
{
    int mid = 0;
    int curVal = 0;
    int posTmp = low;
    while(low <= high)
    {
        mid = (low + high) / 2;
        curVal = (*(pArr + mid))->id;

        if (target < curVal){
            high = mid - 1;
            posTmp = mid; 
        }else if(curVal < target){
            low = mid + 1;
            posTmp = mid + 1;
        }else{
            return mid;
        }   
    }

    *pos = posTmp;

    return -1;
}

int AddDataItem_B(DataItem *pItem)
{
    if(0 == GDataItemList_B){
        GDataItemList_B = (DataItem**)malloc(sizeof(DataItem*) * ITEMCOUNTBUFF_B);  
        memset(GDataItemList_B, 0, sizeof(DataItem*) * ITEMCOUNTBUFF_B);
        GDataItemCapacity_B = ITEMCOUNTBUFF_B;
    }

    if(GDataItemCounter_B + 1 == GDataItemCapacity_B){
        int iNewCap = GDataItemCapacity_B * 2; 
        DataItem **pNewList = (DataItem**)malloc(sizeof(DataItem*) * iNewCap);    
        memset(pNewList, 0, sizeof(DataItem*) * iNewCap);
        memcpy(pNewList, GDataItemList_B, sizeof(DataItem*) * GDataItemCounter_B);

        free(GDataItemList_B);
        GDataItemList_B = pNewList;
        GDataItemCapacity_B = iNewCap;
    }

    int pos = 0;
    int idx = BinarySearch(GDataItemList_B, 0, GDataItemCounter_B - 1, pItem->id, &pos);

    if(idx < 0){
        if(idx < GDataItemCounter_B){
            for(int pIdx = GDataItemCounter_B - 1; pIdx >= pos; --pIdx){
                *(GDataItemList_B + pIdx + 1) = *(GDataItemList_B + pIdx);
            }
        }

        *(GDataItemList_B + pos) = pItem;
        ++GDataItemCounter_B;

        return pos;
    }else{
        return -1;
    }
}


DataItem *GetDataItem_B(int id)
{
    int pos = 0;
    int idx = BinarySearch(GDataItemList_B, 0, GDataItemCounter_B - 1, id, &pos);

    if(idx >= 0){
        return GDataItemList_B[idx];
    }else{
        return NULL;
    }   
}

void ResetData_B()
{
    if(GDataItemList_B)free(GDataItemList_B);
    GDataItemList_B = NULL;
    GDataItemCapacity_B = 0;
    GDataItemCounter_B = 0;
}