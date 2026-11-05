#ifndef GAME_ANIMMOMENTUMACTOR_H
#define GAME_ANIMMOMENTUMACTOR_H

#include "engine/Record_800D81C8.h"

/* Partial view of the player whose momentum src/game/AnimMomentum.cpp carries
   into an animation; fn_8009BCE8 decodes its packed partner reference. */
struct AnimMomentumActor_t {
    char mUnknown0[12];
    unsigned int mUnknownC;
    char mUnknown10[320];
    int mUnknown150;
    char mUnknown154[84];
    Pair_802270A4 mUnknown1A8;
    char mUnknown1B0[20];
    float mUnknown1C4;
    char mUnknown1C8[8];
    Pair_802270A4 mUnknown1D0;
    char mUnknown1D8[308];
    void *mpUnknown30C;
    char mUnknown310[8];
    void *mpUnknown318;
    char mUnknown31C[4];
    Record_800D81C8 *mpUnknown320;
};

#endif
