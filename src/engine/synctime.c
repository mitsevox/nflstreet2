/* Synchronised game clock: a 'timg' block in the state registry holding the
   game time and its tick counter, which the registry can reset, compare, save
   and restore; advancing the clock and reading ticks and elapsed time. */

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

typedef struct SyncTimeCounter_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} SyncTimeCounter_t;

typedef struct SyncTime_t {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    SyncTimeCounter_t *mpUnknown12;
} SyncTime_t;

typedef struct SyncTimeSave_t {
    SyncTime_t mUnknown0;
    SyncTimeCounter_t mUnknown16;
} SyncTimeSave_t;

extern SyncTime_t *_SyncTime_pState;
extern int _SyncTime_iStep;
extern void *SyncStateGetData(void *pHandle);
extern int fn_80238278(const void *p, int size, int seed);
int SyncTimeSaveState(void *p, void *pBuffer);
void SyncTimeSetTime(unsigned int time);
void SyncTimeCounterInit(void);
void SyncTimeCounterShutdown(void);
SyncTimeCounter_t *SyncTimeNewCounter(int a, int b);
void SyncTimeDelCounter(SyncTimeCounter_t *p);
void SyncTimeCounterSetMode(SyncTimeCounter_t *p, int value);
void SyncTimeCounterSetStep(SyncTimeCounter_t *p, int value);
void SyncTimeCounterAddTime(SyncTimeCounter_t *p, int delta);
int SyncTimeCounterUpdate(SyncTimeCounter_t *p);
int SyncTimeCounterGetTicks(SyncTimeCounter_t *p);

int SyncTimeInitState(void *p, int value)
{
    SyncTime_t *pTimer = p;

    pTimer->mUnknown8 = pTimer->mUnknown0;
    pTimer->mUnknown4 = pTimer->mUnknown0;
    pTimer->mpUnknown12 = SyncTimeNewCounter(0, _SyncTime_iStep);
    return 0;
}

int SyncTimeShutdownState(void *p, int value)
{
    SyncTime_t *pTimer = p;

    SyncTimeDelCounter(pTimer->mpUnknown12);
    return 0;
}

int SyncTimeCompareState(void *p, void *q)
{
    SyncTime_t *pA = p;
    SyncTime_t *pB = q;
    int result;

    if (pB != 0) {
        result = 0;
        result |= pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
        result |= SyncTimeCounterGetTicks(pA->mpUnknown12) != SyncTimeCounterGetTicks(pB->mpUnknown12);
    } else {
        result = fn_80238278(pA, sizeof(SyncTime_t), 0);
        result = fn_80238278(pA->mpUnknown12, sizeof(SyncTimeCounter_t), result);
    }
    return result;
}

int SyncTimeSaveState(void *p, void *pBuffer)
{
    SyncTime_t *pTimer = p;
    *(SyncTime_t *)pBuffer = *pTimer;
    pBuffer = (char *)pBuffer + 64;
    *(SyncTimeCounter_t *)pBuffer = *pTimer->mpUnknown12;
    return 1;
}

int SyncTimeLoadState(void *p, void *pBuffer)
{
    SyncTime_t *pTimer = p;
    SyncTimeSave_t *pIn = pBuffer;

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
    SyncTime_t *pTimer;

    SyncTimeCounterInit();
    _SyncTime_iStep = a;
    pHandle = SyncStateRegister(0, (void **)&_SyncTime_pState, sizeof(SyncTime_t), 0, 0x74696D67);
    SyncStateSetCallbacks(pHandle, SyncTimeInitState, SyncTimeShutdownState, 0, SyncTimeCompareState);
    SyncStateSetSaveCallbacks(pHandle, SyncTimeSaveState, SyncTimeGetStateSize, SyncTimeLoadState);
    pTimer = SyncStateGetData(pHandle);
    pTimer->mUnknown4 = 0;
    pTimer->mUnknown0 = 0;
    SyncStateCommit(pHandle);
}

void SyncTimeAdvance(int delta)
{
    if (_SyncTime_pState != 0) {
        SyncTimeSetTime(_SyncTime_pState->mUnknown8 + delta);
    }
}

void SyncTimeShutdown(void)
{
    SyncTimeCounterShutdown();
}

void SyncTimeSetTime(unsigned int time)
{
    unsigned int old = _SyncTime_pState->mUnknown8;

    if (time > old) {
        _SyncTime_pState->mUnknown8 = time;
        SyncTimeCounterAddTime(_SyncTime_pState->mpUnknown12, time - old);
    }
}

unsigned int SyncTimeUpdateTicks(void)
{
    unsigned int value = 0;

    if (_SyncTime_pState != 0) {
        value = SyncTimeCounterUpdate(_SyncTime_pState->mpUnknown12);
        _SyncTime_pState->mUnknown4 += value;
    }
    return value;
}

int SyncTimeGetGameTime(void)
{
    int value = 0;

    if (_SyncTime_pState != 0) {
        value = _SyncTime_pState->mUnknown4 - _SyncTime_pState->mUnknown0;
    }
    return value;
}

void SyncTimeCounterInit(void)
{
}

void SyncTimeCounterShutdown(void)
{
}

SyncTimeCounter_t *SyncTimeNewCounter(int a, int b)
{
    SyncTimeCounter_t *p = fn_801D2B7C(sizeof(SyncTimeCounter_t), 0, 0);

    memset(p, 0, sizeof(SyncTimeCounter_t));
    SyncTimeCounterSetMode(p, a);
    SyncTimeCounterSetStep(p, b);
    return p;
}

void SyncTimeDelCounter(SyncTimeCounter_t *p)
{
    fn_801D2BD0(p);
}

void SyncTimeCounterSetMode(SyncTimeCounter_t *p, int value)
{
    p->mUnknown0 = value;
}

void SyncTimeCounterSetStep(SyncTimeCounter_t *p, int value)
{
    p->mUnknown4 = value;
}

void SyncTimeCounterAddTime(SyncTimeCounter_t *p, int delta)
{
    p->mUnknown12 += delta;
}

int SyncTimeCounterUpdate(SyncTimeCounter_t *p)
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

int SyncTimeCounterGetTicks(SyncTimeCounter_t *p)
{
    return p->mUnknown8;
}
