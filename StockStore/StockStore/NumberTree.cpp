#include "NumberTree.h"

NumTreeNote *GetNewNumTreeNote(int lever){
    NumTreeNote *p = new NumTreeNote();
    p->lever = lever;
    p->num = 0;
    p->data = NULL;
    memset((NumTreeNote*)(p->list), 0, sizeof(p->list));    

    return p;
}