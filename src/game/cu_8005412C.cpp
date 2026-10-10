#include "game/Level_80054130.h"
#include "game/fn_80054138.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80218FC4.h"

/* 12-byte record of the array 0x800543D4 allocates at lbl_803EA558, one per
   record of the list at +140 of the level data. */
struct Record_803EA558 {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

/* 12-byte text slot of lbl_80309E10, filled by 0x800544A4. */
struct Text_80309E10 {
    int mUnknown0;
    int mUnknown4;
    const char *mpUnknown8;
};

extern "C" {
Area_80054138 *fn_80053F8C(float *pPos, int value);
int fn_801784C4(void);
void *fn_801D2BB0(int a, int size, int c, int d);
int fn_801CFE40(float y, float x);
unsigned int fn_801C3180(const char *pText);
void fn_802195E4(void *p, short a, short b);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);

extern void *lbl_803EB688;

Level_80054130 *lbl_803EA554 = 0;
Record_803EA558 *lbl_803EA558 = 0;
Text_80309E10 *lbl_80309E04[3];
Text_80309E10 lbl_80309E10[3];

void fn_8005412C(void)
{
}

Level_80054130 *fn_80054130(void)
{
    return lbl_803EA554;
}

Area_80054138 *fn_80054138(float *pPos)
{
    return fn_80053F8C(pPos, 0);
}

void fn_8005415C(int id, int value)
{
    unsigned int i;

    for (i = 0; i < lbl_803EA554->mUnknown24; i++) {
        if (lbl_803EA554->mUnknown28[i].mUnknown32 == id) {
            lbl_803EA554->mUnknown28[i].mUnknown8 = value;
        }
    }
}

void fn_800541AC(Record_80054130 *pRecord, void *pFirst, void *pSecond)
{
    float *pA = (float *)pFirst;
    float *pB = (float *)pSecond;
    int foundA = 0;
    int foundB = 0;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pRecord->mUnknown12[i].mZ < 0.1f) {
            if (!foundA) {
                foundA = 1;
                pA[0] = pRecord->mUnknown12[i].mX;
                pA[1] = pRecord->mUnknown12[i].mY;
            } else {
                foundB = 1;
                pB[0] = pRecord->mUnknown12[i].mX;
                pB[1] = pRecord->mUnknown12[i].mY;
            }
        }
    }
    if (foundA && foundB && fn_801784C4()) {
        pA[0] = -pA[0];
        pA[1] = -pA[1];
        pB[0] = -pB[0];
        pB[1] = -pB[1];
    }
}

float fn_8005429C(Record_80054130 *pRecord)
{
    float result = 0.0f;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pRecord->mUnknown12[i].mZ >= 0.1f) {
            result = pRecord->mUnknown12[i].mZ;
        }
    }
    return result;
}

void fn_800542DC(Points_800542DC *pPoints, float *pA, float *pB)
{
    int found = 0;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pPoints->mPoint[i].mZ < 0.1f) {
            if (!found) {
                found = 1;
                pA[0] = pPoints->mPoint[i].mX;
                pA[1] = pPoints->mPoint[i].mY;
            } else {
                pB[0] = pPoints->mPoint[i].mX;
                pB[1] = pPoints->mPoint[i].mY;
            }
        }
    }
}

float fn_8005434C(Points_800542DC *pPoints)
{
    float result = 0.0f;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pPoints->mPoint[i].mZ >= 0.1f) {
            result = pPoints->mPoint[i].mZ;
        }
    }
    return result;
}

Object_8005438C *fn_8005438C(int id)
{
    Object_8005438C *pEntry = 0;

    if (id < lbl_803EA554->mUnknown152) {
        pEntry = &lbl_803EA554->mUnknown156[id];
    }
    return pEntry;
}

int fn_800543B4(void)
{
    Level_80054130 *pLevel = lbl_803EA554;
    int total = 0;

    if (pLevel != 0) {
        total = pLevel->mUnknown88 + pLevel->mUnknown104;
    }
    return total;
}

void fn_800543D4(void)
{
    unsigned int i = 0;
    unsigned int count = fn_80054130()->mUnknown136;
    Record_80054130 *pRecord = fn_80054130()->mUnknown140;

    lbl_803EA558 = (Record_803EA558 *)fn_801D2BB0(1, count * 12, 0, 0);
    for (; i < count; i++, pRecord++) {
        int angle;

        lbl_803EA558[i].mUnknown0 = fn_8005429C(pRecord);
        angle = fn_801CFE40(pRecord->mUnknown0.mY, pRecord->mUnknown0.mX);
        lbl_803EA558[i].mUnknown4 = angle;
        lbl_803EA558[i].mUnknown8 = (angle + 0x800000) & 0xFFFFFF;
    }
}

void fn_80054478(void)
{
    fn_801D2BD0(lbl_803EA558);
    lbl_803EA558 = 0;
}

void fn_800544A4(const char *pTitle, const char *pText, const char *pButtons)
{
    lbl_80309E10[0].mUnknown0 = 0;
    lbl_80309E10[0].mpUnknown8 = pTitle;
    lbl_80309E10[0].mUnknown4 = fn_801C3180(pTitle) + 1;
    lbl_80309E10[1].mUnknown0 = 0;
    lbl_80309E10[1].mpUnknown8 = pText;
    lbl_80309E10[1].mUnknown4 = fn_801C3180(pText) + 1;
    lbl_80309E10[2].mUnknown0 = 0;
    lbl_80309E10[2].mpUnknown8 = pButtons;
    lbl_80309E10[2].mUnknown4 = fn_801C3180(pButtons) + 1;
    lbl_80309E04[0] = &lbl_80309E10[0];
    lbl_80309E04[1] = &lbl_80309E10[1];
    lbl_80309E04[2] = &lbl_80309E10[2];
    fn_80218FC4(lbl_803EB688, 1, 3, 3, (int *)lbl_80309E04);
    fn_802195E4(lbl_803EB688, 1, 3);
}

int fn_80054568(void)
{
    unsigned short group;
    unsigned short screen;

    fn_80219650(lbl_803EB688, &group, &screen);
    return group != 1 || screen != 3;
}
}
