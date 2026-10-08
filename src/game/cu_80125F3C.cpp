#include "game/cu_80125F3C.h"
#include "game/Object_80039F5C.h"
#include "game/fn_80178D18.h"

extern "C" {
int fn_800A8444(int team);
int fn_800A8408(int team);
float fn_80237260(int stream);
int fn_801486A0(void);
}

static inline short Clamp_80125F3C(const short &value, short low, short high)
{
    return value < low ? low : (value > high ? high : value);
}

static inline short Scale_80125F3C(short from, short to, short t, short range)
{
    return from + (to - from) * t / range;
}

extern "C" signed char fn_80125F3C(short *pRatings)
{
    short value = Scale_80125F3C(15, 0, Clamp_80125F3C(pRatings[9], 0, 255), 255);
    return value < 0 ? 0 : (value > 15 ? 15 : value);
}

extern "C" signed char fn_80125FA0(Object_80039F5C *p)
{
    short *pRatings = p->mRatings;
    short value;

    if (fn_800A8444(p->mIdBytes[2]) && fn_800A8408(p->mIdBytes[2]) == 1) {
        value = (int)(fn_80237260(0) * 45.0f);
    } else {
        value = Scale_80125F3C(126, 0, Clamp_80125F3C(pRatings[5], 0, 255), 255);
    }
    if (fn_801486A0() == 2 && fn_80178D70(p->mIdBytes[2]) == 1) {
        value = (int)(value / 10.0f);
    }
    return value < 0 ? 0 : (value > 126 ? 126 : value);
}
