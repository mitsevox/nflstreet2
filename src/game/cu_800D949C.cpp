#include "game/Object_800DA8D8.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/Block_801BE60C.h"
#include "game/Record_8036B55C.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/Object_8017886C.h"
#include <math.h>

extern "C" {
extern unsigned char lbl_802DA888[];

struct Key_800DA6AC { unsigned short mUnknown0; unsigned short mUnknown2; };
extern Key_800DA6AC lbl_802DA8AC[4];
int fn_801486A0(void);
int fn_801481B0(void);
int fn_801787A0(void);
int fn_800D0B90(Object_80039F5C *p);
unsigned char fn_800D0B98(Object_80039F5C *p);
int fn_800D9188(void);
int fn_800D91D8(void);
int fn_800DC080(Object_80039F5C *p);
int fn_800D9078(Object_80039F5C *p, int flag);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
Point_8017886C fn_80177FFC(int team);
void fn_8009BEFC(Object_80039F5C *p, int joint, Vector_80039F5C *out, int *scratch);
int fn_801C4E98(void *p, const char *name);
int fn_800D8F8C(Object_80039F5C *p, Object_801BBD5C *object);
int fn_800D8E68(Object_80039F5C *p, Block_801BE60C *block, unsigned char *value);
void fn_800D8FFC(Block_801BE60C *block, Object_800DA8D8 *object, Record_800D81C8 *entries, float value);
int fn_800D78C4(Object_80039F5C *p, int key);
void fn_800ADBC0(Object_80039F5C *p, int a, int b, int c);
int fn_8009C4B0(Table_80089904 *table, Key_80110630 *key);
unsigned int fn_801BA568(void *record, Record_800D81C8 *entries, unsigned short key);
unsigned int fn_801BA5A8(void *record, Record_800D81C8 *entries, unsigned short key, unsigned short index);
int fn_801BA2A8(void *record, Record_800D81C8 *entries, unsigned short value, int animation, int key, Object_80039F5C *p, float weight);
int fn_801BA6B0(Record_800D81C8 *entry);
void fn_801BA6BC(Record_800D81C8 *entry, int value);
void fn_801BA650(Record_800D81C8 *entry, Object_80039F5C *p, float value);
float fn_801BD60C(void *p);
float fn_801CFFA0(float value);
void fn_801BD81C(void *p, float value);
void fn_800DA6AC(Record_8036B55C *record, Record_800D81C8 *entries, Object_80039F5C *p);
void fn_800DA814(Object_800DA8D8 *object, Block_801BE60C *block, Object_80039F5C *p, int value, int index, int key, Record_8036B55C *record, Record_800D81C8 *entries);
void fn_800DA8D8(Object_800DA8D8 *, Block_801BE60C *, Object_80039F5C *, int, int, unsigned short, void *, Record_800D81C8 *, unsigned char);
void fn_800DAC78(Block_801BE60C *, float, float);
void fn_800DAC88(Block_801BE60C *, void *, Record_800D81C8 *);
int fn_800D9B0C(Object_80039F5C *, int, int);

int fn_800D9A10(void *, Block_801BE60C *, Object_80039F5C *, Object_80039F5C *, int);
int fn_800D9C40(Object_80039F5C *);

extern float lbl_803EA2C4;

int fn_80178308(void);
int fn_800D91E0(Object_80039F5C *p, int team, int flag, unsigned char *pValue);
int fn_800D949C(Object_80039F5C *p, Object_80039F5C *pOther, int team, int flag, unsigned char value);
void fn_800D8DD8(void *a, Block_801BE60C *pBlock, Object_80039F5C *p, int value);
int fn_801BA2D0(void *a, Record_800D81C8 *pEntries, Record_800D81C8 *pEntry);
void fn_801BA384(void *a, Record_800D81C8 *pEntries, int index);
void fn_801BA418(void *a, Record_800D81C8 *pEntries, unsigned char index, unsigned short b,
                 int c, unsigned short d, Object_80039F5C *pRecord);
void fn_801BD758(Block_801BD6D4 *p, float value);
void fn_801BF3C8(Block_801BF3C8 *p, int a, int b, float x, float y);
void fn_801BF4A8(Block_801BF3C8 *p, int a, float x, float y);

int fn_800D949C(Object_80039F5C *p, Object_80039F5C *pOther, int team, int flag, unsigned char value)
{
    int result = value;
    if (p->mIdBytes[3] != 1) {
        result = 2;
        goto finish;
    }
    if (pOther == p || (fn_801486A0() == 1 && fn_80137C48(p))) {
        switch (p->mUnknown528.mUnknown15) {
        case 10: case 11: result = 34; goto finish;
        case 20: case 21:
            if (fn_800D0B90(p) == 2) result = lbl_802DA888[(unsigned char)fn_800D0B98(p)];
            else result = 1;
            goto finish;
        case 6: case 7: result = 11; goto finish;
        case 8: case 9: result = 12; goto finish;
        case 29: result = 1; goto finish;
        case 13: result = 17; goto finish;
        case 14: result = 16; goto finish;
        case 26: result = 37; goto finish;
        case 27: result = 41; goto finish;
        case 22: case 23: result = 33; goto finish;
        case 3: result = 40; goto finish;
        case 2: result = 42; goto finish;
        }
        result = fn_800D9188() ? 19 : 1;
        if (fn_800D91D8()) result = 38;
        if (p->mUnknown2914 != 0 && p->mUnknown2914 != 20 &&
            p->mUnknown2914 != 1 && p->mUnknown2914 != 3) goto finish;
        if (fn_800DC080(p)) {
            int direction = fn_801CFE40(p->mMotion.mUnknown44, p->mMotion.mUnknown40) & 0xFFFFFF;
            Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, 74);
            if (p->mUnknown2913 == 0) {
                int angle = block->mUnknown3D == 9 ? 95 : 85;
                result = 6;
                if (fn_801CFFD0(direction, 0) < (int)(angle * 46603.37890625f)) result = 9;
            } else {
                int angle = block->mUnknown3D == 9 ? 85 : 95;
                result = 9;
                if (fn_801CFFD0(direction, 0) < (int)(angle * 46603.37890625f)) result = 6;
                if (!(p->mMotion.mUnknown28 > 0.0000001f)) result = 9;
            }
        } else if (fn_801481B0() || !(p->mFlags & 0x400)) {
            result = p->mUnknown2913 ? 22 : 23;
        }
        goto finish;
    }
    if (p->mUnknown1052 && (result == 1 || (result == 2 && fn_800D9078(p, flag)))) {
        switch (p->mUnknown1032) {
        case 2: case 3: result = 4; break;
        case 4: case 7: result = 5; break;
        default: result = 3; break;
        }
        goto finish;
    }
    switch (p->mUnknown528.mUnknown15) {
    case 15: result = 24; break;
    case 16: result = 25; break;
    case 12: result = 14; break;
    case 18: result = 26; break;
    case 19: result = 27; break;
    case 24: case 25: result = 36; break;
    case 30: result = 77; break;
    default: result = fn_800D9188() ? 20 : 2; break;
    }
    if (p->mUnknown528.mUnknown14 == 9) result = fn_800D9188() ? 20 : 2;
    if (p->mpState->mId == 42 && fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0x2AAAA9) {
        Point_8017886C point = fn_80177FFC(p->mIdBytes[2]);
        if (!(p->mMotion.mPos.mY - point.mY >= 6.0f)) {
            result = 15;
            if (!(fabsf(p->mMotion.mPos.mX - point.mX) >= 9.0f)) result = 13;
        }
    }
finish:
    if (fn_801787A0()) {
        if (result == 1) result = 43;
        else if (result == 2) result = 18;
    }
    return result;
}


