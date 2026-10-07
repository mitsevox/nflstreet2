#include <string.h>

#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/Lookup_8012078C.h"
#include "game/State_803EB098.h"
#include "game/fn_800670B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_8022781C.h"
#include "game/fn_80238174.h"
#include "game/cu_80136B1C.h"

/* 92-byte state allocated through fn_80238174 under the id 'blck'
   (fn_8011DF3C). */
struct Block_803EB028 {
    int mUnknown0;
    char mUnknown4[80];
    unsigned int mUnknown84;
    char mUnknown88[1];
    unsigned char mUnknown89;
    unsigned char mUnknown90;
    char mUnknown91[1];
};

/* 48-byte entry of Plan_80121264; the array fills +0 to +1440. */
struct Entry_80120E98 {
    char mUnknown0[12];
    float mUnknown12;
    char mUnknown16[20];
    int mUnknown36;
    char mUnknown40[8];
};

/* 32-byte entry of Plan_80121264; the array fills +1444 to +2372. */
struct Entry_801230B8 {
    char mUnknown0[16];
    int mUnknown16;
    char mUnknown20[8];
    float mUnknown28;
};

/* 2376-byte record cleared and filled by fn_80121264 (fn_801231E4 keeps one
   on its stack). */
struct Plan_80121264 {
    Entry_80120E98 mUnknown0[30];
    int mUnknown1440;
    Entry_801230B8 mUnknown1444[29];
    unsigned int mUnknown2372;
};

extern "C" int fn_800F08F8() {
    return 0;
}

extern "C" int fn_800F0900() {
    return 1;
}

extern "C" int fn_800F0908() {
    return 0;
}

extern "C" int fn_800F2C14() {
    return 0;
}

extern "C" int fn_800F8D24() {
    return 0;
}

extern "C" int fn_800F9CAC() {
    return 1;
}

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" {

extern Block_803EB028 *lbl_803EB028;
extern State_803EB098 *lbl_803EB098;
extern Lookup_8012078C *lbl_803EB09C;
extern float lbl_802DB004[];

void *fn_8023816C(void *pHandle);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
int fn_801BE648(void *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_801486A0(void);
Object_800670B4 *fn_80168708(int team);
int fn_80165098(Record_80067338 *pRecord);
int fn_801650BC(Record_80067338 *pRecord);
int fn_801650DC(Record_80067338 *pRecord);
int fn_801650FC(Record_80067338 *pRecord);
void fn_8016444C(Object_800670B4 *p);
void fn_800A5A88(void *p);
void fn_801F51DC(int a, void *pBase, int count, int size, int (*pCompare)(void *, void *),
                 void (*pSwap)(void *, void *), int b, int c);

void fn_8011893C(void);
void fn_80119020(void);
void fn_80119478(void);
void fn_801194F0(void);
void fn_80119B98(void);
void fn_8011AB38(void);
void fn_8011D9B8(void);
void fn_8011DBC8(Object_80039F5C *p, Block_8011DBC8 *pBlock);
void fn_8011DCDC(void);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
int fn_8011F1CC(void);
int fn_8011FA78(void *pA, void *pB);
int fn_8011FAFC(void *pA, void *pB);
int fn_8011FB80(void *pA, void *pB);
void fn_8011FE0C(void);
void fn_80120384(void);
void fn_80121264(Object_80039F5C *p, Plan_80121264 *pPlan);
void fn_80122670(Object_80039F5C *p, Plan_80121264 *pPlan, int angle);
void fn_801227DC(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry);
Entry_801230B8 *fn_801230B8(Plan_80121264 *pPlan);
int fn_80123254(void *pA, void *pB);
void fn_8012430C(float *pOut, int kind, Object_80039F5C *p);
int fn_801CFFD0(int a, int b);
float fn_801CFB94(int angle);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);

