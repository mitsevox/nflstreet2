#ifndef GAME_BLOCK_801BE60C_H
#define GAME_BLOCK_801BE60C_H

#include "game/Object_800D81C8.h"

struct State_800D8140 {
    Pair_802270A4 mUnknown0;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
};

/* Payload returned by fn_801BE60C. Only the accessed parts are declared. */
struct Block_801BE60C {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[24];
    State_800D8140 mUnknown20;
};

extern "C" Block_801BE60C *fn_801BE60C(void *p, int key);

#endif
