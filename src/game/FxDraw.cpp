/* Effect drawing helpers: begin and end hooks around the particle pass, loading and freeing the
   animated particle textures, and full-screen colour tints. */
#include <dolphin/gx/GXPixel.h>
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
void fn_801D03D0(Mtx44 m);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0F80(Mtx44 m);
void *fn_801D2BB0(int a, int size, int c, int d);
void ResLoadToBuffer(void *a, int b, void *p);
int ResGetSize(void *a, int b);
void TMXform(int a, void *b);
void fn_8024FA68(int a, GXColor color);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void GXSetProjection(Mtx44 m, int a);
void GXSetProjectionv(float *p);
void GXGetProjectionv(float *p);
void GXLoadPosMtxImm(Mtx44 m, int a);
void GXSetCurrentMtx(int a);
void GXSetClipMode(int a);

void FxParticleDrawBegin(void)
{
    fn_801D0508();
    TMXform(0, 0);
    fn_801D0544();
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
    fn_8024FC48(1);
    fn_8024FA68(4, black);
    fn_8024FB58(4, fill);
    fn_8024FC84(4, 0, 0, 0, 1, 0, 2);
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
        fn_801D04C4();
        fn_801D03D0(view);
        GXLoadPosMtxImm(view, 0);
        GXSetCurrentMtx(0);
        fn_801D0544();
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, -1.0f);
        GXPosition3f32(640.0f, 0.0f, -1.0f);
        GXPosition3f32(0.0f, 448.0f, -1.0f);
        GXPosition3f32(640.0f, 448.0f, -1.0f);
        GXSetProjectionv(saved);
    }
    fn_801D0F80(view);
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
}
