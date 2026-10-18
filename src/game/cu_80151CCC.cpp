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
    char mUnknown100[16];
    unsigned char mUnknown116;
    unsigned char mUnknown117;
    unsigned char mCount;
    unsigned char mUnknown119;
    int mUnknown120;
    unsigned char mUnknown124;
    unsigned char mUnknown125;
    unsigned char mUnknown126;
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
Object_80039F5C *fn_8003AC84(int id);
void fn_800B6658(Object_80039F5C *pPlayer);
void fn_801488D4(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80148814(Object_80039F5C *p);
void fn_8017E094(int a);

void fn_80151CCC(Class_802A2918 *p, unsigned int index, int value)
{
    Object_80039F5C *pPlayer;
    Object_80039F5C *pOther;

    p->mpUnknown1C->mpUnknown36->mEntries[index].mUnknown12[1] = 1;
    p->mpUnknown1C->mpUnknown36->mCount--;
    p->mpUnknown1C->mpUnknown36->mUnknown119--;
    pPlayer = fn_8003AC84(p->mpUnknown1C->mpUnknown36->mEntries[index].mUnknown0);
    fn_800B6658(pPlayer);
    if (value) {
        pOther = fn_80039F5C(1, p->mpUnknown1C->mpUnknown36->mCount);
        if (pOther != pPlayer) {
            fn_801488D4(pPlayer, pOther);
        }
        fn_80148814(pOther);
        fn_8017E094(p->mpUnknown1C->mpUnknown36->mCount);
    }
}
}
