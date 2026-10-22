#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

extern unsigned char *lbl_803EBED0;
extern unsigned char *lbl_803EBED4;
extern unsigned char *lbl_803EBED8;

void fn_8020ED10(Extent_802144AC *pExtent, short *pPoints, int count)
{
    float scale = 1.0f / 32768.0f;

    for (; count > 0; count--) {
        fn_802144D8(pExtent, pPoints[0] * scale, pPoints[1] * scale, pPoints[2] * scale);
        pPoints += 3;
    }
}

void fn_8020EDE4(Extent_802144AC *pExtent, float *pPoints, int count)
{
    for (; count > 0; count--) {
        fn_802144D8(pExtent, pPoints[0], pPoints[1], pPoints[2]);
        pPoints += 3;
    }
}

static int fn_8020EE38(Geom_8020ED10 *pPart, GeomNode_8020ED10 *pNodeA, GeomNode_8020ED10 *pNodeB)
{
    GeomAttr_8020ED10 *pAttrA;
    GeomAttr_8020ED10 *pAttrB;
    int i;

    if (pNodeA->mNumAttrs != pNodeB->mNumAttrs) {
        return 0;
    }
    if ((pNodeA->mFlags & 1) != (pNodeB->mFlags & 1)) {
        return 0;
    }
    for (i = 0; i < pNodeA->mNumAttrs; i++) {
        pAttrA = &pPart->mpAttrs[pNodeA->mFirstAttr + i];
        pAttrB = &pPart->mpAttrs[pNodeB->mFirstAttr + i];
        if (pAttrA->mType != pAttrB->mType) {
            return 0;
        }
        if (pAttrA->mCompCount != pAttrB->mCompCount || pAttrA->mCompType != pAttrB->mCompType || pAttrA->mFrac != pAttrB->mFrac) {
            return 0;
        }
        if (pAttrA->mDescType != pAttrB->mDescType) {
            return 0;
        }
    }
    return 1;
}

static void fn_8020EEE8(Geom_8020ED10 *pPart)
{
    GeomNode_8020ED10 *apFormats[32];
    GeomNode_8020ED10 *pNode;
    unsigned int i;
    int numFormats;
    int j;

    if ((pPart->mFlags & 0x10) == 0) {
        numFormats = 0;
        for (i = 0; i < pPart->mNumNodes; i++) {
            pNode = &pPart->mpNodes[i];
            for (j = 0; j < numFormats; j++) {
                if (fn_8020EE38(pPart, apFormats[j], pNode)) {
                    break;
                }
            }
            if (j == numFormats) {
                if (j < 32) {
                    apFormats[j] = pNode;
                    numFormats = j + 1;
                } else {
                    j = -1;
                }
            }
            pNode->mFormatIndex = j + 1;
        }
        pPart->mFlags |= 0x10;
    }
}

void fn_8020EFC8(int size)
{
    unsigned char *p;

    p = fn_801D2B7C(size, 0, 0);
    lbl_803EBED0 = p;
    lbl_803EBED4 = p;
    lbl_803EBED8 = p + size;
}

void fn_8020F00C(void)
{
    fn_801D2BD0(lbl_803EBED0);
}

void fn_8020F08C(Geom_8020ED10 *pPart, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    pPart->mpNodes = fn_8020EB94(pPart->mpNodes, pOldBase, pNewBase);
    pPart->mpAttrs = fn_8020EB94(pPart->mpAttrs, pOldBase, pNewBase);
    for (i = 0; i < pPart->mNumNodes; i++) {
        GeomNode_8020ED10 *pNode = &pPart->mpNodes[i];

        pNode->mpData = fn_8020EB94(pNode->mpData, pOldBase, pNewBase);
    }
    for (i = 0; i < pPart->mNumAttrs; i++) {
        GeomAttr_8020ED10 *pAttr = &pPart->mpAttrs[i];

        pAttr->mpData = fn_8020EB94(pAttr->mpData, pOldBase, pNewBase);
    }
    pPart->mpUnknown14 = fn_8020EB94(pPart->mpUnknown14, pOldBase, pNewBase);
    fn_8020EEE8(pPart);
}

void fn_8020F178(Geom_8020ED10 *pPart, unsigned short *pRemap, int numMaterials)
{
    GeomNode_8020ED10 *pNode;
    unsigned int i;

    for (i = 0; i < pPart->mNumNodes; i++) {
        pNode = &pPart->mpNodes[i];
        if (pNode->mMaterial >= 0 && pNode->mMaterial < numMaterials) {
            pNode->mMaterial = pRemap[pNode->mMaterial];
        } else {
            pNode->mMaterial = -1;
        }
    }
}

void fn_8020F1D8(Geom_8020ED10 *pPart, int nodeIndex, Extent_802144AC *pExtent)
{
    GeomNode_8020ED10 *pNode;
    GeomAttr_8020ED10 *pAttr;
    int i;

    pNode = &pPart->mpNodes[nodeIndex];
    for (i = 0; i < pNode->mNumAttrs; i++) {
        pAttr = &pPart->mpAttrs[pNode->mFirstAttr + i];
        if (pAttr->mType == 9) {
            switch (pAttr->mCompType) {
            case 3:
                fn_8020ED10(pExtent, pAttr->mpData, pAttr->mCount);
                break;
            case 4:
                fn_8020EDE4(pExtent, pAttr->mpData, pAttr->mCount);
                break;
            }
        }
    }
}
