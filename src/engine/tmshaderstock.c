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

static void fn_80212D5C(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    fn_80213A38(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void fn_80212DAC(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    fn_80213A38(GX_TEVSTAGE0, GX_PASSCLR, 1);
}

static void fn_80212DFC(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    fn_80213A38(GX_TEVSTAGE0, GX_MODULATE, 1);
}

static void fn_80212E4C(TMShader_t *pShader)
{
    GXSetNumTexGens(2);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    fn_80213A38(GX_TEVSTAGE0, GX_REPLACE, 0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    fn_80213A38(GX_TEVSTAGE1, GX_DECAL, 0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_KONST, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
}

static void fn_80212F3C(TMShader_t *pShader)
{
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
}

static void fn_80212F88(TMShader_t *pShader)
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

static void fn_80213128(TMShader_t *pShader);

static void fn_80213054(TMRegistry_t *pLib)
{
    TMShader_t *pShader;

    TMShaderLibAddShader(pLib, &lbl_802F9C18, fn_80212D5C);
    TMShaderLibAddShader(pLib, &lbl_802F9C34, fn_80212DAC);
    TMShaderLibAddShader(pLib, &lbl_802F9C80, fn_80212DFC);
    TMShaderLibAddShader(pLib, &lbl_802F9CF4, fn_80212E4C);
    TMShaderLibAddShader(pLib, &lbl_802F9D38, fn_80212F88);
    TMShaderLibAddShader(pLib, &lbl_802F9C50, fn_80212F3C);
    pShader = TMShaderLibAddShader(pLib, &lbl_802F9CB0, fn_80212DFC);
    TMShaderSetUnbindFunc(pShader, fn_80213128);
}

static void fn_80213128(TMShader_t *pShader)
{
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
}

void fn_80213160(void)
{
    TMShaderNew(&lbl_8039B55C, &lbl_802F9C18);
    TMShaderSetBindFunc(&lbl_8039B55C, fn_80212D5C);
    TMShaderLibSetNullShader(&lbl_8039B55C);
    TMShaderLibAlloc(&lbl_8039B54C, 16);
    fn_80213054(&lbl_8039B54C);
    TMShaderLibRegister("stock", &lbl_8039B54C);
}

void fn_802131D8(void)
{
    TMShaderLibFree(&lbl_8039B54C);
    TMShaderDelete(&lbl_8039B55C);
    TMShaderLibSetNullShader(0);
}
