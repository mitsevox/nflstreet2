#include <dolphin/gx/GXTev.h>
#include "engine/tmlib.h"

extern void fn_80251690(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
extern void fn_802516D4(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
extern void fn_80251718(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
extern void fn_80251780(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);

void fn_80213A38(GXTevStageID stage, GXTevMode mode, GXTevScale scale)
{
    GXTevColorArg colorIn;
    GXTevAlphaArg alphaIn;

    if (stage == GX_TEVSTAGE0) {
        colorIn = GX_CC_RASC;
        alphaIn = GX_CA_RASA;
    } else {
        colorIn = GX_CC_CPREV;
        alphaIn = GX_CA_APREV;
    }
    switch (mode) {
    case GX_REPLACE:
        fn_80251690(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        fn_802516D4(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        break;
    case GX_PASSCLR:
        fn_80251690(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, colorIn);
        fn_802516D4(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaIn);
        break;
    case GX_DECAL:
        fn_80251690(stage, colorIn, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        fn_802516D4(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaIn);
        break;
    case GX_BLEND:
        fn_80251690(stage, colorIn, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
        fn_802516D4(stage, GX_CA_ZERO, GX_CA_TEXA, alphaIn, GX_CA_ZERO);
        break;
    case GX_MODULATE:
        fn_80251690(stage, GX_CC_ZERO, GX_CC_TEXC, colorIn, GX_CC_ZERO);
        fn_802516D4(stage, GX_CA_ZERO, GX_CA_TEXA, alphaIn, GX_CA_ZERO);
        break;
    }
    fn_80251718(stage, GX_TEV_ADD, GX_TB_ZERO, scale, GX_TRUE, GX_TEVPREV);
    fn_80251780(stage, GX_TEV_ADD, GX_TB_ZERO, scale, GX_TRUE, GX_TEVPREV);
}
