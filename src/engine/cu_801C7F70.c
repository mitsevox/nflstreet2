#include "engine/cu_801C665C.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"


typedef int (*VisitFn_801C7F70)(void *, int, int);

/* Node flag bits (low byte of BinNode_801C7F70.mFlags). */
#define BIN_LEFT_THREAD 0x1
#define BIN_RIGHT_THREAD 0x2
#define BIN_FIRST 0x4
#define BIN_LAST 0x8
#define BIN_IS_LEFT 0x10
#define BIN_IS_RIGHT 0x20

#define BIN_NODE_SIZE (lbl_803D4FB8[1].mNodeSize)
#define BIN_ITEM(pNode) ((pNode) ? (char *)(pNode) + BIN_NODE_SIZE : 0)

extern BinNode_801C7F70 lbl_8037F880;

void fn_801C8298(BinTree_801C7F70 *pTree, BinNode_801C7F70 **ppNodes, int count);
void fn_801C87C0(BinTree_801C7F70 *pTree);
static BinNode_801C7F70 *fn_801C819C(BinNode_801C7F70 *pNode);
static BinNode_801C7F70 *fn_801C81E0(BinNode_801C7F70 *pNode);
static BinNode_801C7F70 *fn_801C8834(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, int mode);
static BinNode_801C7F70 *fn_801C89D4(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, unsigned int mode);
static int fn_801C8C44(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, int a, int b,
                       VisitFn_801C7F70 callback, int direction);
static int fn_801C8D38(BinTree_801C7F70 *pTree, int force, int enable, float avgLimit, float depthLimit);

static int fn_801C7F70(BinNode_801C7F70 *pNode, int a, int b, VisitFn_801C7F70 callback)
{
    BinNode_801C7F70 *pNext;
    int done = 0;
    int result;

    do {
        pNext = fn_801C81E0(pNode);
        result = callback(BIN_ITEM(pNode), a, b);
        if (result == 0 || (pNode->mFlags & BIN_LAST)) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static int fn_801C8014(BinNode_801C7F70 *pNode, int a, int b, VisitFn_801C7F70 callback)
{
    BinNode_801C7F70 *pNext;
    int done = 0;
    int result;

    do {
        pNext = fn_801C819C(pNode);
        result = callback(BIN_ITEM(pNode), a, b);
        if (result == 0 || (pNode->mFlags & BIN_FIRST)) {
            done = 1;
        }
        pNode = pNext;
    } while (!done);
    return result == 0 ? 4 : 0;
}

static void fn_801C80B8(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pParent, BinNode_801C7F70 *pNode, int cmp)
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

static BinNode_801C7F70 *fn_801C819C(BinNode_801C7F70 *pNode)
{
    BinNode_801C7F70 *pPrev;

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

static BinNode_801C7F70 *fn_801C81E0(BinNode_801C7F70 *pNode)
{
    BinNode_801C7F70 *pNext;

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

static BinNode_801C7F70 *fn_801C8224(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode)
{
    BinNode_801C7F70 *pParent;

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
        lbl_8037F880.mFlags = 0;
        lbl_8037F880.mpLeft = pNode;
        lbl_8037F880.mpRight = pNode;
        pParent = &lbl_8037F880;
    }
    return pParent;
}

static int fn_801C82E0(void *pItem, BinNode_801C7F70 **ppNodes, int *pIndex)
{
    ppNodes[*pIndex] = pItem ? (BinNode_801C7F70 *)((char *)pItem - lbl_803D4FB8[1].mNodeSize) : 0;
    (*pIndex)++;
    return 1;
}

static void fn_801C831C(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode)
{
    fn_801C8834(pTree, pNode, 0);
}

static void fn_801C8340(BinTree_801C7F70 *pTree, BinNode_801C7F70 **ppNodes, unsigned int lo, unsigned int hi)
{
    unsigned int span = hi - lo;
    unsigned int mid = span / 2 + lo;

    if (span > 1) {
        fn_801C831C(pTree, ppNodes[mid]);
        fn_801C8340(pTree, ppNodes, lo, mid - 1);
        fn_801C8340(pTree, ppNodes, mid + 1, hi);
    } else if (span == 1) {
        fn_801C831C(pTree, ppNodes[lo]);
        fn_801C831C(pTree, ppNodes[hi]);
    } else {
        fn_801C831C(pTree, ppNodes[lo]);
    }
}

static int fn_801C83FC(BinTree_801C7F70 *pTree)
{
    BinNode_801C7F70 **ppNodes;
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
        fn_801C8C44(pTree, fn_801C89D4(pTree, 0, 0), (int)ppNodes, (int)&index,
                    (VisitFn_801C7F70)fn_801C82E0, 1);
        autoOptimize = pTree->mAutoOptimize;
        fn_801C8298(pTree, ppNodes, count);
        fn_801C8340(pTree, ppNodes, 0, index - 1);
        pTree->mAutoOptimize = autoOptimize;
        if (pTree->mppScratch == 0) {
            result = fn_801D2BD0(ppNodes) == 0;
        } else {
            result = 1;
        }
    }
    return result;
}

static unsigned int fn_801C84EC(unsigned int count)
{
    unsigned int depth = 1;

    while (count >>= 1) {
        depth++;
    }
    return depth;
}

static BinNode_801C7F70 *fn_801C850C(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, BinNode_801C7F70 *pParent,
                                     BinNode_801C7F70 *pPrev, BinNode_801C7F70 *pNext)
{
    BinNode_801C7F70 *pPrevParent = fn_801C8224(pTree, pPrev);

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

static BinNode_801C7F70 *fn_801C8650(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, BinNode_801C7F70 *pParent,
                                     BinNode_801C7F70 *pPrev, BinNode_801C7F70 *pNext)
{
    BinNode_801C7F70 *pNextParent = fn_801C8224(pTree, pNext);

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
        } else {
            pNextParent->mFlags |= BIN_LEFT_THREAD;
            pNextParent->mpLeft = pNext;
        }
        pNext->mFlags = pNode->mFlags;
        pNext->mpLeft = pNode->mpLeft;
        pNext->mpRight = pNode->mpRight;
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

static BinNode_801C7F70 *fn_801C8770(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, BinNode_801C7F70 *pParent)
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

static int fn_801C87DC(BinTree_801C7F70 *pTree)
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

static BinNode_801C7F70 *fn_801C8834(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, int mode)
{
    BinNode_801C7F70 *pResult = pNode;
    BinNode_801C7F70 *pCur;
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
        fn_801C80B8(pTree, pCur, pNode, cmp);
        pNode->mDepth = depth;
        if (depth > pTree->mMaxDepth) {
            pTree->mMaxDepth = depth;
        }
        pTree->mTotalDepth += depth;
        if (pTree->mAutoOptimize) {
            fn_801C8D38(pTree, 0, 1, pTree->mAvgLimit, pTree->mDepthLimit);
        }
    } else {
        pResult = pCur;
    }
    return pResult;
}

static void fn_801C89AC(BinNode_801C7F70 *pNode, int size)
{
    fn_801C1F94(pNode, 0, size);
}

static BinNode_801C7F70 *fn_801C89D4(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, unsigned int mode)
{
    BinNode_801C7F70 *pResult = pNode;

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
            pResult = fn_801C819C(pResult);
            break;
        case 4:
            pResult = fn_801C81E0(pResult);
            break;
        default:
            pResult = pNode ? (BinNode_801C7F70 *)((char *)pNode - lbl_803D4FB8[1].mNodeSize) : 0;
            break;
        }
    } else {
        pResult = 0;
    }
    return pResult;
}

