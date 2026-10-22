#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXDispList.h>
#include "engine/tmlib.h"

static void fn_80210D30(SwapNode_8020ED10 *pNode, ChannelList_8021592C *pList)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    if (pNode->mFormatIndex != pState->mUnknown60) {
        fn_80215A14(pList);
        if (pNode->mFlags & 1) {
            GXSetVtxDesc(GX_VA_PNMTXIDX, GX_DIRECT);
        }
        if (pNode->mFormatIndex != 0) {
            pState->mUnknown60 = pNode->mFormatIndex;
        }
    } else {
        fn_80215B00(pList);
    }
    GXCallDisplayList(pNode->mpData, pNode->mDisplayListSize << 5);
    if (pNode->mFlags & 1) {
        GXSetCurrentMtx(GX_PNMTX0);
    }
}

static void fn_80211138(RenderState_80210298 *pState, SwapNode_8020ED10 *pNode)
{
    ChannelList_8021592C list;
    SwapNode_8020ED10 *pLod;

    fn_80210B6C(pNode->mMaterial);
    pLod = pNode;
    if (pState->mLod != 0 && pNode->mNumLods >= pState->mLod) {
        pLod = &pNode[pState->mLod];
    }
    fn_8021592C(&list, pLod, pState->mpGeom->mpAttrs, pState->mpChannels);
    if (pState->mNumHooks == 0) {
        if (pNode->mFlags & 8) {
            unsigned int i;

            for (i = 0; i < list.mCount; i++) {
                SwapAttr_8020ED10 *pAttr = list.mapAttrs[i];

                if (pAttr->mType == GX_VA_POS && pAttr->mCompType == GX_S16) {
                    list.maCompType[i] = GX_F32;
                    list.maStride[i] = 12;
                }
            }
        }
        fn_80210D30(pNode, &list);
    } else {
        int i;

        for (i = 0; i < pState->mNumHooks; i++) {
            RenderHook_80211138 *pHook = pState->mapHooks[i];

            if (pHook->mFunc != 0) {
                pHook->mFunc(pHook, pNode, &list);
            }
        }
    }
}

void fn_8021126C(void)
{
    RenderState_80210298 *pState = &lbl_803E96E8;
    SwapPart_8020ED10 *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumNodes; i++) {
            fn_80210DCC(pState, &pGeom->mpNodes[i]);
        }
    }
}

void fn_802112DC(unsigned short *pIndices, unsigned int count)
{
    RenderState_80210298 *pState = &lbl_803E96E8;
    SwapPart_8020ED10 *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < count; i++) {
            fn_80211138(pState, &pGeom->mpNodes[pIndices[i]]);
        }
    }
}

void fn_80211350(void)
{
    RenderState_80210298 *pState = &lbl_803E96E8;
    SwapPart_8020ED10 *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumNodes; i++) {
            fn_80211138(pState, &pGeom->mpNodes[i]);
        }
    }
}

void fn_802113C0(int state, int arg)
{
    Swap_802160A0 *pSwap = lbl_803E96E8.mpSwap;

    if (pSwap != 0) {
        SwapState_802160A0 *pSwapState = fn_80216190(pSwap, state, arg);

        if (pSwapState != 0) {
            fn_802112DC(&pSwap->mpNodeIndices[pSwapState->mFirstNode], pSwapState->mNumNodes);
        }
    }
}

void fn_80211424(unsigned short *pIndices, unsigned int count)
{
    SwapPart_8020ED10 *pGeom = lbl_803E96E8.mpGeom;
    RenderState_80210298 *pState = &lbl_803E96E8;
    MaterialList_8020FF34 *pList = pState->mpMaterialList;
    SwapAttr_8020ED10 *pAttrs;
    unsigned int i;

    if (pGeom != 0) {
        pAttrs = pGeom->mpAttrs;

        for (i = 0; i < count; i++) {
            SwapNode_8020ED10 *pNode = &pGeom->mpNodes[pIndices[i]];
            MaterialParm_8020FAAC *pParm = pList->mppMaterials[pNode->mMaterial]->mpParms;
            Clut_80212534 *pClut = pParm->mpClut;
            Texture_80212234 *pTexture = pParm->mpTexture;

            if (pClut != 0) {
                GXLoadTlut(&pClut->u.maTlut[0], 0);
                GXInitTexObjTlut(&pTexture->mObj, 0);
            }
            GXLoadTexObj(&pTexture->mObj, GX_TEXMAP0);
            if (pNode->mFlags & 8) {
                int j;

                for (j = 0; j < pNode->mNumAttrs; j++) {
                    if (pAttrs[j].mType == GX_VA_POS && pAttrs[j].mCompType == GX_S16) {
                        pAttrs[j].mCompType = GX_F32;
                        pAttrs[j].mStride = 12;
                    }
                }
            }
            if (pNode->mFormatIndex != lbl_803E96E8.mUnknown60) {
                SwapAttr_8020ED10 *pAttr = &pAttrs[pNode->mFirstAttr];
                int n = pNode->mNumAttrs;

                GXClearVtxDesc();
                for (; n > 0; n--) {
                    GXSetVtxDesc(pAttr->mType, pAttr->mDescType);
                    GXSetVtxAttrFmt(GX_VTXFMT0, pAttr->mType, pAttr->mCompCount, pAttr->mCompType, pAttr->mFrac);
                    GXSetArray(pAttr->mType, pAttr->mpData, pAttr->mStride);
                    pAttr++;
                }
                if (pNode->mFlags & 1) {
                    GXSetVtxDesc(GX_VA_PNMTXIDX, GX_DIRECT);
                }
                if (pNode->mFormatIndex != 0) {
                    lbl_803E96E8.mUnknown60 = pNode->mFormatIndex;
                }
            } else {
                SwapAttr_8020ED10 *pAttr = &pAttrs[pNode->mFirstAttr];
                int n = pNode->mNumAttrs;

                for (; n > 0; n--) {
                    GXSetArray(pAttr->mType, pAttr->mpData, pAttr->mStride);
                    pAttr++;
                }
            }
            GXCallDisplayList(pNode->mpData, pNode->mDisplayListSize << 5);
        }
        GXSetCurrentMtx(GX_PNMTX0);
        pState->mpMaterial = 0;
        pState->mpShader = 0;
    }
}
