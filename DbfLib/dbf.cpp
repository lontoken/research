#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ctime>

#include "dbf.h"

int CreateDbf(const char *fname, const Column *item)
{
    FILE *out;
    static time_t InnerTimer;
    int  headlen=33, reclen=1;
    char buf[32];

    static struct tm *local;
    InnerTimer = time(NULL);
    local = localtime(&InnerTimer);

    if((out=fopen(fname,"wb"))==NULL)
        return 0;
    memset(buf,0,32);
    //getdate(&curdate);

    buf[0] = 0x03;
    buf[1] = (char)(local->tm_year + 1900 - 2000);
    buf[2] = local->tm_mon + 1;
    buf[3] = local->tm_mday;
    *(long*)&buf[4] = 0L; //record number
    fwrite(buf,32,1,out);

    while(item->len!=0)
    {
        memset(buf,0,32);
        strncpy(buf,item->name,10);
        strupr(buf);
        //*(int*)&buf[11] = 0x100+item->type;
        buf[11] = item->type;
        *(int*)&buf[12] = reclen;

        *(int*)&buf[16] = item->len;
        *(int*)&buf[17] = item->dotLen;
        fwrite(buf,32,1,out);
        reclen += item->len;
        headlen += 32;
        item++;
    }
    buf[0] = 0x0D;
    fwrite(buf,1,1,out);
    fseek(out,8,SEEK_SET);
    fwrite(&headlen,2,1,out);
    fwrite(&reclen,2,1,out);

    fclose(out);
    return 1;
}

Cdbfile::Cdbfile(const char *filename)
{
    int len=0;
    char *tmpbuf;

    hitem=NULL;
    Recnum=0L;
    hsize=Recsize=Fieldnum=0;

    if((fp=fopen(filename,"r+b"))==NULL) return;
    fread(&Recnum,4,1,fp);
    if(*(char*)&Recnum!=3)
    {
        fclose(fp); fp=NULL; return;
    }

    fread(&Recnum,4,1,fp);
    fread(&hsize,2,1,fp);
    Fieldnum=hsize/0x20-1;
    hsize++;

    fread(&Recsize,2,1,fp);

    hitem=new Column[Fieldnum];
    tmpbuf=new char [11*Fieldnum+2*Fieldnum];
    if(tmpbuf)
    {
        for(int i=0; i<Fieldnum; i++)
            hitem[i].name=tmpbuf+11*i;
        Fieldlen=(int*)(tmpbuf+11*Fieldnum);
    }
    else
    {
        if(hitem) delete hitem;
        hitem=NULL;
        fclose(fp);
        fp=NULL;
        return;
    }

    fseek(fp,0x20L,SEEK_SET);
    for(int i=0; i<Fieldnum; i++)
    {
        Fieldlen[i] = 0;
        if(hitem)
        {
            fread(hitem[i].name,11,1,fp);
            fread(&hitem[i].type,1,1,fp);
            fseek(fp,4L,SEEK_CUR);
            fread(&hitem[i].len,1,1,fp);
            Fieldlen[i]=hitem[i].len;
        }
        Fieldlen[i]+=len;
        len=Fieldlen[i];
        fseek(fp,15L,SEEK_CUR);
    }
}

Cdbfile::~Cdbfile(void)
{
    if(fp) fclose(fp);
    if(hitem)
    {
        delete hitem[0].name;
        delete hitem;
    }
    fp=NULL;
    hitem=NULL;
}

BOOL Cdbfile::IsOpen(void)
{
    return fp!=NULL;
}

int Cdbfile::GetFieldidx(const char *itemname)
{
    if(hitem)
        for(int i=0; i<Fieldnum; i++)
            if(stricmp(itemname,hitem[i].name)==0)
                return i;
    return -1;
}

long Cdbfile::GetRecNum(void)
{
    return Recnum;
}

int Cdbfile::GetFieldNum(void)
{
    return Fieldnum;
}

int Cdbfile::GetFieldlen(int fieldno)
{
    int len=0;

    if(Fieldnum==0) return 0;
    if(fieldno>0)
        len=Fieldlen[fieldno-1];
    return Fieldlen[fieldno]-len;
}

int Cdbfile::GetFieldoff(int fieldno)
{
    if(Fieldnum==0) return 0;
    if(fieldno>0)
        return Fieldlen[fieldno-1];
    return 0;
}

int Cdbfile::GetMaxFieldlen(void)
{
    int len=0;

    if(Fieldnum==0) return 0;
    for(int i=0; i<Fieldnum; i++)
        if(Fieldlen[i]>len)
            len=Fieldlen[i];
    return len;
}

