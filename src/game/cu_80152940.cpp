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

struct Info_80152940 {
    Info_80152940() : mpObject(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}

    Object_80039F5C *mpObject;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

extern "C" {
Table_8015005C *fn_801530FC(void);
Object_80039F5C *fn_8003AC84(int id);

void fn_80152940(Class_802A2918 *p, int index, Info_80152940 *pInfo)
{
    Entry_8015005C *pEntry = &p->mpUnknown1C->mpUnknown36->mEntries[index];

    pInfo->mUnknown4 = pEntry->mUnknown16 + pEntry->mUnknown14 * 2;
    pInfo->mUnknown8 = pEntry->mUnknown4;
    pInfo->mUnknown12 = pEntry->mUnknown14;
    pInfo->mUnknown16 = pEntry->mUnknown16;
    pInfo->mpObject = fn_8003AC84(pEntry->mUnknown0);
    pInfo->mUnknown20 = pEntry->mUnknown12;
    pInfo->mUnknown21 = index;
}

unsigned char fn_801529C0(Class_802A2918 *p)
{
    Info_80152940 info;
    unsigned char result = 0;
    int i;

    for (i = 0; i <= 3; i++) {
        if (fn_801530FC()->mEntries[i].mUnknown12 != 255) {
            fn_80152940(p, i, &info);
            result = info.mUnknown21;
            break;
        }
    }
    return result;
}
}
