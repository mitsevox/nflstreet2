#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Object_8008044C.h"
#include "game/cu_8003AEA8.h"
#include "game/cu_8003E214.h"
#include "game/fn_8003B6BC.h"
#include "game/fn_801C1F94.h"

/* Passed by pointer; only the words at +4 and +8 are read. */
struct Pair_8003AEA8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
int fn_800808F8(Object_8008044C *pObject);
int fn_800809FC(Object_8008044C *pObject, int a, int *pResult);
int fn_80080D10(Object_8008044C *pObject);
int fn_800812E0(Object_8008044C *pObject, int a);
int fn_80085620(int a, int b);
int *fn_80085744(int a, int b);
int fn_8008593C(int a, int b, int c, int d);
int fn_80085BE4(int a);
int fn_80085C3C(int a);
int fn_80085C94(int a, int *values);
int fn_80085D54(void);
int fn_800B4A18(int a, int b, int c);
int fn_801485D4(void);
int fn_80187C6C(void);
int fn_80187C8C(void);
int fn_8022D874(int tag, int a, int b, int c);
}

static Object_8008044C lbl_8030749C;
static int lbl_803074C8[2][14];
static int lbl_80307538[2][14];
static int lbl_803075A8[2][7];

static int lbl_802CCCAC[2][7] = {
    {11, 8, 10, 7, 13, 9, 12},
    {2, 4, 5, 6, 3, 0, 1},
};
static int lbl_802CCCE4[14][3] = {
    {6, 2, 0}, {2, 4, 0}, {3, 4, 1}, {3, 4, 1}, {7, 0, 4}, {7, 0, 4}, {7, 0, 4},
    {9, 5, 4}, {9, 5, 4}, {5, 8, 4}, {5, 8, 4}, {8, 5, 4}, {8, 5, 4}, {8, 5, 4},
};

/* Pending slot for each row of lbl_803074C8; 7 means none. */
static int lbl_803EA400[2] = {7, 7};
static unsigned char lbl_803EA408 = 1;
static unsigned char lbl_803EA409 = 0;

