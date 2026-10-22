#include <math.h>
#include "game/fn_800670B4.h"
#include "game/fn_801C1F94.h"
#include "game/Object_8016B04C.h"
#include "game/Object_8017886C.h"

extern "C" {
extern Object_8016B04C *lbl_803EB40C;
extern float lbl_802E9970[3];
extern float lbl_802E99AC[3];
extern float lbl_802E99B8[3];

int fn_800BA6F8(void);
int fn_8011F1CC(void);
Object_800670B4 *fn_80168708(int team);
Point_8017886C fn_80177FE0(void);
int fn_80178308(void);
int fn_8022DDB4(int tag, void *data);
int fn_80169F80(int value);
void fn_80169FCC(int team, unsigned char *pOut, unsigned int *pFlags);
unsigned int fn_8016AD80(int kind, Point_8017886C from, Point_8017886C *pTo, int flag);
void fn_8016B438(int team, unsigned char *pOut, unsigned int *pFlags);
unsigned char fn_8016B7C4(Point_8017886C *pTo);
void fn_8016B82C(int team, Record_80067338 *pRecord, unsigned char *pOut, unsigned int *pFlags);
float fn_8016B8C8(int team, int value);
float fn_8016B938(void);
float fn_8016B974(void);
float GetTrackerFloat8(void);
float fn_8016B9B0(void);
float fn_8016B9EC(void);
void SumKind1WeightsBit28(int team, float *pBit29, float *pBit28);
void SumKind1WeightsBit30(int team, float *pSet, float *pClear);
void fn_8016BA28(unsigned char *pOut);
void fn_8016BA80(void);
void fn_8016BAAC(void);
}

void fn_8016B438(int team, unsigned char *pOut, unsigned int *pFlags)
{
    float kind2Gain = 0.0f;
    float kind2 = 0.0f;
    float kind1Gain = 0.0f;
    float kind1 = 0.0f;
    float kind1Flag4 = 0.0f;
    float kind1Flag8 = 0.0f;
    float kind1Flag2 = 0.0f;
    float kind2Flag100 = 0.0f;
    float kind2Flag200 = 0.0f;
    float kind2Flag80 = 0.0f;
    float kind2Flag40 = 0.0f;
    float kind2Flag20 = 0.0f;
    float kind2Flag10 = 0.0f;
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];

    *pOut = 0;
    *pFlags = 0;
    if (count <= 8)
        return;

    for (unsigned char i = 0; i < count; i++) {
        unsigned int flags = pEntries[i].mUnknown8;
        float gain;

        switch (pEntries[i].mUnknownE) {
        case 1:
        case 3:
        case 4:
            gain = 0.0f;
            break;
        default:
            gain = pEntries[i].mUnknownD;
            break;
        }

        if (pEntries[i].mUnknownF == 1) {
            kind1 += 1.0f;
            if (gain > 4.9f) {
                kind1Gain += 1.0f;
                if (flags & 2)
                    kind1Flag2 += 1.0f;
                if (flags & 4)
                    kind1Flag4 += 1.0f;
                if (flags & 8)
                    kind1Flag8 += 1.0f;
            }
        } else {
            kind2 += 1.0f;
            if (gain > 9.0f) {
                kind2Gain += 1.0f;
                if (flags & 0x80)
                    kind2Flag80 += 1.0f;
                if (flags & 0x100)
                    kind2Flag100 += 1.0f;
                if (flags & 0x200)
                    kind2Flag200 += 1.0f;
                if (flags & 0x10)
                    kind2Flag10 += 1.0f;
                if (flags & 0x20)
                    kind2Flag20 += 1.0f;
                if (flags & 0x40)
                    kind2Flag40 += 1.0f;
            }
        }
    }

    if (kind1 <= 7.0f || kind2 <= 7.0f)
        return;

    float kind1Rate = kind1Gain / kind1;
    float kind2Rate = kind2Gain / kind2;
    if (fabsf(kind1Rate - kind2Rate) > 0.35f)
        *pOut = kind1Rate > kind2Rate ? 1 : 2;

    if (kind1Gain != 0.0f) {
        if (kind1Flag2 / kind1Gain > 0.4f)
            *pFlags |= 2;
        else if (kind1Flag8 / kind1Gain > 0.4f)
            *pFlags |= 8;
        else if (kind1Flag4 / kind1Gain > 0.4f)
            *pFlags |= 4;
    }

    if (kind2Gain != 0.0f) {
        if (kind2Flag10 / kind2Gain > 0.4f)
            *pFlags |= 0x10;
        else if (kind2Flag20 / kind2Gain > 0.4f)
            *pFlags |= 0x20;
        else if (kind2Flag40 / kind2Gain > 0.4f)
            *pFlags |= 0x40;

        if (kind2Flag80 / kind2Gain > 0.4f)
            *pFlags |= 0x80;
        else if (kind2Flag200 / kind2Gain > 0.4f)
            *pFlags |= 0x200;
        else if (kind2Flag100 / kind2Gain > 0.4f)
            *pFlags |= 0x100;
    }
}

