#ifndef GAME_FN_800670B4_H
#define GAME_FN_800670B4_H

#include "game/Object_8017886C.h"

struct Team_80167A8C;

/* One of the 8-byte slots at Object_8006719C +0x1C, filled by fn_80066318. */
struct Slot_8006719C {
    union {
        char mName[6];
        struct {
            char mUnknown0[5];
            unsigned char mUnknown5;
        };
    };
    union {
        unsigned short mUnknown6;
        unsigned short mId;
    };
};

/* One 40-byte entry of the 11 x 7 table at Object_8006719C +0x84. */
struct Entry_8006719C {
    unsigned short mUnknown0;
    union {
        unsigned short mUnknown2;
        struct {
            char mUnknown2Pad;
            unsigned char mUnknown3;
        };
    };
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
    unsigned short mUnknownC;
    unsigned short mUnknownE;
    Point_8017886C mUnknown10;
    Point_8017886C mUnknown18;
    int mUnknown20;
    int mUnknown24;
};

/* Filled by fn_8006719C and fn_8006723C, which clear all 0xCA8 bytes first. */
struct Object_8006719C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned short mUnknownC;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    int mUnknown10;
    unsigned int mUnknown14;
    int mUnknown18;
    Slot_8006719C mUnknown1C[13];
    Entry_8006719C mUnknown84[11][7];
    char mUnknownC8C[0x1C];
};

/* Filled by fn_800670B4, which clears all 0xCE4 bytes first. */
struct Object_800670B4 {
    int mUnknown0;
    int mUnknown4;
    Object_8006719C mUnknown8;
    char mUnknownCB0[0x34];
};

/* Filled by fn_80067338, which clears all 0x20C bytes first. */
struct Record_80067338 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    char mUnknownE[2];
    int mUnknown10;
    /* Read both as a word and as its last byte. */
    union {
        int mUnknown14;
        struct {
            char mUnknown14Pad[3];
            unsigned char mUnknown17;
        };
    };
    unsigned int mUnknown18;
    unsigned char mUnknown1C[3][4];
    unsigned char mUnknown28[5][3];
    char mUnknown37;
    unsigned char mUnknown38[7][10][4];
    char mUnknown150[0xA0];
    char mUnknown1F0[0x1C];
};

extern "C" {
unsigned short fn_80067038(int tag, int kind);
int fn_800670B4(int tag, int a, int b, Object_800670B4 *pObject);
unsigned short fn_80067120(int tag, int key);
void fn_8006719C(int tag, int key, int index, Team_80167A8C *pTeam, Object_8006719C *pObject);
void fn_8006723C(int tag, int key, Team_80167A8C *pTeam, Object_8006719C *pObject);
unsigned short fn_800672BC(int tag, int key);
int fn_80067338(int tag, int key, int index, Record_80067338 *pRecord);
}

#endif
