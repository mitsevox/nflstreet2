#ifndef GAME_RECORD_800A0624_H
#define GAME_RECORD_800A0624_H

#include "game/Object_8017886C.h"

/* 24 bytes cleared by fn_800A0624. */
struct Record_800A0624 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    int mUnknown4;
    union { unsigned char mUnknown8[4]; int mWord8; };
    int mUnknownC;
    int mUnknown10;
    union { unsigned char mUnknown14[4]; float mFloat14; };
};

/* 32 bytes cleared by fn_800A0684. */
struct Record_800A0684 {
    int mUnknown0;
    int mUnknown4;
    Point_8017886C mUnknown8;
    unsigned char mUnknown10[12];
    unsigned char mUnknown1C;
};

struct Block_802D7C64 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
};

#endif
