/* The TM renderer's built-in shaders: GX TEV setups for untextured, flat, one-texture,
   two-texture, replace and specular environment-map materials, registered at render start-up
   as the "stock" shader library together with the null shader. */

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include "engine/tmlib.h"

extern TMShaderDef_t lbl_802F9C18;
extern TMShaderDef_t lbl_802F9C34;
extern TMShaderDef_t lbl_802F9C50;
extern TMShaderDef_t lbl_802F9C80;
extern TMShaderDef_t lbl_802F9CB0;
extern TMShaderDef_t lbl_802F9CF4;
extern TMShaderDef_t lbl_802F9D38;
extern TMRegistry_t lbl_8039B54C;
extern TMShader_t lbl_8039B55C;

static void _TMShaderStockBind_Null(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void _TMShaderStockBind_Flat(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void _TMShaderStockBind_OnePass(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    TMTevSetTevOp(GX_TEVSTAGE0, GX_MODULATE, 1);
}

static void _TMShaderStockBind_TwoPass(TMShader_t *pShader)
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

static void _TMShaderStockBind_Replace(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
}

static void _TMShaderStockBind_SpecularEnvMap(TMShader_t *pShader)
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

static void _TMShaderStockBind_OnePassTXDef(TMShader_t *pShader);

static void _TMShaderStockCreateShaders(TMRegistry_t *pLib)
{
    TMShader_t *pShader;

    TMShaderLibAddShader(pLib, &lbl_802F9C18, _TMShaderStockBind_Null);
    TMShaderLibAddShader(pLib, &lbl_802F9C34, _TMShaderStockBind_Flat);
    TMShaderLibAddShader(pLib, &lbl_802F9C80, _TMShaderStockBind_OnePass);
    TMShaderLibAddShader(pLib, &lbl_802F9CF4, _TMShaderStockBind_TwoPass);
    TMShaderLibAddShader(pLib, &lbl_802F9D38, _TMShaderStockBind_SpecularEnvMap);
    TMShaderLibAddShader(pLib, &lbl_802F9C50, _TMShaderStockBind_Replace);
    pShader = TMShaderLibAddShader(pLib, &lbl_802F9CB0, _TMShaderStockBind_OnePass);
    TMShaderSetUnbindFunc(pShader, _TMShaderStockBind_OnePassTXDef);
}

static void _TMShaderStockBind_OnePassTXDef(TMShader_t *pShader)
{
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
}

void TMShaderStockInit(void)
{
    TMShaderNew(&lbl_8039B55C, &lbl_802F9C18);
    TMShaderSetBindFunc(&lbl_8039B55C, _TMShaderStockBind_Null);
    TMShaderLibSetNullShader(&lbl_8039B55C);
    TMShaderLibAlloc(&lbl_8039B54C, 16);
    _TMShaderStockCreateShaders(&lbl_8039B54C);
    TMShaderLibRegister("stock", &lbl_8039B54C);
}

void TMShaderStockShutdown(void)
{
    TMShaderLibFree(&lbl_8039B54C);
    TMShaderDelete(&lbl_8039B55C);
    TMShaderLibSetNullShader(0);
}
