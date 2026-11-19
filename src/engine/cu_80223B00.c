#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXDispList.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include "engine/MovieRcmpInfo.h"
#include <string.h>
#include "engine/Font.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* Partial source for the engine range 0x80223B00-0x80223FF4 (neutral file
   name): render set-up of the flag-2/flag-4 node path that keeps the
   small-data colours 0x803EBF68/0x803EBF6C. Functions without a body here
   keep their original bytes. */

extern GXColor lbl_803EBF68;
extern GXColor lbl_803EBF6C;
extern GXLightObj lbl_803E9880;

void TMRenderReset(void);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);

void fn_80223C4C(void)
{
    Color_80223C4C *pColor = fn_80220D34();
    GXColor MatColor = pColor->unk_20;
    GXColor LightColor = pColor->unk_24;

    GXSetChanMatColor(GX_COLOR0A0, MatColor);
    GXInitLightColor(&lbl_803E9880, LightColor);
    GXLoadLightObjImm(&lbl_803E9880, GX_LIGHT7);
    lbl_803EBF68 = MatColor;
    lbl_803EBF6C = LightColor;
}

void fn_80223CB8(Uint32 Flags)
{
    Int32 bColor = 1;
    Int32 bTex;

    if ((Flags & 3) == 2) {
        bColor = 0;
    }
    TMRenderReset();
    bTex = Flags & 2;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    LLUIGSetColorChannel(bColor);
    LLUIGSetTexturing(bTex);
    fn_80223C4C();
    if (Flags & 0x8000) {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    } else {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }
    GXSetCullMode((Flags & 4) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])MatGetCurMatrixPtr(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
}
