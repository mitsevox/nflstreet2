#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"
#include "game/cu_80136B1C.h"

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
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    unsigned char mUnknown44[4];
};

class Class_802A1930 : public Class_802A56E8 {
};

extern "C" {
extern Class_802A2918 lbl_8031BDD4;

int fn_801787DC(int team);

Table_8015005C *fn_801530FC(void)
{
    return lbl_8031BDD4.mpUnknown1C->mpUnknown36;
}

int fn_8015310C(Class_802A2918 *p)
{
    int result = 1;
    unsigned char i;

    for (i = 0; i < fn_801383C8(); i++) {
        if (p->mUnknown44[i] == 0) {
            result = 0;
            break;
        }
    }
    return result;
}

void fn_80153168(Class_802A2918 *p, int index, unsigned char value)
{
    p->mUnknown44[index] = value;
}

int fn_80153174(Class_802A1930 *p)
{
    unsigned short score0 = fn_801787DC(0);
    unsigned short score1 = fn_801787DC(1);

    unsigned short high;

    if (score0 > score1) {
        high = score0;
    } else {
        high = score1;
    }
    return high + 8;
}
}
