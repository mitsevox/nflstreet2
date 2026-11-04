#include "engine/GCmp.h"
#include "game/fn_801C68FC.h"

/* 12-byte tree node. */
typedef struct Node_8027FB7C {
    unsigned char mSymbol;
    struct Node_8027FB7C *mpLeft;
    struct Node_8027FB7C *mpRight;
} Node_8027FB7C;

/* Pool item ordered by fn_8027FB2C. */
typedef struct Item_8027FB2C {
    int mCount;
    Node_8027FB7C *mpNode;
} Item_8027FB2C;

/* 12-byte coder state allocated by fn_8027FD64 and fn_80280080. */
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

int fn_8027FB2C(void *a, void *b)
{
    Item_8027FB2C *pA = a;
    Item_8027FB2C *pB = b;

    return pA->mCount - pB->mCount;
}

int fn_8027FB3C(void *item, void *key, void *pFound)
{
    Item_8027FB2C *pItem = item;
    Node_8027FB7C *pNode = pItem->mpNode;

    if (pNode->mpLeft == 0 && pNode->mpRight == 0 && pNode->mSymbol == *(unsigned char *)key) {
        *(Item_8027FB2C **)pFound = pItem;
        return 0;
    }
    return -1;
}

int fn_8027FB7C(Node_8027FB7C *pNode, int symbol)
{
    if (pNode->mpLeft == 0 && pNode->mpRight == 0) {
        return pNode->mSymbol == symbol;
    }
    if (fn_8027FB7C(pNode->mpLeft, symbol) || fn_8027FB7C(pNode->mpRight, symbol)) {
        return 1;
    }
    return 0;
}

Node_8027FB7C *fn_8027FC08(void *pool)
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

void fn_8027FD14(Node_8027FB7C *pNode)
{
    if (pNode->mpLeft != 0) {
        fn_8027FD14(pNode->mpLeft);
    }
    if (pNode->mpRight != 0) {
        fn_8027FD14(pNode->mpRight);
    }
    fn_801D2BD0(pNode);
}

State_8027FD64 *fn_8027FD64(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Item_8027FB2C *pItem = 0;
    unsigned char symbol;
    unsigned short count;
    State_8027FD64 *pState;
    void *pool;
    int index;

    pState = fn_801D2BB0(1, sizeof(State_8027FD64), 0, 0);
    pool = fn_801C68FC(1, 0, 2056, sizeof(Item_8027FB2C), fn_8027FB2C, 0);
    while (fn_8027F9AC(pSrc, &symbol, 1)) {
        pItem = 0;
        if (fn_801C6DCC(pool, 0, &symbol, &pItem, fn_8027FB3C) == 2) {
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
    fn_8027FA04(pDst, &pSrc->mSize, 4);
    index = 0;
    count = fn_801C6880(pool, 3);
    fn_8027FA04(pDst, &count, 2);
    for (pItem = fn_801C6B4C(pool, 0); pItem != 0; pItem = fn_801C6C84(pool, pItem)) {
        fn_8027FA04(pDst, pItem->mpNode, 1);
        pItem->mCount = index;
        index++;
    }
    pState->mpRoot = fn_8027FC08(pool);
    fn_801C69E4(pool);
    pState->mBits = 0;
    pState->mBitCount = 0;
    return pState;
}

int fn_8027FF54(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    unsigned char symbol;
    Node_8027FB7C *pNode;

    if (fn_8027F9AC(pSrc, &symbol, 1) != 0) {
        pNode = pState->mpRoot;
        while (pNode->mpLeft != 0 || pNode->mpRight != 0) {
            if (fn_8027FB7C(pNode->mpRight, symbol)) {
                pState->mBits |= 1 << pState->mBitCount;
                pNode = pNode->mpRight;
            } else {
                pNode = pNode->mpLeft;
            }
            if (++pState->mBitCount > 7) {
                fn_8027FA04(pDst, &pState->mBits, 1);
                pState->mBits = 0;
                pState->mBitCount = 0;
            }
        }
        return 0;
    }
    return 1;
}

void fn_8028002C(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    if (pState->mBitCount != 0) {
        fn_8027FA04(pDst, &pState->mBits, 1);
    }
    fn_8027FD14(pState->mpRoot);
    fn_801D2BD0(pState);
}

State_8027FD64 *fn_80280080(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned short count;
    unsigned int i = 0;
    State_8027FD64 *pState;
    void *pool;
    Item_8027FB2C *pItem;

    pState = fn_801D2BB0(1, sizeof(State_8027FD64), 0, 0);
    pool = fn_801C68FC(1, 0, 2056, sizeof(Item_8027FB2C), fn_8027FB2C, 0);
    fn_8027F9AC(pSrc, &pState->mRemaining, 4);
    fn_8027F9AC(pSrc, &count, 2);
    for (; i < count; i++) {
        pItem = fn_801C6A20(pool);
        pItem->mpNode = fn_801D2BB0(1, sizeof(Node_8027FB7C), 0, 0);
        fn_8027F9AC(pSrc, pItem->mpNode, 1);
        pItem->mCount = i;
        pItem->mpNode->mpLeft = pItem->mpNode->mpRight = 0;
        fn_801C6AA4(pool, pItem, 0);
    }
    pState->mpRoot = fn_8027FC08(pool);
    fn_801C69E4(pool);
    pState->mBits = 0;
    pState->mBitCount = 0;
    return pState;
}

int fn_802801A0(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    Node_8027FB7C *pNode = pState->mpRoot;

    while (pNode->mpLeft != 0 || pNode->mpRight != 0) {
        if (pState->mBitCount == 0) {
            fn_8027F9AC(pSrc, &pState->mBits, 1);
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
    fn_8027FA04(pDst, pNode, 1);
    return --pState->mRemaining == 0;
}

void fn_80280268(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, State_8027FD64 *pState)
{
    fn_8027FD14(pState->mpRoot);
    fn_801D2BD0(pState);
}
