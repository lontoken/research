#include "dbf.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    char fileName[] = "p.dbf";

    Column *pCol = new Column[5];
    memset(pCol, 0, sizeof(Column) * 5);

    pCol[0].name = "id";
    pCol[0].type = 'N';
    pCol[0].len = 10;

    pCol[1].name = "age";
    pCol[1].type = 'N';
    pCol[1].len = 5;

    pCol[2].name = "name";
    pCol[2].type = 'C';
    pCol[2].len = 50;

    pCol[3].name = "sex";
    pCol[3].type = 'C';
    pCol[3].len = 1;

    //pCol[4].name = "star";
    //pCol[4].type = 'N';
    //pCol[4].len = 10;

    int res = CreateDbf(fileName, pCol);
    cout << "res=" << res << endl;  

    Cdbfile *pFile = new Cdbfile(fileName);
    cout << "GetRecNum: " << pFile->GetRecNum() << endl;
    cout << "GetFieldNum: " << pFile->GetFieldNum() << endl;
    cout << "GetMaxFieldlen: " << pFile->GetMaxFieldlen() << endl;
    cout << "GetRecordSize: " << pFile->GetRecordSize() << endl;

    cout << "GetFieldlen: " << pFile->GetFieldlen(1) << endl;  
    cout << "GetFieldoff: " << pFile->GetFieldoff(1) << endl;

    int i ;
    cin >> i;

    return 0;
}