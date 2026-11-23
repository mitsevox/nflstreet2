#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include <dolphin/gx/GXStruct.h>

/* Font file header; glyph, kerning and texture data follow at the given offsets. */
typedef struct FontHeader_t {
    int mMagic;
    unsigned char mUnk4[6];
    unsigned short mNumGlyphs;
    unsigned int mFlags;
    unsigned char mUnk10[3];
    unsigned char mHeight;
    int mGlyphOffset;
    int mKernOffset;
    int mTexOffset;
} FontHeader_t;

typedef struct FontGlyph_t {
    unsigned short mCode;
    unsigned char mWidth;
    unsigned char mHeight;
    unsigned short mU;
    unsigned short mV;
    signed char mAdvance;
    signed char mOffsetX;
    signed char mOffsetY;
    unsigned char mUnkB;
} FontGlyph_t;

typedef struct FontKernPair_t {
    unsigned short mFirst;
    unsigned short mSecond;
    signed char mAmount;
    unsigned char mPad[3];
} FontKernPair_t;

typedef struct FontKernTable_t {
    int mCount;
    FontKernPair_t mPairs[1];
} FontKernTable_t;

typedef struct FontTexHeader_t {
    unsigned char mUnk0[4];
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mUnk8[8];
    unsigned char mImage[1];
} FontTexHeader_t;

typedef struct FontEntry_t {
    void *mpFile;
    int mHandle;
    int mId;
    FontHeader_t *mpData;
} FontEntry_t;

typedef struct Font_t {
    FontEntry_t *mpEntry;
    FontHeader_t *mpHeader;
    FontGlyph_t *mpGlyphs;
    FontKernTable_t *mpKern;
    FontTexHeader_t *mpTex;
    unsigned char mUnk14[4];
    GXTexObj *mpTexObj;
    unsigned char mUnk1C[0xC];
} Font_t;

typedef struct FontQuad_t {
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    unsigned short mU;
    unsigned short mV;
} FontQuad_t;

typedef struct FontColor_t {
    float r;
    float g;
    float b;
    float a;
} FontColor_t;

typedef struct FontRenderState_t {
    unsigned int mFlags;
    FontColor_t mColor;
    FontColor_t mShadowColor;
    float mShadowOffset[3];
    unsigned char unk_0x30[0xC];
} FontRenderState_t;

int FontAddFontFromBuffer(void *pFile, int id, FontHeader_t *pData);
Font_t *FontCreateFont(int id);
void FontUploadTextures(Font_t *pFont, int a);
int FontResetRenderState(void);
int FontSetRenderColor(int which, FontColor_t color);
void FontDrawText(Font_t *pFont, const char *pText, unsigned int flags, float maxWidth,
                 FontQuad_t *pQuads, unsigned int *pCount);
int FontLLRenderText(Font_t *pFont, const char *pText, unsigned int flags, float maxWidth, float *pPos);
void FontLLRenderBegin(void);
void FontLLUploadPalettes(void **ppTlut0, void **ppTlut1, void **ppTlut2);
void FontLLReleasePalettes(void *pTlut0, void *pTlut1, void *pTlut2);
void FontLLUploadTextures(Font_t *pFont, void *pTlut0, void *pTlut1, void *pTlut2, int a);
void FontLLReleaseTextures(Font_t *pFont);
void FontLLCreateFont(Font_t *pFont);

#endif