int fn_800D9A10(void *a, Block_801BE60C *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, int value)
{
    int changed = 0;
    int first;
    int second;

    if (p->mIdBytes[3] == 1) {
        int team = fn_80178308();
        int flag = 1;
        if (fn_800AD9B4() == 3) {
            flag = 0;
        }
        unsigned char result = 2;
        first = fn_800D91E0(p, team, flag, &result);
        second = fn_800D949C(p, pOther, team, flag, result);
    } else {
        first = 2;
        second = fn_80137C48(p) ? 1 : 2;
    }
    if (pBlock->mUnknown3C != first || pBlock->mUnknown3D != second) {
        pBlock->mUnknown3C = first;
        pBlock->mUnknown3D = second;
        fn_800D8DD8(a, pBlock, p, value);
        changed = 1;
    }
    return changed;
}

int fn_800D9B0C(Object_80039F5C *p, int check, int value)
{
    if (p->mIdBytes[3] == 1) {
        switch (p->mUnknown528.mUnknown15) {
        case 6:
        case 7:
        case 16:
        case 19:
            return 1;
        case 8:
        case 9:
        case 15:
        case 18:
            return 0;
        }
        switch (p->mUnknown512.mUnknown15) {
        case 6:
        case 7:
        case 16:
        case 19:
            return 1;
        case 8:
        case 9:
        case 15:
        case 18:
            return 0;
        }
        if (fn_80137C48(p) == 0) {
            if (check != 0 && fn_800AD9B4() != 2) {
                value = fn_802372EC(0, 100) < 50;
            }
        } else {
            value = p->mUnknown776 == 1;
        }
    } else {
        return 0;
    }
    return value;
}

