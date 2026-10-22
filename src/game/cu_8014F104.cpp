#include "game/Class_802A2B68.h"
#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"

struct Info_8014F3E4 {
    Object_80039F5C *mpUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned int mUnknown12;
    unsigned char mUnknown16;
};

extern "C" {
extern int lbl_803EB2D8;

Object_80039F5C *fn_8003AC84(int id);
int fn_8017F584(void);
int fn_8014FF34(Class_802A2B68 *p);
unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer);

Block_8014F104 *fn_8014F104(Class_80148A58 *p)
{
    return static_cast<Class_802A2B68 *>(p)->mpUnknown1C;
}

int fn_8014F10C(Class_802A2B68 *p, int team)
{
    if (team == 0) {
        return 5;
    }
    return 1;
}

void fn_8014F120(Class_802A2B68 *p, int value, int *pList, int *pIds)
{
    for (unsigned char i = 0; i <= 6 && pList[i] != 32767; i++) {
        pIds[i] = pIds[i + 7] = pList[i];
    }
}

void fn_8014F168(Class_802A2B68 *p, int value, int *pList, int *pIds, int a, int b)
{
    p->vfn_10(value, pList, pIds);
}

int fn_8014F36C(Class_802A2B68 *p)
{
    if (fn_8017F584() == 7) {
        return fn_8014FF34(p) <= 4;
    }
    return fn_8014F104(fn_80148A58())->mpUnknown34[0].mUnknown8 != 255;
}

void fn_8014F3DC(int value)
{
    lbl_803EB2D8 = value;
}

void fn_8014F3E4(Class_80148A58 *p, int index, Info_8014F3E4 *pInfo)
{
    Record_8014F104 *pRecord = &static_cast<Class_802A2B68 *>(p)->mpUnknown1C->mpUnknown34[index];
    pInfo->mUnknown4 = pRecord->mUnknown4;
    pInfo->mUnknown8 = pRecord->mUnknown12[8];
    pInfo->mUnknown12 = pRecord->mUnknown12[0];
    pInfo->mpUnknown0 = fn_8003AC84(pRecord->mUnknown0);
    pInfo->mUnknown16 = pRecord->mUnknown8;
}

Object_80039F5C *fn_8014F448(Class_80148A58 *p)
{
    return fn_8003AC84(static_cast<Class_802A2B68 *>(p)->mpUnknown1C->mpUnknown34[0].mUnknown0);
}

unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer)
{
    unsigned int i;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0 == pPlayer->mUnknown2908) {
            break;
        }
    }
    return i;
}

void fn_8014F4D8(Class_80148A58 *p, Object_80039F5C *pPlayer, int kind, int value)
{
    unsigned int index = fn_8014F474(fn_80148A58(), pPlayer);
    if (kind == 8 && value > fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown48) {
        fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown48 = value;
    }
    fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown12[kind] += value;
}
}
