/*
 * Animation channels: the fixed set of 0x7C-byte channel records an animated object blends.
 * Finds a free channel (or the weakest blending one) for a new animation, starts animations
 * per state, stops, counts and delays channels by state, and steps each channel's sequence
 * and weight every frame.
 */
#include "engine/cu_801B9F00.h"
#include "engine/animemot.h"

float fn_80260260(float x, float y);
void fn_801BA360(Record_800D81C8 *pChannel, int type, float a, void *pSource, float b);
int fn_801BA720(Record_800D81C8 *pChannel, AnimScript_t *pAnim, void *pUser);

int fn_801B9F00(AnimHeader_t *pList, Record_800D81C8 *pChannels)
{
    unsigned char pass;
    int i;
    float best;
    int selected;

    for (pass = 0; pass <= 1; pass++) {
        for (i = 0; i < pList->mUnknown4; i++) {
            if (pChannels[i].mUnknown1 == pass)
                return i;
        }
    }
    best = 1.0f;
    selected = -1;
    for (i = 0; i < pList->mUnknown4; i++) {
        if ((pChannels[i].mUnknown8 & 0x8000) && pChannels[i].mUnknown30.mUnknown0 <= best) {
            best = pChannels[i].mUnknown30.mUnknown0;
            selected = i;
        }
    }
    if (selected == -1)
        return -1;
    fn_801BA384(pList, pChannels, selected);
    return selected;
}

void fn_801B9FEC(AnimHeader_t *pList, Record_800D81C8 *pChannels)
{
    unsigned char state = 4;
    int i;

    if (pList->mUnknown0 == 0)
        state = 1;
    for (i = 0; i < pList->mUnknown4; i++) {
        pChannels[i].mUnknown0 = state;
        pChannels[i].mUnknown1 = 0;
        pChannels[i].mUnknown4C.mpUnknown0 = 0;
    }
}

void fn_801BA03C(AnimHeader_t *pList, Record_800D81C8 *pChannels, float time, void *pUser)
{
    int i;
    int active;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 1)
            pChannels[i].mUnknown1 = 0;
        if (pChannels[i].mUnknown1 != 0) {
            pChannels[i].mUnknown48 -= time;
            if (pChannels[i].mUnknown48 < 0.0f) {
                pChannels[i].mUnknown48 = 0.0f;
                active = pChannels[i].mUnknown30.mUnknown8;
                AnimWgtProcess(&pChannels[i].mUnknown30, time);
                if (pChannels[i].mUnknown30.mUnknown0 < 1e-7f && active != 0)
                    pChannels[i].mUnknown1 = 1;
                if (pChannels[i].mUnknown1 != 0 && fn_801BA650(&pChannels[i], time, pUser) == 1)
                    pChannels[i].mUnknown1 = 1;
            }
        }
    }
}

int fn_801BA154(AnimHeader_t *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef)
{
    int index = fn_801B9F00(pList, pChannels);

    if (index != -1) {
        fn_801BA360(&pChannels[index], 0, weight, 0, weight);
        pChannels[index].mUnknown4 = AnimFileGetFileNum(fn_801BC084(slot));
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        pChannels[index].mUnknown8 = state;
        if (stateRef != 0xFFFF)
            pChannels[index].mUnknownA = AnimFileGetStateRef(fn_801BC084(pChannels[index].mUnknown6), stateRef);
        else if (!(state & 0x8000))
            pChannels[index].mUnknownA = AnimFileGetStateRef(fn_801BC084(pChannels[index].mUnknown6), state);
        else
            pChannels[index].mUnknownA = stateRef;
        pChannels[index].mUnknownC = pList->mUnknown8;
        pChannels[index].mUnknown1C = 0;
        pChannels[index].mUnknown24.mUnknown4 = 0.0f;
        pChannels[index].mUnknown24.mUnknown0 = 0.0f;
        pChannels[index].mUnknown2C = 1.0f;
        pChannels[index].mUnknown20 = 0x01000000;
        pChannels[index].mUnknown48 = 0.0f;
        if (fn_801BA720(&pChannels[index], AnimFileGetAnimation(fn_801BC084(slot), anim), pUser) == 0)
            pChannels[index].mUnknown1 = 2;
    }
    return index;
}

