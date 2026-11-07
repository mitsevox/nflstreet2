/* Fixed-size record pools used by the game database and its query indexes. */
#include "engine/t3db.h"

/* Reserve the initial block; requested counts of four or fewer become ten. */
int _TDbMemPoolInit(TDbMemPool_t *pPool, void *pHeap, unsigned int itemSize, unsigned short count,
                unsigned short growCount)
{
    TDbMemBlock_t *pBlock;
    int err;

    if (count <= 4) {
        count = 10;
    }
    itemSize += 3;
    itemSize &= ~3;
    pPool->mGrowCount = growCount;
    pPool->mHeap = pHeap;
    pPool->mFree = 0;
    pPool->mItemSize = itemSize;
    pPool->mCount = count;
    _TDbMemNotify(0, -1, -1);
    err = TDbExtMemAlloc(pHeap, count * itemSize + sizeof(TDbMemBlock_t), &pBlock);
    _TDbMemNotify(4, -1, -1);
    if (err != 0) {
        return err;
    }
    pBlock->mNext = 0;
    pPool->mRemaining = count;
    pPool->mBlocks = pBlock;
    pPool->mNext = (unsigned char *)(pBlock + 1);
    return 0;
}

/* Growth blocks precede the initial block, whose allocation count can differ. */
int _TDbMemPoolDeinit(TDbMemPool_t *pPool)
{
    TDbMemBlock_t *pBlock;
    TDbMemBlock_t *pNext;

    pBlock = pPool->mBlocks;
    pPool->mFree = 0;
    pPool->mNext = 0;
    pPool->mRemaining = 0;
    while ((pNext = pBlock->mNext) != 0) {
        TDbExtMemFree(pPool->mHeap, pBlock, pPool->mItemSize * pPool->mGrowCount + sizeof(TDbMemBlock_t));
        pBlock = pNext;
    }
    TDbExtMemFree(pPool->mHeap, pBlock, pPool->mItemSize * pPool->mCount + sizeof(TDbMemBlock_t));
    pPool->mBlocks = 0;
    return 0;
}

/* Discard all items and recreate the pool with its existing configuration. */
int _TDbMemPoolReset(TDbMemPool_t *pPool)
{
    _TDbMemPoolDeinit(pPool);
    return _TDbMemPoolInit(pPool, pPool->mHeap, pPool->mItemSize, pPool->mCount, pPool->mGrowCount);
}

/* Reuse returned items before consuming fresh slots or growing the pool. */
int __TDbMemPoolAlloc(TDbMemPool_t *pPool, void *ppItem)
{
    TDbMemBlock_t *pBlock;
    int err;

    if (pPool->mFree) {
        *(void **)ppItem = pPool->mFree;
        pPool->mFree = *(void **)pPool->mFree;
        return 0;
    }
    if (pPool->mRemaining == 0) {
        if (pPool->mGrowCount == 0) {
            return 2;
        }
        _TDbMemNotify(0, -1, -1);
        err = TDbExtMemAlloc(pPool->mHeap, pPool->mGrowCount * pPool->mItemSize + sizeof(TDbMemBlock_t), &pBlock);
        if (err) {
            *(void **)ppItem = 0;
            return err;
        }
        pBlock->mNext = pPool->mBlocks;
        pPool->mBlocks = pBlock;
        pPool->mRemaining = pPool->mGrowCount;
        pPool->mNext = (unsigned char *)(pBlock + 1);
        if (_tDbMemAllocInfoCallback) {
            TDbMemEvent_t event;

            event.mType = 4;
            event.mUnknown4 = -1;
            event.mUnknown8 = -1;
            _tDbMemAllocInfoCallback(&event);
        }
    }
    *(void **)ppItem = pPool->mNext;
    pPool->mNext += pPool->mItemSize;
    pPool->mRemaining--;
    return 0;
}

/* A returned item carries the free-list link until it is allocated again. */
void __TDbMemPoolFree(TDbMemPool_t *pPool, void *pItem)
{
    *(void **)pItem = pPool->mFree;
    pPool->mFree = pItem;
}
