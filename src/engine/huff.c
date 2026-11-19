/* Huffman codec for the compression library: builds the code tree from symbol counts and encodes or
   decodes a byte stream bit by bit. */

#include "engine/GCmp.h"
#include "engine/dslist.h"

/* 12-byte tree node. */
typedef struct HuffNode_t {
    unsigned char mSymbol;
    struct HuffNode_t *mpLeft;
    struct HuffNode_t *mpRight;
} HuffNode_t;

/* Pool item ordered by _InsertSortByFreq. */
typedef struct HuffItem_t {
    int mCount;
    HuffNode_t *mpNode;
} HuffItem_t;

/* 12-byte coder state allocated by _HuffCoStart and _HuffDecStart. */
typedef struct HuffState_t {
    HuffNode_t *mpRoot;
    unsigned char mBits;
    unsigned char mBitCount;
    int mRemaining;
} HuffState_t;

extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern unsigned int DSGetListStat(void *pool, int c);
extern void *DSNewListNode(void *pool);
extern void *DSGetListNode(void *pool, void *item);
extern void DSRemoveListNode(void *pool, void *item);
extern void *DSNextListNode(void *pool, void *item);
extern int DSSearchList(void *pool, void *start, void *key, void *pFound,
                       int (*match)(void *, void *, void *));

int _InsertSortByFreq(void *a, void *b)
{
    HuffItem_t *pA = a;
    HuffItem_t *pB = b;

    return pA->mCount - pB->mCount;
}

int _SearchForSymbol(void *item, void *key, void *pFound)
{
    HuffItem_t *pItem = item;
    HuffNode_t *pNode = pItem->mpNode;

    if (pNode->mpLeft == 0 && pNode->mpRight == 0 && pNode->mSymbol == *(unsigned char *)key) {
        *(HuffItem_t **)pFound = pItem;
        return 0;
    }
    return -1;
}

int _IsSymbolInTree(HuffNode_t *pNode, int symbol)
{
    if (pNode->mpLeft == 0 && pNode->mpRight == 0) {
        return pNode->mSymbol == symbol;
    }
    if (_IsSymbolInTree(pNode->mpLeft, symbol) || _IsSymbolInTree(pNode->mpRight, symbol)) {
        return 1;
    }
    return 0;
}

HuffNode_t *_BuildTree(void *pool)
{
    HuffItem_t *pItem;
    HuffItem_t *pChild;
    HuffNode_t *pRoot;

    while (DSGetListStat(pool, 3) > 1) {
        pItem = DSNewListNode(pool);
        pItem->mpNode = fn_801D2BB0(1, sizeof(HuffNode_t), 0, 0);
        pChild = DSGetListNode(pool, 0);
        pItem->mpNode->mpLeft = pChild->mpNode;
        pItem->mCount = pChild->mCount;
        DSRemoveListNode(pool, pChild);
        pChild = DSGetListNode(pool, 0);
        pItem->mpNode->mpRight = pChild->mpNode;
        pItem->mCount += pChild->mCount;
        DSRemoveListNode(pool, pChild);
        pItem->mpNode->mSymbol = 0;
        DSAddListNode(pool, pItem, 0);
    }
    pChild = DSGetListNode(pool, 0);
    pRoot = pChild->mpNode;
    DSRemoveListNode(pool, pChild);
    return pRoot;
}

void _DestroyTree(HuffNode_t *pNode)
{
    if (pNode->mpLeft != 0) {
        _DestroyTree(pNode->mpLeft);
    }
    if (pNode->mpRight != 0) {
        _DestroyTree(pNode->mpRight);
    }
    fn_801D2BD0(pNode);
}

