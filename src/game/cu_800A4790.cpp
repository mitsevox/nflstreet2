#include "game/Object_80039F5C.h"
#include "game/Team_80167A8C.h"

extern "C" {
void fn_80227538(Point_80167910 *pOut, int angle, float length);
void fn_80227638(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
}

extern "C" int fn_800A4790(Object_80039F5C *p, Object_80039F5C *pTarget)
{
    Point_80167910 offset;
    int angle = (pTarget->mMotion.mFacing + 0x400000) & 0xFFFFFF;

    if (pTarget->mUnknown344 == 3) {
        angle = (angle + 0x800000) & 0xFFFFFF;
    }
    fn_80227538(&offset, angle, 2.5f);
    fn_80227638(&offset, &offset, &pTarget->mMotion.mPos);
    fn_80227690(&offset, &offset, &p->mMotion.mPos);
    return fn_801CFE40(offset.mY, offset.mX);
}
