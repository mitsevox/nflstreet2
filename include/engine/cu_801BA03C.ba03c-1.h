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

Object_801BC084 *fn_801BC084(unsigned int slot);
unsigned short fn_801BAB24(Object_801BC084 *pFile);
unsigned short fn_801BAB2C(Object_801BC084 *pFile);
Anim_801BAB34 *fn_801BAB34(Object_801BC084 *pFile, int anim);
int fn_801BAB48(Object_801BC084 *pFile, int state);
void *fn_801BAC9C(Object_801BC084 *pFile, int stateRef);
unsigned int fn_801BACB0(Object_801BC084 *pFile);
unsigned short fn_801BACBC(Object_801BC084 *pFile, int stateRef);
void fn_801BA850(Object_801BC084 *pFile);

#endif
