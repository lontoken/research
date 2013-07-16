#include <iostream>
#include <sstream>
#include "Stock.h"
#include "StockTree.h"
#include "NumberTree.h"

using namespace std;

void test(){
    cout << sizeof(NumTreeNote) << endl;
}

int main()
{
    StockTree *pStkTree = new StockTree();

    test();

    int i;
    cin >> i;

    return 0;
}