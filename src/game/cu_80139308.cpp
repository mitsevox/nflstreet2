#include "game/cu_80136B1C.h"

extern "C" {
void fn_801D0470(int a);
void fn_801D0494(void);
void fn_801D0860(Quat_801EB488 *pRot);
void fn_801D0C58(void *a);
void fn_80227CC0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_80139400(Object_80137ABC *pBall, Vector_80039F5C *pOut, int *pIndex);
}

Vector_80039F5C lbl_802DBBE0[6] = {
    {0.0f, 0.0f, 0.16666667f},
    {-0.097261354f, 0.0f, 0.0f},
    {0.0f, 0.097261354f, 0.0f},
    {0.097261354f, 0.0f, 0.0f},
    {0.0f, -0.097261354f, 0.0f},
    {0.0f, 0.0f, -0.16666667f},
};

extern "C" void fn_80139308(Vector_80039F5C *pPos, Quat_801EB488 *pRot, int index, Vector_80039F5C *pOut)
{
    fn_801D0470(3);
    fn_801D0494();
    fn_801D0C58(pPos);
    fn_801D0860(pRot);
    fn_80227CC0(pOut, &lbl_802DBBE0[index]);
}

extern "C" void fn_80139370(Object_80137ABC *pBall)
{
    Vector_80039F5C pos;
    int index;

    pos.mX = pBall->mState.mPos.mX;
    pos.mY = pBall->mState.mPos.mY;
    pos.mZ = pBall->mState.mPos.mZ - 0.16666667f;
    index = 0;
    if (pos.mZ <= 0.0f) {
        fn_80139400(pBall, &pos, &index);
    }
    pBall->mState.mUnknown94.mX = pos.mX;
    pBall->mState.mUnknown94.mY = pos.mY;
    pBall->mState.mUnknown94.mZ = pos.mZ;
    pBall->mState.mUnknownA0 = index;
}

extern "C" void fn_80139400(Object_80137ABC *pBall, Vector_80039F5C *pOut, int *pIndex)
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
        fn_80227CC0(&point, &lbl_802DBBE0[i]);
        if (point.mZ < pOut->mZ) {
            pOut->mX = point.mX;
            pOut->mY = point.mY;
            pOut->mZ = point.mZ;
            *pIndex = i;
        }
    }
}
