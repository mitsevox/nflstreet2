#ifndef GAME_TABLE_80089904_H
#define GAME_TABLE_80089904_H

struct Info_80089904 {
    unsigned char mUnknown0[4];
    unsigned char mValue;
    unsigned char mType;
    unsigned char mUnknown6;
};

struct Entry_80089904 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Info_80089904 *mpInfo;
};

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