void fn_8011DA40(void)
{
    int team = fn_80178308();
    unsigned char side;

    lbl_803EB028->mUnknown84++;
    for (side = 0; side < 2; side++) {
        unsigned int count = fn_80178D70(side);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(side, i);
            Block_8011DBC8 *pBlock40 = &p->mUnknown1032.mUnknown40;
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1032.mUnknown4);

            switch (p->mUnknown1032.mUnknown0) {
            case 4:
            case 7:
                p->mUnknown1032.mUnknown16 = p->mUnknown1032.mUnknown4;
                if (side == team) {
                    if (--p->mUnknown1032.mUnknown102 < 0) {
                        fn_8011E1BC(p, pOther, 0, 2);
                        fn_8011E33C(pOther, p, 8);
                    }
                } else {
                    p->mUnknown1032.mUnknown102++;
                }
                break;
            case 3:
                if (p->mUnknown1032.mUnknown102 > 20 && fn_8011F1CC()) {
                    p->mUnknown1032.mUnknown0 = 2;
                }
            default:
                if (++p->mUnknown1032.mUnknown102 > 10) {
                    p->mUnknown1032.mUnknown16 = 0;
                }
                break;
            }
            if (--pBlock40->mUnknown52 <= 0) {
                pBlock40->mUnknown52 = 0;
                fn_8011DBC8(p, pBlock40);
            }
        }
    }
}

void fn_8011DBC0(void)
{
}

void fn_8011DBC4(void)
{
}

int fn_8011DC68(unsigned int id);

int fn_8011DBE0(Object_80039F5C *p, Object_80039F5C *pOther)
{
    unsigned int id = fn_801BE648(p->mpUnknown792);
    unsigned int otherId = fn_801BE648(pOther->mpUnknown792);

    if (otherId == id) {
        if (fn_8011DC68(id) && fn_8011DC68(otherId)) {
            return 1;
        }
        switch (otherId) {
        case 146:
        case 147:
        case 148:
        case 149:
        case 150:
        case 151:
        case 161:
            return 1;
        }
    }
    return 0;
}

int fn_8011DC68(unsigned int id)
{
    switch (id) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 106:
    case 107:
        return 1;
    }
    return 0;
}

int fn_8011DCA8(unsigned int id)
{
    switch (id) {
    case 49:
    case 52:
    case 55:
        return 1;
    }
    return 0;
}

void fn_8011DF3C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB028, sizeof(Block_803EB028), 0, 0x626C636B);

    fn_8023816C(pHandle);
    fn_802381E0(pHandle);
}

void fn_8011DF8C(void)
{
}

void fn_8011E938(Object_80039F5C *p);

void fn_8011DF90(void)
{
    unsigned char side;
    int team;

    fn_801C1F94(lbl_803EB028->mUnknown4, 0, sizeof(lbl_803EB028->mUnknown4));
    lbl_803EB028->mUnknown84 = 0;
    lbl_803EB028->mUnknown90 = 0;
    fn_8011E938(0);
    team = fn_80178308();
    for (side = 0; side < 2; side++) {
        unsigned int count = fn_80178D18(side);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);

            fn_801C1F94(&p->mUnknown1032, 0, sizeof(p->mUnknown1032));
            fn_8011DBC8(p, &p->mUnknown1032.mUnknown40);
            p->mUnknown1032.mUnknown107 = 5;
            p->mUnknown1032.mUnknown106 = 0;
        }
        team = fn_80178320();
    }
}

void fn_8011E3EC(Object_80039F5C *p, int a);

void fn_8011E068(void)
{
    int team = fn_80178308();
    unsigned int count = fn_80178D70(team);
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        if (p->mpState->mId == 51) {
            if (p->mpState->mUnknown4 == 33) {
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 2);
            } else if (p->mpState->mUnknown4 == 31) {
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 1);
            }
        }
    }
    fn_8011DCDC();
    lbl_803EB028->mUnknown89 = 1;
}

void fn_8011E13C(void)
{
    int mode = fn_800AD9B4();

    if (mode == 3 || mode == 4) {
        fn_8011DA40();
        fn_8011D9B8();
        fn_8011893C();
        fn_80119020();
        fn_80119478();
        fn_801194F0();
        fn_80119B98();
        fn_8011AB38();
    }
}

unsigned int fn_8011E188(void)
{
    return lbl_803EB028->mUnknown84;
}

void fn_8011E194(Object_80039F5C *p, unsigned char mask)
{
    Block_8011E240 *pBlock = &p->mUnknown1032;

    pBlock->mUnknown100 |= mask;
}

void fn_8011E1A8(Object_80039F5C *p, unsigned char mask)
{
    Block_8011E240 *pBlock = &p->mUnknown1032;

    pBlock->mUnknown100 &= ~mask;
}

