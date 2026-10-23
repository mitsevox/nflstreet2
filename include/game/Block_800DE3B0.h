#ifndef GAME_BLOCK_800DE3B0_H
#define GAME_BLOCK_800DE3B0_H

#include "game/Block_801BE60C.h"

/* Records of the table fn_801BBD5C returns, as src/game/cu_800DAEE4.cpp
   reads them. */
struct Entry_800DE51C {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    char mUnknown3[17];
};

struct Table_800DE51C {
    char mUnknown0[4];
    unsigned short mCount;
    char mUnknown6[2];
    Entry_800DE51C mEntries[1];
};

/* Per-key block that fn_801BE60C returns and fn_800DEAB0 fills (same layout
   as the local definition in src/game/cu_800DAEE4.cpp). */
struct Block_800DE3B0 {
    float mUnknown0;
    Pair_802270A4 mUnknown4, mUnknownC;
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C, mUnknown1D, mUnknown1E, mUnknown1F;
    State_800D8140 mUnknown20;
    int mUnknown38;
    unsigned char mUnknown3C, mUnknown3D;
    signed char mUnknown3E, mUnknown3F;
};

#endif
