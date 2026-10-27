/* Random-number streams (linear congruential, shuffled minimal-standard and subtractive generators). */

#include <dolphin/os.h>
#include "game/cu_801CF5BC.h"
#include "game/fn_801D2B7C.h"

typedef struct RandStream_801CEFF0 {
    int mType;
} RandStream_801CEFF0;

typedef struct RandFast_801CEFF0 {
    int mType;
    unsigned int mSeed;
} RandFast_801CEFF0;

typedef struct RandSlow_801CEFF0 {
    int mType;
    int mY;
    int mTable[32];
    int mSeed;
} RandSlow_801CEFF0;

typedef struct RandSub_801CEFF0 {
    int mType;
    int mNext;
    int mNextP;
    int mInit;
    int mTable[56];
} RandSub_801CEFF0;

extern void *(*lbl_802F7AD0[])(int seed);
extern int (*lbl_802F7AE8[])(void *pDst, void *pSrc);
extern float (*lbl_802F7AF4[])(void *pStream);
extern int lbl_802F7B00[];


static void fn_801CF040(void *pHandle, int seed);
static void fn_801CF12C(void *pHandle, int seed);
static void fn_801CF358(void *pHandle, int seed);

static void *fn_801CEFF0(int seed)
{
    RandFast_801CEFF0 *pStream = fn_801D2B7C(sizeof(RandFast_801CEFF0), 0, 0);

    if (pStream) {
        fn_801CF040(pStream, seed);
    }
    return pStream;
}

static void fn_801CF040(void *pHandle, int seed)
{
    RandFast_801CEFF0 *pStream = pHandle;
    pStream->mSeed = seed;
}

static int fn_801CF048(void *pDstHandle, void *pSrcHandle)
{
    RandFast_801CEFF0 *pDst = pDstHandle;
    RandFast_801CEFF0 *pSrc = pSrcHandle;
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        pDst->mType = pSrc->mType;
        pDst->mSeed = pSrc->mSeed;
        result = 0;
    }
    return result;
}

static float fn_801CF074(void *pHandle)
{
    RandFast_801CEFF0 *pStream = pHandle;
    float value;

    pStream->mSeed = pStream->mSeed * 1664525 + 1013904223;
    value = (float)pStream->mSeed * 2.3283064e-10f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

static void *fn_801CF0DC(int seed)
{
    RandSlow_801CEFF0 *pStream = fn_801D2B7C(sizeof(RandSlow_801CEFF0), 0, 0);

    if (pStream) {
        fn_801CF12C(pStream, seed);
    }
    return pStream;
}

static void fn_801CF12C(void *pHandle, int seed)
{
    RandSlow_801CEFF0 *pStream = pHandle;
    int i;
    int k;

    if (seed == 0) {
        seed = 1;
    }
    for (i = 39; i >= 0; i--) {
        k = seed / 127773;
        seed = 16807 * (seed - k * 127773) - 2836 * k;
        if (seed < 0) {
            seed += 2147483647;
        }
        if (i < 32) {
            pStream->mTable[i] = seed;
        }
    }
    pStream->mY = pStream->mTable[0];
}

static int fn_801CF1B0(void *pDstHandle, void *pSrcHandle)
{
    RandSlow_801CEFF0 *pDst = pDstHandle;
    RandSlow_801CEFF0 *pSrc = pSrcHandle;
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        *pDst = *pSrc;
        result = 0;
    }
    return result;
}