void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value)
{
    Block_8011E240 *pBlock = &p->mUnknown1032;

    fn_8011E240(p);
    pBlock->mUnknown0 = value;
    pBlock->mUnknown102 = 0;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    pBlock->mUnknown40.mUnknown54 = 0;
    fn_8009BD2C(pA, &pBlock->mUnknown4);
    fn_8009BD2C(pB, &pBlock->mUnknown8);
    if (pBlock->mUnknown12 == 0) {
        fn_8009BD2C(pA, &pBlock->mUnknown12);
    }
}

void fn_8011E3A4(Object_80039F5C *p);

void fn_8011E240(Object_80039F5C *p)
{
    Block_8011E240 *pBlock = &p->mUnknown1032;
    Object_80039F5C *pOther;
    int ref;

    pBlock->mUnknown0 = 0;
    pBlock->mUnknown102 = 0;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    pBlock->mUnknown40.mUnknown54 = 0;
    pOther = fn_8009BCE8(&pBlock->mUnknown4);
    if (pOther) {
        fn_80143EBC(p, pOther);
        fn_80143EBC(pOther, p);
        fn_8009BD2C(p, &ref);
        if (pOther->mUnknown1032.mUnknown4 == ref) {
            fn_8011E3A4(pOther);
        }
    }
    fn_8009BD2C(0, &pBlock->mUnknown4);
    pOther = fn_8009BCE8(&pBlock->mUnknown8);
    if (pOther) {
        fn_80143EBC(p, pOther);
        fn_80143EBC(pOther, p);
        fn_8009BD2C(p, &ref);
        if (pOther->mUnknown1032.mUnknown4 == ref) {
            fn_8011E3A4(pOther);
        }
    }
    fn_8009BD2C(0, &pBlock->mUnknown8);
}

void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value)
{
    Block_8011E240 *pBlock = &p->mUnknown1032;

    pBlock->mUnknown40.mUnknown54 = 0;
    pBlock->mUnknown0 = value;
    pBlock->mUnknown102 = 0;
    fn_8009BD2C(pOther, &pBlock->mUnknown4);
    if (pBlock->mUnknown12 == 0) {
        fn_8009BD2C(pOther, &pBlock->mUnknown12);
    }
}

void fn_8011E3A4(Object_80039F5C *p)
{
    Block_8011E240 *pBlock = &p->mUnknown1032;

    pBlock->mUnknown0 = 0;
    pBlock->mUnknown102 = 0;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    pBlock->mUnknown40.mUnknown54 = 0;
    fn_8009BD2C(0, &pBlock->mUnknown4);
}

void fn_8011E3EC(Object_80039F5C *p, int a)
{
    p->mUnknown1032.mUnknown20 = a;
}

void fn_8011E884(Object_80039F5C *p, int a)
{
    p->mUnknown1032.mUnknown40.mUnknown52 = a;
}

int fn_8011E88C(Object_80039F5C *p)
{
    return p->mUnknown1032.mUnknown40.mUnknown52 != 0;
}

int fn_8011E8A4(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mUnknown1032.mUnknown0) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
        result = 1;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
    return result;
}

void fn_8011E8D8(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    if (p->mIdBytes[2] == fn_80178308()) {
        fn_8011E240(p);
    } else {
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1032.mUnknown4);

        if (pOther) {
            fn_8011E240(pOther);
        }
    }
}

void fn_8011E938(Object_80039F5C *p)
{
    fn_8009BD2C(p, &lbl_803EB028->mUnknown0);
}

int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);

int fn_8011E95C(void)
{
    int result = 0;

    if (fn_8011F1A4() && fn_8011F4C8() <= 3) {
        result = lbl_803EB028->mUnknown84 < 60;
    }
    return result;
}

int fn_8011E9B4(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mUnknown1032.mUnknown0) {
    case 4:
    case 5:
    case 6:
    case 7:
        result = 1;
        break;
    }
    return result;
}

int fn_8011E9D8(State_80039F5C *pState)
{
    unsigned int c = 0xFFFF;
    int result = 0;

    if (pState) {
        unsigned int a = fn_800F06F4(0, pState, 31, 0xFFFF);
        unsigned int b = fn_800F06F4(0, pState, 47, 0xFFFF);

        if (a != 0xFFFF || b != 0xFFFF) {
            c = fn_800F06F4(0, pState, 19, 0xFFFF);
        }
        if (a != 0xFFFF && c != 0xFFFF && a < c) {
            result = 1;
        }
        if (b != 0xFFFF && c != 0xFFFF && b < c) {
            result = 1;
        }
    }
    return result;
}

