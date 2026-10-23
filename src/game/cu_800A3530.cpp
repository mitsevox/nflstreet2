#include "game/Object_80039F5C.h"
#include "game/fn_8022781C.h"
#include "engine/Record_800D81C8.h"
#include "game/Table_80089904.h"
#include "game/Block_801BE60C.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801BA2A8.h"
#include "game/Object_8003DEC4.h"
#include "game/fn_800A3530.h"

extern "C" {
void fn_801BE3C0(void *p, unsigned short key, float from, int type, float to, void *pSource);
float fn_801BD660(void *pScript, int key);
float fn_801BD6D4(Block_801BD6D4 *p);
void fn_800425D4(Object_8003DEC4 *pObject);
void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index);
void fn_801BE420(void *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, void *pOwner, float step);
void fn_800A3D68(int value);
extern int lbl_803EC93C;
extern int lbl_803EC940;
void fn_8009BD60(Object_80039F5C *p);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
Object_80039F5C *fn_80137B40(void);
int fn_801CFFD0(int from, int to);
extern float lbl_802D7EA4[];
extern float lbl_802D7ED0[];
extern float lbl_803EAA04;
extern float lbl_803EAA08;
extern float lbl_803EAA0C;
}

extern "C" int fn_800A3530(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown804, key);
    switch (phase) {
    case 0:
        fn_801BE760(p->mpUnknown804, key, 1);
        if (p->mUnknown1012[0] < table->mCount) {
            int entry = fn_801BA2A8(record, entries, table->mEntries[p->mUnknown1012[0]].mUnknown0,
                                    table->mEntries[p->mUnknown1012[0]].mUnknown2, key, p, 1.0f);
            block->mUnknown0Word = entry;
            block->mUnknown4Unsigned =
                (unsigned int)fn_801BD660(p->mpUnknown812[entry].mUnknown4C.mpUnknown0, 0x8000);
            p->mpUnknown4->mUnknown20 |= 0x10;
        }
        block->mUnknown8Byte = p->mUnknown1012[2];
        break;
    case 1:
        if (block->mUnknown8Byte == 1 && fn_801BE648(p->mpUnknown804) == key) {
            Data1_801BF4A8 data;
            data.mUnknown4 = 1;
            data.mUnknown0 = 1.0f;
            fn_801BE3C0(p->mpUnknown804, key, 1.0f, 1, 0.0f, &data);
            fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, 2, 1.0f, p);
        }
        break;
    case 2:
        if (block->mUnknown8Byte == 1 && fn_801BE648(p->mpUnknown804) == key
            && (unsigned int)((float)block->mUnknown4Unsigned
                              - fn_801BD6D4(&p->mpUnknown812[block->mUnknown0Word].mUnknown4C)) <= 7) {
            Data1_801BF4A8 data;
            data.mUnknown4 = 8;
            data.mUnknown0 = 1.0f;
            fn_801BE3C0(p->mpUnknown804, key, 1.0f, 1, 0.0f, &data);
            fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, 2, 1.0f, p);
        }
        break;
    case 3:
        if (block->mUnknown8Byte == 1) {
            fn_800A3D68(0);
            if (!fn_800A3B10(p))
                fn_800425D4((Object_8003DEC4 *)p->mpUnknown4);
        }
        break;
    }
    return 0;
}

extern "C" int fn_800A37D8(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    switch (phase) {
    case 0:
        fn_801BA2A8(record, entries, lbl_803EC93C, lbl_803EC940, key, p, 1.0f);
        p->mpUnknown4->mUnknown20 |= 0x10;
        break;
    case 1:
        if (!fn_800A3B10(p))
            fn_800425D4((Object_8003DEC4 *)p->mpUnknown4);
        break;
    case 2:
        break;
    case 3:
        if (!fn_800A3B10(p))
            fn_800425D4((Object_8003DEC4 *)p->mpUnknown4);
        break;
    }
    return 0;
}

