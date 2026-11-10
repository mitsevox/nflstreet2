/* Audio event queue of the Audmon module: the game posts events (a type, a
   position and a few values), which are time-stamped and passed straight to
   the registered audio listeners. */

#include "engine/Desc_80238424.h"
#include "game/StyleTracker.h"
#include "engine/fn_80238680.h"
#include "game/AudmonEvent.h"
#include "game/fn_8009D990.h"

/* Descriptor passed to fn_80238424, which allocates mUnknown0 records of
   mUnknown4 bytes after mUnknown8 callback slots. */

typedef unsigned int (*AudmonClockFn_t)(int);

extern "C" {
void SndgHandleEvent(AudmonEvent_t *pRecord);
int MemFill(void *pDest, int size, int value, int width);
void fn_802384C4(int handle);
void *fn_8023850C(int handle);
void fn_80238570(int handle, int unknown);
void fn_8023861C(int handle);
}

static Desc_80238424 _AudmonEvent_QueueDesc = { 50, sizeof(AudmonEvent_t), 3 };
static int _AudmonEvent_iQueue = 0xFF;
static AudmonClockFn_t _AudmonEvent_pfnClock = 0;

extern "C" void AudmonEventInit(void)
{
    _AudmonEvent_iQueue = fn_80238424(&_AudmonEvent_QueueDesc);
    _AudmonEvent_pfnClock = 0;
}

extern "C" void AudmonEventShutdown(void)
{
    fn_802384C4(_AudmonEvent_iQueue);
    _AudmonEvent_iQueue = 0xFF;
}

extern "C" void AudmonEventStartInGame(void)
{
    _AudmonEvent_pfnClock = fn_8009D990;
    fn_80238680(_AudmonEvent_iQueue, SndgHandleEvent);
}

extern "C" AudmonEvent_t *AudmonEventGetRecord(void)
{
    return (AudmonEvent_t *)fn_8023850C(_AudmonEvent_iQueue);
}

extern "C" void AudmonEventClear(void)
{
    fn_8023861C(_AudmonEvent_iQueue);
}

extern "C" void AudmonEventSend(void)
{
    AudmonEvent_t *p = AudmonEventGetRecord();

    if (_AudmonEvent_pfnClock) {
        p->mUnknown1C = _AudmonEvent_pfnClock(1);
    }
    fn_80238570(_AudmonEvent_iQueue, 0);
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
    fn_80238680(_AudmonEvent_iQueue, pCallback);
}

extern "C" void AudmonEventRemoveListener(AudmonEventFn_t pCallback)
{
    fn_802386DC(_AudmonEvent_iQueue, pCallback);
}
