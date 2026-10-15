#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80163E94.h"
#include "game/Record_800DB60C.h"

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
int fn_801783AC(int bit);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E3EC(Object_80039F5C *p, int a);
}

extern "C" void fn_8010F058(Object_80039F5C *p, Object_80039F5C *pOther) {
    if (p->mUnknown1032 != 4 && p->mUnknown1032 != 7 && pOther != 0) {
        Object_800B26B0 *pMotion = &p->mMotion;
        Point_8017886C delta;
        int angle;
        float dist;

        fn_80227690(&delta, &pOther->mMotion, pMotion);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        dist = fn_802270A4(&delta);
        if (fn_801CFFD0(angle, pMotion->mFacing) <= 0x4E38E2) {
            int kind = 0;
            float scale = 0.0f;

            if (pMotion->mPos.mY < pOther->mMotion.mPos.mY) {
                if (dist < 3.0f) {
                    dist -= 1.0f;
                    if (dist < 0.0f) {
                        dist = 0.0f;
                    }
                    scale = 1.0f - dist / 3.0f;
                } else if (dist < 10.0f) {
                    kind = 1;
                    dist -= 1.0f;
                    if (dist < 0.0f) {
                        dist = 0.0f;
                    }
                    scale = 1.0f - dist * 0.1f;
                }
            } else if (dist < 4.0f) {
                dist -= 1.0f;
                if (dist < 0.0f) {
                    dist = 0.0f;
                }
                scale = 1.0f - dist * 0.25f;
            }
            if (scale != 0.0f) {
                fn_800C89F0(p, angle, 2, kind, scale);
            }
        }
    }
}

extern "C" void fn_8010F1F4(Object_80039F5C *p, Object_80039F5C *pOther) {
    Object_80039F5C *pTarget;
    Object_80039F5C *pNext;
    Point_8017886C delta;
    int angle;

    if (pOther == 0 || p->mUnknown560.mFlags.mBytes[0] == 0) {
        return;
    }
    pTarget = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    if (pTarget == 0) {
        pTarget = fn_8009BCE8(&p->mUnknown560.mUnknown44);
        if (pTarget == 0) {
            return;
        }
        pTarget = fn_8009BCE8(&pTarget->mUnknown1036);
        if (pTarget == 0) {
            return;
        }
    }
    if (pOther == pTarget || !fn_8011F1A4() || fn_8011F4C8() > 3 || fn_801783AC(0)) {
        return;
    }
    fn_80227690(&delta, &pTarget->mMotion, &p->mMotion);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801CFFD0(angle, p->mMotion.mFacing) >= 0x2AAAAA) {
        return;
    }
    delta.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * 5.0f;
    delta.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * 5.0f;
    fn_80227690(&delta, &delta, &p->mMotion);
    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) >= 0x18E38E) {
        return;
    }
    pNext = fn_8009BCE8(&pTarget->mUnknown1036);
    if (pNext == 0) {
        return;
    }
    fn_80227690(&delta, &pTarget->mMotion, &pNext->mMotion);
    angle = fn_801CFE40(delta.mY, delta.mX);
    delta.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * 5.0f;
    delta.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * 5.0f;
    fn_80227690(&delta, &delta, &pNext->mMotion);
    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) <= 0x18E38E) {
        return;
    }
    switch (pNext->mUnknown1032) {
    case 2:
    case 4:
    case 7:
    case 8:
        fn_8011E240(pNext);
        fn_8011E1BC(pNext, 0, 0, 1);
        fn_8011E3EC(pNext, 2);
        fn_8011E240(p);
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
        break;
    }
}
