#include "engine/t3db.h"

int fn_80203444(TDbMemPool_80202B60 *pPool, void *pHeap, unsigned int itemSize, unsigned short count,
                unsigned short growCount)
{
    TDbMemBlock_80203444 *pBlock;
    int err;

    if (count <= 4) {
        count = 10;
    }
    itemSize = (itemSize + 3) & ~3;
    pPool->mGrowCount = growCount;
    pPool->mHeap = pHeap;
    pPool->mFree = 0;
    pPool->mItemSize = itemSize;
    pPool->mCount = count;
    TDbMemNotify_801FC9D4(0, -1, -1);
    err = fn_8020D1B0(pHeap, count * itemSize + sizeof(TDbMemBlock_80203444), &pBlock);
    TDbMemNotify_801FC9D4(4, -1, -1);
    if (err != 0) {
        return err;
    }
    pBlock->mNext = 0;
    pPool->mRemaining = count;
    pPool->mBlocks = pBlock;
    pPool->mNext = (unsigned char *)(pBlock + 1);
    return 0;
}

int fn_8020353C(TDbMemPool_80202B60 *pPool)
{
    TDbMemBlock_80203444 *pBlock;
    TDbMemBlock_80203444 *pNext;

    pBlock = pPool->mBlocks;
    pPool->mFree = 0;
    pPool->mNext = 0;
    pPool->mRemaining = 0;
    while ((pNext = pBlock->mNext) != 0) {
        fn_8020D2AC(pPool->mHeap, pBlock, pPool->mItemSize * pPool->mGrowCount + sizeof(TDbMemBlock_80203444));
        pBlock = pNext;
    }
    fn_8020D2AC(pPool->mHeap, pBlock, pPool->mItemSize * pPool->mCount + sizeof(TDbMemBlock_80203444));
    pPool->mBlocks = 0;
    return 0;
}

int fn_802035C8(TDbMemPool_80202B60 *pPool)
{
    fn_8020353C(pPool);
    return fn_80203444(pPool, pPool->mHeap, pPool->mItemSize, pPool->mCount, pPool->mGrowCount);
}

int fn_8020360C(TDbMemPool_80202B60 *pPool, void *ppItem)
{
    TDbMemBlock_80203444 *pBlock;
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
        TDbMemNotify_801FC9D4(0, -1, -1);
        err = fn_8020D1B0(pPool->mHeap, pPool->mGrowCount * pPool->mItemSize + sizeof(TDbMemBlock_80203444), &pBlock);
        if (err) {
            *(void **)ppItem = 0;
            return err;
        }
        pBlock->mNext = pPool->mBlocks;
        pPool->mBlocks = pBlock;
        pPool->mRemaining = pPool->mGrowCount;
        pPool->mNext = (unsigned char *)(pBlock + 1);
        {
            TDbMemEvent_801FC5FC event;

            if (lbl_803EBE80) {
                event.mType = 4;
                event.mUnknown4 = -1;
                event.mUnknown8 = -1;
                lbl_803EBE80(&event);
            }
        }
    }
    *(void **)ppItem = pPool->mNext;
    pPool->mNext += pPool->mItemSize;
    pPool->mRemaining--;
    return 0;
}

void fn_80203744(TDbMemPool_80202B60 *pPool, void *pItem)
{
    *(void **)pItem = pPool->mFree;
    pPool->mFree = pItem;
}
