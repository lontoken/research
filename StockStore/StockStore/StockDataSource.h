#ifndef _STOCKDATASOURCE_H
#define _STOCKDATASOURCE_H

#include <fstream>
#include <sstream>
#include <list>

using namespace std;

class StockDataSource{
public:
    StockDataSource(){};
    StockDataSource(file): filename(file){};

    
private:
    string filename;
    list<Stock*> stockList;
}

#endif