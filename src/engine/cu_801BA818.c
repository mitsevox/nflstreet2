#include "engine/cu_801BA818.h"

extern void (*lbl_803ECEB8)(AnimFileFormat_t *pFile);

void *fn_801BACD0(AnimFileFormat_t *pFile, int a, int b, unsigned int index, int group);

void fn_801BA818(AnimFileFormat_t *pFile)
{
    if (lbl_803ECEB8)
        lbl_803ECEB8(pFile);
}

void fn_801BA848(void (*pFunc)(AnimFileFormat_t *))
{
    lbl_803ECEB8 = pFunc;
}

void fn_801BA850(AnimFileFormat_t *pFile)
{
    int i;
    int j;
    int k;

    if (!(pFile->flags & 0x1000)) {
        pFile->states = (States_801BAB48 *)((char *)pFile->states + (int)pFile);
        pFile->anims = (Anims_801BAB34 *)((char *)pFile->anims + (int)pFile);
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
            State_801BAB48 *pState = &pFile->states->mStates[i];
            unsigned short count;

            pState->mpAnims = (StateAnims_801BAB88 *)((char *)pState->mpAnims + (int)pFile);
            if (!(pFile->flags & 8)) {
                count = pState->mpAnims->mCount;
                pState->mpAnims->mCount = pState->mpAnims->mUnknown2;
                pState->mpAnims->mUnknown2 = count;
            }
            for (j = 0; j < pState->mpAnims->mCount; j++) {
                if (pState->mpAnims->mEntries[j].mpAnim)
                    pState->mpAnims->mEntries[j].mpAnim =
                        (Anim_801BAB34 *)((char *)pState->mpAnims->mEntries[j].mpAnim + (int)pFile);
            }
            if (pState->mpUnknown8)
                pState->mpUnknown8 = (char *)pState->mpUnknown8 + (int)pFile;
            pState->mpTrans = (StateTrans_801BAC1C *)((char *)pState->mpTrans + (int)pFile);
            for (j = 0; j < pState->mpTrans->mCount; j++) {
                if (pState->mpTrans->mEntries[j].mpUnknownC)
                    pState->mpTrans->mEntries[j].mpUnknownC =
                        (struct Transition_801BEFA4 *)((char *)pState->mpTrans->mEntries[j].mpUnknownC + (int)pFile);
            }
        }
        for (i = 0; i < pFile->anims->mCount; i++)
            pFile->anims->mAnims[i] = (Anim_801BAB34 *)((char *)pFile->anims->mAnims[i] + (int)pFile);
        fn_801BA818(pFile);
        pFile->flags |= 0x1000;
    }
    if (!(pFile->flags & 0x2000))
        fn_801BF7BC(fn_801BAB24(pFile));
}

unsigned short fn_801BAB24(AnimFileFormat_t *pFile)
{
    return pFile->objectType;
}

unsigned short fn_801BAB2C(AnimFileFormat_t *pFile)
{
    return pFile->fileNum;
}

Anim_801BAB34 *fn_801BAB34(AnimFileFormat_t *pFile, int anim)
{
    return pFile->anims->mAnims[anim];
}

int fn_801BAB48(AnimFileFormat_t *pFile, int state)
{
    unsigned int i;
    unsigned int count = pFile->states->mCount;
    State_801BAB48 *pState = pFile->states->mStates;

    for (i = 0; i < count; i++) {
        if (pState[i].mId == state)
            return i;
    }
    return -1;
}

void fn_801BAB88(AnimFileFormat_t *pFile, int slot, int stateRef, List_801BAB88 *pList)
{
    StateAnims_801BAB88 *pAnims;
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

void fn_801BAC1C(AnimFileFormat_t *pFile, int slot, int stateRef, List_801BAC1C *pList)
{
    StateTrans_801BAC1C *pTrans;

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

void *fn_801BAC9C(AnimFileFormat_t *pFile, int stateRef)
{
    return pFile->states->mStates[stateRef].mpUnknown8;
}

unsigned int fn_801BACB0(AnimFileFormat_t *pFile)
{
    return pFile->states->mCount;
}

unsigned short fn_801BACBC(AnimFileFormat_t *pFile, int stateRef)
{
    return pFile->states->mStates[stateRef].mId;
}

void *fn_801BACD0(AnimFileFormat_t *pFile, int a, int b, unsigned int index, int group)
{
    void *pMotion;

    if (pFile->flags & 4) {
        pMotion = pFile->groupMotion[group].motion[index];
        if (pFile->flags & 0x200)
            pMotion = fn_801BFD8C(pFile, a, b, index, pMotion, group);
    } else {
        if (index >= pFile->motionCount)
            index = 0;
        pMotion = pFile->motion[index];
        if (pFile->flags & 0x200)
            pMotion = fn_801BFD8C(pFile, a, b, index, pMotion, 0xFFFF);
    }
    return pMotion;
}

void *fn_801BAD70(AnimFileFormat_t *pFile, int a, int b, unsigned int index)
{
    return fn_801BACD0(pFile, a, b, index, 0xFFFF);
}
