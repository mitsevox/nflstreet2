/* Audio event queue of the Audmon module: the game posts events (a type, a
   position and a few values), which are time-stamped and passed straight to
   the registered audio listeners. */

#include "engine/EvMonDesc.h"
#include "game/StyleTracker.h"
#include "engine/EvMonAddListener.h"
#include "game/AudmonEvent.h"
#include "game/fn_8009D990.h"

/* Descriptor passed to EvMonAlloc, which allocates mUnknown0 records of
   mUnknown4 bytes after mUnknown8 callback slots. */

typedef unsigned int (*AudmonClockFn_t)(int);

extern "C" {
void SndgHandleEvent(AudmonEvent_t *pRecord);
int MemFill(void *pDest, int size, int value, int width);
void EvMonFree(int handle);
void *EvMonGetCurrentRecord(int handle);
void EvMonFire(int handle, int unknown);
void EvMonClear(int handle);
}

static EvMonDesc_t _AudmonEvent_QueueDesc = { 50, sizeof(AudmonEvent_t), 3 };
static int _AudmonEvent_iQueue = 0xFF;
static AudmonClockFn_t _AudmonEvent_pfnClock = 0;

extern "C" void AudmonEventInit(void)
{
    _AudmonEvent_iQueue = EvMonAlloc(&_AudmonEvent_QueueDesc);
    _AudmonEvent_pfnClock = 0;
}

extern "C" void AudmonEventShutdown(void)
{
    EvMonFree(_AudmonEvent_iQueue);
    _AudmonEvent_iQueue = 0xFF;
}

extern "C" void AudmonEventStartInGame(void)
{
    _AudmonEvent_pfnClock = fn_8009D990;
    EvMonAddListener(_AudmonEvent_iQueue, SndgHandleEvent);
}

extern "C" AudmonEvent_t *AudmonEventGetRecord(void)
{
    return (AudmonEvent_t *)EvMonGetCurrentRecord(_AudmonEvent_iQueue);
}

extern "C" void AudmonEventClear(void)
{
    EvMonClear(_AudmonEvent_iQueue);
}

extern "C" void AudmonEventSend(void)
{
    AudmonEvent_t *p = AudmonEventGetRecord();

    if (_AudmonEvent_pfnClock) {
        p->mUnknown1C = _AudmonEvent_pfnClock(1);
    }
    EvMonFire(_AudmonEvent_iQueue, 0);
    StyleTrackerHandleAudioEvent(p);
}

extern "C" void AudmonEventPost(int type, Vector_80039F5C *pPos)
{
    AudmonEvent_t *p = AudmonEventGetRecord();

    MemFill(p, sizeof(*p), 0, 4);
    p->mType = type;
    if (pPos) {
        p->mPos.mX = pPos->mX;
        p->mPos.mY = pPos->mY;
        p->mPos.mZ = pPos->mZ;
    }
    AudmonEventSend();
}

extern "C" void AudmonEventPostArgs(int type, Vector_80039F5C *pPos, int a, int b, int c)
{
    AudmonEvent_t *p = AudmonEventGetRecord();

    MemFill(p, sizeof(*p), 0, 4);
    p->mType = type;
    p->mUnknown10.mValue = a;
    p->mUnknown14 = b;
    p->mUnknown18 = c;
    if (pPos) {
        p->mPos.mX = pPos->mX;
        p->mPos.mY = pPos->mY;
        p->mPos.mZ = pPos->mZ;
    }
    AudmonEventSend();
}

extern "C" void AudmonEventPostId(int type, Vector_80039F5C *pPos, int id, int a, int b, int c)
{
    AudmonEvent_t *p = AudmonEventGetRecord();

    MemFill(p, sizeof(*p), 0, 4);
    p->mType = type;
    p->mUnknown0 = id;
    p->mUnknown10.mValue = a;
    p->mUnknown14 = b;
    p->mUnknown18 = c;
    if (pPos) {
        p->mPos.mX = pPos->mX;
        p->mPos.mY = pPos->mY;
        p->mPos.mZ = pPos->mZ;
    }
    AudmonEventSend();
}

extern "C" void AudmonEventAddListener(AudmonEventFn_t pCallback)
{
    EvMonAddListener(_AudmonEvent_iQueue, pCallback);
}

extern "C" void AudmonEventRemoveListener(AudmonEventFn_t pCallback)
{
    EvMonRemoveListener(_AudmonEvent_iQueue, pCallback);
}
