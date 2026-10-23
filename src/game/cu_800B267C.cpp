#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Team_80167A8C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "engine/vec.h"

extern "C" {
void fn_80227538(void *pOut, int angle, float length);
void fn_80227248(void *pOut, void *pIn, float scale);
}

extern "C" void fn_800B267C(Object_800B26B0 *pMotion)
{
    pMotion->mPos.mX = 0.0f;
    pMotion->mPos.mY = 0.0f;
    pMotion->mPos.mZ = 0.0f;
    pMotion->mFacing = 0;
    pMotion->mUnknown32 = 0;
    pMotion->mUnknown28 = 0.0f;
    pMotion->mUnknown36 = 0.0f;
    pMotion->mUnknown52 = 0.0f;
    pMotion->mUnknown56 = 0;
}

extern "C" void fn_800B26B0(Object_800B26B0 *pMotion)
{
    pMotion->mUnknown52 = 0.0f;
    pMotion->mUnknown60 = 0.0036f;
    ((MotionTail_800B26B0 *)pMotion)->mUnknown72 = 0.0f;
}

extern "C" void fn_800B26D0(Object_800B26B0 *pMotion, int a, int b, float c)
{
    pMotion->mUnknown56 = a;
    pMotion->mUnknown52 = c;
    pMotion->mFacing = b;
}

static inline float Snap(float value)
{
    return fabsf(value) < 1e-7f ? 0.0f : value;
}

static inline void Snap(Vector_80039F5C *pV)
{
    pV->mX = Snap(pV->mX);
    pV->mY = Snap(pV->mY);
    pV->mZ = Snap(pV->mZ);
}

extern "C" void fn_800B26E0(Object_800B26B0 *pMotion)
{
    MotionTail_800B26B0 *pTail = (MotionTail_800B26B0 *)pMotion;
    Vector_80039F5C *pVel = (Vector_80039F5C *)&pMotion->mUnknown40;
    float maxSpeed = pMotion->mUnknown36;

    pTail->mUnknown68 = pMotion->mUnknown28;
    pMotion->mUnknown12.mX = pMotion->mPos.mX;
    pMotion->mUnknown12.mY = pMotion->mPos.mY;
    pMotion->mUnknown12.mZ = pMotion->mPos.mZ;
    pTail->mUnknown64 = maxSpeed;
    for (int i = 0; i < 1; i++) {
        float speed = pMotion->mUnknown28;

        if (pMotion->mPos.mZ == 0.0f) {
            speed -= pTail->mUnknown72;
            if (speed < 1e-7f) {
                speed = 0.0f;
            }
        }
        if (pMotion->mUnknown52 != 0.0f && maxSpeed != 0.0f) {
            Point_80167910 push;

            fn_80227538(&push, pMotion->mUnknown56, pMotion->mUnknown52);
            float ratio = speed / maxSpeed;
            speed -= ratio * ratio * pMotion->mUnknown52;
            if (speed < 0.0f) {
                speed = 0.0f;
            }
            fn_80227538(pVel, pMotion->mUnknown32, speed);
            fn_80227638(pVel, &push, pVel);
            speed = fn_802270A4(pVel);
            if (speed < 1e-7f) {
                speed = 0.0f;
            } else if (speed > maxSpeed) {
                fn_80227248(pVel, pVel, maxSpeed / speed);
                Snap(pVel);
                speed = maxSpeed;
            }
            pMotion->mUnknown32 = fn_801CFE40(pVel->mY, pVel->mX);
        } else {
            if (speed < pMotion->mUnknown60) {
                pMotion->mUnknown60 = speed;
            }
            speed -= pMotion->mUnknown60;
            if (speed > maxSpeed) {
                speed = maxSpeed;
            }
            fn_80227538(pVel, pMotion->mUnknown32, speed);
            Snap(pVel);
        }
        if (pMotion->mPos.mZ > 0.0f) {
            pVel->mZ -= 0.0029814816f;
        }
        Snap(pVel);
        fn_8022765C(&pMotion->mPos, &pMotion->mPos, pVel);
        pMotion->mUnknown28 = speed;
    }
    pTail->mUnknown80 = 0.0f;
    pTail->mUnknown76 = pMotion->mUnknown32 = pMotion->mUnknown32 & 0xFFFFFF;
}
