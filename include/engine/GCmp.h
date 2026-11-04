#ifndef ENGINE_GCMP_H
#define ENGINE_GCMP_H

/* Stream buffer of the codec layer in src/engine/GCmp.c: +0 data,
   +4 size, +8 position and the byte flag +0x18 used there. fn_8020E6A0 sets
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

typedef void *(*CodecInit_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);
typedef int (*CodecRun_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState);
typedef void (*CodecEnd_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState);

/* 40-byte codec descriptor registered through fn_8027F2D8. */
typedef struct Codec_8027F2D8 {
    unsigned int mTag;
    unsigned int mFlags;
    CodecInit_8027F2D8 mpEncodeInit;
    CodecRun_8027F2D8 mpEncodeRun;
    CodecEnd_8027F2D8 mpEncodeEnd;
    CodecInit_8027F2D8 mpDecodeInit;
    CodecRun_8027F2D8 mpDecodeRun;
    CodecEnd_8027F2D8 mpDecodeEnd;
    int (*mpStartup)(void);
    int (*mpShutdown)(void);
} Codec_8027F2D8;

/* 28-byte stream record allocated by fn_8027F45C and fn_8027F7B0. */
typedef struct Stream_8027F45C {
    Buffer_8027F9AC *mpSrc;
    Buffer_8027F9AC *mpDst;
    void *mpState;
    int mMode;
    int mCodec;
    unsigned int mStatus;
    unsigned char mOwnsDst;
} Stream_8027F45C;

int fn_8027F2D8(int index, Codec_8027F2D8 *pCodec);
Stream_8027F45C *fn_8027F45C(int mode, int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);
void fn_8027F61C(Stream_8027F45C *pStream);
void fn_8027F6A8(Stream_8027F45C *pStream);
int fn_8027F9AC(Buffer_8027F9AC *pBuffer, void *pOut, unsigned int size);
int fn_8027FA04(Buffer_8027F9AC *pBuffer, void *pIn, unsigned int size);
void fn_8027F3A4(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);

#endif
