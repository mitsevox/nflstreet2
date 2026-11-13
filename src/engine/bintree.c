/* Threaded binary search tree list type (list type 1): ordered insert, remove, lookup, in-order traversal and
   rebalancing of the tree when it grows too deep, registered with the generic list module. */
#include "engine/list.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"


typedef int (*BinVisitFn_t)(void *, int, int);

/* Node flag bits (low byte of BinNode_t.mFlags). */
#define BIN_LEFT_THREAD 0x1
#define BIN_RIGHT_THREAD 0x2
#define BIN_FIRST 0x4
#define BIN_LAST 0x8
#define BIN_IS_LEFT 0x10
#define BIN_IS_RIGHT 0x20

#define BIN_NODE_SIZE (lbl_803D4FB8[1].mNodeSize)
#define BIN_ITEM(pNode) ((pNode) ? (char *)(pNode) + BIN_NODE_SIZE : 0)

static void _DSListResetBinaryTree(BinTree_t *pTree, BinNode_t **ppNodes, int count);
static void _DSListInitBinaryTree(BinTree_t *pTree);
static BinNode_t *_DSListGetBinaryPrev(BinNode_t *pNode);
static BinNode_t *_DSListGetBinaryNext(BinNode_t *pNode);
static BinNode_t *_DSListAddBinaryNode(BinTree_t *pTree, BinNode_t *pNode, int mode);
static BinNode_t *_DSListGetBinaryNode(BinTree_t *pTree, BinNode_t *pNode, unsigned int mode);
static int _DSListTraverseBinaryTree(BinTree_t *pTree, BinNode_t *pNode, int a, int b,
                       BinVisitFn_t callback, int direction);
static int _DSListOptimizeBinaryTree(BinTree_t *pTree, float avgLimit, int force, float depthLimit, int enable);

