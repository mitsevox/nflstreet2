/* Synchronised random numbers: a 'rand' block of seeded random streams kept
   in the state registry, which can reset, compare, save and restore it; draws
   from a stream, ranged draws and a no-repeat bit pool built on them. */

#include "engine/SyncStateGroup.h"
#include "engine/EvMonDesc.h"
#include "engine/EvMonAddListener.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/SyncStateRegister.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct SyncRand_t {
    unsigned char mNumStreams;
    signed char mOverride;
    int mSeed;
    int mNumDraws;
    int mChecksum;
    char mUnknown16[4];
    void **mpStreams;
} SyncRand_t;

typedef struct SyncRandBitPool_t {
    unsigned int mCount;
    unsigned char mStream;
    char mUnknown5[3];
    unsigned char mBits[1];
} SyncRandBitPool_t;

static SyncRand_t *_SyncRand_pState = 0;
static int _SyncRand_iToggle = 0;
extern void *SyncStateGetData(void *pHandle);
int SyncRandSaveState(void *p, void *pBuffer);
int SyncRandLoadState(void *p, void *pBuffer);

int SyncRandInitState(void *p, int value)
{
    SyncRand_t *pRandom = p;
    int i;
    int seed;

    pRandom->mpStreams = fn_801D2B7C(pRandom->mNumStreams * 4, 0, 0);
    pRandom->mNumDraws = 0;
    pRandom->mChecksum = 0;
    seed = pRandom->mSeed;
    for (i = 0; i < pRandom->mNumStreams; i++) {
        pRandom->mpStreams[i] = MathNewRandomStream(0, seed);
        seed = MathGetRandomRange(pRandom->mpStreams[i], 0x7FFFFFFF);
    }
    return 0;
}

int SyncRandShutdownState(void *p, int value)
{
    SyncRand_t *pRandom = p;

    while (pRandom->mNumStreams-- != 0) {
        MathDelRandomStream(pRandom->mpStreams[pRandom->mNumStreams]);
    }
    fn_801D2BD0(pRandom->mpStreams);
    return 0;
}

int SyncRandCompareState(void *p, void *q)
{
    SyncRand_t *pA = p;
    SyncRand_t *pB = q;
    int result;

    if (pB != 0) {
        result = 0;
        result |= pA->mNumStreams != pB->mNumStreams;
        result |= pA->mSeed != pB->mSeed;
        result |= pA->mNumDraws != pB->mNumDraws;
    } else {
        result = pA->mChecksum;
    }
    return result;
}

int SyncRandSaveState(void *p, void *pBuffer)
{
    SyncRand_t *pRandom = p;
    memcpy(pBuffer, pRandom, sizeof(SyncRand_t));
    MathCopyRandomStream((char *)pBuffer + 24, pRandom->mpStreams[0]);
    return 1;
}

int SyncRandLoadState(void *p, void *pBuffer)
{
    SyncRand_t *pRandom = p;
    memcpy(pRandom, pBuffer, sizeof(SyncRand_t));
    MathCopyRandomStream(pRandom->mpStreams[0], (char *)pBuffer + 24);
    return 1;
}

int SyncRandGetStateSize(void *p)
{
    return MathGetRandomStreamSize(_SyncRand_pState->mpStreams[0]) + sizeof(SyncRand_t);
}

void SyncRandInit(int count, int seed)
{
    void *pHandle;
    SyncRand_t *pRandom;

    pHandle = SyncStateRegister(0, (void **)&_SyncRand_pState, sizeof(SyncRand_t), 0, 0x72616E64);
    SyncStateSetCallbacks(pHandle, SyncRandInitState, SyncRandShutdownState, 0, SyncRandCompareState);
    SyncStateSetSaveCallbacks(pHandle, SyncRandSaveState, SyncRandGetStateSize, SyncRandLoadState);
    pRandom = SyncStateGetData(pHandle);
    pRandom->mNumStreams = count;
    pRandom->mSeed = seed;
    pRandom->mChecksum = seed;
    SyncStateCommit(pHandle);
}

void SyncRandShutdown(void)
{
}

float SyncRandGetFloat(int stream)
{
    float value;

    value = MathGetRandom(_SyncRand_pState->mpStreams[stream]);
    if (stream == 0) {
        _SyncRand_pState->mNumDraws++;
        _SyncRand_pState->mChecksum++;
    } else if (_SyncRand_pState->mOverride != 0) {
        if (_SyncRand_pState->mOverride < 0) {
            value = 0.0f;
        } else {
            value = 0.9999f;
        }
    }
    return value;
}

unsigned int SyncRandGetRange(int stream, unsigned int count)
{
    unsigned int value;

    value = MathGetRandomRange(_SyncRand_pState->mpStreams[stream], count);
    if (stream == 0) {
        _SyncRand_pState->mNumDraws++;
        _SyncRand_pState->mChecksum = (_SyncRand_pState->mChecksum ^ count) + 7;
    } else if (_SyncRand_pState->mOverride != 0 && count > 1) {
        _SyncRand_iToggle = value = 1 - _SyncRand_iToggle;
        if (!(_SyncRand_pState->mOverride & 0x80)) {
            value = count - 1 - value;
        }
    }
    return value;
}

int SyncRandGetIntRange(int stream, int low, int high)
{
    return SyncRandGetRange(stream, high - low + 1) + low;
}

float SyncRandGetFloatRange(int stream, float low, float high)
{
    float range = high - low;
    float value = SyncRandGetFloat(stream);

    if (value >= 0.99999976f) {
        value = 1.0f;
    } else if (value <= 1e-7f) {
        value = 0.0f;
    }
    return range * value + low;
}

void SyncRandBitPoolClear(SyncRandBitPool_t *pBits)
{
    unsigned int i;
    unsigned char *pData = pBits->mBits;
    unsigned int count = (pBits->mCount + 7) >> 3;

    for (i = 0; i < count; i++) {
        *pData++ = 0;
    }
}

SyncRandBitPool_t *SyncRandBitPoolNew(int stream, unsigned int count)
{
    SyncRandBitPool_t *pBits = fn_801D2B7C(((count + 7) >> 3) + 8, 0, 0);

    pBits->mCount = count;
    pBits->mStream = stream;
    SyncRandBitPoolClear(pBits);
    return pBits;
}

int SyncRandBitPoolDraw(SyncRandBitPool_t *pBits)
{
    unsigned int i;
    unsigned int index;
    int bit;
    unsigned int start;
    unsigned char *pData = pBits->mBits;

    i = SyncRandGetRange(pBits->mStream, pBits->mCount);
    index = i >> 3;
    bit = i & 7;
    start = i;
    while ((pData[index] >> bit) & 1) {
        i = (i + 1) % pBits->mCount;
        index = i >> 3;
        bit = i & 7;
        if (i == start) {
            SyncRandBitPoolClear(pBits);
        }
    }
    pData[index] |= 1 << bit;
    return i;
}

void SyncRandBitPoolDelete(SyncRandBitPool_t *pBits)
{
    fn_801D2BD0(pBits);
}
