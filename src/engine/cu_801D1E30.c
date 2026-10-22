#include "engine/cu_801D1E30.h"

typedef MemHeap_801D1E30 MemHeap;

typedef struct MemBlock {
    short mOffset;
    unsigned char mType;
    MemHeap *mHeap;
    void **mEnd;
} MemBlock;

typedef struct MemFreeNode {
    unsigned int mSize;
    char mUnknown4[0xC - 0x4];
    struct MemFreeNode *mNext;
} MemFreeNode;

typedef struct MemDebugInfo {
    char mUnknown0[0x4];
    int mSerial;
    char mUnknown8[0xC - 0x8];
    char mFile[0x2C - 0xC];
    char mLabel[16];
    char mName[16];
    char mGuard[16];
    int mExtra;
} MemDebugInfo;

typedef struct MemHeapParams {
    char mName[8];
    int mIdent;
    char *mStart;
    unsigned int mSize;
    unsigned short mAlign;
} MemHeapParams;

typedef struct MemInitParams {
    char mUnknown0[0x40];
    MemHeapParams *mHeap;
} MemInitParams;

typedef struct MemLock_803E92AC MemLock_803E92AC;

extern int lbl_803EBCC4;
extern void (*lbl_803EBCD4)(void);
extern unsigned short lbl_803EBCD8;
extern unsigned char lbl_803EBCDA;
extern unsigned char lbl_803EBCDB;
extern unsigned char lbl_803EBCDC;
extern unsigned char lbl_803EBCE4;
extern int lbl_803EBCE8;
extern MemHeap *lbl_803EBCC8;
extern MemHeap *lbl_803EBCCC;
extern void (*lbl_803EBCEC)(void);
extern int (*lbl_803EBCF0)(int a, void *pAddr);
extern int (*lbl_803EBCF4)(int a, int flags, int c, int d);
extern MemLock_803E92AC lbl_803E92AC;
extern const char lbl_802AF9BC[];
extern const char lbl_802AF628[];

extern void *memset(void *pDst, int value, unsigned int size);
extern void *memcpy();
extern char *strcpy(char *pDst, const char *pSrc);
extern int sprintf(char *pDst, const char *pFormat, ...);

extern MemHeap *fn_801D134C(int ident);
extern MemHeap *fn_801D13A4(void *pAddr);
extern void *fn_801D1C14(MemBlock *pBlock, int size, int align, unsigned int minSize);
extern void *fn_801D28A8(int a, int size, int ident, int flags);
extern void *fn_801D2E5C(int a, void *pAddr, int size, int ident, int flags);
extern void fn_801C3284(char *pDst, const char *pSrc);
extern int fn_801F7ABC(void);
extern void fn_801F7FA8(MemLock_803E92AC *pLock);
extern void fn_801F80D0(MemLock_803E92AC *pLock);
extern int fn_801D2130(MemHeapParams *pParams);
extern int fn_801D2570(int ident);
extern void fn_801D1474(void);
extern void *fn_801D2BB0(int a, int size, int ident, int flags);
extern int fn_801D2BD0(void *pAddr);
extern void fn_801D34CC(void *pAddr);
extern void fn_801F8014(MemLock_803E92AC *pLock);
extern void fn_801F809C(MemLock_803E92AC *pLock);

static void *fn_801D1E30(MemHeap *pHeap, int size, int align, unsigned int minSize)
{
    MemBlock *pBlock;
    void *pResult;

    if (pHeap == 0) {
        return 0;
    }
    for (pBlock = (MemBlock *)(pHeap->mEnd - 0x10); pBlock->mType != 2;
         pBlock = (MemBlock *)((char *)((MemBlock *)((char *)pBlock - pBlock->mOffset))->mEnd - 8)) {
        if ((unsigned int)((char *)pBlock->mEnd - (char *)*pBlock->mEnd - 4) >= minSize && pBlock->mType == 0) {
            pResult = fn_801D1C14(pBlock, size, align, minSize);
            if (pResult != 0) {
                return pResult;
            }
        }
    }
    return 0;
}

static void fn_801D1ED8(MemDebugInfo *pInfo, const char *pFile, unsigned int line, const char *pLabel,
                        const char *pName, int extra)
{
    int i;

    memset(pInfo->mGuard, '*', sizeof(pInfo->mGuard));
    if (line > 999999) {
        line = 999999;
    }
    for (i = 0; pFile[i] != 0; i++) {
        if (pFile[i] == '/' || pFile[i] == '\\') {
            pFile += i + 1;
            i = -1;
        } else if (i == 22) {
            pFile++;
            i = 21;
        }
    }
    sprintf(pInfo->mFile, lbl_802AF628, pFile, line);
    for (i = 0; i != 15 && pLabel[i] != 0; i++) {
        pInfo->mLabel[i] = pLabel[i];
    }
    pInfo->mLabel[i] = 0;
    for (i = 0; i != 15 && pName[i] != 0; i++) {
        pInfo->mName[i] = pName[i];
    }
    pInfo->mName[i] = 0;
    pInfo->mExtra = extra;
    if (lbl_803EBCE4) {
        pInfo->mSerial = lbl_803EBCE8;
        lbl_803EBCE8++;
    } else {
        pInfo->mSerial = fn_801F7ABC();
    }
}

