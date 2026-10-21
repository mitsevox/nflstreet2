#include <string.h>
#include "game/fn_801C68FC.h"

/* Byte buffer read and written by the codec functions; only the accessed fields are declared. */
typedef struct Buffer_8027F9AC {
    unsigned char *mpData;
    unsigned int mSize;
    unsigned int mPos;
    unsigned char mUnknownC[12];
    unsigned char mUnknown18;
} Buffer_8027F9AC;

typedef void *(*CodecInit_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);
typedef int (*CodecRun_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState);
typedef void (*CodecEnd_8027F2D8)(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState);

/* 40-byte codec descriptor registered through fn_8027F2D8. */
typedef struct Codec_8027F2D8 {
    unsigned int mTag;
    unsigned int mFlags;
    CodecInit_8027F2D8 mpEncodeInit;
    CodecRun_8027F2D8 mpEncodeRun;
    CodecEnd_8027F2D8 mpEncodeEnd;
    CodecInit_8027F2D8 mpDecodeInit;
    CodecRun_8027F2D8 mpDecodeRun;
    CodecEnd_8027F2D8 mpDecodeEnd;
    int (*mpStartup)(void);
    int (*mpShutdown)(void);
} Codec_8027F2D8;

/* 28-byte stream record allocated by fn_8027F45C and fn_8027F7B0. */
typedef struct Stream_8027F45C {
    Buffer_8027F9AC *mpSrc;
    Buffer_8027F9AC *mpDst;
    void *mpState;
    int mMode;
    int mCodec;
    unsigned int mStatus;
    unsigned char mOwnsDst;
} Stream_8027F45C;

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
extern void *fn_801D310C(void *allocation, int size, int c, int d);
extern void fn_801F7BD4(int err);
extern char *fn_801C3284(char *pDest, const char *pSource, int size);
extern int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
extern unsigned int fn_801C6880(void *pool, int c);
extern void *fn_801C6A20(void *pool);
extern void *fn_801C6B4C(void *pool, void *item);
extern void fn_801C6BC0(void *pool, void *item);
extern void *fn_801C6C84(void *pool, void *item);
extern int fn_801C6DCC(void *pool, void *start, void *key, void *pFound,
                       int (*match)(void *, void *, void *));

static unsigned char lbl_803EC570 = 0;
static int lbl_803EC574 = 0;
static Codec_8027F2D8 **lbl_803ED410;
extern char lbl_803018A8[];
extern Codec_8027F2D8 lbl_803018C8;
extern Codec_8027F2D8 lbl_803018F0;
extern Codec_8027F2D8 lbl_80301918;
extern Codec_8027F2D8 lbl_80301940;
extern Codec_8027F2D8 lbl_80301968;

int fn_8027F2D8(int index, Codec_8027F2D8 *pCodec);
Stream_8027F45C *fn_8027F45C(int mode, int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst);
void fn_8027F61C(Stream_8027F45C *pStream);
void fn_8027F6A8(Stream_8027F45C *pStream);
int fn_8027F9AC(Buffer_8027F9AC *pBuffer, void *pOut, unsigned int size);
int fn_8027FA04(Buffer_8027F9AC *pBuffer, void *pIn, unsigned int size);

int fn_8027EFAC(int year)
{
    int leap = 0;

    if (year % 4 == 0) {
        if (year % 100 != 0) {
            leap = 1;
        } else {
            leap = year % 400 == 0;
        }
    }
    return leap;
}

int fn_8027F000(int year)
{
    return fn_8027EFAC(year) ? 366 : 365;
}

int fn_8027F030(int month, int year)
{
    int days = 31;

    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    case 2:
        days = fn_8027EFAC(year) ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    }
    return days;
}

