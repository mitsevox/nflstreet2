#include "game/Object_80039F5C.h"

extern "C" void fn_800B2B90(Object_800B26B0 *pMotion)
{
    if (pMotion->mPos.mZ <= 0.0f && pMotion->mUnknown48 < 0.0f) {
        pMotion->mUnknown48 = 0.0f;
        pMotion->mPos.mZ = 0.0f;
    }
}
