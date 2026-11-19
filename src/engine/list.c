#include "engine/list.h"
#include "engine/dslist.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

/* The handler table of each list type (0 linked, 1 binary tree, 2 splay tree, ...), filled by
   DSAddListType. */
DSListType_t DSList_Interface[9];

void DSListInitLinkedModule(void);
void fn_801C7EE4(void);
void DSListInitBinTreeModule(void);

static int _DSGetListNodeSize(int type, int size)
{
    return DSAlignSize(size) + DSList_Interface[type].mNodeSize;
}

static int _DSGetListMemSize(int type, int count, int *pSize)
{
    int size;

    *pSize = _DSGetListNodeSize(type, *pSize);
    size = DSGetNodeHandlerMemSize(count, *pSize);
    return size + DSAlignSize(DSList_Interface[type].mHeaderSize);
}

static void _DSRemoveListNode(DSList_t *pList, DSListNode_t *pNode)
{
    DSList_Interface[pList->mType].mRemove(pList, pNode);
    pNode->mFlags &= ~0x80000000;
}

void DSListInitModule(void)
{
    int i;

    for (i = 0; i < 9; i++) {
        DSList_Interface[i].mActive = 0;
    }
    DSListInitLinkedModule();
    DSListInitBinTreeModule();
    fn_801C7EE4();
}

void DSAddListType(int type, void (*init)(DSList_t *), int (*del)(DSList_t *),
                 void (*initNode)(DSListNode_t *, int),
                 DSListNode_t *(*add)(DSList_t *, DSListNode_t *, int),
                 DSListNode_t *(*get)(DSList_t *, DSListNode_t *, int),
                 void (*remove)(DSList_t *, DSListNode_t *),
                 int (*traverse)(DSList_t *, DSListNode_t *, void *, void *, DSListVisitFn_t, int),
                 int (*search)(DSList_t *, DSListNode_t *, void *, void *, DSListSearchFn_t),
                 void (*optimize)(DSList_t *), int headerSize, int nodeSize)
{
    DSList_Interface[type].mDelete = del;
    DSList_Interface[type].mInitNode = initNode;
    DSList_Interface[type].mAdd = add;
    DSList_Interface[type].mGet = get;
    DSList_Interface[type].mRemove = remove;
    DSList_Interface[type].mTraverse = traverse;
    DSList_Interface[type].mSearch = search;
    DSList_Interface[type].mOptimize = optimize;
    DSList_Interface[type].mInit = init;
    DSList_Interface[type].mHeaderSize = DSAlignSize(headerSize);
    DSList_Interface[type].mNodeSize = DSAlignSize(nodeSize);
    DSList_Interface[type].mActive = 1;
}

int DSGetListMemSize(int type, int count, int size)
{
    return _DSGetListMemSize(type, count, &size);
}

unsigned int DSGetListStat(DSList_t *pList, unsigned int stat)
{
    unsigned int value;

    switch (stat) {
    case 0:
        value = DSGetNodeHandlerStat(pList->mpNodes, 0);
        break;
    case 1:
        value = DSGetNodeHandlerStat(pList->mpNodes, 1);
        break;
    case 2:
        value = DSGetNodeHandlerStat(pList->mpNodes, 2);
        break;
    case 3:
        value = pList->mCount;
        break;
    default:
        value = 0;
        break;
    }
    return value;
}

void *DSNewList(int a, int b, int count, int size, int (*cmp)(void *, void *), void *storage)
{
    DSList_t *pList = storage;
    int itemSize;
    int memSize;
    NodePool_t *pPool;
    void *pResult;

    itemSize = DSAlignSize(size);
    memSize = _DSGetListMemSize(b, count, &size);
    if (pList == 0) {
        pList = fn_801D2BB0(a, memSize, 0, 0);
    }
    if (pList != 0) {
        // FAKEMATCH: the result goes through its own local set first, and the node pool pointer is
        // computed into a local before the DSNewNodeHandler call (same values, same calls).
        pResult = pList;
        pList->mItemSize = itemSize;
        pList->mHeap = a;
        pList->mCount = 0;
        pList->mCompare = cmp;
        pList->mType = b;
        pPool = (NodePool_t *)((char *)pList + DSAlignSize(DSList_Interface[b].mHeaderSize));
        pList->mpNodes = DSNewNodeHandler(0, count, size, pPool);
        DSList_Interface[b].mInit(pList);
        fn_801F7BD4(0);
    } else {
        pResult = 0;
    }
    return pResult;
}

