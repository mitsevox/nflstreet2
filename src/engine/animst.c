/* Animation state slots: each animated object keeps up to four animation states (the current
   one and those fading out), started, weighted, delayed and ended here, with per-object-type
   handlers choosing the animation for each state event. */
#include <string.h>
#include "engine/animst.h"
#include "engine/SysSetLastErrorFunc.h"
#include "game/fn_801D2B7C.h"

extern AnimStStateDefs_t **lbl_803EBB98;
static AnimStateAnimList_t _AnimSt_pStatAnimList;
static int _AnimSt_NumObjTypes;

int _AnimStCallSelectAnimFunc(unsigned short type, unsigned short key, void *pOwner, int event, AnimHeader_t *pObject,
                AnimChannel_t *pRecords)
{
    if (key & 0x8000) {
        return 0;
    }
    AnimFileGetStateAnimList(type, key, &_AnimSt_pStatAnimList);
    return lbl_803EBB98[type]->mpUnknown4[key](&_AnimSt_pStatAnimList, key, pObject, pRecords, pOwner, event);
}

void _AnimStOrganizeInfo(AnimStInfo_t *p)
{
    int count;
    int i;
    int j;

    for (count = 3; count >= 0; count--) {
        if (p->mUnknown4[count].mUnknown2 != 0) {
            break;
        }
    }
    if (count > 0) {
        i = 0;
        while (i < count) {
            if (p->mUnknown4[i].mUnknown2 == 0) {
                // FAKEMATCH: always true inside while (i < count); present only so the compiler emits the target's second i/count test before the inner loop.
                if (i != count) {
                    for (j = i; j < count; j++) {
                        *(p->mUnknown4 + j) = *(p->mUnknown4 + j + 1);
                        p->mUnknown4[j + 1].mUnknown2 = 0;
                        p->mUnknown4[j + 1].mUnknown8 = 0.0f;
                    }
                }
                count--;
            } else {
                i++;
            }
        }
    }
}

void _AnimStEndState(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, int index,
                 void *pOwner)
{
    _AnimStCallSelectAnimFunc(pObject->mUnknown2, p->mUnknown4[index].mUnknown0, pOwner, 3, pObject, pRecords);
    AnimChanStopByStateIndex(pObject, pRecords, p->mUnknown4[index].mUnknown0);
    p->mUnknown4[index].mUnknown2 = 0;
}

unsigned short _AnimStGetFreeSlotIndex(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, void *pOwner,
                           unsigned short key)
{
    int slot = -1;
    int freed = 0;
    int i;

    _AnimStOrganizeInfo(p);
    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 == 0) {
            slot = i;
            break;
        }
    }
    if (i == 4) {
        for (i = 0; i < 4; i++) {
            if (p->mUnknown4[i].mUnknown8 != 0.0f) {
                _AnimStEndState(p, pObject, pRecords, i, pOwner);
                freed = 1;
                _AnimStOrganizeInfo(p);
                break;
            }
        }
        if (!freed) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown4C.mUnknown0 <= 1e-07f && (p->mUnknown4[i].mUnknown0 & 0x8000) &&
                    p->mUnknown4[i].mUnknown0 != 0xFFFF && AnimChanGetNumActiveByState(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    _AnimStEndState(p, pObject, pRecords, i, pOwner);
                    freed = 1;
                    _AnimStOrganizeInfo(p);
                    break;
                }
            }
        }
        if (!freed) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown0 != 0xFFFF &&
                    AnimChanGetNumActiveByState(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    _AnimStEndState(p, pObject, pRecords, i, pOwner);
                    freed = 1;
                    _AnimStOrganizeInfo(p);
                    break;
                }
            }
        }
        if (!freed) {
            float lowest = 1.1f;
            int index = -1;

            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown0 != 0xFFFF &&
                    p->mUnknown4[i].mUnknown4C.mUnknown0 < lowest) {
                    lowest = p->mUnknown4[i].mUnknown4C.mUnknown0;
                    index = i;
                }
            }
            if (index != -1) {
                _AnimStEndState(p, pObject, pRecords, index, pOwner);
                freed = 1;
                _AnimStOrganizeInfo(p);
            }
        }
        if (freed == 1) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 0) {
                    slot = i;
                    break;
                }
            }
        }
    }
    if (slot == -1) {
        slot = 3;
        _AnimStEndState(p, pObject, pRecords, 0, pOwner);
        _AnimStOrganizeInfo(p);
    }
    return slot;
}

