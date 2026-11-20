/* Low-level font rendering: per-string draw with optional shadow pass, GX state setup, palettes and textures. */

#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/os/OSCache.h>
#include "engine/Font.h"
#include "engine/SysSetLastErrorFunc.h"
#include "game/fn_801D2B7C.h"
#include "engine/llmatrix.h"
#include "engine/viewport.h"

typedef struct FontTexInfo_801CDB5C {
    unsigned short mWidth;
    unsigned short mHeight;
    int mUnk4;
    int mUnk8;
    void *mpImage;
    unsigned char mUnk10[0x10];
} FontTexInfo_801CDB5C;

extern unsigned short lbl_80383D20[16];
extern unsigned short lbl_80383D40[16];
extern GXTlutObj lbl_80383D60;
extern GXTlutObj lbl_80383D80;
extern FontRenderState_801CCA64 lbl_803E7600;
extern FontQuad_801CCA64 lbl_803E763C[];

/* The four corners of one glyph quad: positions, then texture coordinates. */
typedef struct FontVerts_801CD79C {
    float mPos[4][4];
    float mUV[4][4];
} FontVerts_801CD79C;

/* No GameCube code: nothing calls it, and SN ngcld -strip-unused drops the body, while its
   unsigned int-to-float bias stays in .rodata ahead of the pool of fn_801CD79C (evidence.tsv
   linker row 0x802AF4B0-0x802AF4B8). fn_801CD79C writes the same texel-to-UV division out. */
static float FontLLTexelToUV(unsigned int texel, float size)
{
    return texel / size;
}

static void fn_801CD79C(Font_801CCA64 *pFont, FontVerts_801CD79C *pVerts, FontQuad_801CCA64 *pQuad)
{
    float texWidth;
    float texHeight;
    float u;
    float v;
    float u0;
    float u1;
    float v0;
    float v1;

    pVerts->mPos[0][0] = pVerts->mPos[3][0] = pQuad->mX;
    pVerts->mPos[1][0] = pVerts->mPos[2][0] = pQuad->mX + pQuad->mWidth;
    pVerts->mPos[0][1] = pVerts->mPos[1][1] = pQuad->mY;
    pVerts->mPos[2][1] = pVerts->mPos[3][1] = pQuad->mY + pQuad->mHeight;
    u = pQuad->mU;
    texWidth = (int)pFont->mpTex->mWidth;
    u0 = u / texWidth;
    u1 = (pQuad->mU + pQuad->mWidth) / texWidth;
    v = pQuad->mV;
    texHeight = (int)pFont->mpTex->mHeight;
    v0 = v / texHeight;
    v1 = (pQuad->mV + pQuad->mHeight) / texHeight;
    pVerts->mUV[0][0] = pVerts->mUV[3][0] = u0;
    pVerts->mUV[1][0] = pVerts->mUV[2][0] = u1;
    pVerts->mUV[0][1] = pVerts->mUV[1][1] = v0;
    pVerts->mUV[2][1] = pVerts->mUV[3][1] = v1;
}

static int fn_801CD964(int state, Font_801CCA64 *pFont, FontQuad_801CCA64 *pQuads, unsigned int count,
                       FontColor_801CCA64 *pColor, int unused)
{
    FontVerts_801CD79C verts;
    GXColor color;
    unsigned int i;

    color.r = pColor->r * 255.0f;
    color.g = pColor->g * 255.0f;
    color.b = pColor->b * 255.0f;
    color.a = pColor->a * 255.0f;
    verts.mPos[0][2] = verts.mPos[1][2] = verts.mPos[2][2] = verts.mPos[3][2] = 0.0f;
    for (i = 0; i < count; i++) {
        fn_801CD79C(pFont, &verts, &pQuads[i]);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(verts.mPos[0][0], verts.mPos[0][1], verts.mPos[0][2]);
        GXColor4u8(color.r, color.g, color.b, color.a);
        GXTexCoord2f32(verts.mUV[0][0], verts.mUV[0][1]);
        GXPosition3f32(verts.mPos[1][0], verts.mPos[1][1], verts.mPos[1][2]);
        GXColor4u8(color.r, color.g, color.b, color.a);
        GXTexCoord2f32(verts.mUV[1][0], verts.mUV[1][1]);
        GXPosition3f32(verts.mPos[2][0], verts.mPos[2][1], verts.mPos[2][2]);
        GXColor4u8(color.r, color.g, color.b, color.a);
        GXTexCoord2f32(verts.mUV[2][0], verts.mUV[2][1]);
        GXPosition3f32(verts.mPos[3][0], verts.mPos[3][1], verts.mPos[3][2]);
        GXColor4u8(color.r, color.g, color.b, color.a);
        GXTexCoord2f32(verts.mUV[3][0], verts.mUV[3][1]);
    }
    return state;
}

