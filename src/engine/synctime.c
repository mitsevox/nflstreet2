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
    int mMode;
    int mStep;
    int mTicks;
    int mPending;
} SyncTimeCounter_t;

typedef struct SyncTime_t {
    unsigned int mStartTime;
    unsigned int mGameTime;
    unsigned int mTime;
    SyncTimeCounter_t *mpCounter;
} SyncTime_t;

typedef struct SyncTimeSave_t {
    SyncTime_t mClock;
    SyncTimeCounter_t mCounter;
} SyncTimeSave_t;

static SyncTime_t *_SyncTime_pState = 0;
static int _SyncTime_iStep = 1;
extern void *SyncStateGetData(void *pHandle);
extern int Crc32Update(const void *p, int size, int seed);
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

    pTimer->mTime = pTimer->mStartTime;
    pTimer->mGameTime = pTimer->mStartTime;
    pTimer->mpCounter = SyncTimeNewCounter(0, _SyncTime_iStep);
    return 0;
}

int SyncTimeShutdownState(void *p, int value)
{
    SyncTime_t *pTimer = p;

    SyncTimeDelCounter(pTimer->mpCounter);
    return 0;
}

int SyncTimeCompareState(void *p, void *q)
{
    SyncTime_t *pA = p;
    SyncTime_t *pB = q;
    int result;

    if (pB != 0) {
        result = 0;
        result |= pA->mStartTime != pB->mStartTime;
        result |= pA->mGameTime != pB->mGameTime;
        result |= pA->mTime != pB->mTime;
        result |= SyncTimeCounterGetTicks(pA->mpCounter) != SyncTimeCounterGetTicks(pB->mpCounter);
    } else {
        result = Crc32Update(pA, sizeof(SyncTime_t), 0);
        result = Crc32Update(pA->mpCounter, sizeof(SyncTimeCounter_t), result);
    }
    return result;
}

int SyncTimeSaveState(void *p, void *pBuffer)
{
    SyncTime_t *pTimer = p;
    *(SyncTime_t *)pBuffer = *pTimer;
    pBuffer = (char *)pBuffer + 64;
    *(SyncTimeCounter_t *)pBuffer = *pTimer->mpCounter;
    return 1;
}

int SyncTimeLoadState(void *p, void *pBuffer)
{
    SyncTime_t *pTimer = p;
    SyncTimeSave_t *pIn = pBuffer;

    *pTimer = pIn->mClock;
    *pTimer->mpCounter = pIn->mCounter;
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
    pTimer->mGameTime = 0;
    pTimer->mStartTime = 0;
    SyncStateCommit(pHandle);
}

void SyncTimeAdvance(int delta)
{
    if (_SyncTime_pState != 0) {
        SyncTimeSetTime(_SyncTime_pState->mTime + delta);
    }
}

void SyncTimeShutdown(void)
{
    SyncTimeCounterShutdown();
}

void SyncTimeSetTime(unsigned int time)
{
    unsigned int old = _SyncTime_pState->mTime;

    if (time > old) {
        _SyncTime_pState->mTime = time;
        SyncTimeCounterAddTime(_SyncTime_pState->mpCounter, time - old);
    }
}

unsigned int SyncTimeUpdateTicks(void)
{
    unsigned int value = 0;

    if (_SyncTime_pState != 0) {
        value = SyncTimeCounterUpdate(_SyncTime_pState->mpCounter);
        _SyncTime_pState->mGameTime += value;
    }
    return value;
}

int SyncTimeGetGameTime(void)
{
    int value = 0;

    if (_SyncTime_pState != 0) {
        value = _SyncTime_pState->mGameTime - _SyncTime_pState->mStartTime;
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
    p->mMode = value;
}

void SyncTimeCounterSetStep(SyncTimeCounter_t *p, int value)
{
    p->mStep = value;
}

void SyncTimeCounterAddTime(SyncTimeCounter_t *p, int delta)
{
    p->mPending += delta;
}

int SyncTimeCounterUpdate(SyncTimeCounter_t *p)
{
    int value = 0;

    if (p->mMode == 0) {
        if (p->mPending >= p->mStep) {
            value = p->mStep;
            p->mPending -= value;
        }
    } else if (p->mMode == 1) {
        value = p->mPending;
        p->mPending = 0;
    }
    p->mTicks = value;
    return value;
}

int SyncTimeCounterGetTicks(SyncTimeCounter_t *p)
{
    return p->mTicks;
}
