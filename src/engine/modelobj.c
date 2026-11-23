/* Model objects: binds a TM model, its textures and shader to a game object and draws it with the object's
   blend, depth, fog and lighting settings. */
#include "engine/SyncStateGroup.h"
#include "engine/EvMonDesc.h"
#include "engine/EvMonAddListener.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/SyncStateRegister.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct ModelObjMaterialDefs_t {
    unsigned int mNumMaterials;
} ModelObjMaterialDefs_t;

typedef struct ModelObjTextureElement_t {
    char unk_0x0[40];
    int unk_0x28;
    ModelObjMaterialDefs_t *mpMaterialDefs;
} ModelObjTextureElement_t;

extern float gModelObjEyePos[3];
extern void TMModelResRelocate(void *p);
extern void TMModelReset(void *p);
extern void TMModelBindModelRes(void *p, void *pData);
extern void TMModelAddExtent(void *p, void *q, int a, int b);
extern void TMMaterialListAlloc(void *p, int a);
extern void TMMaterialListFree(void *p);
extern void TMMaterialListSetMatDefs(void *p, void *q);
extern int TMShaderLibGetShader(const char *pName);
extern void TMTexLibRegistryReset(void);
extern void TMTexLibRegister(const char *pName, void *p);
extern void TMClipResetExtent(void *p);
extern void TMClipProjection(int a);
extern void TMClipMatrix(void *pMtx);
extern unsigned int TMClipBBox(void *p, void *q, int a);
extern void TMRenderBindShader(void *pShader);
extern void TMXform(unsigned int id, float (*pMtx)[4]);
extern void TMXformSelect(unsigned int id);
extern void TMRenderSetBlendMode(unsigned int mode);
extern void TMRenderSetZMode(GXBool compareEnable, GXCompare func, GXBool updateEnable);
extern void TMRenderSetZRange(float nearZ, float farZ);
extern void TMRenderBindModel(void *pModel);
extern void TMRenderBindMaterialList(void *pList);
extern void TMRenderGeomAll(void);
extern void TMRenderGeomNode(int state, int arg);
extern int LLFogEnable(int enable);
/* Model objects are drawn only while this is set. */
static int _ModelObj_bRenderEnabled = 1;
typedef struct Owner_80235328 Owner_80235328;
void fn_80235328(Owner_80235328 *pOwner, int key);
void fn_802353D4(Object_80235588 *p, int flags);
void fn_802353D8(Object_80235588 *p, int flags);
void fn_802353E8(Object_80235588 *p, int flags);
void ModelObjRender(Object_80235588 *p, int handle, int lightMask);

void ModelObjReset(Object_80235588 *p)
{
    if (p->mpUnknown88 != 0) {
        TMMaterialListFree(p->mUnknown92);
        p->mpUnknown88 = 0;
    }
    TMModelReset(&p->mUnknown100);
}

void ModelObjSetModel(Object_80235588 *p, void *pData)
{
    if (p->mpUnknown84 != pData) {
        p->mpUnknown84 = pData;
        TMModelReset(&p->mUnknown100);
        if (pData != 0) {
            TMModelBindModelRes(&p->mUnknown100, pData);
        }
        fn_802353E8(p, 0x8000);
        fn_802353E8(p, 0x10000);
        if (p->mUnknown100.mpUnknown8 != 0) {
            if (p->mUnknown100.mpUnknown8->mUnknown16 & 2) {
                fn_802353D8(p, 0x8000);
            }
            if (p->mUnknown100.mpUnknown8->mUnknown16 & 4) {
                fn_802353D8(p, 0x10000);
            }
            TMClipResetExtent(p->mUnknown152);
            TMModelAddExtent(&p->mUnknown100, p->mUnknown152, -1, -1);
        }
    }
}

void ModelObjSetShader(Object_80235588 *p, const char *pName)
{
    p->mUnknown184 = TMShaderLibGetShader(pName);
}

void ModelObjStoreMatrix(Object_80235588 *p, int handle)
{
    MatStore(p->mUnknown8[0]);
}

void ModelObjDraw(Object_80235588 *p, int handle)
{
    ModelObjRender(p, handle, 1);
}

/* Whether the model is drawn with fog turned off (flag bit 0 clear). */
static inline int _ModelObjFogOff(Object_80235588 *p)
{
    return !(p->mUnknown0 & 1);
}