static int _DSListTraverseBinaryTreeRight(BinNode_t *pNode, int a, int b, BinVisitFn_t callback)
{
    BinNode_t *pNext;
    int done = 0;
    int result;

    do {
        pNext = _DSListGetBinaryNext(pNode);
        result = callback(BIN_ITEM(pNode), a, b);
        if (result == 0 || (pNode->mFlags & BIN_LAST)) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static int _DSListTraverseBinaryTreeLeft(BinNode_t *pNode, int a, int b, BinVisitFn_t callback)
{
    BinNode_t *pNext;
    int done = 0;
    int result;

    do {
        pNext = _DSListGetBinaryPrev(pNode);
        result = callback(BIN_ITEM(pNode), a, b);
        if (result == 0 || (pNode->mFlags & BIN_FIRST)) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static void _DSListInsertBinaryNode(BinTree_t *pTree, BinNode_t *pParent, BinNode_t *pNode, int cmp)
{
    pNode->mFlags = 0x80000000;
    if (pParent) {
        if (cmp < 0) {
            pNode->mpLeft = pParent->mpLeft;
            pParent->mpLeft = pNode;
            pParent->mFlags &= ~BIN_LEFT_THREAD;
            pNode->mpRight = pParent;
            pNode->mFlags |= pParent->mFlags & BIN_FIRST;
            pParent->mFlags &= ~BIN_FIRST;
            pNode->mFlags |= BIN_IS_LEFT;
        } else {
            pNode->mpRight = pParent->mpRight;
            pParent->mpRight = pNode;
            pParent->mFlags &= ~BIN_RIGHT_THREAD;
            pNode->mpLeft = pParent;
            pNode->mFlags |= pParent->mFlags & BIN_LAST;
            pParent->mFlags &= ~BIN_LAST;
            pNode->mFlags |= BIN_IS_RIGHT;
        }
    } else {
        pTree->mpRoot = pNode;
        pNode->mpRight = pNode;
        pNode->mpLeft = pNode;
        pNode->mFlags |= BIN_FIRST | BIN_LAST;
    }
    pNode->mFlags |= BIN_LEFT_THREAD | BIN_RIGHT_THREAD;
    pTree->mBase.mCount++;
}

static BinNode_t *_DSListGetBinaryPrev(BinNode_t *pNode)
{
    BinNode_t *pPrev;

    if (!(pNode->mFlags & BIN_FIRST)) {
        pPrev = pNode->mpLeft;
        if (!((unsigned char)pNode->mFlags & BIN_LEFT_THREAD)) {
            while (!(pPrev->mFlags & BIN_RIGHT_THREAD)) {
                pPrev = pPrev->mpRight;
            }
        }
        return pPrev;
    }
    return 0;
}

static BinNode_t *_DSListGetBinaryNext(BinNode_t *pNode)
{
    BinNode_t *pNext;

    if (!(pNode->mFlags & BIN_LAST)) {
        pNext = pNode->mpRight;
        if (!((unsigned char)pNode->mFlags & BIN_RIGHT_THREAD)) {
            while (!(pNext->mFlags & BIN_LEFT_THREAD)) {
                pNext = pNext->mpLeft;
            }
        }
        return pNext;
    }
    return 0;
}

static BinNode_t *_DSListGetBinaryParent(BinTree_t *pTree, BinNode_t *pNode)
{
    static BinNode_t _FakeNode;
    BinNode_t *pParent;

    if (pNode != pTree->mpRoot) {
        pParent = pNode;
        if (pParent->mFlags & BIN_IS_LEFT) {
            while (!(pParent->mFlags & BIN_RIGHT_THREAD)) {
                pParent = pParent->mpRight;
            }
            pParent = pParent->mpRight;
        } else {
            while (!(pParent->mFlags & BIN_LEFT_THREAD)) {
                pParent = pParent->mpLeft;
            }
            pParent = pParent->mpLeft;
        }
    } else {
        _FakeNode.mFlags = 0;
        _FakeNode.mpLeft = pNode;
        _FakeNode.mpRight = pNode;
        pParent = &_FakeNode;
    }
    return pParent;
}

static void _DSListResetBinaryTree(BinTree_t *pTree, BinNode_t **ppNodes, int count)
{
    int i;

    pTree->mpRoot = 0;
    pTree->mBase.mCount = 0;
    pTree->mMaxDepth = 0;
    pTree->mTotalDepth = 0;
    pTree->mAutoOptimize = 0;
    for (i = 0; i < count; i++) {
        ppNodes[i]->mFlags = 0x80000000;
        ppNodes[i]->mDepth = 0;
    }
}

static int _DSListOptTrvFunc(void *pItem, BinNode_t **ppNodes, int *pIndex)
{
    ppNodes[*pIndex] = pItem ? (BinNode_t *)((char *)pItem - lbl_803D4FB8[1].mNodeSize) : 0;
    (*pIndex)++;
    return 1;
}

static void _DSListAddBinNodeOpt(BinTree_t *pTree, BinNode_t *pNode)
{
    _DSListAddBinaryNode(pTree, pNode, 0);
}

static void _DSListAddBinTreeOpt(BinTree_t *pTree, BinNode_t **ppNodes, unsigned int lo, unsigned int hi)
{
    unsigned int span = hi - lo;
    unsigned int mid = span / 2 + lo;

    if (span > 1) {
        _DSListAddBinNodeOpt(pTree, ppNodes[mid]);
        _DSListAddBinTreeOpt(pTree, ppNodes, lo, mid - 1);
        _DSListAddBinTreeOpt(pTree, ppNodes, mid + 1, hi);
    } else if (span == 1) {
        _DSListAddBinNodeOpt(pTree, ppNodes[lo]);
        _DSListAddBinNodeOpt(pTree, ppNodes[hi]);
    } else {
        _DSListAddBinNodeOpt(pTree, ppNodes[lo]);
    }
}

static int _DSListDoOptBinaryTree(BinTree_t *pTree)
{
    BinNode_t **ppNodes;
    int count;
    int index = 0;
    int result = 0;
    unsigned char autoOptimize;

    count = pTree->mBase.mCount;
    if (pTree->mppScratch == 0) {
        ppNodes = fn_801D2BB0(1, (count + 1) * 4, 0, 0);
    } else {
        ppNodes = pTree->mppScratch;
    }
    if (ppNodes) {
        _DSListTraverseBinaryTree(pTree, _DSListGetBinaryNode(pTree, 0, 0), (int)ppNodes, (int)&index,
                    (BinVisitFn_t)_DSListOptTrvFunc, 1);
        autoOptimize = pTree->mAutoOptimize;
        _DSListResetBinaryTree(pTree, ppNodes, count);
        _DSListAddBinTreeOpt(pTree, ppNodes, 0, index - 1);
        pTree->mAutoOptimize = autoOptimize;
        if (pTree->mppScratch == 0) {
            result = fn_801D2BD0(ppNodes) == 0;
        } else {
            result = 1;
        }
    }
    return result;
}

static unsigned int _DSListCalcOptimalDepth(unsigned int count)
{
    unsigned int depth = 1;

    while (count >>= 1) {
        depth++;
    }
    return depth;
}

static BinNode_t *_DSListRemoveBinaryNodeLeft(BinTree_t *pTree, BinNode_t *pNode, BinNode_t *pParent,
                                     BinNode_t *pPrev, BinNode_t *pNext)
{
    BinNode_t *pPrevParent = _DSListGetBinaryParent(pTree, pPrev);

    if (pNode->mFlags & BIN_IS_LEFT) {
        pParent->mpLeft = pPrev;
    } else {
        pParent->mpRight = pPrev;
    }
    if (pPrevParent != pNode) {
        if (!(pPrev->mFlags & BIN_LEFT_THREAD)) {
            pPrevParent->mpRight = pPrev->mpLeft;
            pPrevParent->mpRight->mFlags &= ~BIN_IS_LEFT;
            pPrevParent->mpRight->mFlags |= BIN_IS_RIGHT;
        } else {
            pPrevParent->mpRight = pPrev;
            pPrevParent->mFlags |= BIN_RIGHT_THREAD;
        }
        pPrev->mFlags = pNode->mFlags;
        pPrev->mpLeft = pNode->mpLeft;
        pPrev->mpRight = pNode->mpRight;
    } else {
        if (pPrev->mFlags & BIN_IS_LEFT) {
            pPrev->mpRight = pNode->mpRight;
            pPrev->mFlags &= ~(BIN_IS_LEFT | BIN_IS_RIGHT | BIN_RIGHT_THREAD);
            pPrev->mFlags |= pNode->mFlags & BIN_RIGHT_THREAD;
        } else {
            pPrev->mpLeft = pNode->mpLeft;
            pPrev->mFlags &= ~(BIN_IS_LEFT | BIN_IS_RIGHT | BIN_LEFT_THREAD);
            pPrev->mFlags = pPrev->mFlags | (pNode->mFlags & BIN_LEFT_THREAD) | BIN_IS_LEFT;
        }
        pPrev->mFlags |= pNode->mFlags & (BIN_FIRST | BIN_LAST | BIN_IS_LEFT | BIN_IS_RIGHT);
    }
    if (pNext && (pNext->mFlags & BIN_LEFT_THREAD)) {
        pNext->mpLeft = pPrev;
    }
    return pPrev;
}

static BinNode_t *_DSListRemoveBinaryNodeRight(BinTree_t *pTree, BinNode_t *pNode, BinNode_t *pParent,
                                     BinNode_t *pPrev, BinNode_t *pNext)
{
    BinNode_t *pNextParent = _DSListGetBinaryParent(pTree, pNext);

    if (pNode->mFlags & BIN_IS_LEFT) {
        pParent->mpLeft = pNext;
    } else {
        pParent->mpRight = pNext;
    }
    if (pNextParent != pNode) {
        if (!(pNext->mFlags & BIN_RIGHT_THREAD)) {
            pNextParent->mpLeft = pNext->mpRight;
            pNextParent->mpLeft->mFlags &= ~BIN_IS_RIGHT;
            pNextParent->mpLeft->mFlags |= BIN_IS_LEFT;
            pNext->mFlags = pNode->mFlags;
            pNext->mpLeft = pNode->mpLeft;
            pNext->mpRight = pNode->mpRight;
        } else {
            pNextParent->mFlags |= BIN_LEFT_THREAD;
            pNextParent->mpLeft = pNext;
            pNext->mFlags = pNode->mFlags;
            pNext->mpLeft = pNode->mpLeft;
            pNext->mpRight = pNode->mpRight;
        }
    } else {
        if (pNext->mFlags & BIN_IS_LEFT) {
            pNext->mpRight = pNode->mpRight;
            pNext->mFlags &= ~(BIN_IS_LEFT | BIN_IS_RIGHT | BIN_RIGHT_THREAD);
            pNext->mFlags |= pNode->mFlags & BIN_RIGHT_THREAD;
        } else {
            pNext->mpLeft = pNode->mpLeft;
            pNext->mFlags &= ~(BIN_IS_LEFT | BIN_IS_RIGHT | BIN_LEFT_THREAD);
            pNext->mFlags = pNext->mFlags | (pNode->mFlags & BIN_LEFT_THREAD);
        }
        pNext->mFlags |= pNode->mFlags & (BIN_FIRST | BIN_LAST | BIN_IS_LEFT | BIN_IS_RIGHT);
    }
    return pNext;
}

static BinNode_t *_DSListRemoveBinaryLeaf(BinTree_t *pTree, BinNode_t *pNode, BinNode_t *pParent)
{
    if (pNode->mFlags & BIN_IS_LEFT) {
        pParent->mpLeft = pNode->mpLeft;
        pParent->mFlags |= BIN_LEFT_THREAD;
    } else {
        pParent->mpRight = pNode->mpRight;
        pParent->mFlags |= BIN_RIGHT_THREAD;
    }
    pParent->mFlags |= pNode->mFlags & (BIN_FIRST | BIN_LAST);
    return pParent;
}

static void _DSListInitBinaryTree(BinTree_t *pTree)
{
    pTree->mpRoot = 0;
    pTree->mMaxDepth = 0;
    pTree->mTotalDepth = 0;
    pTree->mAutoOptimize = 0;
    pTree->mppScratch = 0;
}

static int _DSListDelBinaryTree(BinTree_t *pTree)
{
    int result = 0;

    if (pTree->mppScratch) {
        fn_801D2BD0(pTree->mppScratch);
    }
    if (pTree->mBase.mHeap) {
        result = fn_801D2BD0(pTree);
    }
    return result;
}

static BinNode_t *_DSListAddBinaryNode(BinTree_t *pTree, BinNode_t *pNode, int mode)
{
    BinNode_t *pResult = pNode;
    BinNode_t *pCur;
    void *pItem;
    void *pCurItem;
    int cmp = 1;
    int found = 0;
    unsigned int depth = 1;

    pItem = BIN_ITEM(pNode);
    pCur = pTree->mpRoot;
    if (pTree->mBase.mCompare && pCur) {
        pCurItem = BIN_ITEM(pCur);
        while (!found) {
            cmp = -pTree->mBase.mCompare(pCurItem, pItem);
            if (cmp < 0) {
                if (!(pCur->mFlags & BIN_LEFT_THREAD)) {
                    pCur = pCur->mpLeft;
                    depth++;
                } else {
                    found = 1;
                }
            } else {
                if (!(pCur->mFlags & BIN_RIGHT_THREAD)) {
                    pCur = pCur->mpRight;
                    depth++;
                } else {
                    found = 1;
                }
            }
            pCurItem = BIN_ITEM(pCur);
        }
    }
    if (mode != 1 || cmp != 0) {
        depth++;
        _DSListInsertBinaryNode(pTree, pCur, pNode, cmp);
        pNode->mDepth = depth;
        if (depth > pTree->mMaxDepth) {
            pTree->mMaxDepth = depth;
        }
        pTree->mTotalDepth += depth;
        if (pTree->mAutoOptimize) {
            _DSListOptimizeBinaryTree(pTree, pTree->mAvgLimit, 0, pTree->mDepthLimit, 1);
        }
    } else {
        pResult = pCur;
    }
    return pResult;
}

static void _DSListInitBinaryNode(BinNode_t *pNode, int size)
{
    fn_801C1F94(pNode, 0, size);
}

static BinNode_t *_DSListGetBinaryNode(BinTree_t *pTree, BinNode_t *pNode, unsigned int mode)
{
    BinNode_t *pResult = pNode;

    if (pTree->mpRoot) {
        switch (mode) {
        case 2:
            pResult = pTree->mpRoot;
            break;
        case 0:
            pResult = pTree->mpRoot;
            while (!(pResult->mFlags & BIN_LEFT_THREAD)) {
                pResult = pResult->mpLeft;
            }
            break;
        case 1:
            pResult = pTree->mpRoot;
            while (!(pResult->mFlags & BIN_RIGHT_THREAD)) {
                pResult = pResult->mpRight;
            }
            break;
        case 3:
            pResult = _DSListGetBinaryPrev(pResult);
            break;
        case 4:
            pResult = _DSListGetBinaryNext(pResult);
            break;
        default:
            pResult = pNode ? (BinNode_t *)((char *)pNode - lbl_803D4FB8[1].mNodeSize) : 0;
            break;
        }
    } else {
        pResult = 0;
    }
    return pResult;
}

static void _DSListRemoveBinaryNode(BinTree_t *pTree, BinNode_t *pNode)
{
    BinNode_t *pPrev = _DSListGetBinaryPrev(pNode);
    BinNode_t *pNext = _DSListGetBinaryNext(pNode);
    BinNode_t *pParent = _DSListGetBinaryParent(pTree, pNode);

    /* pNext becomes the replacement node, or the parent when a leaf is removed; pPrev is reused for the
       first node only when the root is removed. */
    if (!(pNode->mFlags & BIN_LEFT_THREAD)) {
        pNext = _DSListRemoveBinaryNodeLeft(pTree, pNode, pParent, pPrev, pNext);
    } else if (!(pNode->mFlags & BIN_RIGHT_THREAD)) {
        pNext = _DSListRemoveBinaryNodeRight(pTree, pNode, pParent, pPrev, pNext);
    } else if (pNode != pTree->mpRoot) {
        pNext = _DSListRemoveBinaryLeaf(pTree, pNode, pParent);
    } else {
        pNext = 0;
    }
    if (pNode == pTree->mpRoot) {
        pTree->mpRoot = pNext;
        if (pNext) {
            pPrev = _DSListGetBinaryNode(pTree, pNode, 0);
            pParent = _DSListGetBinaryNode(pTree, pNode, 1);
            pPrev->mpLeft = pNext;
            pParent->mpRight = pNext;
            pNext->mFlags |= pNode->mFlags & (BIN_FIRST | BIN_LAST);
        }
    }
    pTree->mBase.mCount--;
    if (pNext) {
        pTree->mTotalDepth -= pNext->mDepth;
        pNext->mDepth = pNode->mDepth;
    } else {
        pTree->mTotalDepth--;
    }
    if (pTree->mAutoOptimize) {
        _DSListOptimizeBinaryTree(pTree, pTree->mAvgLimit, 0, pTree->mDepthLimit, 1);
    }
}

static int _DSListTraverseBinaryTree(BinTree_t *pTree, BinNode_t *pNode, int a, int b,
                       BinVisitFn_t callback, int direction)
{
    int result;

    if (direction < 0) {
        result = _DSListTraverseBinaryTreeLeft(pNode, a, b, callback);
    } else {
        result = _DSListTraverseBinaryTreeRight(pNode, a, b, callback);
    }
    return result;
}

static int _DSListSearchBinaryTree(BinTree_t *pTree, BinNode_t *pNode, int a, int b,
                       BinVisitFn_t callback)
{
    BinNode_t *pCur = pTree->mpRoot;
    int result = -1;
    int cmp;

    do {
        cmp = -callback(BIN_ITEM(pCur), a, b);
        if (cmp < 0) {
            if (pCur->mFlags & BIN_LEFT_THREAD) {
                result = 3;
            }
            pCur = pCur->mpLeft;
        } else if (cmp > 0) {
            if (pCur->mFlags & BIN_RIGHT_THREAD) {
                result = 3;
            }
            pCur = pCur->mpRight;
        } else {
            result = 2;
        }
    } while (result == -1);
    return result;
}

static int _DSListOptimizeBinaryTree(BinTree_t *pTree, float avgLimit, int force, float depthLimit, int enable)
{
    int result = 5;
    unsigned int count;
    float maxDepth;
    float avgDepth;
    float optimal;

    pTree->mAutoOptimize = enable;
    if (enable) {
        pTree->mAvgLimit = avgLimit;
        pTree->mDepthLimit = depthLimit;
    }
    count = pTree->mBase.mCount;
    if (count > 3) {
        maxDepth = pTree->mMaxDepth;
        avgDepth = (float)pTree->mTotalDepth / (float)count;
        optimal = _DSListCalcOptimalDepth(count);
        avgDepth = avgDepth - optimal + 1.0f;
        maxDepth = maxDepth - optimal;
        if (force || avgDepth >= avgLimit || !(maxDepth < depthLimit)) {
            if (_DSListDoOptBinaryTree(pTree)) {
                result = 0;
            }
        }
    } else if (count == 0) {
        result = 1;
    }
    return result;
}

void DSListInitBinTreeModule(void)
{
    fn_801C67AC(1, (void (*)(List_801C68FC *))_DSListInitBinaryTree, (int (*)(List_801C68FC *))_DSListDelBinaryTree,
                (void (*)(Node_801C6A20 *, int))_DSListInitBinaryNode,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) _DSListAddBinaryNode,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) _DSListGetBinaryNode,
                (void (*)(List_801C68FC *, Node_801C6A20 *))_DSListRemoveBinaryNode,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListVisitFn_801C6D34, int))_DSListTraverseBinaryTree,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC))_DSListSearchBinaryTree,
                (void (*)(List_801C68FC *))_DSListOptimizeBinaryTree, sizeof(BinTree_t), sizeof(BinNode_t));
}