int fn_8011EFD4(void *p, void *q)
{
    State_803EB098 *pState = (State_803EB098 *)p;
    State_803EB098 *pOther = (State_803EB098 *)q;
    int result;

    if (pOther) {
        result = (pState->mUnknown4 != pOther->mUnknown4) | (pState->mUnknown0 != pOther->mUnknown0);
        result |= memcmp(pState->mUnknown8, pOther->mUnknown8, sizeof(pState->mUnknown8));
    } else {
        result = fn_80238278(pState, 576 + pState->mUnknown572 * sizeof(Record_8011F4F8), 0);
    }
    return result;
}

void fn_8011F068(void)
{
    Point_8017886C point;

    point = fn_80177FE0();
    if (lbl_803EB098->mUnknown4 <= 13) {
        lbl_803EB098->mUnknown0 = point.mX + lbl_802DB004[lbl_803EB098->mUnknown4];
    } else {
        lbl_803EB098->mUnknown0 = point.mX;
    }
}

void fn_8011F174(void)
{
    fn_800A5A88(lbl_803EB098->mUnknown528);
    lbl_803EB098 = 0;
}

int fn_8011F1A4(void)
{
    return fn_801650BC(fn_8016871C(fn_80178308()));
}

int fn_8011F1CC(void)
{
    return fn_801650DC(fn_8016871C(fn_80178308()));
}

int fn_8011F1F4(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 14;
}

int fn_8011F228(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 16;
}

int fn_8011F25C(void)
{
    return fn_8016871C(fn_80178308())->mUnknown14 == 4;
}

int fn_8011F290(void)
{
    return fn_8016871C(fn_80178308())->mUnknown14 == 18;
}

int fn_8011F2C4(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 2;
}

int fn_8011F2F8(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 5;
}

int fn_8011F32C(void)
{
    return fn_801650FC(fn_8016871C(fn_80178308()));
}

int fn_8011F354(void)
{
    return fn_801650FC(fn_8016871C(fn_80178348()));
}

void fn_8011F3A8(void)
{
    if (fn_8011F1A4()) {
        lbl_803EB098->mUnknown4 = fn_8016871C(fn_80178308())->mUnknown1C;
        if (fn_80168708(fn_80178308())->mUnknown8.mUnknownF) {
            if (lbl_803EB098->mUnknown4 & 1) {
                lbl_803EB098->mUnknown4 = lbl_803EB098->mUnknown4 - 1;
            } else {
                lbl_803EB098->mUnknown4 = lbl_803EB098->mUnknown4 + 1;
            }
        }
        fn_8011F068();
        lbl_803EB098->mUnknown5 = 1;
    } else {
        lbl_803EB098->mUnknown5 = 0;
        lbl_803EB098->mUnknown4 = 0;
        lbl_803EB098->mUnknown0 = fn_80177FE0().mX;
    }
}

void fn_8011F45C(int a)
{
    if (lbl_803EB098->mUnknown5) {
        lbl_803EB098->mUnknown4 = a;
    } else if (fn_8016871C(fn_80178308())->mUnknown14 == 2) {
        lbl_803EB098->mUnknown4 = a;
        lbl_803EB098->mUnknown5 = 1;
    }
    fn_8011F068();
}

unsigned char fn_8011F4C8(void)
{
    return lbl_803EB098->mUnknown4;
}

float fn_8011F4D4(void)
{
    return lbl_803EB098->mUnknown0;
}

void *fn_8011F4E0(void)
{
    return lbl_803EB098->mUnknown8;
}

void *fn_8011F4EC(void)
{
    return lbl_803EB098->mUnknown56;
}

Record_8011F4F8 *fn_8011F4F8(int index)
{
    return &lbl_803EB098->mUnknown576[index];
}

void *fn_8011F50C(void)
{
    return lbl_803EB098->mUnknown528;
}

Record_8011F518 *fn_8011F518(void)
{
    return &lbl_803EB098->mUnknown512;
}

int fn_8011F524(void)
{
    return fn_80165098(fn_8016871C(fn_80178348()));
}

void fn_8011F54C(void)
{
    fn_8016444C(fn_80168708(fn_80178308()));
}