unsigned short _AnimStMakeUniqueTransitionState(AnimStInfo_t *p)
{
    unsigned short key = 0xFFFE;
    int unique;
    int i;

    do {
        unique = 1;
        for (i = 0; i < 4; i++) {
            if (p->mUnknown4[i].mUnknown0 == key) {
                key--;
                unique = 0;
                break;
            }
        }
    } while (!unique);
    return key;
}

int fn_801BDF90(int count)
{
    int result;

    lbl_803EBB98 = fn_801D2B7C(count * 4, 0, 0);
    result = SysGetLastError();
    _AnimSt_NumObjTypes = count;
    if (lbl_803EBB98 != 0) {
        memset(lbl_803EBB98, 0, count * 4);
    }
    return result;
}

int fn_801BDFF8(void)
{
    if (lbl_803EBB98 != 0) {
        fn_801D2BD0(lbl_803EBB98);
        lbl_803EBB98 = 0;
    }
    return 0;
}

void fn_801BE030(int type, AnimStStateDefs_t *pHandlers)
{
    lbl_803EBB98[type] = pHandlers;
}

void AnimStInitStructure(AnimStInfo_t *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        p->mUnknown4[i].mUnknown0 = 0;
        p->mUnknown4[i].mUnknown6 = -16;
        p->mUnknown4[i].mUnknown2 = 0;
    }
}

int fn_801BE068(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, unsigned short key,
                float frames, void *pOwner)
{
    unsigned short previous = fn_801BE648(p);
    unsigned short slot;
    int add;
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 == 3) {
            p->mUnknown4[i].mUnknown2 = 2;
            _AnimStCallSelectAnimFunc(pObject->mUnknown2, previous, pOwner, 4, pObject, pRecords);
            if (p->mUnknown4[i].mUnknown8 != 0.0f && i > 0) {
                _AnimStEndState(p, pObject, pRecords, i, pOwner);
                i--;
                if (p->mUnknown4[i].mUnknown0 == 0xFFFF) {
                    p->mUnknown4[i].mUnknown0 = _AnimStMakeUniqueTransitionState(p);
                    AnimWgtSetLinear(&p->mUnknown4[i].mUnknown4C, 10, -1.0f, 0.0f);
                    while (AnimChanGetNumActiveByState(pObject, pRecords, 0xFFFF)) {
                        pRecords[AnimChanGetStateChannelByIndex(pObject, pRecords, 0xFFFF, 0)].mUnknown8 = p->mUnknown4[i].mUnknown0;
                    }
                }
            }
            break;
        }
    }
    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0) {
            unsigned short old = p->mUnknown4[i].mUnknown0;

            if (old == key || old == 0xFFFF) {
                p->mUnknown4[i].mUnknown0 = _AnimStMakeUniqueTransitionState(p);
                p->mUnknown4[i].mUnknown4 &= ~1;
                while (AnimChanGetNumActiveByState(pObject, pRecords, old)) {
                    pRecords[AnimChanGetStateChannelByIndex(pObject, pRecords, old, 0)].mUnknown8 = p->mUnknown4[i].mUnknown0;
                }
            }
        }
    }
    add = 0;
    if (_AnimTranGetStateTransitions(pObject->mUnknown2, previous)) {
        add = 1;
    }
    if (add == 1) {
        slot = _AnimStGetFreeSlotIndex(p, pObject, pRecords, pOwner, 0xFFFF);
        memset(&p->mUnknown4[slot], 0, sizeof(AnimStSlot_t));
        p->mUnknown4[slot].mUnknown0 = 0xFFFF;
        p->mUnknown4[slot].mUnknown2 = add;
        p->mUnknown4[slot].mUnknown8 = 0.0f;
        AnimWgtSet(&p->mUnknown4[slot].mUnknown4C, 0, 0.0f, 0, 0.0f);
    }
    slot = _AnimStGetFreeSlotIndex(p, pObject, pRecords, pOwner, key);
    memset(&p->mUnknown4[slot], 0, sizeof(AnimStSlot_t));
    p->mUnknown4[slot].mUnknown2 = 3;
    p->mUnknown4[slot].mUnknown0 = key;
    p->mUnknown4[slot].mUnknown8 = 0.0f;
    AnimWgtSetLinear(&p->mUnknown4[slot].mUnknown4C, 10, 0.0f, frames);
    _AnimStCallSelectAnimFunc(pObject->mUnknown2, key, pOwner, 0, pObject, pRecords);
    _AnimTranDoTransition(p, pObject, pRecords, key, previous, 2, pOwner);
    return 0;
}

