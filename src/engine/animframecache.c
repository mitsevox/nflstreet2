/* Animation frame cache: keeps the most recently used motion frames of
   compressed animation files unpacked in a fixed pool of buffers, reusing the
   least recently used buffer when a new frame is needed. */

#include "engine/animemot.h"
#include "game/fn_801D2B7C.h"

typedef struct AnimFrameCacheNode_t {
    struct AnimFrameCacheNode_t *mPrev;
    struct AnimFrameCacheNode_t *mNext;
    char *mSource;
    unsigned short mMotion;
    unsigned char mHandle;
    unsigned char mUsed;
    int mGroup;
} AnimFrameCacheNode_t;

typedef struct AnimFrameCacheList_t {
    unsigned short mCount;
    AnimFrameCacheNode_t *mHead;
    AnimFrameCacheNode_t *mTail;
    AnimFrameCacheNode_t *mNodes;
} AnimFrameCacheList_t;

typedef struct AnimFrameCache_t {
    unsigned short mCount;
    unsigned short mSize;
    AnimFrameCacheNode_t *mNodes;
    unsigned char *mData;
    AnimFrameCacheList_t mList;
} AnimFrameCache_t;

typedef void (*AnimFrameCacheCustomFunc_t)(AnimFileFormat_t *pFile, int a, unsigned char *pDest, unsigned int source,
                                  unsigned int size, int group);

extern AnimFrameCacheCustomFunc_t _AnimFrameCache_CustomFunc;

void AnimFrameCacheRestoreSources(AnimFrameCache_t *cache);

static inline void SetMotion(AnimFileFormat_t *file, unsigned int motion, int group, char *value)
{
    if (file->flags & 4)
        file->groupMotion[group].motion[motion] = value;
    else
        file->motion[motion] = value;
}

void _AnimFrameCacheRemoveNode(AnimFrameCacheList_t *list, AnimFrameCacheNode_t *node)
{
    if (node == list->mHead) {
        list->mHead = node->mNext;
        list->mHead->mPrev = 0;
    } else if (node == list->mTail) {
        list->mTail = node->mPrev;
        list->mTail->mNext = 0;
    } else {
        AnimFrameCacheNode_t *prev = node->mPrev;
        AnimFrameCacheNode_t *next = node->mNext;
        prev->mNext = next;
        next->mPrev = prev;
    }
}

void _AnimFrameCacheInitList(AnimFrameCacheList_t *list, AnimFrameCacheNode_t *nodes, int count)
{
    AnimFrameCacheNode_t *prev = 0;
    unsigned int i;

    list->mCount = count;
    list->mNodes = nodes;
    list->mHead = nodes;
    for (i = 0; i < count; i++) {
        AnimFrameCacheNode_t *node = &list->mNodes[i];
        memset(node, 0, sizeof(AnimFrameCacheNode_t));
        node->mPrev = prev;
        node->mNext = &list->mNodes[i + 1];
        prev = node;
    }
    list->mTail = &list->mNodes[count - 1];
    list->mTail->mNext = 0;
}

unsigned char *_AnimFrameCacheGetFromCache(AnimFrameCache_t *cache, unsigned int key, int group, int check, unsigned char *pFound)
{
    unsigned int index;
    AnimFrameCacheNode_t *node;
    AnimFrameCacheList_t *list;

    *pFound = 1;
    index = key & 0x0FFFFFFF;
    node = &cache->mNodes[index];
    if (check == 1 && node->mGroup != group) {
        *pFound = 0;
        return 0;
    }
    list = &cache->mList;
    _AnimFrameCacheRemoveNode(list, node);
    node->mPrev = list->mTail;
    node->mPrev->mNext = node;
    list->mTail = node;
    node->mNext = 0;
    return cache->mData + index * cache->mSize;
}

