/* Animation state cache: for each kind of animated object, remembers which
   loaded animation file and state entry serve each animation state, so state
   lookups do not have to search every loaded file. */

#include "engine/animemot.h"
#include "game/fn_801D2B7C.h"

typedef struct AnimCacheObjType_t {
    unsigned short mId;
    unsigned char mDirty;
    unsigned short mCountA;
    AnimCacheStateInfo_t *mPairsA;
    unsigned short mCountB;
    AnimCacheStateInfo_t *mPairsB;
} AnimCacheObjType_t;

extern unsigned int _AnimCache_nCaches;
extern int _AnimCache_MemoryHeap;
extern AnimCacheObjType_t *_AnimCache_pCaches;
extern unsigned char _AnimCache_Initialized;

void AnimCacheClearObjectType(unsigned int index);

void AnimCacheInit(int heap, unsigned int count)
{
    _AnimCache_MemoryHeap = heap;
    _AnimCache_nCaches = count;
    _AnimCache_pCaches = fn_801D2BB0(heap, count * sizeof(AnimCacheObjType_t), 0, 0);
    memset(_AnimCache_pCaches, 0, count * sizeof(AnimCacheObjType_t));
    _AnimCache_Initialized = 1;
}

void AnimCacheShutdown(void)
{
    unsigned int i;

    for (i = 0; i < _AnimCache_nCaches; i++)
        AnimCacheClearObjectType(i);
    fn_801D2BD0(_AnimCache_pCaches);
    _AnimCache_pCaches = 0;
    _AnimCache_nCaches = 0;
    _AnimCache_Initialized = 0;
}

static inline AnimCacheObjType_t *GetEntry(unsigned int index)
{
    return index < _AnimCache_nCaches ? &_AnimCache_pCaches[index] : 0;
}

void AnimCacheSetUpObjectType(unsigned int index, unsigned int countA, unsigned int countB)
{
    AnimCacheObjType_t *entry;

    AnimCacheClearObjectType(index);
    entry = GetEntry(index);
    if (entry != 0) {
        entry->mCountA = countA;
        entry->mCountB = countB;
        entry->mId = index;
        entry->mPairsA = fn_801D2BB0(_AnimCache_MemoryHeap, (countA + countB) * sizeof(AnimCacheStateInfo_t), 0, 0);
        entry->mPairsB = entry->mPairsA + countA;
        AnimCacheInvalidate(index);
    }
}

void AnimCacheClearObjectType(unsigned int index)
{
    AnimCacheObjType_t *entry = GetEntry(index);

    if (entry != 0) {
        if (entry->mPairsA != 0) {
            fn_801D2BD0(entry->mPairsA);
            entry->mPairsA = 0;
        }
        entry->mPairsB = 0;
        entry->mCountA = 0;
        entry->mId = 0;
    }
}

void AnimCacheInvalidate(unsigned int index)
{
    AnimCacheObjType_t *entry = GetEntry(index);
    unsigned int i;

    if (entry == 0)
        return;
    for (i = 0; i < entry->mCountA; i++) {
        entry->mPairsA[i].mUnknown0 = -1;
        entry->mPairsA[i].mUnknown2 = -1;
    }
    for (i = 0; i < entry->mCountB; i++) {
        entry->mPairsB[i].mUnknown0 = -1;
        entry->mPairsB[i].mUnknown2 = -1;
    }
    entry->mDirty = 1;
}

AnimCacheStateInfo_t *AnimCacheGetStateInfo(unsigned int index, unsigned int key)
{
    AnimCacheObjType_t *entry = GetEntry(index);

    if (entry != 0) {
        if (key > 0x1FFF) {
            key &= 0x1FFF;
            if (key < entry->mCountB)
                return &entry->mPairsB[key];
        } else if (key < entry->mCountA) {
            return &entry->mPairsA[key];
        }
    }
    return 0;
}

void AnimCacheUpdate(void)
{
    unsigned int i;

    for (i = 0; i < _AnimCache_nCaches; i++) {
        AnimCacheObjType_t *entry = &_AnimCache_pCaches[i];
        if (entry->mDirty) {
            AnimFileBuildStateCache(i);
            entry->mDirty = 0;
        }
    }
}