int fn_8027F0DC(int count)
{
    int err = 0;
    unsigned short i;

    if (lbl_803EC570 == 0) {
        lbl_803EC574 = count + 6;
        lbl_803ED410 = fn_801D2BB0(1, lbl_803EC574 * 4, 0, 0);
        fn_8027F2D8(0, &lbl_80301918);
        fn_8027F2D8(1, &lbl_803018F0);
        fn_8027F2D8(2, &lbl_803018C8);
        fn_8027F2D8(3, &lbl_80301940);
        fn_8027F2D8(5, &lbl_80301968);
        lbl_803ED410[4] = 0;
        for (i = 0; i <= 5 && err == 0; i++) {
            if (lbl_803ED410[i] != 0 && lbl_803ED410[i]->mpStartup != 0) {
                err = lbl_803ED410[i]->mpStartup();
            }
        }
        while (count--) {
            fn_8027F2D8(count + 6, 0);
        }
        lbl_803EC570 = 1;
    } else {
        err = 0x150001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_8027F21C(void)
{
    int err = 0;
    unsigned short i;

    if (lbl_803EC570) {
        for (i = 0; i <= 5 && err == 0; i++) {
            if (lbl_803ED410[i] != 0 && lbl_803ED410[i]->mpShutdown != 0) {
                err = lbl_803ED410[i]->mpShutdown();
            }
        }
        fn_801D2BD0(lbl_803ED410);
        lbl_803EC570 = 0;
    } else {
        err = 0x150002;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_8027F2C0(void)
{
    return lbl_803EC570 != 0;
}

int fn_8027F2D8(int index, Codec_8027F2D8 *pCodec)
{
    lbl_803ED410[index] = pCodec;
    return 0;
}

void fn_8027F2EC(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_8027F45C(0, codec, pSrc, pDst);

    if (pStream->mStatus == 0) {
        do {
            fn_8027F61C(pStream);
            switch (pStream->mStatus) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
                pDst->mpData = fn_801D310C(pDst->mpData, pDst->mSize * 2, 0, 0);
                pDst->mSize *= 2;
                pStream->mOwnsDst = 1;
                pStream->mStatus = 0;
                break;
            }
        } while (pStream->mStatus == 0);
    }
    fn_8027F6A8(pStream);
}

void fn_8027F3A4(int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_8027F45C(1, codec, pSrc, pDst);

    if (pStream->mStatus == 0) {
        do {
            fn_8027F61C(pStream);
            switch (pStream->mStatus) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
                pDst->mpData = fn_801D310C(pDst->mpData, pDst->mSize * 2, 0, 0);
                pDst->mSize *= 2;
                pStream->mOwnsDst = 1;
                pStream->mStatus = 0;
                break;
            }
        } while (pStream->mStatus == 0);
    }
    fn_8027F6A8(pStream);
}

Stream_8027F45C *fn_8027F45C(int mode, int codec, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_801D2BB0(1, sizeof(Stream_8027F45C), 4, 0);
    unsigned int size;

    if (pStream != 0) {
        pStream->mMode = mode;
        pStream->mCodec = codec;
        pStream->mStatus = 0;
        pStream->mOwnsDst = 0;
        pStream->mpSrc = pSrc;
        pSrc->mPos = 0;
        pStream->mpDst = pDst;
        pDst->mPos = 0;
        pStream->mpState = 0;
        switch (pStream->mMode) {
        case 0:
            if (pStream->mpDst->mpData == 0) {
                pStream->mpDst->mSize = pStream->mpSrc->mSize;
                pStream->mpDst->mpData = fn_801D2BB0(1, pStream->mpDst->mSize, 0, 0);
                pStream->mOwnsDst = 1;
            }
            pStream->mpSrc->mUnknown18 = 1;
            pStream->mpDst->mUnknown18 = 0;
            pStream->mpState = lbl_803ED410[pStream->mCodec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        case 1:
            pStream->mpDst->mUnknown18 = 1;
            if (pStream->mpDst->mpData == 0) {
                size = pStream->mpDst->mSize;
                if (size != 0) {
                    pStream->mpDst->mpData = fn_801D2BB0(1, size, 0, 0);
                } else {
                    pStream->mpDst->mSize = pStream->mpSrc->mSize * 2;
                    pStream->mpDst->mpData = fn_801D2BB0(1, pStream->mpDst->mSize, 0, 0);
                    pStream->mOwnsDst = 1;
                    pStream->mpDst->mUnknown18 = 0;
                }
            }
            pStream->mpSrc->mUnknown18 = 1;
            pStream->mpState = lbl_803ED410[pStream->mCodec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

void fn_8027F61C(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
}

void fn_8027F6A8(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        lbl_803ED410[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        lbl_803ED410[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    pStream->mpDst->mSize = pStream->mpDst->mPos;
    if (pStream->mOwnsDst) {
        pStream->mpDst->mpData = fn_801D310C(pStream->mpDst->mpData, pStream->mpDst->mSize, 0, 0);
    }
    fn_801D2BD0(pStream);
}

int fn_8027F77C(int index)
{
    Codec_8027F2D8 *pCodec;

    if (lbl_803ED410 != 0) {
        pCodec = lbl_803ED410[index];
        if (pCodec != 0 && (pCodec->mFlags & 2)) {
            return 1;
        }
    }
    return 0;
}

Stream_8027F45C *fn_8027F7B0(int codec, int mode, Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    Stream_8027F45C *pStream = fn_801D2BB0(1, sizeof(Stream_8027F45C), 0, 0);

    if (pStream != 0) {
        pStream->mpSrc = pSrc;
        pSrc->mPos = 0;
        pStream->mpDst = pDst;
        pDst->mPos = 0;
        pStream->mMode = mode;
        pStream->mCodec = codec;
        pStream->mStatus = 0;
        pStream->mOwnsDst = 0;
        pStream->mpState = 0;
        switch (mode) {
        case 0:
            pStream->mpState = lbl_803ED410[codec]->mpEncodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        case 1:
            pStream->mpState = lbl_803ED410[codec]->mpDecodeInit(pStream->mpSrc, pStream->mpDst);
            break;
        }
    }
    return pStream;
}

unsigned int fn_8027F880(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpEncodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    case 1:
        pStream->mStatus = lbl_803ED410[pStream->mCodec]->mpDecodeRun(pStream->mpSrc, pStream->mpDst,
                                                                      pStream->mpState);
        break;
    }
    return pStream->mStatus;
}

void fn_8027F910(Stream_8027F45C *pStream)
{
    switch (pStream->mMode) {
    case 0:
        lbl_803ED410[pStream->mCodec]->mpEncodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    case 1:
        lbl_803ED410[pStream->mCodec]->mpDecodeEnd(pStream->mpSrc, pStream->mpDst, pStream->mpState);
        break;
    }
    fn_801D2BD0(pStream);
}

int fn_8027F9AC(Buffer_8027F9AC *pBuffer, void *pOut, unsigned int size)
{
    unsigned char *pDst = pOut;

    if (pBuffer->mPos + size > pBuffer->mSize) {
        return 0;
    }
    while (size--) {
        *pDst++ = pBuffer->mpData[pBuffer->mPos++];
    }
    return 1;
}

int fn_8027FA04(Buffer_8027F9AC *pBuffer, void *pIn, unsigned int size)
{
    unsigned char *pSrc = pIn;

    while (pBuffer->mPos + size > pBuffer->mSize) {
        pBuffer->mpData = fn_801D310C(pBuffer->mpData, pBuffer->mSize * 2, 0, 0);
        pBuffer->mSize *= 2;
    }
    while (size--) {
        pBuffer->mpData[pBuffer->mPos++] = *pSrc++;
    }
    return 1;
}

void fn_8027FAB8(const char *pName)
{
    if (pName == 0) {
        fn_801C3284(lbl_803018A8, "GCMP.LIB", 32);
    } else {
        fn_801C2D88(lbl_803018A8, 32, "%s", pName);
        lbl_803018A8[31] = 0;
    }
}

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

void *fn_802802A0(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int fn_802802A8(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char *pIn = pSrc->mpData;
    unsigned int size = pSrc->mSize;
    unsigned int pos = pSrc->mPos;
    unsigned char *pOut = pDst->mpData;
    unsigned int outPos = pDst->mPos;
    unsigned int capacity = pDst->mSize;
    unsigned char value;
    unsigned char run;
    unsigned char marker = '!';
    int escape;
    unsigned int length;

    while (pos < size) {
        value = pIn[pos];
        run = 1;
        pos++;
        while (pos < size && run < 255 && pIn[pos] == value) {
            run++;
            pos++;
        }
        if (run > 3 || value == marker) {
            escape = 1;
            length = 3;
        } else {
            escape = 0;
            length = run;
        }
        while (outPos + length > capacity) {
            pOut = fn_801D310C(pOut, capacity * 2, 0, 0);
            capacity *= 2;
        }
        if (escape) {
            pOut[outPos++] = marker;
            pOut[outPos++] = value;
            pOut[outPos++] = run;
        } else {
            memset(&pOut[outPos], value, run);
            outPos += run;
        }
    }
    pSrc->mPos = pos;
    pDst->mPos = outPos;
    pDst->mSize = capacity;
    pDst->mpData = pOut;
    return 1;
}

void fn_802803F8(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}

void *fn_802803FC(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int fn_80280404(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char *pIn = pSrc->mpData;
    unsigned int size = pSrc->mSize;
    unsigned int pos = pSrc->mPos;
    unsigned char *pOut = pDst->mpData;
    unsigned int outPos = pDst->mPos;
    unsigned int capacity = pDst->mSize;
    unsigned char value;
    unsigned char run;

    while (pos < size) {
        value = pIn[pos];
        run = 1;
        pos++;
        if (value == '!') {
            value = pIn[pos];
            pos++;
            run = pIn[pos];
            pos++;
        }
        while (outPos + run > capacity) {
            pOut = fn_801D310C(pOut, capacity * 2, 0, 0);
            capacity *= 2;
        }
        if (run == 1) {
            pOut[outPos++] = value;
        } else {
            memset(&pOut[outPos], value, run);
            outPos += run;
        }
    }
    pSrc->mPos = pos;
    pDst->mPos = outPos;
    pDst->mSize = capacity;
    pDst->mpData = pOut;
    return 1;
}

void fn_80280500(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}

void *fn_80280504(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int fn_8028050C(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char value;

    if (fn_8027F9AC(pSrc, &value, 1) == 0) {
        return 1;
    }
    fn_8027FA04(pDst, &value, 1);
    return 0;
}

void fn_80280560(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}

void *fn_80280564(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int fn_8028056C(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char value;

    if (fn_8027F9AC(pSrc, &value, 1) == 0) {
        return 1;
    }
    fn_8027FA04(pDst, &value, 1);
    return 0;
}

void fn_802805C0(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}
