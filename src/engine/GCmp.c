/* Compression library front end: registers the codecs (none, run-length, Huffman, LZM, LZH) and
   compresses or decompresses memory buffers through them, whole or block by block; resources and
   textures are unpacked through it. */

#include "engine/GCmp.h"

typedef void *(*CodecInit_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);
typedef int (*CodecRun_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState);
typedef void (*CodecEnd_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState);

/* 40-byte codec descriptor registered through GCmpRegisterType. */
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

/* 28-byte stream record allocated by GCmpStart and GCmpBlockStart. */
typedef struct Stream_8027F45C {
    Buffer_8027F9AC *mpSrc;
    Buffer_8027F9AC *mpDst;
    void *mpState;
    int mMode;
    int mCodec;
    unsigned int mStatus;
    unsigned char mOwnsDst;
} Stream_8027F45C;

int GCmpRegisterType(int index, Codec_8027F2D8 *pCodec);
Stream_8027F45C *GCmpStart(int mode, int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);
void GCmpProcess(Stream_8027F45C *pStream);
void GCmpStop(Stream_8027F45C *pStream);

extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern void *fn_801D310C(void *allocation, int size, int c, int d);
extern void fn_801F7BD4(int err);
extern char *fn_801C3284(char *pDest, const char *pSource, int size);
extern int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);

static unsigned char _GCmpModuleActive = 0;
static int _GCmpNumTypes = 0;
static Codec_8027F2D8 **_GCmp_ppTypes;
extern char lbl_803018A8[];
extern Codec_8027F2D8 lbl_803018C8;
extern Codec_8027F2D8 lbl_803018F0;
extern Codec_8027F2D8 lbl_80301918;
extern Codec_8027F2D8 lbl_80301940;
extern Codec_8027F2D8 lbl_80301968;

int GCmpInit(int count)
{
    int err = 0;
    unsigned short i;

    if (_GCmpModuleActive == 0) {
        _GCmpNumTypes = count + 6;
        _GCmp_ppTypes = fn_801D2BB0(1, _GCmpNumTypes * 4, 0, 0);
        GCmpRegisterType(0, &lbl_80301918);
        GCmpRegisterType(1, &lbl_803018F0);
        GCmpRegisterType(2, &lbl_803018C8);
        GCmpRegisterType(3, &lbl_80301940);
        GCmpRegisterType(5, &lbl_80301968);
        _GCmp_ppTypes[4] = 0;
        for (i = 0; i <= 5 && err == 0; i++) {
            if (_GCmp_ppTypes[i] != 0 && _GCmp_ppTypes[i]->mpStartup != 0) {
                err = _GCmp_ppTypes[i]->mpStartup();
            }
        }
        while (count--) {
            GCmpRegisterType(count + 6, 0);
        }
        _GCmpModuleActive = 1;
    } else {
        err = 0x150001;
    }
    fn_801F7BD4(err);
    return err;
}

int GCmpShutdown(void)
{
    int err = 0;
    unsigned short i;

    if (_GCmpModuleActive) {
        for (i = 0; i <= 5 && err == 0; i++) {
            if (_GCmp_ppTypes[i] != 0 && _GCmp_ppTypes[i]->mpShutdown != 0) {
                err = _GCmp_ppTypes[i]->mpShutdown();
            }
        }
        fn_801D2BD0(_GCmp_ppTypes);
        _GCmpModuleActive = 0;
    } else {
        err = 0x150002;
    }
    fn_801F7BD4(err);
    return err;
}

int GCmpIsActive(void)
{
    return _GCmpModuleActive != 0;
}

int GCmpRegisterType(int index, Codec_8027F2D8 *pCodec)
{
    _GCmp_ppTypes[index] = pCodec;
    return 0;
}

void GCmpCompress(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = GCmpStart(0, codec, pSrc, pDst);

    if (pStream->mStatus == 0) {
        do {
            GCmpProcess(pStream);
            switch (pStream->mStatus) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
                pDst->mpData = fn_801D310C(pDst->mpData, pDst->mSize * 2, 0, 0);
                pDst->mSize *= 2;
                pStream->mOwnsDst = 1;
                pStream->mStatus = 0;
                break;
            }
        } while (pStream->mStatus == 0);
    }
    GCmpStop(pStream);
}

void GCmpDecompress(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = GCmpStart(1, codec, pSrc, pDst);

    if (pStream->mStatus == 0) {
        do {
            GCmpProcess(pStream);
            switch (pStream->mStatus) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
                pDst->mpData = fn_801D310C(pDst->mpData, pDst->mSize * 2, 0, 0);
                pDst->mSize *= 2;
                pStream->mOwnsDst = 1;
                pStream->mStatus = 0;
                break;
            }
        } while (pStream->mStatus == 0);
    }
    GCmpStop(pStream);
}

