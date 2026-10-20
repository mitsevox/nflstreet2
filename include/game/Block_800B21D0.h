#ifndef GAME_BLOCK_800B21D0_H
#define GAME_BLOCK_800B21D0_H

#include "game/Entry_800B206C.h"

/* The 96 bytes after the first word of Block_800B21D0, compared by
   fn_800B19E8. */
struct State_800B19E8 {
    Entry_800B206C mUnknown0[1];
    Entry_800B206C mUnknown24[1];
    unsigned char mUnknown48[4];
    short mUnknown4C;
    unsigned char mUnknown4E[12];
    unsigned char mUnknown5A;
    unsigned char mUnknown5B;
    unsigned char mUnknown5C;
    unsigned char mUnknown5D;
    unsigned char mUnknown5E;
    unsigned char mUnknown5F[1];
};

/* Allocated through fn_80238174 under the id 'penl' (fn_800B21D0). */
struct Block_800B21D0 {
    void *mpUnknown0;
    State_800B19E8 mUnknown4;
};

#endif