HuffState_t *_HuffCoStart(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    HuffItem_t *pItem = 0;
    unsigned char symbol;
    unsigned short count;
    HuffState_t *pState;
    void *pool;
    int index;

    pState = fn_801D2BB0(1, sizeof(HuffState_t), 0, 0);
    pool = DSNewList(1, 0, 2056, sizeof(HuffItem_t), _InsertSortByFreq, 0);
    while (GCmpRead(pSrc, &symbol, 1)) {
        pItem = 0;
        if (DSSearchList(pool, 0, &symbol, &pItem, _SearchForSymbol) == 2) {
            DSRemoveListNode(pool, pItem);
            pItem->mCount++;
            DSAddListNode(pool, pItem, 0);
        } else {
            pItem = DSNewListNode(pool);
            pItem->mCount = 1;
            pItem->mpNode = fn_801D2BB0(1, sizeof(HuffNode_t), 0, 0);
            pItem->mpNode->mSymbol = symbol;
            pItem->mpNode->mpLeft = pItem->mpNode->mpRight = 0;
            DSAddListNode(pool, pItem, 0);
        }
    }
    pSrc->mPos = 0;
    GCmpWrite(pDst, &pSrc->mSize, 4);
    index = 0;
    count = DSGetListStat(pool, 3);
    GCmpWrite(pDst, &count, 2);
    for (pItem = DSGetListNode(pool, 0); pItem != 0; pItem = DSNextListNode(pool, pItem)) {
        GCmpWrite(pDst, pItem->mpNode, 1);
        pItem->mCount = index;
        index++;
    }
    pState->mpRoot = _BuildTree(pool);
    DSDelList(pool);
    pState->mBits = 0;
    pState->mBitCount = 0;
    return pState;
}

int _HuffCoProcess(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, HuffState_t *pState)
{
    unsigned char symbol;
    HuffNode_t *pNode;

    if (GCmpRead(pSrc, &symbol, 1) != 0) {
        pNode = pState->mpRoot;
        while (pNode->mpLeft != 0 || pNode->mpRight != 0) {
            if (_IsSymbolInTree(pNode->mpRight, symbol)) {
                pState->mBits |= 1 << pState->mBitCount;
                pNode = pNode->mpRight;
            } else {
                pNode = pNode->mpLeft;
            }
            if (++pState->mBitCount > 7) {
                GCmpWrite(pDst, &pState->mBits, 1);
                pState->mBits = 0;
                pState->mBitCount = 0;
            }
        }
        return 0;
    }
    return 1;
}

void _HuffCoStop(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, HuffState_t *pState)
{
    if (pState->mBitCount != 0) {
        GCmpWrite(pDst, &pState->mBits, 1);
    }
    _DestroyTree(pState->mpRoot);
    fn_801D2BD0(pState);
}

HuffState_t *_HuffDecStart(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    unsigned short count;
    unsigned int i = 0;
    HuffState_t *pState;
    void *pool;
    HuffItem_t *pItem;

    pState = fn_801D2BB0(1, sizeof(HuffState_t), 0, 0);
    pool = DSNewList(1, 0, 2056, sizeof(HuffItem_t), _InsertSortByFreq, 0);
    GCmpRead(pSrc, &pState->mRemaining, 4);
    GCmpRead(pSrc, &count, 2);
    for (; i < count; i++) {
        pItem = DSNewListNode(pool);
        pItem->mpNode = fn_801D2BB0(1, sizeof(HuffNode_t), 0, 0);
        GCmpRead(pSrc, pItem->mpNode, 1);
        pItem->mCount = i;
        pItem->mpNode->mpLeft = pItem->mpNode->mpRight = 0;
        DSAddListNode(pool, pItem, 0);
    }
    pState->mpRoot = _BuildTree(pool);
    DSDelList(pool);
    pState->mBits = 0;
    pState->mBitCount = 0;
    return pState;
}

int _HuffDecProcess(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, HuffState_t *pState)
{
    HuffNode_t *pNode = pState->mpRoot;

    while (pNode->mpLeft != 0 || pNode->mpRight != 0) {
        if (pState->mBitCount == 0) {
            GCmpRead(pSrc, &pState->mBits, 1);
            pState->mBitCount = 8;
        }
        if (pState->mBits & 1) {
            pNode = pNode->mpRight;
        } else {
            pNode = pNode->mpLeft;
        }
        pState->mBits >>= 1;
        pState->mBitCount--;
    }
    GCmpWrite(pDst, pNode, 1);
    return --pState->mRemaining == 0;
}

void _HuffDecStop(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, HuffState_t *pState)
{
    _DestroyTree(pState->mpRoot);
    fn_801D2BD0(pState);
}
