#include <stdlib.h>
#include "Stock.h"

void Stock::SetCode(string &code){
    this->code.assign(code);
    this->code_i = stoi(code.c_str());

    return;
}

void Stock::SetCode(int code){
    stringstream ss;
    ss << code;
    this->code = ss.str();
    this->code_i = code;

    return;
}

void Stock::SetName(string &name){
    this->name.assign(name);

    return;
}
