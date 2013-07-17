#ifndef _NUMBERTREE_H
#define _NUMBERTREE_H

#pragma once

#include "Stock.h"

typedef struct TNumTreeNote NumTreeNote;

struct TNumTreeNote{
    int lever;
    int num;
    NumTreeNote *list[10];
    Stock* data;
};

NumTreeNote *GetNewNumTreeNote(int lever);

#endif