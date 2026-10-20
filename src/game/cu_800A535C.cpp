#include "game/Object_80039F5C.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

/* Per-condition counters passed to the condition callbacks. */
struct Pair_800A554C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
int fn_8009F058(Object_80039F5C *p, Object_80039F5C *pOther, int angle);
int fn_800A7ECC(int team);
int fn_800A54F4(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther, Pair_800A554C *pPair);
}

/* Maps value in [0, range] linearly onto [from, to]. */
static inline int Interpolate(int value, int range, int from, int to)
{
    return from + value * (to - from) / range;
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
