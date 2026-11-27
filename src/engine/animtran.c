/* Animation state transitions: when an object changes animation state, picks the transition rule
   between the outgoing and incoming animations and cross-fades, cuts or plays a transition clip. */
#include "engine/animst.h"

void _AnimTranSetTransOutWgt(AnimStInfo_t *p, unsigned short key, int frames);
AnimTranInfo_t *_AnimTranGetBestTransition(AnimStateTransList_t *pTable, AnimHeader_t *pObject, AnimChannel_t *pRecords,
                                 unsigned short fromAnim, unsigned short fromFileNum, unsigned short fromReadPos,
                                 unsigned short state, unsigned short toAnim, unsigned short toFileNum);

int _AnimTranGetStateTransitions(unsigned short type, unsigned short key)
{
    AnimFileGetTransList(type, key, &lbl_803D4F50);
    return lbl_803D4F50.mCount;
}

unsigned int _AnimTranFindBestChannel(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, unsigned short key)
{
    float highest = 0.0f;
    unsigned int best = 0xFFFF;
    unsigned int count = AnimChanGetNumActiveByState(pObject, pRecords, key);
    unsigned short i;

    for (i = 0; i < count; i++) {
        unsigned int index = AnimChanGetStateChannelByIndex(pObject, pRecords, key, i);

        if (highest < pRecords[index].mUnknown30.mUnknown0) {
            highest = pRecords[index].mUnknown30.mUnknown0;
            best = index;
        }
    }
    return best;
}

void _AnimTranSetTransOutWgt(AnimStInfo_t *p, unsigned short key, int frames)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown0 == key
            || ((p->mUnknown4[i].mUnknown0 & 0x8000) && p->mUnknown4[i].mUnknown0 != 0xFFFF)) {
            AnimWgtSetLinear(&p->mUnknown4[i].mUnknown4C, frames, -1.0f, 0.0f);
        }
    }
}

