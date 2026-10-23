#ifndef GAME_PLAN_80121264_H
#define GAME_PLAN_80121264_H

#include "game/Object_8017886C.h"

/* 48-byte entry of Plan_80121264; the array fills +0 to +1440. */
struct Entry_80120E98 {
    Point_8017886C *mpUnknown0;
    Point_8017886C *mpUnknown4;
    Point_8017886C mUnknown8;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
};

/* 32-byte entry of Plan_80121264; the array fills +1444 to +2372. fn_80122670
   fills one per pair of neighbouring Entry_80120E98 records: their midpoint,
   the angle and distance to it from the player, and the gap between them. */
struct Entry_801230B8 {
    Entry_80120E98 *mpUnknown0;
    Entry_80120E98 *mpUnknown4;
    Point_8017886C mUnknown8;
    int mUnknown16;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
};

/* 2376-byte record cleared and filled by fn_80121264 (fn_801231E4 keeps one
   on its stack). */
struct Plan_80121264 {
    Entry_80120E98 mUnknown0[30];
    unsigned int mUnknown1440;
    Entry_801230B8 mUnknown1444[29];
    unsigned int mUnknown2372;
};

#endif
