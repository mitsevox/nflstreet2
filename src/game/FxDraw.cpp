/* Effect drawing helpers: begin and end hooks around the particle pass, loading and freeing the
   animated particle textures, full-screen colour tints and the orange ground pulse quad. */
#include <dolphin/gx/GXPixel.h>
#include "engine/viewport.h"
#include "game/Vector_80039F5C.h"
#include <dolphin/gx/GXTexture.h>
#include "game/fn_801D2B7C.h"
#include "engine/animTexLib.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

extern "C" {
int fn_800A34F8(int index);
void MatMakeUnitMatrix(Mtx44 m);
void MatPush(void);
void MatPushUnit(void);
void MatPop(void);
void MatStore(Mtx44 m);
void *fn_801D2BB0(int a, int size, int c, int d);
void ResLoadToBuffer(void *a, int b, void *p);
int ResGetSize(void *a, int b);
void TMXform(int a, void *b);
void GXSetChanAmbColor(int a, GXColor color);
void GXSetChanMatColor(int a, GXColor color);
void GXSetNumChans(int a);
void GXSetChanCtrl(int a, int b, int c, int d, int e, int f, int g);
void GXSetProjection(Mtx44 m, int a);
void GXSetProjectionv(float *p);
void GXGetProjectionv(float *p);
void GXLoadPosMtxImm(Mtx44 m, int a);
void GXSetCurrentMtx(int a);
void GXSetClipMode(int a);

void FxParticleDrawBegin(void)
{
    MatPushUnit();
    TMXform(0, 0);
    MatPop();
}

void FxParticleDrawEnd(void)
{
}

void FxAnimTexLoadAll(AnimTexFile_t *pEntries, AnimTex_t **pValues, void *pData)
{
    unsigned char i;

    for (i = 0; i <= 7; i++) {
        pEntries[i].mData = pData;
        if (fn_800A34F8(i)) {
            void *pBuffer = fn_801D2BB0(1, ResGetSize(pEntries[i].mData, pEntries[i].mIndex), 4, 0);

            ResLoadToBuffer(pEntries[i].mData, pEntries[i].mIndex, pBuffer);
            pValues[i] = AnimTexLoadResource(&pEntries[i], 0);
            fn_801D2BD0(pBuffer);
        }
    }
}

void FxAnimTexFreeAll(AnimTex_t **pValues)
{
    unsigned char i;

    for (i = 0; i <= 7; i++) {
        if (fn_800A34F8(i)) {
            AnimTexFree(pValues[i]);
        }
    }
}

void FxTintDraw(unsigned int color, int mode, float alpha)
{
    Mtx44 view;
    Mtx44 projection;
    GXColor fill = {0, 0, 0, 255};
    GXColor black = {0, 0, 0, 0};
    unsigned int r;
    unsigned int g;
    unsigned int b;

    r = (color & 0xFF) * 2;
    g = ((color >> 8) & 0xFF) * 2;
    b = ((color >> 16) & 0xFF) * 2;
    fill.r = r > 255 ? 255 : r;
    fill.g = g > 255 ? 255 : g;
    fill.b = b > 255 ? 255 : b;
    fill.a = alpha * 255.0f;
    GXSetNumChans(1);
    GXSetChanAmbColor(4, black);
    GXSetChanMatColor(4, fill);
    GXSetChanCtrl(4, 0, 0, 0, 1, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 4);
    GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetClipMode(1);
    switch (mode) {
    case 1:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_SRCALPHA, GX_LO_NOOP);
        break;
    case 0:
    default:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        break;
    }
    {
        float saved[7];

        GXGetProjectionv(saved);
        C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, 1.0f, 2.0f);
        GXSetProjection(projection, 1);
        MatPush();
        MatMakeUnitMatrix(view);
        GXLoadPosMtxImm(view, 0);
        GXSetCurrentMtx(0);
        MatPop();
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, -1.0f);
        GXPosition3f32(640.0f, 0.0f, -1.0f);
        GXPosition3f32(0.0f, 448.0f, -1.0f);
        GXPosition3f32(640.0f, 448.0f, -1.0f);
        GXSetProjectionv(saved);
    }
    MatStore(view);
    GXLoadPosMtxImm(view, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetClipMode(0);
}

void FxTintDrawAlpha(int unused, unsigned int color, float alpha)
{
    FxTintDraw(color, 0, alpha);
}

void FxTintDrawSrcColor(int unused, unsigned int color, float alpha)
{
    FxTintDraw(color, 1, alpha);
}

void TMRenderReset(void);
void TMRenderSetBlendMode(int mode);
void MatSetStack(int stack);
void MatCatSlot(int slot);
Mtx44Ptr MatGetCurMatrixPtr(void);
void fn_8022765C(void *pOut, void *pA, void *pB);
}

/* The ground pulse texture: 0x4C bytes of .bss, of which the draw code uses only the texture
   object at +0x20 and the palette object at +0x40. No GameCube code initialises them. */
struct FxDrawTexture_t {
    unsigned char mUnknown0[0x20];
    GXTexObj mTexObj;
    GXTlutObj mTlutObj;
};

/* 8 bytes of .sdata: the draw code reads only byte +0, which selects the palette load when
   it is 1. */
struct FxDrawTextureInfo_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1[7];
};

static FxDrawTextureInfo_t _FxDraw_GroundPulseTextureInfo = {0};
static FxDrawTexture_t _FxDraw_GroundPulseTexture;

static float _FxDraw_aGroundPulseUVs[4][2] = {
    {0.0f, 1.0f},
    {1.0f, 1.0f},
    {1.0f, 0.0f},
    {0.0f, 0.0f},
};

static inline float _FxRemap(float x, float x0, float x1, float y0, float y1)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}

extern "C" {
void FxGroundPulseDraw(float scale, void *position)
{
    Vector_80039F5C offset;
    Vector_80039F5C vertex;
    unsigned char color[3] = {255, 125, 25};
    Vector_80039F5C corners[4] = {
        {-3.0f, 3.0f, 0.15f}, {-3.0f, -3.0f, 0.15f},
        {3.0f, -3.0f, 0.15f}, {3.0f, 3.0f, 0.15f}
    };
    TMRenderReset();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    TMRenderSetBlendMode(6);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
    MatSetStack(VptGetMatrixStack());
    MatPushUnit();
    MatCatSlot(3);
    GXLoadPosMtxImm(MatGetCurMatrixPtr(), 0);
    MatPop();
    if (_FxDraw_GroundPulseTextureInfo.mUnknown0 == 1)
        GXLoadTlut(&_FxDraw_GroundPulseTexture.mTlutObj, 0);
    GXLoadTexObj(&_FxDraw_GroundPulseTexture.mTexObj, GX_TEXMAP0);
    unsigned char alpha = (unsigned char)_FxRemap(scale, 0.05f, 3.0f, 255.0f, 0.0f);
    for (unsigned char i = 0; i <= 3; ++i) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        for (unsigned char j = 0; j <= 3; ++j) {
            offset.mX = corners[j].mX * scale;
            offset.mY = corners[j].mY * scale;
            fn_8022765C(&vertex, position, &offset);
            GXPosition3f32(vertex.mX, vertex.mY, vertex.mZ);
            GXColor4u8(color[0], color[1], color[2], alpha);
            GXTexCoord2f32(_FxDraw_aGroundPulseUVs[j][0], _FxDraw_aGroundPulseUVs[j][1]);
        }
    }
    TMRenderSetBlendMode(1);
}
}
