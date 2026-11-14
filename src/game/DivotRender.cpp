/* Turf divot rendering: per divot type, loads the variant textures and draws
   each divot as a faded, rotated and scaled textured quad; dispatchers route
   the divot code's events to the type's handlers. */
#include <dolphin/gx/GXPixel.h>
#include "game/ResLoad.h"
#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

/* 48-byte element; DivotRenderLoadType fills one per entry of the handler set. */
struct DivotTexLib {
    char mUnknown0[0x28];
    int mUnknown28;
    int mUnknown2C;
};

struct DivotOwnerView;

/* Object passed to the per-object handlers; +0x68 selects its handler set. */
struct DivotDrawView {
    char mUnknown0[0xC];
    float mUnknownC;
    float mUnknown10;
    float mUnknown14;
    char mUnknown18[0x18];
    int mUnknown30;
    float mUnknown34;
    char mUnknown38[0x18];
    DivotOwnerView *mpUnknown50;
    char mUnknown54[0xC];
    DivotTexLib *mpUnknown60;
    char mUnknown64[4];
    int mUnknown68;
    int mUnknown6C;
};

struct DivotOwnerView {
    char mUnknown0[0xB];
    unsigned char mUnknownB;
};

extern "C" {
int DivotGetVariantCount(int index);
int DivotGetLevelResource(void);
int DivotGetTextureRef(int index, int i);
void TMTexLibLoad(DivotTexLib *pElement, int a);
void TMTexLibUnload(DivotTexLib *pElement);
int TMTexLibGetTexture(DivotTexLib *pElement, int a);
int TMTexLibGetClut(DivotTexLib *pElement, int a, int b);
void TMRenderReset(void);
void TMRenderBindTexture(int a, int b, int c);
void TMRenderSetZRange(float a, float b);
int fn_80236EC0(int a);
void GXSetChanMatColor(int a, GXColor color);
void GXSetNumChans(int a);
void GXSetChanCtrl(int a, int b, int c, int d, int e, int f, int g);
void GXLoadPosMtxImm(Mtx44 m, int a);
void GXSetCurrentMtx(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0D94(float x, float y, float z);
void fn_801D0F80(Mtx44 m);
}

static DivotTexLib *_DivotRender_apTexLibs[1];
static unsigned char _DivotRender_bSavedFog;

extern "C" {
void DivotRenderLoadType(int index)
{
    if (DivotGetVariantCount(index) > 0) {
        int i = 0;
        DivotTexLib *pElement;
        int handle;

        pElement = _DivotRender_apTexLibs[index] = (DivotTexLib *)fn_801D2B7C(DivotGetVariantCount(index) * sizeof(DivotTexLib), 0, 0);
        handle = DivotGetLevelResource();
        for (; i < DivotGetVariantCount(index); i++) {
            TMTexLibLoad(pElement, ResLoad((void *)handle, DivotGetTextureRef(index, i), 1));
            pElement->mUnknown28 = TMTexLibGetTexture(pElement, 0xFF000000);
            pElement->mUnknown2C = TMTexLibGetClut(pElement, 0xFF000000, 0);
            pElement++;
        }
    }
}

void DivotRenderFreeType(int index)
{
    if (DivotGetVariantCount(index) > 0) {
        DivotTexLib *pElements = _DivotRender_apTexLibs[index];
        int i;

        for (i = 0; i < DivotGetVariantCount(index); i++) {
            TMTexLibUnload(&pElements[i]);
            ResUnLoad((void *)DivotGetLevelResource(), DivotGetTextureRef(index, i));
        }
        fn_801D2BD0(pElements);
        _DivotRender_apTexLibs[index] = 0;
    }
}

void DivotRenderPlace(DivotDrawView *pObject)
{
    pObject->mpUnknown60 = &_DivotRender_apTexLibs[pObject->mUnknown68][pObject->mUnknown6C];
}

void DivotRenderRemove(DivotDrawView *pObject)
{
    pObject->mpUnknown60 = 0;
}

void DivotRenderRefresh(DivotDrawView *pObject)
{
    pObject->mpUnknown60 = &_DivotRender_apTexLibs[pObject->mUnknown68][pObject->mUnknown6C];
}

void DivotRenderBegin(int index)
{
    GXColor color = { 255, 255, 255, 255 };

    TMRenderReset();
    _DivotRender_bSavedFog = fn_80236EC0(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_DISABLE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    TMRenderSetZRange(0.01f, 0.01f);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetChanMatColor(4, color);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 1, 2, 1);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}

void DivotRenderEnd(int index)
{
    TMRenderSetZRange(0.0f, 1.0f);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    fn_80236EC0(_DivotRender_bSavedFog);
}

void DivotRenderDrawOne(DivotDrawView *pObject)
{
    Mtx44 mtx;
    GXColor color = { 255, 255, 255, 255 };

    if (pObject->mpUnknown50 == 0 || pObject->mpUnknown50->mUnknownB != 0) {
        color.a = pObject->mUnknown34 * 255.0f;
        GXSetChanMatColor(4, color);
        TMRenderBindTexture(0, pObject->mpUnknown60->mUnknown28, pObject->mpUnknown60->mUnknown2C);
        fn_801D04C4();
        fn_801D0C58(pObject);
        fn_801D0ADC(pObject->mUnknown30);
        fn_801D0D94(pObject->mUnknownC, pObject->mUnknown10, pObject->mUnknown14);
        fn_801D0F80(mtx);
        GXLoadPosMtxImm(mtx, 0);
        GXSetCurrentMtx(0);
        fn_801D0544();
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
        GXWGFifo.f32 = -0.16f;
        GXWGFifo.f32 = 0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.16f;
        GXWGFifo.f32 = 0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 1.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.16f;
        GXWGFifo.f32 = -0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 1.0f;
        GXWGFifo.f32 = 1.0f;
        GXWGFifo.f32 = -0.16f;
        GXWGFifo.f32 = -0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 1.0f;
    }
}
}

struct DivotRenderHandlers {
    void (*mpUnknown0)(int index);
    void (*mpUnknown4)(int index);
    void (*mpUnknown8)(DivotDrawView *pObject);
    void (*mpUnknownC)(DivotDrawView *pObject);
    void (*mpUnknown10)(DivotDrawView *pObject);
    void (*mpUnknown14)(int index);
    void (*mpUnknown18)(int index);
    void (*mpUnknown1C)(DivotDrawView *pObject);
};

static DivotRenderHandlers _DivotRender_aHandlers[] = {
    { DivotRenderLoadType, DivotRenderFreeType, DivotRenderPlace, DivotRenderRemove, DivotRenderRefresh, DivotRenderBegin, DivotRenderEnd, DivotRenderDrawOne },
};

extern "C" {
void DivotRenderLoadAll(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(_DivotRender_aHandlers) / sizeof(_DivotRender_aHandlers[0]); i++) {
        _DivotRender_aHandlers[i].mpUnknown0(i);
    }
}

void DivotRenderFreeAll(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(_DivotRender_aHandlers) / sizeof(_DivotRender_aHandlers[0]); i++) {
        _DivotRender_aHandlers[i].mpUnknown4(i);
    }
}

void DivotRenderOnPlace(DivotDrawView *pObject)
{
    _DivotRender_aHandlers[pObject->mUnknown68].mpUnknown8(pObject);
}

void DivotRenderOnRemove(DivotDrawView *pObject)
{
    _DivotRender_aHandlers[pObject->mUnknown68].mpUnknownC(pObject);
}

void DivotRenderOnRefresh(DivotDrawView *pObject)
{
    _DivotRender_aHandlers[pObject->mUnknown68].mpUnknown10(pObject);
}

void DivotRenderOnDraw(DivotDrawView *pObject)
{
    _DivotRender_aHandlers[pObject->mUnknown68].mpUnknown1C(pObject);
}

void DivotRenderBeginType(int index)
{
    _DivotRender_aHandlers[index].mpUnknown14(index);
}

void DivotRenderEndType(int index)
{
    _DivotRender_aHandlers[index].mpUnknown18(index);
}
}