void fn_801BE3C0(AnimStInfo_t *p, float from, float to, unsigned short key, int type, void *pSource)
{
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown0 == key && p->mUnknown4[i].mUnknown2 == 3) {
            AnimWgtSet(&p->mUnknown4[i].mUnknown4C, type, from, pSource, to);
            break;
        }
    }
}

void fn_801BE420(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, void *pOwner, float step)
{
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 == 0) {
            break;
        }
        p->mUnknown4[i].mUnknown8 -= step;
        if (p->mUnknown4[i].mUnknown8 < 0.0f) {
            p->mUnknown4[i].mUnknown8 = 0.0f;
            AnimWgtProcess(&p->mUnknown4[i].mUnknown4C, step);
            if (p->mUnknown4[i].mUnknown4C.mUnknown0 > 1e-07f) {
                if (p->mUnknown4[i].mUnknown4 & 1) {
                    _AnimStCallSelectAnimFunc(pObject->mUnknown2, p->mUnknown4[i].mUnknown0, pOwner, 2, pObject, pRecords);
                }
                if (AnimChanGetNumActiveByState(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    if (p->mUnknown4[i].mUnknown2 == 3) {
                        _AnimStCallSelectAnimFunc(pObject->mUnknown2, p->mUnknown4[i].mUnknown0, pOwner, 1, pObject, pRecords);
                    } else {
                        _AnimStEndState(p, pObject, pRecords, i, pOwner);
                    }
                }
            } else {
                _AnimStEndState(p, pObject, pRecords, i, pOwner);
            }
        }
    }
    _AnimStOrganizeInfo(p);
}

AnimStSlot_t *AnimStGetStateSlot(AnimStInfo_t *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return &p->mUnknown4[i];
        }
    }
    return 0;
}

float AnimStGetStateWeight(AnimStInfo_t *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return p->mUnknown4[i].mUnknown4C.mUnknown0;
        }
    }
    return 0.0f;
}

struct Block_801BE60C *fn_801BE60C(AnimStInfo_t *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return (struct Block_801BE60C *)p->mUnknown4[i].mUnknownC;
        }
    }
    return 0;
}

unsigned short fn_801BE648(AnimStInfo_t *p)
{
    unsigned short key = 0xFFFF;
    int i;

    for (i = 3; i >= 0; i--) {
        if (p->mUnknown4[i].mUnknown2 == 3) {
            key = p->mUnknown4[i].mUnknown0;
        }
    }
    return key;
}

void fn_801BE67C(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pRecords, void *pOwner)
{
    int i;

    for (i = 3; i >= 0; i--) {
        if (p->mUnknown4[i].mUnknown2 != 3 && p->mUnknown4[i].mUnknown2 != 0) {
            _AnimStEndState(p, pObject, pRecords, i, pOwner);
        }
    }
    _AnimStOrganizeInfo(p);
    if (p->mUnknown4[0].mUnknown2 == 3) {
        p->mUnknown4[0].mUnknown8 = 0.0f;
        AnimWgtSet(&p->mUnknown4[0].mUnknown4C, 0, 1.0f, 0, 1.0f);
    }
}

void *fn_801BE72C(unsigned short type, unsigned short key)
{
    AnimFileGetStateAnimList(type, key, &_AnimSt_pStatAnimList);
    return &_AnimSt_pStatAnimList;
}

void fn_801BE760(AnimStInfo_t *p, unsigned short key, unsigned short flags)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            p->mUnknown4[i].mUnknown4 |= flags;
        }
    }
}

void AnimStSetStateDelay(AnimStInfo_t *p, unsigned short key, float value)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            p->mUnknown4[i].mUnknown8 = value;
        }
    }
}

float AnimStGetStateDelay(AnimStInfo_t *p, unsigned short key)
{
    float value = 0.0f;
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            value = p->mUnknown4[i].mUnknown8;
            break;
        }
    }
    return value;
}
