#include <dolphin/gx/GXPixel.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>

extern "C" {
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0F80(Mtx44 m);
void fn_80210388(void);
int fn_80236EC0(int a);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_80252448(float *p);
void fn_802524D4(float *p);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);
}

static float lbl_803651E4[7];
static unsigned char lbl_803ECBE0;

extern "C" {
void fn_801981D8(void *p, int value)
{
    Mtx44 mtx;

    fn_80210388();
    fn_802525BC(0);
    fn_801D0508();
    fn_801D0F80(mtx);
    fn_8025251C(mtx, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 0, 1, 2, 2);
    GXSetNumTevStages(1);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    fn_802524D4(lbl_803651E4);
    lbl_803ECBE0 = fn_80236EC0(0);
}

void fn_8019831C(void *p, int value)
{
    Mtx44 mtx;

    fn_801D0544();
    fn_801D0F80(mtx);
    fn_8025251C(mtx, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    fn_80252448(lbl_803651E4);
    fn_80236EC0(lbl_803ECBE0);
}
}
