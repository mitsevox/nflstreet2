/* Low-level texture helpers: widen a texture whose sides are not powers of two to
   the next power-of-two size (the image is copied into a zero-filled buffer row by
   row), and copy image data into memory the graphics hardware reads, flushing it
   from the data cache. */

#include <dolphin/os/OSCache.h>
#include "game/fn_801D2B7C.h"
#include "engine/tmlib.h"

/* Pad the image on the right and bottom while preserving the copied rows. */
void LLTexPadToPow2(Texture_t *pTex)
{
    short bpp;
    int imageSize;
    unsigned int paddedSize;
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
    imageSize = (pTex->mWidth * pTex->mHeight * bpp) >> 3;
    pImage = fn_801D2BB0(_Tex_ImageHeap, imageSize, 4, 0);
    memcpy(pImage, pTex->mpImage, imageSize);
    fn_801D2BD0(pTex->mpImage);
    pTex->mpImage = pImage;
    for (width = 1; width < pTex->mWidth; width <<= 1) {
    }
    for (height = 1; height < pTex->mHeight; height <<= 1) {
    }
    srcPitch = (pTex->mWidth * bpp) / 8;
    dstPitch = width * bpp / 8;
    paddedSize = height * dstPitch;
    pDst = fn_801D2BB0(_Tex_ImageHeap, paddedSize, 0, 0);
    MemFill(pDst, paddedSize, 0, 1);
    for (y = 0; y < pTex->mHeight; y++) {
        memcpy(pDst + y * dstPitch, pTex->mpImage + y * srcPitch, srcPitch);
    }
    fn_801D2BD0(pTex->mpImage);
    pTex->mpImage = pDst;
    pTex->mWidth = width;
    pTex->mHeight = height;
}

void LLTexCopyFlush(void *pDst, void *pSrc, unsigned int size)
{
    if (size != 0) {
        memcpy(pDst, pSrc, size);
        DCFlushRange(pDst, size);
    }
}
