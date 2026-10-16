#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_802270D4.h"

extern "C" {
int fn_800E7C84(Object_80039F5C *p);
int fn_800E815C(Object_80039F5C *p, void *pArg, int flag);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" int fn_800E8098(Object_80039F5C *p, void *pArg)
{
    int result = 0;
    if (fn_800E7C84(p) == 1) {
        Object_80039F5C *pCarrier = fn_80137B40();
        if (pCarrier && pCarrier->mpState->mId == 1) {
            Point_8017886C delta;
            fn_80227690(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
            if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) <= 0x3FFFFF &&
                fn_802270A4(&delta) < 10.0f) {
                result = fn_800E815C(p, pArg, 0);
            }
        }
    }
    return result;
}
