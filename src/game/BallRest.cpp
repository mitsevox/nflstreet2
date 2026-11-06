/* Finds the lowest point of the ball's shape so the ball can rest on the ground. */

#include "game/Ball.h"

extern "C" {
void fn_801D0470(int a);
void fn_801D0494(void);
void fn_801D0860(Quat_801EB488 *pRot);
void fn_801D0C58(void *a);
void fn_80227CC0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void BallFindLowestPoint(Ball_t *pBall, Vector_80039F5C *pOut, int *pIndex);
}

Vector_80039F5C _BallRest_vShapePoints[6] = {
    {0.0f, 0.0f, 0.16666667f},
    {-0.097261354f, 0.0f, 0.0f},
    {0.0f, 0.097261354f, 0.0f},
    {0.097261354f, 0.0f, 0.0f},
    {0.0f, -0.097261354f, 0.0f},
    {0.0f, 0.0f, -0.16666667f},
};

extern "C" void BallTransformShapePoint(Vector_80039F5C *pPos, Quat_801EB488 *pRot, int index, Vector_80039F5C *pOut)
{
    fn_801D0470(3);
    fn_801D0494();
    fn_801D0C58(pPos);
    fn_801D0860(pRot);
    fn_80227CC0(pOut, &_BallRest_vShapePoints[index]);
}

extern "C" void BallUpdateGroundPoint(Ball_t *pBall)
{
    Vector_80039F5C pos;
    int index;

    pos.mX = pBall->mState.mPos.mX;
    pos.mY = pBall->mState.mPos.mY;
    pos.mZ = pBall->mState.mPos.mZ - 0.16666667f;
    index = 0;
    if (pos.mZ <= 0.0f) {
        BallFindLowestPoint(pBall, &pos, &index);
    }
    pBall->mState.mUnknown94.mX = pos.mX;
    pBall->mState.mUnknown94.mY = pos.mY;
    pBall->mState.mUnknown94.mZ = pos.mZ;
    pBall->mState.mUnknownA0 = index;
}

extern "C" void BallFindLowestPoint(Ball_t *pBall, Vector_80039F5C *pOut, int *pIndex)
{
    Vector_80039F5C point;
    int i;

    fn_801D0470(3);
    fn_801D0494();
    fn_801D0C58(&pBall->mState.mPos);
    fn_801D0860(&pBall->mState.mUnknown18);
    pOut->mZ = pBall->mState.mPos.mZ;
    *pIndex = 0;
    for (i = 0; i <= 5; i++) {
        fn_80227CC0(&point, &_BallRest_vShapePoints[i]);
        if (point.mZ < pOut->mZ) {
            pOut->mX = point.mX;
            pOut->mY = point.mY;
            pOut->mZ = point.mZ;
            *pIndex = i;
        }
    }
}
