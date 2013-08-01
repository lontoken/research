#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "DataSource.h"
#include "djb2.h"
#include "sdbm.h"
#include "fnv.h"
#include "crc32.h"
#include "murmurhash.h"

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
    delete pHashTable;
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

    delete pHashTable;
    return collis;
}

unsigned int testFnv(vector<string> &words)
{
    char *pHashTable = new char[HashTableSize];
    memset(pHashTable, 0, sizeof(char) * HashTableSize);

    unsigned int hash = 0;
    unsigned int collis = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        hash = fnv_32_str((*it).c_str());
        hash = hash % HashTableSize;
        if(pHashTable[hash]){
            collis++;
        }
        pHashTable[hash] = 1;
    }

    delete pHashTable;
    return collis;
}


unsigned int testFnva(vector<string> &words)
{
    char *pHashTable = new char[HashTableSize];
    memset(pHashTable, 0, sizeof(char) * HashTableSize);

    unsigned int hash = 0;
    unsigned int collis = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        hash = fnv_32a_str((*it).c_str());
        hash = hash % HashTableSize;
        if(pHashTable[hash]){
            collis++;
        }
        pHashTable[hash] = 1;
    }

    delete pHashTable;
    return collis;
}

unsigned int testCrc32(vector<string> &words)
{
    char *pHashTable = new char[HashTableSize];
    memset(pHashTable, 0, sizeof(char) * HashTableSize);

    unsigned int hash = 0;
    unsigned int collis = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        hash = GenerateCrc32(0, (*it).c_str(), (*it).size());
        hash = hash % HashTableSize;
        if(pHashTable[hash]){
            collis++;
        }
        pHashTable[hash] = 1;
    }

    delete pHashTable;
    return collis;
}


unsigned int testMurmurHash(vector<string> &words)
{
    char *pHashTable = new char[HashTableSize];
    memset(pHashTable, 0, sizeof(char) * HashTableSize);

    unsigned int hash = 0;
    unsigned int collis = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        hash = MurmurHash2A((*it).c_str(), (*it).size(), 0);
        hash = hash % HashTableSize;
        if(pHashTable[hash]){
            collis++;
        }
        pHashTable[hash] = 1;
    }

    delete pHashTable;
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
    collis = testFnv(words);
    cout << "size:" << HashTableSize << ": fnv : collis= " << collis << endl;
    collis = testFnva(words);
    cout << "size:" << HashTableSize << ": fnva : collis= " << collis << endl;
    collis = testCrc32(words);
    cout << "size:" << HashTableSize << ": crc32 : collis= " << collis << endl;
    collis = testMurmurHash(words);
    cout << "size:" << HashTableSize << ": murmur : collis= " << collis << endl;


    HashTableSize = 1000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;
    collis = testFnv(words);
    cout << "size:" << HashTableSize << ": fnv : collis= " << collis << endl;
    collis = testFnva(words);
    cout << "size:" << HashTableSize << ": fnva : collis= " << collis << endl;
    collis = testCrc32(words);
    cout << "size:" << HashTableSize << ": crc32 : collis= " << collis << endl;
    collis = testMurmurHash(words);
    cout << "size:" << HashTableSize << ": murmur : collis= " << collis << endl;


    HashTableSize = 10000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;
    collis = testFnv(words);
    cout << "size:" << HashTableSize << ": fnv : collis= " << collis << endl;
    collis = testFnva(words);
    cout << "size:" << HashTableSize << ": fnva : collis= " << collis << endl;
    collis = testCrc32(words);
    cout << "size:" << HashTableSize << ": crc32 : collis= " << collis << endl;
    collis = testMurmurHash(words);
    cout << "size:" << HashTableSize << ": murmur : collis= " << collis << endl;

    HashTableSize = 100000000;
    collis = testDjb2(words);
    cout << "size:" << HashTableSize << ": djd2 : collis= " << collis << endl;
    collis = testSdbm(words);
    cout << "size:" << HashTableSize << ": sdbm : collis= " << collis << endl;
    collis = testFnv(words);
    cout << "size:" << HashTableSize << ": fnv : collis= " << collis << endl;
    collis = testFnva(words);
    cout << "size:" << HashTableSize << ": fnva : collis= " << collis << endl;
    collis = testCrc32(words);
    cout << "size:" << HashTableSize << ": crc32 : collis= " << collis << endl;
    collis = testMurmurHash(words);
    cout << "size:" << HashTableSize << ": murmur : collis= " << collis << endl;

    int i;
    cin >> i;

    return 0;
}