#ifndef GAME_FONT_8019BE30_H
#define GAME_FONT_8019BE30_H

/* Descriptor of a bitmap font: the characters of the font texture in order,
   the glyph row height (+0xC), the advance of characters without a glyph
   (+0x10) and the gap after each glyph (+0x14). */
struct FontDesc_8019BE30 {
    int mCount;
    const char *mpChars;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

/* One glyph: a rectangle of the font texture's 8-bit pixels. */
struct Glyph_8019BE30 {
    unsigned char mWidth;
    unsigned char mHeight;
    unsigned short mStride;
    unsigned char *mpPixels;
};

/* Texture block filled by fn_8020DFD8; only the members read by the font
   code are declared. */
struct Texture_8020DFD8 {
    unsigned short mWidth;
    unsigned short mHeight;
    char mUnknown4[8];
    unsigned char *mpPixels;
    char mUnknown10[4];
    unsigned short *mpPalette;
    char mUnknown18[8];
};

struct Font_8019BE30 {
    unsigned int mCount;
    Glyph_8019BE30 *mpGlyphs;
    unsigned int mSpaceWidth;
    unsigned int mSpacing;
    unsigned char mBorder;
    Texture_8020DFD8 mTexture;
    char mUnknown34[0x28];
    unsigned char mMapCount;
    unsigned char mMap[256];
};

extern "C" {
unsigned int fn_8019BC50(Font_8019BE30 *pFont, unsigned char *pDest, const unsigned char *pString);
void fn_8019BE30(Font_8019BE30 *pFont, FontDesc_8019BE30 *pDesc, void *p, int index);
void fn_8019BE94(Font_8019BE30 *pFont);
Font_8019BE30 *fn_801614C4(void);
}

#endif
