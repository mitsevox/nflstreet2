#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/Block_801BE60C.h"
#include "game/Record_8036B55C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802372EC.h"
#include <math.h>

struct Entry_800DA8D8
{
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
};

struct Object_800DA8D8
{
    char mUnknown0[24];
    Entry_800DA8D8 mUnknown24[1];
};

extern "C" {
extern float lbl_803EA2C4;
extern unsigned char lbl_802DA888[];

int fn_80178308(void);
int fn_801BE648(void *p);
int fn_800D91E0(Object_80039F5C *p, int team, int flag, unsigned char *pValue);
int fn_800D949C(Object_80039F5C *p, Object_80039F5C *pOther, int team, int flag, unsigned char value);
void fn_800D8DD8(void *a, Block_801BE60C *pBlock, Object_80039F5C *p, int value);
int fn_801BA2D0(void *a, Record_800D81C8 *pEntries, Record_800D81C8 *pEntry);
void fn_801BA384(void *a, Record_800D81C8 *pEntries, int index);
void fn_801BA418(void *a, Record_800D81C8 *pEntries, unsigned char index, unsigned short b,
                 int c, unsigned short d, Record_8036B55C *pRecord);
void fn_801BD758(Block_801BD6D4 *p, float value);
void fn_801BF3C8(Block_801BF3C8 *p, int a, int b, float x, float y);
void fn_801BF4A8(Block_801BF3C8 *p, int a, float x, float y);

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

unsigned char fn_800DA53C(unsigned short index)
{
    return lbl_802DA888[index];
}

void fn_800DA8D8(Object_800DA8D8 *pObject, Block_801BE60C *pBlock, Record_8036B55C *pRecord, int b,
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
}
