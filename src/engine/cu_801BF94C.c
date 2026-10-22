#include "engine/cu_801BA818.h"
#include "game/fn_801D2B7C.h"

typedef struct Node_801BF94C {
    struct Node_801BF94C *mPrev;
    struct Node_801BF94C *mNext;
    char *mSource;
    unsigned short mMotion;
    unsigned char mHandle;
    unsigned char mUsed;
    int mGroup;
} Node_801BF94C;

typedef struct List_801BF94C {
    unsigned short mCount;
    Node_801BF94C *mHead;
    Node_801BF94C *mTail;
    Node_801BF94C *mNodes;
} List_801BF94C;

typedef struct Cache_801BFCC4 {
    unsigned short mCount;
    unsigned short mSize;
    Node_801BF94C *mNodes;
    unsigned char *mData;
    List_801BF94C mList;
} Cache_801BFCC4;

typedef void (*Callback_801BFCB0)(AnimFileFormat_t *pFile, int a, unsigned char *pDest, unsigned int source,
                                  unsigned int size, int group);

extern Callback_801BFCB0 lbl_803ECEC0;

void fn_801BFE4C(Cache_801BFCC4 *cache);

static inline void SetMotion(AnimFileFormat_t *file, unsigned int motion, int group, char *value)
{
    if (file->flags & 4)
        file->groupMotion[group].motion[motion] = value;
    else
        file->motion[motion] = value;
}

void fn_801BF94C(List_801BF94C *list, Node_801BF94C *node)
{
    if (node == list->mHead) {
        list->mHead = node->mNext;
        list->mHead->mPrev = 0;
    } else if (node == list->mTail) {
        list->mTail = node->mPrev;
        list->mTail->mNext = 0;
    } else {
        Node_801BF94C *prev = node->mPrev;
        Node_801BF94C *next = node->mNext;
        prev->mNext = next;
        next->mPrev = prev;
    }
}

void fn_801BF9A0(List_801BF94C *list, Node_801BF94C *nodes, int count)
{
    Node_801BF94C *prev = 0;
    unsigned int i;

    list->mCount = count;
    list->mNodes = nodes;
    list->mHead = nodes;
    for (i = 0; i < count; i++) {
        Node_801BF94C *node = &list->mNodes[i];
        memset(node, 0, sizeof(Node_801BF94C));
        node->mPrev = prev;
        node->mNext = &list->mNodes[i + 1];
        prev = node;
    }
    list->mTail = &list->mNodes[count - 1];
    list->mTail->mNext = 0;
}

unsigned char *fn_801BFA50(Cache_801BFCC4 *cache, unsigned int key, int group, int check, unsigned char *pFound)
{
    unsigned int index;
    Node_801BF94C *node;
    List_801BF94C *list;

    *pFound = 1;
    index = key & 0x0FFFFFFF;
    node = &cache->mNodes[index];
    if (check == 1 && node->mGroup != group) {
        *pFound = 0;
        return 0;
    }
    list = &cache->mList;
    fn_801BF94C(list, node);
    node->mPrev = list->mTail;
    node->mPrev->mNext = node;
    list->mTail = node;
    node->mNext = 0;
    return cache->mData + index * cache->mSize;
}

Node_801BF94C *fn_801BFAEC(Cache_801BFCC4 *cache)
{
    List_801BF94C *list = &cache->mList;
    Node_801BF94C *node = list->mHead;

    list->mHead = node->mNext;
    list->mHead->mPrev = 0;
    node->mPrev = list->mTail;
    node->mPrev->mNext = node;
    list->mTail = node;
    node->mNext = 0;
    return node;
}

unsigned char *fn_801BFB20(AnimFileFormat_t *file, Cache_801BFCC4 *cache, int handle, unsigned int motion,
                           char *source, int group)
{
    Node_801BF94C *node = fn_801BFAEC(cache);
    int index;
    unsigned char *data;

    if (node->mUsed == 1)
        SetMotion(fn_801BC084(node->mHandle), node->mMotion, (unsigned short)node->mGroup, node->mSource);
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

unsigned char *fn_801BFC34(AnimFileFormat_t *file, int a, Cache_801BFCC4 *cache, int handle, unsigned int motion,
                           char *source, int group)
{
    unsigned char *data = fn_801BFB20(file, cache, handle, motion, source, group);

    lbl_803ECEC0(file, a, data, (unsigned int)source, cache->mSize, group);
    return data;
}

void fn_801BFCB0(Callback_801BFCB0 callback)
{
    lbl_803ECEC0 = callback;
}

void fn_801BFCB8(void)
{
    lbl_803ECEC0 = 0;
}

Cache_801BFCC4 *fn_801BFCC4(int count, int size)
{
    Cache_801BFCC4 *cache = fn_801D2B7C(sizeof(Cache_801BFCC4), 0, 0);

    cache->mNodes = fn_801D2B7C(count * sizeof(Node_801BF94C), 0, 0);
    cache->mData = fn_801D2B7C(count * size, 0, 0);
    cache->mSize = size;
    cache->mCount = count;
    fn_801BF9A0(&cache->mList, cache->mNodes, count);
    return cache;
}

void fn_801BFD48(Cache_801BFCC4 *cache)
{
    fn_801BFE4C(cache);
    fn_801D2BD0(cache->mNodes);
    fn_801D2BD0(cache->mData);
    fn_801D2BD0(cache);
}

void *fn_801BFD8C(AnimFileFormat_t *file, int a, int handle, unsigned int motion, char *source, int group)
{
    Cache_801BFCC4 *cache = fn_801BC0C0(handle);
    unsigned char *data;
    unsigned char found;

    if (((unsigned int)source & 0xF0000000) == 0xF0000000) {
        data = fn_801BFA50(cache, (unsigned int)source, group, (file->flags & 4) != 0, &found);
        if (!found)
            data = fn_801BFC34(file, a, cache, handle, motion, source, group);
    } else {
        data = fn_801BFC34(file, a, cache, handle, motion, source, group);
    }
    return data;
}

void fn_801BFE4C(Cache_801BFCC4 *cache)
{
    unsigned int i;

    for (i = 0; i < cache->mList.mCount; i++) {
        Node_801BF94C *node = &cache->mList.mNodes[i];
        if (node->mUsed == 1)
            SetMotion(fn_801BC084(node->mHandle), node->mMotion, (unsigned short)node->mGroup, node->mSource);
    }
}
