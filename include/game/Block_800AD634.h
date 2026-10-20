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

/* Enter, update and exit handlers of each game mode, indexed by mode. */
struct Mode_80297FC8 {
    void (*mpEnter)(float dt);
    void (*mpUpdate)(float dt);
    void (*mpExit)(float dt);
};

extern "C" Mode_80297FC8 lbl_80297FC8[12];

#endif