int fn_801CDB5C(Font_801CCA64 *pFont, const char *pText, unsigned int flags, float maxWidth, float *pPos)
{
    FontQuad_801CCA64 *pQuads = lbl_803E763C;
    float mtx[4][4];
    unsigned int count;
    int state = 0;

    count = 0;
    fn_801CD3E4(pFont, pText, flags, maxWidth, pQuads, &count);
    if (count) {
        MatSetStack(VptGetMatrixStack());
        MatPush();
        MatTranslate(pPos);
        MatStore(mtx[0]);
        GXLoadPosMtxImm(mtx, 0);
        if (pFont->mpHeader->mFlags & 4) {
            lbl_803E7600.mFlags |= 0x40;
            GXLoadTlut(&lbl_80383D60, 0);
            GXLoadTexObj(pFont->mpTexObj, 0);
            state = fn_801CD964(0, pFont, pQuads, count, &lbl_803E7600.mShadowColor, 0);
            GXLoadTlut(&lbl_80383D80, 0);
            GXLoadTexObj(pFont->mpTexObj, 0);
            fn_801CD964(state, pFont, pQuads, count, &lbl_803E7600.mColor, 0);
        } else {
            GXLoadTexObj(pFont->mpTexObj, 0);
            if (lbl_803E7600.mFlags & 0x10) {
                MatPush();
                MatTranslate(lbl_803E7600.mShadowOffset);
                MatStore(mtx[0]);
                GXLoadPosMtxImm(mtx, 0);
                state = fn_801CD964(0, pFont, pQuads, count, &lbl_803E7600.mShadowColor, 0);
                MatPop();
                MatStore(mtx[0]);
                GXLoadPosMtxImm(mtx, 0);
            }
            fn_801CD964(state, pFont, pQuads, count, &lbl_803E7600.mColor, 0);
        }
        MatPop();
        SysSetLastErrorFunc(0);
    }
    return 0;
}

void fn_801CDD18(void)
{
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(11, 1);
    GXSetVtxDesc(13, 1);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 1, 1, 2, 1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOp(0, 0);
    GXSetTevColorIn(0, 15, 15, 15, 10);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 0, 4, 60, 0, 125);
    GXSetCullMode(0);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 11, 1, 5, 0);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    GXSetBlendMode(1, 4, 5, 5);
    GXSetZCompLoc(0);
    GXSetZMode(0, 7, 0);
    GXSetAlphaCompare(4, 0, 0, 4, 0);
}

void fn_801CDE98(void **ppTlut0, void **ppTlut1, void **ppTlut2)
{
    unsigned int levels = 8;
    unsigned int i;
    unsigned int j;

    for (i = 0; i < levels; i++) {
        lbl_80383D20[i] = ((i * 0xFF / (levels - 1)) << 8) | 0xFF;
    }
    for (; i < 16; i++) {
        lbl_80383D20[i] = 0xFFFF;
    }
    DCFlushRange(lbl_80383D20, sizeof(lbl_80383D20));
    GXInitTlutObj(&lbl_80383D60, lbl_80383D20, 0, 16);
    for (i = 0; i < levels; i++) {
        lbl_80383D40[i] = 0;
    }
    for (j = 0; i < 16; i++, j++) {
        lbl_80383D40[i] = ((j * 0xFF / (levels - 1)) << 8) | 0xFF;
    }
    DCFlushRange(lbl_80383D40, sizeof(lbl_80383D40));
    GXInitTlutObj(&lbl_80383D80, lbl_80383D40, 0, 16);
}

void fn_801CDFE4(void *pTlut0, void *pTlut1, void *pTlut2)
{
}

void fn_801CDFE8(Font_801CCA64 *pFont, void *pTlut0, void *pTlut1, void *pTlut2, int a)
{
    FontTexInfo_801CDB5C info;

    info.mWidth = pFont->mpTex->mWidth;
    info.mHeight = pFont->mpTex->mHeight;
    info.mpImage = pFont->mpTex->mImage;
    DCFlushRange(info.mpImage, info.mWidth * info.mHeight * 2);
    pFont->mpTexObj = fn_801D2B7C(0x20, 0, 0);
    if (pFont->mpHeader->mFlags & 4) {
        GXInitTexObjCI(pFont->mpTexObj, info.mpImage, info.mWidth, info.mHeight, 8, 0, 0, 0, 0);
        GXInitTexObjLOD(pFont->mpTexObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    } else {
        GXInitTexObj(pFont->mpTexObj, info.mpImage, info.mWidth, info.mHeight, 0, 0, 0, 0);
        GXInitTexObjLOD(pFont->mpTexObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    }
}

void fn_801CE108(Font_801CCA64 *pFont)
{
    if (pFont->mpTexObj) {
        fn_801D2BD0(pFont->mpTexObj);
    }
}

void fn_801CE134(Font_801CCA64 *pFont)
{
}
