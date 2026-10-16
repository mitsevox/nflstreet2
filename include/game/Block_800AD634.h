#ifndef GAME_BLOCK_800AD634_H
#define GAME_BLOCK_800AD634_H

/* 16-byte block allocated under the id 'gply' by fn_800AD634: the current
   and previous game mode, then a flag and a value set by fn_800AD9C0. */
struct Block_800AD634 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9[3];
    float mUnknownC;
};

#endif
