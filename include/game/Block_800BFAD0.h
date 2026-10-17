#ifndef GAME_BLOCK_800BFAD0_H
#define GAME_BLOCK_800BFAD0_H

/* Read by fn_800BD608 through a pointer to +12 of Slot_800BFAD0. */
struct Stick_800BD608 {
    float mX;
    float mY;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
};

/* One of the two 32-byte records at the start of Block_800BFAD0. */
struct Slot_800BFAD0 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    union {
        struct {
            float mUnknownC;
            float mUnknown10;
            unsigned char mUnknown14;
            unsigned char mUnknown15[3];
        };
        Stick_800BD608 mStick;
    };
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
    int mUnknown44;
    unsigned char mUnknown48[0x50];
    int mUnknown98;
    int mUnknown9C;
    int mUnknownA0;
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
