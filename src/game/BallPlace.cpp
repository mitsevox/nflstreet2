/* Puts balls in place: at a point, on the spot, or parked off the field, and pushes them with
   impulses. */

#include "game/Ball.h"
#include "game/fn_802270D4.h"
#include "game/Object_8017886C.h"

extern "C" {
void BallRestAtAngles(Ball_t *pBall, int *pAngles);
void fn_8013AD9C(Ball_t *pBall, int a);
Point_8017886C fn_80177FE0(void);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_802277DC(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);

void BallPlaceAt(Ball_t *pBall, Vector_80039F5C *pPos)
{
    Vector_80039F5C v;
    int angles[3];

    v.mZ = 0.0f;
    v.mY = 0.0f;
    v.mX = 0.0f;
    angles[0] = 0;
    angles[1] = 0xFFC00000;
    angles[2] = 0xFFC00000;
    BallClearSpin(pBall);
    BallReleaseStill(pBall, 6, 0);
    BallSetPosition(pBall, pPos);
    BallSetVelocity(pBall, &v);
    BallRestAtAngles(pBall, angles);
    fn_8013AD9C(pBall, 0);
}

void BallsPark(void)
{
    Vector_80039F5C pos;
    int count;
    int i;

    count = BallsGetCount();
    pos.mX = -150.0f;
    pos.mY = -150.0f;
    pos.mZ = 0.0f;
    for (i = 0; i < count; i++) {
        Ball_t *pBall = BallGet(i);
        BallPlaceAt(pBall, &pos);
        BallSetVisible(pBall, 0);
        pos.mX += 10.0f;
    }
}

void BallPlaceAtSpot(void)
{
    Vector_80039F5C pos;
    Point_8017886C point;
    Ball_t *pBall = BallGetCurrent();

    point = fn_80177FE0();
    pos.mX = point.mX;
    pos.mY = point.mY;
    pos.mZ = 0.3f;
    BallPlaceAt(pBall, &pos);
}

void BallResetToSpot(void)
{
    BallPlaceAtSpot();
}

void BallApplyImpulse(Ball_t *pBall, Vector_80039F5C *pA, Vector_80039F5C *pB)
{
    Vector_80039F5C offset;
    Vector_80039F5C cross;

    fn_802276B4(&offset, pB, &pBall->mState.mPos);
    fn_802277DC(&cross, &offset, pA);
    fn_8022765C(&pBall->mState.mUnknown7C, &pBall->mState.mUnknown7C, pA);
    fn_8022765C(&pBall->mState.mUnknown88, &pBall->mState.mUnknown88, &cross);
}

}
