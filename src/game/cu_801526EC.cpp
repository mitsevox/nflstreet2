#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    char mUnknown13;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mUnknown18[2];
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[17];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

struct Object_8015005C {
    char mUnknown0[36];
    Table_8015005C *mpUnknown36;
};

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
};

extern "C" {
void fn_801526EC(Class_802A2918 *p)
{
    unsigned char i;

    p->mpUnknown1C->mpUnknown36->mCount = 4;
    p->mpUnknown1C->mpUnknown36->mUnknown119[0] = 3;
    p->mpUnknown1C->mpUnknown36->mUnknown119[5] = 0;
    p->mpUnknown1C->mpUnknown36->mUnknown125 = 2;
    for (i = 0; i <= 3; i++) {
        Entry_8015005C *pEntries = p->mpUnknown1C->mpUnknown36->mEntries;

        pEntries[i].mUnknown4 = pEntries[i].mUnknown8 = pEntries[i].mUnknown10 =
            pEntries[i].mUnknown14 = pEntries[i].mUnknown16 = 0;
        p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown13 = 0;
        fn_80039F5C(1, i)->mUnknown9[2] = 1;
    }
}
}
