#include "game/Object_80039F5C.h"
#include <math.h>

extern "C" float lbl_803EAFC0;
extern "C" float lbl_803EAFC4;
extern "C" float lbl_803EAFC8;

extern "C" int fn_80116984(Object_80039F5C *p, Object_80039F5C *pOther, float *pOut)
{
    int result = 0;

    if (p != 0 && pOther != 0 && pOut != 0) {
        *pOut = 0.0f;
        if (pOther->mRatings[4] > p->mRatings[4]) {
            unsigned int diff = (unsigned int)(pOther->mRatings[4] * 0.38823533f - p->mRatings[4] * 0.38823533f);
            float value = diff;

            *pOut = value * lbl_803EAFC0;
            if (value > lbl_803EAFC4 && fabsf(pOther->mMotion.mPos.mY - p->mMotion.mPos.mY) < lbl_803EAFC8) {
                result = 1;
            }
        }
    }
    return result;
}

