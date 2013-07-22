#include <iostream>
#include <sstream>
#include "Stock.h"
#include "StockTree.h"
#include "NumberTree.h"

#include <windows.h> 
#include <stdio.h> 

using namespace std;

void addStock(StockTree *pStkTree, int code){
    Stock *pStk = new Stock();
    pStk->SetCode(code);
    pStkTree->AddStock(pStk); 

    delete pStk;
}

void testAdd(StockTree *pStkTree){
    int num;

    for(num = 300000; num < 301000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 310000; num < 311000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 320000; num < 321000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 600000; num < 601000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 610000; num < 611000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 620000; num < 621000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 630000; num < 631000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 640000; num < 641000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 650000; num < 651000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 660000; num < 666000; ++num){
        addStock(pStkTree, num);
    }

    for(num = 800000; num < 850000; ++num){
        addStock(pStkTree, num);
    }
}

void testSearch(StockTree *pStkTree){
    int num;
    for(num = 300000; num < 301000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 310000; num < 311000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 320000; num < 321000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 600000; num < 601000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 610000; num < 611000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 620000; num < 621000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 630000; num < 631000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 640000; num < 641000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 650000; num < 651000; ++num){
        pStkTree->GetStock(num);
    }

    for(num = 660000; num < 666000; ++num){
        pStkTree->GetStock(num);
    }
}

int main()
{
    WORD laster;

    SYSTEMTIME sys; 
    GetLocalTime( &sys ); 
    
    printf( "%02d.%03d \n", sys.wSecond, sys.wMilliseconds); 

    StockTree *pStkTree = new StockTree();
    testAdd(pStkTree);

    GetLocalTime( &sys ); 
    printf( "%02d.%03d\n", sys.wSecond, sys.wMilliseconds); 

    testSearch(pStkTree);
    testSearch(pStkTree);
    testSearch(pStkTree);

    GetLocalTime( &sys ); 
    printf( "%02d.%03d\n", sys.wSecond, sys.wMilliseconds); 

    cout << "stock:" << pStkTree->GetStockCounter() << " , note: " << pStkTree->GetNoteCounter() 
        << ", search: " << pStkTree->GetSearchCounter() << endl;

    int i;
    cin >> i;

    return 0;
}