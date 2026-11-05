#ifndef GAME_BMFONT_H
#define GAME_BMFONT_H

#include "engine/texture.h"

/* Descriptor of a bitmap font: the characters of the font texture in order,
   the glyph row height (+0xC), the advance of characters without a glyph
   (+0x10) and the gap after each glyph (+0x14). */
struct BmFontDesc {
    int mCount;
    const char *mpChars;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

/* One glyph: a rectangle of the font texture's 8-bit pixels. */
struct BmGlyph {
    unsigned char mWidth;
    unsigned char mHeight;
    unsigned short mStride;
    unsigned char *mpPixels;
};

struct BmFont {
    unsigned int mCount;
    BmGlyph *mpGlyphs;
    unsigned int mSpaceWidth;
    unsigned int mSpacing;
    unsigned char mBorder;
    Texture_8020DB34 mTexture;
    char mUnknown34[0x28];
    unsigned char mMapCount;
    unsigned char mMap[256];
};

extern "C" {
unsigned int BmFontRenderString(BmFont *pFont, unsigned char *pDest, const unsigned char *pString);
void BmFontLoad(BmFont *pFont, BmFontDesc *pDesc, void *p, int index);
void BmFontFree(BmFont *pFont);
BmFont *fn_801614C4(void);
}

#endif
