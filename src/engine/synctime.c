/* Synchronised game clock: a 'timg' block in the state registry holding the
   game time and its tick counter, which the registry can reset, compare, save
   and restore; advancing the clock and reading ticks and elapsed time. */

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

typedef struct Counter_80237934 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Counter_80237934;

typedef struct Timer_80237780 {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    Counter_80237934 *mpUnknown12;
} Timer_80237780;

typedef struct TimerState_80237728 {
    Timer_80237780 mUnknown0;
    Counter_80237934 mUnknown16;
} TimerState_80237728;

extern Timer_80237780 *lbl_803EC138;
extern int lbl_803EC13C;
extern void *fn_8023816C(void *pHandle);
extern int fn_80238278(const void *p, int size, int seed);
int fn_802376D8(void *p, void *pBuffer);
void fn_80237888(unsigned int time);
void fn_8023792C(void);
void fn_80237930(void);
Counter_80237934 *fn_80237934(int a, int b);
void fn_8023799C(Counter_80237934 *p);
void fn_802379BC(Counter_80237934 *p, int value);
void fn_802379C4(Counter_80237934 *p, int value);
void fn_802379CC(Counter_80237934 *p, int delta);
int fn_802379DC(Counter_80237934 *p);
int fn_80237A28(Counter_80237934 *p);

int fn_8023758C(void *p, int value)
{
    Timer_80237780 *pTimer = p;

    pTimer->mUnknown8 = pTimer->mUnknown0;
    pTimer->mUnknown4 = pTimer->mUnknown0;
    pTimer->mpUnknown12 = fn_80237934(0, lbl_803EC13C);
    return 0;
}

int fn_802375D4(void *p, int value)
{
    Timer_80237780 *pTimer = p;

    fn_8023799C(pTimer->mpUnknown12);
    return 0;
}

int fn_802375FC(void *p, void *q)
{
    Timer_80237780 *pA = p;
    Timer_80237780 *pB = q;
    int result;

    if (pB != 0) {
        result = pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
        result |= fn_80237A28(pA->mpUnknown12) != fn_80237A28(pB->mpUnknown12);
    } else {
        result = fn_80238278(pA, sizeof(Timer_80237780), 0);
        result = fn_80238278(pA->mpUnknown12, sizeof(Counter_80237934), result);
    }
    return result;
}

int fn_802376D8(void *p, void *pBuffer)
{
    Timer_80237780 *pTimer = p;
    TimerState_80237728 *pOut = pBuffer;
    pOut->mUnknown0 = *pTimer;
    *(Counter_80237934 *)((char *)pBuffer + 64) = *pTimer->mpUnknown12;
    return 1;
}

int fn_80237728(void *p, void *pBuffer)
{
    Timer_80237780 *pTimer = p;
    TimerState_80237728 *pIn = pBuffer;

    *pTimer = pIn->mUnknown0;
    *pTimer->mpUnknown12 = pIn->mUnknown16;
    return 1;
}

int fn_80237778(void *p)
{
    return 32;
}

void fn_80237780(int a)
{
    void *pHandle;
    Timer_80237780 *pTimer;

    fn_8023792C();
    lbl_803EC13C = a;
    pHandle = fn_80238174(0, (void **)&lbl_803EC138, sizeof(Timer_80237780), 0, 0x74696D67);
    fn_80238234(pHandle, fn_8023758C, fn_802375D4, 0, fn_802375FC);
    fn_80238248(pHandle, fn_802376D8, fn_80237778, fn_80237728);
    pTimer = fn_8023816C(pHandle);
    pTimer->mUnknown4 = 0;
    pTimer->mUnknown0 = 0;
    fn_802381E0(pHandle);
}

void fn_80237830(int delta)
{
    if (lbl_803EC138 != 0) {
        fn_80237888(lbl_803EC138->mUnknown8 + delta);
    }
}

void fn_80237868(void)
{
    fn_80237930();
}

void fn_80237888(unsigned int time)
{
    unsigned int old = lbl_803EC138->mUnknown8;

    if (time > old) {
        lbl_803EC138->mUnknown8 = time;
        fn_802379CC(lbl_803EC138->mpUnknown12, time - old);
    }
}

unsigned int fn_802378C8(void)
{
    unsigned int value = 0;

    if (lbl_803EC138 != 0) {
        value = fn_802379DC(lbl_803EC138->mpUnknown12);
        lbl_803EC138->mUnknown4 += value;
    }
    return value;
}

int fn_8023790C(void)
{
    int value = 0;

    if (lbl_803EC138 != 0) {
        value = lbl_803EC138->mUnknown4 - lbl_803EC138->mUnknown0;
    }
    return value;
}

void fn_8023792C(void)
{
}

void fn_80237930(void)
{
}

Counter_80237934 *fn_80237934(int a, int b)
{
    Counter_80237934 *p = fn_801D2B7C(sizeof(Counter_80237934), 0, 0);

    memset(p, 0, sizeof(Counter_80237934));
    fn_802379BC(p, a);
    fn_802379C4(p, b);
    return p;
}

void fn_8023799C(Counter_80237934 *p)
{
    fn_801D2BD0(p);
}

void fn_802379BC(Counter_80237934 *p, int value)
{
    p->mUnknown0 = value;
}

void fn_802379C4(Counter_80237934 *p, int value)
{
    p->mUnknown4 = value;
}

void fn_802379CC(Counter_80237934 *p, int delta)
{
    p->mUnknown12 += delta;
}

int fn_802379DC(Counter_80237934 *p)
{
    int value = 0;

    if (p->mUnknown0 == 0) {
        if (p->mUnknown12 >= p->mUnknown4) {
            value = p->mUnknown4;
            p->mUnknown12 -= value;
        }
    } else if (p->mUnknown0 == 1) {
        value = p->mUnknown12;
        p->mUnknown12 = 0;
    }
    p->mUnknown8 = value;
    return value;
}

int fn_80237A28(Counter_80237934 *p)
{
    return p->mUnknown8;
}
