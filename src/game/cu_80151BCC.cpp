#include "game/Class_80148A58.h"
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
Point_8017886C fn_80177FFC(int team);

void fn_80151BCC(Class_802A2918 *p)
{
    unsigned int i;
    unsigned int count;
    Object_80039F5C *pPlayer;

    count = p->mpUnknown1C->mpUnknown36->mUnknown119;
    for (i = 0; i < count; i++) {
        pPlayer = fn_80039F5C(0, i);
        float limit = fn_80177FFC(0).mY;
        if (pPlayer->mMotion.mPos.mY > limit) {
            pPlayer->mMotion.mPos.mY = limit;
        }
    }
    count = p->mpUnknown1C->mpUnknown36->mCount;
    for (i = 0; i < count; i++) {
        pPlayer = fn_8003AC84(p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown0);
        float limit = fn_80177FFC(1).mY + 5.0f;
        if (pPlayer->mMotion.mPos.mY < limit) {
            pPlayer->mMotion.mPos.mY = limit;
        }
    }
}
}
