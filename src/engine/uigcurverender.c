/* Renders the curved ribbons in UI screens: sets the GX material and vertex state,
   batches the generated strip vertices and writes their colours and texture coordinates. */

#include <dolphin/gx/GXVert.h>
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
#include "engine/TMRenderReset.h"
#include "engine/cu_8021A438.h"
#include "engine/uigcurve.h"
#include "engine/uigcurverender.h"
#include "engine/viewport.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"



GXColor _UIGCurve_cMaterialColor = {0x12, 0x34, 0x56, 0x78};
GXColor _UIGCurve_cLightColor = {0x12, 0x34, 0x56, 0x78};
extern GXLightObj lbl_803E9880;


void _UIGCurveSetupRender(Uint32 Flags);
void _UIGCurveEmitStrip(UIGNode_t *pNode, UIGCurvePoint_t *pPoints, UIGCurvePoint_t *pCoord,
                 UIGCurvePoint_t offset, int first, int count, int unused);

void UIGCurveRender(UIGNode_t *pNode, Int32 item)
{
    UIGCurvePoint_t points[200];
    UIGCurvePoint_t coord;
    int texture = 0;
    int first;
    int total;
    int count;

    _UIGCurveSetupRender(pNode->Flags);
    if (pNode->Flags & 2) {
        if (item == 0) return;
        LLUIGSetClamp(0, 0, (Texture_t *)item);
        texture = LLUIGTexNodeRegisterObj((Texture_t *)item);
    }
    if (pNode->Flags & 0x8000) {
        UIGDispListCall(&pNode->u.List);
    } else {
        UIGCurveBuildStrip(3, pNode->u.c.unk_18, pNode->u.c.unk_38, points, pNode->u.c.unk_10);
        total = pNode->u.c.unk_10 * 2;
        coord.mX = 0.0f;
        coord.mY = 0.0f;
        for (first = 0; first < total; first += 8) {
            count = total - first;
            if (count > 10) count = 10;
            _UIGCurveEmitStrip(pNode, points, &coord, pNode->u.c.unk_30, first, count, 0);
        }
    }
    if (texture != 0) {
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    }
}

void _UIGCurveSetMaterialColors(void)
{
    UIGMaterialColorState_t *pColor = fn_80220D34();
    GXColor MatColor = pColor->mMaterialColor;
    GXColor LightColor = pColor->mLightColor;

    GXSetChanMatColor(GX_COLOR0A0, MatColor);
    GXInitLightColor(&lbl_803E9880, LightColor);
    GXLoadLightObjImm(&lbl_803E9880, GX_LIGHT7);
    _UIGCurve_cMaterialColor = MatColor;
    _UIGCurve_cLightColor = LightColor;
}

void _UIGCurveSetupRender(Uint32 Flags)
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
    _UIGCurveSetMaterialColors();
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

typedef struct UIGCurvePalette_t {
    Uint8 mCount;
    Uint8 unk_01[3];
    GXColor mColors[1];
} UIGCurvePalette_t;

void _UIGCurveEmitStrip(UIGNode_t *pNode, UIGCurvePoint_t *pPoints, UIGCurvePoint_t *pCoord,
                 UIGCurvePoint_t offset, int first, int count, int unused)
{
    int bColor = 0;
    int bTex;
    GXColor color;
    UIGCurvePalette_t *pPalette;
    int i;
    Uint8 red, green, blue, alpha;

    // FAKEMATCH: read the low flag byte for bit0 and texturing; the target mixes byte and halfword flag accesses.
    if (((Uint8)pNode->Flags & 1) || !(pNode->Flags & 2)) bColor = 1;
    bTex = (Uint8)pNode->Flags & 2;
    memcpy(&color, pNode->u.c.unk_14, sizeof(color));
    if (pNode->unk_0A != -1 && pNode->unk_08 != -1) {
        pPalette = (UIGCurvePalette_t *)fn_80220B4C(pNode->unk_0A, pNode->unk_08);
        if (pPalette != 0) {
            if (color.r > pPalette->mCount) color.r = pPalette->mCount - 1;
            color = pPalette->mColors[color.r];
        }
    }
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, count);
    for (i = first; i < first + count; i++) {
        red = color.r; green = color.g; blue = color.b; alpha = color.a;
        GXPosition3f32(pPoints[i].mX, pPoints[i].mY, 0.0f);
        if (bColor) GXColor4u8(red, green, blue, alpha);
        else GXColor4u8(255, 255, 255, alpha);
        if (bTex) {
            GXTexCoord2f32(pCoord->mX + offset.mX, pCoord->mY + offset.mY);
            pCoord->mX += 1.0f;
            if (!(pCoord->mX <= 1.0f)) {
                pCoord->mX = 0.0f;
                pCoord->mY += 1.0f;
                if (!(pCoord->mY <= 1.0f)) pCoord->mY = 0.0f;
            }
        }
    }
}
