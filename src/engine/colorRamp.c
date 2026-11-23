/* Builds and samples the color ramps used over a particle's lifetime. */
#include "engine/particleLib.h"

float fn_801CFB94(int angle);

void ColorRampSetInterp(ColorRamp_t *pRamp, int interp);
unsigned short ColorRampInsertColor(ColorRamp_t *pRamp, float t, Vec3_801DE1E0 *pColor);

static void _colorRampInsertIndex(ColorRamp_t *pRamp, unsigned short index, float t, Vec3_801DE1E0 *pColor)
{
    ColorRampNode_t *pNode = pRamp->mpNodes[pRamp->mCount];
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

static void _colorRampAppend(ColorRamp_t *pRamp, float t, Vec3_801DE1E0 *pColor)
{
    unsigned short count = pRamp->mCount;

    pRamp->mpNodes[count]->mT = t;
    pRamp->mpNodes[count]->mColor.x = pColor->x;
    pRamp->mpNodes[count]->mColor.y = pColor->y;
    pRamp->mpNodes[count]->mColor.z = pColor->z;
    pRamp->mCount++;
}

static void _colorRampInterp(Vec3_801DE1E0 *pOut, Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, unsigned int interp, float t)
{
    switch (interp) {
    case 0:
        pOut->x = pA->x;
        pOut->y = pA->y;
        pOut->z = pA->z;
        break;
    case 1:
        Vec3Lerp(pOut, pB, pA, t);
        break;
    case 2:
        Vec3Lerp(pOut, pB, pA, -fn_801CFB94((int)(t * 8388608.0f)) * 0.5f + 0.5f);
        break;
    }
}

static ColorRampNode_t *_colorRampCopyNode(ColorRampNode_t *pSrc, ColorRampNode_t *pDst)
{
    pDst->mT = pSrc->mT;
    pDst->mColor.x = pSrc->mColor.x;
    pDst->mColor.y = pSrc->mColor.y;
    pDst->mColor.z = pSrc->mColor.z;
    return pDst;
}

void ColorRampInit(ColorRamp_t *pRamp)
{
    unsigned short i;

    pRamp->mCount = 0;
    pRamp->mInterp = 0;
    for (i = 0; i < 32; i++) {
        pRamp->mpNodes[i] = &pRamp->mPool[i];
    }
}

void ColorRampInitParms(ColorRamp_t *pRamp, ColorRampParms_t *pParm)
{
    unsigned short i;

    ColorRampInit(pRamp);
    ColorRampSetInterp(pRamp, pParm->mInterp);
    for (i = 0; i < pParm->mCount; i++) {
        ColorRampInsertColor(pRamp, pParm->mNodes[i].mT, &pParm->mNodes[i].mColor);
    }
}

unsigned short ColorRampInsertColor(ColorRamp_t *pRamp, float t, Vec3_801DE1E0 *pColor)
{
    int inserted = 0;
    unsigned short i;

    for (i = 0; i < pRamp->mCount; i++) {
        if (t >= pRamp->mpNodes[i]->mT) {
            continue;
        }
        _colorRampInsertIndex(pRamp, i, t, pColor);
        inserted = 1;
        break;
    }
    if (!inserted) {
        _colorRampAppend(pRamp, t, pColor);
    }
    return i;
}

unsigned int ColorRampEval(ColorRamp_t *pRamp, float t, Vec3_801DE1E0 *pColor, unsigned int start)
{
    int found = 0;
    ColorRampNode_t *pNode = 0;
    ColorRampNode_t *pPrev;
    unsigned int i;
    ColorRampNode_t **nodes;
    float blue;
    unsigned int interp;

    i = start;
    if (i < pRamp->mCount) {
        nodes = &pRamp->mpNodes[0];
        pNode = nodes[start];
        goto check_key;

prev_color:
        pColor->x = pNode[-1].mColor.x;
        pColor->y = pNode[-1].mColor.y;
        blue = pNode[-1].mColor.z;
        goto store_blue;

interpolate:
        interp = pRamp->mInterp;
        if (interp == 0) {
            goto prev_color;
        }
        pPrev = pRamp->mpNodes[i - 1];
        _colorRampInterp(pColor, &pPrev->mColor, &pNode->mColor, interp,
                    (t - pPrev->mT) / (pNode->mT - pPrev->mT));
        goto complete;

step:
        ++i;
        if (i >= pRamp->mCount) {
            goto complete;
        }
        pNode = nodes[i];
check_key:
        if (t >= pNode->mT) {
            goto step;
        }

        found = 1;
        if (i != 0) {
            goto interpolate;
        }
        pColor->x = pNode->mColor.x;
        pColor->y = pNode->mColor.y;
        blue = pNode->mColor.z;
store_blue:
        pColor->z = blue;
    }

complete:
    if (!found) {
        if (pNode == 0) {
            pColor->z = pColor->y = pColor->x = 0.0f;
        } else {
            pColor->x = pNode->mColor.x;
            pColor->y = pNode->mColor.y;
            pColor->z = pNode->mColor.z;
        }
    }
    return i;
}

void ColorRampSetInterp(ColorRamp_t *pRamp, int interp)
{
    pRamp->mInterp = interp;
}

ColorRamp_t *ColorRampCopy(ColorRamp_t *pSrc, ColorRamp_t *pDst)
{
    unsigned short i;

    ColorRampInit(pDst);
    pDst->mInterp = pSrc->mInterp;
    pDst->mCount = pSrc->mCount;
    for (i = 0; i < pDst->mCount; i++) {
        pDst->mpNodes[i] = _colorRampCopyNode(pSrc->mpNodes[i], &pDst->mPool[i]);
    }
    return pDst;
}
