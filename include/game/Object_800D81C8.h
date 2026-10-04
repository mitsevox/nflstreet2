#ifndef GAME_OBJECT_800D81C8_H
#define GAME_OBJECT_800D81C8_H

struct Pair_802270A4 {
    float mUnknown0;
    float mUnknown4;
};

struct Block_801BD6D4 {
    void *mpUnknown0;
    float mUnknown4;
    float mUnknown8;
};

struct Record_800D81C8 {
    char mUnknown0[76];
    Block_801BD6D4 mUnknown4C;
    char mUnknown58[36];
};

/* Partial view of the object that fn_8009BCE8 decodes a packed reference to. */
struct Object_800D81C8 {
    char mUnknown0[12];
    unsigned int mUnknownC;
    char mUnknown10[320];
    int mUnknown150;
    char mUnknown154[84];
    Pair_802270A4 mUnknown1A8;
    char mUnknown1B0[20];
    float mUnknown1C4;
    char mUnknown1C8[8];
    Pair_802270A4 mUnknown1D0;
    char mUnknown1D8[308];
    void *mpUnknown30C;
    char mUnknown310[8];
    void *mpUnknown318;
    char mUnknown31C[4];
    Record_800D81C8 *mpUnknown320;
};

#endif
