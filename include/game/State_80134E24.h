#ifndef GAME_STATE_80134E24_H
#define GAME_STATE_80134E24_H

#include "game/Object_80039F5C.h"

/* This mode overlays the opaque block at player+0x150. */
struct State_80134E24 {
    union {
        int mUnknown0Word;
        struct {
            signed char mUnknown0, mUnknown1;
            unsigned char mUnknown2, mUnknown3;
        };
    };
    short mUnknown4, mUnknown6;
    union { int mUnknown8; unsigned char mUnknown8Bytes[4]; };
    union { int mUnknownC; unsigned char mUnknownCByte; };
    int mUnknown10;
    float mUnknown14;
    unsigned char mUnknown18, mUnknown19, mUnknown1A, mUnknown1B, mUnknown1C;
    unsigned char mUnknown1D[3], mUnknown20[3], mUnknown23[3];
    unsigned char mUnknown26[2];
    Object_80039F5C *mUnknown28;
    signed char mUnknown2C;
    unsigned char mUnknown2D[3], mUnknown30[3];
    unsigned char mUnknown33;
    short mUnknown34;
};

#endif
