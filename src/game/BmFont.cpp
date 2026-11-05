/* Bitmap font for player nameplates: cuts glyphs out of a font texture,
   measures strings and renders a string centred into a 256x32 I4 texture. */
#include <string.h>
#include "game/BmFont.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"

extern "C" {

void BmFontClearMap(BmFont *pFont)
{
    memset(pFont->mMap, 0xFF, sizeof(pFont->mMap));
    pFont->mMapCount = 0;
}

void BmFontMapChars(BmFont *pFont, unsigned int c, int count)
{
    while (count > 0 && c <= 0xFF) {
        pFont->mMap[c] = pFont->mMapCount++;
        c++;
        count--;
    }
}

unsigned int BmFontCopyGlyph(BmGlyph *pGlyph, unsigned char *pDest, int destStride)
{
    unsigned int width = pGlyph->mWidth;
    unsigned int height = pGlyph->mHeight;
    unsigned int stride = pGlyph->mStride;
    unsigned char *pSrc = pGlyph->mpPixels;
    unsigned int y;

    for (y = 0; y < height; y++) {
        memcpy(pDest, pSrc, width);
        pDest += destStride;
        pSrc += stride;
    }
    return width;
}

/* Copies the glyph at half width, taking every other column. */
unsigned int BmFontCopyGlyphHalf(BmGlyph *pGlyph, unsigned char *pDest, int destStride)
{
    unsigned int width = pGlyph->mWidth;
    unsigned int height = pGlyph->mHeight;
    unsigned int stride = pGlyph->mStride;
    unsigned char *pSrc = pGlyph->mpPixels;
    unsigned int x;
    unsigned int y;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x += 2) {
            pDest[x / 2] = pSrc[x];
        }
        pDest += destStride;
        pSrc += stride;
    }
    return width / 2;
}

BmGlyph *BmFontFindGlyph(BmFont *pFont, unsigned char c)
{
    unsigned int index = pFont->mMap[c];

    if (index != 0xFF && index < pFont->mCount) {
        return &pFont->mpGlyphs[index];
    }
    return 0;
}

/* Returns 1 when any of count pixels down a column is opaque in pOpaque. */
int BmFontIsColumnOpaque(unsigned char *pPixels, int stride, unsigned int count, unsigned char *pOpaque)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pOpaque[*pPixels]) {
            return 1;
        }
        pPixels += stride;
    }
    return 0;
}

/* Skips the empty columns before a glyph, then takes the following run of
   non-empty columns as the glyph. Returns the number of columns consumed. */
unsigned int BmFontCutGlyph(BmGlyph *pGlyph, unsigned char *pPixels, int stride,
                         unsigned int width, int height, unsigned char *pOpaque)
{
    unsigned int x;

    pGlyph->mWidth = 0;
    pGlyph->mpPixels = pPixels;
    pGlyph->mHeight = height;
    pGlyph->mStride = stride;
    for (x = 0; x < width && !BmFontIsColumnOpaque(pPixels + x, stride, height, pOpaque); x++) {
        pGlyph->mpPixels++;
    }
    for (; x < width && BmFontIsColumnOpaque(pPixels + x, stride, height, pOpaque); x++) {
        pGlyph->mWidth++;
    }
    return x;
}

/* Overwrites the first and last rows of the glyph with value. */
void BmFontSetGlyphEdgeRows(BmGlyph *pGlyph, unsigned char value)
{
    unsigned int last = (pGlyph->mHeight - 1) * pGlyph->mStride;
    unsigned int x;

    for (x = 0; x < pGlyph->mWidth; x++) {
        pGlyph->mpPixels[x] = value;
        pGlyph->mpPixels[x + last] = value;
    }
}

/* Marks the 16 palette entries whose alpha reaches threshold. Opaque RGB5A3
   entries count as alpha 0x80; translucent ones use their 3-bit alpha. */
void BmFontMarkOpaque(unsigned short *pPalette, unsigned char *pOpaque, int size, unsigned int threshold)
{
    unsigned short color;
    unsigned int alpha;
    int i;

    memset(pOpaque, 0, size);
    for (i = 0; i < 16; i++) {
        color = pPalette[i];
        alpha = 0x80;
        if (!(color & 0x8000)) {
            alpha = (color >> 8) & 0xF0;
        }
        pOpaque[i] = alpha >= threshold;
    }
}

void BmFontFillWords(unsigned int *pDest, unsigned long long value, unsigned int count)
{
    while (count > 3) {
        pDest[0] = value;
        pDest[1] = value;
        pDest[2] = value;
        pDest[3] = value;
        pDest += 4;
        count -= 4;
    }
}

unsigned int BmFontGetStringWidth(BmFont *pFont, const unsigned char *pString)
{
    BmGlyph *pGlyph;
    unsigned int width = 0;

    for (; *pString != 0; pString++) {
        pGlyph = BmFontFindGlyph(pFont, *pString);
        if (pGlyph != 0) {
            width += pGlyph->mWidth + pFont->mSpacing;
        } else {
            width += pFont->mSpaceWidth;
        }
    }
    return width;
}

