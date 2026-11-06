/* Sweeps the ball along its last step against a part of a player's body to find where they
   first touch. */

#include "game/Ball.h"
#include "game/BallSweep.h"
#include "game/fn_802270D4.h"

#include <string.h>

extern "C" {
float fn_80088FFC(Vector_80039F5C *pA0, Vector_80039F5C *pA1, Vector_80039F5C *pB0, Vector_80039F5C *pB1, Vector_80039F5C *pOut);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);

static int _BallSweep_iSteps = 4;
static unsigned char _BallSweep_bLinear = 0;

int BallSegmentsTouch(BallSegment_t *pA, BallSegment_t *pB, float limit)
{
    Vector_80039F5C point;

    return fn_80088FFC(&pA->mUnknown0, &pA->mUnknown10, &pB->mUnknown0, &pB->mUnknown10, &point) < limit;
}

int BallSweepLinear(Vector_80039F5C *pOut, BallSegment_t *pA, BallSegment_t *pB, Vector_80039F5C *pStep, float limit)
{
    int result = 0;
    int i;

    fn_80227264(pStep, pStep, 1.0f / _BallSweep_iSteps);
    for (i = 0; i < _BallSweep_iSteps; i++) {
        fn_8022765C(&pA->mUnknown0, &pA->mUnknown0, pStep);
        fn_8022765C(&pA->mUnknown10, &pA->mUnknown10, pStep);
        if (BallSegmentsTouch(pA, pB, limit)) {
            if (i == 0) {
                result = 1;
            }
            break;
        }
    }
    fn_80227350(pOut, pStep, i - 1);
    return result;
}

int BallSweepBisect(Vector_80039F5C *pPos, BallSegment_t *pA, BallSegment_t *pB, Vector_80039F5C *pStep, float limit)
{
    Vector_80039F5C pos;
    int first;
    int hit;
    int i;

    pos.mX = pPos->mX;
    pos.mY = pPos->mY;
    pos.mZ = pPos->mZ;
    first = BallSegmentsTouch(pA, pB, limit);
    hit = first;
    for (i = 0; i < _BallSweep_iSteps; i++) {
        fn_80227264(pStep, pStep, 0.5f);
        if (hit == 0) {
            fn_8022765C(&pos, &pos, pStep);
            fn_8022765C(&pA->mUnknown0, &pA->mUnknown0, pStep);
            fn_8022765C(&pA->mUnknown10, &pA->mUnknown10, pStep);
        } else {
            fn_802276B4(&pos, &pos, pStep);
            fn_802276B4(&pA->mUnknown0, &pA->mUnknown0, pStep);
            fn_802276B4(&pA->mUnknown10, &pA->mUnknown10, pStep);
        }
        hit = BallSegmentsTouch(pA, pB, limit);
        if (hit == 0) {
            pPos->mX = pos.mX;
            pPos->mY = pos.mY;
            pPos->mZ = pos.mZ;
        }
    }
    return first;
}

float BallSweepToPart(CollideObject_t *pA, CollideObject_t *pB, unsigned char sub, Ball_t *pBall, Vector_80039F5C *pPos, unsigned char *pHit)
{
    BallSegment_t seg;
    BallSegment_t *pSeg;
    Vector_80039F5C step;
    Vector_80039F5C delta;
    float sum;
    float limit;

    memcpy(&seg, &pA->mpUnknown20->mUnknown10, sizeof(seg));
    pSeg = (BallSegment_t *)&pB->mpUnknown20[sub].mUnknown10;
    fn_802276B4(&step, &pBall->mState.mPos, &pBall->mState.mUnknown28);
    sum = seg.mUnknownC + pSeg->mUnknownC;
    limit = sum * sum;
    pPos->mX = pBall->mState.mUnknown28.mX;
    pPos->mY = pBall->mState.mUnknown28.mY;
    pPos->mZ = pBall->mState.mUnknown28.mZ;
    fn_802276B4(&seg.mUnknown0, &seg.mUnknown0, &step);
    fn_802276B4(&seg.mUnknown10, &seg.mUnknown10, &step);
    if (_BallSweep_bLinear) {
        *pHit = BallSweepLinear(pPos, &seg, pSeg, &step, limit);
    } else {
        *pHit = BallSweepBisect(pPos, &seg, pSeg, &step, limit);
    }
    fn_802276B4(&delta, pPos, &pBall->mState.mUnknown28);
    return fn_802270D4(&delta);
}

}
