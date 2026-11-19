/* Animation motion blending: turns a channel list into the weighted list of motions to sample
   (each active channel contributes its current and its next motion, split by the sequence's blend
   fraction), finds a channel's state index and compression table, and blends two orientations. */

#include "engine/cu_801BDA30.h"

typedef struct AnimMotQuat_t {
    float mValues[4];
} AnimMotQuat_t;

/* One motion of the weight list: its weights, the channel and file it comes from, the
   motion's compression table and frame data. */
typedef struct AnimMotFrame_t {
    float mWeight;
    float mBlend;
    unsigned char mType;
    unsigned char mChannel;
    unsigned char mUnknownA[22];
    unsigned short mSlot;
    unsigned short mMotion;
    AnimQuantContext *mpCmpTbl;
    void *mpFrame;
} AnimMotFrame_t;

typedef struct AnimMotFrameList_t {
    unsigned short mCount;
    unsigned short mCapacity;
    AnimMotFrame_t mFrames[24];
} AnimMotFrameList_t;

static AnimMotFrameList_t _AnimMot_FrameList;

Slot_801BE594 *fn_801BE594(Collection_801BE594 *p, unsigned short key);
void *AnimFileGetFramePerState(AnimFileFormat_t *pFile, int a, int b, unsigned int index, unsigned short group);

int abs(int x);

void QuatFromEulerYZX(AnimMotQuat_t *pOut, int x, int y, int z);
void QuatSlerp(AnimMotQuat_t *pOut, AnimMotQuat_t *pA, AnimMotQuat_t *pB, float t);
void QuatToEulerYZX(Triple_801BCA74 *pOut, AnimMotQuat_t *pQuat);
void Orient3Lerp(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t);

unsigned short _AnimMotGetStateIndex(int state, AnimFileFormat_t *pFile, Slot_801BE594 *pSlot)
{
    if (pFile->flags & 4)
        return pSlot->mUnknown6;
    return 0xFFFF;
}

void _AnimMotBlendOrient(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t)
{
    AnimMotQuat_t b;
    AnimMotQuat_t a;
    int dx = (pA->mUnknown0 - pB->mUnknown0) << 8 >> 8;
    int dy = (pA->mUnknown4 - pB->mUnknown4) << 8 >> 8;
    int dz = (pA->mUnknown8 - pB->mUnknown8) << 8 >> 8;

    if (abs(dx) + abs(dy) + abs(dz) > 0x400000) {
        QuatFromEulerYZX(&a, pA->mUnknown4, pA->mUnknown8, pA->mUnknown0);
        QuatFromEulerYZX(&b, pB->mUnknown4, pB->mUnknown8, pB->mUnknown0);
        QuatSlerp(&a, &a, &b, t);
        QuatToEulerYZX(pOut, &a);
    } else {
        Orient3Lerp(pOut, pA, pB, t);
    }
}

AnimQuantContext *_AnimMotGetCmpTbl(AnimFileFormat_t *pFile, int group)
{
    if ((pFile->flags & 1) && !(pFile->flags & 0x200)) {
        if (pFile->flags & 4)
            return pFile->groupMotion[group].compress;
        return pFile->compress;
    }
    return 0;
}

AnimMotFrameList_t *AnimMotCreateWeightList(AnimHeader_t *pObject, AnimChannel_t *pChannels, Collection_801BE594 *pSlots)
{
    AnimMotFrameList_t *pList = &_AnimMot_FrameList;
    unsigned short count = 0;
    int i;
    int j;
    Slot_801BE594 *pSlot;
    AnimFileFormat_t *pFile;
    float weight;
    int state;
    float total;

    // FAKEMATCH: the field store order, the split weight product, the goto exit and the second
    // counter j were chosen by trial for the target's code; the logic is unchanged
    pList->mCapacity = 24;
    for (i = 0; i < pObject->mUnknown4; i++) {
        if (count >= pList->mCapacity)
            goto done;
        if (pChannels[i].mUnknown1 && pChannels[i].mUnknown48 == 0.0f) {
            AnimSeq_t *pSeq = &pChannels[i].mUnknown4C;

            pSlot = fn_801BE594(pSlots, pChannels[i].mUnknown8);
            weight = pSlot->mUnknown4C.mUnknown0;
            weight *= pChannels[i].mUnknown30.mUnknown0;
            pList->mFrames[count].mWeight = weight;
            if ((pList->mFrames[count].mBlend = weight * pSeq->mUnknown14) != 0.0f) {
                pFile = AnimFileGetPtrFromSlot(pChannels[i].mUnknown6);
                if (pFile) {
                    state = pChannels[i].mUnknownA == 0xFFFF ? _AnimMotGetStateIndex(pChannels[i].mUnknown8, pFile, pSlot) : pChannels[i].mUnknownA;
                    pList->mFrames[count].mpFrame = AnimFileGetFramePerState(
                        pFile, pChannels[i].mUnknown7, pChannels[i].mUnknown6, pSeq->mUnknown12, state);
                    pList->mFrames[count].mpCmpTbl = _AnimMotGetCmpTbl(pFile, state);
                    pList->mFrames[count].mSlot = pChannels[i].mUnknown6;
                    pList->mFrames[count].mMotion = pSeq->mUnknown12;
                    pList->mFrames[count].mType = pChannels[i].mUnknown7;
                    pList->mFrames[count].mChannel = i;
                    count++;
                }
            }
            if (count < pList->mCapacity) {
                pList->mFrames[count].mWeight = weight;
                if ((pList->mFrames[count].mBlend = weight * (1.0f - pSeq->mUnknown14)) != 0.0f) {
                    pFile = AnimFileGetPtrFromSlot(pChannels[i].mUnknown6);
                    if (pFile) {
                        state = pChannels[i].mUnknownA == 0xFFFF ? _AnimMotGetStateIndex(pChannels[i].mUnknown8, pFile, pSlot) : pChannels[i].mUnknownA;
                        pList->mFrames[count].mpFrame = AnimFileGetFramePerState(
                            pFile, pChannels[i].mUnknown7, pChannels[i].mUnknown6, pSeq->mUnknown10, state);
                        pList->mFrames[count].mpCmpTbl = _AnimMotGetCmpTbl(pFile, state);
                        pList->mFrames[count].mSlot = pChannels[i].mUnknown6;
                        pList->mFrames[count].mMotion = pSeq->mUnknown10;
                        pList->mFrames[count].mType = pChannels[i].mUnknown7;
                        pList->mFrames[count].mChannel = i;
                        count++;
                    }
                }
            }
        }
    }
done:
    pList->mCount = count;
    total = pList->mFrames[0].mBlend;
    pList->mFrames[0].mBlend = 1.0f;
    for (j = 1; j < count; j++) {
        total += pList->mFrames[j].mBlend;
        if (total != 0.0f)
            pList->mFrames[j].mBlend = pList->mFrames[j].mBlend / total;
        else
            pList->mFrames[j].mBlend = 0.0f;
    }
    return pList;
}
