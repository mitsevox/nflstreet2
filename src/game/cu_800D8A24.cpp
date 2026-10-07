#include <string.h>
#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/Table_80089904.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802270D4.h"

struct State_800D8B84 {
    char mUnknown0[12];
    Object_801BBD5C *mpUnknown12;
    Object_801BBD5C *mpUnknown16;
    Object_801BBD5C *mpUnknown20;
    Object_801BBD5C *mpUnknown24;
    char mUnknown28[12];
    unsigned char mUnknown40[2];
    char mUnknown42[6];
    float mUnknown48;
    short mUnknown52;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    char mUnknown58[2];
    unsigned char mUnknown60;
    unsigned char mUnknown61;
};

extern "C" {
int fn_8009C56C(Table_80089904 *pTable, const unsigned char *pValues);
void fn_800ADBC0(Object_80039F5C *p, int a, int b, int c);
unsigned char fn_800C0464(void *p);
void fn_800DA7AC(Object_801BBD5C *pObject, float value);
float fn_800DAA68(int index, State_800D8B84 *pState, Object_801BBD5C *pObject, Record_800D81C8 *pRecords,
                  float value);
int fn_800DC080(Object_80039F5C *p);
void fn_801BBC3C(unsigned short a, unsigned short b, Table_80089904 *pTable);
Object_801BBD5C *fn_801BBD5C(unsigned short a, unsigned short b);
void fn_801BD758(Block_801BD6D4 *p, float value);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);

extern void *lbl_803EABA4;

int fn_800D0B90(Object_80039F5C *p);
int fn_800D0D1C(Object_80039F5C *p);
}

extern "C" void fn_800D8B84(Table_80089904 *pTable, State_800D8B84 *pState, Object_80039F5C *p)
{
    pState->mpUnknown24 = 0;
    pState->mpUnknown20 = 0;
    pState->mUnknown57 = 0;
    pState->mUnknown56 = 0;
    for (unsigned int i = 0; i < pTable->mCount; i++) {
        unsigned char type = pTable->mEntries[i].mpInfo->mValue;
        unsigned short key = pTable->mEntries[i].mUnknown2 & 0x7FFF;
        unsigned short id = pTable->mEntries[i].mUnknown0;
        switch (type) {
        case 1:
            pState->mpUnknown16 = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
            pState->mUnknown55 = id;
            break;
        case 3:
            pState->mpUnknown20 = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
            pState->mUnknown56 = id;
            break;
        case 2:
            pState->mpUnknown24 = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
            pState->mUnknown57 = id;
            break;
        }
    }
    if (pState->mpUnknown20 == 0) {
        pState->mpUnknown20 = pState->mpUnknown16;
        pState->mUnknown56 = pState->mUnknown55;
    }
    if (pState->mpUnknown24 == 0) {
        pState->mpUnknown24 = pState->mpUnknown16;
        pState->mUnknown57 = pState->mUnknown55;
    }
    pState->mpUnknown12 = pState->mpUnknown16;
    pState->mUnknown54 = pState->mUnknown55;
}

extern "C" void fn_800D8CB4(Table_80089904 *pTable, Object_80039F5C *p, int index, int swap)
{
    Info_80089904 *pInfo = pTable->mEntries[index].mpInfo;
    unsigned char a = pInfo->mType;
    unsigned char b = pInfo->mUnknown6;

    if (swap) {
        unsigned char t = a;
        a = b;
        b = t;
    }
    if (p->mIdBytes[3] == 1) {
        fn_800ADBC0(p, a, 8, 0);
        fn_800ADBC0(p, b, 8, 1);
    }
}

extern "C" void fn_800D8D34(Table_80089904 *pTable, State_800D8B84 *pState, Object_80039F5C *p, int swap)
{
    unsigned char values[4];

    memset(values, 255, sizeof(values));
    values[0] = pState->mUnknown61;
    int index = fn_8009C56C(pTable, values);
    unsigned short id = pTable->mEntries[index].mUnknown2 & 0x7FFF;
    fn_800D8CB4(pTable, p, index, swap);
    fn_801BBC3C(p->mpUnknown796->mUnknown2, id, pTable);
    fn_800D8B84(pTable, pState, p);
}

extern "C" void fn_800D8DD8(Table_80089904 *pTable, State_800D8B84 *pState, Object_80039F5C *p, int swap)
{
    unsigned char values[4];

    memset(values, 255, sizeof(values));
    values[0] = pState->mUnknown60;
    int index = fn_8009C56C(pTable, values);
    fn_801BBC3C(p->mpUnknown796->mUnknown2, pTable->mEntries[index].mUnknown2 & 0x7FFF, pTable);
    fn_800D8D34(pTable, pState, p, swap);
}

