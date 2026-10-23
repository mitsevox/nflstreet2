#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_8022781C.h"

extern "C" {

int fn_801787A0(void);
unsigned short fn_801BE648(void *p);
void *fn_80137C48(Object_80039F5C *p);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFFD0(int a, int b);
int fn_800C8BAC(Object_80039F5C *p, int a);
float fn_801CFB94(int angle);
int fn_8011DBE0(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8011F228(void);
int fn_801783AC(int bit);

int fn_8011E484(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    Object_800B26B0 *pMotion;

    if (fn_801787A0()) {
        return 0;
    }
    pMotion = &p->mMotion;
    switch (fn_801BE648(pOther->mpUnknown792)) {
    case 0x30:
    case 0xD0:
    case 0xD1:
        return 0;
    }
    if (pOther) {
        switch (pOther->mpState->mId) {
        case 10:
        case 11:
        case 12:
        case 17:
        case 32:
        case 50:
        case 58:
        case 94:
            break;
        default:
            switch (p->mpState->mId) {
            case 25:
            case 26:
                break;
            default:
                if (!(pOther->mFlags & 0x800) && !fn_80137C48(p)) {
                    Point_8017886C delta;
                    int angle;
                    int both;
                    int limit;

                    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
                    angle = fn_801CFE40(delta.mY, delta.mX);
                    if ((p->mFlags & 0x4000) && fn_801CFFD0(p->mUnknown512.mUnknown4, angle) > 0x600000) {
                        return 0;
                    }
                    both = 0;
                    if (pOther->mUnknown1032 == 4 && (p->mUnknown1032 == 4 || p->mUnknown1032 == 7)) {
                        both = 1;
                    }
                    limit = 0x1C71C7;
                    if (both) {
                        limit = 0x2E38E3;
                    }
                    if (fn_801CFFD0(pMotion->mFacing + fn_800C8BAC(p, 0), angle) < limit) {
                        angle = (angle + 0x800000) & 0xFFFFFF;
                        if ((!pOther->mUnknown512.mUnknown14 || fn_801CFFD0(pOther->mUnknown512.mUnknown4, angle) <= 0x5C71C6)
                            && fn_8022781C(&pMotion->mPos, &pOther->mMotion.mPos) < 2.1f) {
                            int difference = fn_801CFFD0(pMotion->mFacing + fn_800C8BAC(p, 0),
                                                         pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0));
                            Vector_80039F5C joint;
                            Vector_80039F5C otherJoint;
                            Vector_80039F5C angles;
                            float reach;

                            if (!both) {
                                fn_8009BF5C(p, 11, &joint, &angles);
                                fn_8009BF5C(pOther, 11, &otherJoint, &angles);
                                if (difference > 0x400000) {
                                    reach = fabsf(fn_801CFB94(difference) * 0.39999998f) + 0.85f;
                                } else {
                                    reach = 0.85f;
                                }
                                if (fn_8011DBE0(p, pOther)) {
                                    reach *= 1.2f;
                                } else if (fn_8011F228() && !fn_801783AC(0)) {
                                    reach = 1.25f;
                                }
                            }
                            if (both || fn_8022781C(&joint, &otherJoint) < reach) {
                                if (fn_8011DBE0(p, pOther) || difference > 0x3C71C7) {
                                    result = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

}
