#include "engine/cu_801C665C.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"


typedef int (*SearchFn_801C7234)(void *, void *, void *);

#define LINK_NODE_SIZE (lbl_803D4FB8[0].mNodeSize)

static void fn_801C6E5C(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode)
{
    LinkNode_801C6E5C *pHead = pList->mpHead;

    pList->mpHead = pNode;
    pNode->mpNext = pHead;
    pList->mpHead->mpPrev = 0;
    pHead->mpPrev = pNode;
}

static void fn_801C6E7C(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode)
{
    LinkNode_801C6E5C *pTail = pList->mpTail;

    pList->mpTail = pNode;
    pNode->mpNext = 0;
    pList->mpTail->mpPrev = pTail;
    pTail->mpNext = pNode;
}

static void fn_801C6E9C(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pBefore, LinkNode_801C6E5C *pNode)
{
    LinkNode_801C6E5C *pPrev = pBefore->mpPrev;

    pNode->mpPrev = pPrev;
    pPrev->mpNext = pNode;
    pNode->mpNext = pBefore;
    pBefore->mpPrev = pNode;
}

static void fn_801C6EB4(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pBefore, LinkNode_801C6E5C *pNode)
{
    if (pList->mpHead == 0) {
        pList->mpTail = pNode;
        pList->mpHead = pNode;
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
    } else if (pBefore == pList->mpHead) {
        fn_801C6E5C(pList, pNode);
    } else if (pBefore == 0) {
        fn_801C6E7C(pList, pNode);
    } else {
        fn_801C6E9C(pList, pBefore, pNode);
    }
    pList->mBase.mCount++;
}

static void fn_801C6F40(LinkList_801C6E5C *pList)
{
    pList->mpHead = 0;
    pList->mpTail = 0;
}

static int fn_801C6F50(LinkList_801C6E5C *pList)
{
    int result = 0;

    if (pList->mBase.mHeap) {
        result = fn_801D2BD0(pList);
    }
    return result;
}

static LinkNode_801C6E5C *fn_801C6F88(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode, int mode)
{
    LinkNode_801C6E5C *pResult = pNode;
    void *pItem;
    LinkNode_801C6E5C *pCur;
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
        fn_801C6EB4(pList, pCur, pNode);
    } else {
        pResult = pCur;
    }
    return pResult;
}

static void fn_801C7080(LinkNode_801C6E5C *pNode, int size)
{
    fn_801C1F94(pNode, 0, size);
}

static LinkNode_801C6E5C *fn_801C70A8(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode, unsigned int mode)
{
    LinkNode_801C6E5C *pResult = pNode;

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
        pResult = pNode ? (LinkNode_801C6E5C *)((char *)pNode - LINK_NODE_SIZE) : 0;
        break;
    }
    return pResult;
}

static void fn_801C7128(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode)
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

static int fn_801C7188(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode, void *pCtx, void *pArg,
                       ListVisitFn_801C6D34 callback, int direction)
{
    LinkNode_801C6E5C *pNext;
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

static int fn_801C7234(LinkList_801C6E5C *pList, LinkNode_801C6E5C *pNode, void *a, void *b,
                       SearchFn_801C7234 callback)
{
    LinkNode_801C6E5C *pNext;
    int result = -1;

    while (pNode && result < 0) {
        pNext = pNode->mpNext;
        result = callback(pNode ? (char *)pNode + lbl_803D4FB8[0].mNodeSize : 0, a, b);
        pNode = pNext;
    }
    return result == 0 ? 2 : 3;
}

static int fn_801C72C8(LinkList_801C6E5C *pList)
{
    return 5;
}

void fn_801C72D0(void)
{
    fn_801C67AC(0, (void (*)(List_801C68FC *))fn_801C6F40, (int (*)(List_801C68FC *))fn_801C6F50,
                (void (*)(Node_801C6A20 *, int))fn_801C7080,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) fn_801C6F88,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) fn_801C70A8,
                (void (*)(List_801C68FC *, Node_801C6A20 *))fn_801C7128,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListVisitFn_801C6D34, int))fn_801C7188,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC))fn_801C7234,
                (void (*)(List_801C68FC *))fn_801C72C8, sizeof(LinkList_801C6E5C), sizeof(LinkNode_801C6E5C));
}
