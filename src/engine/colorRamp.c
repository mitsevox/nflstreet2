#include "engine/particleLib.h"

float fn_801CFB94(int angle);

void fn_801E0984(Ramp_801E052C *pRamp, int interp);
unsigned short fn_801E079C(Ramp_801E052C *pRamp, float t, Vec3_801DE1E0 *pColor);

static void fn_801E052C(Ramp_801E052C *pRamp, unsigned short index, float t, Vec3_801DE1E0 *pColor)
{
    RampNode_801E052C *pNode = pRamp->mpNodes[pRamp->mCount];
    unsigned short i;

    for (i = pRamp->mCount; i > index; i--) {
        pRamp->mpNodes[i] = pRamp->mpNodes[i - 1];
    }
    pRamp->mpNodes[index] = pNode;
    pNode->mT = t;
    pRamp->mpNodes[index]->mColor.x = pColor->x;
    pRamp->mpNodes[index]->mColor.y = pColor->y;
    pRamp->mpNodes[index]->mColor.z = pColor->z;
    pRamp->mCount++;
}

static void fn_801E05B0(Ramp_801E052C *pRamp, float t, Vec3_801DE1E0 *pColor)
{
    unsigned short count = pRamp->mCount;

    pRamp->mpNodes[count]->mT = t;
    pRamp->mpNodes[count]->mColor.x = pColor->x;
    pRamp->mpNodes[count]->mColor.y = pColor->y;
    pRamp->mpNodes[count]->mColor.z = pColor->z;
    pRamp->mCount++;
}

static void fn_801E05F8(Vec3_801DE1E0 *pOut, Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, unsigned int interp, float t)
{
    switch (interp) {
    case 0:
        pOut->x = pA->x;
        pOut->y = pA->y;
        pOut->z = pA->z;
        break;
    case 1:
        fn_80227930(pOut, pB, pA, t);
        break;
    case 2:
        fn_80227930(pOut, pB, pA, -fn_801CFB94((int)(t * 8388608.0f)) * 0.5f + 0.5f);
        break;
    }
}

static RampNode_801E052C *fn_801E06B0(RampNode_801E052C *pSrc, RampNode_801E052C *pDst)
{
    pDst->mT = pSrc->mT;
    pDst->mColor.x = pSrc->mColor.x;
    pDst->mColor.y = pSrc->mColor.y;
    pDst->mColor.z = pSrc->mColor.z;
    return pDst;
}

void fn_801E06DC(Ramp_801E052C *pRamp)
{
    unsigned short i;

    pRamp->mCount = 0;
    pRamp->mInterp = 0;
    for (i = 0; i < 32; i++) {
        pRamp->mpNodes[i] = &pRamp->mPool[i];
    }
}

void fn_801E071C(Ramp_801E052C *pRamp, RampParm_801E071C *pParm)
{
    unsigned short i;

    fn_801E06DC(pRamp);
    fn_801E0984(pRamp, pParm->mInterp);
    for (i = 0; i < pParm->mCount; i++) {
        fn_801E079C(pRamp, pParm->mNodes[i].mT, &pParm->mNodes[i].mColor);
    }
}

unsigned short fn_801E079C(Ramp_801E052C *pRamp, float t, Vec3_801DE1E0 *pColor)
{
    int inserted = 0;
    unsigned short i;

    for (i = 0; i < pRamp->mCount; i++) {
        if (t >= pRamp->mpNodes[i]->mT) {
            continue;
        }
        fn_801E052C(pRamp, i, t, pColor);
        inserted = 1;
        break;
    }
    if (!inserted) {
        fn_801E05B0(pRamp, t, pColor);
    }
    return i;
}

void fn_801E0984(Ramp_801E052C *pRamp, int interp)
{
    pRamp->mInterp = interp;
}

Ramp_801E052C *fn_801E098C(Ramp_801E052C *pSrc, Ramp_801E052C *pDst)
{
    unsigned short i;

    fn_801E06DC(pDst);
    pDst->mInterp = pSrc->mInterp;
    pDst->mCount = pSrc->mCount;
    for (i = 0; i < pDst->mCount; i++) {
        pDst->mpNodes[i] = fn_801E06B0(pSrc->mpNodes[i], &pDst->mPool[i]);
    }
    return pDst;
}
