#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8008044C.h"
#include "game/cu_8003E214.h"
#include "game/fn_8021D7B8.h"
#include "game/cu_80064864.h"

class Block_802A21E8 {
public:
    char mUnknown0[0x20];
    int mUnknown20;
    int mUnknown24;

    virtual ~Block_802A21E8();
};

class Class_802A2C90 : public Class_80148A58 {
public:
    Block_802A21E8 *mpUnknown1C;
    int mUnknown20;
};

struct Stats_8005CAE4 {
    Object_80039F5C *mpPlayers[4];
    int mValues[4];
};

extern "C" {
extern unsigned char lbl_803EB2D1;
extern void *lbl_803EB688;
extern const int lbl_802DE95C[];

void fn_8021956C(void *p, int a, int b, int c);
void fn_801735D8(unsigned int mask);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
void fn_800AAD58(void *p, float dt);
void fn_800BC51C(void *p);
void fn_800B3644(void *p);
void fn_800BFAB4(void *p);
void fn_800A039C(void *p);
void fn_800B9598(void *p);
void fn_800AACB8(void *p);
void fn_8007F6F8(int a, int b);
void fn_80178F20(void *p);
int fn_8014BC90(void);
void fn_8014BC98(const int *pValues, int *pOrder, unsigned int count);
void fn_8014BED8(const int *pValues, int *pOrder, unsigned int count);
int fn_801486A0(void);
int fn_801787DC(int team);
int fn_800C8744(int team);
Object_80039F5C *fn_8003AC84(int id);
int fn_8022B7A4(int handle, unsigned int tag, int *pValue);
unsigned char fn_8003B560(int group, int index, int *pValue);
int fn_80149F40(Class_80148A58 *p, int team, int kind);
int fn_8014A1B8(Class_80148A58 *p, int kind, int team);
unsigned short fn_800D3EB0(int team, int index);
int fn_800809FC(Object_8008044C *pObject, int a, int *pResult);
int fn_800808F8(Object_8008044C *pObject);

void fn_8014C868(void)
{
    if (lbl_803EB2D1) {
        fn_8021956C(lbl_803EB688, 3, 8, 1);
        lbl_803EB2D1 = 0;
    }
}

void fn_8014C8AC(void *p, float dt)
{
    fn_801735D8(2048);
    fn_8009D8CC(1);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_17(lbl_802DE95C);
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 0, 0);
    fn_800AAD58(p, dt);
}

void fn_8014C954(void)
{
    fn_80064EFC(3, 24, -1);
}

void fn_8014C980(void)
{
    fn_8021956C(lbl_803EB688, 3, 24, 1);
}

void fn_8014C9B0(Class_802A2C90 *p)
{
    fn_800BC51C(0);
    fn_800B3644(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    if (p->mpUnknown1C->mUnknown20 != 0) {
        fn_8007F6F8(14, p->mpUnknown1C->mUnknown20);
    }
    if (p->mpUnknown1C->mUnknown24 != -1) {
        fn_8007F6F8(1, p->mpUnknown1C->mUnknown24);
    }
    p->mUnknown20 = -1;
    fn_80178F20(0);
    delete p->mpUnknown1C;
    p->mpUnknown1C = 0;
}

int fn_8014CA78(void)
{
    return 7;
}

int fn_8014CA80(void)
{
    return 7;
}

int fn_8014CA88(void)
{
    return 4;
}

int fn_8014CA90(void)
{
    return 14;
}

int fn_8014CA98(void)
{
    int result = 0;
    if (fn_8014BC90()) {
        result = 2;
    }
    return result;
}

void fn_8014CAD4(Class_80148A58 *p, int value, int *pList, int *pIds)
{
    fn_8003E8FC(value, pList, pIds);
    fn_8014BC98(pList, pIds, 4);
    fn_8014BED8(pList, pIds, 4);
}

void fn_8014CCE8(Class_80148A58 *p, int team, Stats_8005CAE4 *pStats)
{
    int ids[4];
    Object_8008044C cursor;
    int id = 0;
    int handle = fn_800C8744(team);
    int value = 0;
    fn_8008040C(&cursor, 0);
    if (fn_8003B560(team, 0, &id)) {
        fn_800809FC(&cursor, id, 0);
        id = fn_800808F8(&cursor);
    }
    ids[0] = id;
    if (fn_8003B560(team, 2, &id)) {
        fn_800809FC(&cursor, id, 0);
        id = fn_800808F8(&cursor);
    }
    ids[1] = id;
    if (fn_8003B560(team, 3, &id)) {
        fn_800809FC(&cursor, id, 0);
        id = fn_800808F8(&cursor);
    }
    ids[2] = id;
    if (fn_8003B560(team, 1, &id)) {
        fn_800809FC(&cursor, id, 0);
        id = fn_800808F8(&cursor);
    }
    ids[3] = id;
    fn_8008056C(&cursor);
    for (unsigned char i = 0; i < 4; i++) {
        pStats->mpPlayers[i] = fn_8003AC84(ids[i]);
    }
    pStats->mValues[0] = fn_801787DC((unsigned char)team);
    fn_8022B7A4(handle, 0x74727374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x74507374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x64647374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x69447374, &value);
    pStats->mValues[3] = value;
    pStats->mValues[2] = p->vfn_24(team, 0x61746467);
}

void fn_8014CF44(void)
{
    if (fn_801486A0() == 4) {
        fn_8009D8CC(5);
        fn_8009D964(5, 5);
    }
}

int fn_8014CF80(Class_80148A58 *p, int team, int kind)
{
    int result;
    if (kind == 41) {
        result = p->vfn_34(41, team, 1, 0);
    } else {
        result = fn_80149F40(p, team, kind);
    }
    return result;
}

int fn_8014CFDC(Class_80148A58 *p, int kind, int team)
{
    int result;
    if (kind == 41) {
        result = fn_800D3EB0(team, 101);
    } else {
        result = fn_8014A1B8(p, kind, team);
    }
    return result;
}

void fn_8014D014(Class_802A2C90 *p, int a, int b)
{
    if (a == 0) {
        p->mUnknown20 = b;
    }
}
}
