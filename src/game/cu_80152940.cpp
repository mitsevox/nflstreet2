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
int fn_801499A8(Class_80148A58 *p, int kind, int team, int index, Object_80039F5C *pPlayer);
int fn_8022B414(int handle, unsigned int tag, int *pValue);

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

int fn_80152A54(Class_802A2918 *p, int kind, int team, int index, Object_80039F5C *pPlayer)
{
    Info_80152940 info;
    int result = 0;

    fn_80152940(p, index, &info);
    if (info.mpObject != 0) {
        switch (kind) {
        case 27:
            result = info.mUnknown16 + info.mUnknown12;
            break;
        case 28:
        case 29:
            result = info.mUnknown12;
            break;
        case 31:
            result = 0;
            break;
        case 32:
            fn_8022B414(pPlayer->mUnknown2908, 0x64706467, &result);
            break;
        case 18:
            result = 4 - info.mUnknown21;
            break;
        case 17:
        case 19:
            result = info.mUnknown4;
            break;
        default:
            result = fn_801499A8(p, kind, team, index, pPlayer);
            break;
        }
    }
    return result;
}
}
