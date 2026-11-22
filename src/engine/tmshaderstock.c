/* The TM renderer's built-in shaders: GX TEV setups for untextured, flat, one-texture,
   two-texture, replace and specular environment-map materials, registered at render start-up
   as the "stock" shader library together with the null shader. */

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include "engine/tmlib.h"

/* The stock shader definitions: name, constant allocation, then the parameters. */
static TMShaderDef_t _TMShaderStock_NullDef = { "NULL", 0, 0, 0 };
static TMShaderDef_t _TMShaderStock_FlatDef = { "Flat", 0, 0, 0 };
static TMShaderDef_t _TMShaderStock_ReplaceDef = { "Replace", 0, 0, 1, { { "base", 1, 0, 0 } } };
static TMShaderDef_t _TMShaderStock_OnePassDef = { "OnePass", 0, 0, 1, { { "base", 1, 0, 0 } } };
static TMShaderDef_t _TMShaderStock_OnePassTXDef = { "OnePassTX", 0, 0, 2, { { "base", 1, 0, 0 }, { "texxform", 6, 0, 0 } } };
static TMShaderDef_t _TMShaderStock_TwoPassDef = { "TwoPass", 0, 0, 2, { { "base", 1, 0, 0 }, { "over", 1, 1, 1 } } };
static TMShaderDef_t _TMShaderStock_SpecularEnvMapDef = { "SpecularEnvMap", 0, 0, 2, { { "base", 1, 0, 0 }, { "scale", 3, 0, 0 } } };

/* The stock shader library and the null shader. */
static TMRegistry_t _TMShaderStock_ShaderLib;
static TMShader_t _TMShaderStock_NullShader;

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

    TMShaderLibAddShader(pLib, &_TMShaderStock_NullDef, _TMShaderStockBind_Null);
    TMShaderLibAddShader(pLib, &_TMShaderStock_FlatDef, _TMShaderStockBind_Flat);
    TMShaderLibAddShader(pLib, &_TMShaderStock_OnePassDef, _TMShaderStockBind_OnePass);
    TMShaderLibAddShader(pLib, &_TMShaderStock_TwoPassDef, _TMShaderStockBind_TwoPass);
    TMShaderLibAddShader(pLib, &_TMShaderStock_SpecularEnvMapDef, _TMShaderStockBind_SpecularEnvMap);
    TMShaderLibAddShader(pLib, &_TMShaderStock_ReplaceDef, _TMShaderStockBind_Replace);
    pShader = TMShaderLibAddShader(pLib, &_TMShaderStock_OnePassTXDef, _TMShaderStockBind_OnePass);
    TMShaderSetUnbindFunc(pShader, _TMShaderStockBind_OnePassTXDef);
}

static void _TMShaderStockBind_OnePassTXDef(TMShader_t *pShader)
{
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
}

void TMShaderStockInit(void)
{
    TMShaderNew(&_TMShaderStock_NullShader, &_TMShaderStock_NullDef);
    TMShaderSetBindFunc(&_TMShaderStock_NullShader, _TMShaderStockBind_Null);
    TMShaderLibSetNullShader(&_TMShaderStock_NullShader);
    TMShaderLibAlloc(&_TMShaderStock_ShaderLib, 16);
    _TMShaderStockCreateShaders(&_TMShaderStock_ShaderLib);
    TMShaderLibRegister("stock", &_TMShaderStock_ShaderLib);
}

void TMShaderStockShutdown(void)
{
    TMShaderLibFree(&_TMShaderStock_ShaderLib);
    TMShaderDelete(&_TMShaderStock_NullShader);
    TMShaderLibSetNullShader(0);
}
