#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

/* Texture record of src/engine/texture.c: filled by the load handlers that
   fn_8020DFD8 dispatches to, created by fn_8020E064 and released by
   fn_8020E258. +0x10 is the TLUT format fn_8020E064 stores and
   fn_801C0E04 passes to GXInitTlutObj. */
typedef struct Texture_8020DB34 {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mWrapS;
    unsigned char mWrapT;
    unsigned char mMinFilter;
    unsigned char mMagFilter;
    unsigned int mFormat;
    unsigned char *mpImage;
    unsigned int mTlutFormat;
    unsigned short *mpPalette;
    int mUnknown18;
    unsigned char mbDirty;
} Texture_8020DB34;

#ifdef __cplusplus
extern "C" {
#endif
int fn_8020DFD8(void *pSrc, Texture_8020DB34 *pTex);
int fn_8020E258(Texture_8020DB34 *pTex);
#ifdef __cplusplus
}
#endif

#endif