void fn_8011F574(void)
{
    unsigned char i;

    for (i = 0; i < 2; i++) {
        lbl_803EB098->mUnknown6[i] = 0;
    }
}

unsigned char fn_8011F59C(int index)
{
    return lbl_803EB098->mUnknown6[index];
}

void fn_8011F5AC(int index)
{
    unsigned char *pCount = lbl_803EB098->mUnknown6;

    if (pCount[index] < 255) {
        pCount[index]++;
    }
}

void fn_8011F5CC(Lookup_8012078C *pLookup)
{
    short count = pLookup->mUnknown16;

    pLookup->mpUnknown0 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    fn_801C1F94(pLookup->mpUnknown0, 0, count);
    pLookup->mpUnknown4 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    fn_801C1F94(pLookup->mpUnknown4, 0, count);
    pLookup->mpUnknown8 = (Entry_8011FBE0 *)fn_801D2B7C(pLookup->mUnknown16 * sizeof(Entry_8011FBE0), 0, 0);
    fn_801C1F94(pLookup->mpUnknown8, 0, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pLookup->mpUnknown12 = (int *)fn_801D2B7C(pLookup->mUnknown16 * sizeof(int), 0, 0);
    fn_801C1F94(pLookup->mpUnknown12, 0, pLookup->mUnknown16 * sizeof(int));
}

int fn_8011F698(void *p, int value)
{
    fn_8011F5CC((Lookup_8012078C *)p);
    return 0;
}

int fn_8011F6BC(void *p, int value)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;

    fn_801D2BD0(pLookup->mpUnknown0);
    pLookup->mpUnknown0 = 0;
    fn_801D2BD0(pLookup->mpUnknown4);
    pLookup->mpUnknown4 = 0;
    fn_801D2BD0(pLookup->mpUnknown8);
    pLookup->mpUnknown8 = 0;
    fn_801D2BD0(pLookup->mpUnknown12);
    pLookup->mpUnknown12 = 0;
    return 0;
}

int fn_8011F71C(void *p, void *q)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;
    Lookup_8012078C *pOther = (Lookup_8012078C *)q;
    int result = 0;

    if (pOther) {
        result |= pLookup->mUnknown16 != pOther->mUnknown16;
        result |= pLookup->mUnknown18 != pOther->mUnknown18;
        result |= pLookup->mUnknown19 != pOther->mUnknown19;
        result |= pLookup->mUnknown20 != pOther->mUnknown20;
        result |= fn_80238258(pLookup->mpUnknown0 + ((char *)pLookup - (char *)lbl_803EB09C),
                              pOther->mpUnknown0 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16);
        result |= fn_80238258(pLookup->mpUnknown4 + ((char *)pLookup - (char *)lbl_803EB09C),
                              pOther->mpUnknown4 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16);
        result |= fn_80238258((char *)pLookup->mpUnknown8 + ((char *)pLookup - (char *)lbl_803EB09C),
                              (char *)pOther->mpUnknown8 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
        result |= fn_80238258((char *)pLookup->mpUnknown12 + ((char *)pLookup - (char *)lbl_803EB09C),
                              (char *)pOther->mpUnknown12 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16 * sizeof(int));
    } else {
        result = fn_80238278(pLookup, sizeof(Lookup_8012078C), 0);
        result = fn_80238278(pLookup->mpUnknown0 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16, result);
        result = fn_80238278(pLookup->mpUnknown4 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16, result);
        result = fn_80238278((char *)pLookup->mpUnknown8 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16 * sizeof(Entry_8011FBE0), result);
        result = fn_80238278((char *)pLookup->mpUnknown12 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16 * sizeof(int), result);
    }
    return result;
}

int fn_8011F904(void *p, void *pBuffer)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;

    memcpy(pBuffer, pLookup, sizeof(Lookup_8012078C));
    pBuffer = (char *)pBuffer + sizeof(Lookup_8012078C);
    memcpy(pBuffer, pLookup->mpUnknown0, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pBuffer, pLookup->mpUnknown4, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pBuffer, pLookup->mpUnknown8, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pBuffer = (char *)pBuffer + pLookup->mUnknown16 * sizeof(Entry_8011FBE0);
    memcpy(pBuffer, pLookup->mpUnknown12, pLookup->mUnknown16 * sizeof(int));
    return 1;
}

