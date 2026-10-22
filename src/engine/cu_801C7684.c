#include "engine/cu_801C665C.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"


typedef int (*VisitFn_801C7684)(void *, int, int);

#define SPLAY_NODE_SIZE (lbl_803D4FB8[2].mNodeSize)
#define SPLAY_ITEM(pNode) ((pNode) ? (char *)(pNode) + SPLAY_NODE_SIZE : 0)

SplayNode_801C7684 *fn_801C77DC(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode);
SplayNode_801C7684 *fn_801C7810(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode);

static int fn_801C7684(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode, int a, int b,
                       VisitFn_801C7684 callback)
{
    SplayNode_801C7684 *pNext;
    int done = 0;
    int result;

    do {
        pNext = fn_801C7810(pTree, pNode);
        result = callback(SPLAY_ITEM(pNode), a, b);
        if (result == 0 || pNext == pTree->mpNil) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static int fn_801C7730(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode, int a, int b,
                       VisitFn_801C7684 callback)
{
    SplayNode_801C7684 *pNext;
    int done = 0;
    int result;

    do {
        pNext = fn_801C77DC(pTree, pNode);
        result = callback(SPLAY_ITEM(pNode), a, b);
        if (result == 0 || pNext != pTree->mpNil) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static SplayNode_801C7684 *fn_801C7844(SplayNode_801C7684 *pNode, SplayTree_801C7684 *pTree)
{
    SplayNode_801C7684 header;
    SplayNode_801C7684 *pLeft;
    SplayNode_801C7684 *pRight;
    SplayNode_801C7684 *pChild;
    void *pItem;
    int cmp;

    pLeft = pRight = &header;
    header.mpLeft = header.mpRight = pTree->mpNil;
    pItem = SPLAY_ITEM(pNode);
    while ((cmp = -pTree->mBase.mCompare(SPLAY_ITEM(pTree->mpRoot), pItem)) != 0) {
        if (cmp < 0) {
            if (pTree->mpRoot->mpLeft == pTree->mpNil) {
                break;
            }
            if (-pTree->mBase.mCompare(SPLAY_ITEM(pTree->mpRoot->mpLeft), pItem) < 0) {
                pChild = pTree->mpRoot->mpLeft;
                pTree->mpRoot->mpLeft = pChild->mpRight;
                pChild->mpRight = pTree->mpRoot;
                pTree->mpRoot = pChild;
            }
            if (pTree->mpRoot->mpLeft == pTree->mpNil) {
                break;
            }
            pRight->mpLeft = pTree->mpRoot;
            pRight = pTree->mpRoot;
            pTree->mpRoot = pTree->mpRoot->mpLeft;
        } else {
            if (pTree->mpRoot->mpRight == pTree->mpNil) {
                break;
            }
            if (-pTree->mBase.mCompare(SPLAY_ITEM(pTree->mpRoot->mpRight), pItem) > 0) {
                pChild = pTree->mpRoot->mpRight;
                pTree->mpRoot->mpRight = pChild->mpLeft;
                pChild->mpLeft = pTree->mpRoot;
                pTree->mpRoot = pChild;
            }
            if (pTree->mpRoot->mpRight == pTree->mpNil) {
                break;
            }
            pLeft->mpRight = pTree->mpRoot;
            pLeft = pTree->mpRoot;
            pTree->mpRoot = pTree->mpRoot->mpRight;
        }
    }
    pLeft->mpRight = pTree->mpRoot->mpLeft;
    pRight->mpLeft = pTree->mpRoot->mpRight;
    pTree->mpRoot->mpLeft = header.mpRight;
    pTree->mpRoot->mpRight = header.mpLeft;
    return pTree->mpRoot;
}

static void fn_801C7A34(SplayTree_801C7684 *pTree)
{
    pTree->mBase.mCount = 0;
    pTree->mpNil = &pTree->mNil;
    pTree->mpNil->mpLeft = pTree->mpNil->mpRight = &pTree->mNil;
    pTree->mpFirst = pTree->mpLast = pTree->mpRoot = pTree->mpNil;
}

static int fn_801C7A60(SplayTree_801C7684 *pTree)
{
    int result = 0;

    if (pTree->mBase.mHeap) {
        result = fn_801D2BD0(pTree);
    }
    return result;
}

static SplayNode_801C7684 *fn_801C7A98(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode, int mode)
{
    SplayNode_801C7684 *pResult = pNode;
    SplayNode_801C7684 *pRoot;
    void *pItem;
    int cmp;

    pItem = SPLAY_ITEM(pNode);
    pRoot = pTree->mpRoot;
    if (pTree->mBase.mCompare && pRoot) {
        if (pRoot == pTree->mpNil) {
            pNode->mpLeft = pNode->mpRight = pRoot;
            pTree->mpFirst = pTree->mpLast = pTree->mpRoot = pNode;
        } else {
            pTree->mpRoot = fn_801C7844(pNode, pTree);
            cmp = -pTree->mBase.mCompare(SPLAY_ITEM(pTree->mpRoot), pItem);
            if (cmp < 0) {
                pNode->mpLeft = pTree->mpRoot->mpLeft;
                pNode->mpRight = pTree->mpRoot;
                pTree->mpRoot->mpLeft = pTree->mpNil;
                pTree->mpRoot = pNode;
                for (pRoot = pNode; pRoot->mpLeft != pTree->mpNil; pRoot = pRoot->mpLeft) {
                }
                pTree->mpFirst = pRoot;
            } else if (cmp > 0 || mode != 1) {
                pNode->mpRight = pTree->mpRoot->mpRight;
                pNode->mpLeft = pTree->mpRoot;
                pTree->mpRoot->mpRight = pTree->mpNil;
                pTree->mpRoot = pNode;
                for (pRoot = pNode; pRoot->mpRight != pTree->mpNil; pRoot = pRoot->mpRight) {
                }
                pTree->mpLast = pRoot;
            } else {
                pResult = pRoot;
            }
        }
        pTree->mBase.mCount++;
    }
    return pResult;
}

static void fn_801C7C1C(SplayNode_801C7684 *pNode, int size)
{
    fn_801C1F94(pNode, 0, size);
}

static SplayNode_801C7684 *fn_801C7C44(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode, unsigned int mode)
{
    SplayNode_801C7684 *pResult = pNode;

    if (pTree->mpRoot == pTree->mpNil) {
        pResult = 0;
    } else {
        switch (mode) {
        case 2:
            pResult = pTree->mpRoot;
            break;
        case 0:
            pResult = pTree->mpFirst;
            break;
        case 1:
            pResult = pTree->mpLast;
            break;
        case 3:
            pResult = fn_801C77DC(pTree, pResult);
            break;
        case 4:
            pResult = fn_801C7810(pTree, pResult);
            break;
        default:
            pResult = pNode ? (SplayNode_801C7684 *)((char *)pNode - SPLAY_NODE_SIZE) : 0;
            break;
        }
    }
    if (pResult == pTree->mpNil) {
        pResult = 0;
    }
    return pResult;
}

static void fn_801C7D1C(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode)
{
    SplayNode_801C7684 *pRoot;
    void *pItem;

    if (pTree->mpRoot == pTree->mpNil) {
        return;
    }
    pTree->mpRoot = fn_801C7844(pNode, pTree);
    pItem = SPLAY_ITEM(pNode);
    if (pTree->mBase.mCompare(SPLAY_ITEM(pTree->mpRoot), pItem) == 0) {
        pRoot = pTree->mpRoot;
        if (pRoot->mpLeft == pTree->mpNil) {
            pTree->mpRoot = pRoot->mpRight;
        } else {
            pTree->mpRoot = pRoot->mpLeft;
            pTree->mpRoot = fn_801C7844(pNode, pTree);
            pTree->mpRoot->mpRight = pRoot->mpRight;
        }
        pTree->mBase.mCount--;
    }
}

static int fn_801C7E00(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode, int a, int b,
                       VisitFn_801C7684 callback, int direction)
{
    int result;

    if (direction < 0) {
        result = fn_801C7730(pTree, pNode, a, b, callback);
    } else {
        result = fn_801C7684(pTree, pNode, a, b, callback);
    }
    return result;
}

static int fn_801C7E30(SplayTree_801C7684 *pTree, SplayNode_801C7684 *pNode, int a, int b,
                       VisitFn_801C7684 callback)
{
    SplayNode_801C7684 *pCur = pTree->mpRoot;
    int result = -1;
    int cmp;

    do {
        cmp = -callback(pCur ? (char *)pCur + lbl_803D4FB8[2].mNodeSize : 0, a, b);
        if (cmp < 0) {
            if (pCur->mpLeft == pTree->mpNil) {
                result = 3;
            }
            pCur = pCur->mpLeft;
        } else if (cmp > 0) {
            if (pCur->mpRight == pTree->mpNil) {
                result = 3;
            }
            pCur = pCur->mpRight;
        } else {
            result = 2;
        }
    } while (result == -1);
    return result;
}

static int fn_801C7EDC(SplayTree_801C7684 *pTree)
{
    return 0;
}

void fn_801C7EE4(void)
{
    fn_801C67AC(2, (void (*)(List_801C68FC *))fn_801C7A34, (int (*)(List_801C68FC *))fn_801C7A60,
                (void (*)(Node_801C6A20 *, int))fn_801C7C1C,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) fn_801C7A98,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) fn_801C7C44,
                (void (*)(List_801C68FC *, Node_801C6A20 *))fn_801C7D1C,
                (int (*)(List_801C68FC *, Node_801C6A20 *, int, int, int, int))fn_801C7E00,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, void *))fn_801C7E30,
                (void (*)(List_801C68FC *))fn_801C7EDC, sizeof(SplayTree_801C7684), sizeof(SplayNode_801C7684));
}
