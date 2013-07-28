#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "DataSource.h"
#include "djb2.h"
#include "sdbm.h"

using std::cout;
using std::endl;
using std::cin;

unsigned int HashTableSize = 100000;

unsigned int testDjb2(vector<string> &words)
{
    char *pHashTable = new char[HashTableSize];
    memset(pHashTable, 0, sizeof(char) * HashTableSize);

    unsigned int hash = 0;
    unsigned int collis = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        hash = DJB2Hash((*it).c_str(), (*it).size());
        hash = hash % HashTableSize;
        if(pHashTable[hash]){
            collis++;
        }
        pHashTable[hash] = 1;
    }

    return collis;
}

unsigned int testSdbm(vector<string> &words)
{
    char *pHashTable = new char[HashTableSize];
    memset(pHashTable, 0, sizeof(char) * HashTableSize);

    unsigned int hash = 0;
    unsigned int collis = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        hash = SdbmHash((*it).c_str());
        hash = hash % HashTableSize;
        if(pHashTable[hash]){
            collis++;
        }
        pHashTable[hash] = 1;
    }

    return collis;
}

int main()
{
    DataSource *ds = new DataSource("words.ini");
    int line = ds->LoadData();
    cout << line << endl;

    vector<string> words;
    line = ds->GetAllData(words);

   
    int collis = 0;

    HashTableSize = 100000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;


    HashTableSize = 1000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;

    HashTableSize = 10000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;

    HashTableSize = 100000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;

    /*HashTableSize = 1000000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;*/

    int i;
    cin >> i;

    return 0;
}