int fn_801BA2A8(AnimHeader_t *pList, Record_800D81C8 *pChannels, unsigned short slot, int anim, int state,
                void *pUser, float weight)
{
    return fn_801BA154(pList, pChannels, slot, anim, weight, state, pUser, 0xFFFF);
}

int fn_801BA2D0(AnimHeader_t *pList, Record_800D81C8 *pChannels, Record_800D81C8 *pSource)
{
    int index = fn_801B9F00(pList, pChannels);

    if (index != -1)
        pChannels[index] = *pSource;
    return index;
}

void fn_801BA360(Record_800D81C8 *pChannel, int type, float a, void *pSource, float b)
{
    AnimWgtSet(&pChannel->mUnknown30, type, a, pSource, b);
}

void fn_801BA384(AnimHeader_t *pList, Record_800D81C8 *pChannels, int index)
{
    pChannels[index].mUnknown1 = 0;
}

void fn_801BA398(AnimHeader_t *pList, Record_800D81C8 *pChannels, int state)
{
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 != 0 && pChannels[i].mUnknown8 == state)
            fn_801BA384(pList, pChannels, i);
    }
}

void fn_801BA418(AnimHeader_t *pList, Record_800D81C8 *pChannels, int index, unsigned short slot, int anim,
                 unsigned short state, void *pUser)
{
    float length;
    float time;
    int result;

    if (pChannels[index].mUnknown1 == 2) {
        pChannels[index].mUnknown4 = AnimFileGetFileNum(fn_801BC084(slot));
        pChannels[index].mUnknown8 = state;
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        if (pChannels[index].mUnknown4C.mUnknown1A == 0xFFFF)
            pChannels[index].mUnknown4C.mUnknown1A = AnimSeqGetNumFrames(pChannels[index].mUnknown4C.mpUnknown0);
        length = pChannels[index].mUnknown4C.mUnknown4 * (unsigned int)pChannels[index].mUnknown4C.mUnknown1A;
        time = fn_80260260(pChannels[index].mUnknown4C.mUnknown8, length);
        result = fn_801BA720(&pChannels[index], AnimFileGetAnimation(fn_801BC084(slot), anim), pUser);
        if (result != 1) {
            pChannels[index].mUnknown4C.mUnknown1A = AnimSeqGetNumFrames(pChannels[index].mUnknown4C.mpUnknown0);
            AnimSeqSetRate(&pChannels[index].mUnknown4C, length / (unsigned int)pChannels[index].mUnknown4C.mUnknown1A);
            result = fn_801BA650(&pChannels[index], time, pUser);
        }
        if (result == 1)
            pChannels[index].mUnknown1 = result;
    }
}

unsigned short fn_801BA568(AnimHeader_t *pList, Record_800D81C8 *pChannels, unsigned short state)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 2 && pChannels[i].mUnknown8 == state)
            count++;
    }
    return count;
}

unsigned short fn_801BA5A8(AnimHeader_t *pList, Record_800D81C8 *pChannels, unsigned short state, int index)
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

void fn_801BA60C(AnimHeader_t *pList, Record_800D81C8 *pChannels, int state, float delay)
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

    _AnimUserCallbackPushInfo(pUser);
    _AnimUserCallbackPushState(pChannel->mUnknown8);
    result = AnimSeqGrow(&pChannel->mUnknown4C, time);
    _AnimUserCallbackPopState();
    _AnimUserCallbackPopInfo();
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

int fn_801BA720(Record_800D81C8 *pChannel, AnimScript_t *pAnim, void *pUser)
{
    int result;

    _AnimUserCallbackPushState(pChannel->mUnknown8);
    _AnimUserCallbackPushInfo(pUser);
    result = AnimSeqStart(&pChannel->mUnknown4C, pAnim);
    _AnimUserCallbackPopState();
    _AnimUserCallbackPopInfo();
    pChannel->mUnknown7 = pAnim->mUnknown2;
    return result;
}

void fn_801BA784(Record_800D81C8 *pDest, Record_800D81C8 *pSource)
{
    *pDest = *pSource;
    pDest->mUnknown4C.mpUnknown0 = AnimFileGetAnimation(fn_801BC084(pSource->mUnknown6), pSource->mUnknown2);
}