int fn_8011F99C(void *p, void *pBuffer)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;

    *pLookup = *(Lookup_8012078C *)pBuffer;
    pBuffer = (char *)pBuffer + sizeof(Lookup_8012078C);
    memcpy(pLookup->mpUnknown0, pBuffer, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pLookup->mpUnknown4, pBuffer, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pLookup->mpUnknown8, pBuffer, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pBuffer = (char *)pBuffer + pLookup->mUnknown16 * sizeof(Entry_8011FBE0);
    memcpy(pLookup->mpUnknown12, pBuffer, pLookup->mUnknown16 * sizeof(int));
    return 1;
}

int fn_8011FA54(void *p)
{
    short count = lbl_803EB09C->mUnknown16;

    return sizeof(Lookup_8012078C) + count + count + count * sizeof(Entry_8011FBE0) + count * sizeof(int);
}

void fn_8011FBA8(void *pA, void *pB)
{
    unsigned char *pFirst = (unsigned char *)pA;
    unsigned char *pSecond = (unsigned char *)pB;
    unsigned char value = *pFirst;

    *pFirst = *pSecond;
    *pSecond = value;
}

void fn_8011FBBC(void *pA, void *pB)
{
    Entry_8011FBE0 *pFirst = (Entry_8011FBE0 *)pA;
    Entry_8011FBE0 *pSecond = (Entry_8011FBE0 *)pB;
    Entry_8011FBE0 entry = *pFirst;

    *pFirst = *pSecond;
    *pSecond = entry;
}

void fn_8011FBE0(void)
{
    int team = fn_80178320();
    Object_80039F5C *pPlayer = fn_80137B40();
    Vector_80039F5C pos;
    unsigned char count;
    unsigned char i;

    if (pPlayer) {
        pos.mX = pPlayer->mMotion.mPos.mX;
        pos.mY = pPlayer->mMotion.mPos.mY;
    } else if (!fn_80138064(fn_801374BC(), &pos)) {
        fn_80137D58(fn_801374BC(), &pos);
    }
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Entry_8011FBE0 *pEntry = &lbl_803EB09C->mpUnknown8[i];

        pEntry->mUnknown0 = fn_8022781C(&fn_80039F5C(team, i)->mMotion.mPos, &pos);
        pEntry->mUnknown4 = i;
    }
}

void fn_8011FCA4(void)
{
    int count = fn_80178D70(fn_80178320());

    fn_801F51DC(1, lbl_803EB09C->mpUnknown0, count, 1, fn_8011FA78, fn_8011FBA8, 0, 0);
    fn_801F51DC(1, lbl_803EB09C->mpUnknown4, count, 1, fn_8011FAFC, fn_8011FBA8, 0, 0);
    fn_8011FBE0();
    fn_801F51DC(1, lbl_803EB09C->mpUnknown8, count, sizeof(Entry_8011FBE0), fn_8011FB80, fn_8011FBBC, 0, 1);
}

int fn_8011FD64(unsigned char index)
{
    int result;

    switch (fn_80039F5C(fn_80178320(), index)->mUnknown2914) {
    case 0:
    case 7:
    case 13:
    case 14:
    case 15:
        result = 1;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 16:
    case 17:
    case 18:
        result = 2;
        break;
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    default:
        result = 0;
        break;
    }
    if (fn_801486A0() == 2) {
        result = 1;
    }
    return result;
}

void fn_8012055C(int count)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB09C, sizeof(Lookup_8012078C), 0, 0x70757273);
    Lookup_8012078C *pLookup;

    fn_80238234(pHandle, fn_8011F698, fn_8011F6BC, 0, fn_8011F71C);
    fn_80238248(pHandle, fn_8011F904, fn_8011FA54, fn_8011F99C);
    pLookup = (Lookup_8012078C *)fn_8023816C(pHandle);
    pLookup->mUnknown16 = count;
    pLookup->mUnknown18 = 0;
    pLookup->mUnknown19 = 0;
    pLookup->mUnknown20 = 0;
    fn_802381E0(pHandle);
}

void fn_8012060C(void)
{
    lbl_803EB09C = 0;
}

void fn_80120720(int value)
{
    lbl_803EB09C->mUnknown20 -= value;
    if (lbl_803EB09C->mUnknown20 & 0x80) {
        lbl_803EB09C->mUnknown20 = 5;
        switch (lbl_803EB09C->mUnknown18) {
        case 0:
            fn_8011FE0C();
            break;
        case 3:
            fn_80120384();
            break;
        }
    }
}

