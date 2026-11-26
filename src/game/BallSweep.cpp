/* Sweeps the ball along its last step against a part of a player's body to find where they
   first touch. */

#include "game/Ball.h"
#include "game/BallSweep.h"
#include "game/Vec3Magnitude.h"

#include <string.h>

extern "C" {
float CollideSegmentClosestPoints(Vector_80039F5C *pA0, Vector_80039F5C *pA1, Vector_80039F5C *pB0, Vector_80039F5C *pB1, Vector_80039F5C *pOut);
void Vec3Scale(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void Vec3ScaleAcc(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void Vec3Add(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);

static int _BallSweep_iSteps = 4;
static unsigned char _BallSweep_bLinear = 0;

int BallSegmentsTouch(BallSegment_t *pA, BallSegment_t *pB, float limit)
{
    Vector_80039F5C point;

    return CollideSegmentClosestPoints(&pA->mUnknown0, &pA->mUnknown10, &pB->mUnknown0, &pB->mUnknown10, &point) < limit;
}

int BallSweepLinear(Vector_80039F5C *pOut, BallSegment_t *pA, BallSegment_t *pB, Vector_80039F5C *pStep, float limit)
{
    int result = 0;
    int i;

    Vec3Scale(pStep, pStep, 1.0f / _BallSweep_iSteps);
    for (i = 0; i < _BallSweep_iSteps; i++) {
        Vec3Add(&pA->mUnknown0, &pA->mUnknown0, pStep);
        Vec3Add(&pA->mUnknown10, &pA->mUnknown10, pStep);
        if (BallSegmentsTouch(pA, pB, limit)) {
            if (i == 0) {
                result = 1;
            }
            break;
        }
    }
    Vec3ScaleAcc(pOut, pStep, i - 1);
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
        Vec3Scale(pStep, pStep, 0.5f);
        if (hit == 0) {
            Vec3Add(&pos, &pos, pStep);
            Vec3Add(&pA->mUnknown0, &pA->mUnknown0, pStep);
            Vec3Add(&pA->mUnknown10, &pA->mUnknown10, pStep);
        } else {
            Vec3Sub(&pos, &pos, pStep);
            Vec3Sub(&pA->mUnknown0, &pA->mUnknown0, pStep);
            Vec3Sub(&pA->mUnknown10, &pA->mUnknown10, pStep);
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
    Vec3Sub(&step, &pBall->mState.mPos, &pBall->mState.mUnknown28);
    sum = seg.mUnknownC + pSeg->mUnknownC;
    limit = sum * sum;
    pPos->mX = pBall->mState.mUnknown28.mX;
    pPos->mY = pBall->mState.mUnknown28.mY;
    pPos->mZ = pBall->mState.mUnknown28.mZ;
    Vec3Sub(&seg.mUnknown0, &seg.mUnknown0, &step);
    Vec3Sub(&seg.mUnknown10, &seg.mUnknown10, &step);
    if (_BallSweep_bLinear) {
        *pHit = BallSweepLinear(pPos, &seg, pSeg, &step, limit);
    } else {
        *pHit = BallSweepBisect(pPos, &seg, pSeg, &step, limit);
    }
    Vec3Sub(&delta, pPos, &pBall->mState.mUnknown28);
    return Vec3Magnitude(&delta);
}

}
