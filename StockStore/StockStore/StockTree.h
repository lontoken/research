#include <sstream>
#include "Stock.h"
#include "NumberTree.h"

#pragma once

using namespace std;

class StockTree{
public:
    StockTree():stockCounter(0){root = GetNewNumTreeNote(0);};

    NumTreeNote *AddStock(Stock *pStk);
    NumTreeNote *GetStock(int code);
    NumTreeNote *GetStock(string code);
    int GetNoteCounter(){return noteCounter;};
    int GetStockCounter(){return stockCounter;};
private:
    NumTreeNote *root;
    int stockCounter;
    int noteCounter;
};