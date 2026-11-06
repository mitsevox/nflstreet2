#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXDispList.h>
#include "engine/tmlib.h"

static void fn_80210D30(TMGeomNode_t *pNode, TMChannelList_t *pList)
{
    TMRenderState_t *pState = &lbl_803E96E8;

    if (pNode->mFormatIndex != pState->mUnknown60) {
        TMChannelListSubmit_DFA(pList);
        if (pNode->mFlags & 1) {
            GXSetVtxDesc(GX_VA_PNMTXIDX, GX_DIRECT);
        }
        if (pNode->mFormatIndex != 0) {
            pState->mUnknown60 = pNode->mFormatIndex;
        }
    } else {
        TMChannelListSubmit_A(pList);
    }
    GXCallDisplayList(pNode->mpData, pNode->mDisplayListSize << 5);
    if (pNode->mFlags & 1) {
        GXSetCurrentMtx(GX_PNMTX0);
    }
}

static void fn_80211138(TMRenderState_t *pState, TMGeomNode_t *pNode)
{
    TMChannelList_t list;
    TMGeomNode_t *pLod;

    TMRenderBindMaterialIndex(pNode->mMaterial);
    pLod = pNode;
    if (pState->mLod != 0 && pNode->mNumLods >= pState->mLod) {
        pLod = &pNode[pState->mLod];
    }
    TMChannelListBuild(&list, pLod, pState->mpGeom->mpAttrs, pState->mpChannels);
    if (pState->mNumHooks == 0) {
        if (pNode->mFlags & 8) {
            unsigned int i;

            for (i = 0; i < list.mCount; i++) {
                TMGeomAttr_t *pAttr = list.mapAttrs[i];

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
    TMRenderState_t *pState = &lbl_803E96E8;
    TMGeom_t *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumNodes; i++) {
            fn_80210DCC(pState, &pGeom->mpNodes[i]);
        }
    }
}

void fn_802112DC(unsigned short *pIndices, unsigned int count)
{
    TMRenderState_t *pState = &lbl_803E96E8;
    TMGeom_t *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < count; i++) {
            fn_80211138(pState, &pGeom->mpNodes[pIndices[i]]);
        }
    }
}

void fn_80211350(void)
{
    TMRenderState_t *pState = &lbl_803E96E8;
    TMGeom_t *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumNodes; i++) {
            fn_80211138(pState, &pGeom->mpNodes[i]);
        }
    }
}

void fn_802113C0(int state, int arg)
{
    TMSwapDef_t *pSwap = lbl_803E96E8.mpSwap;

    if (pSwap != 0) {
        TMSwapState_t *pSwapState = TMSwapGetState(pSwap, state, arg);

        if (pSwapState != 0) {
            fn_802112DC(&pSwap->mpNodeIndices[pSwapState->mFirstNode], pSwapState->mNumNodes);
        }
    }
}

void fn_80211424(unsigned short *pIndices, unsigned int count)
{
    TMGeom_t *pGeom = lbl_803E96E8.mpGeom;
    TMRenderState_t *pState = &lbl_803E96E8;
    TMMaterialList_t *pList = pState->mpMaterialList;
    TMGeomAttr_t *pAttrs;
    unsigned int i;

    if (pGeom != 0) {
        pAttrs = pGeom->mpAttrs;

        for (i = 0; i < count; i++) {
            TMGeomNode_t *pNode = &pGeom->mpNodes[pIndices[i]];
            TMMaterialTexState_t *pParm = pList->mppMaterials[pNode->mMaterial]->mpParms;
            TMClut_t *pClut = pParm->mpClut;
            TMTexture_t *pTexture = pParm->mpTexture;

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
                TMGeomAttr_t *pAttr = &pAttrs[pNode->mFirstAttr];
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
                TMGeomAttr_t *pAttr = &pAttrs[pNode->mFirstAttr];
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