unsigned char fn_8016B7C4(Point_8017886C *pTo)
{
    int kind = 1;

    if (fn_8011F1CC())
        kind = 2;
    return fn_8016AD80(kind, fn_80177FE0(), pTo, 1) & lbl_803EB40C->mUnknown14;
}

void fn_8016B82C(int team, Record_80067338 *pRecord, unsigned char *pOut, unsigned int *pFlags)
{
    *pFlags = pRecord->mUnknown18 & 0x3FE;
    if (fn_80168708(team)->mUnknown8.mUnknownF != 0) {
        if (*pFlags & 8)
            *pFlags = (*pFlags & ~8) | 2;
        else if (*pFlags & 2)
            *pFlags = (*pFlags & ~2) | 8;
        if (*pFlags & 0x80)
            *pFlags = (*pFlags & ~0x80) | 0x200;
    }
    *pOut = fn_80169F80(pRecord->mUnknown17);
}

float fn_8016B8C8(int team, int value)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float result = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (value == pEntries[i].mUnknown0)
            result += lbl_802E9970[i / 8];
    }
    return result;
}

float fn_8016B938(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown0;
}

float fn_8016B974(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown4;
}

float GetTrackerFloat8(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown8;
}

float fn_8016B9B0(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknownC;
}

float fn_8016B9EC(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown10;
}

void SumKind1WeightsBit28(int team, float *pBit29, float *pBit28)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    unsigned short kind1Count = 0;

    *pBit29 = 0.0f;
    *pBit28 = 0.0f;
    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownF == 1) {
            kind1Count++;
            if (pEntries[i].mUnknown8 & 0x10000000)
                *pBit28 += lbl_802E99AC[kind1Count / 8];
            else if (pEntries[i].mUnknown8 & 0x20000000)
                *pBit29 += lbl_802E99AC[kind1Count / 8];
        }
    }
}

void SumKind1WeightsBit30(int team, float *pSet, float *pClear)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    unsigned short kind1Count = 0;

    *pSet = 0.0f;
    *pClear = 0.0f;
    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownF == 1) {
            kind1Count++;
            if (pEntries[i].mUnknown8 & 0x40000000)
                *pSet += lbl_802E99B8[kind1Count / 8];
            else
                *pClear += lbl_802E99B8[kind1Count / 8];
        }
    }
}

void fn_8016BA28(unsigned char *pOut)
{
    unsigned int flags;

    if (fn_800BA6F8()) {
        *pOut = 0;
        flags = 0;
    } else {
        fn_80169FCC(fn_80178308(), pOut, &flags);
    }
}

void fn_8016BA80(void)
{
    fn_801C1F94(lbl_803EB40C, 0, sizeof(Object_8016B04C));
}

void fn_8016BAAC(void)
{
    fn_8022DDB4(0x53545047, lbl_803EB40C);
}
