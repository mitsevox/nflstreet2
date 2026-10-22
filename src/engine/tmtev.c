#include <dolphin/gx/GXTev.h>
#include "engine/tmlib.h"

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
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        break;
    case GX_PASSCLR:
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, colorIn);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaIn);
        break;
    case GX_DECAL:
        GXSetTevColorIn(stage, colorIn, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaIn);
        break;
    case GX_BLEND:
        GXSetTevColorIn(stage, colorIn, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, alphaIn, GX_CA_ZERO);
        break;
    case GX_MODULATE:
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, colorIn, GX_CC_ZERO);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, alphaIn, GX_CA_ZERO);
        break;
    }
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, scale, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, scale, GX_TRUE, GX_TEVPREV);
}
