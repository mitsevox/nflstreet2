#ifndef GAME_BLOCK_800BFAD0_H
#define GAME_BLOCK_800BFAD0_H

/* One of the two 32-byte records at the start of Block_800BFAD0. */
struct Slot_800BFAD0 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15[3];
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A[2];
    unsigned char mUnknown1C;
    unsigned char mUnknown1D[3];
};

/* Allocated through fn_80238174 under the id 'prep' (0x800BFAD0). */
struct Block_800BFAD0 {
    Slot_800BFAD0 mSlots[2];
    int mUnknown40;
    unsigned char mUnknown44[0x54];
    unsigned char mUnknown98[4];
    int mUnknown9C;
    unsigned char mUnknownA0[4];
    short mUnknownA4;
    short mUnknownA6;
    unsigned char mUnknownA8;
    unsigned char mUnknownA9[2];
    unsigned char mUnknownAB;
    unsigned int mUnknownAC;
    int mUnknownB0;
    int mUnknownB4;
    int mUnknownB8;
    int mUnknownBC;
    int mUnknownC0;
    unsigned char mUnknownC4;
    unsigned char mUnknownC5;
    unsigned char mUnknownC6;
    unsigned char mUnknownC7;
};

/* .sdata word that holds the allocated block. */
extern "C" Block_800BFAD0 *lbl_803EABA8;

#endif
