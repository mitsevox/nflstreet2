#ifndef GAME_STATE_800FDA58_H
#define GAME_STATE_800FDA58_H
#include "game/Object_8017886C.h"

struct State_800FDA58 {
    union { short mUnknown0; unsigned char mUnknown0Bytes[2]; };
    unsigned char mUnknown2;
    union { char mUnknown3[1]; unsigned char mUnknown3Byte; };
    int mUnknown4;
    float mUnknown8;
    float mUnknown12;
    int mUnknown16;
    union { char mUnknown20[28]; struct { float mUnknown20Float, mUnknown24, mUnknown28; Point_8017886C mUnknown32; float mUnknown40, mUnknown44; }; };
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
};

struct State_800FF7A8 {
    int mUnknown0;
    unsigned char mUnknown4;
};

struct State_800FFDFC {
    unsigned char mUnknown0;
    char mUnknown1[3];
    float mUnknown4;
    float mUnknown8;
};

#endif
