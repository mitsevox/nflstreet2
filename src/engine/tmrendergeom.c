/* Draws the nodes of a TM model's geometry: binds each node's material, sets up its vertex arrays and calls its
   display list, and skins positions and normals in software against the cluster matrices before drawing. */

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXDispList.h>
#include <dolphin/os/OSCache.h>
#include "engine/tmlib.h"

/* llmatrix.c matrix-stack operations (engine/llmatrix.h clashes with tmlib.h over MatStore). */
void MatPush(void);
void MatPop(void);
void MatMakeUnit(void);

static void _TMRenderGeomSubmit(TMGeomNode_t *pNode, TMChannelList_t *pList)
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

static inline float TMs16tof32(short *pIn)
{
    float f;

    asm volatile("psq_l %0,0(%1),1,5" : "=f"(f) : "b"(pIn));
    return f;
}

static inline float TMs8tof32(signed char *pIn)
{
    float f;

    asm volatile("psq_l %0,0(%1),1,4" : "=f"(f) : "b"(pIn));
    return f;
}

static inline void TMf32tos8(float f, signed char *pOut)
{
    asm volatile("psq_st %0,0(%1),1,4" : : "f"(f), "b"(pOut) : "memory");
}

void TMRenderGeomSkin(TMRenderState_t *pState, TMGeomNode_t *pNode)
{
    TMGeomAttr_t *pAttrs;
    TMGeomAttr_t *pAttr;
    short *pMtxIndex;
    unsigned int i;
    Vec v;

    if (pState == 0 || pState->mpClusterObj == 0 || pState->mpClusterObj->mpMatrices == 0) {
        return;
    }
    pAttrs = pState->mpGeom->mpAttrs;
    DCFlushRange(pState->mpClusterObj->mpMatrices, pState->mpClusterObj->mNumMatrices * sizeof(Mtx));
    for (i = 0; i < pNode->mNumAttrs; i++) {
        pAttr = &pAttrs[pNode->mFirstAttr + i];
        if (pAttr->mType == GX_VA_POS) {
            if (pAttr->mCompType == GX_S16) {
                short *pSrc = pAttr->mpData;
                unsigned short j;
                Vec *pDst;

                pMtxIndex = pAttrs[pNode->mUnknown16].mpData;
                pDst = (Vec *)TMGeomAllocChannelBuffer(pAttr->mCount * sizeof(Vec));
                pState->mpChannels[pNode->mFirstAttr + i] = pDst;
                MatPush();
                MatMakeUnit();
                for (j = 0; j < pAttr->mCount; j++) {
                    v.x = TMs16tof32(pSrc);
                    pSrc++;
                    v.y = TMs16tof32(pSrc);
                    pSrc++;
                    v.z = TMs16tof32(pSrc);
                    pSrc++;
                    PSMTXMultVec(((Mtx *)pState->mpClusterObj->mpMatrices)[pMtxIndex[j]], &v, pDst);
                    pDst++;
                }
            } else if (pAttr->mCompType == GX_F32) {
                // FAKEMATCH: own vector for this arm (the other arms share the function-scope one) gives the target's two stack slots
                Vec v;
                float *pSrc = pAttr->mpData;
                unsigned short j;
                Vec *pDst;

                pMtxIndex = pAttrs[pNode->mUnknown16].mpData;
                pDst = (Vec *)TMGeomAllocChannelBuffer(pAttr->mCount * sizeof(Vec));
                pState->mpChannels[pNode->mFirstAttr + i] = pDst;
                MatPush();
                MatMakeUnit();
                for (j = 0; j < pAttr->mCount; j++) {
                    v.x = *pSrc++;
                    v.y = *pSrc++;
                    v.z = *pSrc++;
                    PSMTXMultVec(((Mtx *)pState->mpClusterObj->mpMatrices)[pMtxIndex[j]], &v, pDst);
                    pDst++;
                }
            } else {
                continue;
            }
            MatPop();
            DCFlushRange(pState->mpChannels[pNode->mFirstAttr + i], pAttr->mCount * sizeof(Vec));
        } else if (pAttr->mType == GX_VA_NRM && pAttr->mCompType == GX_S8) {
            signed char *pSrc = pAttr->mpData;
            unsigned short j;
            signed char *pDst;

            pMtxIndex = pAttrs[pNode->mUnknown16].mpData;
            pDst = (signed char *)TMGeomAllocChannelBuffer(pAttr->mCount * 8);
            pState->mpChannels[pNode->mFirstAttr + i] = pDst;
            MatPush();
            MatMakeUnit();
            for (j = 0; j < pAttr->mCount; j++) {
                v.x = TMs8tof32(pSrc);
                pSrc++;
                v.y = TMs8tof32(pSrc);
                pSrc++;
                v.z = TMs8tof32(pSrc);
                pSrc++;
                PSMTXMultVecSR(((Mtx *)pState->mpClusterObj->mpMatrices)[pMtxIndex[j]], &v, &v);
                v.x *= 32768.0f;
                v.y *= 32768.0f;
                v.z *= 32768.0f;
                TMf32tos8(v.x, pDst);
                pDst++;
                TMf32tos8(v.y, pDst);
                pDst++;
                TMf32tos8(v.z, pDst);
                pDst++;
            }
            MatPop();
            DCFlushRange(pState->mpChannels[pNode->mFirstAttr + i], pAttr->mCount * 3);
        }
    }
}

