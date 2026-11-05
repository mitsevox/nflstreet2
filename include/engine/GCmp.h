#ifndef ENGINE_GCMP_H
#define ENGINE_GCMP_H

/* Stream buffer of the codec layer in src/engine/GCmp.c: +0 data,
   +4 size, +8 position and the byte flag +0x18 used there. TexDecompressTexture sets
   up a 0x20-byte source buffer for fn_8027F3A4 with the image width and
   height at +0xC/+0xE and the bit depth 16 at +0x16. */
typedef struct Buffer_8027F9AC {
    unsigned char *mpData;
    unsigned int mSize;
    unsigned int mPos;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mUnknown10[6];
    unsigned short mBits;
    unsigned char mUnknown18;
    unsigned char mUnknown19[7];
} Buffer_8027F9AC;

int fn_8027F9AC(Buffer_8027F9AC *pBuffer, void *pOut, unsigned int size);
int fn_8027FA04(Buffer_8027F9AC *pBuffer, void *pIn, unsigned int size);
void fn_8027F3A4(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);

#endif
