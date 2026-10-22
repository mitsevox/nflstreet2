#ifndef ENGINE_CU_801CCA64_H
#define ENGINE_CU_801CCA64_H

/* Font file header; glyph, kerning and texture data follow at the given offsets. */
typedef struct FontHeader_801CCA64 {
    int mMagic;
    unsigned char mUnk4[6];
    unsigned short mNumGlyphs;
    unsigned int mFlags;
    unsigned char mUnk10[3];
    unsigned char mHeight;
    int mGlyphOffset;
    int mKernOffset;
    int mTexOffset;
} FontHeader_801CCA64;

typedef struct FontGlyph_801CCA64 {
    unsigned short mCode;
    unsigned char mWidth;
    unsigned char mHeight;
    unsigned short mU;
    unsigned short mV;
    signed char mAdvance;
    signed char mOffsetX;
    signed char mOffsetY;
    unsigned char mUnkB;
} FontGlyph_801CCA64;

typedef struct FontKernPair_801CCA64 {
    unsigned short mFirst;
    unsigned short mSecond;
    signed char mAmount;
    unsigned char mPad[3];
} FontKernPair_801CCA64;

typedef struct FontKernTable_801CCA64 {
    int mCount;
    FontKernPair_801CCA64 mPairs[1];
} FontKernTable_801CCA64;

typedef struct FontTexHeader_801CCA64 {
    unsigned char mUnk0[4];
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mUnk8[8];
    unsigned char mImage[1];
} FontTexHeader_801CCA64;

typedef struct FontEntry_801CCA64 {
    void *mpFile;
    int mHandle;
    int mId;
    FontHeader_801CCA64 *mpData;
} FontEntry_801CCA64;

typedef struct Font_801CCA64 {
    FontEntry_801CCA64 *mpEntry;
    FontHeader_801CCA64 *mpHeader;
    FontGlyph_801CCA64 *mpGlyphs;
    FontKernTable_801CCA64 *mpKern;
    FontTexHeader_801CCA64 *mpTex;
    unsigned char mUnk14[4];
    void *mpTexObj;
    unsigned char mUnk1C[0xC];
} Font_801CCA64;

typedef struct FontQuad_801CCA64 {
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    unsigned short mU;
    unsigned short mV;
} FontQuad_801CCA64;

typedef struct FontColor_801CCA64 {
    float r;
    float g;
    float b;
    float a;
} FontColor_801CCA64;

typedef struct FontRenderState_801CCA64 {
    unsigned int mFlags;
    FontColor_801CCA64 mColor;
    FontColor_801CCA64 mShadowColor;
    float mShadowOffset[3];
} FontRenderState_801CCA64;

int fn_801CCF74(void *pFile, int id, FontHeader_801CCA64 *pData);
Font_801CCA64 *fn_801CD130(int id);
void fn_801CD20C(Font_801CCA64 *pFont, int a);
int fn_801CD2A4(void);
int fn_801CD308(int which, FontColor_801CCA64 color);
void fn_801CD3E4(Font_801CCA64 *pFont, const char *pText, unsigned int flags, float maxWidth,
                 FontQuad_801CCA64 *pQuads, unsigned int *pCount);
int fn_801CDB5C(Font_801CCA64 *pFont, const char *pText, unsigned int flags, float maxWidth, float *pPos);
void fn_801CDD18(void);
void fn_801CDE98(void **ppTlut0, void **ppTlut1, void **ppTlut2);
void fn_801CDFE4(void *pTlut0, void *pTlut1, void *pTlut2);
void fn_801CDFE8(Font_801CCA64 *pFont, void *pTlut0, void *pTlut1, void *pTlut2, int a);
void fn_801CE108(Font_801CCA64 *pFont);
void fn_801CE134(Font_801CCA64 *pFont);

#endif
