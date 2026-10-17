#include "game/Class_80148A58.h"

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

unsigned char fn_80152FFC(Class_802A2918 *p, int team)
{
    if (team == 0) {
        return p->mpUnknown1C ? p->mpUnknown1C->mpUnknown36->mUnknown119[0] : 3;
    }
    return p->mpUnknown1C ? p->mpUnknown1C->mpUnknown36->mCount : 4;
}

int fn_80153044(Class_802A2918 *p)
{
    return 0;
}

int fn_8015304C(Class_802A2918 *p, int value)
{
    int result = 0;

    if (value != 255) {
        Entry_8015005C *pEntry = fn_801530FC()->mEntries;
        Entry_8015005C *pEnd = pEntry + 3;
        int count = 0;

        for (; pEntry <= pEnd; pEntry++) {
            unsigned char kind = pEntry->mUnknown12[0];

            if (kind != 255 && pEntry->mUnknown12[1] == 0) {
                count++;
                if (kind == value) {
                    result = 1;
                    break;
                }
            }
        }
        if (count == 0) {
            result = 1;
        }
    }
    return result;
}
}
