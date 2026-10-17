#include "game/Object_80039F5C.h"

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
