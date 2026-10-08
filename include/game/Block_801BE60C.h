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
    /* fn_800DC36C reads and writes +0 and +4 as words for its key; the
       other callers use the byte and float views. */
    union {
        struct {
            unsigned char mUnknown0;
            unsigned char mUnknown1;
            unsigned char mUnknown2;
            unsigned char mUnknown3;
        };
        int mUnknown0Word;
    };
    union {
        float mUnknown4;
        int mUnknown4Word;
    };
    float mUnknown8;
    char mUnknownC[20];
    State_800D8140 mUnknown20;
    char mUnknown38[4];
    unsigned char mUnknown3C;
    unsigned char mUnknown3D;
};

#endif
