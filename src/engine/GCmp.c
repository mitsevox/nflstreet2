#include "engine/GCmp.h"

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

extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern void *fn_801D310C(void *allocation, int size, int c, int d);
extern void fn_801F7BD4(int err);
extern char *fn_801C3284(char *pDest, const char *pSource, int size);
extern int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);

static unsigned char lbl_803EC570 = 0;
static int lbl_803EC574 = 0;
static Codec_8027F2D8 **lbl_803ED410;
extern char lbl_803018A8[];
extern Codec_8027F2D8 lbl_803018C8;
extern Codec_8027F2D8 lbl_803018F0;
extern Codec_8027F2D8 lbl_80301918;
extern Codec_8027F2D8 lbl_80301940;
extern Codec_8027F2D8 lbl_80301968;

int fn_8027F0DC(int count)
{
    int err = 0;
    unsigned short i;

    if (lbl_803EC570 == 0) {
        lbl_803EC574 = count + 6;
        lbl_803ED410 = fn_801D2BB0(1, lbl_803EC574 * 4, 0, 0);
        fn_8027F2D8(0, &lbl_80301918);
        fn_8027F2D8(1, &lbl_803018F0);
        fn_8027F2D8(2, &lbl_803018C8);
        fn_8027F2D8(3, &lbl_80301940);
        fn_8027F2D8(5, &lbl_80301968);
        lbl_803ED410[4] = 0;
        for (i = 0; i <= 5 && err == 0; i++) {
            if (lbl_803ED410[i] != 0 && lbl_803ED410[i]->mpStartup != 0) {
                err = lbl_803ED410[i]->mpStartup();
            }
        }
        while (count--) {
            fn_8027F2D8(count + 6, 0);
        }
        lbl_803EC570 = 1;
    } else {
        err = 0x150001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_8027F21C(void)
{
    int err = 0;
    unsigned short i;

    if (lbl_803EC570) {
        for (i = 0; i <= 5 && err == 0; i++) {
            if (lbl_803ED410[i] != 0 && lbl_803ED410[i]->mpShutdown != 0) {
                err = lbl_803ED410[i]->mpShutdown();
            }
        }
        fn_801D2BD0(lbl_803ED410);
        lbl_803EC570 = 0;
    } else {
        err = 0x150002;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_8027F2C0(void)
{
    return lbl_803EC570 != 0;
}

int fn_8027F2D8(int index, Codec_8027F2D8 *pCodec)
{
    lbl_803ED410[index] = pCodec;
    return 0;
}

void fn_8027F2EC(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_8027F45C(0, codec, pSrc, pDst);

    if (pStream->mStatus == 0) {
        do {
            fn_8027F61C(pStream);
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
    fn_8027F6A8(pStream);
}

void fn_8027F3A4(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_8027F45C(1, codec, pSrc, pDst);

    if (pStream->mStatus == 0) {
        do {
            fn_8027F61C(pStream);
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
    fn_8027F6A8(pStream);
}

Stream_8027F45C *fn_8027F45C(int mode, int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
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
            pStream->mpState = lbl_803ED410[pStream->mCodec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
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
            pStream->mpState = lbl_803ED410[pStream->mCodec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

void fn_8027F61C(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
}

void fn_8027F6A8(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        lbl_803ED410[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        lbl_803ED410[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    pStream->mpDst->mSize = pStream->mpDst->mPos;
    if (pStream->mOwnsDst) {
        pStream->mpDst->mpData = fn_801D310C(pStream->mpDst->mpData, pStream->mpDst->mSize, 0, 0);
    }
    fn_801D2BD0(pStream);
}

int fn_8027F77C(int index)
{
    Codec_8027F2D8 *pCodec;

    if (lbl_803ED410 != 0) {
        pCodec = lbl_803ED410[index];
        if (pCodec != 0 && (pCodec->mFlags & 2)) {
            return 1;
        }
    }
    return 0;
}

Stream_8027F45C *fn_8027F7B0(int codec, int mode, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
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
            pStream->mpState = lbl_803ED410[codec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        case 1:
            pStream->mpState = lbl_803ED410[codec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

unsigned int fn_8027F880(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
    return pStream->mStatus;
}

void fn_8027F910(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        lbl_803ED410[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        lbl_803ED410[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    fn_801D2BD0(pStream);
}

int fn_8027F9AC(Buffer_8027F9AC *pBuffer, void *pOut, unsigned int size)
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

int fn_8027FA04(Buffer_8027F9AC *pBuffer, void *pIn, unsigned int size)
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

void fn_8027FAB8(const char *pName)
{
    if (pName == 0) {
        fn_801C3284(lbl_803018A8, "GCMP.LIB", 32);
    } else {
        fn_801C2D88(lbl_803018A8, 32, "%s", pName);
        lbl_803018A8[31] = 0;
    }
}
