#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/cu_8008E978.h"
#include <math.h>

/* Per-condition counters passed to the condition callbacks. */
struct Pair_800A554C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
int fn_8009F058(Object_80039F5C *p, Object_80039F5C *pOther, int angle);
float fn_80237260(int stream);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
float fn_802270A4(void *pV);
int fn_801CFFD0(int a, int b);
float fn_8016B9EC(void);
int fn_800A7ECC(int team);
int fn_800A54F4(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther, Pair_800A554C *pPair);
}

extern "C" int fn_800A5104(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    int result = 0;

    if (fn_8009F058(p, pTarget, 0x400000) != 0 && fn_8009F058(p, pOther, 0x400000) != 0) {
        result = fn_80237260(0) < 0.33f;
    }
    return result;
}

extern "C" int fn_800A517C(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    Point_8017886C delta;
    int angle;
    float distance;
    float chance;
    int result = 0;

    if (pPair->mUnknown0 <= 2) {
        if (fn_8009F058(p, pTarget, 0x400000) != 0) {
            switch (p->mUnknown2914) {
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                switch (p->mpState->mId) {
                case 22:
                    if (p->mUnknown336 == pOther->mId) {
                        result = 1;
                    }
                    break;
                case 40:
                case 92:
                    if (fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX) < 15.0f) {
                        result = 1;
                    }
                    break;
                case 2:
                case 30:
                    fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
                    angle = fn_801CFE40(delta.mY, delta.mX);
                    distance = fn_802270A4(&delta);
                    if (fn_801CFFD0(p->mMotion.mFacing, angle) <= 0x1FFFFF) {
                        fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
                        angle = fn_801CFE40(delta.mY, delta.mX);
                        if (distance < 6.0f) {
                            result = 1;
                        }
                    }
                    break;
                }
                break;
            case 10:
            case 11:
            case 12:
                if (p->mpState->mId == 2 || p->mpState->mId == 30) {
                    fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
                    angle = fn_801CFE40(delta.mY, delta.mX);
                    distance = fn_802270A4(&delta);
                    if (fn_801CFFD0(p->mMotion.mFacing, angle) <= 0x1FFFFF) {
                        fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
                        angle = fn_801CFE40(delta.mY, delta.mX);
                        if (distance < 6.0f) {
                            result = 1;
                        }
                    }
                }
                break;
            }
        }
        chance = pPair->mUnknown0 * 0.33333334f;
        chance += fn_8016B9EC();
        if (fn_80237260(0) < chance) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800A535C(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    int result = 0;

    if (fn_800A7ECC(p->mIdBytes[2]) == 0) {
        result = fn_800A54F4(p, pTarget, pOther, pPair);
    } else if (fn_8009F058(p, pTarget, 0x400000) != 0 && fn_8009F058(pTarget, p, 0x400000) != 0
               && fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos) < 7.0f) {
        int limit = 256 / (pPair->mUnknown0 + 1);

        if (fn_802372EC(0, 256) < limit) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800A543C(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    int result = 0;

    if (fn_800A7ECC(p->mIdBytes[2]) == 0) {
        result = fn_800A54F4(p, pTarget, pOther, pPair);
    } else if (p->mpState->mId == 22 && p->mUnknown336 == pTarget->mId) {
        unsigned char chance = Interpolate(p->mRatings[8], 10, 90, 10);

        if (fn_802372EC(0, 100) < chance) {
            result = 1;
        }
    }
    return result;
}
