#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFFD0(int a, int b);
}

extern "C" int fn_800B2C48(Object_800B26B0 *pA, Object_800B26B0 *pB, int arc, unsigned char *pHitA,
                           unsigned char *pHitB)
{
    int half = arc / 2;
    Point_8017886C delta;
    Point_8017886C deltaB;

    fn_80227690(&delta, &pA->mUnknown12, &pB->mUnknown12);
    int angle = delta.Heading();

    fn_80227690(&delta, &pA->mPos, &pA->mUnknown12);
    *pHitA = 0;
    if (delta.mX != 0.0f || delta.mY != 0.0f) {
        if (fn_801CFFD0(delta.Heading(), (angle + 0x800000) & 0xFFFFFF) < half) {
            *pHitA = 1;
        }
    }

    fn_80227690(&deltaB, &pB->mPos, &pB->mUnknown12);
    *pHitB = 0;
    if (deltaB.mX != 0.0f || deltaB.mY != 0.0f) {
        if (fn_801CFFD0(deltaB.Heading(), angle) < half) {
            *pHitB = 1;
        }
    }
    return *pHitA || *pHitB;
}
