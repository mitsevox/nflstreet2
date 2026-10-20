#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    char mUnknown12[8];
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
Table_8015005C *fn_801530FC(void);
Object_80039F5C *fn_8003AC84(int id);
void fn_801487C0(int team, unsigned char begin);
void fn_80148814(Object_80039F5C *p);

void fn_801527E0(Class_802A2918 *p, int value)
{
    unsigned char begin = fn_801530FC()->mUnknown119[0];

    fn_801487C0(1, 4);
    if (value) {
        unsigned int i;

        for (i = 0; i < 4; i++) {
            if (fn_801530FC()->mEntries[i].mUnknown12[1]) {
                fn_80148814(fn_8003AC84(fn_801530FC()->mEntries[i].mUnknown0));
            }
        }
    }
    fn_801487C0(0, begin);
}

Object_80039F5C *fn_8015286C(Class_802A2918 *p, int index)
{
    return fn_8003AC84(p->mpUnknown1C->mpUnknown36->mEntries[index].mUnknown0);
}
}
