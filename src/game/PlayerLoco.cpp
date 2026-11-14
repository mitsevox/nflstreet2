/* Player locomotion animation: the handler for the momentum animation states
   and the helpers of the locomotion animation state (key 74). The helpers
   pick the animation sub-states from two category bytes, choose the speed
   blend set, set the two pose elements and scale the cycle duration with the
   player's speed. */
#include <string.h>
#include "game/Block_801BE60C.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/LocoBlendSet.h"
#include "game/Object_801BBD5C.h"
#include "game/Table_80089904.h"
#include "game/Ball.h"
#include "game/fn_801BA2A8.h"
#include "game/fn_801BE60C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802270D4.h"

extern "C" {
int fn_8009C56C(Table_80089904 *pTable, const unsigned char *pValues);
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
int fn_801BA6B0(Record_800D81C8 *pEntry);
void fn_801BA6BC(Record_800D81C8 *pEntry, int value);
void AnimMomentumInit(AnimMomentum_t *p, AnimMomentumActor_t *pOther, int entry);
void AnimMomentumUpdate(AnimMomentum_t *p, AnimMomentumActor_t *pOther);
void fn_800ADBC0(Object_80039F5C *p, int a, int b, int c);
int fn_800C0464(void *p);
int PlayerLocoFindSampleIndex(Object_801BBD5C *pObject, float value);
float PlayerLocoUpdateBlendWeights(int index, Block_801BE60C *pBlock, LocoBlendSet_t *pObject, Record_800D81C8 *pEntries,
                  float value);
int PlayerActionAnimIsPassReady(Object_80039F5C *p);
Object_801BBD5C *AnimFileGetStateData(unsigned short a, unsigned short b);
void AnimSeqSetDuration(AnimSeq_t *p, float value);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);

extern void *lbl_803EABA4;

int PlayerMoveGetKind(Object_80039F5C *p);
int PlayerMoveIsVariantPending(Object_80039F5C *p);
}

/* Payload that fn_801BE60C returns for this handler's key: the channel index
   that fn_801BA2A8 returns and the state AnimMomentumInit and AnimMomentumUpdate update. */
struct PlayerLocoMomentumPayload_t {
    int mEntry;
    AnimMomentum_t mState;
};

extern "C" int PlayerLocoHandleMomentumState(Table_80089904 *pTable, unsigned short key, void *pRecord,
                                             Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int phase)
{
    PlayerLocoMomentumPayload_t *pPayload = (PlayerLocoMomentumPayload_t *)fn_801BE60C(p->mpUnknown792, key);

    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        unsigned char side = p == BallGetCurrentHolder() ? 1 : 2;
        int i = fn_8009C56C(pTable, &side);
        AnimFileGetStateAnimList(p->mpUnknown796->mUnknown2, pTable->mEntries[i].mUnknown2 & 0x7FFF, pTable);
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        if (index >= 0) {
            pPayload->mEntry = fn_801BA2A8(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                                           pTable->mEntries[index].mUnknown2, key, p, 1.0f);
            if (BallFindHeldBy(p) && p->mUnknown776 == 1) {
                Record_800D81C8 *pEntry = &pEntries[pPayload->mEntry];
                fn_801BA6BC(pEntry, fn_801BA6B0(pEntry) == 0);
            }
            AnimMomentumInit(&pPayload->mState, (AnimMomentumActor_t *)p, pPayload->mEntry);
        }
        break;
    }
    case 1:
        break;
    case 2:
        AnimMomentumUpdate(&pPayload->mState, (AnimMomentumActor_t *)p);
        break;
    }
    return 0;
}

extern "C" void PlayerLocoSetupBlendSets(Table_80089904 *pTable, Block_801BE60C *pBlock, Object_80039F5C *p)
{
    pBlock->mpUnknown18 = 0;
    pBlock->mpUnknown14 = 0;
    pBlock->mUnknown39 = 0;
    pBlock->mUnknown38 = 0;
    for (unsigned int i = 0; i < pTable->mCount; i++) {
        unsigned char type = pTable->mEntries[i].mpInfo->mValue;
        unsigned short key = pTable->mEntries[i].mUnknown2 & 0x7FFF;
        unsigned short id = pTable->mEntries[i].mUnknown0;
        switch (type) {
        case 1:
            pBlock->mpUnknown10 = AnimFileGetStateData(key, p->mpUnknown796->mUnknown2);
            pBlock->mUnknown20.mUnknown17 = id;
            break;
        case 3:
            pBlock->mpUnknown14 = AnimFileGetStateData(key, p->mpUnknown796->mUnknown2);
            pBlock->mUnknown38 = id;
            break;
        case 2:
            pBlock->mpUnknown18 = AnimFileGetStateData(key, p->mpUnknown796->mUnknown2);
            pBlock->mUnknown39 = id;
            break;
        }
    }
    if (pBlock->mpUnknown14 == 0) {
        pBlock->mpUnknown14 = pBlock->mpUnknown10;
        pBlock->mUnknown38 = pBlock->mUnknown20.mUnknown17;
    }
    if (pBlock->mpUnknown18 == 0) {
        pBlock->mpUnknown18 = pBlock->mpUnknown10;
        pBlock->mUnknown39 = pBlock->mUnknown20.mUnknown17;
    }
    pBlock->mpUnknownC = pBlock->mpUnknown10;
    pBlock->mUnknown20.mUnknown16 = pBlock->mUnknown20.mUnknown17;
}