void ModelObjRender(Object_80235588 *p, int handle, int lightMask)
{
    int fog = 0;
    GXBool zUpdate = 1;

    if (_ModelObj_bRenderEnabled != 0 && p->mpUnknown84 != 0) {
        // FAKEMATCH: the target stores red with the initializer word and the other three
        // bytes through a pointer register (addi r9,r1,12); the original form is not known.
        GXColor color = {128};
        GXColor *pColor = &color;

        pColor->g = 128;
        pColor->b = 128;
        pColor->a = 255;
        if (p->mUnknown0 & 0x4000) {
            TMClipProjection(0);
            TMClipMatrix(p->mUnknown8);
            if (TMClipBBox(p->mUnknown152, 0, 0) & 0x3F) {
                return;
            }
        }
        if (p->mUnknown184 != 0) {
            TMRenderBindShader((void *)p->mUnknown184);
        }
        GXSetChanMatColor(GX_COLOR0A0, color);
        TMXform(0, p->mUnknown8);
        TMXformSelect(0);
        if (p->mUnknown0 & 0x100000) {
            TMRenderSetBlendMode(3);
        } else if (p->mUnknown0 & 0x200000) {
            TMRenderSetBlendMode(6);
        } else if (p->mUnknown0 & 2) {
            TMRenderSetBlendMode(2);
        } else {
            TMRenderSetBlendMode(1);
        }
        if (p->mUnknown0 & 0x200) {
            GXSetZCompLoc(0);
            GXSetAlphaCompare(GX_GREATER, 32, GX_AOP_AND, GX_GREATER, 0);
        } else {
            GXSetZCompLoc(1);
            GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_GREATER, 0);
        }
        if (p->mUnknown0 & 8) {
            zUpdate = 0;
        }
        if (p->mUnknown0 & 0x40000) {
            TMRenderSetZMode(1, GX_LEQUAL, zUpdate);
            TMRenderSetZRange(0.0f, 1.0f - p->mUnknown188);
        } else if (p->mUnknown0 & 0x80000) {
            TMRenderSetZMode(1, GX_LESS, zUpdate);
            TMRenderSetZRange(p->mUnknown72, p->mUnknown72);
        } else if (p->mUnknown0 & 0x400000) {
            TMRenderSetZMode(1, GX_ALWAYS, zUpdate);
        } else {
            TMRenderSetZMode(1, GX_LEQUAL, zUpdate);
            TMRenderSetZRange(0.0f, 1.0f);
        }
        if (_ModelObjFogOff(p)) {
            fog = LLFogEnable(0);
        }
        GXSetNumChans(1);
        if (p->mUnknown0 & 0x20000) {
            GXSetChanAmbColor(GX_COLOR0A0, *(GXColor *)p->mUnknown76);
            GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, 1, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
        } else if (!(p->mUnknown0 & 0x8000)) {
            GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
            if (p->mUnknown0 & 0x10000) {
                GXSetChanCtrl(GX_COLOR0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
            } else {
                GXSetChanCtrl(GX_COLOR0, 0, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, GX_AF_SPOT);
        }
        TMRenderBindModel(&p->mUnknown100);
        TMRenderBindMaterialList(p->mUnknown92);
        if (p->mUnknown0 & 0x800000) {
            fn_80235328((Owner_80235328 *)&p->mUnknown100, p->mUnknown4);
        }
        if (p->mUnknown100.mUnknown20 == 0 || p->mUnknown4 == -1) {
            TMRenderGeomAll();
        } else {
            TMRenderGeomNode(0, p->mUnknown4);
        }
        if (p->mUnknown0 & 0x4C0000) {
            TMRenderSetZMode(1, GX_LEQUAL, 1);
            TMRenderSetZRange(0.0f, 1.0f);
        }
        if (_ModelObjFogOff(p)) {
            LLFogEnable(fog);
        }
    }
}

void ModelObjSetTextures(Object_80235588 *p, ModelObjTextureElement_t *pElement, int a)
{
    ModelObjMaterialDefs_t *pMaterialDefs;

    if (p->mpUnknown88 != pElement) {
        if (p->mpUnknown88 != 0) {
            TMMaterialListFree(p->mUnknown92);
        }
        if (pElement != 0) {
            TMTexLibRegistryReset();
            if (pElement->unk_0x28 != 0) {
                TMTexLibRegister("model", pElement);
            }
            pMaterialDefs = pElement->mpMaterialDefs;
            if (pMaterialDefs != 0) {
                TMMaterialListAlloc(p->mUnknown92, pMaterialDefs->mNumMaterials);
                TMMaterialListSetMatDefs(p->mUnknown92, pMaterialDefs);
            } else {
                TMMaterialListAlloc(p->mUnknown92, 0);
            }
        }
        p->mpUnknown88 = pElement;
        fn_802353D4(p, 8);
    }
}

void ModelObjSetTexturesDefault(Object_80235588 *p, ModelObjTextureElement_t *pElement)
{
    ModelObjSetTextures(p, pElement, 0);
}

void ModelObjSetParamNop(Object_80235588 *p, int a)
{
}

void ModelObjSetFixedDepth(int a, Object_80235588 *p, float value)
{
    fn_802353D8(p, 0x80000);
    p->mUnknown72 = value;
}

void ModelObjSetAmbientColor(Object_80235588 *p, int unused, float r, float g, float b, float a)
{
    p->mUnknown76[0] = (unsigned char)(r * 255.0f);
    p->mUnknown76[1] = (unsigned char)(g * 255.0f);
    p->mUnknown76[2] = (unsigned char)(b * 255.0f);
    p->mUnknown76[3] = (unsigned char)(a * 255.0f);
    /* Enable the ambient override used by ModelObjRender. */
    p->mUnknown0 |= 0x20000;
}

void ModelObjSetFlagsNop(Object_80235588 *p, int a)
{
}

void ModelObjSetDepthOffset(Object_80235588 *p, float value)
{
    if (!(value <= 0.0f)) {
        fn_802353D8(p, 0x40000);
        p->mUnknown188 = value;
    } else {
        fn_802353E8(p, 0x40000);
    }
}

void ModelObjSetModeNop(Object_80235588 *p, int a)
{
}

void ModelObjSetEyePos(float *p)
{
    gModelObjEyePos[0] = p[0];
    gModelObjEyePos[1] = p[1];
    gModelObjEyePos[2] = p[2];
}

int ModelObjIsModelRes(unsigned int *p)
{
    return *p == 0x544D646C;
}

void ModelObjRelocateModelRes(void *p)
{
    TMModelResRelocate(p);
}
