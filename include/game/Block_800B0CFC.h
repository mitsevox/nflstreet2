#ifndef GAME_BLOCK_800B0CFC_H
#define GAME_BLOCK_800B0CFC_H

#include "game/Team_80167A8C.h"

/* Records that Entry_800B0CFC +0 points to; fn_800AFE8C tests one of the
   two points against the player. */
struct Zone_800AFE8C {
    unsigned char mUnknown0[16];
    Point_80167910 mUnknown10;
    Point_80167910 mUnknown18;
};

/* 72-byte entries of Block_800B0CFC. */
struct Entry_800B0CFC {
    Zone_800AFE8C *mpUnknown0[5];
    void *mpUnknown14[5];
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

extern "C" Block_800B0CFC *lbl_803EAB14;

#endif
