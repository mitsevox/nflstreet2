#ifndef GAME_TABLE_80089904_H
#define GAME_TABLE_80089904_H

/* Record an entry of Table_80089904 points to. Only the accessed bytes are
   declared; the size is unknown. */
struct Info_80089904 {
    unsigned char mUnknown0[4];
    unsigned char mValue;
    unsigned char mType;
    unsigned char mUnknown6;
    char mUnknown7[5];
    int mUnknown12;
    char mUnknown16[8];
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

extern "C" void fn_801BBC3C(unsigned short a, unsigned short b, Table_80089904 *pTable);

#endif
