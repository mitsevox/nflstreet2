#ifndef GAME_BLOCK_801BE60C_H
#define GAME_BLOCK_801BE60C_H

#include "game/Object_800D81C8.h"
#include "game/Object_801BBD5C.h"

struct State_800D8140 {
    Pair_802270A4 mUnknown0;
    union {
        float mUnknown8;
        unsigned char mUnknown8Bytes[2];
    };
    float mUnknownC;
    float mUnknown10;
    union {
        struct {
            unsigned char mUnknown14;
            unsigned char mUnknown15;
        };
        short mUnknown14Half;
    };
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
    union {
        struct {
            float mUnknownC;
            float mUnknown10;
            int mUnknown14;
            char mUnknown18[4];
        };
        struct {
            Object_801BBD5C *mpUnknownC;
            Object_801BBD5C *mpUnknown10;
            Object_801BBD5C *mpUnknown14;
            Object_801BBD5C *mpUnknown18;
        };
        struct {
            short mUnknownCHalf;
            signed char mUnknownE[11];
        };
    };
    unsigned char mUnknown1C;
    unsigned char mUnknown1D;
    char mUnknown1E[2];
    State_800D8140 mUnknown20;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
    char mUnknown3A[2];
    unsigned char mUnknown3C;
    unsigned char mUnknown3D;
};

#endif
