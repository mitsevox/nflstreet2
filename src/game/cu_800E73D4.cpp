#include "game/Object_80039F5C.h"
#include "game/Object_800EA284.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include <math.h>

extern "C" {
extern float lbl_803EAD70;
extern float lbl_803EAD74;
int fn_801CFE08(float value);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
int fn_8011F1CC(void);
void fn_80227690(void *pOut, void *pA, void *pB);
Point_8017886C fn_80177FE0(void);
}

extern "C" int fn_800E73D4(Object_80039F5C *p)
{
    int result = 0;
    Record_800EA284 *pRecord = p->mpUnknown3092->mpUnknown32;
    float distance = fn_8022781C(&pRecord->mUnknown32, &pRecord->mUnknown16);
    if (distance > 0.0f) {
        result = fn_801CFE08(fabsf(pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ) / distance) <= 0x155555;
    }
    return result;
}

extern "C" int fn_800E745C(Object_80039F5C *p)
{
    int result = 1;
    Object_80039F5C *pCarrier = fn_80137B40();
    if (pCarrier) {
        Point_8017886C delta;
        fn_80227690(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
        float distance = fn_802270A4(&delta);
        int difference = fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing);
        if (fn_8011F1CC() && pCarrier->mMotion.mPos.mY < fn_80177FE0().mY) {
            int id = fn_800F06F4(0, pCarrier->mpState, 18, 0xFFFF);
            if (id != 0xFFFF || fn_800F06F4(0, pCarrier->mpState, 15, 0xFFFF) != id) {
                if (difference > (int)(lbl_803EAD70 * 46603.3789f) || distance > lbl_803EAD74) {
                    result = 0;
                }
            }
        }
    } else {
        result = 0;
    }
    return result;
}
