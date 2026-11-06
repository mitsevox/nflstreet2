#ifndef ENGINE_GCMP_H
#define ENGINE_GCMP_H

/* Stream buffer of the codec layer in src/engine/GCmp.c: +0 data,
   +4 size, +8 position and the byte flag +0x18 used there. TexDecompressTexture sets
   up a 0x20-byte source buffer for GCmpDecompress with the image width and
   height at +0xC/+0xE and the bit depth 16 at +0x16. */
typedef struct GCmpBuffer_t {
    unsigned char *mpData;
    unsigned int mSize;
    unsigned int mPos;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mUnknown10[6];
    unsigned short mBits;
    unsigned char mUnknown18;
    unsigned char mUnknown19[7];
} GCmpBuffer_t;

int GCmpRead(GCmpBuffer_t *pBuffer, void *pOut, unsigned int size);
int GCmpWrite(GCmpBuffer_t *pBuffer, void *pIn, unsigned int size);
void GCmpDecompress(int codec, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst);

#endif