int Cdbfile::GetRecordSize(void)
{
    return Recsize;
}

void Cdbfile::AppendRecord(char *Recbuf)
{
    long recnum;

    if(!fp) return;
    fseek(fp,0L,SEEK_END);
    fwrite(Recbuf,Recsize,1,fp);
    fseek(fp,4L,SEEK_SET);
    fread(&recnum,4,1,fp);
    recnum++;
    fseek(fp,4L,SEEK_SET);
    fwrite(&recnum,4,1,fp);
    Recnum++;
}

BOOL Cdbfile::SetFieldData(long recno, const char *fname, const char *buff)
{
    int fieldno=GetFieldidx(fname);
    if(fieldno<0) return -1;
    return SetFieldData(recno,fieldno,buff);
}

BOOL Cdbfile::SetFieldData(long recno, int fieldno, const char *buff)
{
    int num=0;
    long off;
    char outbuf[256];

    if(fp==NULL || recno<0 ||recno>=Recnum || fieldno<0 || fieldno>=Fieldnum)
        return 0;
    off=(long)hsize+recno*Recsize;
    if(fieldno)
    {
        num=Fieldlen[fieldno-1];
        off+=num;
    }
    fseek(fp,off,SEEK_SET);

    num=Fieldlen[fieldno]-num;

    memset(outbuf,0x20,num);
    memcpy(outbuf,buff,strlen(buff));

    fwrite(outbuf,num,1,fp);
    return 1;
}

void *Cdbfile::GetFieldData(long recno, const char *fname)
{
    char *buff;
    int fieldno, size;

    fieldno=GetFieldidx(fname);
    if(fieldno<0)
        return NULL;
    size = Fieldlen[fieldno];
    if(fieldno)
        size -= Fieldlen[fieldno-1];
    buff=new char [size+1];
    if(buff)
        GetFieldData(recno,fieldno,buff);
    return buff;
}

BOOL Cdbfile::GetFieldData(long recno, const char *fname, char *buff, int bufsize)
{
    buff[0] = 0;
    int fieldno=GetFieldidx(fname);
    if(fieldno<0) return -1;
    return GetFieldData(recno,fieldno,buff,bufsize);
}

BOOL Cdbfile::GetFieldData(long recno, int fieldno, char *buff, int bufsize)
{
    int num=0;
    long off;

    buff[0] = 0;
    if(fp==NULL || recno<0 || recno>=Recnum || fieldno<0 || fieldno>=Fieldnum)
        return 0;
    off=(long)hsize+recno*(Fieldlen[Fieldnum-1]+1);
    if(fieldno)
    {
        num=Fieldlen[fieldno-1];
        off+=num;
    }
    fseek(fp,off,SEEK_SET);

    num=Fieldlen[fieldno]-num;

    if(num>=bufsize)
    {
        printf("buffer overflow!/n");
        exit(3);
    }
    fread(buff,num,1,fp);
    if(toupper(hitem[fieldno].type)=='C')
    {
        while(num>=0 && buff[--num]==' ') ;
        num++;
    }
    buff[num] = 0;
    return 1;
}

long Cdbfile::SearchSortStr(int fieldno, const char *str, int igcase)
{
    long temp;
    long leftno = 0L;
    long rightno = Recnum;
    int  l2 = GetFieldlen(fieldno);

    if(fp==NULL || fieldno<0 || fieldno>=Fieldnum) return -1;
    while(leftno<=rightno)
    {
        char *buf = new char [l2];

        temp = (leftno+rightno)>>1;
        GetFieldData(temp,fieldno,buf);

        int val;
        if(igcase)
            val = stricmp(buf,str);
        else
            val = strcmp(buf,str);

        delete buf;

        if(val==0) return temp;
        if(val>0)
            rightno = temp-1;
        else
            leftno = temp+1;
    }
    return -1;
}

long Cdbfile::SearchStr(int fieldno, const char *str, long startno)
{
    int l2 = GetFieldlen(fieldno);

    if(fp==NULL || startno<0 || startno>=Recnum || fieldno<0 || fieldno>=Fieldnum)
        return -1;
    char *buf = new char [l2];
    for(long i=startno; i<Recnum; i++)
    {
        GetFieldData(i,fieldno,buf);

        if(stricmp(str,buf)==0)
        {
            Lookno = i+1;
            delete buf;
            return i;
        }
    }
    delete buf;
    return -1;
}

long Cdbfile::SearchNextStr(int fieldno, const char *str)
{
    if(Lookno<0) return -1;
    return(SearchStr(fieldno,str,Lookno));
}