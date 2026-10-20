#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    char mUnknown12[8];
};

struct Table_8015005C {
    Entry_8015005C mEntries[4];
    Vector_80039F5C mUnknown80;
    Point_8017886C mUnknown92[2];
    char mUnknown108[9];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

extern "C" {
Table_8015005C *fn_801530FC(void);

void fn_80152068(int index, Vector_80039F5C *pOut)
{
    pOut->mX = (fn_801530FC()->mUnknown92 + index)->mX;
    pOut->mY = (fn_801530FC()->mUnknown92 + index)->mY;
    pOut->mZ = 0.0f;
}
}