static void _TMRenderGeom(TMRenderState_t *pState, TMGeomNode_t *pNode)
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
        _TMRenderGeomSubmit(pNode, &list);
    } else {
        int i;

        for (i = 0; i < pState->mNumHooks; i++) {
            TMRenderHook_t *pHook = pState->mapHooks[i];

            if (pHook->mFunc != 0) {
                pHook->mFunc(pHook, pNode, &list);
            }
        }
    }
}

void TMRenderGeomSkinAll(void)
{
    TMRenderState_t *pState = &lbl_803E96E8;
    TMGeom_t *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumNodes; i++) {
            TMRenderGeomSkin(pState, &pGeom->mpNodes[i]);
        }
    }
}

void TMRenderGeomList(unsigned short *pIndices, unsigned int count)
{
    TMRenderState_t *pState = &lbl_803E96E8;
    TMGeom_t *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < count; i++) {
            _TMRenderGeom(pState, &pGeom->mpNodes[pIndices[i]]);
        }
    }
}

void TMRenderGeomAll(void)
{
    TMRenderState_t *pState = &lbl_803E96E8;
    TMGeom_t *pGeom = pState->mpGeom;
    unsigned int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumNodes; i++) {
            _TMRenderGeom(pState, &pGeom->mpNodes[i]);
        }
    }
}

void TMRenderGeomNode(int state, int arg)
{
    TMSwapDef_t *pSwap = lbl_803E96E8.mpSwap;

    if (pSwap != 0) {
        TMSwapState_t *pSwapState = TMSwapGetState(pSwap, state, arg);

        if (pSwapState != 0) {
            TMRenderGeomList(&pSwap->mpNodeIndices[pSwapState->mFirstNode], pSwapState->mNumNodes);
        }
    }
}

void TMRenderGeomListDirect(unsigned short *pIndices, unsigned int count)
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
                // FAKEMATCH: integer address sum (index offset first) gives the target's add order; same address as &pAttrs[pNode->mFirstAttr]
                TMGeomAttr_t *pAttr = (TMGeomAttr_t *)(pNode->mFirstAttr * sizeof(TMGeomAttr_t) + (unsigned int)pAttrs);
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
                // FAKEMATCH: integer address sum, as above
                TMGeomAttr_t *pAttr = (TMGeomAttr_t *)(pNode->mFirstAttr * sizeof(TMGeomAttr_t) + (unsigned int)pAttrs);
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
