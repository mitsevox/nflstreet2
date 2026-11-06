/* Sequence cameras: finds camera samples in a scripted sequence by group,
   subgroup and index, and remembers the last one found. */

#include "engine/AnimSeqCamera.h"

extern unsigned short _uLastGroupIndex;
extern unsigned short _uLastSubGroupIndex;
extern unsigned short _uLastIndex;
extern AnimSeqncrBank_t *_pLastSeq;

void AnimSeqCamResetLast(void)
{
    _uLastGroupIndex = -1;
    _uLastSubGroupIndex = -1;
    _uLastIndex = -1;
    _pLastSeq = 0;
}

void AnimSeqCamSetLast(AnimSeqncrBank_t *bank, unsigned short group, unsigned short sample, unsigned short index)
{
    _uLastGroupIndex = group;
    _uLastSubGroupIndex = sample;
    _uLastIndex = index;
    _pLastSeq = bank;
}

AnimSeqCamGroup_t *AnimSeqCamFindGroup(AnimSeqncrBank_t *bank, unsigned short id)
{
    unsigned short i;

    for (i = 0; i < bank->mGroupCount; i++) {
        AnimSeqCamGroup_t *group = &bank->mGroups[i];
        if (group->mId == id)
            return group;
    }
    return 0;
}

AnimSeqCamSubGroup_t *AnimSeqCamFindSubGroup(AnimSeqncrBank_t *bank, unsigned short id, unsigned short subId)
{
    AnimSeqCamGroup_t *group = AnimSeqCamFindGroup(bank, id);
    unsigned short i;

    if (group == 0)
        return 0;
    for (i = 0; i < group->mCount; i++) {
        AnimSeqCamSubGroup_t *child = &group->mChildren[i];
        if (child->mId == subId)
            return child;
    }
    return 0;
}

AnimSeqCamSample_t *AnimSeqCamFindCamera(AnimSeqncrBank_t *bank, unsigned short id, unsigned short subId,
                             unsigned short index)
{
    AnimSeqCamSubGroup_t *group = AnimSeqCamFindSubGroup(bank, id, subId);

    if (group != 0 && index < group->mCount && group->mSamples != 0)
        return &group->mSamples[index];
    return 0;
}

AnimSeqCamSample_t *AnimSeqCamFindFirstCamera(AnimSeqncrBank_t *bank)
{
    unsigned short i;
    unsigned short j;

    AnimSeqCamResetLast();
    if (bank->mGroupCount == 0)
        return 0;
    for (i = 0; i < bank->mGroupCount; i++) {
        AnimSeqCamGroup_t *group = &bank->mGroups[i];
        for (j = 0; j < group->mCount; j++) {
            AnimSeqCamSubGroup_t *child = &group->mChildren[j];
            if (child->mCount != 0) {
                AnimSeqCamSetLast(bank, i, j, j);
                return child->mSamples;
            }
        }
    }
    return 0;
}

int AnimSeqCamGetFileNum(AnimSeqncrPlayer_t *frame)
{
    return frame->mUnknownE & 0x7FFF;
}

int AnimSeqCamGetFileFlag(AnimSeqncrPlayer_t *frame)
{
    if (frame->mUnknownE & 0x8000)
        return 1;
    return 0;
}
