/* Draws text and its shadows with GX glyph quads, outline palettes and font textures. */

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

typedef struct FontTexInfo_t {
    unsigned short mWidth;
    unsigned short mHeight;
    int unk_0x4;
    int unk_0x8;
    void *mpImage;
    unsigned char unk_0x10[0x10];
} FontTexInfo_t;

static unsigned short _LLFontOutsideOutlinePal[16] __attribute__((aligned(32)));
static unsigned short _LLFontInsideOutlinePal[16] __attribute__((aligned(32)));
static GXTlutObj _LLFontOutsideOutlineObj __attribute__((aligned(32)));
static GXTlutObj _LLFontInsideOutlineObj __attribute__((aligned(32)));
extern FontRenderState_t Font_RenderState;
FontQuad_t _FontLLRenderMapScratch[355];

/* The four corners of one glyph quad: positions, then texture coordinates. */
typedef struct FontQuadVerts_t {
    float mPos[4][4];
    float mUV[4][4];
} FontQuadVerts_t;

/* FAKEMATCH: invented unused static; its body exists only for its unsigned int-to-float bias in .rodata */
static float _FontLLTexelToUV(unsigned int texel, float size)
{
    return texel / size;
}

static void _FontLLSetupGlyph(Font_t *pFont, FontQuadVerts_t *pVerts, FontQuad_t *pQuad)
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

/* FAKEMATCH: the four vertices go through a file-static inline helper; written inline the function does not match */
static inline void _FontLLSendQuad(FontQuadVerts_t *pVerts, GXColor *pColor)
{
    GXPosition3f32(pVerts->mPos[0][0], pVerts->mPos[0][1], pVerts->mPos[0][2]);
    GXColor4u8(pColor->r, pColor->g, pColor->b, pColor->a);
    GXTexCoord2f32(pVerts->mUV[0][0], pVerts->mUV[0][1]);
    GXPosition3f32(pVerts->mPos[1][0], pVerts->mPos[1][1], pVerts->mPos[1][2]);
    GXColor4u8(pColor->r, pColor->g, pColor->b, pColor->a);
    GXTexCoord2f32(pVerts->mUV[1][0], pVerts->mUV[1][1]);
    GXPosition3f32(pVerts->mPos[2][0], pVerts->mPos[2][1], pVerts->mPos[2][2]);
    GXColor4u8(pColor->r, pColor->g, pColor->b, pColor->a);
    GXTexCoord2f32(pVerts->mUV[2][0], pVerts->mUV[2][1]);
    GXPosition3f32(pVerts->mPos[3][0], pVerts->mPos[3][1], pVerts->mPos[3][2]);
    GXColor4u8(pColor->r, pColor->g, pColor->b, pColor->a);
    GXTexCoord2f32(pVerts->mUV[3][0], pVerts->mUV[3][1]);
}

static int _FontLLRender(int state, Font_t *pFont, FontQuad_t *pQuads, unsigned int count,
                       FontColor_t *pColor, int unused)
{
    FontQuadVerts_t verts;
    GXColor color;
    unsigned int i;

    color.r = pColor->r * 255.0f;
    color.g = pColor->g * 255.0f;
    color.b = pColor->b * 255.0f;
    color.a = pColor->a * 255.0f;
    verts.mPos[3][2] = verts.mPos[2][2] = verts.mPos[1][2] = verts.mPos[0][2] = 0.0f;
    for (i = 0; i < count; i++) {
        _FontLLSetupGlyph(pFont, &verts, &pQuads[i]);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        _FontLLSendQuad(&verts, &color);
    }
    return state;
}

int FontLLRenderText(Font_t *pFont, const char *pText, unsigned int flags, float maxWidth, float *pPos)
{
    FontQuad_t *pQuads = _FontLLRenderMapScratch;
    float mtx[4][4];
    unsigned int count;
    int state = 0;

    count = 0;
    FontDrawText(pFont, pText, flags, maxWidth, pQuads, &count);
    if (count) {
        MatSetStack(VptGetMatrixStack());
        MatPush();
        MatTranslate(pPos);
        MatStore(mtx[0]);
        GXLoadPosMtxImm(mtx, 0);
        if (pFont->mpHeader->mFlags & 4) {
            Font_RenderState.mFlags |= 0x40;
            GXLoadTlut(&_LLFontOutsideOutlineObj, 0);
            GXLoadTexObj(pFont->mpTexObj, 0);
            state = _FontLLRender(0, pFont, pQuads, count, &Font_RenderState.mShadowColor, 0);
            GXLoadTlut(&_LLFontInsideOutlineObj, 0);
            GXLoadTexObj(pFont->mpTexObj, 0);
            _FontLLRender(state, pFont, pQuads, count, &Font_RenderState.mColor, 0);
        } else {
            GXLoadTexObj(pFont->mpTexObj, 0);
            if (Font_RenderState.mFlags & 0x10) {
                MatPush();
                MatTranslate(Font_RenderState.mShadowOffset);
                MatStore(mtx[0]);
                GXLoadPosMtxImm(mtx, 0);
                state = _FontLLRender(0, pFont, pQuads, count, &Font_RenderState.mShadowColor, 0);
                MatPop();
                MatStore(mtx[0]);
                GXLoadPosMtxImm(mtx, 0);
            }
            _FontLLRender(state, pFont, pQuads, count, &Font_RenderState.mColor, 0);
        }
        MatPop();
        SysSetLastErrorFunc(0);
    }
    return 0;
}

void FontLLRenderBegin(void)
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

void FontLLUploadPalettes(void **ppTlut0, void **ppTlut1, void **ppTlut2)
{
    unsigned int levels = 8;
    unsigned int i;
    unsigned int j;

    for (i = 0; i < levels; i++) {
        _LLFontOutsideOutlinePal[i] = ((i * 0xFF / (levels - 1)) << 8) | 0xFF;
    }
    for (; i < 16; i++) {
        _LLFontOutsideOutlinePal[i] = 0xFFFF;
    }
    DCFlushRange(_LLFontOutsideOutlinePal, sizeof(_LLFontOutsideOutlinePal));
    GXInitTlutObj(&_LLFontOutsideOutlineObj, _LLFontOutsideOutlinePal, 0, 16);
    for (i = 0; i < levels; i++) {
        _LLFontInsideOutlinePal[i] = 0;
    }
    for (j = 0; i < 16; i++, j++) {
        _LLFontInsideOutlinePal[i] = ((j * 0xFF / (levels - 1)) << 8) | 0xFF;
    }
    DCFlushRange(_LLFontInsideOutlinePal, sizeof(_LLFontInsideOutlinePal));
    GXInitTlutObj(&_LLFontInsideOutlineObj, _LLFontInsideOutlinePal, 0, 16);
}

void FontLLReleasePalettes(void *pTlut0, void *pTlut1, void *pTlut2)
{
}

void FontLLUploadTextures(Font_t *pFont, void *pTlut0, void *pTlut1, void *pTlut2, int a)
{
    FontTexInfo_t info;

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

void FontLLReleaseTextures(Font_t *pFont)
{
    if (pFont->mpTexObj) {
        fn_801D2BD0(pFont->mpTexObj);
    }
}

void FontLLCreateFont(Font_t *pFont)
{
}
