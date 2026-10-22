#include "engine/cu_801C665C.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"


int fn_801C735C(unsigned int count, int size, int *pStackOffset, int *pNodeOffset);
int fn_801C73C0(NodePool_801C750C *pPool);

static void fn_801C7408(NodePool_801C750C *pPool, int index)
{
    if (pPool->mCount <= 0xFF) {
        ((unsigned char *)pPool->mpStack)[pPool->mFree] = index;
    } else {
        ((unsigned short *)pPool->mpStack)[pPool->mFree] = index;
    }
    pPool->mFree++;
}

static void fn_801C7444(NodePool_801C750C *pPool)
{
    unsigned int i;

    pPool->mFree = 0;
    for (i = 0; i < pPool->mCount; i++) {
        fn_801C7408(pPool, i);
    }
}

int fn_801C74A0(unsigned int count, int size)
{
    int stackOffset;
    int nodeOffset;

    return fn_801C735C(count, size, &stackOffset, &nodeOffset);
}

unsigned int fn_801C74C8(NodePool_801C750C *pPool, unsigned int stat)
{
    unsigned int value;

    switch (stat) {
    case 0:
        value = pPool->mFree;
        break;
    case 1:
        value = pPool->mCount - pPool->mFree;
        break;
    case 2:
        value = pPool->mCount;
        break;
    default:
        value = 0;
        break;
    }
    return value;
}

NodePool_801C750C *fn_801C750C(int heap, unsigned int count, int size, NodePool_801C750C *pPool)
{
    int stackOffset;
    int nodeOffset;
    int memSize;

    memSize = fn_801C735C(count, size, &stackOffset, &nodeOffset);
    if (pPool == 0) {
        pPool = fn_801D2BB0(heap, memSize, 0, 0);
        if (pPool == 0) {
            return 0;
        }
    }
    pPool->mCount = count;
    pPool->mNodeSize = size;
    pPool->mHeap = heap;
    pPool->mpStack = (char *)pPool + stackOffset;
    pPool->mpNodes = (char *)pPool + nodeOffset;
    fn_801C7444(pPool);
    fn_801F7BD4(0);
    return pPool;
}

int fn_801C75B8(NodePool_801C750C *pPool)
{
    int result = 0;

    if (pPool->mHeap) {
        result = fn_801D2BD0(pPool);
    }
    return result;
}

void *fn_801C75F0(NodePool_801C750C *pPool)
{
    int index;
    void *pNode;
    int error;

    index = fn_801C73C0(pPool);
    if (index >= 0) {
        pNode = pPool->mpNodes + index * pPool->mNodeSize;
        error = 0;
    } else {
        pNode = 0;
        error = 0x30003;
    }
    fn_801F7BD4(error);
    return pNode;
}

void fn_801C7650(NodePool_801C750C *pPool, void *pNode)
{
    fn_801C7408(pPool, (unsigned int)((char *)pNode - pPool->mpNodes) / pPool->mNodeSize);
}
