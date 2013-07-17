#include "StockTree.h"
#include <cstring>

void GenerateCodeNums(int num, int *bit_1, int *bit_2,int *bit_3, int *bit_4, int *bit_5, int *bit_6){
    int tNum = num;
    *bit_1 = tNum / 100000;
    tNum = tNum % 100000;

    *bit_2 = tNum / 10000;
    tNum = tNum % 10000;

    *bit_3 = tNum / 1000;
    tNum = tNum % 1000;

    *bit_4 = tNum / 100;
    tNum = tNum % 100;

    *bit_5 = tNum / 10;
    tNum = tNum % 10;

    *bit_6 = tNum / 1;
}


Stock* StockTree::AddStock(Stock *pStk){
    int code = pStk->GetCodeI();

    Stock* pNewStk = AddTreeNum(code);
    memcpy(pNewStk, pStk, sizeof(Stock));

    this->stockCounter++;

    return pNewStk;
}

Stock* StockTree::GetStock(int code){
    int bit_1, bit_2, bit_3, bit_4, bit_5, bit_6;
    GenerateCodeNums(code, &bit_1, &bit_2, &bit_3, &bit_4, &bit_5, &bit_6);

    TNumTreeNote *pCur = root;
    pCur = pCur->list[bit_1];

    if(NULL == pCur->list[bit_2]){
        pCur->list[bit_2] = new TNumTreeNote();
    }
    pCur = pCur->list[bit_2];

    if(NULL == pCur->list[bit_3]){
        pCur->list[bit_3] = new TNumTreeNote();
    }
    pCur = pCur->list[bit_3];

    if(NULL == pCur->list[bit_4]){
        pCur->list[bit_4] = new TNumTreeNote();
    }
    pCur = pCur->list[bit_4];

    if(NULL == pCur->list[bit_5]){
        pCur->list[bit_5] = new TNumTreeNote();
    }
    pCur = pCur->list[bit_5];

    if(NULL == pCur->list[bit_6]){
        pCur->list[bit_6] = new TNumTreeNote();
    }
    pCur = pCur->list[bit_6];

    this->searchCounter++;

    return pCur->data;
}


Stock* StockTree::AddTreeNum(int num){
    int bit_1, bit_2, bit_3, bit_4, bit_5, bit_6;
    GenerateCodeNums(num, &bit_1, &bit_2, &bit_3, &bit_4, &bit_5, &bit_6);

    TNumTreeNote *pCur = root;
    if(NULL == pCur->list[bit_1]){
        pCur->list[bit_1] = new TNumTreeNote();
        pCur->list[bit_1]->lever = 1;
        pCur->list[bit_1]->num = bit_1;
        this->noteCounter++;
    }
    pCur = pCur->list[bit_1];

    if(NULL == pCur->list[bit_2]){
        pCur->list[bit_2] = new TNumTreeNote();
        pCur->list[bit_2]->lever = 2;
        pCur->list[bit_2]->num = bit_2;
        this->noteCounter++;
    }
    pCur = pCur->list[bit_2];

    if(NULL == pCur->list[bit_3]){
        pCur->list[bit_3] = new TNumTreeNote();
        pCur->list[bit_3]->lever = 3;
        pCur->list[bit_3]->num = bit_3;
        this->noteCounter++;
    }
    pCur = pCur->list[bit_3];

    if(NULL == pCur->list[bit_4]){
        pCur->list[bit_4] = new TNumTreeNote();
        pCur->list[bit_4]->lever = 4;
        pCur->list[bit_4]->num = bit_4;
        this->noteCounter++;
    }
    pCur = pCur->list[bit_4];

    if(NULL == pCur->list[bit_5]){
        pCur->list[bit_5] = new TNumTreeNote();
        pCur->list[bit_5]->lever = 5;
        pCur->list[bit_5]->num = bit_5;
        this->noteCounter++;
    }
    pCur = pCur->list[bit_5];

    if(NULL == pCur->list[bit_6]){
        pCur->list[bit_6] = new TNumTreeNote();
        pCur->list[bit_6]->lever = 6;
        pCur->list[bit_6]->num = bit_6;
        this->noteCounter++;
    }
    pCur = pCur->list[bit_6];

    pCur->data = new Stock();

    return pCur->data;
}