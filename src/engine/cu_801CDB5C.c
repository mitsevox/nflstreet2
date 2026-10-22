/* Low-level font rendering: per-string draw with optional shadow pass, GX state setup, palettes and textures. */

#include "engine/cu_801CCA64.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

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
extern unsigned char lbl_80383D60[];
extern unsigned char lbl_80383D80[];
extern FontRenderState_801CCA64 lbl_803E7600;
extern FontQuad_801CCA64 lbl_803E763C[];

int fn_801CD964(int state, Font_801CCA64 *pFont, FontQuad_801CCA64 *pQuads, unsigned int count,
                FontColor_801CCA64 *pColor, int a);
void fn_801D0470(unsigned int index);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(float *pPos);
void fn_801D0F80(float *pMatrix);
int fn_80228668(void);
void fn_80239CEC(void *addr, unsigned int size);
void fn_8024CB90(int attr, int type);
void fn_8024D418(void);
void fn_8024D450(int fmt, int attr, int cnt, int type, int frac);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int n);
void fn_8024EB28(int mode);
void fn_8024FC48(int n);
void fn_8024FC84(int chan, int enable, int amb, int mat, int lights, int diff, int attn);
void fn_8024FFC4(void *pObj, void *pImage, int width, int height, int format, int wrapS, int wrapT, int mipmap);
void fn_80250210(void *pObj, void *pImage, int width, int height, int format, int wrapS, int wrapT, int mipmap,
                 int tlut);
void fn_80250258(void *pObj, int minFilter, int magFilter, float minLod, float maxLod, float lodBias, int clamp,
                 int edgeLod, int aniso);
void fn_802505A8(void *pObj, int map);
void fn_802505FC(void *pObj, void *pLut, int format, int entries);
void fn_80250654(void *pObj, int name);
void fn_80251604(int stage, int mode);
void fn_80251690(int stage, int a, int b, int c, int d);
void fn_80251718(int stage, int op, int bias, int scale, int clamp, int reg);
void fn_80251A58(int a, int b, int op, int c, int d);
void fn_80251B28(int stage, int coord, int map, int color);
void fn_80251CC4(int n);
void fn_80252034(int type, int src, int dst, int op);
void fn_802520E0(int enable, int func, int update);
void fn_80252114(int enable);
void fn_8025251C(float (*pMtx)[4], int id);

int fn_801CDB5C(Font_801CCA64 *pFont, const char *pText, unsigned int flags, float maxWidth, float *pPos)
{
    FontQuad_801CCA64 *pQuads = lbl_803E763C;
    float mtx[4][4];
    unsigned int count;
    int state = 0;

    count = state;
    fn_801CD3E4(pFont, pText, flags, maxWidth, pQuads, &count);
    if (count) {
        fn_801D0470(fn_80228668());
        fn_801D04C4();
        fn_801D0C58(pPos);
        fn_801D0F80(mtx[0]);
        fn_8025251C(mtx, 0);
        if (pFont->mpHeader->mFlags & 4) {
            lbl_803E7600.mFlags |= 0x40;
            fn_80250654(lbl_80383D60, 0);
            fn_802505A8(pFont->mpTexObj, 0);
            state = fn_801CD964(0, pFont, pQuads, count, &lbl_803E7600.mShadowColor, 0);
            fn_80250654(lbl_80383D80, 0);
            fn_802505A8(pFont->mpTexObj, 0);
            fn_801CD964(state, pFont, pQuads, count, &lbl_803E7600.mColor, 0);
        } else {
            fn_802505A8(pFont->mpTexObj, 0);
            if (lbl_803E7600.mFlags & 0x10) {
                fn_801D04C4();
                fn_801D0C58(lbl_803E7600.mShadowOffset);
                fn_801D0F80(mtx[0]);
                fn_8025251C(mtx, 0);
                state = fn_801CD964(0, pFont, pQuads, count, &lbl_803E7600.mShadowColor, 0);
                fn_801D0544();
                fn_801D0F80(mtx[0]);
                fn_8025251C(mtx, 0);
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
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024CB90(11, 1);
    fn_8024CB90(13, 1);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 1, 2, 1);
    fn_80251CC4(1);
    fn_80251B28(0, 0, 0, 4);
    fn_80251604(0, 0);
    fn_80251690(0, 15, 15, 15, 10);
    fn_80251718(0, 0, 0, 0, 1, 0);
    fn_8024DF64(1);
    fn_8024DCE4(0, 0, 4, 60, 0, 125);
    fn_8024EB28(0);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024D450(0, 11, 1, 5, 0);
    fn_8024D450(0, 13, 1, 4, 0);
    fn_80252034(1, 4, 5, 5);
    fn_80252114(0);
    fn_802520E0(0, 7, 0);
    fn_80251A58(4, 0, 0, 4, 0);
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
    fn_80239CEC(lbl_80383D20, sizeof(lbl_80383D20));
    fn_802505FC(lbl_80383D60, lbl_80383D20, 0, 16);
    for (i = 0; i < levels; i++) {
        lbl_80383D40[i] = 0;
    }
    for (j = 0; i < 16; i++, j++) {
        lbl_80383D40[i] = ((j * 0xFF / (levels - 1)) << 8) | 0xFF;
    }
    fn_80239CEC(lbl_80383D40, sizeof(lbl_80383D40));
    fn_802505FC(lbl_80383D80, lbl_80383D40, 0, 16);
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
    fn_80239CEC(info.mpImage, info.mWidth * info.mHeight * 2);
    pFont->mpTexObj = fn_801D2B7C(0x20, 0, 0);
    if (pFont->mpHeader->mFlags & 4) {
        fn_80250210(pFont->mpTexObj, info.mpImage, info.mWidth, info.mHeight, 8, 0, 0, 0, 0);
        fn_80250258(pFont->mpTexObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    } else {
        fn_8024FFC4(pFont->mpTexObj, info.mpImage, info.mWidth, info.mHeight, 0, 0, 0, 0);
        fn_80250258(pFont->mpTexObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
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
