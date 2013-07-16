#ifndef _NUMBERTREE_H
#define _NUMBERTREE_H

#pragma once

typedef struct TNumTreeNote NumTreeNote;

struct TNumTreeNote{
    int lever;
    NumTreeNote *list[10];
};

NumTreeNote *GetNewNumTreeNote(int lever);

#endif