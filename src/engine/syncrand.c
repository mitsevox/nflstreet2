/* Synchronised random numbers: a 'rand' block of seeded random streams kept
   in the state registry, which can reset, compare, save and restore it; draws
   from a stream, ranged draws and a no-repeat bit pool built on them. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
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

typedef struct Random_80236F78 {
    unsigned char mUnknown0;
    signed char mUnknown1;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    char mUnknown16[4];
    void **mpUnknown20;
} Random_80236F78;

typedef struct Bits_80237438 {
    unsigned int mUnknown0;
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8[1];
} Bits_80237438;

extern Random_80236F78 *lbl_803EC130;
extern int lbl_803EC134;
extern void *SyncStateGetData(void *pHandle);
int SyncRandSaveState(void *p, void *pBuffer);
int SyncRandLoadState(void *p, void *pBuffer);

int SyncRandInitState(void *p, int value)
{
    Random_80236F78 *pRandom = p;
    int i;
    int seed;

    pRandom->mpUnknown20 = fn_801D2B7C(pRandom->mUnknown0 * 4, 0, 0);
    pRandom->mUnknown8 = 0;
    pRandom->mUnknown12 = 0;
    seed = pRandom->mUnknown4;
    for (i = 0; i < pRandom->mUnknown0; i++) {
        pRandom->mpUnknown20[i] = MathNewRandomStream(0, seed);
        seed = MathGetRandomRange(pRandom->mpUnknown20[i], 0x7FFFFFFF);
    }
    return 0;
}

int SyncRandShutdownState(void *p, int value)
{
    Random_80236F78 *pRandom = p;

    while (pRandom->mUnknown0-- != 0) {
        MathDelRandomStream(pRandom->mpUnknown20[pRandom->mUnknown0]);
    }
    fn_801D2BD0(pRandom->mpUnknown20);
    return 0;
}

int SyncRandCompareState(void *p, void *q)
{
    Random_80236F78 *pA = p;
    Random_80236F78 *pB = q;
    int result;

    if (pB != 0) {
        result = 0;
        result |= pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
    } else {
        result = pA->mUnknown12;
    }
    return result;
}

int SyncRandSaveState(void *p, void *pBuffer)
{
    Random_80236F78 *pRandom = p;
    memcpy(pBuffer, pRandom, sizeof(Random_80236F78));
    MathCopyRandomStream((char *)pBuffer + 24, pRandom->mpUnknown20[0]);
    return 1;
}

int SyncRandLoadState(void *p, void *pBuffer)
{
    Random_80236F78 *pRandom = p;
    memcpy(pRandom, pBuffer, sizeof(Random_80236F78));
    MathCopyRandomStream(pRandom->mpUnknown20[0], (char *)pBuffer + 24);
    return 1;
}

int SyncRandGetStateSize(void *p)
{
    return MathGetRandomStreamSize(lbl_803EC130->mpUnknown20[0]) + sizeof(Random_80236F78);
}

void SyncRandInit(int count, int seed)
{
    void *pHandle;
    Random_80236F78 *pRandom;

    pHandle = SyncStateRegister(0, (void **)&lbl_803EC130, sizeof(Random_80236F78), 0, 0x72616E64);
    SyncStateSetCallbacks(pHandle, SyncRandInitState, SyncRandShutdownState, 0, SyncRandCompareState);
    SyncStateSetSaveCallbacks(pHandle, SyncRandSaveState, SyncRandGetStateSize, SyncRandLoadState);
    pRandom = SyncStateGetData(pHandle);
    pRandom->mUnknown0 = count;
    pRandom->mUnknown4 = seed;
    pRandom->mUnknown12 = seed;
    SyncStateCommit(pHandle);
}

void SyncRandShutdown(void)
{
}

float SyncRandGetFloat(int stream)
{
    float value;

    value = MathGetRandom(lbl_803EC130->mpUnknown20[stream]);
    if (stream == 0) {
        lbl_803EC130->mUnknown8++;
        lbl_803EC130->mUnknown12++;
    } else if (lbl_803EC130->mUnknown1 != 0) {
        if (lbl_803EC130->mUnknown1 < 0) {
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

    value = MathGetRandomRange(lbl_803EC130->mpUnknown20[stream], count);
    if (stream == 0) {
        lbl_803EC130->mUnknown8++;
        lbl_803EC130->mUnknown12 = (lbl_803EC130->mUnknown12 ^ count) + 7;
    } else if (lbl_803EC130->mUnknown1 != 0 && count > 1) {
        lbl_803EC134 = value = 1 - lbl_803EC134;
        if (!(lbl_803EC130->mUnknown1 & 0x80)) {
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

void SyncRandBitPoolClear(Bits_80237438 *pBits)
{
    unsigned int i;
    unsigned char *pData = pBits->mUnknown8;
    unsigned int count = (pBits->mUnknown0 + 7) >> 3;

    for (i = 0; i < count; i++) {
        *pData++ = 0;
    }
}

Bits_80237438 *SyncRandBitPoolNew(int stream, unsigned int count)
{
    Bits_80237438 *pBits = fn_801D2B7C(((count + 7) >> 3) + 8, 0, 0);

    pBits->mUnknown0 = count;
    pBits->mUnknown4 = stream;
    SyncRandBitPoolClear(pBits);
    return pBits;
}

int SyncRandBitPoolDraw(Bits_80237438 *pBits)
{
    unsigned int i;
    unsigned int index;
    int bit;
    unsigned int start;
    unsigned char *pData = pBits->mUnknown8;

    i = SyncRandGetRange(pBits->mUnknown4, pBits->mUnknown0);
    index = i >> 3;
    bit = i & 7;
    start = i;
    while ((pData[index] >> bit) & 1) {
        i = (i + 1) % pBits->mUnknown0;
        index = i >> 3;
        bit = i & 7;
        if (i == start) {
            SyncRandBitPoolClear(pBits);
        }
    }
    pData[index] |= 1 << bit;
    return i;
}

void SyncRandBitPoolDelete(Bits_80237438 *pBits)
{
    fn_801D2BD0(pBits);
}
