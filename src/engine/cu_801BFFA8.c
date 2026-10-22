#include "engine/cu_801BFFA8.h"

extern unsigned short lbl_803EBBB4;
extern unsigned short lbl_803EBBB6;
extern unsigned short lbl_803EBBB8;
extern Bank_801C009C *lbl_803EBBBC;

void fn_801BFFA8(void)
{
    lbl_803EBBB4 = -1;
    lbl_803EBBB6 = -1;
    lbl_803EBBB8 = -1;
    lbl_803EBBBC = 0;
}

void fn_801BFFC4(Bank_801C009C *bank, unsigned short group, unsigned short sample, unsigned short index)
{
    lbl_803EBBB4 = group;
    lbl_803EBBB6 = sample;
    lbl_803EBBB8 = index;
    lbl_803EBBBC = bank;
}

Group_801BFFD8 *fn_801BFFD8(Bank_801C009C *bank, unsigned short id)
{
    unsigned short i;

    for (i = 0; i < bank->mGroupCount; i++) {
        Group_801BFFD8 *group = &bank->mGroups[i];
        if (group->mId == id)
            return group;
    }
    return 0;
}

Group_801C001C *fn_801C001C(Bank_801C009C *bank, unsigned short id, unsigned short subId)
{
    Group_801BFFD8 *group = fn_801BFFD8(bank, id);
    unsigned short i;

    if (group == 0)
        return 0;
    for (i = 0; i < group->mCount; i++) {
        Group_801C001C *child = &group->mChildren[i];
        if (child->mId == subId)
            return child;
    }
    return 0;
}

Sample_801C009C *fn_801C009C(Bank_801C009C *bank, unsigned short id, unsigned short subId,
                             unsigned short index)
{
    Group_801C001C *group = fn_801C001C(bank, id, subId);

    if (group != 0 && index < group->mCount && group->mSamples != 0)
        return &group->mSamples[index];
    return 0;
}

Sample_801C009C *fn_801C00F8(Bank_801C009C *bank)
{
    unsigned short i;
    unsigned short j;

    fn_801BFFA8();
    if (bank->mGroupCount == 0)
        return 0;
    for (i = 0; i < bank->mGroupCount; i++) {
        Group_801BFFD8 *group = &bank->mGroups[i];
        for (j = 0; j < group->mCount; j++) {
            Group_801C001C *child = &group->mChildren[j];
            if (child->mCount != 0) {
                fn_801BFFC4(bank, i, j, j);
                return child->mSamples;
            }
        }
    }
    return 0;
}

int fn_801C01B8(Frame_801C029C *frame)
{
    return frame->mUnknownE & 0x7FFF;
}

int fn_801C01C4(Frame_801C029C *frame)
{
    if (frame->mUnknownE & 0x8000)
        return 1;
    return 0;
}
