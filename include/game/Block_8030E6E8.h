#ifndef GAME_BLOCK_8030E6E8_H
#define GAME_BLOCK_8030E6E8_H

#include "game/Object_80039F5C.h"
#include "game/Entry_802F394C.h"

struct Object_80144CE0;

/* Three code pointers at 0x8030E6DC. */
struct Callbacks_8030E6DC {
    void (*mpCallback0)(void);
    void (*mpCallback4)(void);
    void (*mpCallback8)(float value);
};

/* Object at 0x8030E6E8. Only the accessed members are typed; the size is
   not established. */
struct Block_8030E6E8 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    unsigned short mUnknownC;
    unsigned short mUnknownE;
    union {
        unsigned char mUnknown10[12];
        Vector_80039F5C mVector10;
    };
    Vector_80039F5C mUnknown1C;
    float mUnknown28;
    float mUnknown2C;
    float mUnknown30;
    float mUnknown34;
    union {
        unsigned char mUnknown38[8];
        struct { float mFloat38; unsigned char mUnknown3C; unsigned char mOpaque3D[3]; };
    };
    int mUnknown40;
    unsigned char mUnknown44;
    unsigned char mUnknown45[3];
    int mUnknown48;
    float mUnknown4C;
    float mUnknown50;
    int mUnknown54;
    float mUnknown58;
    int mUnknown5C;
    float mUnknown60;
    int mUnknown64;
    float mUnknown68;
    int mUnknown6C[20];
    Object_80144CE0 *mpUnknownBC[30];
    float mUnknown134[30][4][4];
    unsigned char mUnknown8B4[8];
    unsigned char mUnknown8BC;
    unsigned char mUnknown8BD;
    unsigned char mUnknown8BE[2];
    Entry_802F394C *mpUnknown8C0;
    int mUnknown8C4;
    void *mpUnknown8C8;
};

#endif
