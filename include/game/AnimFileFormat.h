#ifndef GAME_ANIMFILEFORMAT_H
#define GAME_ANIMFILEFORMAT_H

#include "engine/AnimChannel.h"
#include "game/AnimQuantContext.h"

typedef struct AnimMotionGroupView {
    int count;
    char **motion;
    AnimQuantContext *compress;
} AnimMotionGroupView;

typedef struct AnimGroupHeaderView {
    int count;
} AnimGroupHeaderView;

typedef struct AnimFileAnims_t {
    int mCount;
    AnimScript_t *mAnims[1];
} AnimFileAnims_t;

typedef struct AnimFileStateAnim_t {
    unsigned short mId;
    unsigned char mUnknown2[2];
    AnimScript_t *mpAnim;
} AnimFileStateAnim_t;

typedef struct AnimFileStateAnims_t {
    unsigned short mCount;
    unsigned short mUnknown2;
    AnimFileStateAnim_t mEntries[1];
} AnimFileStateAnims_t;

/* Transition rule; fn_801BEFA4 matches it against the current and next state. */
typedef struct AnimFileStateTran_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned short mUnknown8;
    unsigned char mUnknownA[2];
    struct Transition_801BEFA4 *mpUnknownC;
} AnimFileStateTran_t;

typedef struct AnimFileStateTrans_t {
    int mCount;
    AnimFileStateTran_t mEntries[1];
} AnimFileStateTrans_t;

typedef struct AnimFileState_t {
    unsigned short mId;
    unsigned char mUnknown2[2];
    AnimFileStateAnims_t *mpAnims;
    void *mpUnknown8;
    AnimFileStateTrans_t *mpTrans;
} AnimFileState_t;

typedef struct AnimFileStates_t {
    int mCount;
    AnimFileState_t mStates[1];
} AnimFileStates_t;

/* Animation file header; offsets are relocated in place by AnimFileRelocate. */
typedef struct AnimFileFormat_t {
    unsigned short objectType;
    unsigned short fileNum;
    unsigned short motionCount;
    unsigned short flags;
    AnimFileStates_t *states;
    AnimFileAnims_t *anims;
    char **motion;
    AnimQuantContext *compress;
    AnimGroupHeaderView *groups;
    AnimMotionGroupView *groupMotion;
} AnimFileFormat_t;

#ifdef __cplusplus
void AnimExtnRelocateFile(AnimFileFormat_t *file);
#endif

#endif