static inline int _AnimTranPlayTransitionAnim(AnimStInfo_t *p, int i, AnimHeader_t *pObject, AnimChannel_t *pRecords,
                                              unsigned short key, AnimTranInfo_t *pTransition, void *pOwner)
{
    int file;
    int index;
    int result;

    p->mUnknown4[i].mUnknown6 = AnimFileGetTransitionStateFromObjType(pObject->mUnknown2);
    file = AnimFileGetSlotFromFileNum(pObject->mUnknown2, pTransition->mUnknownC);
    if (file != 0xFFFFFF &&
        (index = AnimChanStartAnimPerState(pObject, pRecords, (unsigned short)file, pTransition->mUnknownE, 1.0f, 0xFFFF,
                                           pOwner, p->mUnknown4[i].mUnknown6)) != -1) {
        float duration = AnimSeqGetLife(pRecords[index].mUnknown4C.mpUnknown0);
        unsigned int fade = duration * (1.0f - pTransition->mUnknown8) * 0.5f;
        unsigned int hold = (unsigned int)duration - fade * 2;

        AnimWgtSetLinear(&p->mUnknown4[i].mUnknown4C, fade, -1.0f, 0.0f);
        AnimWgtSetLinearInAndOut(&p->mUnknown4[i + 1].mUnknown4C, fade, hold, -1.0f, 1.0f);
        AnimWgtSetLinear(&p->mUnknown4[i + 2].mUnknown4C, fade, 0.0f, p->mUnknown4[i + 2].mUnknown4C.mUnknown4);
        duration = (float)hold + (float)fade;
        AnimStSetStateDelay(p, key, duration);
        AnimChanSetDelayByState(pObject, pRecords, key, duration);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void _AnimTranDoTransition(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, unsigned short key,
                 unsigned short previous, int state, void *pOwner)
{
    AnimStateTransList_t *pTable = &lbl_803D4F50;
    int fallback = 1;
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown0 == 0xFFFF) {
            p->mUnknown4[i].mUnknown6 = AnimFileGetTransitionStateFromObjType(pObject->mUnknown2);
            continue;
        }
        if (p->mUnknown4[i].mUnknown2 != state) {
            continue;
        }
        p->mUnknown4[i].mUnknown2 = 1;
        if (pTable->mState != previous) {
            _AnimTranGetStateTransitions(pObject->mUnknown2, previous);
        }
        if (pTable->mCount != 0) {
            unsigned short slotKey = p->mUnknown4[i].mUnknown0;
            unsigned int from = _AnimTranFindBestChannel(p, pObject, pRecords, slotKey);
            unsigned int to = _AnimTranFindBestChannel(p, pObject, pRecords, key);

            if (from != 0xFFFF && to != 0xFFFF) {
                AnimTranInfo_t *pTransition;

                pTransition = _AnimTranGetBestTransition(pTable, pObject, pRecords, pRecords[from].mUnknown2, pRecords[from].mUnknown4,
                                          pRecords[from].mUnknown4C.mUnknown18, key, pRecords[to].mUnknown2,
                                          pRecords[to].mUnknown4);
                if (pTransition == 0) {
                    pTransition = _AnimTranGetBestTransition(pTable, pObject, pRecords, pRecords[from].mUnknown2,
                                              pRecords[from].mUnknown4, pRecords[from].mUnknown4C.mUnknown18, key,
                                              0xFFFF, 0);
                }
                if (pTransition == 0) {
                    pTransition = _AnimTranGetBestTransition(pTable, pObject, pRecords, 0xFFFF, 0, 0, key, pRecords[to].mUnknown2,
                                              pRecords[to].mUnknown4);
                }
                if (pTransition == 0) {
                    pTransition = _AnimTranGetBestTransition(pTable, pObject, pRecords, 0xFFFF, 0, 0, key, 0xFFFF, 0);
                }
                if (pTransition != 0) {
                    switch (pTransition->mUnknown4) {
                    case 0:
                        AnimWgtSet(&p->mUnknown4[i].mUnknown4C, 0, 0.0f, 0, 0.0f);
                        fallback = 0;
                        break;
                    case 1: {
                        float frames = pTransition->mUnknown6 * pRecords[from].mUnknown4C.mUnknown4 *
                                           (1.0f - pTransition->mUnknown8) +
                                       pTransition->mUnknown6 * pRecords[to].mUnknown4C.mUnknown4 * pTransition->mUnknown8;

                        _AnimTranSetTransOutWgt(p, slotKey, (unsigned int)frames);
                        AnimWgtSetLinear(&p->mUnknown4[i + 2].mUnknown4C, (unsigned int)frames, 0.0f,
                                    p->mUnknown4[i + 2].mUnknown4C.mUnknown4);
                        fallback = 0;
                        break;
                    }
                    case 2:
                        AnimWgtSet(&p->mUnknown4[i].mUnknown4C, 0, 0.0f, 0, 0.0f);
                        fallback = 0;
                        break;
                    case 3:
                        fallback = _AnimTranPlayTransitionAnim(p, i, pObject, pRecords, key, pTransition, pOwner);
                        break;
                    }
                }
            }
        }
        if (fallback == 1) {
            AnimWgtSetLinear(&p->mUnknown4[i].mUnknown4C, 10, -1.0f, 0.0f);
        }
    }
}

AnimTranInfo_t *_AnimTranGetBestTransition(AnimStateTransList_t *pTable, AnimHeader_t *pObject, AnimChannel_t *pRecords,
                                 unsigned short fromAnim, unsigned short fromFileNum, unsigned short fromReadPos,
                                 unsigned short state, unsigned short toAnim, unsigned short toFileNum)
{
    AnimTranInfo_t *pResult = 0;
    unsigned short key;
    int i;

    if (toAnim != 0xFFFF) {
        key = toFileNum | 0x8000;
    } else {
        key = 0xFFFF;
        toAnim = state;
    }
    for (i = 0; i < pTable->mCount; i++) {
        AnimFileStateTrans_t *pGroup = pTable->mEntries[i].mpUnknown4;
        int j;

        for (j = 0; j < pGroup->mCount; j++) {
            if ((pGroup->mEntries[j].mUnknown0 == key || (key == 0xFFFF && !(pGroup->mEntries[j].mUnknown0 & 0x8000))) &&
                pGroup->mEntries[j].mUnknown2 == toAnim && pGroup->mEntries[j].mUnknown4 == fromAnim &&
                (fromAnim == 0xFFFF ||
                 (fromReadPos >= pGroup->mEntries[j].mUnknown6 && fromReadPos <= pGroup->mEntries[j].mUnknown8))) {
                pResult = pGroup->mEntries[j].mpUnknownC;
            }
        }
    }
    return pResult;
}
