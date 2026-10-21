#include "engine/cu_801BA03C.ba03c-1.h"

int fn_801B9F00(Object_801BA03C *pList, Record_800D81C8 *pChannels);
void fn_801BF3C8(Block_801BF3C8 *pWeight, int a, int b, float x, float y);
void fn_801BF46C(Block_801BF3C8 *pWeight, float time);

void fn_801BA03C(Object_801BA03C *pList, Record_800D81C8 *pChannels, float time, void *pUser)
{
    int i;
    int active;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 1)
            pChannels[i].mStatus = 0;
        if (pChannels[i].mStatus != 0) {
            pChannels[i].mUnknown48 -= time;
            if (!(pChannels[i].mUnknown48 >= 0.0f)) {
                pChannels[i].mUnknown48 = 0.0f;
                active = pChannels[i].mUnknown30.mUnknown8;
                fn_801BF46C(&pChannels[i].mUnknown30, time);
                if (!(pChannels[i].mUnknown30.mWeight >= 1e-7f) && active != 0)
                    pChannels[i].mStatus = 1;
                if (pChannels[i].mStatus != 0 && fn_801BA650(&pChannels[i], time, pUser) == 1)
                    pChannels[i].mStatus = 1;
            }
        }
    }
}

int fn_801BA154(Object_801BA03C *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef)
{
    int index = fn_801B9F00(pList, pChannels);

    if (index != -1) {
        fn_801BA360(&pChannels[index], 0, 0, weight, weight);
        pChannels[index].mUnknown4 = fn_801BAB2C(fn_801BC084(slot));
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        pChannels[index].mUnknown8 = state;
        if (stateRef != 0xFFFF)
            pChannels[index].mUnknownA = fn_801BAB48(fn_801BC084(pChannels[index].mUnknown6), stateRef);
        else if (!(state & 0x8000))
            pChannels[index].mUnknownA = fn_801BAB48(fn_801BC084(pChannels[index].mUnknown6), state);
        else
            pChannels[index].mUnknownA = stateRef;
        pChannels[index].mUnknownC = pList->mUnknown8;
        pChannels[index].mUnknown1C = 0;
        pChannels[index].mUnknown20 = 0x1000000;
        pChannels[index].mUnknown24 = 0.0f;
        pChannels[index].mUnknown28 = 0.0f;
        pChannels[index].mUnknown48 = 0.0f;
        pChannels[index].mUnknown2C = 1.0f;
        if (fn_801BA720(&pChannels[index], fn_801BAB34(fn_801BC084(slot), anim), pUser) == 0)
            pChannels[index].mStatus = 2;
    }
    return index;
}

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
