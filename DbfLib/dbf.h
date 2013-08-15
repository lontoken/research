#ifndef DBF_H
#define DBF_H

#include <stdio.h>

typedef int   BOOL;
#define MAXFIELD 100

typedef struct Column
{
    char      *name; // length <= 10
    unsigned char type;  // C-N-F-D-L-M-G
    unsigned char len;
    unsigned char dotLen;  //dot number when is N Type
} Column;

int CreateDbf(const char *fname, const Column *item);

class Cdbfile
{
private :
    FILE  *fp;
    int   hsize;
    int   Recsize;
    long Recnum;
    int  Fieldnum;
    int   *Fieldlen;
    Column *hitem;
    long  Lookno;
public :
    int  GetFieldidx(const char *itemname);
    long GetRecNum(void);
    int  GetFieldNum(void);
    int  GetFieldlen(int fieldno);
    int  GetFieldoff(int fieldno);
    int  GetMaxFieldlen(void);
    int  GetRecordSize(void);
    void AppendRecord(char *Recbuf);
    void *GetFieldData(long recno, const char *fname);
    BOOL SetFieldData(long recno, const char *fname, const char *buff);
    BOOL GetFieldData(long recno, const char *fname, char *buff, int bufsize=0x7FFF);
    BOOL SetFieldData(long recno, int fieldno, const char *buff);
    BOOL GetFieldData(long recno, int fieldno, char *buff, int bufsize=0x7FFF);
    long SearchSortStr(int fieldno, const char *str, BOOL igcase=0);
    long SearchStr(int fieldno, const char *str, long startno=0L);
    long SearchNextStr(int fieldno, const char *str);
    Cdbfile(const char *filename);
    ~Cdbfile(void);
    BOOL IsOpen(void);
};
#endif