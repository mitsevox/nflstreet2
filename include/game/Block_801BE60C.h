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

/* Payload returned by fn_801BE60C. */
struct Block_801BE60C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    int mUnknown14;
    char mUnknown18[4];
    unsigned char mUnknown1C;
    unsigned char mUnknown1D;
    char mUnknown1E[2];
    State_800D8140 mUnknown20;
    char mUnknown38[4];
    unsigned char mUnknown3C;
    unsigned char mUnknown3D;
};

#endif