static void fn_801C8AB4(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode)
{
    BinNode_801C7F70 *pPrev = fn_801C819C(pNode);
    BinNode_801C7F70 *pNext = fn_801C81E0(pNode);
    BinNode_801C7F70 *pParent = fn_801C8224(pTree, pNode);

    /* pNext becomes the replacement node, or the parent when a leaf is removed; pPrev is reused for the
       first node only when the root is removed. */
    if (!(pNode->mFlags & BIN_LEFT_THREAD)) {
        pNext = fn_801C850C(pTree, pNode, pParent, pPrev, pNext);
    } else if (!(pNode->mFlags & BIN_RIGHT_THREAD)) {
        pNext = fn_801C8650(pTree, pNode, pParent, pPrev, pNext);
    } else if (pNode != pTree->mpRoot) {
        pNext = fn_801C8770(pTree, pNode, pParent);
    } else {
        pNext = 0;
    }
    if (pNode == pTree->mpRoot) {
        pTree->mpRoot = pNext;
        if (pNext) {
            pPrev = fn_801C89D4(pTree, pNode, 0);
            pParent = fn_801C89D4(pTree, pNode, 1);
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
        fn_801C8D38(pTree, 0, 1, pTree->mAvgLimit, pTree->mDepthLimit);
    }
}

static int fn_801C8C44(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, int a, int b,
                       VisitFn_801C7F70 callback, int direction)
{
    int result;

    if (direction < 0) {
        result = fn_801C8014(pNode, a, b, callback);
    } else {
        result = fn_801C7F70(pNode, a, b, callback);
    }
    return result;
}

static int fn_801C8C84(BinTree_801C7F70 *pTree, BinNode_801C7F70 *pNode, int a, int b,
                       VisitFn_801C7F70 callback)
{
    BinNode_801C7F70 *pCur = pTree->mpRoot;
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

static int fn_801C8D38(BinTree_801C7F70 *pTree, int force, int enable, float avgLimit, float depthLimit)
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
        optimal = fn_801C84EC(count);
        avgDepth = avgDepth - optimal + 1.0f;
        maxDepth = maxDepth - optimal;
        if (force || avgDepth >= avgLimit || !(maxDepth < depthLimit)) {
            if (fn_801C83FC(pTree)) {
                result = 0;
            }
        }
    } else if (count == 0) {
        result = 1;
    }
    return result;
}

void fn_801C8E88(void)
{
    fn_801C67AC(1, (void (*)(List_801C68FC *))fn_801C87C0, (int (*)(List_801C68FC *))fn_801C87DC,
                (void (*)(Node_801C6A20 *, int))fn_801C89AC,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) fn_801C8834,
                (Node_801C6A20 * (*)(List_801C68FC *, Node_801C6A20 *, int)) fn_801C89D4,
                (void (*)(List_801C68FC *, Node_801C6A20 *))fn_801C8AB4,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, int, ListVisitFn_801C6D34, int))fn_801C8C44,
                (int (*)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC))fn_801C8C84,
                (void (*)(List_801C68FC *))fn_801C8D38, sizeof(BinTree_801C7F70), sizeof(BinNode_801C7F70));
}