int fn_800D9C40(Object_80039F5C *p)
{
    int result = 1;
    if (fn_801BE648(p->mpUnknown792) == 84) {
        result = 0;
    }
    return result;
}

int fn_800D9C80(Table_80089904 *table, unsigned short key, Record_8036B55C *record,
                 Record_800D81C8 *entries, Object_80039F5C *p, int phase)
{
    unsigned char value = 0;
    unsigned char frames = 8;
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        int mode = fn_800D9B0C(p, 1, 0);
        Object_80039F5C *other = fn_80137B40();
        int team = fn_80178308();
        int flag = fn_800AD9B4() == 3 ? 0 : 1;
        block->mUnknown3C = fn_800D91E0(p, team, flag, &value);
        block->mUnknown3D = fn_800D949C(p, other, team, flag, value);
        fn_800D8DD8(table, block, p, mode);
        block->mUnknown4 = 1.0f;
        int index = fn_800D8F8C(p, block->mpUnknownC);
        block->mUnknown20.mUnknown14Half = index;
        fn_800DA814((Object_800DA8D8 *)block->mpUnknownC, block, p,
                   block->mUnknown20.mUnknown16, (signed char)index, key, record, entries);
        block->mUnknown20.mUnknown8Bytes[1] = 255;
        block->mUnknown20.mUnknown8Bytes[0] = 255;
        Vector_80039F5C left, right;
        int scratch[3];
        fn_8009BEFC(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "lankle"), &left, scratch);
        fn_8009BEFC(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "rankle"), &right, scratch);
        if (mode) {
            fn_801BA6BC(&entries[block->mUnknown0], 1);
            fn_801BA6BC(&entries[block->mUnknown1], 1);
            if (!(left.mZ >= right.mZ)) {
                Record_800D81C8 *entry = &entries[block->mUnknown0];
                float duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
                float scale;
                entry = &entries[block->mUnknown0];
                scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
                scale *= 0.6f;
                fn_801BA650(&entries[block->mUnknown0], p, duration * scale);
                entry = &entries[block->mUnknown1];
                duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
                entry = &entries[block->mUnknown1];
                scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
                scale *= 0.6f;
                fn_801BA650(&entries[block->mUnknown1], p, duration * scale);
            }
        } else if (!(right.mZ >= left.mZ)) {
            Record_800D81C8 *entry = &entries[block->mUnknown0];
            float duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
            float scale;
            entry = &entries[block->mUnknown0];
            scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
            scale *= 0.6f;
            fn_801BA650(&entries[block->mUnknown0], p, duration * scale);
            entry = &entries[block->mUnknown1];
            duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
            entry = &entries[block->mUnknown1];
            scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
            scale *= 0.6f;
            fn_801BA650(&entries[block->mUnknown1], p, duration * scale);
        }
        block->mUnknown20.mUnknownC = p->mMotion.mUnknown28;
        break;
    }
    case 2: {
        if (fn_801BE648(p->mpUnknown792) != key) return 0;
        Object_80039F5C *other = fn_80137B40();
        if ((signed char)block->mUnknown3A[1] <= 0) {
            int mode = fn_801BA6B0(&entries[block->mUnknown0]);
            unsigned char changed = fn_800D9A10(table, block, p, other, mode);
            changed |= fn_800D8E68(p, block, &frames);
            int index = fn_800D8F8C(p, block->mpUnknownC);
            if ((index != block->mUnknown20.mUnknown14Half || changed) && block->mUnknown20.mUnknown14Half != -1) {
                fn_800DA8D8((Object_800DA8D8 *)block->mpUnknownC, block, p,
                           block->mUnknown20.mUnknown16, (signed char)index, key, record, entries, frames);
                fn_801BA6BC(&entries[block->mUnknown0], mode);
                fn_801BA6BC(&entries[block->mUnknown1], mode);
                if (mode == 1) {
                    if (fn_800D9B0C(p, 0, 1) == 0) {
                        Record_800D81C8 *entry = &entries[block->mUnknown0];
                        float duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
                        float scale;
                        entry = &entries[block->mUnknown0];
                        scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
                        scale *= 0.5f;
                        fn_801BA650(&entries[block->mUnknown0], p, duration * scale);
                        entry = &entries[block->mUnknown1];
                        duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
                        entry = &entries[block->mUnknown1];
                        scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
                        scale *= 0.5f;
                        fn_801BA650(&entries[block->mUnknown1], p, duration * scale);
                        fn_801BA6BC(&entries[block->mUnknown0], 0);
                        fn_801BA6BC(&entries[block->mUnknown1], 0);
                    }
                } else if (fn_800D9B0C(p, 0, mode) == 1) {
                    Record_800D81C8 *entry = &entries[block->mUnknown0];
                    float duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
                    float scale;
                    entry = &entries[block->mUnknown0];
                    scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
                    scale *= 0.5f;
                    fn_801BA650(&entries[block->mUnknown0], p, duration * scale);
                    entry = &entries[block->mUnknown1];
                    duration = fn_801BD60C(entry->mUnknown4C.mpUnknown0);
                    entry = &entries[block->mUnknown1];
                    scale = entry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)entry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
                    scale *= 0.5f;
                    fn_801BA650(&entries[block->mUnknown1], p, duration * scale);
                    fn_801BA6BC(&entries[block->mUnknown0], 1);
                    fn_801BA6BC(&entries[block->mUnknown1], 1);
                }
                block->mUnknown20.mUnknown14Half = index;
                block->mUnknown3A[1] = frames;
                block->mUnknown3A[0] = frames;
            }
        } else if (p == other) {
            unsigned char state = p->mUnknown528.mUnknown15;
            if (state != 6 && state != 8 && state != 7 && state != 9 &&
                fn_800D78C4(p, key) != p->mUnknown776) p->mUnknown778 = -1;
        }
        block->mUnknown20.mUnknownC = p->mMotion.mUnknown28;
        if ((signed char)block->mUnknown3A[1] > 0) {
            signed char remaining = block->mUnknown3A[1] - 1;
            block->mUnknown3A[1] = remaining;
            fn_800DAC78(block, (float)(signed char)block->mUnknown3A[0], (float)remaining);
            fn_800DAC88(block, record, entries);
        } else {
            block->mUnknown3A[0] = 0;
            block->mUnknown4 = 1.0f;
        }
        break;
    }
    case 3:
        if (p->mIdBytes[3] == 1 && p->mpState->mId != 50 && fn_800D9C40(p)) {
            fn_800ADBC0(p, 1, 8, 0);
            fn_800ADBC0(p, 1, 8, 1);
        }
        return 0;
    default: return 0;
    }
    if (fn_801CFFD0(p->mMotion.mFacing, p->mMotion.mUnknown32) > 0x56C16C)
        fn_800D8FFC(block, (Object_800DA8D8 *)block->mpUnknownC, entries, -block->mUnknown20.mUnknownC);
    else fn_800D8FFC(block, (Object_800DA8D8 *)block->mpUnknownC, entries, block->mUnknown20.mUnknownC);
    return 0;
}

