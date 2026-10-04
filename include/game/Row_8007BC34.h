#ifndef GAME_ROW_8007BC34_H
#define GAME_ROW_8007BC34_H

#include "game/Object_8007A334.h"

/* One 'RAEG' row as fn_8007BC34 copies it out of the cursor: four words, two
   33-byte names (the second one is cut at its first space), 16 bytes, words at
   +0x64, +0x68 and +0x6C, seven flags at +0x70 and a word at +0x78. */
struct Row_8007BC34 {
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
void fn_8007BC34(Object_8007A334 *pCursor, Row_8007BC34 *pRow);
unsigned int fn_8007BDF8(Object_8007A334 *pCursor);
}

#endif
