#include "game/Object_80039F5C.h"

extern "C" int fn_800A5A04(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int result = 1;

    if (*pState == -1) {
        if (pTarget->mpState->mId != 20) {
            result = 0;
        } else {
            *pState = pTarget->mMotion.mUnknown32;
        }
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = *pState;
    p->mUnknown512.mUnknown4 = *pState;
    p->mUnknown512.mUnknown0 = 1.0f;
    return result;
}
