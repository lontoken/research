#ifndef _DATASOURCE_H
#define _DATASOURCE_H

#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class DataSource{
public:
    DataSource(string file): fileName(file){};
    virtual ~DataSource(){};

    int LoadData();
    int GetAllData(vector<string> &out);
private:
   string fileName;
   vector<string> dataSource; 
};

#endif