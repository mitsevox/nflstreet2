#include <dolphin/gx/GXGeometry.h>
#include "engine/tmlib.h"

void fn_8021592C(ChannelList_8021592C *pList, GeomNode_8020ED10 *pNode, GeomAttr_8020ED10 *pAttrs, void **ppChannels)
{
    unsigned int count = pNode->mNumAttrs;
    unsigned int i;

    pList->mCount = count;
    for (i = 0; i < count; i++) {
        pList->maCompType[i] = 0xFF;
        pList->maStride[i] = 0xFF;
        pList->maFrac[i] = 0xFF;
    }
    if (ppChannels == 0) {
        pAttrs += pNode->mFirstAttr;
        for (i = 0; i < count; i++) {
            pList->mapAttrs[i] = pAttrs;
            pList->mapData[i] = pAttrs->mpData;
            pAttrs++;
        }
    } else {
        pAttrs += pNode->mFirstAttr;
        ppChannels += pNode->mFirstAttr;
        for (i = 0; i < pNode->mNumAttrs; i++) {
            void *pData;

            pList->mapAttrs[i] = pAttrs;
            pData = ppChannels[i];
            if (pData == 0) {
                pData = pAttrs->mpData;
            }
            pList->mapData[i] = pData;
            pAttrs++;
        }
    }
}

void fn_80215A14(ChannelList_8021592C *pList)
{
    int count;
    int i;

    GXClearVtxDesc();
    count = pList->mCount;
    for (i = 0; i < count; i++) {
        GeomAttr_8020ED10 *pAttr = pList->mapAttrs[i];
        unsigned char compType;
        unsigned char stride;
        unsigned char frac;

        if (pList->maCompType[i] == 0xFF) {
            compType = pAttr->mCompType;
        } else {
            compType = pList->maCompType[i];
        }
        if (pList->maStride[i] == 0xFF) {
            stride = pAttr->mStride;
        } else {
            stride = pList->maStride[i];
        }
        if (pList->maFrac[i] == 0xFF) {
            frac = pAttr->mFrac;
        } else {
            frac = pList->maFrac[i];
        }
        GXSetVtxDesc(pAttr->mType, pAttr->mDescType);
        GXSetVtxAttrFmt(GX_VTXFMT0, pAttr->mType, pAttr->mCompCount, compType, frac);
        GXSetArray(pAttr->mType, pList->mapData[i], stride);
    }
}

void fn_80215B00(ChannelList_8021592C *pList)
{
    int count = pList->mCount;
    int i;

    for (i = 0; i < count; i++) {
        GeomAttr_8020ED10 *pAttr = pList->mapAttrs[i];
        int stride = pList->maStride[i];

        if (stride == 0xFF) {
            stride = pAttr->mStride;
        }
        GXSetArray(pAttr->mType, pList->mapData[i], stride);
    }
}
