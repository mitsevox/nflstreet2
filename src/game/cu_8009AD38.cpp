#include "game/Item_80097440.h"

extern "C" {
extern Block_8009AB34 *lbl_803EA948;
extern float lbl_803EA954;
extern float lbl_803EA958;
extern float lbl_803EA95C;
extern float lbl_803EA960;
extern float lbl_803EA964;
extern float lbl_803EA968;
extern float lbl_803EA96C;
extern float lbl_803EA970;
extern float lbl_803EA974;
extern float lbl_803EA978;
}

extern "C" int fn_8009AD38(int team, int value)
{
    int other = 1;

    if (team == 1) {
        other = 0;
    }
    if (lbl_803EA948->mUnknown0[team] != 0.0f) {
        value -= (int)(value * lbl_803EA948->mUnknown0[team] * lbl_803EA958);
    } else if (lbl_803EA948->mUnknown0[other] != 0.0f) {
        value += (int)(value * (lbl_803EA954 * lbl_803EA948->mUnknown0[other]));
    }
    return value;
}

extern "C" int fn_8009AE1C(int team, int value)
{
    int other = 1;

    if (team == 1) {
        other = 0;
    }
    if (lbl_803EA948->mUnknown0[team] != 0.0f) {
        value -= (int)(value * lbl_803EA948->mUnknown0[team] * lbl_803EA960);
    } else if (lbl_803EA948->mUnknown0[other] != 0.0f) {
        value += (int)(value * (lbl_803EA95C * lbl_803EA948->mUnknown0[other]));
    }
    return value;
}

extern "C" signed char fn_8009AF00(int team, signed char value)
{
    int other = 1;

    if (team == 1) {
        other = 0;
    }
    if (lbl_803EA948->mUnknown0[team] != 0.0f) {
        value -= (int)(value * lbl_803EA948->mUnknown0[team] * lbl_803EA968);
    } else if (lbl_803EA948->mUnknown0[other] != 0.0f) {
        value += (int)(value * (lbl_803EA964 * lbl_803EA948->mUnknown0[other]));
    }
    return value;
}

extern "C" int fn_8009AFE8(int team, int value)
{
    int other = 1;

    if (team == 1) {
        other = 0;
    }
    if (lbl_803EA948->mUnknown0[team] != 0.0f) {
        value -= (int)(value * lbl_803EA948->mUnknown0[team] * lbl_803EA970);
    } else if (lbl_803EA948->mUnknown0[other] != 0.0f) {
        value += (int)(value * (lbl_803EA96C * lbl_803EA948->mUnknown0[other]));
    }
    return value;
}

extern "C" int fn_8009B0CC(int team, int value)
{
    int other = 1;

    if (team == 1) {
        other = 0;
    }
    if (lbl_803EA948->mUnknown0[team] != 0.0f) {
        value -= (int)(value * lbl_803EA948->mUnknown0[team] * lbl_803EA978);
    } else if (lbl_803EA948->mUnknown0[other] != 0.0f) {
        value += (int)(value * (lbl_803EA974 * lbl_803EA948->mUnknown0[other]));
    }
    return value;
}