extern const unsigned int data_8029D848[7] = {
    0x43300000, 0x80000000, 0x3E800000, 0x3F000000,
    0x3F800000, 0x00000000, 0x3F800000
};

unsigned char fn_800DA53C(unsigned short index)
{
    return lbl_802DA888[index];
}

int fn_800DA54C(Table_80089904 *table, unsigned short key, Record_8036B55C *record,
                 Record_800D81C8 *entries, Object_80039F5C *p, int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        block->mUnknown1 = p->mUnknown1008.mUnknown0;
        block->mUnknown2 = p->mUnknown1008.mUnknown1;
        int index = fn_8009C4B0(table, &p->mUnknown1008);
        int entry = fn_801BA2A8(record, entries, table->mEntries[index].mUnknown0,
                                         table->mEntries[index].mUnknown2, key, p, 1.0f);
        block->mUnknown0 = entry;
        if (block->mUnknown2 == 2 && p->mUnknown528.mUnknown0 != 0.0f)
            fn_801BD81C(&entries[(unsigned char)entry].mUnknown4C, fn_801CFFA0(p->mUnknown528.mUnknown0));
        break;
    }
    case 2:
        if (block->mUnknown2 == 2 && p->mUnknown528.mUnknown0 != 0.0f) {
            p->mpUnknown800[block->mUnknown0].mUnknownC = p->mUnknown528.mUnknown8;
            fn_801BD81C(&entries[block->mUnknown0].mUnknown4C, fn_801CFFA0(p->mUnknown528.mUnknown0));
        }
        break;
    }
    return 0;
}