AnimFrameCacheNode_t *_AnimFrameCacheAllocCacheEntry(AnimFrameCache_t *cache)
{
    AnimFrameCacheList_t *list = &cache->mList;
    AnimFrameCacheNode_t *node = list->mHead;

    list->mHead = node->mNext;
    list->mHead->mPrev = 0;
    node->mPrev = list->mTail;
    node->mPrev->mNext = node;
    list->mTail = node;
    node->mNext = 0;
    return node;
}

unsigned char *_AnimFrameCacheAddToCache(AnimFileFormat_t *file, AnimFrameCache_t *cache, int handle, unsigned int motion,
                           char *source, int group)
{
    AnimFrameCacheNode_t *node = _AnimFrameCacheAllocCacheEntry(cache);
    int index;
    unsigned char *data;

    if (node->mUsed == 1)
        SetMotion(AnimFileGetPtrFromSlot(node->mHandle), node->mMotion, (unsigned short)node->mGroup, node->mSource);
    node->mSource = source;
    node->mHandle = handle;
    node->mUsed = 1;
    node->mMotion = motion;
    node->mGroup = group;
    index = node - cache->mNodes;
    data = cache->mData + index * cache->mSize;
    SetMotion(file, motion, group, (char *)(index | 0xF0000000));
    return data;
}

unsigned char *_AnimFrameCacheCreateCache(AnimFileFormat_t *file, int a, AnimFrameCache_t *cache, int handle, unsigned int motion,
                           char *source, int group)
{
    unsigned char *data = _AnimFrameCacheAddToCache(file, cache, handle, motion, source, group);

    _AnimFrameCache_CustomFunc(file, a, data, (unsigned int)source, cache->mSize, group);
    return data;
}

void AnimFrameCacheSetCustomFunc(AnimFrameCacheCustomFunc_t callback)
{
    _AnimFrameCache_CustomFunc = callback;
}

void AnimFrameCacheClearCustomFunc(void)
{
    _AnimFrameCache_CustomFunc = 0;
}

AnimFrameCache_t *AnimFrameCacheCreate(int count, int size)
{
    AnimFrameCache_t *cache = fn_801D2B7C(sizeof(AnimFrameCache_t), 0, 0);

    cache->mNodes = fn_801D2B7C(count * sizeof(AnimFrameCacheNode_t), 0, 0);
    cache->mData = fn_801D2B7C(count * size, 0, 0);
    cache->mSize = size;
    cache->mCount = count;
    _AnimFrameCacheInitList(&cache->mList, cache->mNodes, count);
    return cache;
}

void AnimFrameCacheDestroy(AnimFrameCache_t *cache)
{
    AnimFrameCacheRestoreSources(cache);
    fn_801D2BD0(cache->mNodes);
    fn_801D2BD0(cache->mData);
    fn_801D2BD0(cache);
}

void *AnimFrameCacheGetFrame(AnimFileFormat_t *file, int a, int handle, unsigned int motion, char *source, int group)
{
    AnimFrameCache_t *cache = AnimFileGetFrameCacheFromSlot(handle);
    unsigned char *data;
    unsigned char found;

    if (((unsigned int)source & 0xF0000000) == 0xF0000000) {
        data = _AnimFrameCacheGetFromCache(cache, (unsigned int)source, group, (file->flags & 4) != 0, &found);
        if (!found)
            data = _AnimFrameCacheCreateCache(file, a, cache, handle, motion, source, group);
    } else {
        data = _AnimFrameCacheCreateCache(file, a, cache, handle, motion, source, group);
    }
    return data;
}

void AnimFrameCacheRestoreSources(AnimFrameCache_t *cache)
{
    unsigned int i;

    for (i = 0; i < cache->mList.mCount; i++) {
        AnimFrameCacheNode_t *node = &cache->mList.mNodes[i];
        if (node->mUsed == 1)
            SetMotion(AnimFileGetPtrFromSlot(node->mHandle), node->mMotion, (unsigned short)node->mGroup, node->mSource);
    }
}
