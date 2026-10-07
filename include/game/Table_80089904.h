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

/* Counted table of 8-byte entries; passed to fn_8009C56C and fn_801BBC3C. */
struct Table_80089904 {
    unsigned short mCount;
    unsigned char mUnknown2[2];
    Entry_80089904 mEntries[1];
};

struct Value_801BBD5C {
    float mValue;
    unsigned char mUnknown4[8];
};

/* Object that fn_801BBD5C returns. */
struct Object_801BBD5C {
    unsigned char mUnknown0[4];
    unsigned int mCount;
    unsigned char mUnknown8[4];
    float mUnknown12;
    float mUnknown16;
    unsigned char mUnknown20[8];
    Value_801BBD5C mValues[1];
};

#endif
