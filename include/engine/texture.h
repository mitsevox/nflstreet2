#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

/* Texture record of src/engine/texture.c: filled by the load handlers that
   TexCreate dispatches to, created by TexCreateEmpty and released by
   TexDelete. +0x10 is the TLUT format TexCreateEmpty stores and
   fn_801C0E04 passes to GXInitTlutObj. */
typedef struct Texture_t {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned int mFormat;
    unsigned char *mpImage;
    unsigned int mTlutFormat;
    unsigned short *mpPalette;
    int mUnknown18;
    unsigned char mUnknown1C;
} Texture_t;

#ifdef __cplusplus
extern "C" {
#endif
int TexInit(int heap, int count, int unknown);
int TexShutdown(void);
int TexCreate(void *pSrc, Texture_t *pTex);
int TexDelete(Texture_t *pTex);
void fn_8020E7EC(Texture_t *pTex);
#ifdef __cplusplus
}
#endif

#endif
