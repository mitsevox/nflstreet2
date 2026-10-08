#ifndef GAME_BLOCK_801BE60C_H
#define GAME_BLOCK_801BE60C_H

#include "game/Object_800D81C8.h"
#include "game/Object_801BBD5C.h"

struct State_800D8140 {
    Pair_802270A4 mUnknown0;
    /* A float for the cu_800D8140 functions; fn_800D8FFC reads the first
       two bytes of the payload's state (payload +0x28) as record indexes. */
    union {
        float mUnknown8;
        unsigned char mUnknown8Bytes[2];
    };
    float mUnknownC;
    float mUnknown10;
    /* Two bytes for the cu_800D8140 functions; fn_800D8FFC and 0x800D9C80
       read payload +0x34 as one signed halfword. */
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
    /* fn_800DC36C reads and writes +0 and +4 as words for its key, and
       fn_800D7BC4/fn_800D7D78 use +0 and +4 as words; the other callers
       use the byte and float views. */
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
    /* fn_800D8B84 and fn_800D8E68 keep four object pointers here;
       fn_800D7BC4 and fn_800D7D78 use a halfword and signed bytes. */
    union {
        struct {
            Object_801BBD5C *mpUnknownC;
            Object_801BBD5C *mpUnknown10;
            Object_801BBD5C *mpUnknown14;
            Object_801BBD5C *mpUnknown18;
        };
        struct {
            short mUnknownC;
            signed char mUnknownE[11];
        };
    };
    char mUnknown1C[4];
    State_800D8140 mUnknown20;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
    char mUnknown3A[2];
    unsigned char mUnknown3C;
    unsigned char mUnknown3D;
};

#endif
