/* Synchronised game clock: a 'timg' block in the state registry holding the
   game time and its tick counter, which the registry can reset, compare, save
   and restore; advancing the clock and reading ticks and elapsed time. */

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
extern void *SyncStateGetData(void *pHandle);
extern int fn_80238278(const void *p, int size, int seed);
int SyncTimeSaveState(void *p, void *pBuffer);
void SyncTimeSetTime(unsigned int time);
void SyncTimeCounterInit(void);
void SyncTimeCounterShutdown(void);
Counter_80237934 *SyncTimeNewCounter(int a, int b);
void SyncTimeDelCounter(Counter_80237934 *p);
void SyncTimeCounterSetMode(Counter_80237934 *p, int value);
void SyncTimeCounterSetStep(Counter_80237934 *p, int value);
void SyncTimeCounterAddTime(Counter_80237934 *p, int delta);
int SyncTimeCounterUpdate(Counter_80237934 *p);
int SyncTimeCounterGetTicks(Counter_80237934 *p);

int SyncTimeInitState(void *p, int value)
{
    Timer_80237780 *pTimer = p;

    pTimer->mUnknown8 = pTimer->mUnknown0;
    pTimer->mUnknown4 = pTimer->mUnknown0;
    pTimer->mpUnknown12 = SyncTimeNewCounter(0, lbl_803EC13C);
    return 0;
}

int SyncTimeShutdownState(void *p, int value)
{
    Timer_80237780 *pTimer = p;

    SyncTimeDelCounter(pTimer->mpUnknown12);
    return 0;
}

int SyncTimeCompareState(void *p, void *q)
{
    Timer_80237780 *pA = p;
    Timer_80237780 *pB = q;
    int result;

    if (pB != 0) {
        result = 0;
        result |= pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
        result |= SyncTimeCounterGetTicks(pA->mpUnknown12) != SyncTimeCounterGetTicks(pB->mpUnknown12);
    } else {
        result = fn_80238278(pA, sizeof(Timer_80237780), 0);
        result = fn_80238278(pA->mpUnknown12, sizeof(Counter_80237934), result);
    }
    return result;
}

int SyncTimeSaveState(void *p, void *pBuffer)
{
    Timer_80237780 *pTimer = p;
    *(Timer_80237780 *)pBuffer = *pTimer;
    pBuffer = (char *)pBuffer + 64;
    *(Counter_80237934 *)pBuffer = *pTimer->mpUnknown12;
    return 1;
}

int SyncTimeLoadState(void *p, void *pBuffer)
{
    Timer_80237780 *pTimer = p;
    TimerState_80237728 *pIn = pBuffer;

    *pTimer = pIn->mUnknown0;
    *pTimer->mpUnknown12 = pIn->mUnknown16;
    return 1;
}

int SyncTimeGetStateSize(void *p)
{
    return 32;
}

void SyncTimeInit(int a)
{
    void *pHandle;
    Timer_80237780 *pTimer;

    SyncTimeCounterInit();
    lbl_803EC13C = a;
    pHandle = SyncStateRegister(0, (void **)&lbl_803EC138, sizeof(Timer_80237780), 0, 0x74696D67);
    SyncStateSetCallbacks(pHandle, SyncTimeInitState, SyncTimeShutdownState, 0, SyncTimeCompareState);
    SyncStateSetSaveCallbacks(pHandle, SyncTimeSaveState, SyncTimeGetStateSize, SyncTimeLoadState);
    pTimer = SyncStateGetData(pHandle);
    pTimer->mUnknown4 = 0;
    pTimer->mUnknown0 = 0;
    SyncStateCommit(pHandle);
}

void SyncTimeAdvance(int delta)
{
    if (lbl_803EC138 != 0) {
        SyncTimeSetTime(lbl_803EC138->mUnknown8 + delta);
    }
}

void SyncTimeShutdown(void)
{
    SyncTimeCounterShutdown();
}

void SyncTimeSetTime(unsigned int time)
{
    unsigned int old = lbl_803EC138->mUnknown8;

    if (time > old) {
        lbl_803EC138->mUnknown8 = time;
        SyncTimeCounterAddTime(lbl_803EC138->mpUnknown12, time - old);
    }
}

unsigned int SyncTimeUpdateTicks(void)
{
    unsigned int value = 0;

    if (lbl_803EC138 != 0) {
        value = SyncTimeCounterUpdate(lbl_803EC138->mpUnknown12);
        lbl_803EC138->mUnknown4 += value;
    }
    return value;
}

int SyncTimeGetGameTime(void)
{
    int value = 0;

    if (lbl_803EC138 != 0) {
        value = lbl_803EC138->mUnknown4 - lbl_803EC138->mUnknown0;
    }
    return value;
}

void SyncTimeCounterInit(void)
{
}

void SyncTimeCounterShutdown(void)
{
}

Counter_80237934 *SyncTimeNewCounter(int a, int b)
{
    Counter_80237934 *p = fn_801D2B7C(sizeof(Counter_80237934), 0, 0);

    memset(p, 0, sizeof(Counter_80237934));
    SyncTimeCounterSetMode(p, a);
    SyncTimeCounterSetStep(p, b);
    return p;
}

void SyncTimeDelCounter(Counter_80237934 *p)
{
    fn_801D2BD0(p);
}

void SyncTimeCounterSetMode(Counter_80237934 *p, int value)
{
    p->mUnknown0 = value;
}

void SyncTimeCounterSetStep(Counter_80237934 *p, int value)
{
    p->mUnknown4 = value;
}

void SyncTimeCounterAddTime(Counter_80237934 *p, int delta)
{
    p->mUnknown12 += delta;
}

int SyncTimeCounterUpdate(Counter_80237934 *p)
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

int SyncTimeCounterGetTicks(Counter_80237934 *p)
{
    return p->mUnknown8;
}
