#ifndef ENGINE_CU_801BA03C_BA03C_1_H
#define ENGINE_CU_801BA03C_BA03C_1_H

typedef struct Anim_801BAB34 {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2;
} Anim_801BAB34;

typedef struct Anims_801BAB34 {
    unsigned int mCount;
    Anim_801BAB34 *mAnims[1];
} Anims_801BAB34;

typedef struct StateAnim_801BAB88 {
    unsigned short mId;
    unsigned char mUnknown2[2];
    void *mpAnim;
} StateAnim_801BAB88;

typedef struct StateAnims_801BAB88 {
    unsigned short mCount;
    unsigned short mUnknown2;
    StateAnim_801BAB88 mEntries[1];
} StateAnims_801BAB88;

typedef struct StateTran_801BAC1C {
    unsigned char mUnknown0[12];
    void *mpUnknownC;
} StateTran_801BAC1C;

typedef struct StateTrans_801BAC1C {
    int mCount;
    StateTran_801BAC1C mEntries[1];
} StateTrans_801BAC1C;

typedef struct State_801BAB48 {
    unsigned short mId;
    unsigned char mUnknown2[2];
    StateAnims_801BAB88 *mpAnims;
    void *mpUnknown8;
    StateTrans_801BAC1C *mpTrans;
} State_801BAB48;

typedef struct States_801BAB48 {
    unsigned int mCount;
    State_801BAB48 mStates[1];
} States_801BAB48;

typedef struct Group_801BACD0 {
    unsigned int mCount;
    void **mpMotion;
    void *mpCompress;
} Group_801BACD0;

/* Animation file header returned by fn_801BC084; offsets are relocated in place by fn_801BA850. */
typedef struct Object_801BC084 {
    unsigned short mObjectType;
    unsigned short mFileNum;
    unsigned short mMotionCount;
    unsigned short mFlags;
    States_801BAB48 *mpStates;
    Anims_801BAB34 *mpAnims;
    void **mpMotion;
    void *mpCompress;
    unsigned int *mpGroups;
    Group_801BACD0 *mpGroupMotion;
} Object_801BC084;

/* 32-byte slot record of the table at lbl_803ED5FC. */
typedef struct Buffer_801BB2D8 {
    int mId;
    int mSize;
    int mPart;
    Object_801BC084 *mpData;
    unsigned short mFlags;
    unsigned char mStatus;
    unsigned char mUnknown13;
    unsigned short mObjectType;
    unsigned short mParent;
    int mFrameCache;
    unsigned char mUnknown1C;
    unsigned char mUnknown1D[3];
} Buffer_801BB2D8;

typedef struct Block_801BF3C8 {
    float mWeight;
    unsigned char mUnknown4[4];
    int mUnknown8;
    unsigned char mUnknownC[12];
} Block_801BF3C8;

typedef struct Block_801BD6D4 {
    void *mpUnknown0;
    float mUnknown4;
    float mUnknown8;
    unsigned char mUnknownC[4];
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    float mUnknown14;
    unsigned short mUnknown18;
    unsigned short mUnknown1A;
} Block_801BD6D4;

/* 124-byte channel record; the list header's mCount records follow each other. */
typedef struct Record_800D81C8 {
    unsigned char mUnknown0;
    unsigned char mStatus;
    short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mFlags;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    int mUnknownC;
    unsigned char mUnknown10[12];
    int mUnknown1C;
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown2C;
    Block_801BF3C8 mUnknown30;
    float mUnknown48;
    Block_801BD6D4 mUnknown4C;
    unsigned char mUnknown68[2];
    unsigned char mUnknown6A;
    unsigned char mUnknown6B[17];
} Record_800D81C8;

typedef struct Object_801BA03C {
    unsigned short mUnknown0;
    unsigned char mUnknown2[2];
    unsigned short mCount;
    unsigned char mUnknown6[2];
    int mUnknown8;
} Object_801BA03C;

void fn_801BA360(Record_800D81C8 *pChannel, int a, int b, float x, float y);
void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index);
int fn_801BA650(Record_800D81C8 *pChannel, float time, void *pUser);
int fn_801BA720(Record_800D81C8 *pChannel, Anim_801BAB34 *pAnim, void *pUser);
unsigned short fn_801BAB2C(Object_801BC084 *pFile);
Anim_801BAB34 *fn_801BAB34(Object_801BC084 *pFile, int anim);
int fn_801BAB48(Object_801BC084 *pFile, int state);
void *fn_801BACD0(Object_801BC084 *pFile, int a, int b, unsigned int index, int group);
Object_801BC084 *fn_801BC084(unsigned int slot);

#endif
