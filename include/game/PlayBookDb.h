#ifndef GAME_PLAYBOOKDB_H
#define GAME_PLAYBOOKDB_H

#include "game/Object_8017886C.h"

struct PlayBookTeam_t;

/* One of the 8-byte slots at PlayBookSet_t +0x1C, filled by PlayBookDbLoadSetSlots. */
struct PlayBookSlot_t {
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

/* One 40-byte entry of the 11 x 7 table at PlayBookSet_t +0x84. */
struct PlayBookPosition_t {
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

/* Filled by PlayBookDbLoadSetByOrder and PlayBookDbLoadSet, which clear all 0xCA8 bytes first. */
struct PlayBookSet_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned short mUnknownC;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    int mUnknown10;
    unsigned int mUnknown14;
    int mUnknown18;
    PlayBookSlot_t mUnknown1C[13];
    PlayBookPosition_t mUnknown84[11][7];
    char mUnknownC8C[0x1C];
};

/* Filled by PlayBookDbLoadFormation, which clears all 0xCE4 bytes first. */
struct PlayBookFormation_t {
    int mUnknown0;
    int mUnknown4;
    PlayBookSet_t mUnknown8;
    char mUnknownCB0[0x34];
};

/* Filled by PlayBookDbLoadPlay, which clears all 0x20C bytes first. */
struct PlayBookPlay_t {
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
unsigned short PlayBookDbCountFormations(int tag, int kind);
int PlayBookDbLoadFormation(int tag, int a, int b, PlayBookFormation_t *pObject);
unsigned short PlayBookDbCountSets(int tag, int key);
void PlayBookDbLoadSetByOrder(int tag, int key, int index, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject);
void PlayBookDbLoadSet(int tag, int key, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject);
unsigned short PlayBookDbCountPlays(int tag, int key);
int PlayBookDbLoadPlay(int tag, int key, int index, PlayBookPlay_t *pRecord);
}

#endif
