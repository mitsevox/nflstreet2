/* Doubly linked list type of the data-structure library: insert, sorted add, lookup, removal and
   traversal, registered as list type 0. */

#include "engine/list.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"


typedef int (*LinkSearchFn_t)(void *, void *, void *);

#define LINK_NODE_SIZE (lbl_803D4FB8[0].mNodeSize)

static void _DSListInsertLinkAtHead(LinkList_t *pList, LinkNode_t *pNode)
{
    LinkNode_t *pHead = pList->mpHead;

    pList->mpHead = pNode;
    pNode->mpNext = pHead;
    pList->mpHead->mpPrev = 0;
    pHead->mpPrev = pNode;
}

static void _DSListInsertLinkAtTail(LinkList_t *pList, LinkNode_t *pNode)
{
    LinkNode_t *pTail = pList->mpTail;

    pList->mpTail = pNode;
    pNode->mpNext = 0;
    pList->mpTail->mpPrev = pTail;
    pTail->mpNext = pNode;
}

static void _DSListInsertLink(LinkList_t *pList, LinkNode_t *pBefore, LinkNode_t *pNode)
{
    LinkNode_t *pPrev = pBefore->mpPrev;

    pNode->mpPrev = pPrev;
    pPrev->mpNext = pNode;
    pNode->mpNext = pBefore;
    pBefore->mpPrev = pNode;
}

static void _DSListInsertLinkedNode(LinkList_t *pList, LinkNode_t *pBefore, LinkNode_t *pNode)
{
    if (pList->mpHead == 0) {
        pList->mpTail = pNode;
        pList->mpHead = pNode;
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
    } else if (pBefore == pList->mpHead) {
        _DSListInsertLinkAtHead(pList, pNode);
    } else if (pBefore == 0) {
        _DSListInsertLinkAtTail(pList, pNode);
    } else {
        _DSListInsertLink(pList, pBefore, pNode);
    }
    pList->mBase.mCount++;
}

static void _DSListInitLinkedList(LinkList_t *pList)
{
    pList->mpHead = 0;
    pList->mpTail = 0;
}

static int _DSListDelLinkedList(LinkList_t *pList)
{
    int result = 0;

    if (pList->mBase.mHeap) {
        result = fn_801D2BD0(pList);
    }
    return result;
}

static LinkNode_t *_DSListAddLinkedNode(LinkList_t *pList, LinkNode_t *pNode, int mode)
{
    LinkNode_t *pResult = pNode;
    void *pItem;
    LinkNode_t *pCur;
    void *pCurItem;
    int cmp = 1;

    pItem = pNode ? (char *)pNode + LINK_NODE_SIZE : 0;
    pCur = pList->mpHead;
    pCurItem = pCur ? (char *)pCur + LINK_NODE_SIZE : 0;
    if (pList->mBase.mCompare) {
        while (pCur && (cmp = pList->mBase.mCompare(pCurItem, pItem)) < 0) {
            pCur = pCur->mpNext;
            pCurItem = pCur ? (char *)pCur + LINK_NODE_SIZE : 0;
        }
    }
    if (mode != 1 || cmp != 0) {
        _DSListInsertLinkedNode(pList, pCur, pNode);
    } else {
        pResult = pCur;
    }
    return pResult;
}

static void _DSListInitLinkedNode(LinkNode_t *pNode, int size)
{
    fn_801C1F94(pNode, 0, size);
}

static LinkNode_t *_DSListGetLinkedNode(LinkList_t *pList, LinkNode_t *pNode, unsigned int mode)
{
    LinkNode_t *pResult = pNode;

    switch (mode) {
    case 0:
    case 2:
        pResult = pList->mpHead;
        break;
    case 1:
        pResult = pList->mpTail;
        break;
    case 3:
        pResult = pNode->mpPrev;
        break;
    case 4:
        pResult = pNode->mpNext;
        break;
    default:
        pResult = pNode ? (LinkNode_t *)((char *)pNode - LINK_NODE_SIZE) : 0;
        break;
    }
    return pResult;
}

static void _DSListRemoveLinkedNode(LinkList_t *pList, LinkNode_t *pNode)
{
    if (pList->mpHead == pNode) {
        pList->mpHead = pNode->mpNext;
    }
    if (pList->mpTail == pNode) {
        pList->mpTail = pNode->mpPrev;
    }
    if (pNode->mpNext) {
        pNode->mpNext->mpPrev = pNode->mpPrev;
    }
    if (pNode->mpPrev) {
        pNode->mpPrev->mpNext = pNode->mpNext;
    }
    pList->mBase.mCount--;
}

static int _DSListTraverseLinkedList(LinkList_t *pList, LinkNode_t *pNode, void *pCtx, void *pArg,
                       ListVisitFn_801C6D34 callback, int direction)
{
    LinkNode_t *pNext;
    int result = 1;

    while (pNode && result) {
        if (direction < 0) {
            pNext = pNode->mpPrev;
        } else {
            pNext = pNode->mpNext;
        }
        result = callback(pNode ? (char *)pNode + lbl_803D4FB8[0].mNodeSize : 0, pCtx, pArg);
        pNode = pNext;
    }
    return result == 0 ? 4 : 0;
}

static int _DSListSearchLinkedList(LinkList_t *pList, LinkNode_t *pNode, void *a, void *b,
                       LinkSearchFn_t callback)
{
    LinkNode_t *pNext;
    int result = -1;

    while (pNode && result < 0) {
        pNext = pNode->mpNext;
        result = callback(pNode ? (char *)pNode + lbl_803D4FB8[0].mNodeSize : 0, a, b);
        pNode = pNext;
    }
    return result == 0 ? 2 : 3;
}

static int _DSListOptimizeLinkedList(LinkList_t *pList)
{
    return 5;
}

void DSListInitLinkedModule(void)
{
    fn_801C67AC(0, (void (*)(List_801C68FC *))_DSListInitLinkedList, (int (*)(List_801C68FC *))_DSListDelLinkedList,
                (void (*)(Node_801C6A20 *, int))_DSListInitLinkedNode,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) _DSListAddLinkedNode,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) _DSListGetLinkedNode,
                (void (*)(List_801C68FC *, Node_801C6A20 *))_DSListRemoveLinkedNode,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListVisitFn_801C6D34, int))_DSListTraverseLinkedList,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC))_DSListSearchLinkedList,
                (void (*)(List_801C68FC *))_DSListOptimizeLinkedList, sizeof(LinkList_t), sizeof(LinkNode_t));
}
