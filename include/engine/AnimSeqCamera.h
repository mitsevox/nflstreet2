#ifndef ENGINE_ANIMSEQCAMERA_H
#define ENGINE_ANIMSEQCAMERA_H

#include "engine/AnimSeqCamSample.h"

typedef struct AnimSeqCamSubGroup_t {
    unsigned short mId;
    unsigned short mCount;
    AnimSeqCamSample_t *mSamples;
} AnimSeqCamSubGroup_t;

typedef struct AnimSeqCamGroup_t {
    unsigned short mId;
    unsigned short mCount;
    AnimSeqCamSubGroup_t *mChildren;
} AnimSeqCamGroup_t;

typedef struct AnimSeqncrKey_t {
    float mTime;
    unsigned char mUnknown4;
    unsigned char mValue;
    unsigned char mUnknown6[2];
} AnimSeqncrKey_t;

typedef struct AnimSeqncrPlayer_t {
    unsigned char mUnknown0[14];
    unsigned short mUnknownE;
    unsigned char mUnknown10[16];
    float mUnknown20;
    unsigned char mUnknown24[4];
    unsigned short mKeyCount;
    unsigned short mUnknown2A;
    AnimSeqncrKey_t *mKeys;
} AnimSeqncrPlayer_t;

typedef struct AnimSeqncrItem_t {
    unsigned char mUnknown0[16];
    void *mUnknown10;
} AnimSeqncrItem_t;

typedef struct AnimSeqncrBank_t {
    unsigned char mUnknown0[4];
    unsigned short mFrameCount;
    unsigned short mFrameCount2;
    unsigned char mUnknown8[4];
    unsigned char mItemCount;
    unsigned char mGroupCount;
    unsigned char mUnknownE[2];
    AnimSeqCamGroup_t *mGroups;
    void *mUnknown14;
    AnimSeqncrPlayer_t *mFirstFrame;
    AnimSeqncrPlayer_t *mFrames;
    AnimSeqncrPlayer_t *mFrames2;
    AnimSeqncrItem_t *mItems;
} AnimSeqncrBank_t;

typedef struct AnimSeqncrFile_t {
    unsigned char mUnknown0[4];
    unsigned int mCount;
    AnimSeqncrBank_t *mBanks[1];
} AnimSeqncrFile_t;

typedef struct AnimSeqncrTable_t {
    union {
        unsigned int mWord;
        struct {
            unsigned short mVersion;
            unsigned short mCount;
        } mParts;
    } mHeader;
    char *mEntries[1];
} AnimSeqncrTable_t;

#ifdef __cplusplus
extern "C" {
#endif
int AnimSequencerInit(float rate);
int AnimSequencerShutdown(void);
float AnimSequencerGetFrameRate(void);
void AnimSeqCamResetLast(void);
void AnimSeqCamSetLast(AnimSeqncrBank_t *bank, unsigned short group, unsigned short sample, unsigned short index);
AnimSeqCamGroup_t *AnimSeqCamFindGroup(AnimSeqncrBank_t *bank, unsigned short id);
AnimSeqCamSubGroup_t *AnimSeqCamFindSubGroup(AnimSeqncrBank_t *bank, unsigned short id, unsigned short subId);
AnimSeqCamSample_t *AnimSeqCamFindCamera(AnimSeqncrBank_t *bank, unsigned short id, unsigned short subId, unsigned short index);
AnimSeqCamSample_t *AnimSeqCamFindFirstCamera(AnimSeqncrBank_t *bank);
void *_AnimSeqncrRelocatePtr(void *base, int offset);
AnimSeqncrPlayer_t *AnimSeqncrGetPlayerPtr(AnimSeqncrBank_t *bank, unsigned short index);
AnimSeqncrPlayer_t *AnimSeqncrGetStaticPtr(AnimSeqncrBank_t *bank, int index);
void AnimSeqncrRelocateSeqFile(AnimSeqncrFile_t *file);
void AnimSeqncrRelocateTable(AnimSeqncrTable_t *table);
#ifdef __cplusplus
}
#endif

#endif
