/* TM renderer geometry: relocates a model's Geom chunk, groups its nodes by vertex format,
   remaps node materials, grows bounding extents from vertex positions and runs the ring buffer
   that geometry submission takes its per-frame vertex channel data from. */

#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

unsigned char *_TMGeom_ChannelBuffer = 0;
unsigned char *_TMGeom_BufferPosition = 0;
unsigned char *_TMGeom_BufferEnd = 0;

void TMGeomExtentAddS16Points(Extent_802144AC *pExtent, short *pPoints, int count)
{
    float scale = 1.0f / 32768.0f;

    for (; count > 0; count--) {
        fn_802144D8(pExtent, pPoints[0] * scale, pPoints[1] * scale, pPoints[2] * scale);
        pPoints += 3;
    }
}

void TMGeomExtentAddF32Points(Extent_802144AC *pExtent, float *pPoints, int count)
{
    for (; count > 0; count--) {
        fn_802144D8(pExtent, pPoints[0], pPoints[1], pPoints[2]);
        pPoints += 3;
    }
}

static int _TMGeometryIsSameFormat(TMGeom_t *pPart, TMGeomNode_t *pNodeA, TMGeomNode_t *pNodeB)
{
    TMGeomAttr_t *pAttrA;
    TMGeomAttr_t *pAttrB;
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

static void _TMGeometryHashFormat(TMGeom_t *pPart)
{
    TMGeomNode_t *apFormats[32];
    TMGeomNode_t *pNode;
    unsigned int i;
    int numFormats;
    int j;

    if ((pPart->mFlags & 0x10) == 0) {
        numFormats = 0;
        for (i = 0; i < pPart->mNumNodes; i++) {
            pNode = &pPart->mpNodes[i];
            for (j = 0; j < numFormats; j++) {
                if (_TMGeometryIsSameFormat(pPart, apFormats[j], pNode)) {
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

void TMGeomInitChannelBuffer(int size)
{
    unsigned char *p;

    p = fn_801D2B7C(size, 0, 0);
    _TMGeom_ChannelBuffer = p;
    _TMGeom_BufferPosition = p;
    _TMGeom_BufferEnd = p + size;
}

void TMGeomFreeChannelBuffer(void)
{
    fn_801D2BD0(_TMGeom_ChannelBuffer);
}

/* Reserve scratch bytes, wrapping when the remaining space is not greater than the request. */
unsigned char *TMGeomAllocChannelBuffer(unsigned int size)
{
    unsigned char *p;
    unsigned char *cursor;

    if (_TMGeom_BufferEnd - _TMGeom_BufferPosition > size) {
        p = _TMGeom_BufferPosition;
        _TMGeom_BufferPosition += size;
    } else {
        p = _TMGeom_ChannelBuffer;
        _TMGeom_BufferPosition = p + size;
    }
    while ((unsigned int)(cursor = _TMGeom_BufferPosition) & 31) {
        *cursor = 0;
        _TMGeom_BufferPosition++;
    }
    return p;
}

void TMGeomRelocateChunk(TMGeom_t *pPart, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    pPart->mpNodes = TMModelResRelocatePtr(pPart->mpNodes, pOldBase, pNewBase);
    pPart->mpAttrs = TMModelResRelocatePtr(pPart->mpAttrs, pOldBase, pNewBase);
    for (i = 0; i < pPart->mNumNodes; i++) {
        TMGeomNode_t *pNode = &pPart->mpNodes[i];

        pNode->mpData = TMModelResRelocatePtr(pNode->mpData, pOldBase, pNewBase);
    }
    for (i = 0; i < pPart->mNumAttrs; i++) {
        TMGeomAttr_t *pAttr = &pPart->mpAttrs[i];

        pAttr->mpData = TMModelResRelocatePtr(pAttr->mpData, pOldBase, pNewBase);
    }
    pPart->mpUnknown14 = TMModelResRelocatePtr(pPart->mpUnknown14, pOldBase, pNewBase);
    _TMGeometryHashFormat(pPart);
}

void TMGeometryRemapMaterials(TMGeom_t *pPart, unsigned short *pRemap, int numMaterials)
{
    TMGeomNode_t *pNode;
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

void TMGeomAddNodeExtent(TMGeom_t *pPart, int nodeIndex, Extent_802144AC *pExtent)
{
    TMGeomNode_t *pNode;
    TMGeomAttr_t *pAttr;
    int i;

    pNode = &pPart->mpNodes[nodeIndex];
    for (i = 0; i < pNode->mNumAttrs; i++) {
        pAttr = &pPart->mpAttrs[pNode->mFirstAttr + i];
        if (pAttr->mType == 9) {
            switch (pAttr->mCompType) {
            case 3:
                TMGeomExtentAddS16Points(pExtent, pAttr->mpData, pAttr->mCount);
                break;
            case 4:
                TMGeomExtentAddF32Points(pExtent, pAttr->mpData, pAttr->mCount);
                break;
            }
        }
    }
}