static void fn_801D2050(void)
{
}

int fn_801D2054(MemInitParams *pParams)
{
    int result = 0;

    fn_801F7FA8(&lbl_803E92AC);
    lbl_803EBCC8 = 0;
    lbl_803EBCCC = 0;
    lbl_803EBCD4 = fn_801D2050;
    if (pParams != 0) {
        result = fn_801D2130(pParams->mHeap);
        if (result == 0) {
            lbl_803EBCC4 = pParams->mHeap->mIdent;
        }
    }
    return result;
}

int fn_801D20C8(void)
{
    if (lbl_803EBCC4 != 0) {
        fn_801D2570(lbl_803EBCC4);
    }
    while (lbl_803EBCC8 != 0) {
        fn_801D2570(lbl_803EBCC8->mIdent);
    }
    lbl_803EBCC8 = 0;
    lbl_803EBCCC = 0;
    lbl_803EBCDC = 0;
    fn_801F80D0(&lbl_803E92AC);
    return 0;
}

void *fn_801D2478(int ident, int parentIdent, char *pStart, unsigned int size, int dataSize,
                  MemHeapFuncs_801D1E30 *pFuncs)
{
    MemHeap *pHeap;
    int total;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mNext) {
        if (ident == pHeap->mIdent || (pStart < pHeap->mEnd && pStart + size > pHeap->mStart)) {
            goto fail;
        }
    }
    if (dataSize == 0) {
        dataSize = 1;
    }
    total = dataSize + sizeof(MemHeap);
    pHeap = fn_801D2BB0(parentIdent, total, 0, 0);
    if (pHeap == 0) {
        goto fail;
    }
    memset(pHeap, 0, total);
    pHeap->mIdent = ident;
    pHeap->mSize = size;
    pHeap->mEnd = pStart + size;
    pHeap->mDebugSize = lbl_803EBCD8;
    pHeap->mFuncs = pFuncs;
    pHeap->mStart = pStart;
    pHeap->mDebug = lbl_803EBCDA;
    pHeap->mSelf = pHeap;
    pHeap->mNext = lbl_803EBCC8;
    lbl_803EBCC8 = pHeap;
    fn_801D1474();
    return pHeap + 1;
fail:
    return 0;
}

int fn_801D2570(int ident)
{
    MemHeap **ppLink = &lbl_803EBCC8;
    MemHeap *pHeap;
    MemHeap *pParent;
    int freeStart = 0;
    int ownsMemory;
    char *pStart;

    while ((pHeap = *ppLink) != 0) {
        if (ident == -1 || ident == pHeap->mIdent) {
            if (pHeap->mParent != 0) {
                freeStart = 1;
                for (pParent = pHeap->mParent; pParent != 0; pParent = pParent->mSibling) {
                    if (pParent->mSibling == pHeap) {
                        pParent->mSibling = pHeap->mSibling;
                        break;
                    }
                }
            }
            ownsMemory = pHeap->mOwnsMemory;
            *ppLink = pHeap->mNext;
            pStart = pHeap->mStart;
            if (pHeap->mFuncs != 0) {
                pHeap->mFuncs->mDestroy(pHeap + 1);
                fn_801D2BD0(pHeap);
            } else if (pHeap->mFillByte != 0x80) {
                memset(pStart, pHeap->mFillByte, pHeap->mSize);
            }
            if (freeStart) {
                fn_801D2BD0(pStart);
            }
            if (ownsMemory) {
                fn_801D34CC(pStart);
            }
        } else {
            ppLink = &pHeap->mNext;
        }
    }
    fn_801D1474();
    return 0;
}

void fn_801D2694(void)
{
    if (lbl_803EBCEC != 0) {
        lbl_803EBCEC();
    }
}

int fn_801D26C4(int a, int flags, int c)
{
    if (lbl_803EBCF4 != 0) {
        lbl_803EBCF4(a, flags | 0x20, c, 0);
    }
    return 0;
}

int fn_801D2700(int ident)
{
    return fn_801D134C(ident) != 0;
}

int fn_801D2730(void)
{
    int ident;
    MemHeap *pHeap;

    for (ident = 1;; ident++) {
        if ((ident & -ident) != ident) {
            for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mNext) {
                if (pHeap->mIdent == ident) {
                    break;
                }
            }
            if (pHeap == 0) {
                return ident;
            }
        }
    }
}

void fn_801D277C(int ident)
{
    lbl_803EBCCC = fn_801D134C(ident);
}

