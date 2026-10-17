#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_8017F584.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    char mUnknown13[7];
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
extern Class_802A2918 lbl_8031BDD4;

Object_80039F5C *fn_8003AC84(int id);
int fn_801529C0(Class_802A2918 *p);

Object_80039F5C *fn_8015264C(void)
{
    return fn_8003AC84(lbl_8031BDD4.mpUnknown1C->mpUnknown36->mEntries[0].mUnknown0);
}

int fn_8015267C(Class_802A2918 *p)
{
    if (fn_8017F584() == 7) {
        return fn_801529C0(p) <= 2;
    }
    return lbl_8031BDD4.mpUnknown1C->mpUnknown36->mEntries[0].mUnknown12 != 255;
}
}
