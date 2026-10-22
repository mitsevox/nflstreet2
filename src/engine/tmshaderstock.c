#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include "engine/tmlib.h"

extern void fn_80251690(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
extern void fn_802516D4(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
extern void fn_80251718(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
extern void fn_80251780(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);

extern ShaderDef_80211638 lbl_802F9C18;
extern ShaderDef_80211638 lbl_802F9C34;
extern ShaderDef_80211638 lbl_802F9C50;
extern ShaderDef_80211638 lbl_802F9C80;
extern ShaderDef_80211638 lbl_802F9CB0;
extern ShaderDef_80211638 lbl_802F9CF4;
extern ShaderDef_80211638 lbl_802F9D38;
extern Registry_8021283C lbl_8039B54C;
extern Shader_80211638 lbl_8039B55C;

static void fn_80212D5C(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    fn_80213A38(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void fn_80212DAC(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    fn_80213A38(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void fn_80212DFC(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    fn_80213A38(GX_TEVSTAGE0, GX_MODULATE, 1);
}

static void fn_80212E4C(Shader_80211638 *pShader)
{
    GXSetNumTexGens(2);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    fn_80213A38(GX_TEVSTAGE0, GX_REPLACE, 0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    fn_80213A38(GX_TEVSTAGE1, GX_DECAL, 0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    fn_80251690(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    fn_80251718(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    fn_802516D4(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_KONST, GX_CA_RASA, GX_CA_ZERO);
    fn_80251780(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
}

static void fn_80212F3C(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
}

static void fn_80212F88(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0_A);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    fn_80251690(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    fn_80251690(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    fn_80251718(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    fn_802516D4(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    fn_80251780(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

static void fn_80213128(Shader_80211638 *pShader);

static void fn_80213054(Registry_8021283C *pLib)
{
    Shader_80211638 *pShader;

    fn_80211860(pLib, &lbl_802F9C18, fn_80212D5C);
    fn_80211860(pLib, &lbl_802F9C34, fn_80212DAC);
    fn_80211860(pLib, &lbl_802F9C80, fn_80212DFC);
    fn_80211860(pLib, &lbl_802F9CF4, fn_80212E4C);
    fn_80211860(pLib, &lbl_802F9D38, fn_80212F88);
    fn_80211860(pLib, &lbl_802F9C50, fn_80212F3C);
    pShader = fn_80211860(pLib, &lbl_802F9CB0, fn_80212DFC);
    fn_80211764(pShader, fn_80213128);
}

static void fn_80213128(Shader_80211638 *pShader)
{
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
}

void fn_80213160(void)
{
    fn_80211638(&lbl_8039B55C, &lbl_802F9C18);
    fn_8021175C(&lbl_8039B55C, fn_80212D5C);
    fn_802119BC(&lbl_8039B55C);
    fn_802117C8(&lbl_8039B54C, 16);
    fn_80213054(&lbl_8039B54C);
    fn_80211928("stock", &lbl_8039B54C);
}

void fn_802131D8(void)
{
    fn_802117F0(&lbl_8039B54C);
    fn_80211730(&lbl_8039B55C);
    fn_802119BC(0);
}