void fn_800DA6AC(Record_8036B55C *record, Record_800D81C8 *entries, Object_80039F5C *)
{
    for (unsigned int i = 0; i <= 3; i++) {
        unsigned int count = fn_801BA568(record, entries, lbl_802DA8AC[i].mUnknown2);
        while (count > 2) {
            unsigned int selected = 0xFFFF;
            float best = 1.0f;
            for (unsigned int j = 0; j < count; j++) {
                unsigned int index = fn_801BA5A8(record, entries, lbl_802DA8AC[i].mUnknown2, (unsigned short)j);
                float weight = entries[index].mUnknown30.mUnknown0;
                if (!(best <= weight)) {
                    best = weight;
                    selected = index;
                }
            }
            fn_801BA384(record, entries, selected);
            count--;
        }
    }
}

int fn_800DA7AC(Object_801BBD5C *pObject, float value)
{
    int index = 0;
    while (index < (int)(pObject->mCount - 2)) {
        float end = pObject->mValues[index + 1].mValue * lbl_803EA2C4;
        if (!(fabsf(end) >= 0.000001f)) end = 0.0f;
        if (!(end <= value)) break;
        index++;
    }
    return index;
}

void fn_800DA814(Object_800DA8D8 *object, Block_801BE60C *block, Object_80039F5C *p,
                 int value, int index, int key, Record_8036B55C *record,
                 Record_800D81C8 *entries)
{
    fn_800DA6AC(record, entries, p);
    int first = object->mUnknown24[index].mUnknown8;
    int second = object->mUnknown24[index + 1].mUnknown8;
    block->mUnknown0 = fn_801BA2A8(record, entries, (unsigned short)value, first, key, p, 1.0f);
    block->mUnknown1 = fn_801BA2A8(record, entries, (unsigned short)value, second, key, p, 1.0f);
    block->mUnknown3 = 255;
    block->mUnknown2 = 255;
}

void fn_800DA8D8(Object_800DA8D8 *pObject, Block_801BE60C *pBlock, Object_80039F5C *pRecord, int b,
                 int index, unsigned short d, void *a, Record_800D81C8 *pEntries, unsigned char flag)
{
    int first = fn_801BA2D0(a, pEntries, &pEntries[pBlock->mUnknown0]);
    int second = fn_801BA2D0(a, pEntries, &pEntries[pBlock->mUnknown1]);

    pBlock->mUnknown2 = pBlock->mUnknown0;
    pBlock->mUnknown3 = pBlock->mUnknown1;
    pBlock->mUnknown8 = pEntries[pBlock->mUnknown0].mUnknown30.mUnknown0;
    pBlock->mUnknown0 = first;
    pBlock->mUnknown1 = second;

    fn_801BA418(a, pEntries, pBlock->mUnknown0, b, pObject->mUnknown24[index].mUnknown8, d, pRecord);
    fn_801BF3C8(&pEntries[pBlock->mUnknown0].mUnknown30, 0, 0, 0.0f, 0.0f);
    fn_801BF4A8(&pEntries[pBlock->mUnknown0].mUnknown30, flag, -1.0f, 1.0f);
    fn_801BA418(a, pEntries, pBlock->mUnknown1, b, pObject->mUnknown24[index + 1].mUnknown8, d, pRecord);
    fn_801BF3C8(&pEntries[pBlock->mUnknown1].mUnknown30, 0, 0, 0.0f, 0.0f);
    fn_801BF4A8(&pEntries[pBlock->mUnknown1].mUnknown30, flag, -1.0f, 1.0f);
}

