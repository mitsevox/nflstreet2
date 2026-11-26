#ifndef GAME_GEARDB_H
#define GAME_GEARDB_H

#include "game/DbCursor.h"

/* One 'RAEG' row as GearDbReadRow copies it out of the cursor: four words, two
   33-byte names (the second one is cut at its first space), 16 bytes, words at
   +0x64, +0x68 and +0x6C, seven flags at +0x70 and a word at +0x78. */
struct GearRow_t {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    char mUnknown10[33];
    char mName[33];
    char mUnknown52[16];
    int mUnknown64;
    int mUnknown68;
    int mUnknown6C;
    unsigned char mUnknown70;
    unsigned char mUnknown71;
    unsigned char mUnknown72;
    unsigned char mUnknown73;
    unsigned char mUnknown74;
    unsigned char mUnknown75;
    unsigned char mUnknown76;
    int mUnknown78;
};

extern "C" {
void GearDbReadRow(DbCursor *pCursor, GearRow_t *pRow);
unsigned int GearDbGetGrsi(DbCursor *pCursor);
}

#endif