extern "C" int fn_800A3898(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown804, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown804, key, 1);
        int index = (signed char)p->mUnknown1012[0];
        int entry = fn_801BA2A8(record, entries, table->mEntries[index].mUnknown0,
                                table->mEntries[index].mUnknown2, key, p, 1.0f);
        block->mUnknown0Word = entry;
        block->mUnknown4Unsigned =
            (unsigned int)fn_801BD660(p->mpUnknown812[entry].mUnknown4C.mpUnknown0, 0x8000);
        p->mpUnknown4->mUnknown20 |= 0x10;
        p->mpUnknown4->mUnknown20 &= ~0x40000;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown804) == key) {
            p->mpUnknown4->mUnknown20 |= 0x40000;
            if (block->mUnknown4Unsigned
                    - (unsigned int)fn_801BD6D4(&p->mpUnknown812[block->mUnknown0Word].mUnknown4C) <= 7) {
            Data1_801BF4A8 data;
                data.mUnknown4 = 8;
                data.mUnknown0 = 1.0f;
                fn_801BE3C0(p->mpUnknown804, key, 1.0f, 1, 0.0f, &data);
                fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, 2, 1.0f, p);
            }
        }
        break;
    case 1:
        if (fn_801BE648(p->mpUnknown804) == key) {
            Data1_801BF4A8 data;
            data.mUnknown4 = 1;
            data.mUnknown0 = 1.0f;
            fn_801BE3C0(p->mpUnknown804, key, 1.0f, 1, 0.0f, &data);
            fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, 2, 1.0f, p);
        }
        break;
    case 3:
        if (fn_801BE648(p->mpUnknown804) == key && !fn_800A3B10(p))
            fn_800425D4((Object_8003DEC4 *)p->mpUnknown4);
        break;
    }
    return 0;
}

extern "C" void Stripped_8029674C(Object_80039F5C *p, unsigned char index, unsigned short key)
{
    p->mUnknown1012[0] = index;
    p->mUnknown1012[1] = 0;
    p->mUnknown1012[2] = 0;
    fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, key, 1.0f, p);
}

extern "C" void fn_800A3B5C(Object_80039F5C *p)
{
    if (p->mpUnknown808 != 0) {
        for (int i = 0; i < p->mpUnknown808->mUnknown4; i++) {
            if (p->mpUnknown812[i].mUnknown1 == 2)
                fn_801BA384(p->mpUnknown808, p->mpUnknown812, i);
        }
        fn_801BE420(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, p, 1.0f);
        fn_801BE420(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, p, 1.0f);
    }
    fn_800425D4((Object_8003DEC4 *)p->mpUnknown4);
}

struct Keys_800A3C14;

extern "C" {
extern void *lbl_803EC938;
extern Keys_800A3C14 *lbl_803EC944;
}

struct Record_80296754 {
    short mUnknown0;
    char pad2[6];
    float mUnknown8;
    unsigned char mUnknownC;
    char padD[0x1F];
    Keys_800A3C14 *mpKeys2C;
    char pad30[4];
    float mUnknown34;
    unsigned char mUnknown38;
    char pad39[0x1F];
    void *mpUnknown58;
};

extern Record_80296754 gStripped_80296754Record;

extern "C" Record_80296754 *Stripped_80296754(const unsigned char *pData)
{
    gStripped_80296754Record.mpKeys2C = lbl_803EC944;
    gStripped_80296754Record.mUnknownC = 0;
    gStripped_80296754Record.mUnknown38 = 0;
    gStripped_80296754Record.mUnknown0 = 2;
    gStripped_80296754Record.mUnknown8 = 1.0f;
    gStripped_80296754Record.mpUnknown58 = lbl_803EC938;
    gStripped_80296754Record.mUnknown34 = (8 - pData[3]) * 0.125f;
    return &gStripped_80296754Record;
}

