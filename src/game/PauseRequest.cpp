/* Pause request: when a pad's input asks to pause during play, remembers the
   request so that the pause manager opens the in-game pause screen for that
   pad. */

#include "game/Class_80148A58.h"
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

extern void *lbl_803EA368;

extern "C" {
int fn_8002D060(void *p);
int fn_8009B9A8(int a);
int fn_8009D86C(void);
int fn_800A7FD8(void);
int fn_800B6644(int a);
int fn_800BA6F8(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801788D8(int *pValue);
int fn_80178AE0(void);

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

    if ((fn_800B65A0(fn_80178308()) == 0xFF && fn_800B65A0(fn_80178320()) == 0xFF) || fn_800B6644(a) != 0xFF || a == 8) {
        if (fn_80148A58()) {
            result = fn_80148A58()->vfn_22(a);
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
    if (!PauseRequestIsAllowed(a) || fn_8002D060(lbl_803EA368) || fn_8009B9A8(0)) {
        return;
    }
    if (mode == 2 && fn_800A7FD8()) {
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
    if (fn_80178AE0() == 2 || fn_800BA6F8() || (fn_801788D8(&value) == 1 && mode == 3)) {
        _PauseRequest_Request.mUnknown0 = 3;
        _PauseRequest_Request.mUnknown2 = 1;
        _PauseRequest_Request.mUnknown4 = a;
        _PauseRequest_Request.mPending = 1;
    }
}
}
