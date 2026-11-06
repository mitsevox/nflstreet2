/* The TM renderer's built-in shaders: GX TEV setups for untextured, flat, one-texture,
   two-texture, replace and specular environment-map materials, registered at render start-up
   as the "stock" shader library together with the null shader. */

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include "engine/tmlib.h"

extern ShaderDef_80211638 lbl_802F9C18;
extern ShaderDef_80211638 lbl_802F9C34;
extern ShaderDef_80211638 lbl_802F9C50;
extern ShaderDef_80211638 lbl_802F9C80;
extern ShaderDef_80211638 lbl_802F9CB0;
extern ShaderDef_80211638 lbl_802F9CF4;
extern ShaderDef_80211638 lbl_802F9D38;
extern Registry_8021283C lbl_8039B54C;
extern Shader_80211638 lbl_8039B55C;

static void _TMShaderStockBind_Null(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void _TMShaderStockBind_Flat(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void _TMShaderStockBind_OnePass(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_MODULATE, 1);
}

static void _TMShaderStockBind_TwoPass(Shader_80211638 *pShader)
{
    GXSetNumTexGens(2);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_REPLACE, 0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    TMTevSetTevOp(GX_TEVSTAGE1, GX_DECAL, 0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_KONST, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
}

static void _TMShaderStockBind_Replace(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
}

static void _TMShaderStockBind_SpecularEnvMap(Shader_80211638 *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0_A);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

static void _TMShaderStockBind_OnePassTXDef(Shader_80211638 *pShader);

static void _TMShaderStockCreateShaders(Registry_8021283C *pLib)
{
    Shader_80211638 *pShader;

    fn_80211860(pLib, &lbl_802F9C18, _TMShaderStockBind_Null);
    fn_80211860(pLib, &lbl_802F9C34, _TMShaderStockBind_Flat);
    fn_80211860(pLib, &lbl_802F9C80, _TMShaderStockBind_OnePass);
    fn_80211860(pLib, &lbl_802F9CF4, _TMShaderStockBind_TwoPass);
    fn_80211860(pLib, &lbl_802F9D38, _TMShaderStockBind_SpecularEnvMap);
    fn_80211860(pLib, &lbl_802F9C50, _TMShaderStockBind_Replace);
    pShader = fn_80211860(pLib, &lbl_802F9CB0, _TMShaderStockBind_OnePass);
    fn_80211764(pShader, _TMShaderStockBind_OnePassTXDef);
}

static void _TMShaderStockBind_OnePassTXDef(Shader_80211638 *pShader)
{
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
}

void TMShaderStockInit(void)
{
    fn_80211638(&lbl_8039B55C, &lbl_802F9C18);
    fn_8021175C(&lbl_8039B55C, _TMShaderStockBind_Null);
    fn_802119BC(&lbl_8039B55C);
    fn_802117C8(&lbl_8039B54C, 16);
    _TMShaderStockCreateShaders(&lbl_8039B54C);
    fn_80211928("stock", &lbl_8039B54C);
}

void TMShaderStockShutdown(void)
{
    fn_802117F0(&lbl_8039B54C);
    fn_80211730(&lbl_8039B55C);
    fn_802119BC(0);
}