extern "C" {
void fn_8003AEA8(int a, int b, int c)
{
    fn_80080A68(&lbl_8030749C, (char *)a, b);
}

void fn_8003AED8(int kind, int index, int value)
{
    lbl_803075A8[kind][index] = value;
}

void fn_8003AEF4(int a, int kind, int index, int d, Pair_8003AEA8 *p0, Pair_8003AEA8 *p1, Pair_8003AEA8 *p2)
{
    fn_800B4A18(lbl_802CCCE4[lbl_803075A8[kind][index]][0], p0->mUnknown8, p0->mUnknown4);
    fn_800B4A18(lbl_802CCCE4[lbl_803075A8[kind][index]][1], p1->mUnknown8, p1->mUnknown4);
    fn_800B4A18(lbl_802CCCE4[lbl_803075A8[kind][index]][2], p2->mUnknown8, p2->mUnknown4);
}

void fn_8003AF8C(int a, int kind, int index, int key, int e, Pair_8003AEA8 *pPair, int *pValues, int *pResult)
{
    int handle;
    int *list;
    unsigned char i;

    if (kind == 1) {
        handle = fn_80085620(e, 1);
    } else {
        handle = fn_80085620(e, 0);
    }
    list = fn_80085744(handle, a);
    if (list != 0) {
        if (fn_800809C4(&lbl_8030749C, list[lbl_803075A8[kind][key]], 0) != 0) {
            fn_8003AEA8(pPair->mUnknown8, pPair->mUnknown4, 1);
            for (i = 0; i <= 2; i++) {
                pValues[i] = fn_800812E0(&lbl_8030749C, lbl_802CCCE4[lbl_803075A8[kind][index]][i]);
            }
            *pResult = fn_80080D10(&lbl_8030749C);
        }
    }
}

int fn_8003B0A0(int a, int kind, int index0, int index1)
{
    return fn_8008593C(kind == 1, a, lbl_803075A8[kind][index0], lbl_803075A8[kind][index1]);
}

void fn_8003B0F8(int group, int kind, int slot, int code, int a, int b)
{
    int step;
    int row;

    step = code == 1 ? 1 : (code == 3 ? -1 : 0);
    slot--;
    row = kind == 1;
    if (lbl_803EA400[group] == 7) {
        lbl_803EA400[group] = slot;
    }
    lbl_803EA400[group] = (lbl_803EA400[group] + step + 7) % 7;
    fn_800809C4(&lbl_8030749C, lbl_803074C8[group][lbl_802CCCAC[row][lbl_803EA400[group]]], 0);
    fn_8003AEA8(a, b, 1);
}

void fn_8003B1F4(int group)
{
    int i;

    for (i = 0; i < 14; i++) {
        lbl_803074C8[group][i] = lbl_80307538[group][i];
    }
    lbl_803EA400[group] = 7;
}

void fn_8003B234(int group, int kind, Pair_8003AEA8 **pPairs)
{
    int row = kind == 1;
    int i;

    for (i = 0; i < 7; i++) {
        fn_800809C4(&lbl_8030749C, lbl_803074C8[group][lbl_802CCCAC[row][i]], 0);
        fn_8003AEA8(pPairs[i]->mUnknown8, pPairs[i]->mUnknown4, 1);
    }
}

void fn_8003B2D0(int group, int kind, int slot)
{
    int current;
    int row;
    int from;
    int to;
    int temp;

    slot--;
    if (slot < 0 || slot > 6) {
        return;
    }
    current = lbl_803EA400[group];
    if (current == 7) {
        return;
    }
    row = kind == 1;
    if (slot != current) {
        from = lbl_802CCCAC[row][slot];
        to = lbl_802CCCAC[row][current];
        temp = lbl_803074C8[group][from];
        lbl_803074C8[group][from] = lbl_803074C8[group][to];
        lbl_803074C8[group][to] = temp;
    }
    lbl_803EA400[group] = 7;
}

int fn_8003B360(int group)
{
    int i;

    for (i = 0; i < 14; i++) {
        lbl_80307538[group][i] = lbl_803074C8[group][i];
    }
    return fn_80085BE4(group);
}

int fn_8003B3AC(int group)
{
    int i;

    for (i = 0; i < 14; i++) {
        lbl_803074C8[group][i] = lbl_80307538[group][i];
    }
    return fn_80085C3C(group);
}

void fn_8003B3F8(int group, int *list, int value)
{
    if (fn_801485D4()) {
        fn_80148A58()->vfn_10(value, list, lbl_80307538[group]);
    } else {
        fn_8003E8FC(value, list, lbl_80307538[group]);
    }
    fn_80085C94(group, lbl_80307538[group]);
    fn_80085BE4(group);
}

int fn_8003B4A4(int group, int *list, int value, int a, int b)
{
    if (fn_801485D4()) {
        fn_80148A58()->vfn_11(value, list, lbl_80307538[group], a, b);
    } else {
        fn_8003E8FC(value, list, lbl_80307538[group]);
    }
    fn_80085C94(group, lbl_80307538[group]);
    return fn_80085BE4(group);
}

unsigned char fn_8003B560(int group, int index, int *pValue)
{
    unsigned char loaded = lbl_803EA408;

    *pValue = lbl_80307538[group][index];
    return loaded;
}

void fn_8003B584(int group, int value, int index0, int index1)
{
    lbl_80307538[group][index0] = value;
    lbl_80307538[group][index1] = value;
}

int fn_8003B5AC(int group, int value, int *pFirst, int *pSecond)
{
    int found;
    unsigned char i;

    *pSecond = 0xFF;
    *pFirst = 0xFF;
    found = 0;
    for (i = 0; i < 7; i++) {
        if (lbl_80307538[group][i] == value) {
            *pFirst = i;
            break;
        }
    }
    for (i = 7; i < 14; i++) {
        if (lbl_80307538[group][i] == value) {
            *pSecond = i;
            break;
        }
    }
    if (*pFirst != 0xFF && *pSecond != 0xFF) {
        found = 1;
    }
    return found;
}

void fn_8003B688(int group, int *values)
{
    int i;

    for (i = 0; i < 14; i++) {
        lbl_80307538[group][i] = values[i];
    }
}

void fn_8003B6BC(int group, Record_8003B6BC *pRecord)
{
    int i;

    for (i = 0; i < 14; i++) {
        pRecord->mUnknown[i] = lbl_80307538[group][i];
    }
}

void fn_8003B6F0(int reset)
{
    lbl_803EA409 = 1;
    if (fn_80027DF0()) {
        Desc_8008044C desc;
        int *p;

        desc.mUnknown0 = 1;
        fn_8008044C(&lbl_8030749C, &desc, 0x54415453);
        lbl_803EA408 = 1;
        if (reset) {
            fn_80085D54();
            p = lbl_803EA400;
            do {
                *p = 7;
                p++;
            } while (p <= &lbl_803EA400[1]);
            fn_801C1F94(lbl_803074C8, 0, sizeof(lbl_803074C8));
            fn_801C1F94(lbl_80307538, 0, sizeof(lbl_80307538));
        }
    } else {
        fn_8008040C(&lbl_8030749C, 0);
        if (lbl_803EA408) {
            Object_8008044C cursor;
            Desc_8008044C desc;
            int ids[2];
            unsigned char group;
            int i;

            ids[0] = fn_80187C8C();
            ids[1] = fn_80187C6C();
            for (group = 0; group <= 1; group++) {
                desc.mUnknown0 = 1;
                desc.mUnknown4 = 1;
                desc.mUnknown8 = ids[group];
                fn_8008040C(&cursor, &desc);
                for (i = 0; i < 14; i++) {
                    fn_800809FC(&cursor, lbl_80307538[group][i], 0);
                    lbl_803074C8[group][i] = lbl_80307538[group][i] = fn_800808F8(&cursor);
                }
                fn_8008056C(&cursor);
            }
        }
        lbl_803EA408 = 0;
        fn_80085BE4(0);
        fn_80085BE4(1);
    }
}

void fn_8003B8BC(void)
{
    lbl_803EA409 = 0;
    fn_8008056C(&lbl_8030749C);
    if (!fn_80027DF0()) {
        int ids[2];
        unsigned char group;
        int i;

        ids[0] = fn_80187C8C();
        ids[1] = fn_80187C6C();
        for (group = 0; group <= 1; group++) {
            for (i = 0; i <= 13; i++) {
                fn_8022D874(0x54484344, ids[group], lbl_80307538[group][i], i);
            }
        }
    }
}
}
