/* Partial source for 0x80235010-0x802355E4 (neutral file name): the environment-map texture
   coordinates of a geometry node, the swap-group walk that calls it, and the model object
   state setters that src/engine/modelobj.c uses. */

#include <dolphin/os/OSCache.h>
#include "engine/tmlib.h"
#include "engine/vec.h"
#include "game/Object_80235588.h"

extern float gModelObjEyePos[3];

extern void MatPushUnit(void);
extern void MatPop(void);
extern void MatRotX(int angle);
extern void MatRotZ(int angle);
extern void MatScale(float scale);
extern int MathArcCos(float value);
extern void Vec3Sub(void *pOut, void *pA, void *pB);

static inline float TMs8tof32(signed char *pIn)
{
    float f;

    asm volatile("psq_l %0,0(%1),1,4" : "=f"(f) : "b"(pIn));
    return f;
}

static inline void TMf32tos16(float f, short *pOut)
{
    asm volatile("psq_st %0,0(%1),1,5" : : "f"(f), "b"(pOut) : "memory");
}

void ModelObjEnvMapTexCoords(TMRenderState_t *pState, TMGeomNode_t *pNode)
{
    TMGeomAttr_t *pAttrs;
    TMGeomAttr_t *pAttr;
    TMGeomAttr_t *pPos;
    TMGeomAttr_t *pNrm;
    TMGeomAttr_t *pTex;
    unsigned char *pList;
    signed char *pSrc;
    short *pDst;
    float *pPoint;
    unsigned int i;
    unsigned int j;
    unsigned int count;
    int k;
    int rotZ;
    int rotX;
    float nrmScale;
    float offset;
    Vec v;
    Vec eye;
    Vec r;
    Mtx44 mtx;

    pAttrs = pState->mpGeom->mpAttrs;
    pPos = 0;
    pNrm = 0;
    pTex = 0;
    k = 0;
    for (i = 0; i < pNode->mNumAttrs; i++) {
        pAttr = &pAttrs[pNode->mFirstAttr + i];
        if (pAttr->mType == GX_VA_POS) {
            pPos = pAttr;
        } else if (pAttr->mType == GX_VA_NRM) {
            pNrm = pAttr;
        } else if (pAttr->mType == GX_VA_TEX0) {
            pTex = pAttr;
        }
    }
    MatStore(mtx);

    nrmScale = 1.0f / (float)(1 << pNrm->mFrac);
    pList = pNode->mpData;
    pSrc = (signed char *)pNrm->mpData + pNrm->mStride * pList[4];
    v.x = TMs8tof32(pSrc);
    pSrc++;
    v.z = TMs8tof32(pSrc);
    pSrc++;
    v.y = TMs8tof32(pSrc);
    Vec3Scale(&v, &v, nrmScale);
    Vec3Normalize(&v, &v);
    rotZ = MathArcCos(v.y);
    rotX = MathArcCos(v.z);
    MatPushUnit();
    MatRotX(rotX);
    MatRotZ(rotZ);
    MatScale((float)(1 << pTex->mFrac) * 0.5f);
    offset = (float)(1 << pTex->mFrac) * 0.5f;

    while (k < pNode->mNumVerts) {
        pList++;
        count = *(unsigned short *)pList;
        pList += 2;
        for (j = 0; j < count; j++) {
            pPoint = (float *)((char *)pPos->mpData + pPos->mStride * pList[0]);
            pSrc = (signed char *)pNrm->mpData + pNrm->mStride * pList[1];
            pDst = (short *)((char *)pTex->mpData + pTex->mStride * pList[3]);
            v.x = TMs8tof32(pSrc);
            pSrc++;
            v.z = TMs8tof32(pSrc);
            pSrc++;
            v.y = TMs8tof32(pSrc);
            Vec3Scale(&v, &v, nrmScale);
            Vec3Sub(&eye, pPoint, gModelObjEyePos);
            Vec3Normalize(&eye, &eye);
            Vec3Scale(&r, &v, Vec3DotProduct(&eye, &v) * 2.0f);
            Vec3Sub(&r, &eye, &r);
            Vec3Mat33Mul(&r, &r);
            r.x += offset;
            r.y += offset;
            TMf32tos16(r.x, pDst);
            pDst++;
            TMf32tos16(r.y, pDst);
            pList += 4;
            k++;
        }
    }
    MatPop();
    DCFlushRange(pTex->mpData, pTex->mCount * sizeof(short));
}

