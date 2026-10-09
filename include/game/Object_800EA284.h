#ifndef GAME_OBJECT_800EA284_H
#define GAME_OBJECT_800EA284_H

#include "game/Object_80039F5C.h"
#include "game/cu_80138CC0.h"

/* 48-byte record of the arrays that words +32 and +36 of the player's +3092
   object point to. The two points at +16 and +32 are also read as one
   Segment_80138CC0. */
struct Record_800EA284 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[4];
    union {
        struct {
            Vector_80039F5C mUnknown16;
            char mUnknown28[4];
            Vector_80039F5C mUnknown32;
            char mUnknown44[4];
        };
        Segment_80138CC0 mSegment16;
    };
};

struct Object_800EA284 {
    char mUnknown0[32];
    Record_800EA284 *mpUnknown32;
    Record_800EA284 *mpUnknown36;
};

#endif
