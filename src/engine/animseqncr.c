/* Scripted sequence files: makes a loaded sequence file usable by turning its
   offsets into pointers, gives access to its player, static and item records and
   their timed keys, and measures the sequence's length. */

#include "engine/fn_801C065C.h"
#include "engine/animchan.h"
#include "engine/animemot.h"
#include "engine/AnimSeqCamera.h"

#define RELOCATE(p, base) ((p) = (void *)((char *)(base) + (int)(p)))

void *_AnimSeqncrRelocatePtr(void *base, int offset)
{
    return (char *)base + offset;
}

float AnimSeqncrGetLength(AnimSeqncrBank_t *bank)
{
    float result = 0.0f;
    unsigned short i;

    for (i = 0; i < bank->mFrameCount; i++) {
        AnimSeqncrPlayer_t *frame = AnimSeqncrGetPlayerPtr(bank, i);
        AnimFileFormat_t *file = AnimFileGetPtrFromSlot(AnimFileGetSlotFromFileNum(frame->mUnknown2A | 0x4000, frame->mUnknownE));
        if (file != 0) {
            float length = AnimSeqGetLife(AnimFileGetAnimation(file, 0)) / AnimSequencerGetTicksPerSecond();
            if (length > result)
                result = length;
        }
    }
    return result;
}

AnimSeqncrPlayer_t *AnimSeqncrGetPlayerPtr(AnimSeqncrBank_t *bank, unsigned short index)
{
    if (index == 0)
        return bank->mFirstFrame;
    return &bank->mFrames[index - 1];
}

AnimSeqncrPlayer_t *AnimSeqncrGetFirstPlayerPtr(AnimSeqncrBank_t *bank)
{
    return bank->mFirstFrame;
}

AnimSeqncrPlayer_t *AnimSeqncrGetStaticPtr(AnimSeqncrBank_t *bank, int index)
{
    return &bank->mFrames2[index];
}

AnimSeqncrItem_t *AnimSeqncrGetItemPtr(AnimSeqncrBank_t *bank, int index)
{
    return &bank->mItems[index];
}

void AnimSeqncrRelocateSeqFile(AnimSeqncrFile_t *file)
{
    unsigned int i;

    for (i = 0; i < file->mCount; i++) {
        AnimSeqncrBank_t *bank;
        unsigned short j;
        unsigned int k;

        file->mBanks[i] = bank = _AnimSeqncrRelocatePtr(file, (int)file->mBanks[i]);
        bank->mUnknown14 = _AnimSeqncrRelocatePtr(file, (int)bank->mUnknown14);
        bank->mFirstFrame = _AnimSeqncrRelocatePtr(file, (int)bank->mFirstFrame);
        bank->mFrames = _AnimSeqncrRelocatePtr(file, (int)bank->mFrames);
        bank->mFrames2 = _AnimSeqncrRelocatePtr(file, (int)bank->mFrames2);
        bank->mGroups = _AnimSeqncrRelocatePtr(file, (int)bank->mGroups);
        bank->mItems = _AnimSeqncrRelocatePtr(file, (int)bank->mItems);
        if (bank->mFrameCount == 0xFFFF) {
            bank->mFirstFrame = 0;
            bank->mFrameCount = 0;
        }
        for (j = 0; j < bank->mGroupCount; j++) {
            AnimSeqCamGroup_t *group = &bank->mGroups[j];
            unsigned short m;

            group->mChildren = _AnimSeqncrRelocatePtr(file, (int)group->mChildren);
            if (AnimGetSeqVersion() != 2)
                continue;
            for (m = 0; m < group->mCount; m++) {
                AnimSeqCamSubGroup_t *child = &group->mChildren[m];
                unsigned short n;

                child->mSamples = _AnimSeqncrRelocatePtr(file, (int)child->mSamples);
                for (n = 0; n < child->mCount; n++) {
                    AnimSeqCamSample_t *sample = &child->mSamples[n];
                    RELOCATE(sample->mCurves[0].mpKeys, file);
                    RELOCATE(sample->mCurves[1].mpKeys, file);
                    RELOCATE(sample->mCurves[2].mpKeys, file);
                    RELOCATE(sample->mCurves[3].mpKeys, file);
                    RELOCATE(sample->mCurves[4].mpKeys, file);
                    RELOCATE(sample->mCurves[5].mpKeys, file);
                    RELOCATE(sample->mCurves[6].mpKeys, file);
                    RELOCATE(sample->mCurves[7].mpKeys, file);
                    RELOCATE(sample->mCurves[8].mpKeys, file);
                    RELOCATE(sample->mCurves[9].mpKeys, file);
                    RELOCATE(sample->mCurves[10].mpKeys, file);
                    RELOCATE(sample->mCurves[11].mpKeys, file);
                    RELOCATE(sample->mCurves[12].mpKeys, file);
                    RELOCATE(sample->mCurves[13].mpKeys, file);
                    RELOCATE(sample->mCurves[14].mpKeys, file);
                }
            }
        }
        for (k = 0; k < bank->mFrameCount; k++) {
            bank->mFrames[k].mKeys = _AnimSeqncrRelocatePtr(file, (int)bank->mFrames[k].mKeys);
            bank->mFrames[k].mUnknown20 = 0.0f;
        }
        if (bank->mFirstFrame != 0) {
            bank->mFirstFrame->mKeys = _AnimSeqncrRelocatePtr(file, (int)bank->mFirstFrame->mKeys);
            bank->mFrameCount++;
        }
        for (k = 0; k < bank->mFrameCount2; k++)
            bank->mFrames2[k].mKeys = _AnimSeqncrRelocatePtr(file, (int)bank->mFrames2[k].mKeys);
        for (k = 0; k < bank->mItemCount; k++)
            bank->mItems[k].mUnknown10 = _AnimSeqncrRelocatePtr(file, (int)bank->mItems[k].mUnknown10);
    }
}

/* Queries before the first key return the default value zero. */
int AnimSeqncrGetKeyValue(void *p, float time)
{
    AnimSeqncrPlayer_t *frame = p;
    unsigned int count = frame->mKeyCount;
    unsigned int i = 0;
    int result = 0;

    while (i < count) {
        if (time >= frame->mKeys[i].mTime) {
            result = frame->mKeys[i].mValue;
            i++;
        } else {
            break;
        }
    }
    return result;
}

void AnimSeqncrRelocateTable(AnimSeqncrTable_t *table)
{
    int i;

    if ((table->mHeader.mWord & 0xFFFF0000) != 0x01000000)
        return;
    for (i = 0; i < table->mHeader.mParts.mCount; i++)
        table->mEntries[i] = (char *)table + (int)table->mEntries[i];
}
