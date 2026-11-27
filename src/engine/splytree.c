/* Splay-tree list type (list type 2) of the engine's generic list library: self-adjusting
   ordered trees that game and engine code use as sorted containers through the DS list calls. */
#include "engine/list.h"
#include "game/fn_801D2B7C.h"
#include <string.h>

typedef int (*SplayVisitFn_t)(void *, int, int);

#define SPLAY_NODE_SIZE (DSList_Interface[2].mNodeSize)
#define SPLAY_ITEM(pNode) ((pNode) ? (char *)(pNode) + SPLAY_NODE_SIZE : 0)

SplayNode_t *_DSListGetSplayPrev(SplayTree_t *pTree, SplayNode_t *pNode);
SplayNode_t *_DSListGetSplayNext(SplayTree_t *pTree, SplayNode_t *pNode);

static int _DSListTraverseSplayTreeRight(SplayTree_t *pTree, SplayNode_t *pNode, int a, int b,
                       SplayVisitFn_t callback)
{
    SplayNode_t *pNext;
    int done = 0;
    int result;

    do {
        pNext = _DSListGetSplayNext(pTree, pNode);
        result = callback(SPLAY_ITEM(pNode), a, b);
        if (result == 0 || pNext == pTree->mpNil) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static int _DSListTraverseSplayTreeLeft(SplayTree_t *pTree, SplayNode_t *pNode, int a, int b,
                       SplayVisitFn_t callback)
{
    SplayNode_t *pNext;
    int done = 0;
    int result;

    do {
        pNext = _DSListGetSplayPrev(pTree, pNode);
        result = callback(SPLAY_ITEM(pNode), a, b);
        if (result == 0 || pNext != pTree->mpNil) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

SplayNode_t *_DSListGetSplayPrev(SplayTree_t *pTree, SplayNode_t *pNode)
{
    SplayNode_t *pChild = pNode->mpLeft;
    SplayNode_t *pNil = pTree->mpNil;

    // FAKEMATCH: dead increment of pTree (unused afterwards). flow deletes it, but the branch
    // stays a block boundary through register allocation, so the child load keeps its own
    // register (r0) and is copied to the result (r3) after the sentinel load, as in the target.
    if (pChild != 0) {
        pTree++;
    }
    pNode = pChild;
    if (pNode != pNil) {
        while (pNode->mpRight != pNil) {
            pNode = pNode->mpRight;
        }
    }
    return pNode;
}

SplayNode_t *_DSListGetSplayNext(SplayTree_t *pTree, SplayNode_t *pNode)
{
    SplayNode_t *pChild = pNode->mpRight;
    SplayNode_t *pNil = pTree->mpNil;

    // FAKEMATCH: dead increment of pTree (unused afterwards). flow deletes it, but the branch
    // stays a block boundary through register allocation, so the child load keeps its own
    // register (r0) and is copied to the result (r3) after the sentinel load, as in the target.
    if (pChild != 0) {
        pTree++;
    }
    pNode = pChild;
    if (pNode != pNil) {
        while (pNode->mpLeft != pNil) {
            pNode = pNode->mpLeft;
        }
    }
    return pNode;
}

static SplayNode_t *_DSListSplay(SplayNode_t *pNode, SplayTree_t *pTree)
{
    SplayNode_t header;
    SplayNode_t *pLeft;
    SplayNode_t *pRight;
    SplayNode_t *pChild;
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

static void _DSListInitSplayTree(SplayTree_t *pTree)
{
    pTree->mBase.mCount = 0;
    pTree->mpNil = &pTree->mNil;
    pTree->mpNil->mpLeft = pTree->mpNil->mpRight = &pTree->mNil;
    pTree->mpFirst = pTree->mpLast = pTree->mpRoot = pTree->mpNil;
}

static int _DSListDelSplayTree(SplayTree_t *pTree)
{
    int result = 0;

    if (pTree->mBase.mHeap) {
        result = fn_801D2BD0(pTree);
    }
    return result;
}

static SplayNode_t *_DSListAddSplayNode(SplayTree_t *pTree, SplayNode_t *pNode, int mode)
{
    SplayNode_t *pResult = pNode;
    SplayNode_t *pRoot;
    void *pItem;
    int cmp;

    pItem = SPLAY_ITEM(pNode);
    pRoot = pTree->mpRoot;
    if (pTree->mBase.mCompare && pRoot) {
        if (pRoot == pTree->mpNil) {
            pNode->mpLeft = pNode->mpRight = pRoot;
            pTree->mpFirst = pTree->mpLast = pTree->mpRoot = pNode;
        } else {
            pTree->mpRoot = _DSListSplay(pNode, pTree);
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

static void _DSListInitSplayNode(SplayNode_t *pNode, int size)
{
    memset(pNode, 0, size);
}

static SplayNode_t *_DSListGetSplayNode(SplayTree_t *pTree, SplayNode_t *pNode, unsigned int mode)
{
    SplayNode_t *pResult = pNode;

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
            pResult = _DSListGetSplayPrev(pTree, pResult);
            break;
        case 4:
            pResult = _DSListGetSplayNext(pTree, pResult);
            break;
        default:
            pResult = pNode ? (SplayNode_t *)((char *)pNode - SPLAY_NODE_SIZE) : 0;
            break;
        }
    }
    if (pResult == pTree->mpNil) {
        pResult = 0;
    }
    return pResult;
}

static void _DSListRemoveSplayNode(SplayTree_t *pTree, SplayNode_t *pNode)
{
    SplayNode_t *pRoot;
    void *pItem;

    if (pTree->mpRoot == pTree->mpNil) {
        return;
    }
    pTree->mpRoot = _DSListSplay(pNode, pTree);
    pItem = SPLAY_ITEM(pNode);
    if (pTree->mBase.mCompare(SPLAY_ITEM(pTree->mpRoot), pItem) == 0) {
        pRoot = pTree->mpRoot;
        if (pRoot->mpLeft == pTree->mpNil) {
            pTree->mpRoot = pRoot->mpRight;
        } else {
            pTree->mpRoot = pRoot->mpLeft;
            pTree->mpRoot = _DSListSplay(pNode, pTree);
            pTree->mpRoot->mpRight = pRoot->mpRight;
        }
        pTree->mBase.mCount--;
    }
}

static int _DSListTraverseSplayTree(SplayTree_t *pTree, SplayNode_t *pNode, int a, int b,
                       SplayVisitFn_t callback, int direction)
{
    int result;

    if (direction < 0) {
        result = _DSListTraverseSplayTreeLeft(pTree, pNode, a, b, callback);
    } else {
        result = _DSListTraverseSplayTreeRight(pTree, pNode, a, b, callback);
    }
    return result;
}

static int _DSListSearchSplayTree(SplayTree_t *pTree, SplayNode_t *pNode, int a, int b,
                       SplayVisitFn_t callback)
{
    SplayNode_t *pCur = pTree->mpRoot;
    int result = -1;
    int cmp;

    do {
        cmp = -callback(pCur ? (char *)pCur + DSList_Interface[2].mNodeSize : 0, a, b);
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

static int _DSListOptimizeSplayTree(SplayTree_t *pTree)
{
    return 0;
}

void DSListInitSplayTreeModule(void)
{
    DSAddListType(2, (void (*)(DSList_t *))_DSListInitSplayTree, (int (*)(DSList_t *))_DSListDelSplayTree,
                (void (*)(DSListNode_t *, int))_DSListInitSplayNode,
                (DSListNode_t * (*)(DSList_t *, DSListNode_t *, int)) _DSListAddSplayNode,
                (DSListNode_t * (*)(DSList_t *, DSListNode_t *, int)) _DSListGetSplayNode,
                (void (*)(DSList_t *, DSListNode_t *))_DSListRemoveSplayNode,
                (int (*)(DSList_t *, DSListNode_t *, void *, void *, DSListVisitFn_t, int))_DSListTraverseSplayTree,
                (int (*)(DSList_t *, DSListNode_t *, void *, void *, DSListSearchFn_t))_DSListSearchSplayTree,
                (void (*)(DSList_t *))_DSListOptimizeSplayTree, sizeof(SplayTree_t), sizeof(SplayNode_t));
}
