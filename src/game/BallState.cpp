/* The ball's state machine: one handler table per ball state and the calls that switch and
   run states. */

#include "game/Ball.h"

/* Per-state handlers, indexed by BallState_t::mState. */
struct BallStateFuncs_t {
    void (*mUnknown0)(Ball_t *p, float dt);
    void (*mUnknown4)(Ball_t *p, float dt);
    void (*mUnknown8)(Ball_t *p, float dt);
    void (*mEnter)(Ball_t *p);
    void (*mExit)(Ball_t *p);
    int (*mUnknown14)(Ball_t *p, void *pData, unsigned int type);
    void (*mUnknown18)(Ball_t *p, float dt);
};

extern "C" {
void fn_8013A3BC(Ball_t *p);
void BallApplyContactForce(Ball_t *p, float dt);
void fn_8013A64C(Ball_t *p, float dt);
void BallStepMotion(Ball_t *p, float dt);
void fn_8013AF88(Ball_t *p);
void fn_8013AFE8(Ball_t *p);
void fn_8013B024(Ball_t *p);
void fn_8013B068(Ball_t *p);
void BallStateStepTimed(Ball_t *p, float dt);
void BallStateStopVelocity(Ball_t *p, float dt);
void fn_8013B1E4(Ball_t *p, float dt);
void fn_8013B230(Ball_t *p);
void fn_8013B250(Ball_t *p);
void fn_8013B2A0(Ball_t *p, float dt);
void fn_8013B330(Ball_t *p, float dt);
void fn_8013B350(Ball_t *p, float dt);
int fn_8013B3EC(Ball_t *p, void *pData, unsigned int type);
int fn_8013B52C(Ball_t *p, void *pData, unsigned int type);
int fn_8013B5EC(Ball_t *p, void *pData, unsigned int type);
int fn_8013B6A0(Ball_t *p, void *pData, unsigned int type);
void fn_8013B730(Ball_t *p, float dt);
void BallStatePlacedUpdate(Ball_t *p, float dt);
int fn_8013B86C(Ball_t *p, void *pData, unsigned int type);
int BallStateIsCurrent(Ball_t *p, void *pData, unsigned int type);
}

static BallStateFuncs_t _BallState_Handlers[9] = {
    { 0, BallApplyContactForce, 0, 0, 0, BallStateIsCurrent, BallStepMotion },
    { 0, 0, BallStateStepTimed, fn_8013AF88, fn_8013B250, fn_8013B3EC, BallStepMotion },
    { 0, fn_8013B350, 0, 0, 0, fn_8013B6A0, BallStepMotion },
    { 0, fn_8013B350, 0, 0, 0, fn_8013B6A0, BallStepMotion },
    { 0, fn_8013B2A0, fn_8013B1E4, fn_8013AFE8, fn_8013B024, fn_8013B5EC, BallStepMotion },
    { 0, fn_8013B330, 0, fn_8013B068, 0, fn_8013B52C, BallStepMotion },
    { 0, BallApplyContactForce, BallStateStopVelocity, fn_8013B230, 0, fn_8013B3EC, 0 },
    { 0, BallApplyContactForce, 0, 0, 0, fn_8013B6A0, BallStepMotion },
    { 0, 0, fn_8013B730, 0, 0, fn_8013B86C, BallStatePlacedUpdate },
};

extern "C" {

void BallStateUpdate(Ball_t *p, float dt)
{
    if (_BallState_Handlers[p->mState.mState].mUnknown18) {
        _BallState_Handlers[p->mState.mState].mUnknown18(p, dt);
    }
}

void BallStatePreUpdate(Ball_t *p, float dt)
{
    if (_BallState_Handlers[p->mState.mState].mUnknown0) {
        _BallState_Handlers[p->mState.mState].mUnknown0(p, dt);
    }
}

void BallStateHitGround(Ball_t *p, float dt)
{
    if (_BallState_Handlers[p->mState.mState].mUnknown4) {
        _BallState_Handlers[p->mState.mState].mUnknown4(p, dt);
        fn_8013A3BC(p);
    }
    p->mState.mFlags |= 0x10;
}

void BallStateMove(Ball_t *p, float dt)
{
    if (_BallState_Handlers[p->mState.mState].mUnknown8) {
        _BallState_Handlers[p->mState.mState].mUnknown8(p, dt);
    } else {
        fn_8013A64C(p, dt);
    }
}

void BallStateChange(Ball_t *p, int state, int arg)
{
    int prevState = p->mState.mState;
    int prevArg = p->mState.mStateArg;

    p->mState.mState = state;
    p->mState.mPrevStateArg = prevArg;
    p->mState.mStateArg = arg;
    p->mState.mPrevState = prevState;
    if (_BallState_Handlers[prevState].mExit) {
        _BallState_Handlers[prevState].mExit(p);
    }
    if (_BallState_Handlers[p->mState.mState].mEnter) {
        _BallState_Handlers[p->mState.mState].mEnter(p);
    }
}

int BallStateGet(Ball_t *p, int *pArg)
{
    if (pArg) {
        *pArg = p->mState.mStateArg;
    }
    return p->mState.mState;
}

int BallStateGetPrev(Ball_t *p, int *pArg)
{
    if (pArg) {
        *pArg = p->mState.mPrevStateArg;
    }
    return p->mState.mPrevState;
}

int BallStateCheckPlayerHit(Ball_t *p, void *pData, int value)
{
    int result = 0;

    if (_BallState_Handlers[p->mState.mState].mUnknown14) {
        result = _BallState_Handlers[p->mState.mState].mUnknown14(p, pData, value);
    }
    return result;
}

int BallStateIsCurrent(Ball_t *p, void *pData, unsigned int type)
{
    return p == BallGetCurrent();
}
}