int fn_801D27A0(void)
{
    MemHeap *pHeap = lbl_803EBCCC;
    int ident = 1;

    if (pHeap != 0) {
        ident = pHeap->mIdent;
    }
    return ident;
}

char *fn_801D27B8(int ident)
{
    char *pStart = 0;
    MemHeap *pHeap = fn_801D134C(ident);

    if (pHeap != 0) {
        pStart = pHeap->mStart;
    }
    return pStart;
}

unsigned int fn_801D27F4(int ident)
{
    unsigned int largest = 0;
    MemHeap *pHeap = fn_801D134C(ident);
    MemFreeNode *pNode;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mFuncs != 0) {
        return pHeap->mFuncs->mInfo(pHeap + 1, 3);
    }
    for (pNode = pHeap->mFreeList; pNode != 0; pNode = pNode->mNext) {
        largest = pNode->mSize;
    }
    return largest;
}

int fn_801D2874(int a, void *pAddr)
{
    if (lbl_803EBCF0 != 0) {
        lbl_803EBCF0(a, pAddr);
    }
    return 0;
}

void *fn_801D2B7C(int size, int a, int b)
{
    return fn_801D28A8(0, size, a, b);
}

void *fn_801D2BB0(int a, int size, int ident, int flags)
{
    return fn_801D28A8(a, size, ident, flags);
}

void *fn_801D310C(void *pAddr, int size, int ident, int flags)
{
    return fn_801D2E5C(0, pAddr, size, ident, flags);
}

int fn_801D3148(int a, void *pAddr)
{
    MemHeap *pHeap = fn_801D13A4(pAddr);
    MemBlock *pBlock;
    int size;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mFuncs != 0) {
        return pHeap->mFuncs->mSizeof(pHeap + 1, pAddr);
    }
    if (pHeap->mDebug) {
        fn_801D2874(a, pAddr);
    }
    fn_801F8014(&lbl_803E92AC);
    pBlock = ((void **)pAddr)[-1];
    size = (char *)pBlock - (char *)*(void **)pBlock - 4;
    fn_801F809C(&lbl_803E92AC);
    return size;
}

void fn_801D31F0(void *pDst, void *pSrc, int size)
{
    MemHeap *pSrcHeap;
    MemHeap *pDstHeap;
    int kind;

    if (size <= 0) {
        return;
    }
    pSrcHeap = fn_801D13A4(pSrc);
    pDstHeap = fn_801D13A4(pDst);
    kind = 0;
    if (pSrcHeap != 0 && pSrcHeap->mFuncs != 0) {
        kind = 1;
    }
    if (pDstHeap != 0 && pDstHeap->mFuncs != 0) {
        kind |= 2;
    }
    if (kind == 0) {
        memcpy(pDst, pSrc, size);
    } else if (kind == 1) {
        if (pSrcHeap->mCopy != 0) {
            pSrcHeap->mCopy(pDst, 0, pSrc, 1, size);
        }
    } else if (kind == 2) {
        if (pDstHeap->mCopy != 0) {
            pSrcHeap->mCopy(pDst, 1, pSrc, 0, size);
        }
    } else if (pSrcHeap == pDstHeap) {
        pSrcHeap->mCopy(pDst, 1, pSrc, 1, size);
    }
}

void fn_801D3318(int ident, const char *pLabel)
{
    MemHeap *pHeap;
    int i;
    char *pOut;

    if (pLabel == 0) {
        pLabel = lbl_802AF9BC;
    }
    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mNext) {
        if (ident == -1 || ident == pHeap->mIdent) {
            pOut = pHeap->mLabels[pHeap->mLabelDepth];
            for (i = 0; i != 15 && pLabel[i] != 0; i++) {
                pOut[i] = pLabel[i];
            }
            pOut[i] = 0;
        }
    }
}

void fn_801D339C(int ident)
{
    MemHeap *pHeap;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mNext) {
        if (ident == -1 || ident == pHeap->mIdent) {
            if (pHeap->mLabelDepth < 5) {
                pHeap->mLabelDepth++;
                strcpy(pHeap->mLabels[pHeap->mLabelDepth], pHeap->mLabels[pHeap->mLabelDepth - 1]);
            }
        }
    }
}

void fn_801D342C(int ident)
{
    MemHeap *pHeap;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mNext) {
        if (ident == -1 || ident == pHeap->mIdent) {
            if (pHeap->mLabelDepth != 0) {
                pHeap->mLabelDepth--;
            }
        }
    }
}

void fn_801D3470(void *pAddr, char *pOut)
{
    MemBlock *pBlock = (MemBlock *)((char *)pAddr - 0xC);
    char *pDebug;

    if (pBlock->mOffset > 0x6B) {
        pDebug = (char *)pBlock - (pBlock->mOffset - 0xC);
    } else {
        pDebug = 0;
    }
    if (pDebug != 0) {
        fn_801C3284(pOut, pDebug + 0x3C);
    }
}
