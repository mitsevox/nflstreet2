/* Compression library front end: registers the codecs (none, run-length, Huffman, LZM, LZH) and
   compresses or decompresses memory buffers through them, whole or block by block; resources and
   textures are unpacked through it. */

#include "engine/GCmp.h"

typedef void *(*GCmpCodecInitFunc_t)(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst);
typedef int (*GCmpCodecRunFunc_t)(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState);
typedef void (*GCmpCodecEndFunc_t)(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState);

/* 40-byte codec descriptor registered through GCmpRegisterType. */
typedef struct GCmpCodec_t {
    unsigned int mTag;
    unsigned int mFlags;
    GCmpCodecInitFunc_t mpEncodeInit;
    GCmpCodecRunFunc_t mpEncodeRun;
    GCmpCodecEndFunc_t mpEncodeEnd;
    GCmpCodecInitFunc_t mpDecodeInit;
    GCmpCodecRunFunc_t mpDecodeRun;
    GCmpCodecEndFunc_t mpDecodeEnd;
    int (*mpStartup)(void);
    int (*mpShutdown)(void);
} GCmpCodec_t;

/* 28-byte stream record allocated by GCmpStart and GCmpBlockStart. */
typedef struct GCmpStream_t {
    GCmpBuffer_t *mpSrc;
    GCmpBuffer_t *mpDst;
    void *mpState;
    int mMode;
    int mCodec;
    unsigned int mStatus;
    unsigned char mOwnsDst;
} GCmpStream_t;

int GCmpRegisterType(int index, GCmpCodec_t *pCodec);
GCmpStream_t *GCmpStart(int mode, int codec, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst);
void GCmpProcess(GCmpStream_t *pStream);
void GCmpStop(GCmpStream_t *pStream);

extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern void *fn_801D310C(void *allocation, int size, int c, int d);
extern void fn_801F7BD4(int err);
extern char *strnzcpy(char *pDest, const char *pSource, int size);
extern int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);

static unsigned char _GCmpModuleActive = 0;
static int _GCmpNumTypes = 0;
static GCmpCodec_t **_GCmpTypes;
extern char lbl_803018A8[];
extern GCmpCodec_t lbl_803018C8;
extern GCmpCodec_t lbl_803018F0;
extern GCmpCodec_t lbl_80301918;
extern GCmpCodec_t lbl_80301940;
extern GCmpCodec_t lbl_80301968;

int GCmpInit(int count)
{
    int err = 0;
    unsigned short i;

    if (_GCmpModuleActive == 0) {
        _GCmpNumTypes = count + 6;
        _GCmpTypes = fn_801D2BB0(1, _GCmpNumTypes * 4, 0, 0);
        GCmpRegisterType(0, &lbl_80301918);
        GCmpRegisterType(1, &lbl_803018F0);
        GCmpRegisterType(2, &lbl_803018C8);
        GCmpRegisterType(3, &lbl_80301940);
        GCmpRegisterType(5, &lbl_80301968);
        _GCmpTypes[4] = 0;
        for (i = 0; i <= 5 && err == 0; i++) {
            if (_GCmpTypes[i] != 0 && _GCmpTypes[i]->mpStartup != 0) {
                err = _GCmpTypes[i]->mpStartup();
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
            if (_GCmpTypes[i] != 0 && _GCmpTypes[i]->mpShutdown != 0) {
                err = _GCmpTypes[i]->mpShutdown();
            }
        }
        fn_801D2BD0(_GCmpTypes);
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

int GCmpRegisterType(int index, GCmpCodec_t *pCodec)
{
    _GCmpTypes[index] = pCodec;
    return 0;
}

void GCmpCompress(int codec, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    GCmpStream_t *pStream = GCmpStart(0, codec, pSrc, pDst);

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

void GCmpDecompress(int codec, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    GCmpStream_t *pStream = GCmpStart(1, codec, pSrc, pDst);

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

GCmpStream_t *GCmpStart(int mode, int codec, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    GCmpStream_t *pStream = fn_801D2BB0(1, sizeof(GCmpStream_t), 4, 0);
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
            pStream->mpState = _GCmpTypes[pStream->mCodec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
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
            pStream->mpState = _GCmpTypes[pStream->mCodec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

void GCmpProcess(GCmpStream_t *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = _GCmpTypes[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = _GCmpTypes[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
}

void GCmpStop(GCmpStream_t *pStream)
{
    switch (pStream->mMode) {
    case 0:
        _GCmpTypes[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        _GCmpTypes[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
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
    GCmpCodec_t *pCodec;

    if (_GCmpTypes != 0) {
        pCodec = _GCmpTypes[index];
        if (pCodec != 0 && (pCodec->mFlags & 2)) {
            return 1;
        }
    }
    return 0;
}

GCmpStream_t *GCmpBlockStart(int codec, int mode, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    GCmpStream_t *pStream = fn_801D2BB0(1, sizeof(GCmpStream_t), 0, 0);

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
            pStream->mpState = _GCmpTypes[codec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        case 1:
            pStream->mpState = _GCmpTypes[codec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

unsigned int GCmpBlockProcess(GCmpStream_t *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = _GCmpTypes[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = _GCmpTypes[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
    return pStream->mStatus;
}

void GCmpBlockStop(GCmpStream_t *pStream)
{
    switch (pStream->mMode) {
    case 0:
        _GCmpTypes[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        _GCmpTypes[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    fn_801D2BD0(pStream);
}

int GCmpRead(GCmpBuffer_t *pBuffer, void *pOut, unsigned int size)
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

int GCmpWrite(GCmpBuffer_t *pBuffer, void *pIn, unsigned int size)
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
        strnzcpy(lbl_803018A8, "GCMP.LIB", 32);
    } else {
        fn_801C2D88(lbl_803018A8, 32, "%s", pName);
        lbl_803018A8[31] = 0;
    }
}
