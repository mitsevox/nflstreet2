#ifndef GAME_TABLE_80089904_H
#define GAME_TABLE_80089904_H

/* Record that an entry of Table_80089904 points to. Only accessed members
   are declared; the size is unknown. */
struct Info_80089904 {
    unsigned char mUnknown0[4];
    unsigned char mValue;
    unsigned char mType;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
};

struct Entry_80089904 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Info_80089904 *mpInfo;
};

/* Counted table of 8-byte entries starting at +4. */
struct Table_80089904 {
    unsigned short mCount;
    unsigned char mUnknown2[2];
    Entry_80089904 mEntries[1];
};

#endif