Lookup_8012078C *fn_8012078C(void)
{
    return lbl_803EB09C;
}

void fn_80120B4C(int value, int *pList, unsigned char i, unsigned char count)
{
    for (; i < count; i++) {
        if (value == pList[i]) {
            pList[i] = 0;
            return;
        }
    }
}

void fn_80120CDC(Object_80039F5C *p, Object_80039F5C *pOther, Entry_80120E98 *pEntry)
{
    if (pOther->mIdBytes[2] == p->mIdBytes[2]) {
        switch (pOther->mUnknown1032.mUnknown0) {
        case 4:
        case 5:
        case 6:
        case 7:
            pEntry->mUnknown36 |= 1;
            break;
        case 1:
        case 2:
        case 3:
        default:
            pEntry->mUnknown36 |= 2;
            if (pOther->mUnknown3048.mId == 47) {
                pEntry->mUnknown36 |= 4;
            }
            break;
        }
        if (pOther->mFlags & 0x800) {
            pEntry->mUnknown36 |= 32;
        }
    } else {
        switch (pOther->mUnknown1032.mUnknown0) {
        case 4:
        case 5:
        case 6:
        case 7:
            pEntry->mUnknown36 |= 1;
            break;
        default:
            pEntry->mUnknown36 |= 8;
            break;
        }
        if (pOther->mFlags & 0x800) {
            pEntry->mUnknown36 |= 16;
        }
    }
}

void fn_80120E98(Plan_80121264 *pPlan, int index)
{
    int last = pPlan->mUnknown1440 - 1;

    if (index != last) {
        memcpy(&pPlan->mUnknown0[index], &pPlan->mUnknown0[index + 1], (last - index) * sizeof(Entry_80120E98));
    }
    pPlan->mUnknown1440--;
}

void fn_80123024(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    unsigned char i;

    for (i = 0; i < pPlan->mUnknown2372; i++) {
        pPlan->mUnknown1444[i].mUnknown28 = fn_801CFB94(fn_801CFFD0(pPlan->mUnknown1444[i].mUnknown16, angle) / 2);
        fn_801227DC(p, pPlan, &pPlan->mUnknown1444[i]);
    }
}

void fn_8012311C(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    fn_80121264(p, pPlan);
    fn_80122670(p, pPlan, angle & 0xFFFFFF);
    fn_80123024(p, pPlan, angle & 0xFFFFFF);
}

int fn_801231E4(Object_80039F5C *p, int angle)
{
    Plan_80121264 plan;

    fn_80121264(p, &plan);
    fn_80122670(p, &plan, angle);
    if (plan.mUnknown2372) {
        fn_80123024(p, &plan, angle);
        angle = fn_801230B8(&plan)->mUnknown16;
    }
    return angle;
}

void fn_80123E2C(void)
{
}

float fn_801242E0(float *pValues, unsigned int index)
{
    return pValues[index] + pValues[(index + 7) % 8] + pValues[(index + 9) % 8];
}

float fn_80125004(Object_80039F5C *p, int kind, int index);

float fn_80124FE0(Object_80039F5C *p, int kind)
{
    return fn_80125004(p, kind, 0);
}

float fn_80125004(Object_80039F5C *p, int kind, int index)
{
    float values[8];

    fn_8012430C(values, kind, p);
    fn_801F51DC(0, values, 8, sizeof(float), fn_80123254, 0, 0, -2);
    return values[index];
}

int fn_801251FC(Object_80039F5C *p)
{
    return p->mUnknown1032.mUnknown0 != 4;
}

}

extern "C" int fn_80125508() {
    return 0;
}

extern "C" {

int fn_80125510(Object_80039F5C *p, Message_800F01CC *pIn)
{
    int result = 0;
    unsigned char value;

    if (pIn) {
        value = pIn->mUnknown1[0];
    } else {
        value = 255;
    }
    if (fn_801251FC(p)) {
        Message_800F01CC message;

        result = 1;
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 96;
        message.mUnknown1[0] = value;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

int fn_80125DF0(Object_80039F5C *p)
{
    fn_801C1F94(&p->mUnknown336, 0, 12);
    return 0;
}

}