Stream_8027F45C *GCmpStart(int mode, int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_801D2BB0(1, sizeof(Stream_8027F45C), 4, 0);
    unsigned int size;

    if (pStream != 0) {
        pStream->mMode = mode;
        pStream->mCodec = codec;
        pStream->mStatus = 0;
        pStream->mOwnsDst = 0;
        pStream->mpSrc = pSrc;
        pSrc->mPos = 0;
        pStream->mpDst = pDst;
        pDst->mPos = 0;
        pStream->mpState = 0;
        switch (pStream->mMode) {
        case 0:
            if (pStream->mpDst->mpData == 0) {
                pStream->mpDst->mSize = pStream->mpSrc->mSize;
                pStream->mpDst->mpData = fn_801D2BB0(1, pStream->mpDst->mSize, 0, 0);
                pStream->mOwnsDst = 1;
            }
            pStream->mpSrc->mUnknown18 = 1;
            pStream->mpDst->mUnknown18 = 0;
            pStream->mpState = _GCmp_ppTypes[pStream->mCodec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        case 1:
            pStream->mpDst->mUnknown18 = 1;
            if (pStream->mpDst->mpData == 0) {
                size = pStream->mpDst->mSize;
                if (size != 0) {
                    pStream->mpDst->mpData = fn_801D2BB0(1, size, 0, 0);
                } else {
                    pStream->mpDst->mSize = pStream->mpSrc->mSize * 2;
                    pStream->mpDst->mpData = fn_801D2BB0(1, pStream->mpDst->mSize, 0, 0);
                    pStream->mOwnsDst = 1;
                    pStream->mpDst->mUnknown18 = 0;
                }
            }
            pStream->mpSrc->mUnknown18 = 1;
            pStream->mpState = _GCmp_ppTypes[pStream->mCodec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

void GCmpProcess(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = _GCmp_ppTypes[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = _GCmp_ppTypes[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
}

void GCmpStop(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        _GCmp_ppTypes[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        _GCmp_ppTypes[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    pStream->mpDst->mSize = pStream->mpDst->mPos;
    if (pStream->mOwnsDst) {
        pStream->mpDst->mpData = fn_801D310C(pStream->mpDst->mpData, pStream->mpDst->mSize, 0, 0);
    }
    fn_801D2BD0(pStream);
}

int GCmpIsBlockCodec(int index)
{
    Codec_8027F2D8 *pCodec;

    if (_GCmp_ppTypes != 0) {
        pCodec = _GCmp_ppTypes[index];
        if (pCodec != 0 && (pCodec->mFlags & 2)) {
            return 1;
        }
    }
    return 0;
}

Stream_8027F45C *GCmpBlockStart(int codec, int mode, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_801D2BB0(1, sizeof(Stream_8027F45C), 0, 0);

    if (pStream != 0) {
        pStream->mpSrc = pSrc;
        pSrc->mPos = 0;
        pStream->mpDst = pDst;
        pDst->mPos = 0;
        pStream->mMode = mode;
        pStream->mCodec = codec;
        pStream->mStatus = 0;
        pStream->mOwnsDst = 0;
        pStream->mpState = 0;
        switch (mode) {
        case 0:
            pStream->mpState = _GCmp_ppTypes[codec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        case 1:
            pStream->mpState = _GCmp_ppTypes[codec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

unsigned int GCmpBlockProcess(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = _GCmp_ppTypes[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = _GCmp_ppTypes[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
    return pStream->mStatus;
}

void GCmpBlockStop(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        _GCmp_ppTypes[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        _GCmp_ppTypes[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    fn_801D2BD0(pStream);
}

int GCmpRead(Buffer_8027F9AC *pBuffer, void *pOut, unsigned int size)
{
    unsigned char *pDst = pOut;

    if (pBuffer->mPos + size > pBuffer->mSize) {
        return 0;
    }
    while (size--) {
        *pDst++ = pBuffer->mpData[pBuffer->mPos++];
    }
    return 1;
}

int GCmpWrite(Buffer_8027F9AC *pBuffer, void *pIn, unsigned int size)
{
    unsigned char *pSrc = pIn;

    while (pBuffer->mPos + size > pBuffer->mSize) {
        pBuffer->mpData = fn_801D310C(pBuffer->mpData, pBuffer->mSize * 2, 0, 0);
        pBuffer->mSize *= 2;
    }
    while (size--) {
        pBuffer->mpData[pBuffer->mPos++] = *pSrc++;
    }
    return 1;
}

void GCmpSetLabel(const char *pName)
{
    if (pName == 0) {
        fn_801C3284(lbl_803018A8, "GCMP.LIB", 32);
    } else {
        fn_801C2D88(lbl_803018A8, 32, "%s", pName);
        lbl_803018A8[31] = 0;
    }
}