extern "C" void PlayerLocoSetPoseElements(Table_80089904 *pTable, Object_80039F5C *p, int index, int swap)
{
    Info_80089904 *pInfo = pTable->mEntries[index].mpInfo;
    unsigned char a = pInfo->mType;
    unsigned char b = pInfo->mUnknown6;

    if (swap) {
        unsigned char t = a;
        a = b;
        b = t;
    }
    if (p->mIdBytes[3] == 1) {
        fn_800ADBC0(p, a, 8, 0);
        fn_800ADBC0(p, b, 8, 1);
    }
}

extern "C" void PlayerLocoSelectSecondaryState(Table_80089904 *pTable, Block_801BE60C *pBlock, Object_80039F5C *p, int swap)
{
    unsigned char values[4];

    memset(values, 255, sizeof(values));
    values[0] = pBlock->mUnknown3D;
    int index = fn_8009C56C(pTable, values);
    unsigned short id = pTable->mEntries[index].mUnknown2 & 0x7FFF;
    PlayerLocoSetPoseElements(pTable, p, index, swap);
    AnimFileGetStateAnimList(p->mpUnknown796->mUnknown2, id, pTable);
    PlayerLocoSetupBlendSets(pTable, pBlock, p);
}

extern "C" void PlayerLocoSelectStates(Table_80089904 *pTable, Block_801BE60C *pBlock, Object_80039F5C *p, int swap)
{
    unsigned char values[4];

    memset(values, 255, sizeof(values));
    values[0] = pBlock->mUnknown3C;
    int index = fn_8009C56C(pTable, values);
    AnimFileGetStateAnimList(p->mpUnknown796->mUnknown2, pTable->mEntries[index].mUnknown2 & 0x7FFF, pTable);
    PlayerLocoSelectSecondaryState(pTable, pBlock, p, swap);
}

extern "C" int PlayerLocoSelectBlendSet(Object_80039F5C *p, Block_801BE60C *pBlock, unsigned char *pKind)
{
    unsigned char id = 0;
    int changed = 0;
    Object_801BBD5C *pObject = 0;
    float t = p->mMotion.mUnknown28;

    if (t == 0.0f) {
        pObject = pBlock->mpUnknown10;
        id = pBlock->mUnknown20.mUnknown17;
        *pKind = 6;
    } else if (p->mMotion.mUnknown52 < 0.0f) {
        Object_801BBD5C *pCandidate = pBlock->mpUnknown14;
        if (t >= pCandidate->mUnknown12 && t <= pCandidate->mUnknown16) {
            pObject = pCandidate;
            id = pBlock->mUnknown38;
            *pKind = 6;
        }
    } else if (p->mMotion.mUnknown52 == 0.0f && p->mUnknown528.mUnknown14 == 10) {
        Object_801BBD5C *pCandidate = pBlock->mpUnknown18;
        if (t >= pCandidate->mUnknown12 && t <= pCandidate->mUnknown16) {
            pObject = pCandidate;
            id = pBlock->mUnknown39;
            *pKind = 6;
        }
    } else if (p->mUnknown492 > p->mUnknown488) {
        pObject = pBlock->mpUnknown10;
        id = pBlock->mUnknown20.mUnknown17;
        *pKind = 6;
    } else if (p->mMotion.mUnknown28 > p->mUnknown492) {
        pObject = pBlock->mpUnknown10;
        id = pBlock->mUnknown20.mUnknown17;
        *pKind = 8;
    }
    if (pObject && pObject != pBlock->mpUnknownC) {
        if (pBlock->mpUnknownC == pBlock->mpUnknown18) {
            *pKind += *pKind;
        }
        pBlock->mpUnknownC = pObject;
        pBlock->mUnknown20.mUnknown16 = id;
        changed = 1;
    }
    return changed;
}