float fn_800DAA68(int index, Block_801BE60C *pBlock, Object_800DA8D8 *pObject, Record_800D81C8 *pEntries,
                  float value)
{
    float start = pObject->mUnknown24[index].mUnknown4 * lbl_803EA2C4;
    float ratio = (value - start) / (pObject->mUnknown24[index + 1].mUnknown4 * lbl_803EA2C4 - start);
    float t = ratio < 0.0f ? 0.0f : (ratio > 1.0f ? 1.0f : ratio);

    pObject->mUnknown24[index + 1].mUnknown0 = fabsf(pObject->mUnknown24[index + 1].mUnknown0);
    pObject->mUnknown24[index].mUnknown0 = fabsf(pObject->mUnknown24[index].mUnknown0);
    float result = (pObject->mUnknown24[index + 1].mUnknown0 - pObject->mUnknown24[index].mUnknown0) * t +
                   pObject->mUnknown24[index].mUnknown0;

    fn_801BD758(&pEntries[pBlock->mUnknown0].mUnknown4C, result);
    fn_801BD758(&pEntries[pBlock->mUnknown1].mUnknown4C, result);
    if (pBlock->mUnknown2 != 255) {
        fn_801BD758(&pEntries[pBlock->mUnknown2].mUnknown4C, result);
    }
    if (pBlock->mUnknown3 != 255) {
        fn_801BD758(&pEntries[pBlock->mUnknown3].mUnknown4C, result);
    }

    float first = 1.0f - t;
    first *= pBlock->mUnknown4;
    float second = t * pBlock->mUnknown4;
    float a = pEntries[pBlock->mUnknown0].mUnknown30.mUnknown0;
    float b = pEntries[pBlock->mUnknown1].mUnknown30.mUnknown0;
    if (a + b == 1.0f) {
        if (fabsf(a - first) > 0.33f || fabsf(b - second) > 0.33f) {
            first = (first - a) * 0.22f + a;
            second = b + (a - first);
        }
    }
    fn_801BF3C8(&pEntries[pBlock->mUnknown0].mUnknown30, 0, 0, first, first);
    fn_801BF3C8(&pEntries[pBlock->mUnknown1].mUnknown30, 0, 0, second, second);
    return result;
}

void fn_800DAC78(Block_801BE60C *p, float a, float b)
{
    p->mUnknown4 = (a - b) / a;
}

void fn_800DAC88(Block_801BE60C *pBlock, void *a, Record_800D81C8 *pEntries)
{
    float weight = 1.0f - pBlock->mUnknown4;

    if (pBlock->mUnknown2 != 255) {
        if (weight != 0.0f) {
            fn_801BF3C8(&pEntries[pBlock->mUnknown2].mUnknown30, 0, 0, weight * pBlock->mUnknown8,
                        weight * pBlock->mUnknown8);
        } else {
            fn_801BA384(a, pEntries, pBlock->mUnknown2);
            pBlock->mUnknown2 = 255;
        }
    }
    if (pBlock->mUnknown3 != 255) {
        if (weight != 0.0f) {
            fn_801BF3C8(&pEntries[pBlock->mUnknown3].mUnknown30, 0, 0, weight * (1.0f - pBlock->mUnknown8),
                        weight * (1.0f - pBlock->mUnknown8));
        } else {
            fn_801BA384(a, pEntries, pBlock->mUnknown3);
            pBlock->mUnknown3 = 255;
        }
    }
}

int fn_800DAD90(Table_80089904 *pTable, int value, int a, unsigned char b)
{
    float best = 0.0f;
    int result = 0xFFFF;

    for (unsigned short i = 0; i < pTable->mCount; i++) {
        Info_80089904 *pInfo = pTable->mEntries[i].mpInfo;
        if (pInfo->mValue == a && pInfo->mUnknown6 == 1 && value >= pInfo->mUnknown16 &&
            value <= pInfo->mUnknown20) {
            float weight = 0.5f;
            if (pInfo->mType == b) {
                weight += weight;
            }
            if (weight > best) {
                best = weight;
                result = i;
            }
        }
    }
    if (result == 0xFFFF) {
        result = 0;
    }
    return result;
}

int fn_800DAE4C(Object_80039F5C *p)
{
    Vector_80039F5C left, right;
    int scratch[3];
    fn_8009BEFC(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "lankle"), &left, scratch);
    fn_8009BEFC(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "rankle"), &right, scratch);
    int result = 1;
    if (!(left.mZ >= right.mZ)) result = 2;
    return result;
}

}