/* Cuts the font texture into glyphs, row by row, in the order of the
   descriptor's character list. */
void BmFontCutGlyphs(BmFont *pFont, BmFontDesc *pDesc)
{
    unsigned char opaque[256];
    unsigned char *pPixels = pFont->mTexture.mpImage;
    unsigned int i;
    unsigned int x;
    unsigned int y;

    BmFontMarkOpaque(pFont->mTexture.mpPalette, opaque, sizeof(opaque), 0x20);
    x = 0;
    y = 0;
    for (i = 0; i < pFont->mCount && y < pFont->mTexture.mHeight; i++) {
        x += BmFontCutGlyph(&pFont->mpGlyphs[i], pPixels + y * 256 + x, pFont->mTexture.mWidth,
                         pFont->mTexture.mWidth - x, pDesc->mUnknownC, opaque);
        BmFontSetGlyphEdgeRows(&pFont->mpGlyphs[i], pFont->mBorder);
        if (x >= pFont->mTexture.mWidth) {
            x = 0;
            y += pDesc->mUnknownC;
        }
    }
    pFont->mCount = i;
}

void BmFontSetImageEdgeRows(unsigned char *pPixels, int width, int height, unsigned char value)
{
    unsigned char *pLast = pPixels + width * (height - 1);
    int x;

    for (x = 0; x < width; x++) {
        pPixels[x] = value;
        pLast[x] = value;
    }
}

/* Packs a block of 8-bit intensities into 4-bit pairs. */
void BmFontPackI4(unsigned char *pDest, unsigned char *pSrc, int srcStride, int width, int height)
{
    int x;
    int y;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x += 2) {
            *pDest++ = (pSrc[0] << 4) | pSrc[1];
            pSrc += 2;
        }
        pSrc += srcStride - width;
    }
}

/* Converts an 8-bit image into I4 texture tiles of 8x8 texels. */
unsigned char *BmFontConvertI4(unsigned char *pDest, unsigned char *pSrc, int width, int height, int stride)
{
    int x;
    int y;

    for (y = 0; y < height; y += 8) {
        for (x = 0; x < width; x += 8) {
            BmFontPackI4(pDest, pSrc + y * stride + x, stride, 8, 8);
            pDest += 32;
        }
    }
    return pDest;
}

/* Draws pString centred into a 256x32 image and stores it as an I4 texture
   at pDest; text too wide for the image is drawn at half width. */
unsigned int BmFontRenderString(BmFont *pFont, unsigned char *pDest, const unsigned char *pString)
{
    unsigned char image[0x4000];
    BmGlyph *pGlyph;
    unsigned int width;
    unsigned int spaceWidth;
    int scale = 1;
    int x;

    BmFontFillWords((unsigned int *)image, 0, 0x800);
    width = BmFontGetStringWidth(pFont, pString);
    spaceWidth = pFont->mSpaceWidth;
    x = 128 - width / 2;
    if (x <= 0) {
        x = 128 - width / 4;
        spaceWidth /= 2;
        scale = 2;
        if (x <= 0) {
            x = 1;
        }
    }
    for (; *pString != 0; pString++) {
        pGlyph = BmFontFindGlyph(pFont, *pString);
        if (pGlyph != 0) {
            if (x + pGlyph->mWidth > 256) {
                break;
            }
            if (scale == 2) {
                x += BmFontCopyGlyphHalf(pGlyph, image + x, 256);
            } else {
                x += BmFontCopyGlyph(pGlyph, image + x, 256);
            }
            x += pFont->mSpacing;
        } else {
            x += spaceWidth;
        }
    }
    BmFontSetImageEdgeRows(image, 256, 32, pFont->mBorder);
    BmFontConvertI4(pDest, image, 256, 32, 256);
    return width;
}

void BmFontBuild(BmFont *pFont, BmFontDesc *pDesc)
{
    const char *pChars;

    pFont->mCount = strlen(pDesc->mpChars);
    pFont->mpGlyphs = (BmGlyph *)fn_801D2B7C(pFont->mCount * sizeof(BmGlyph), 0, 0);
    pFont->mSpaceWidth = pDesc->mUnknown10;
    pFont->mSpacing = pDesc->mUnknown14;
    pFont->mBorder = 0;
    BmFontClearMap(pFont);
    for (pChars = pDesc->mpChars; *pChars != 0; pChars++) {
        BmFontMapChars(pFont, *pChars, 1);
    }
    BmFontCutGlyphs(pFont, pDesc);
}

void BmFontLoad(BmFont *pFont, BmFontDesc *pDesc, void *p, int index)
{
    fn_8020DFD8((void *)fn_801EF390(p, index, 1), &pFont->mTexture);
    BmFontBuild(pFont, pDesc);
    fn_801F010C(p, index);
}

void BmFontFree(BmFont *pFont)
{
    fn_8020E258(&pFont->mTexture);
    fn_801D2BD0(pFont->mpGlyphs);
}
}
