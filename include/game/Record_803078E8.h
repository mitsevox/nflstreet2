#ifndef GAME_RECORD_803078E8_H
#define GAME_RECORD_803078E8_H

#include "game/Block_80307980.h"
#include "game/Object_8008044C.h"

/* Element of lbl_803078E8 (14 records of 0xC0 bytes). */
struct Record_803078E8 {
    char mName[32];
    Info_80307908 mInfo;
    unsigned char mUnknown68;
    char mUnknown69;
    unsigned short mUnknown6A;
    unsigned short mUnknown6C;
    unsigned short mUnknown6E;
    unsigned short mUnknown70;
    unsigned char mUnknown72;
    unsigned char mUnknown73;
    unsigned char mUnknown74;
    unsigned char mUnknown75;
    unsigned char mUnknown76;
    unsigned char mUnknown77;
    unsigned char mUnknown78;
    char mUnknown79;
    unsigned char mUnknown7A[25];
    unsigned char mUnknown93;
    unsigned char mUnknown94;
    unsigned char mUnknown95;
    char mUnknown96[2];
    Block_80307980 mBlock;
};

#endif
