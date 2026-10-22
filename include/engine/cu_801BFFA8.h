#ifndef ENGINE_CU_801BFFA8_H
#define ENGINE_CU_801BFFA8_H

#include "engine/Sample_801C009C.h"

typedef struct Group_801C001C {
    unsigned short mId;
    unsigned short mCount;
    Sample_801C009C *mSamples;
} Group_801C001C;

typedef struct Group_801BFFD8 {
    unsigned short mId;
    unsigned short mCount;
    Group_801C001C *mChildren;
} Group_801BFFD8;

typedef struct Key_801C065C {
    float mTime;
    unsigned char mUnknown4;
    unsigned char mValue;
    unsigned char mUnknown6[2];
} Key_801C065C;

typedef struct Frame_801C029C {
    unsigned char mUnknown0[14];
    unsigned short mUnknownE;
    unsigned char mUnknown10[16];
    float mUnknown20;
    unsigned char mUnknown24[4];
    unsigned short mKeyCount;
    unsigned short mUnknown2A;
    Key_801C065C *mKeys;
} Frame_801C029C;

typedef struct Item_801C02DC {
    unsigned char mUnknown0[16];
    void *mUnknown10;
} Item_801C02DC;

typedef struct Bank_801C009C {
    unsigned char mUnknown0[4];
    unsigned short mFrameCount;
    unsigned short mFrameCount2;
    unsigned char mUnknown8[4];
    unsigned char mItemCount;
    unsigned char mGroupCount;
    unsigned char mUnknownE[2];
    Group_801BFFD8 *mGroups;
    void *mUnknown14;
    Frame_801C029C *mFirstFrame;
    Frame_801C029C *mFrames;
    Frame_801C029C *mFrames2;
    Item_801C02DC *mItems;
} Bank_801C009C;

typedef struct File_801C02EC {
    unsigned char mUnknown0[4];
    unsigned int mCount;
    Bank_801C009C *mBanks[1];
} File_801C02EC;

typedef struct Table_801C06A0 {
    union {
        unsigned int mWord;
        struct {
            unsigned short mVersion;
            unsigned short mCount;
        } mParts;
    } mHeader;
    char *mEntries[1];
} Table_801C06A0;

#ifdef __cplusplus
extern "C" {
#endif
int fn_801BFEF8(float rate);
int fn_801BFF50(void);
float fn_801BFFA0(void);
void fn_801BFFA8(void);
void fn_801BFFC4(Bank_801C009C *bank, unsigned short group, unsigned short sample, unsigned short index);
Group_801BFFD8 *fn_801BFFD8(Bank_801C009C *bank, unsigned short id);
Group_801C001C *fn_801C001C(Bank_801C009C *bank, unsigned short id, unsigned short subId);
Sample_801C009C *fn_801C009C(Bank_801C009C *bank, unsigned short id, unsigned short subId, unsigned short index);
Sample_801C009C *fn_801C00F8(Bank_801C009C *bank);
void *fn_801C01DC(void *base, int offset);
Frame_801C029C *fn_801C029C(Bank_801C009C *bank, unsigned short index);
Frame_801C029C *fn_801C02CC(Bank_801C009C *bank, int index);
void fn_801C02EC(File_801C02EC *file);
void fn_801C06A0(Table_801C06A0 *table);
#ifdef __cplusplus
}
#endif

#endif
