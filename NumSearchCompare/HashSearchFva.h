#ifndef _HASHSEARCHFNA_H
#define _HASHSEARCHFNA_H

#include "DataDefine.h"


typedef unsigned int Fnv32_t;
#define FNV0_32_INIT ((Fnv32_t)0)
#define FNV1_32_INIT ((Fnv32_t)0x811c9dc5)
#define FNV1_32A_INIT FNV1_32_INIT

#define FNV_32_PRIME ((Fnv32_t)0x01000193)

extern int CollCounter;

int AddDataItem_H(DataItem *pArr);

DataItem *GetDataItem_H(int id);

void ResetData_H();

#endif