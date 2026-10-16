#include "game/fn_801248D4.h"
#include "game/State_800FDA58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_802270D4.h"

/* View of the player object from +1032. */
struct Block_8010FB4C {
    int mUnknown0;
    char mUnknown4[101];
    unsigned char mUnknown105;
};

extern "C" {
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
int fn_801783AC(int bit);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" void fn_8010F058(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Point_8017886C delta;
    int angle;
    float distance;
    float scale;
    int a;
    Object_800B26B0 *pMotion;

    if (((Block_8010FB4C *)&p->mUnknown1032)->mUnknown0 == 4 || ((Block_8010FB4C *)&p->mUnknown1032)->mUnknown0 == 7 ||
        pOther == 0) {
        return;
    }
    pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    if (fn_801CFFD0(angle, pMotion->mFacing) > 0x4E38E2) {
        return;
    }
    scale = 0.0f;
    a = 0;
    if (pMotion->mPos.mY < pOther->mMotion.mPos.mY) {
        if (distance < 3.0f) {
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            scale = 1.0f - distance * 0.33333334f;
        } else if (distance < 10.0f) {
            a = 1;
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            scale = 1.0f - distance * 0.1f;
        }
    } else if (distance < 4.0f) {
        distance -= 1.0f;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        scale = 1.0f - distance * 0.25f;
    }
    if (scale != 0.0f) {
        fn_800C89F0(p, angle, 2, a, scale);
    }
}

extern "C" void fn_8010F1F4(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Point_8017886C delta;
    Object_80039F5C *pTarget;
    Object_80039F5C *pBlocker;
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
    fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801CFFD0(angle, p->mMotion.mFacing) > 0x2AAAA9) {
        return;
    }
    delta.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * 5.0f;
    delta.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * 5.0f;
    fn_80227690(&delta, &delta, &p->mMotion.mPos);
    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) > 0x18E38D) {
        return;
    }
    pBlocker = fn_8009BCE8(&pTarget->mUnknown1036);
    if (pBlocker == 0) {
        return;
    }
    fn_80227690(&delta, &pTarget->mMotion.mPos, &pBlocker->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    delta.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * 5.0f;
    delta.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * 5.0f;
    fn_80227690(&delta, &delta, &pBlocker->mMotion.mPos);
    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) <= 0x18E38E) {
        return;
    }
    switch (pBlocker->mUnknown1032) {
    case 2:
    case 4:
    case 7:
    case 8:
        fn_8011E240(pBlocker);
        fn_8011E1BC(pBlocker, 0, 0, 1);
        fn_8011E3EC(pBlocker, 2);
        fn_8011E240(p);
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
        break;
    }
}
