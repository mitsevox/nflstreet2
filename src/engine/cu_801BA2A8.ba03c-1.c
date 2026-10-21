#include "engine/cu_801BA03C.ba03c-1.h"

int fn_801B9F00(Object_801BA03C *pList, Record_800D81C8 *pChannels);
int fn_801BA154(Object_801BA03C *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef);
void fn_801BF3C8(Block_801BF3C8 *pWeight, int a, int b, float x, float y);

int fn_801BA2A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser)
{
    return fn_801BA154(pList, pChannels, slot, anim, weight, state, pUser, 0xFFFF);
}

int fn_801BA2D0(Object_801BA03C *pList, Record_800D81C8 *pChannels, Record_800D81C8 *pSource)
{
    int index = fn_801B9F00(pList, pChannels);

    if (index != -1)
        pChannels[index] = *pSource;
    return index;
}

void fn_801BA360(Record_800D81C8 *pChannel, int a, int b, float x, float y)
{
    fn_801BF3C8(&pChannel->mUnknown30, a, b, x, y);
}

void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index)
{
    pChannels[index].mStatus = 0;
}

void fn_801BA398(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state)
{
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus != 0 && pChannels[i].mUnknown8 == state)
            fn_801BA384(pList, pChannels, i);
    }
}
