/*
 * Animation channels: the fixed set of 0x7C-byte channel records an animated object blends.
 * Finds a free channel (or the weakest blending one) for a new animation, starts animations
 * per state, stops, counts and delays channels by state, and steps each channel's sequence
 * and weight every frame.
 */
#include "engine/animchan.h"
#include "engine/animemot.h"

float fn_80260260(float x, float y);
void AnimChanSetWeightFunction(AnimChannel_t *pChannel, int type, float a, void *pSource, float b);
int AnimChanStart(AnimChannel_t *pChannel, AnimScript_t *pAnim, void *pUser);

int _AnimChanFindChannel(AnimHeader_t *pList, AnimChannel_t *pChannels)
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
    AnimChanStopAnim(pList, pChannels, selected);
    return selected;
}

void AnimChanInitChannels(AnimHeader_t *pList, AnimChannel_t *pChannels)
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

void AnimChanProcess(AnimHeader_t *pList, AnimChannel_t *pChannels, float time, void *pUser)
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
                if (pChannels[i].mUnknown1 != 0 && AnimChanGrow(&pChannels[i], time, pUser) == 1)
                    pChannels[i].mUnknown1 = 1;
            }
        }
    }
}

int AnimChanStartAnimPerState(AnimHeader_t *pList, AnimChannel_t *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef)
{
    int index = _AnimChanFindChannel(pList, pChannels);

    if (index != -1) {
        AnimChanSetWeightFunction(&pChannels[index], 0, weight, 0, weight);
        pChannels[index].mUnknown4 = AnimFileGetFileNum(AnimFileGetPtrFromSlot(slot));
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        pChannels[index].mUnknown8 = state;
        // FAKEMATCH: stateRef != 0xFFFF written as a sum so the else arm stores stateRef, not a folded -1
        if (stateRef + 1 != 0x10000)
            pChannels[index].mUnknownA = AnimFileGetStateRef(AnimFileGetPtrFromSlot(pChannels[index].mUnknown6), stateRef);
        else if (!(state & 0x8000))
            pChannels[index].mUnknownA = AnimFileGetStateRef(AnimFileGetPtrFromSlot(pChannels[index].mUnknown6), state);
        else
            pChannels[index].mUnknownA = stateRef;
        pChannels[index].mUnknownC = pList->mUnknown8;
        pChannels[index].mUnknown1C = 0;
        pChannels[index].mUnknown24.mUnknown4 = 0.0f;
        pChannels[index].mUnknown24.mUnknown0 = 0.0f;
        pChannels[index].mUnknown2C = 1.0f;
        pChannels[index].mUnknown20 = 0x01000000;
        pChannels[index].mUnknown48 = 0.0f;
        if (AnimChanStart(&pChannels[index], AnimFileGetAnimation(AnimFileGetPtrFromSlot(slot), anim), pUser) == 0)
            pChannels[index].mUnknown1 = 2;
    }
    return index;
}

int AnimChanStartAnim(AnimHeader_t *pList, AnimChannel_t *pChannels, unsigned short slot, int anim, int state,
                void *pUser, float weight)
{
    return AnimChanStartAnimPerState(pList, pChannels, slot, anim, weight, state, pUser, 0xFFFF);
}

int AnimChanStartCopy(AnimHeader_t *pList, AnimChannel_t *pChannels, AnimChannel_t *pSource)
{
    int index = _AnimChanFindChannel(pList, pChannels);

    if (index != -1)
        pChannels[index] = *pSource;
    return index;
}

void AnimChanSetWeightFunction(AnimChannel_t *pChannel, int type, float a, void *pSource, float b)
{
    AnimWgtSet(&pChannel->mUnknown30, type, a, pSource, b);
}

void AnimChanStopAnim(AnimHeader_t *pList, AnimChannel_t *pChannels, int index)
{
    pChannels[index].mUnknown1 = 0;
}

void AnimChanStopByStateIndex(AnimHeader_t *pList, AnimChannel_t *pChannels, int state)
{
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 != 0 && pChannels[i].mUnknown8 == state)
            AnimChanStopAnim(pList, pChannels, i);
    }
}

void AnimChanSwitchAnim(AnimHeader_t *pList, AnimChannel_t *pChannels, int index, unsigned short slot, int anim,
                 unsigned short state, void *pUser)
{
    float length;
    float time;
    int result;

    if (pChannels[index].mUnknown1 == 2) {
        pChannels[index].mUnknown4 = AnimFileGetFileNum(AnimFileGetPtrFromSlot(slot));
        pChannels[index].mUnknown8 = state;
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        if (pChannels[index].mUnknown4C.mUnknown1A == 0xFFFF)
            pChannels[index].mUnknown4C.mUnknown1A = AnimSeqGetNumFrames(pChannels[index].mUnknown4C.mpUnknown0);
        length = pChannels[index].mUnknown4C.mUnknown4 * (unsigned int)pChannels[index].mUnknown4C.mUnknown1A;
        time = fn_80260260(pChannels[index].mUnknown4C.mUnknown8, length);
        result = AnimChanStart(&pChannels[index], AnimFileGetAnimation(AnimFileGetPtrFromSlot(slot), anim), pUser);
        if (result != 1) {
            pChannels[index].mUnknown4C.mUnknown1A = AnimSeqGetNumFrames(pChannels[index].mUnknown4C.mpUnknown0);
            AnimSeqSetRate(&pChannels[index].mUnknown4C, length / (unsigned int)pChannels[index].mUnknown4C.mUnknown1A);
            result = AnimChanGrow(&pChannels[index], time, pUser);
        }
        if (result == 1)
            pChannels[index].mUnknown1 = result;
    }
}

unsigned short AnimChanGetNumActiveByState(AnimHeader_t *pList, AnimChannel_t *pChannels, unsigned short state)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 2 && pChannels[i].mUnknown8 == state)
            count++;
    }
    return count;
}

unsigned short AnimChanGetStateChannelByIndex(AnimHeader_t *pList, AnimChannel_t *pChannels, unsigned short state, int index)
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

void AnimChanSetDelayByState(AnimHeader_t *pList, AnimChannel_t *pChannels, int state, float delay)
{
    int i;

    for (i = 0; i < pList->mUnknown4; i++) {
        if (pChannels[i].mUnknown1 == 2 && pChannels[i].mUnknown8 == state)
            pChannels[i].mUnknown48 = delay;
    }
}

int AnimChanGrow(AnimChannel_t *pChannel, float time, void *pUser)
{
    int result;

    _AnimUserCallbackPushInfo(pUser);
    _AnimUserCallbackPushState(pChannel->mUnknown8);
    result = AnimSeqGrow(&pChannel->mUnknown4C, time);
    _AnimUserCallbackPopState();
    _AnimUserCallbackPopInfo();
    return result;
}

int AnimChanIsMirrored(AnimChannel_t *pChannel)
{
    return pChannel->mUnknown7 & 1;
}

void AnimChanSetMirrored(AnimChannel_t *pChannel, int enable)
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

int AnimChanStart(AnimChannel_t *pChannel, AnimScript_t *pAnim, void *pUser)
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

void AnimChanCopyChannel(AnimChannel_t *pDest, AnimChannel_t *pSource)
{
    *pDest = *pSource;
    pDest->mUnknown4C.mpUnknown0 = AnimFileGetAnimation(AnimFileGetPtrFromSlot(pSource->mUnknown6), pSource->mUnknown2);
}
