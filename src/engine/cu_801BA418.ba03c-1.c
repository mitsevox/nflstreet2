#include "engine/cu_801BA03C.ba03c-1.h"

void fn_801B9D84(int state);
void fn_801B9DA8(void *pUser);
void fn_801B9DCC(void);
void fn_801B9DDC(void);
int fn_801BD4C0(Block_801BD6D4 *pSeq, Anim_801BAB34 *pAnim);
int fn_801BD4E4(Block_801BD6D4 *pSeq, float time);
unsigned short fn_801BD6DC(void *pSeq);
void fn_801BD710(Block_801BD6D4 *pSeq, float rate);
float fn_80260260(float x, float y);

void fn_801BA418(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index, int slot, int anim, int state,
                 void *pUser)
{
    float length;
    float time;
    int result;

    if (pChannels[index].mStatus == 2) {
        pChannels[index].mUnknown4 = fn_801BAB2C(fn_801BC084(slot));
        pChannels[index].mUnknown8 = state;
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        if (pChannels[index].mUnknown4C.mUnknown1A == 0xFFFF)
            pChannels[index].mUnknown4C.mUnknown1A = fn_801BD6DC(pChannels[index].mUnknown4C.mpUnknown0);
        length = pChannels[index].mUnknown4C.mUnknown4 * (unsigned int)pChannels[index].mUnknown4C.mUnknown1A;
        time = fn_80260260(pChannels[index].mUnknown4C.mUnknown8, length);
        result = fn_801BA720(&pChannels[index], fn_801BAB34(fn_801BC084(slot), anim), pUser);
        if (result != 1) {
            pChannels[index].mUnknown4C.mUnknown1A = fn_801BD6DC(pChannels[index].mUnknown4C.mpUnknown0);
            fn_801BD710(&pChannels[index].mUnknown4C, length / (unsigned int)pChannels[index].mUnknown4C.mUnknown1A);
            result = fn_801BA650(&pChannels[index], time, pUser);
        }
        if (result == 1)
            pChannels[index].mStatus = result;
    }
}

unsigned short fn_801BA568(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 2 && pChannels[i].mUnknown8 == state)
            count++;
    }
    return count;
}

unsigned short fn_801BA5A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state, int index)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 2 && pChannels[i].mUnknown8 == state) {
            if (count == index)
                return i;
            count++;
        }
    }
    return 0xFFFF;
}

void fn_801BA60C(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state, float delay)
{
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 2 && pChannels[i].mUnknown8 == state)
            pChannels[i].mUnknown48 = delay;
    }
}

int fn_801BA650(Record_800D81C8 *pChannel, float time, void *pUser)
{
    int result;

    fn_801B9DA8(pUser);
    fn_801B9D84(pChannel->mUnknown8);
    result = fn_801BD4E4(&pChannel->mUnknown4C, time);
    fn_801B9DCC();
    fn_801B9DDC();
    return result;
}

int fn_801BA6B0(Record_800D81C8 *pChannel)
{
    return pChannel->mFlags & 1;
}

void fn_801BA6BC(Record_800D81C8 *pChannel, int enable)
{
    int changed;

    if (enable == 1) {
        changed = !(pChannel->mFlags & 1);
        pChannel->mFlags |= 1;
    } else {
        changed = pChannel->mFlags & 1;
        pChannel->mFlags &= ~1;
    }
    if (changed) {
        if (pChannel->mFlags & 0x10)
            pChannel->mFlags = (pChannel->mFlags & ~0x10) | 0x20;
        else if (pChannel->mFlags & 0x20)
            pChannel->mFlags = (pChannel->mFlags & ~0x20) | 0x10;
    }
}

int fn_801BA720(Record_800D81C8 *pChannel, Anim_801BAB34 *pAnim, void *pUser)
{
    int result;

    fn_801B9D84(pChannel->mUnknown8);
    fn_801B9DA8(pUser);
    result = fn_801BD4C0(&pChannel->mUnknown4C, pAnim);
    fn_801B9DCC();
    fn_801B9DDC();
    pChannel->mFlags = pAnim->mUnknown2;
    return result;
}

void fn_801BA784(Record_800D81C8 *pDest, Record_800D81C8 *pSource)
{
    *pDest = *pSource;
    pDest->mUnknown4C.mpUnknown0 = fn_801BAB34(fn_801BC084(pSource->mUnknown6), pSource->mUnknown2);
}
