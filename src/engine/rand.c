/* Random-number streams (linear congruential, shuffled minimal-standard and subtractive generators). */

#include <dolphin/os.h>
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"

typedef struct RandStream_t {
    int mType;
} RandStream_t;

typedef struct RandFast_t {
    int mType;
    unsigned int mSeed;
} RandFast_t;

typedef struct RandSlow_t {
    int mType;
    int mY;
    int mTable[32];
    int mSeed;
} RandSlow_t;

typedef struct RandSub_t {
    int mType;
    int mNext;
    int mNextP;
    int mInit;
    int mTable[56];
} RandSub_t;

extern void *(*_MathRand_aInitFuncs[])(int seed);
extern int (*_MathRand_aCopyFuncs[])(void *pDst, void *pSrc);
extern float (*_MathRand_aGetFuncs[])(void *pStream);
extern int _MathRand_Size[];


static void _MathRandResetFastLinear(void *pHandle, int seed);
static void _MathRandResetSlowLinear(void *pHandle, int seed);
static void _MathRandResetSubtractive(void *pHandle, int seed);

static void *_MathRandInitFastLinear(int seed)
{
    RandFast_t *pStream = fn_801D2B7C(sizeof(RandFast_t), 0, 0);

    if (pStream) {
        _MathRandResetFastLinear(pStream, seed);
    }
    return pStream;
}

static void _MathRandResetFastLinear(void *pHandle, int seed)
{
    RandFast_t *pStream = pHandle;
    pStream->mSeed = seed;
}

/* Copy state only between streams of the same generator type. */
static int _MathRandCopyFastLinear(void *pDstHandle, void *pSrcHandle)
{
    RandFast_t *pDst = pDstHandle;
    RandFast_t *pSrc = pSrcHandle;
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        pDst->mType = pSrc->mType;
        pDst->mSeed = pSrc->mSeed;
        result = 0;
    }
    return result;
}

static float _MathRandFastLinear(void *pHandle)
{
    RandFast_t *pStream = pHandle;
    float value;

    pStream->mSeed = pStream->mSeed * 1664525 + 1013904223;
    value = (float)pStream->mSeed * 2.3283064e-10f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

static void *_MathRandInitSlowLinear(int seed)
{
    RandSlow_t *pStream = fn_801D2B7C(sizeof(RandSlow_t), 0, 0);

    if (pStream) {
        _MathRandResetSlowLinear(pStream, seed);
    }
    return pStream;
}

static void _MathRandResetSlowLinear(void *pHandle, int seed)
{
    RandSlow_t *pStream = pHandle;
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

static int _MathRandCopySlowLinear(void *pDstHandle, void *pSrcHandle)
{
    RandSlow_t *pDst = pDstHandle;
    RandSlow_t *pSrc = pSrcHandle;
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        *pDst = *pSrc;
        result = 0;
    }
    return result;
}

static float _MathRandSlowLinear(void *pHandle)
{
    RandSlow_t *pStream = pHandle;
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

static void *_MathRandInitSubtractive(int seed)
{
    RandSub_t *pStream = fn_801D2B7C(sizeof(RandSub_t), 0, 0);

    if (pStream) {
        _MathRandResetSubtractive(pStream, seed);
    }
    return pStream;
}

static void _MathRandResetSubtractive(void *pHandle, int seed)
{
    RandSub_t *pStream = pHandle;
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

static int _MathRandCopySubtractive(void *pDstHandle, void *pSrcHandle)
{
    RandSub_t *pDst = pDstHandle;
    RandSub_t *pSrc = pSrcHandle;
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        *pDst = *pSrc;
        result = 0;
    }
    return result;
}

static float _MathRandSubtractive(void *pHandle)
{
    RandSub_t *pStream = pHandle;
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

void *MathNewRandomStream(int type, int seed)
{
    RandStream_t *pStream = _MathRand_aInitFuncs[type](seed);

    if (pStream) {
        pStream->mType = type;
    }
    return pStream;
}

int MathCopyRandomStream(void *pDstHandle, void *pSrcHandle)
{
    RandStream_t *pDst = pDstHandle;
    RandStream_t *pSrc = pSrcHandle;
    int type = pDst->mType;
    int result = 0x40003;

    if (pDst && pSrc) {
        result = _MathRand_aCopyFuncs[type](pDst, pSrc);
    }
    return result;
}

int MathGetRandomStreamSize(void *pHandle)
{
    RandStream_t *pStream = pHandle;
    return _MathRand_Size[pStream->mType];
}

int MathDelRandomStream(void *pStream)
{
    return fn_801D2BD0(pStream);
}

float MathGetRandom(void *pHandle)
{
    RandStream_t *pStream = pHandle;
    return _MathRand_aGetFuncs[pStream->mType](pStream);
}

unsigned int MathGetRandomRange(void *pStream, unsigned int range)
{
    float value = MathGetRandom(pStream) * (float)range;

    if ((unsigned int)value >= range) {
        value = 0.0f;
    }
    return (unsigned int)value;
}

int MathGetRandomSeed(void)
{
    return OSGetTick();
}

void *(*_MathRand_aInitFuncs[3])(int seed) = {
    _MathRandInitFastLinear, _MathRandInitSlowLinear, _MathRandInitSubtractive
};

void (*_MathRand_aResetFuncs[3])(void *pStream, int seed) = {
    _MathRandResetFastLinear, _MathRandResetSlowLinear, _MathRandResetSubtractive
};

int (*_MathRand_aCopyFuncs[3])(void *pDst, void *pSrc) = {
    _MathRandCopyFastLinear, _MathRandCopySlowLinear, _MathRandCopySubtractive
};

float (*_MathRand_aGetFuncs[3])(void *pStream) = {
    _MathRandFastLinear, _MathRandSlowLinear, _MathRandSubtractive
};

int _MathRand_Size[3] = {
    sizeof(RandFast_t), sizeof(RandSlow_t), sizeof(RandSub_t)
};
