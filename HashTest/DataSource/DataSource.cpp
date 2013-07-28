#include "DataSource.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

const int LINE_LENGTH = 500;

char* trim(char *str)
{
    char *str_last, *str_cur;
    if(str == NULL) return NULL;
    for(; *str==0x20 || *str=='\t'; ++str);
    for(str_last=str_cur=str; *str_cur!='\0'; ++str_cur)
        if(*str_cur!=0x20 && *str_cur!='\t') str_last=str_cur;

    *++str_last=0;
    return str;
}

int DataSource::LoadData()
{
    ifstream fin;
    fin.open(fileName);

    if (!fin.is_open()){
        cerr << "Error opening file" << endl; 
        return 0;
    }  

    int iCount = 0;
    int iLine = 0;
    bool bIsNum = true;
    char strBuf[LINE_LENGTH];
    string word;
    string curWrod;
    while(!fin.eof()){
        ++iCount;

        fin.getline(strBuf, LINE_LENGTH);
        char *pChar = trim(strBuf);

        int idx = 0;
        char *pCur = pChar;
        while(*pCur){
            
            if(*pCur >= '0' && *pCur <= '9'){
                pCur++;
            }else if(*pCur == 0x09 || *pCur == 0x20){
                pCur++;
            }else{
                break;
            }
        }
        
        if(*pCur){
            word.assign(pCur);
            dataSource.push_back(word);
        }
    }

    return iCount;
}

int DataSource::GetAllData(vector<string> &out)
{
    out.insert(out.end(), dataSource.begin(), dataSource.end());  
    return out.size();
}
