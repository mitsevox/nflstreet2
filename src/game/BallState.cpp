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
void BallRecordBounce(Ball_t *p);
void BallApplyContactForce(Ball_t *p, float dt);
void BallStepDefault(Ball_t *p, float dt);
void BallStepMotion(Ball_t *p, float dt);
void BallStateHeldEnter(Ball_t *p);
void BallStatePassEnter(Ball_t *p);
void BallStatePassExit(Ball_t *p);
void BallStateLooseExit(Ball_t *p);
void BallStateStepTimed(Ball_t *p, float dt);
void BallStateStopVelocity(Ball_t *p, float dt);
void BallStatePassMove(Ball_t *p, float dt);
void BallStateDeadEnter(Ball_t *p);
void BallStateHeldExit(Ball_t *p);
void BallStatePassHitGround(Ball_t *p, float dt);
void BallStateLooseHitGround(Ball_t *p, float dt);
void BallStatePitchHitGround(Ball_t *p, float dt);
int BallStateHandoffTouch(Ball_t *p, void *pData, unsigned int type);
int BallStateLooseTouch(Ball_t *p, void *pData, unsigned int type);
int BallStatePassTouch(Ball_t *p, void *pData, unsigned int type);
int BallStatePitchTouch(Ball_t *p, void *pData, unsigned int type);
void BallStatePlacedMove(Ball_t *p, float dt);
void BallStatePlacedUpdate(Ball_t *p, float dt);
int BallStatePlacedTouch(Ball_t *p, void *pData, unsigned int type);
int BallStateIsCurrent(Ball_t *p, void *pData, unsigned int type);
}

static BallStateFuncs_t _BallState_Handlers[9] = {
    { 0, BallApplyContactForce, 0, 0, 0, BallStateIsCurrent, BallStepMotion },
    { 0, 0, BallStateStepTimed, BallStateHeldEnter, BallStateHeldExit, BallStateHandoffTouch, BallStepMotion },
    { 0, BallStatePitchHitGround, 0, 0, 0, BallStatePitchTouch, BallStepMotion },
    { 0, BallStatePitchHitGround, 0, 0, 0, BallStatePitchTouch, BallStepMotion },
    { 0, BallStatePassHitGround, BallStatePassMove, BallStatePassEnter, BallStatePassExit, BallStatePassTouch, BallStepMotion },
    { 0, BallStateLooseHitGround, 0, BallStateLooseExit, 0, BallStateLooseTouch, BallStepMotion },
    { 0, BallApplyContactForce, BallStateStopVelocity, BallStateDeadEnter, 0, BallStateHandoffTouch, 0 },
    { 0, BallApplyContactForce, 0, 0, 0, BallStatePitchTouch, BallStepMotion },
    { 0, 0, BallStatePlacedMove, 0, 0, BallStatePlacedTouch, BallStatePlacedUpdate },
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
        BallRecordBounce(p);
    }
    p->mState.mFlags |= 0x10;
}

void BallStateMove(Ball_t *p, float dt)
{
    if (_BallState_Handlers[p->mState.mState].mUnknown8) {
        _BallState_Handlers[p->mState.mState].mUnknown8(p, dt);
    } else {
        BallStepDefault(p, dt);
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
