/* Synchronised random numbers: a 'rand' block of seeded random streams kept
   in the state registry, which can reset, compare, save and restore it; draws
   from a stream, ranged draws and a no-repeat bit pool built on them. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
#include "engine/fn_80238680.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
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
extern void *fn_8023816C(void *pHandle);
int fn_802370E8(void *p, void *pBuffer);
int fn_80237138(void *p, void *pBuffer);

int fn_80236F78(void *p, int value)
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

int fn_8023701C(void *p, int value)
{
    Random_80236F78 *pRandom = p;

    while (pRandom->mUnknown0-- != 0) {
        MathDelRandomStream(pRandom->mpUnknown20[pRandom->mUnknown0]);
    }
    fn_801D2BD0(pRandom->mpUnknown20);
    return 0;
}

int fn_80237080(void *p, void *q)
{
    Random_80236F78 *pA = p;
    Random_80236F78 *pB = q;
    int result;

    if (pB != 0) {
        result = pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
        return result;
    }
    return pA->mUnknown12;
}

int fn_802370E8(void *p, void *pBuffer)
{
    Random_80236F78 *pRandom = p;
    memcpy(pBuffer, pRandom, sizeof(Random_80236F78));
    MathCopyRandomStream((char *)pBuffer + 24, pRandom->mpUnknown20[0]);
    return 1;
}

int fn_80237138(void *p, void *pBuffer)
{
    Random_80236F78 *pRandom = p;
    memcpy(pRandom, pBuffer, sizeof(Random_80236F78));
    MathCopyRandomStream(pRandom->mpUnknown20[0], (char *)pBuffer + 24);
    return 1;
}

int fn_80237180(void *p)
{
    return MathGetRandomStreamSize(lbl_803EC130->mpUnknown20[0]) + sizeof(Random_80236F78);
}

void fn_802371B0(int count, int seed)
{
    void *pHandle;
    Random_80236F78 *pRandom;

    pHandle = fn_80238174(0, (void **)&lbl_803EC130, sizeof(Random_80236F78), 0, 0x72616E64);
    fn_80238234(pHandle, fn_80236F78, fn_8023701C, 0, fn_80237080);
    fn_80238248(pHandle, fn_802370E8, fn_80237180, fn_80237138);
    pRandom = fn_8023816C(pHandle);
    pRandom->mUnknown0 = count;
    pRandom->mUnknown4 = seed;
    pRandom->mUnknown12 = seed;
    fn_802381E0(pHandle);
}

void fn_8023725C(void)
{
}

unsigned int fn_802372EC(int stream, unsigned int count)
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

int fn_80237390(int stream, int low, int high)
{
    return fn_802372EC(stream, high - low + 1) + low;
}

void fn_80237438(Bits_80237438 *pBits)
{
    unsigned int i;
    unsigned char *pData = pBits->mUnknown8;
    unsigned int count = (pBits->mUnknown0 + 7) >> 3;

    for (i = 0; i < count; i++) {
        *pData++ = 0;
    }
}

Bits_80237438 *fn_80237470(int stream, unsigned int count)
{
    Bits_80237438 *pBits = fn_801D2B7C(((count + 7) >> 3) + 8, 0, 0);

    pBits->mUnknown0 = count;
    pBits->mUnknown4 = stream;
    fn_80237438(pBits);
    return pBits;
}

int fn_802374C8(Bits_80237438 *pBits)
{
    unsigned int i;
    unsigned int index;
    int bit;
    unsigned int start;
    unsigned char *pData = pBits->mUnknown8;

    i = fn_802372EC(pBits->mUnknown4, pBits->mUnknown0);
    index = i >> 3;
    bit = i & 7;
    start = i;
    while ((pData[index] >> bit) & 1) {
        i = (i + 1) % pBits->mUnknown0;
        index = i >> 3;
        bit = i & 7;
        if (i == start) {
            fn_80237438(pBits);
        }
    }
    pData[index] |= 1 << bit;
    return i;
}

void fn_8023756C(Bits_80237438 *pBits)
{
    fn_801D2BD0(pBits);
}
