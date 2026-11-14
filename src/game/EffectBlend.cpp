/* Begins and ends the additive, fog-free GX state used while the in-game effects list draws its entries. */
#include <dolphin/gx/GXPixel.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>

extern "C" {
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0F80(Mtx44 m);
void TMRenderReset(void);
int fn_80236EC0(int a);
void GXSetNumChans(int a);
void GXSetChanCtrl(int a, int b, int c, int d, int e, int f, int g);
void GXSetProjectionv(float *p);
void GXGetProjectionv(float *p);
void GXLoadPosMtxImm(Mtx44 m, int a);
void GXSetCurrentMtx(int a);
}

static float _EffectBlend_afProjection[7];
static unsigned char _EffectBlend_bFog;

extern "C" {
void EffectBlendBegin(void *p, int value)
{
    Mtx44 mtx;

    TMRenderReset();
    GXSetCurrentMtx(0);
    fn_801D0508();
    fn_801D0F80(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 1, 2, 2);
    GXSetNumTevStages(1);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXGetProjectionv(_EffectBlend_afProjection);
    _EffectBlend_bFog = fn_80236EC0(0);
}

void EffectBlendEnd(void *p, int value)
{
    Mtx44 mtx;

    fn_801D0544();
    fn_801D0F80(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    GXSetProjectionv(_EffectBlend_afProjection);
    fn_80236EC0(_EffectBlend_bFog);
}
}
