#include "game/cu_80136B1C.h"
#include "game/fn_802270D4.h"
#include "game/Object_8017886C.h"

extern "C" {
void fn_8013A910(Object_80137ABC *pBall, int *pAngles);
void fn_8013AD9C(Object_80137ABC *pBall, int a);
Point_8017886C fn_80177FE0(void);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_802277DC(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);

void fn_801390D0(Object_80137ABC *pBall, Vector_80039F5C *pPos)
{
    Vector_80039F5C v;
    int angles[3];

    v.mZ = 0.0f;
    v.mY = 0.0f;
    v.mX = 0.0f;
    angles[0] = 0;
    angles[1] = 0xFFC00000;
    angles[2] = 0xFFC00000;
    fn_80137F18(pBall);
    fn_8013791C(pBall, 6, 0);
    fn_80137D74(pBall, pPos);
    fn_80137EE0(pBall, &v);
    fn_8013A910(pBall, angles);
    fn_8013AD9C(pBall, 0);
}

void fn_80139168(void)
{
    Vector_80039F5C pos;
    int count;
    int i;

    count = fn_801383C8();
    pos.mX = -150.0f;
    pos.mY = -150.0f;
    pos.mZ = 0.0f;
    for (i = 0; i < count; i++) {
        Object_80137ABC *pBall = fn_80137ABC(i);
        fn_801390D0(pBall, &pos);
        fn_80138440(pBall, 0);
        pos.mX += 10.0f;
    }
}

void fn_80139204(void)
{
    Vector_80039F5C pos;
    Point_8017886C point;
    Object_80137ABC *pBall = fn_801374BC();

    point = fn_80177FE0();
    pos.mX = point.mX;
    pos.mY = point.mY;
    pos.mZ = 0.3f;
    fn_801390D0(pBall, &pos);
}

void fn_80139274(void)
{
    fn_80139204();
}

void fn_80139294(Object_80137ABC *pBall, Vector_80039F5C *pA, Vector_80039F5C *pB)
{
    Vector_80039F5C offset;
    Vector_80039F5C cross;

    fn_802276B4(&offset, pB, &pBall->mState.mPos);
    fn_802277DC(&cross, &offset, pA);
    fn_8022765C(&pBall->mState.mUnknown7C, &pBall->mState.mUnknown7C, pA);
    fn_8022765C(&pBall->mState.mUnknown88, &pBall->mState.mUnknown88, &cross);
}

}
