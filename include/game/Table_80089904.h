#ifndef GAME_TABLE_80089904_H
#define GAME_TABLE_80089904_H

#include "game/Object_801BBD5C.h"

/* Record an entry of Table_80089904 points to. Only the accessed bytes are
   declared; the size is unknown. */
struct Info_80089904 {
    unsigned char mUnknown0[4];
    unsigned char mValue;
    unsigned char mType;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    char mUnknown8[4];
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
};

struct Entry_80089904 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Info_80089904 *mpInfo;
};

/* Filled by fn_801BBC3C: an entry count followed by the entries. */
struct Table_80089904 {
    unsigned short mCount;
    unsigned char mUnknown2[2];
    Entry_80089904 mEntries[1];
};

extern "C" {
int fn_8009C56C(Table_80089904 *pTable, const unsigned char *pValues);
void fn_801BBC3C(unsigned short a, unsigned short b, Table_80089904 *pTable);
}

#endif
