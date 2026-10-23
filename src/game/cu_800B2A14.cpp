#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Team_80167A8C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

/* The steering input at +544 of the player object: two enable flags, a
   facing change and a movement vector. */
struct Input_800B2A14 {
    unsigned char mTurn;
    unsigned char mMove;
    char mUnknown2[2];
    int mTurnAngle;
    Point_80167910 mMove8;
};

extern "C" {
void fn_80227538(void *pOut, int angle, float length);
void fn_80227690(void *pOut, void *pA, void *pB);

extern float lbl_803ECB08;
}

extern "C" void fn_800B2A14(Object_800B26B0 *pMotion, Input_800B2A14 *pInput)
{
    MotionTail_800B26B0 *pTail = (MotionTail_800B26B0 *)pMotion;

    pTail->mUnknown68 = pMotion->mUnknown28;
    if (pInput->mTurn) {
        pMotion->mFacing = (pMotion->mFacing + pInput->mTurnAngle) & 0xFFFFFF;
    }
    if (pInput->mMove) {
        float speed = fn_802270A4(&pInput->mMove8);
        if (pTail->mUnknown76 != pMotion->mUnknown32) {
            if (pTail->mUnknown80 != 0.0f && speed > 0.05f) {
                speed *= pMotion->mUnknown28 / pTail->mUnknown80;
                if (speed > lbl_803ECB08) {
                    speed = lbl_803ECB08;
                }
            }
            fn_80227538(&pInput->mMove8, pMotion->mUnknown32, speed);
        }
        pMotion->mUnknown40 = pInput->mMove8.mX;
        pMotion->mUnknown44 = pInput->mMove8.mY;
        pMotion->mUnknown52 = pMotion->mUnknown28 = speed;
        pMotion->mUnknown12.mX = pMotion->mPos.mX;
        pMotion->mUnknown12.mY = pMotion->mPos.mY;
        pMotion->mUnknown12.mZ = pMotion->mPos.mZ;
        fn_80227638(&pMotion->mPos, &pMotion->mPos, &pMotion->mUnknown40);

        Point_8017886C delta;
        fn_80227690(&delta, &pMotion->mPos, &pMotion->mUnknown12);
        pMotion->mUnknown56 = pMotion->mUnknown32 = delta.Heading();
    } else {
        pMotion->mUnknown28 = pMotion->mUnknown52 = pMotion->mUnknown40 = pMotion->mUnknown44 = 0.0f;
    }
    pMotion->mUnknown32 &= 0xFFFFFF;
    pTail->mUnknown76 = pMotion->mUnknown32;
    pTail->mUnknown80 = pMotion->mUnknown28;
}
