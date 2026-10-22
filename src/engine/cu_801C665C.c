#include "engine/cu_801C665C.h"
#include "game/fn_801C68FC.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

void fn_801C72D0(void);
void fn_801C7EE4(void);
void fn_801C8E88(void);

static int fn_801C665C(int type, int size)
{
    return fn_801C6644(size) + lbl_803D4FB8[type].mNodeSize;
}

static int fn_801C66A4(int type, int count, int *pSize)
{
    int size;

    *pSize = fn_801C665C(type, *pSize);
    size = fn_801C74A0(count, *pSize);
    return size + fn_801C6644(lbl_803D4FB8[type].mHeaderSize);
}

static void fn_801C670C(List_801C68FC *pList, Node_801C6A20 *pNode)
{
    lbl_803D4FB8[pList->mType].mRemove(pList, pNode);
    pNode->mFlags &= ~0x80000000;
}

void fn_801C6760(void)
{
    int i;

    for (i = 0; i < 9; i++) {
        lbl_803D4FB8[i].mActive = 0;
    }
    fn_801C72D0();
    fn_801C8E88();
    fn_801C7EE4();
}

void fn_801C67AC(int type, void (*init)(List_801C68FC *), int (*del)(List_801C68FC *),
                 void (*initNode)(Node_801C6A20 *, int),
                 Node_801C6A20 *(*add)(List_801C68FC *, Node_801C6A20 *, int),
                 Node_801C6A20 *(*get)(List_801C68FC *, Node_801C6A20 *, int),
                 void (*remove)(List_801C68FC *, Node_801C6A20 *),
                 int (*traverse)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListVisitFn_801C6D34, int),
                 int (*search)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC),
                 void (*optimize)(List_801C68FC *), int headerSize, int nodeSize)
{
    lbl_803D4FB8[type].mDelete = del;
    lbl_803D4FB8[type].mInitNode = initNode;
    lbl_803D4FB8[type].mAdd = add;
    lbl_803D4FB8[type].mGet = get;
    lbl_803D4FB8[type].mRemove = remove;
    lbl_803D4FB8[type].mTraverse = traverse;
    lbl_803D4FB8[type].mSearch = search;
    lbl_803D4FB8[type].mOptimize = optimize;
    lbl_803D4FB8[type].mInit = init;
    lbl_803D4FB8[type].mHeaderSize = fn_801C6644(headerSize);
    lbl_803D4FB8[type].mNodeSize = fn_801C6644(nodeSize);
    lbl_803D4FB8[type].mActive = 1;
}

int fn_801C6858(int type, int count, int size)
{
    return fn_801C66A4(type, count, &size);
}

unsigned int fn_801C6880(List_801C68FC *pList, unsigned int stat)
{
    unsigned int value;

    switch (stat) {
    case 0:
        value = fn_801C74C8(pList->mpNodes, 0);
        break;
    case 1:
        value = fn_801C74C8(pList->mpNodes, 1);
        break;
    case 2:
        value = fn_801C74C8(pList->mpNodes, 2);
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

void *fn_801C68FC(int a, int b, int count, int size, int (*cmp)(void *, void *), void *storage)
{
    List_801C68FC *pList = storage;
    int itemSize;
    int memSize;

    itemSize = fn_801C6644(size);
    memSize = fn_801C66A4(b, count, &size);
    if (pList == 0) {
        pList = fn_801D2BB0(a, memSize, 0, 0);
        if (pList == 0) {
            return 0;
        }
    }
    pList->mItemSize = itemSize;
    pList->mHeap = a;
    pList->mCount = 0;
    pList->mCompare = cmp;
    pList->mType = b;
    pList->mpNodes = fn_801C750C(0, count, size,
                                 (NodePool_801C750C *)((char *)pList + fn_801C6644(lbl_803D4FB8[b].mHeaderSize)));
    lbl_803D4FB8[b].mInit(pList);
    fn_801F7BD4(0);
    return pList;
}

int fn_801C69E4(void *pool)
{
    List_801C68FC *pList = pool;

    return lbl_803D4FB8[pList->mType].mDelete(pList);
}

void *fn_801C6A20(void *pool)
{
    List_801C68FC *pList = pool;
    Node_801C6A20 *pNode;

    pNode = fn_801C75F0(pList->mpNodes);
    if (pNode) {
        lbl_803D4FB8[pList->mType].mInitNode(pNode, lbl_803D4FB8[pList->mType].mNodeSize);
        pNode->mFlags &= ~0x80000000;
        pNode = (Node_801C6A20 *)((char *)pNode + lbl_803D4FB8[pList->mType].mNodeSize);
    }
    return pNode;
}

void *fn_801C6AA4(void *pool, void *item, int c)
{
    List_801C68FC *pList = pool;

    item = item ? (char *)item - lbl_803D4FB8[pList->mType].mNodeSize : 0;
    item = lbl_803D4FB8[pList->mType].mAdd(pList, item, c);
    ((Node_801C6A20 *)item)->mFlags |= 0x80000000;
    return item ? (char *)item + lbl_803D4FB8[pList->mType].mNodeSize : 0;
}

void *fn_801C6B4C(List_801C68FC *pList, int mode)
{
    Node_801C6A20 *pNode;

    pNode = lbl_803D4FB8[pList->mType].mGet(pList, 0, mode);
    return pNode ? (char *)pNode + lbl_803D4FB8[pList->mType].mNodeSize : 0;
}

void fn_801C6BC0(List_801C68FC *pList, void *item)
{
    fn_801C670C(pList, item ? (Node_801C6A20 *)((char *)item - lbl_803D4FB8[pList->mType].mNodeSize) : 0);
}

void fn_801C6C0C(List_801C68FC *pList, void *item)
{
    Node_801C6A20 *pNode;

    pNode = item ? (Node_801C6A20 *)((char *)item - lbl_803D4FB8[pList->mType].mNodeSize) : 0;
    if (pNode->mFlags & 0x80000000) {
        fn_801C670C(pList, pNode);
    }
    fn_801C7650(pList->mpNodes, pNode);
}

void *fn_801C6C84(List_801C68FC *pList, void *item)
{
    Node_801C6A20 *pNode = item;

    pNode = pNode ? (Node_801C6A20 *)((char *)pNode - lbl_803D4FB8[pList->mType].mNodeSize) : 0;
    if (pNode->mFlags & 0x80000000) {
        pNode = lbl_803D4FB8[pList->mType].mGet(pList, pNode, 4);
        if (pNode) {
            return (char *)pNode + lbl_803D4FB8[pList->mType].mNodeSize;
        }
    }
    return 0;
}

/* pStart is a get selector (0-4: first, last, ...) or an item, as for the type's get function. */
int fn_801C6D34(List_801C68FC *pList, void *pStart, void *pCtx, void *pArg, ListVisitFn_801C6D34 fn, int direction)
{
    Node_801C6A20 *pNode;

    pNode = lbl_803D4FB8[pList->mType].mGet(pList, pStart, (int)pStart);
    if (pNode == 0) {
        return 1;
    }
    return lbl_803D4FB8[pList->mType].mTraverse(pList, pNode, pCtx, pArg, fn, direction);
}

int fn_801C6DCC(List_801C68FC *pList, void *pStart, void *pKey, void *pResult, ListSearchFn_801C6DCC fn)
{
    Node_801C6A20 *pNode;

    pNode = lbl_803D4FB8[pList->mType].mGet(pList, pStart, (int)pStart);
    if (pNode == 0) {
        return 1;
    }
    return lbl_803D4FB8[pList->mType].mSearch(pList, pNode, pKey, pResult, fn);
}