int DSDelList(void *pool)
{
    DSList_t *pList = pool;

    return DSList_Interface[pList->mType].mDelete(pList);
}

void *DSNewListNode(void *pool)
{
    DSList_t *pList = pool;
    DSListNode_t *pNode;

    pNode = DSNewNode(pList->mpNodes);
    if (pNode) {
        DSList_Interface[pList->mType].mInitNode(pNode, DSList_Interface[pList->mType].mNodeSize);
        pNode->mFlags &= ~0x80000000;
        pNode = (DSListNode_t *)((char *)pNode + DSList_Interface[pList->mType].mNodeSize);
    }
    return pNode;
}

void *DSAddListNode(void *pool, void *item, int c)
{
    DSList_t *pList = pool;

    item = item ? (char *)item - DSList_Interface[pList->mType].mNodeSize : 0;
    item = DSList_Interface[pList->mType].mAdd(pList, item, c);
    ((DSListNode_t *)item)->mFlags |= 0x80000000;
    return item ? (char *)item + DSList_Interface[pList->mType].mNodeSize : 0;
}

void *DSGetListNode(DSList_t *pList, int mode)
{
    DSListNode_t *pNode;

    pNode = DSList_Interface[pList->mType].mGet(pList, 0, mode);
    return pNode ? (char *)pNode + DSList_Interface[pList->mType].mNodeSize : 0;
}

void DSRemoveListNode(DSList_t *pList, void *item)
{
    _DSRemoveListNode(pList, item ? (DSListNode_t *)((char *)item - DSList_Interface[pList->mType].mNodeSize) : 0);
}

void DSDelListNode(DSList_t *pList, void *item)
{
    DSListNode_t *pNode;

    pNode = item ? (DSListNode_t *)((char *)item - DSList_Interface[pList->mType].mNodeSize) : 0;
    if (pNode->mFlags & 0x80000000) {
        _DSRemoveListNode(pList, pNode);
    }
    DSDelNode(pList->mpNodes, pNode);
}

void *DSNextListNode(DSList_t *pList, void *item)
{
    DSListNode_t *pNode = item;

    pNode = pNode ? (DSListNode_t *)((char *)pNode - DSList_Interface[pList->mType].mNodeSize) : 0;
    if (pNode->mFlags & 0x80000000) {
        pNode = DSList_Interface[pList->mType].mGet(pList, pNode, 4);
        pNode = pNode ? (DSListNode_t *)((char *)pNode + DSList_Interface[pList->mType].mNodeSize) : 0;
    } else {
        pNode = 0;
    }
    return pNode;
}

/* pStart is a get selector (0-4: first, last, ...) or an item, as for the type's get function. */
int DSTraverseList(DSList_t *pList, void *pStart, void *pCtx, void *pArg, DSListVisitFn_t fn, int direction)
{
    DSListNode_t *pNode;

    pNode = DSList_Interface[pList->mType].mGet(pList, pStart, (int)pStart);
    if (pNode == 0) {
        return 1;
    }
    return DSList_Interface[pList->mType].mTraverse(pList, pNode, pCtx, pArg, fn, direction);
}

int DSSearchList(DSList_t *pList, void *pStart, void *pKey, void *pResult, DSListSearchFn_t fn)
{
    DSListNode_t *pNode;

    pNode = DSList_Interface[pList->mType].mGet(pList, pStart, (int)pStart);
    if (pNode == 0) {
        return 1;
    }
    return DSList_Interface[pList->mType].mSearch(pList, pNode, pKey, pResult, fn);
}
