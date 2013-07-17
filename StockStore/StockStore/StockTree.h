#include <sstream>
#include "Stock.h"
#include "NumberTree.h"

#pragma once

using namespace std;

class StockTree{
public:
    StockTree():stockCounter(0), noteCounter(0), searchCounter(0){root = GetNewNumTreeNote(0);};

    Stock *AddStock(Stock *pStk);
    Stock *GetStock(int code);
    Stock *GetStock(string code);
    int GetNoteCounter(){return noteCounter;};
    int GetStockCounter(){return stockCounter;};
    int GetSearchCounter(){return searchCounter;};
private:
    Stock* AddTreeNum(int num);

private:
    NumTreeNote *root;
    
    int stockCounter;
    int noteCounter;
    int searchCounter;
};