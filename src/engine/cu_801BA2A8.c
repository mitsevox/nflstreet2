#include "engine/cu_801B9F00.h"
#include "engine/cu_801BA818.h"

float fn_80260260(float x, float y);
int fn_801BA720(Record_800D81C8 *pChannel, Anim_801BAB34 *pAnim, void *pUser);

int fn_801BA2A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, unsigned short slot, int anim, int state,
                void *pUser, float weight)
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

void fn_801BA360(Record_800D81C8 *pChannel, int type, float a, void *pSource, float b)
{
    fn_801BF3C8(&pChannel->mUnknown30, type, a, pSource, b);
}

void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index)
{
    pChannels[index].mUnknown1 = 0;
}

void fn_801BA398(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state)
{
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 != 0 && pChannels[i].mUnknown8 == state)
            fn_801BA384(pList, pChannels, i);
    }
}

void fn_801BA418(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index, unsigned short slot, int anim,
                 unsigned short state, void *pUser)
{
    float length;
    float time;
    int result;

    if (pChannels[index].mUnknown1 == 2) {
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
            pChannels[index].mUnknown1 = result;
    }
}

unsigned short fn_801BA568(Object_801BA03C *pList, Record_800D81C8 *pChannels, unsigned short state)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 2 && pChannels[i].mUnknown8 == state)
            count++;
    }
    return count;
}

unsigned short fn_801BA5A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, unsigned short state, int index)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 2 && pChannels[i].mUnknown8 == state) {
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

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 2 && pChannels[i].mUnknown8 == state)
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
    return pChannel->mUnknown7 & 1;
}

void fn_801BA6BC(Record_800D81C8 *pChannel, int enable)
{
    int changed;

    if (enable == 1) {
        changed = !(pChannel->mUnknown7 & 1);
        pChannel->mUnknown7 |= 1;
    } else {
        changed = pChannel->mUnknown7 & 1;
        pChannel->mUnknown7 &= ~1;
    }
    if (changed) {
        if (pChannel->mUnknown7 & 0x10)
            pChannel->mUnknown7 = (pChannel->mUnknown7 & ~0x10) | 0x20;
        else if (pChannel->mUnknown7 & 0x20)
            pChannel->mUnknown7 = (pChannel->mUnknown7 & ~0x20) | 0x10;
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
    pChannel->mUnknown7 = pAnim->mUnknown2;
    return result;
}

void fn_801BA784(Record_800D81C8 *pDest, Record_800D81C8 *pSource)
{
    *pDest = *pSource;
    pDest->mUnknown4C.mpUnknown0 = fn_801BAB34(fn_801BC084(pSource->mUnknown6), pSource->mUnknown2);
}
