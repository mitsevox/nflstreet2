#ifndef GAME_ENTRY_800B206C_H
#define GAME_ENTRY_800B206C_H

/* 36-byte entry filled by fn_800B206C. Two arrays of them sit at +4 and +40
   of the block that 0x803EAB20 points to; fn_801763D0 sorts two of them and
   fn_801744E8 swaps them. */
struct Entry_800B206C {
    int mUnknown0;
    /* Reference word written through fn_8009BD2C, also read by byte. */
    union {
        int mUnknown4;
        unsigned char mUnknown4Bytes[4];
    };
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23[1];
};

#endif
