#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_8009E9A4(void);
void fn_800F6D40(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pOut);
extern float lbl_803ECB08;
extern float lbl_803EAE30;
extern float lbl_803EAE34;
extern float lbl_803EAE38;
extern float lbl_803EAE3C;
}

extern "C" int fn_800F6878(Object_80039F5C *p, Object_80039F5C *pOther) {
    int result = 0;

    if (p && pOther) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) < 0xAAAAA
            && (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) < 0x400000 || fn_802270A4(&delta) < 2.0f)) {
            result = 1;
        }
        if (result && fn_801CFFD0(p->mMotion.mFacing, 0x400000) < 0x155555) {
            result = 0;
        }
        if (result && !(p->mMotion.mPos.mY < fn_80178A44() - 5.0f)) {
            result = 0;
        }
        if (result && (pOther->mpState->mId == 51 || pOther->mpState->mId == 52)) {
            result = 0;
        }
        if (result && !(pOther->mMotion.mUnknown28 >= lbl_803ECB08 * 0.72f)) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800F69C0(int angle, Object_80039F5C *p) {
    int found = 0;
    int result = angle;
    unsigned char team;
    unsigned char i;
    int direction;

    for (team = 0; team <= 1; team++) {
        unsigned int n = fn_80178D18(team);

        for (i = 0; i < n; i++) {
            Object_80039F5C *pOther = fn_80039F5C(team, i);

            if (fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos) <= lbl_803EAE34) {
                Point_8017886C delta;

                fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
                direction = fn_801CFE40(delta.mY, delta.mX);
                if (fn_801CFFD0(direction, result) < (int)(lbl_803EAE30 * 46603.38f)) {
                    found = 1;
                    result += (int)(lbl_803EAE38 * 46603.38f);
                }
            }
        }
    }
    return found ? result : angle;
}

extern "C" void fn_800F6AD8(float *p) {
    if (p) {
        if (fabsf(p[0]) < 0.3f) {
            p[0] = 0.0f;
        }
        if (fabsf(p[1]) < 0.3f) {
            p[1] = 0.0f;
        }
    }
}

extern "C" void fn_800F6B2C(Object_80039F5C *p, Point_8017886C *pDelta) {
    if (p && pDelta) {
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Point_8017886C origin;
        Point_8017886C target;
        float limit;

        origin = fn_80177FE0();
        fn_80227638(&target, pPos, pDelta);
        if (fabsf(target.mX) < 4.0f) {
            limit = origin.mY + lbl_803EAE3C;
        } else {
            limit = origin.mY - 1.0f;
        }
        target.mY = target.mY < limit ? limit : target.mY;
        target.mY = target.mY > fn_80178A44() - 5.0f ? fn_80178A44() - 5.0f : target.mY;
        target.mX = target.mX < 2.5f - fn_80178A08() ? 2.5f - fn_80178A08()
                  : (target.mX > fn_80178A08() - 2.5f ? fn_80178A08() - 2.5f : target.mX);
        fn_80227690(pDelta, &target, pPos);
    }
}

extern "C" void fn_800F6C90(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C origin;

        origin = fn_80177FE0();
        if (pTarget->mY < origin.mY + 7.0f) {
            pOut->mY = 0.0f;
        } else {
            fn_800F6D40(p, pOther, pTarget, pOut);
        }
        fn_800F6AD8(&pOut->mX);
    }
}

extern "C" void fn_800F6D40(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C delta;

        fn_80227690(&delta, pTarget, &p->mMotion.mPos);
        if (!(p->mpState->mUnknown2 & 2)) {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY;
            if (fn_8009E9A4() == 1 && pOther->mUnknown2914 == 3) {
                pOut->mY = pOut->mY + 5.0f;
            }
        } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY;
        } else {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY;
        }
        if (fn_800F6878(p, pOther)) {
            pOut->mY = pOut->mY + 2.5f;
        } else {
            fn_800F6AD8(&pOut->mX);
        }
    }
}
