/* Huffman codec for the compression library: builds the code tree from symbol counts and encodes or
   decodes a byte stream bit by bit. */

#include "engine/GCmp.h"
#include "game/fn_801C68FC.h"

/* 12-byte tree node. */
typedef struct Node_8027FB7C {
    unsigned char mSymbol;
    struct Node_8027FB7C *mpLeft;
    struct Node_8027FB7C *mpRight;
} Node_8027FB7C;

/* Pool item ordered by _InsertSortByFreq. */
typedef struct Item_8027FB2C {
    int mCount;
    Node_8027FB7C *mpNode;
} Item_8027FB2C;

/* 12-byte coder state allocated by _HuffCoStart and _HuffDecStart. */
typedef struct State_8027FD64 {
    Node_8027FB7C *mpRoot;
    unsigned char mBits;
    unsigned char mBitCount;
    int mRemaining;
} State_8027FD64;

extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern unsigned int fn_801C6880(void *pool, int c);
extern void *fn_801C6A20(void *pool);
extern void *fn_801C6B4C(void *pool, void *item);
extern void fn_801C6BC0(void *pool, void *item);
extern void *fn_801C6C84(void *pool, void *item);
extern int fn_801C6DCC(void *pool, void *start, void *key, void *pFound,
                       int (*match)(void *, void *, void *));

int _InsertSortByFreq(void *a, void *b)
{
    Item_8027FB2C *pA = a;
    Item_8027FB2C *pB = b;

    return pA->mCount - pB->mCount;
}

int _SearchForSymbol(void *item, void *key, void *pFound)
{
    Item_8027FB2C *pItem = item;
    Node_8027FB7C *pNode = pItem->mpNode;

    if (pNode->mpLeft == 0 && pNode->mpRight == 0 && pNode->mSymbol == *(unsigned char *)key) {
        *(Item_8027FB2C **)pFound = pItem;
        return 0;
    }
    return -1;
}

int _IsSymbolInTree(Node_8027FB7C *pNode, int symbol)
{
    if (pNode->mpLeft == 0 && pNode->mpRight == 0) {
        return pNode->mSymbol == symbol;
    }
    if (_IsSymbolInTree(pNode->mpLeft, symbol) || _IsSymbolInTree(pNode->mpRight, symbol)) {
        return 1;
    }
    return 0;
}

Node_8027FB7C *_BuildTree(void *pool)
{
    Item_8027FB2C *pItem;
    Item_8027FB2C *pChild;
    Node_8027FB7C *pRoot;

    while (fn_801C6880(pool, 3) > 1) {
        pItem = fn_801C6A20(pool);
        pItem->mpNode = fn_801D2BB0(1, sizeof(Node_8027FB7C), 0, 0);
        pChild = fn_801C6B4C(pool, 0);
        pItem->mpNode->mpLeft = pChild->mpNode;
        pItem->mCount = pChild->mCount;
        fn_801C6BC0(pool, pChild);
        pChild = fn_801C6B4C(pool, 0);
        pItem->mpNode->mpRight = pChild->mpNode;
        pItem->mCount += pChild->mCount;
        fn_801C6BC0(pool, pChild);
        pItem->mpNode->mSymbol = 0;
        fn_801C6AA4(pool, pItem, 0);
    }
    pChild = fn_801C6B4C(pool, 0);
    pRoot = pChild->mpNode;
    fn_801C6BC0(pool, pChild);
    return pRoot;
}

void _DestroyTree(Node_8027FB7C *pNode)
{
    if (pNode->mpLeft != 0) {
        _DestroyTree(pNode->mpLeft);
    }
    if (pNode->mpRight != 0) {
        _DestroyTree(pNode->mpRight);
    }
    fn_801D2BD0(pNode);
}

State_8027FD64 *_HuffCoStart(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Item_8027FB2C *pItem = 0;
    unsigned char symbol;
    unsigned short count;
    State_8027FD64 *pState;
    void *pool;
    int index;

    pState = fn_801D2BB0(1, sizeof(State_8027FD64), 0, 0);
    pool = fn_801C68FC(1, 0, 2056, sizeof(Item_8027FB2C), _InsertSortByFreq, 0);
    while (GCmpRead(pSrc, &symbol, 1)) {
        pItem = 0;
        if (fn_801C6DCC(pool, 0, &symbol, &pItem, _SearchForSymbol) == 2) {
            fn_801C6BC0(pool, pItem);
            pItem->mCount++;
            fn_801C6AA4(pool, pItem, 0);
        } else {
            pItem = fn_801C6A20(pool);
            pItem->mCount = 1;
            pItem->mpNode = fn_801D2BB0(1, sizeof(Node_8027FB7C), 0, 0);
            pItem->mpNode->mSymbol = symbol;
            pItem->mpNode->mpLeft = pItem->mpNode->mpRight = 0;
            fn_801C6AA4(pool, pItem, 0);
        }
    }
    pSrc->mPos = 0;
    GCmpWrite(pDst, &pSrc->mSize, 4);
    index = 0;
    count = fn_801C6880(pool, 3);
    GCmpWrite(pDst, &count, 2);
    for (pItem = fn_801C6B4C(pool, 0); pItem != 0; pItem = fn_801C6C84(pool, pItem)) {
        GCmpWrite(pDst, pItem->mpNode, 1);
        pItem->mCount = index;
        index++;
    }
    pState->mpRoot = _BuildTree(pool);
    fn_801C69E4(pool);
    pState->mBits = 0;
    pState->mBitCount = 0;
    return pState;
}

int _HuffCoProcess(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    unsigned char symbol;
    Node_8027FB7C *pNode;

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

void _HuffCoStop(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    if (pState->mBitCount != 0) {
        GCmpWrite(pDst, &pState->mBits, 1);
    }
    _DestroyTree(pState->mpRoot);
    fn_801D2BD0(pState);
}

State_8027FD64 *_HuffDecStart(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned short count;
    unsigned int i = 0;
    State_8027FD64 *pState;
    void *pool;
    Item_8027FB2C *pItem;

    pState = fn_801D2BB0(1, sizeof(State_8027FD64), 0, 0);
    pool = fn_801C68FC(1, 0, 2056, sizeof(Item_8027FB2C), _InsertSortByFreq, 0);
    GCmpRead(pSrc, &pState->mRemaining, 4);
    GCmpRead(pSrc, &count, 2);
    for (; i < count; i++) {
        pItem = fn_801C6A20(pool);
        pItem->mpNode = fn_801D2BB0(1, sizeof(Node_8027FB7C), 0, 0);
        GCmpRead(pSrc, pItem->mpNode, 1);
        pItem->mCount = i;
        pItem->mpNode->mpLeft = pItem->mpNode->mpRight = 0;
        fn_801C6AA4(pool, pItem, 0);
    }
    pState->mpRoot = _BuildTree(pool);
    fn_801C69E4(pool);
    pState->mBits = 0;
    pState->mBitCount = 0;
    return pState;
}

int _HuffDecProcess(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    Node_8027FB7C *pNode = pState->mpRoot;

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

void _HuffDecStop(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    _DestroyTree(pState->mpRoot);
    fn_801D2BD0(pState);
}