extern "C" int fn_800A3E84(Object_80039F5C *p, int angle, int unused)
{
    float distance = 0.0f;
    int result = 0;

    Target_800A3E84 *pTarget = &p->mTarget;
    if (!(p->mFlags & 0x4000)) {
        Object_80039F5C *pOther = fn_8009BCE8(&pTarget->mRef);
        if (pOther)
            distance = fn_8022781C(&p->mMotion, &pOther->mMotion);
        if (pTarget->mMode == 2 && (p->mpState->mId == 30 || p->mpState->mId == 2))
            angle = 0x400000;
        int turn = fn_801CFFD0(p->mMotion.mFacing, angle);
        if (distance > 0.5f && (float)pTarget->mValue > lbl_802D7ED0[pTarget->mMode]
            && turn > 0x1C71C7) {
            fn_8009BD60(p);
            unsigned char style = 6;
            if (((p->mMotion.mFacing + turn) & 0xFFFFFF) == (angle & 0xFFFFFF))
                style = 3;
            unsigned char speed = 3;
            if (!((float)pTarget->mValue >= lbl_802D7EA4[pTarget->mMode]))
                speed = 1;
            p->mUnknown1008.mUnknown0 = style;
            p->mUnknown1008.mUnknown1 = speed;
            p->mUnknown1008.mUnknown2 = angle >> 17;
            if (fn_801CFFD0(p->mMotion.mFacing, (p->mUnknown1008.mUnknown2 << 17) & 0xFFFFFF) > 0x1C71C7) {
                p->mTarget.mUnknown10 = 1;
                if (distance > lbl_803EAA04 && distance < lbl_803EAA08
                    && turn < (int)(lbl_803EAA0C * 46603.38f)
                    && (pTarget->mMode == 4 || pTarget->mMode == 5))
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 185, 1.0f, p);
                else if (pTarget->mMode == 2 && fn_80137B40() != 0
                         && fn_8022781C(&p->mMotion, &fn_80137B40()->mMotion) < 6.0f
                         && (p->mpState->mId == 2 || p->mpState->mId == 30))
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 185, 1.0f, p);
                else
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 155, 1.0f, p);
                result = 1;
                fn_800A3B58(p, 10, 0);
                p->mUnknown512.mUnknown14 = 0;
            } else {
                result = 0;
            }
        }
    }
    return result;
}

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_80110C10(Object_80039F5C *p);
signed char fn_8009C4B0(Table_80089904 *pTable, const unsigned char *pValues);
extern float lbl_803EAA10;
}

extern "C" unsigned short fn_800A414C(Table_80089904 *table, Object_80039F5C *p, Block_801BE60C *block)
{
    Target_800A3E84 *pTarget = &p->mTarget;
    Object_80039F5C *pOther = fn_8009BCE8(&pTarget->mRef);
    if (pTarget->mMode == 2)
        p->mUnknown1008.mUnknown0 = 2;
    else
        p->mUnknown1008.mUnknown0 = 1;
    Pair_802270A4 delta;
    fn_80227690(&delta, &pOther->mMotion, &p->mMotion);
    int heading = fn_801CFE40(delta.mUnknown4, delta.mUnknown0) & 0xFFFFFF;
    int facing = p->mMotion.mUnknown32 & 0xFFFFFF;
    if (fn_801CFFD0(heading, facing) <= (int)(lbl_803EAA10 * 46603.38f)) {
        p->mUnknown1008.mUnknown1 = 1;
        switch (pTarget->mMode) {
        case 5:
            if (fn_801CFB94(fn_80110C10(pOther)) < 0.0f)
                p->mUnknown1008.mUnknown2 = 3;
            else
                p->mUnknown1008.mUnknown2 = 6;
            break;
        case 4:
            p->mUnknown1008.mUnknown2 = pOther->mUnknown1008.mUnknown1;
            break;
        }
    } else {
        p->mUnknown1008.mUnknown1 = ((facing - heading) & 0xFFFFFF) <= 0x7FFFFF ? 7 : 2;
    }
    p->mUnknown1011 = pTarget->mValue;
    return fn_8009C4B0(table, (const unsigned char *)&p->mUnknown1008);
}