extern "C" int PlayerLocoGetBlendIndex(Object_80039F5C *p, Object_801BBD5C *pObject)
{
    float value = p->mMotion.mUnknown28;

    if (value != 0.0f && MathAngleDiff(p->mMotion.mFacing, p->mMotion.mUnknown32) > 0x3C71C7) {
        value = -value;
    }
    return PlayerLocoFindSampleIndex(pObject, value);
}

extern "C" void PlayerLocoSetCycleDuration(float value, Block_801BE60C *pBlock, LocoBlendSet_t *pObject,
                                           Record_800D81C8 *pRecords)
{
    pBlock->mUnknown20.mUnknown10 = PlayerLocoUpdateBlendWeights(pBlock->mUnknown20.mUnknown14Half, pBlock, pObject, pRecords, value);
    for (unsigned char i = 0; i <= 1; i++) {
        unsigned char index = pBlock->mUnknown20.mUnknown8Bytes[i];
        if (index != 255) {
            AnimSeqSetDuration(&pRecords[index].mUnknown4C, pBlock->mUnknown20.mUnknown10);
        }
    }
}

extern "C" int PlayerLocoIsEngaged(Object_80039F5C *p, int a)
{
    Block_8011E240 *pBlock = &p->mBlock1032;
    int result = 0;

    if (pBlock->mUnknown20 != 0) {
        switch (p->mUnknown1032) {
        case 4:
        case 7:
            result = 1;
            break;
        case 1:
        case 2:
        case 3:
            if (a == 0) {
                if (pBlock->mUnknown20 == 1) {
                    result = 1;
                } else {
                    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mUnknown4);
                    if (pOther) {
                        Pair_802270A4 delta;
                        fn_80227690(&delta, &pOther->mMotion, &p->mMotion);
                        if (MathAngleDiff(fn_801CFE40(delta.mUnknown4, delta.mUnknown0), p->mMotion.mFacing) <= 0x1FFFFF
                            && fn_802270A4(&delta) < 4.5f) {
                            result = 1;
                        }
                    }
                }
            }
            break;
        }
    }
    if (pBlock->mUnknown20 == 3 && !result && p->mMotion.mUnknown28 < 1e-7f) {
        result = 1;
    }
    return result;
}

extern "C" int PlayerLocoUseAltCategory(Object_80039F5C *, Object_80039F5C *, int, int)
{
    int mode = fn_800AD9B4();

    if (mode == 3 || (mode == 2 && (unsigned char)fn_800C0464(lbl_803EABA4))) {
        return 1;
    }
    return 0;
}

extern "C" int PlayerLocoUseSpecialCategory(Object_80039F5C *)
{
    return 0;
}

extern "C" int PlayerLocoGetPrimaryCategory(Object_80039F5C *p, int team, int a, unsigned char *pOut)
{
    int result;

    if (p->mIdBytes[3] != 1) {
        result = 2;
    } else {
        unsigned char kind = p->mUnknown528.mUnknown15;
        if (kind <= 1 || kind == 4 || kind == 5 || kind == 29 || kind == 20 || kind == 21) {
            if (p->mIdBytes[2] == team) {
                *pOut = PlayerLocoIsEngaged(p, a);
                if (*pOut) {
                    *pOut = 1;
                    result = 7;
                } else if (p->mpState->mId == 18 || PlayerActionAnimIsPassReady(p)) {
                    *pOut = 0;
                    result = 3;
                } else {
                    switch (p->mUnknown2921) {
                    case 10: result = 10; break;
                    case 8: result = 12; break;
                    case 1: result = 18; break;
                    case 2: result = 19; break;
                    case 3: result = 20; break;
                    case 9: result = 11; break;
                    case 4: result = 14; break;
                    case 5: result = 15; break;
                    case 6: result = 16; break;
                    case 7: result = 17; break;
                    case 0:
                    default: result = 13; break;
                    }
                }
                if ((unsigned char)(p->mUnknown528.mUnknown15 - 20) <= 1 && PlayerMoveGetKind(p) == 2 && !PlayerMoveIsVariantPending(p)) {
                    result = 1;
                }
            } else if (p->mUnknown1032 == 4) {
                result = 8;
            } else {
                switch (p->mUnknown2921) {
                case 10: result = 10; break;
                case 8: result = 12; break;
                case 1: result = 18; break;
                case 2: result = 19; break;
                case 3: result = 20; break;
                case 9: result = 11; break;
                case 4: result = 14; break;
                case 5: result = 15; break;
                case 6: result = 16; break;
                case 7: result = 17; break;
                case 0:
                default: result = 13; break;
                }
            }
        } else {
            result = 1;
        }
    }
    return result;
}
