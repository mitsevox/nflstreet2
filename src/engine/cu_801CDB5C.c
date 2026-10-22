/* Low-level font rendering: per-string draw with optional shadow pass, GX state setup, palettes and textures. */

#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include "engine/cu_801CCA64.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"
#include "engine/cu_801D03D0.h"
#include "engine/cu_80227F14.h"

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

int fn_801CD964(int state, Font_801CCA64 *pFont, FontQuad_801CCA64 *pQuads, unsigned int count,
                FontColor_801CCA64 *pColor, int a);

int fn_801CDB5C(Font_801CCA64 *pFont, const char *pText, unsigned int flags, float maxWidth, float *pPos)
{
    FontQuad_801CCA64 *pQuads = lbl_803E763C;
    float mtx[4][4];
    unsigned int count;
    int state = 0;

    count = 0;
    fn_801CD3E4(pFont, pText, flags, maxWidth, pQuads, &count);
    if (count) {
        fn_801D0470(fn_80228668());
        fn_801D04C4();
        fn_801D0C58(pPos);
        fn_801D0F80(mtx[0]);
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
                fn_801D04C4();
                fn_801D0C58(lbl_803E7600.mShadowOffset);
                fn_801D0F80(mtx[0]);
                GXLoadPosMtxImm(mtx, 0);
                state = fn_801CD964(0, pFont, pQuads, count, &lbl_803E7600.mShadowColor, 0);
                fn_801D0544();
                fn_801D0F80(mtx[0]);
                GXLoadPosMtxImm(mtx, 0);
            }
            fn_801CD964(state, pFont, pQuads, count, &lbl_803E7600.mColor, 0);
        }
        fn_801D0544();
        fn_801F7BD4(0);
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
