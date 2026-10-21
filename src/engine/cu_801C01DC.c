#include "engine/cu_801B9F00.h"
#include "engine/cu_801BA818.h"
#include "engine/cu_801BFFA8.h"

#define RELOCATE(p, base) ((p) = (void *)((char *)(base) + (int)(p)))

void *fn_801C01DC(void *base, int offset)
{
    return (char *)base + offset;
}

float fn_801C01E4(Bank_801C009C *bank)
{
    float result = 0.0f;
    unsigned short i;

    for (i = 0; i < bank->mFrameCount; i++) {
        Frame_801C029C *frame = fn_801C029C(bank, i);
        AnimFileFormat_t *file = fn_801BC084(fn_801BBE5C(frame->mUnknown2A | 0x4000, frame->mUnknownE));
        if (file != 0) {
            float length = fn_801BD60C(fn_801BAB34(file, 0)) / fn_801BFFA0();
            if (!(length <= result))
                result = length;
        }
    }
    return result;
}

Frame_801C029C *fn_801C029C(Bank_801C009C *bank, unsigned short index)
{
    if (index == 0)
        return bank->mFirstFrame;
    return &bank->mFrames[index - 1];
}

Frame_801C029C *fn_801C02C4(Bank_801C009C *bank)
{
    return bank->mFirstFrame;
}

Frame_801C029C *fn_801C02CC(Bank_801C009C *bank, int index)
{
    return &bank->mFrames2[index];
}

Item_801C02DC *fn_801C02DC(Bank_801C009C *bank, int index)
{
    return &bank->mItems[index];
}

void fn_801C02EC(File_801C02EC *file)
{
    unsigned int i;

    for (i = 0; i < file->mCount; i++) {
        Bank_801C009C *bank;
        unsigned short j;
        unsigned int k;

        file->mBanks[i] = bank = fn_801C01DC(file, (int)file->mBanks[i]);
        bank->mUnknown14 = fn_801C01DC(file, (int)bank->mUnknown14);
        bank->mFirstFrame = fn_801C01DC(file, (int)bank->mFirstFrame);
        bank->mFrames = fn_801C01DC(file, (int)bank->mFrames);
        bank->mFrames2 = fn_801C01DC(file, (int)bank->mFrames2);
        bank->mGroups = fn_801C01DC(file, (int)bank->mGroups);
        bank->mItems = fn_801C01DC(file, (int)bank->mItems);
        if (bank->mFrameCount == 0xFFFF) {
            bank->mFirstFrame = 0;
            bank->mFrameCount = 0;
        }
        for (j = 0; j < bank->mGroupCount; j++) {
            Group_801BFFD8 *group = &bank->mGroups[j];
            unsigned short m;

            group->mChildren = fn_801C01DC(file, (int)group->mChildren);
            if (fn_801B9EF8() != 2)
                continue;
            for (m = 0; m < group->mCount; m++) {
                Group_801C001C *child = &group->mChildren[m];
                unsigned short n;

                child->mSamples = fn_801C01DC(file, (int)child->mSamples);
                for (n = 0; n < child->mCount; n++) {
                    Sample_801C009C *sample = &child->mSamples[n];
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
            bank->mFrames[k].mKeys = fn_801C01DC(file, (int)bank->mFrames[k].mKeys);
            bank->mFrames[k].mUnknown20 = 0.0f;
        }
        if (bank->mFirstFrame != 0) {
            bank->mFirstFrame->mKeys = fn_801C01DC(file, (int)bank->mFirstFrame->mKeys);
            bank->mFrameCount++;
        }
        for (k = 0; k < bank->mFrameCount2; k++)
            bank->mFrames2[k].mKeys = fn_801C01DC(file, (int)bank->mFrames2[k].mKeys);
        for (k = 0; k < bank->mItemCount; k++)
            bank->mItems[k].mUnknown10 = fn_801C01DC(file, (int)bank->mItems[k].mUnknown10);
    }
}

void fn_801C06A0(Table_801C06A0 *table)
{
    int i;

    if ((table->mHeader.mWord & 0xFFFF0000) != 0x01000000)
        return;
    for (i = 0; i < table->mHeader.mParts.mCount; i++)
        table->mEntries[i] = (char *)table + (int)table->mEntries[i];
}
