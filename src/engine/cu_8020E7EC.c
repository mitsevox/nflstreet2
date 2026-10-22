#include <dolphin/os/OSCache.h>
#include "game/fn_801D2B7C.h"
#include "engine/tmlib.h"

void fn_8020E7EC(Texture_8020DB34 *pTex)
{
    int bpp;
    int size;
    unsigned char *pImage;
    unsigned short width;
    unsigned short height;
    unsigned short srcPitch;
    unsigned short dstPitch;
    unsigned char *pDst;
    unsigned int y;

    if ((pTex->mWidth & (pTex->mWidth - 1)) == 0 && (pTex->mHeight & (pTex->mHeight - 1)) == 0) {
        return;
    }
    switch (pTex->mFormat) {
    case 0:
        bpp = 4;
        break;
    case 1:
        bpp = 8;
        break;
    case 2:
        bpp = 8;
        break;
    case 3:
    case 14:
        bpp = 16;
        break;
    case 6:
        bpp = 32;
        break;
    default:
        bpp = 0;
        break;
    }
    size = (pTex->mWidth * pTex->mHeight * bpp) >> 3;
    pImage = fn_801D2BB0(lbl_803EBEBC, size, 4, 0);
    memcpy(pImage, pTex->mpImage, size);
    fn_801D2BD0(pTex->mpImage);
    pTex->mpImage = pImage;
    for (width = 1; width < pTex->mWidth; width <<= 1) {
    }
    for (height = 1; height < pTex->mHeight; height <<= 1) {
    }
    srcPitch = (pTex->mWidth * bpp) >> 3;
    dstPitch = width * bpp / 8;
    size = height * dstPitch;
    pDst = fn_801D2BB0(lbl_803EBEBC, size, 0, 0);
    fn_801D34D0(pDst, size, 0, 1);
    for (y = 0; y < pTex->mHeight; y++) {
        memcpy(pDst + y * dstPitch, pTex->mpImage + y * srcPitch, srcPitch);
    }
    fn_801D2BD0(pTex->mpImage);
    pTex->mWidth = width;
    pTex->mpImage = pDst;
    pTex->mHeight = height;
}

void fn_8020E9D0(void *pDst, void *pSrc, unsigned int size)
{
    if (size != 0) {
        memcpy(pDst, pSrc, size);
        DCFlushRange(pDst, size);
    }
}
