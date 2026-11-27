/* Pause request: when a pad's input asks to pause during play, remembers the
   request so that the pause manager opens the in-game pause screen for that
   pad. */

#include "game/MiniGameC.h"
#include "game/PauseMenu.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800B65A0.h"

/* Request latched by PauseRequestHandleInput and handed out once through the slot-0 callback PauseRequestPoll. */
struct PauseRequest_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    unsigned char mPending;
};

extern void *gpReplay;

extern "C" {
int ReplayIsShowing(void *p);
int CelebrationBlockIsActive(int a);
int fn_8009D86C(void);
int GamebreakerIsCutscenePlaying(void);
int fn_800B6644(int a);
int fn_800BA6F8(void);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
int ScrmGetScoreGoal(int *pValue);
int ScrmGetWinner(void);

static PauseRequest_t _PauseRequest_Request;

void PauseRequestReset(void)
{
    _PauseRequest_Request.mUnknown0 = 0xFFFF;
    _PauseRequest_Request.mUnknown2 = 0xFFFF;
    _PauseRequest_Request.mUnknown4 = -1;
    _PauseRequest_Request.mPending = 0;
}

int PauseRequestPoll(unsigned short *pA, unsigned short *pB, int *pC)
{
    int result = 0;

    if (_PauseRequest_Request.mPending) {
        *pA = _PauseRequest_Request.mUnknown0;
        result = 1;
        *pB = _PauseRequest_Request.mUnknown2;
        *pC = _PauseRequest_Request.mUnknown4;
        PauseRequestReset();
    }
    return result;
}

int PauseRequestIsAllowed(int a)
{
    int result = 0;

    if ((fn_800B65A0(ScrmGetOffenseTeam()) == 0xFF && fn_800B65A0(ScrmGetDefenseTeam()) == 0xFF) || fn_800B6644(a) != 0xFF || a == 8) {
        if (MiniGameGetCurrent()) {
            result = MiniGameGetCurrent()->vfn_22(a);
        } else {
            result = 1;
        }
    }
    return result;
}

void PauseRequestCancel(void)
{
    PauseRequestReset();
}

void PauseRequestInit(void)
{
    PauseRequestReset();
    PauseSetRequestCallback(0, PauseRequestPoll);
}

int PauseRequestIsPending(void)
{
    return _PauseRequest_Request.mPending == 1;
}

void PauseRequestHandleInput(int a, int b, float c)
{
    int mode = fn_800AD9B4();
    int value;

    if (_PauseRequest_Request.mPending != 0) {
        return;
    }
    if (b != 0 && b != 0x46) {
        return;
    }
    if (!PauseRequestIsAllowed(a) || ReplayIsShowing(gpReplay) || CelebrationBlockIsActive(0)) {
        return;
    }
    if (mode == 2 && GamebreakerIsCutscenePlaying()) {
        return;
    }
    if (c != 1.0f) {
        return;
    }
    switch (mode) {
    case 1:
    case 7:
        return;
    case 6:
        if (fn_8009D86C() == 6) {
            return;
        }
        break;
    }
    if (ScrmGetWinner() == 2 || fn_800BA6F8() || (ScrmGetScoreGoal(&value) == 1 && mode == 3)) {
        _PauseRequest_Request.mUnknown0 = 3;
        _PauseRequest_Request.mUnknown2 = 1;
        _PauseRequest_Request.mUnknown4 = a;
        _PauseRequest_Request.mPending = 1;
    }
}
}
