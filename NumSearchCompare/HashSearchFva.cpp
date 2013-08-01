#include "HashSearchFva.h"
#include <cstring>
#include <cstdlib>
#include "Base.h"

DataItem **GDataItemList_H = 0;
int GDataItemCapacity_H = 0;
int GDataItemCounter_H = 0;
const int ITEMCOUNTBUFF_H = 1000;
int CollCounter = 0;


/*
 * fnv_32_buf - perform a 32 bit Fowler/Noll/Vo hash on a buffer
 *
 * input:
 *	buf	- start of buffer to hash
 *	len	- length of buffer in octets
 *	hval	- previous hash value or 0 if first call
 *
 * returns:
 *	32 bit hash as a static hash type
 *
 * NOTE: To use the 32 bit FNV-0 historic hash, use FNV0_32_INIT as the hval
 *	 argument on the first call to either fnv_32_buf() or fnv_32_str().
 *
 * NOTE: To use the recommended 32 bit FNV-1 hash, use FNV1_32_INIT as the hval
 *	 argument on the first call to either fnv_32_buf() or fnv_32_str().
 */
//Fnv32_t fnv_32_buf(void *buf, size_t len, Fnv32_t hval)
//{
//    unsigned char *bp = (unsigned char *)buf;	/* start of buffer */
//    unsigned char *be = bp + len;		/* beyond end of buffer */
//
//    /*
//     * FNV-1 hash each octet in the buffer
//     */
//    while (bp < be) {
//
//	/* multiply by the 32 bit FNV magic prime mod 2^32 */
//#if defined(NO_FNV_GCC_OPTIMIZATION)
//	hval *= FNV_32_PRIME;
//#else
//	hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
//#endif
//
//	/* xor the bottom with the current octet */
//	hval ^= (Fnv32_t)*bp++;
//    }
//
//    /* return our new hash value */
//    return hval;
//}

Fnv32_t fnv_32_buf(const void *buf, size_t len, Fnv32_t hval)
{
    const unsigned char *bp = (const unsigned char *)buf;	/* start of buffer */
    const unsigned char *be = bp + len;		/* beyond end of buffer */

    /*
    * FNV-1 hash each octet in the buffer
    */
    while (bp < be) {

        hval *= FNV_32_PRIME;

        /* xor the bottom with the current octet */
        hval ^= (Fnv32_t)*bp++;
    }

    /* return our new hash value */
    return hval;
}


int GetHashPos(DataItem **pArr, int target, int nTableSize)
{
    int id = target; 
    Fnv32_t hash = fnv_32_buf((void *)(&id), sizeof(id), 0);
    int nHashStart = hash % nTableSize;
    int nHashPos = nHashStart;

    while( (pArr[nHashPos]) && (0 != (pArr[nHashPos])->id) ){
        if((pArr[nHashPos])->id == target){
            return -1;
        }

        nHashPos = (nHashPos + 1) % nTableSize;

        if(nHashPos == nHashStart) return -1;
    }

    return nHashPos;
}

int HashSearch(DataItem **pArr, int target, int nTableSize)
{
    int id = target; 
    Fnv32_t hash = fnv_32_buf((void *)(&id), sizeof(id), 0);  

    int nHashStart = hash % nTableSize;
    int nHashPos = nHashStart;

    while( (pArr[nHashPos]) && (0 != (pArr[nHashPos])->id) ){
        if((pArr[nHashPos])->id == target){
            return nHashPos; 
        }else{
            nHashPos = (nHashPos + 1) % nTableSize;
            CollCounter++;
        }

        if(nHashPos == nHashStart) break;
    }
    
    return -1;
}

int AddDataItem_H(DataItem *pArr)
{
    if(0 == GDataItemList_H){
        GDataItemList_H = (DataItem**)malloc(sizeof(DataItem*) * ITEMCOUNTBUFF_H);  
        memset(GDataItemList_H, 0, sizeof(DataItem*) * ITEMCOUNTBUFF_H);
        GDataItemCapacity_H = ITEMCOUNTBUFF_H;
    }

    if(GDataItemCounter_H << 1 >= GDataItemCapacity_H){
        int iNewCap = GDataItemCapacity_H << 1; 
        DataItem **pNewList = (DataItem**)malloc(sizeof(DataItem*) * iNewCap); 
        memset(pNewList, 0, sizeof(DataItem*) * iNewCap);

        for(int i = 0; i < GDataItemCapacity_H; ++i){
            if(GDataItemList_H[i]){
                int idx = GetHashPos(pNewList, GDataItemList_H[i]->id, iNewCap);

                ASSERT(idx >= 0);
                pNewList[idx] = GDataItemList_H[i];
            }
        }

        free(GDataItemList_H);
        GDataItemList_H = pNewList;
        GDataItemCapacity_H = iNewCap;
    }

    int idx = GetHashPos(GDataItemList_H, pArr->id, GDataItemCapacity_H);
    if(idx >= 0){
        GDataItemList_H[idx] = pArr;
        ++GDataItemCounter_H;
        return 0;
    }else{
        return  -1;
    }
}


DataItem *GetDataItem_H(int id)
{
    int idx = HashSearch(GDataItemList_H, id, GDataItemCapacity_H);
    if(idx >= 0){
        return GDataItemList_H[idx];
    }else{
        return  NULL;
    }
}

void ResetData_H()
{
    if(GDataItemList_H)free(GDataItemList_H);
    GDataItemList_H = NULL;
    GDataItemCapacity_H = 0;
    GDataItemCounter_H = 0;
    CollCounter = 0;
}