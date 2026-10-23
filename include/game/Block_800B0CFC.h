#ifndef GAME_BLOCK_800B0CFC_H
#define GAME_BLOCK_800B0CFC_H

#include "game/Team_80167A8C.h"
#include "game/fn_800670B4.h"

/* 72-byte entries of Block_800B0CFC. */
struct Entry_800B0CFC {
    Entry_8006719C *mpUnknown0[5];
    Entry_8006719C *mpUnknown14[5];
    int mUnknown28[5];
    unsigned char mUnknown3C[5];
    unsigned char mUnknown41[5];
    unsigned char mUnknown46;
    unsigned char mUnknown47;
};

/* 744-byte block allocated under the id 'mmot' (fn_800B0CFC). */
struct Block_800B0CFC {
    Entry_800B0CFC mEntries[2][5];
    int mUnknown2D0;
    int mUnknown2D4;
    int mUnknown2D8;
    int mUnknown2DC;
    int mUnknown2E0;
    unsigned char mUnknown2E4;
    unsigned char mUnknown2E5;
    unsigned char mUnknown2E6[2];
};

extern "C" {
extern Block_800B0CFC *lbl_803EAB14;
}

#endif
