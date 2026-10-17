#ifndef GAME_STEP_800C4460_H
#define GAME_STEP_800C4460_H

#include "game/Object_8017886C.h"

struct Pair_800A14A8 {
    Object_8017886C *mpFirst;
    Object_8017886C *mpSecond;
};

/* One of the eight 32-byte steps of Sequence_800C4460. */
struct Step_800C4460 {
    int (*mpCallback0)(void *p);
    int (*mpCallback4)(void *p);
    void (*mpCallback8)(void *p);
    float mUnknownC;
    union { unsigned char mUnknown10[16]; Pair_800A14A8 mContext; Step_800C4460 *mpUnknown10; };
};

/* 260-byte block cleared by fn_800C4438. */
struct Sequence_800C4460 {
    Step_800C4460 mSteps[8];
    unsigned char mUnknown100;
    unsigned char mUnknown101;
    unsigned char mUnknown102[2];
};

#endif
