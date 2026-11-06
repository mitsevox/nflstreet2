/* Fixed-size node pools of the data-structure library: a block of equal nodes with a stack of free
   indices, used to hand out and take back list nodes. */

#include "engine/list.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"


static int _DSGetNodeHandlerMemSize(unsigned int count, int size, int *pStackOffset, int *pNodeOffset)
{
    int entrySize;
    int offset;

    entrySize = count <= 0xFF ? 1 : 2;
    offset = 24;
    *pStackOffset = offset;
    offset += count * entrySize;
    offset = DSAlignSize(offset);
    *pNodeOffset = offset;
    offset += count * size;
    return offset;
}

static int _DSPopNode(NodePool_t *pPool)
{
    int result;

    if (pPool->mFree != 0) {
        pPool->mFree--;
        if (pPool->mCount <= 0xFF) {
            result = ((unsigned char *)pPool->mpStack)[pPool->mFree];
        } else {
            result = ((unsigned short *)pPool->mpStack)[pPool->mFree];
        }
    } else {
        result = -1;
    }
    return result;
}

static void _DSPushNode(NodePool_t *pPool, int index)
{
    if (pPool->mCount <= 0xFF) {
        ((unsigned char *)pPool->mpStack)[pPool->mFree] = index;
    } else {
        ((unsigned short *)pPool->mpStack)[pPool->mFree] = index;
    }
    pPool->mFree++;
}

static void _DSFormatNodeHandlerStack(NodePool_t *pPool)
{
    unsigned int i;

    pPool->mFree = 0;
    for (i = 0; i < pPool->mCount; i++) {
        _DSPushNode(pPool, i);
    }
}

int DSGetNodeHandlerMemSize(unsigned int count, int size)
{
    int stackOffset;
    int nodeOffset;

    return _DSGetNodeHandlerMemSize(count, size, &stackOffset, &nodeOffset);
}

unsigned int DSGetNodeHandlerStat(NodePool_t *pPool, unsigned int stat)
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

NodePool_t *DSNewNodeHandler(int heap, unsigned int count, int size, NodePool_t *pPool)
{
    int stackOffset;
    int nodeOffset;
    int memSize;
    NodePool_t *pResult;

    memSize = _DSGetNodeHandlerMemSize(count, size, &stackOffset, &nodeOffset);
    if (pPool == 0) {
        pPool = fn_801D2BB0(heap, memSize, 0, 0);
    }
    if (pPool != 0) {
        pResult = pPool;
        pPool->mCount = count;
        pPool->mNodeSize = size;
        pPool->mHeap = heap;
        pPool->mpStack = (char *)pPool + stackOffset;
        pPool->mpNodes = (char *)pPool + nodeOffset;
        _DSFormatNodeHandlerStack(pPool);
        fn_801F7BD4(0);
    } else {
        pResult = 0;
    }
    return pResult;
}

int DSDelNodeHandler(NodePool_t *pPool)
{
    int result = 0;

    if (pPool->mHeap) {
        result = fn_801D2BD0(pPool);
    }
    return result;
}

void *DSNewNode(NodePool_t *pPool)
{
    int index;
    void *pNode;
    int error;

    index = _DSPopNode(pPool);
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

void DSDelNode(NodePool_t *pPool, void *pNode)
{
    _DSPushNode(pPool, (unsigned int)((char *)pNode - pPool->mpNodes) / pPool->mNodeSize);
}
