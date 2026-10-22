#ifndef GAME_ANIMFILEFORMAT_H
#define GAME_ANIMFILEFORMAT_H

#include "engine/Record_800D81C8.h"
#include "game/Record_8019D8AC.h"

typedef struct AnimMotionGroupView {
    int count;
    char **motion;
    Record_8019D8AC *compress;
} AnimMotionGroupView;

typedef struct AnimGroupHeaderView {
    int count;
} AnimGroupHeaderView;

typedef struct Anims_801BAB34 {
    int mCount;
    Anim_801BAB34 *mAnims[1];
} Anims_801BAB34;

typedef struct StateAnim_801BAB88 {
    unsigned short mId;
    unsigned char mUnknown2[2];
    Anim_801BAB34 *mpAnim;
} StateAnim_801BAB88;

typedef struct StateAnims_801BAB88 {
    unsigned short mCount;
    unsigned short mUnknown2;
    StateAnim_801BAB88 mEntries[1];
} StateAnims_801BAB88;

/* Transition rule; fn_801BEFA4 matches it against the current and next state. */
typedef struct StateTran_801BAC1C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned short mUnknown8;
    unsigned char mUnknownA[2];
    struct Transition_801BEFA4 *mpUnknownC;
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
    int mCount;
    State_801BAB48 mStates[1];
} States_801BAB48;

/* Animation file header; offsets are relocated in place by fn_801BA850. */
typedef struct AnimFileFormat_t {
    unsigned short objectType;
    unsigned short fileNum;
    unsigned short motionCount;
    unsigned short flags;
    States_801BAB48 *states;
    Anims_801BAB34 *anims;
    char **motion;
    Record_8019D8AC *compress;
    AnimGroupHeaderView *groups;
    AnimMotionGroupView *groupMotion;
} AnimFileFormat_t;

#ifdef __cplusplus
void AnimExtnRelocateFile(AnimFileFormat_t *file);
#endif

#endif