extern "C" int fn_800D8E68(Object_80039F5C *p, State_800D8B84 *pState, unsigned char *pKind)
{
    unsigned char id = 0;
    int changed = 0;
    Object_801BBD5C *pObject = 0;
    float t = p->mMotion.mUnknown28;

    if (t == 0.0f) {
        pObject = pState->mpUnknown16;
        id = pState->mUnknown55;
        *pKind = 6;
    } else if (p->mMotion.mUnknown52 < 0.0f) {
        Object_801BBD5C *pCandidate = pState->mpUnknown20;
        if (t >= pCandidate->mUnknown12 && t <= pCandidate->mUnknown16) {
            pObject = pCandidate;
            id = pState->mUnknown56;
            *pKind = 6;
        }
    } else if (p->mMotion.mUnknown52 == 0.0f && p->mUnknown528.mUnknown14 == 10) {
        Object_801BBD5C *pCandidate = pState->mpUnknown24;
        if (t >= pCandidate->mUnknown12 && t <= pCandidate->mUnknown16) {
            pObject = pCandidate;
            id = pState->mUnknown57;
            *pKind = 6;
        }
    } else if (p->mUnknown492 > p->mUnknown488) {
        pObject = pState->mpUnknown16;
        id = pState->mUnknown55;
        *pKind = 6;
    } else if (p->mMotion.mUnknown28 > p->mUnknown492) {
        pObject = pState->mpUnknown16;
        id = pState->mUnknown55;
        *pKind = 8;
    }
    if (pObject && pObject != pState->mpUnknown12) {
        if (pState->mpUnknown12 == pState->mpUnknown24) {
            *pKind += *pKind;
        }
        pState->mpUnknown12 = pObject;
        pState->mUnknown54 = id;
        changed = 1;
    }
    return changed;
}

extern "C" void fn_800D8F8C(Object_80039F5C *p, Object_801BBD5C *pObject)
{
    float value = p->mMotion.mUnknown28;

    if (value != 0.0f && fn_801CFFD0(p->mMotion.mFacing, p->mMotion.mUnknown32) > 0x3C71C7) {
        value = -value;
    }
    fn_800DA7AC(pObject, value);
}

extern "C" void fn_800D8FFC(State_800D8B84 *pState, Object_801BBD5C *pObject, Record_800D81C8 *pRecords,
                            float value)
{
    pState->mUnknown48 = fn_800DAA68(pState->mUnknown52, pState, pObject, pRecords, value);
    for (unsigned char i = 0; i <= 1; i++) {
        unsigned char index = pState->mUnknown40[i];
        if (index != 255) {
            fn_801BD758(&pRecords[index].mUnknown4C, pState->mUnknown48);
        }
    }
}

extern "C" int fn_800D9078(Object_80039F5C *p, int a)
{
    int result = 0;

    if (p->mUnknown1052 != 0) {
        switch (p->mUnknown1032) {
        case 4:
        case 7:
            result = 1;
            break;
        case 1:
        case 2:
        case 3:
            if (a == 0 && p->mUnknown1052 != 1) {
                Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
                if (pOther) {
                    Pair_802270A4 delta;
                    fn_80227690(&delta, &pOther->mMotion, &p->mMotion);
                    if (fn_801CFFD0(fn_801CFE40(delta.mUnknown4, delta.mUnknown0), p->mMotion.mFacing) <= 0x1FFFFF
                        && fn_802270A4(&delta) < 4.5f) {
                        result = 1;
                    }
                }
            }
            break;
        }
    }
    if (p->mUnknown1052 == 3 && !result && p->mMotion.mUnknown28 < 1e-7f) {
        result = 1;
    }
    return result;
}

extern "C" int fn_800D9188(void)
{
    int mode = fn_800AD9B4();

    if (mode == 3 || (mode == 2 && fn_800C0464(lbl_803EABA4))) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800D91D8(void)
{
    return 0;
}

extern "C" int fn_800D91E0(Object_80039F5C *p, int team, int a, unsigned char *pOut)
{
    int result;

    if (p->mIdBytes[3] != 1) {
        result = 2;
    } else {
    unsigned char kind = p->mUnknown528.mUnknown15;
    if (kind <= 1 || kind == 4 || kind == 5 || kind == 29 || kind == 20 || kind == 21) {
        if (p->mIdBytes[2] == team) {
            *pOut = fn_800D9078(p, a);
            if (*pOut) {
                *pOut = 1;
                result = 7;
            } else if (p->mpState->mId == 18 || fn_800DC080(p)) {
                *pOut = 0;
                result = 3;
            } else {
                switch (p->mUnknown2921) {
                case 10: result = 10; break;
                case 8: result = 12; break;
                case 1: result = 18; break;
                case 2: result = 19; break;
                case 3: result = 20; break;
                case 9: result = 11; break;
                case 4: result = 14; break;
                case 5: result = 15; break;
                case 6: result = 16; break;
                case 7: result = 17; break;
                case 0:
            default: result = 13; break;
                }
            }
            if ((unsigned char)(p->mUnknown528.mUnknown15 - 20) <= 1 && fn_800D0B90(p) == 2 && !fn_800D0D1C(p)) {
                result = 1;
            }
        } else if (p->mUnknown1032 == 4) {
            result = 8;
        } else {
            switch (p->mUnknown2921) {
            case 10: result = 10; break;
            case 8: result = 12; break;
            case 1: result = 18; break;
            case 2: result = 19; break;
            case 3: result = 20; break;
            case 9: result = 11; break;
            case 4: result = 14; break;
            case 5: result = 15; break;
            case 6: result = 16; break;
            case 7: result = 17; break;
            case 0:
            default: result = 13; break;
            }
        }
    } else {
        result = 1;
    }
    }
    return result;
}