void fn_80235328(TMModel_t *pModel, int key)
{
    TMGeom_t *pGeom = pModel->mpGeom;
    TMRenderState_t *pState = &lbl_803E96E8;
    TMSwapDef_t *pSwap = pState->mpSwap;
    TMSwapState_t *pSwapState;
    unsigned short *pIndex;
    int i;

    if (pSwap != 0) {
        pSwapState = TMSwapGetState(pSwap, 0, key);
        if (pSwapState != 0) {
            pIndex = &pSwap->mpNodeIndices[pSwapState->mFirstNode];
            for (i = 0; i < pSwapState->mNumNodes; i++) {
                ModelObjEnvMapTexCoords(pState, &pGeom->mpNodes[pIndex[i]]);
            }
        }
    }
}

void fn_802353CC(void *p)
{
}

void fn_802353D0(void *p)
{
}

void fn_802353D4(Object_80235588 *p, int flags)
{
}

void fn_802353D8(Object_80235588 *p, int flags)
{
    p->mUnknown0 |= flags;
}

void fn_802353E8(Object_80235588 *p, int flags)
{
    p->mUnknown0 &= ~flags;
}

void fn_802353F8(Object_80235588 *p, int flags)
{
    int old = p->mUnknown4;

    p->mUnknown4 = 0;
    if (flags & 0xC000) {
        p->mUnknown4 = 1;
    }
    if (flags & 1) {
        p->mUnknown4 = 4;
    }
    if (flags == 0x02000000) {
        p->mUnknown4 = 2;
    }
    if (flags == 0x04000000) {
        p->mUnknown4 = 3;
    }
    if (flags & 0x10000000) {
        p->mUnknown4 = 5;
    }
    if (flags & 0x20000000) {
        p->mUnknown4 = 6;
    }
    if (flags & 0x2000) {
        p->mUnknown4 = 17;
    }
    if (flags & 0x200) {
        p->mUnknown4 = 18;
    }
    if (flags & 0x400) {
        p->mUnknown4 = 19;
    }
    if (old != p->mUnknown4) {
        TMClipResetExtent((TMClipExtent_t *)p->mUnknown152);
        if (p->mUnknown4 == -1) {
            TMModelAddExtent((TMModel_t *)&p->mUnknown100, (TMClipExtent_t *)p->mUnknown152, -1, -1);
        } else {
            TMModelAddExtent((TMModel_t *)&p->mUnknown100, (TMClipExtent_t *)p->mUnknown152, 0, p->mUnknown4);
        }
    }
}

void fn_80235510(Object_80235588 *p, int mode)
{
    int old = p->mUnknown4;

    p->mUnknown4 = mode;
    if (old != mode) {
        TMClipResetExtent((TMClipExtent_t *)p->mUnknown152);
        if (p->mUnknown4 == -1) {
            TMModelAddExtent((TMModel_t *)&p->mUnknown100, (TMClipExtent_t *)p->mUnknown152, -1, -1);
        } else {
            TMModelAddExtent((TMModel_t *)&p->mUnknown100, (TMClipExtent_t *)p->mUnknown152, 0, p->mUnknown4);
        }
    }
}

void fn_80235588(Object_80235588 *p, int a)
{
    p->mUnknown0 = 0x4000;
    p->mUnknown4 = -1;
    p->mpUnknown88 = 0;
    p->mpUnknown84 = 0;
    p->mUnknown184 = 0;
    TMModelReset((TMModel_t *)&p->mUnknown100);
    TMMaterialListAlloc((TMMaterialList_t *)p->mUnknown92, 0);
}
