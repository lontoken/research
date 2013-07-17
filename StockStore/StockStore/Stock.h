#ifndef _STOCK_H
#define _STOCK_H

#pragma once

#include <sstream>

using namespace std;

class Stock{
public:
    Stock(){};

    void SetName(string &code);
    void SetCode(string &code);
    void SetCode(int code);
    string& GetCode();
    int GetCodeI();
private:
    string name;
    string code;
    int code_i;
};

#endif