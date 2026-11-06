/* Animation file access: turns a loaded animation file's offsets into pointers
   and answers questions about it (its object type, states, animations,
   transitions and the motion frames each animation plays). */

#include "engine/animemot.h"

extern void (*_AnimFile_RelocateFunc)(AnimFileFormat_t *pFile);

void *AnimFileGetFramePerState(AnimFileFormat_t *pFile, int a, int b, unsigned int index, int group);

void _AnimFileRelocateCustom(AnimFileFormat_t *pFile)
{
    if (_AnimFile_RelocateFunc)
        _AnimFile_RelocateFunc(pFile);
}

void AnimFileSetCustomRelocateFunc(void (*pFunc)(AnimFileFormat_t *))
{
    _AnimFile_RelocateFunc = pFunc;
}

void AnimFileRelocate(AnimFileFormat_t *pFile)
{
    int i;
    int j;
    int k;

    if (!(pFile->flags & 0x1000)) {
        pFile->states = (AnimFileStates_t *)((char *)pFile->states + (int)pFile);
        pFile->anims = (AnimFileAnims_t *)((char *)pFile->anims + (int)pFile);
        pFile->motion = (char **)((char *)pFile->motion + (int)pFile);
        if (pFile->flags & 8) {
            pFile->groups = (AnimGroupHeaderView *)((char *)pFile->groups + (int)pFile);
            pFile->groupMotion = (AnimMotionGroupView *)((char *)pFile->groupMotion + (int)pFile);
            if (pFile->flags & 4) {
                for (k = 0; k < pFile->groups->count; k++) {
                    if (pFile->groupMotion[k].motion) {
                        pFile->groupMotion[k].motion = (char **)((char *)pFile->groupMotion[k].motion + (int)pFile);
                        for (i = 0; i < pFile->groupMotion[k].count; i++)
                            pFile->groupMotion[k].motion[i] = pFile->groupMotion[k].motion[i] + (int)pFile;
                    }
                }
            }
        }
        for (i = 0; i < pFile->motionCount; i++) {
            if (pFile->flags & 4)
                pFile->motion[i] = 0;
            else
                pFile->motion[i] = pFile->motion[i] + (int)pFile;
        }
        for (i = 0; i < pFile->states->mCount; i++) {
            AnimFileState_t *pState = &pFile->states->mStates[i];
            unsigned short count;

            pState->mpAnims = (AnimFileStateAnims_t *)((char *)pState->mpAnims + (int)pFile);
            if (!(pFile->flags & 8)) {
                count = pState->mpAnims->mCount;
                pState->mpAnims->mCount = pState->mpAnims->mUnknown2;
                pState->mpAnims->mUnknown2 = count;
            }
            for (j = 0; j < pState->mpAnims->mCount; j++) {
                if (pState->mpAnims->mEntries[j].mpAnim)
                    pState->mpAnims->mEntries[j].mpAnim =
                        (AnimScript_t *)((char *)pState->mpAnims->mEntries[j].mpAnim + (int)pFile);
            }
            if (pState->mpUnknown8)
                pState->mpUnknown8 = (char *)pState->mpUnknown8 + (int)pFile;
            pState->mpTrans = (AnimFileStateTrans_t *)((char *)pState->mpTrans + (int)pFile);
            for (j = 0; j < pState->mpTrans->mCount; j++) {
                if (pState->mpTrans->mEntries[j].mpUnknownC)
                    pState->mpTrans->mEntries[j].mpUnknownC =
                        (struct Transition_801BEFA4 *)((char *)pState->mpTrans->mEntries[j].mpUnknownC + (int)pFile);
            }
        }
        for (i = 0; i < pFile->anims->mCount; i++)
            pFile->anims->mAnims[i] = (AnimScript_t *)((char *)pFile->anims->mAnims[i] + (int)pFile);
        _AnimFileRelocateCustom(pFile);
        pFile->flags |= 0x1000;
    }
    if (!(pFile->flags & 0x2000))
        AnimCacheInvalidate(AnimFileGetObjectType(pFile));
}

unsigned short AnimFileGetObjectType(AnimFileFormat_t *pFile)
{
    return pFile->objectType;
}

unsigned short AnimFileGetFileNum(AnimFileFormat_t *pFile)
{
    return pFile->fileNum;
}

AnimScript_t *AnimFileGetAnimation(AnimFileFormat_t *pFile, int anim)
{
    return pFile->anims->mAnims[anim];
}

int AnimFileGetStateRef(AnimFileFormat_t *pFile, int state)
{
    unsigned int i;
    unsigned int count = pFile->states->mCount;
    AnimFileState_t *pState = pFile->states->mStates;

    for (i = 0; i < count; i++) {
        if (pState[i].mId == state)
            return i;
    }
    return -1;
}

void AnimFileGetStateAnimListByStateRef(AnimFileFormat_t *pFile, int slot, int stateRef, AnimStateAnimList_t *pList)
{
    AnimFileStateAnims_t *pAnims;
    unsigned int i;

    if (pFile) {
        pAnims = pFile->states->mStates[stateRef].mpAnims;
        for (i = 0; i < pAnims->mCount; i++) {
            if (pList->mCount >= pList->mMax)
                return;
            pList->mEntries[pList->mCount].mUnknown0 = slot;
            pList->mEntries[pList->mCount].mUnknown2 = pAnims->mEntries[i].mId;
            pList->mEntries[pList->mCount].mpUnknown4 = pAnims->mEntries[i].mpAnim;
            pList->mCount++;
        }
    }
}

void AnimFileGetStateTransListByStateRef(AnimFileFormat_t *pFile, int slot, int stateRef, AnimStateTransList_t *pList)
{
    AnimFileStateTrans_t *pTrans;

    if (pList->mCount < pList->mMax) {
        pTrans = pFile->states->mStates[stateRef].mpTrans;
        if (pTrans && pTrans->mCount) {
            pList->mEntries[pList->mCount].mUnknown0 = slot;
            pList->mEntries[pList->mCount].mUnknown2 = pFile->fileNum;
            pList->mEntries[pList->mCount].mpUnknown4 = pFile->states->mStates[stateRef].mpTrans;
            pList->mCount++;
        }
    }
}

void *AnimFileGetStateDataByStateRef(AnimFileFormat_t *pFile, int stateRef)
{
    return pFile->states->mStates[stateRef].mpUnknown8;
}

unsigned int AnimFileGetNumStates(AnimFileFormat_t *pFile)
{
    return pFile->states->mCount;
}

unsigned short AnimFileGetStateIdByStateRef(AnimFileFormat_t *pFile, int stateRef)
{
    return pFile->states->mStates[stateRef].mId;
}

void *AnimFileGetFramePerState(AnimFileFormat_t *pFile, int a, int b, unsigned int index, int group)
{
    void *pMotion;

    if (pFile->flags & 4) {
        pMotion = pFile->groupMotion[group].motion[index];
        if (pFile->flags & 0x200)
            pMotion = AnimFrameCacheGetFrame(pFile, a, b, index, pMotion, group);
    } else {
        if (index >= pFile->motionCount)
            index = 0;
        pMotion = pFile->motion[index];
        if (pFile->flags & 0x200)
            pMotion = AnimFrameCacheGetFrame(pFile, a, b, index, pMotion, 0xFFFF);
    }
    return pMotion;
}

void *AnimFileGetFrame(AnimFileFormat_t *pFile, int a, int b, unsigned int index)
{
    return AnimFileGetFramePerState(pFile, a, b, index, 0xFFFF);
}