static float fn_801CF240(void *pHandle)
{
    RandSlow_801CEFF0 *pStream = pHandle;
    int seed = pStream->mSeed;
    int k;
    int j;
    float value;

    k = seed / 127773;
    seed = 16807 * (seed - k * 127773) - 2836 * k;
    if (seed < 0) {
        seed += 2147483647;
    }
    j = pStream->mY / 67108864;
    pStream->mY = pStream->mTable[j];
    pStream->mTable[j] = seed;
    pStream->mSeed = seed;
    value = (float)seed * 4.65639582e-10f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

static void *fn_801CF308(int seed)
{
    RandSub_801CEFF0 *pStream = fn_801D2B7C(sizeof(RandSub_801CEFF0), 0, 0);

    if (pStream) {
        fn_801CF358(pStream, seed);
    }
    return pStream;
}

static void fn_801CF358(void *pHandle, int seed)
{
    RandSub_801CEFF0 *pStream = pHandle;
    int mj;
    int mk;
    int i;
    int ii;
    int k;

    if (seed == 0) {
        seed = 1;
    }
    mj = 161803398 - seed;
    mj %= 1000000000;
    pStream->mTable[55] = mj;
    mk = 1;
    for (i = 1; i <= 54; i++) {
        ii = (21 * i) % 55;
        pStream->mTable[ii] = mk;
        mk = mj - mk;
        if (mk < 0) {
            mk += 1000000000;
        }
        mj = pStream->mTable[ii];
    }
    for (k = 1; k <= 4; k++) {
        for (i = 1; i <= 55; i++) {
            pStream->mTable[i] -= pStream->mTable[1 + (i + 30) % 55];
            if (pStream->mTable[i] < 0) {
                pStream->mTable[i] += 1000000000;
            }
        }
    }
    pStream->mNext = 0;
    pStream->mNextP = 31;
    pStream->mInit = 1;
}

static int fn_801CF498(void *pDstHandle, void *pSrcHandle)
{
    RandSub_801CEFF0 *pDst = pDstHandle;
    RandSub_801CEFF0 *pSrc = pSrcHandle;
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        *pDst = *pSrc;
        result = 0;
    }
    return result;
}

static float fn_801CF504(void *pHandle)
{
    RandSub_801CEFF0 *pStream = pHandle;
    int mj;
    float value;

    if (++pStream->mNext > 55) {
        pStream->mNext = 1;
    }
    if (++pStream->mNextP > 55) {
        pStream->mNextP = 1;
    }
    mj = pStream->mTable[pStream->mNext] - pStream->mTable[pStream->mNextP];
    if (mj < 0) {
        mj += 1000000000;
    }
    pStream->mTable[pStream->mNext] = mj;
    value = (float)mj * 1e-9f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

void *fn_801CF5BC(int type, int seed)
{
    RandStream_801CEFF0 *pStream = lbl_802F7AD0[type](seed);

    if (pStream) {
        pStream->mType = type;
    }
    return pStream;
}

int fn_801CF60C(void *pDstHandle, void *pSrcHandle)
{
    RandStream_801CEFF0 *pDst = pDstHandle;
    RandStream_801CEFF0 *pSrc = pSrcHandle;
    int type = pDst->mType;
    int result = 0x40003;

    if (pDst && pSrc) {
        result = lbl_802F7AE8[type](pDst, pSrc);
    }
    return result;
}

int fn_801CF664(void *pHandle)
{
    RandStream_801CEFF0 *pStream = pHandle;
    return lbl_802F7B00[pStream->mType];
}

int fn_801CF67C(void *pStream)
{
    return fn_801D2BD0(pStream);
}

float fn_801CF69C(void *pHandle)
{
    RandStream_801CEFF0 *pStream = pHandle;
    return lbl_802F7AF4[pStream->mType](pStream);
}

unsigned int fn_801CF6D4(void *pStream, unsigned int range)
{
    float value = fn_801CF69C(pStream) * (float)range;

    if ((unsigned int)value >= range) {
        value = 0.0f;
    }
    return (unsigned int)value;
}

int fn_801CF7AC(void)
{
    return OSGetTick();
}

void *(*lbl_802F7AD0[3])(int seed) = {
    fn_801CEFF0, fn_801CF0DC, fn_801CF308
};

void (*lbl_802F7ADC[3])(void *pStream, int seed) = {
    fn_801CF040, fn_801CF12C, fn_801CF358
};

int (*lbl_802F7AE8[3])(void *pDst, void *pSrc) = {
    fn_801CF048, fn_801CF1B0, fn_801CF498
};

float (*lbl_802F7AF4[3])(void *pStream) = {
    fn_801CF074, fn_801CF240, fn_801CF504
};

int lbl_802F7B00[3] = {
    sizeof(RandFast_801CEFF0), sizeof(RandSlow_801CEFF0), sizeof(RandSub_801CEFF0)
};
