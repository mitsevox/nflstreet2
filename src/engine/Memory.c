#include "game/fn_801D2B7C.h"
#include "engine/Memory.h"
#include "engine/llmemory.h"

typedef struct MemRange_801D134C {
    char *mpStart;
    char *mpEnd;
    int mId;
    MemHeap_801D134C *mpHeap;
} MemRange_801D134C;

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
    int mId;
    char *mStart;
    unsigned int mSize;
    unsigned short mAlign;
} MemHeapParams;

typedef struct MemInitParams {
    char mUnknown0[0x40];
    MemHeapParams *mpHeap;
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
extern MemHeap_801D134C *lbl_803EBCC8;
extern MemHeap_801D134C *lbl_803EBCCC;
extern int lbl_803EBCD0;
extern MemRange_801D134C lbl_80384BC0[16];
extern void (*lbl_803EBCEC)(void);
extern int (*lbl_803EBCF0)(int a, void *pAddr);
extern int (*lbl_803EBCF4)(int ident, int flags, const char *pMessage, int d);
extern MemLock_803E92AC lbl_803E92AC;
extern const char lbl_802AF9BC[];
extern const char lbl_802AF628[];

extern void *memset(void *pDst, int value, unsigned int size);
extern void *memcpy();
extern char *strcpy(char *pDst, const char *pSrc);
extern int sprintf(char *pDst, const char *pFormat, ...);

extern void *fn_801D28A8(int a, int size, int ident, int flags);
extern void *fn_801D2E5C(int a, void *pAddr, int size, int ident, int flags);
extern char *fn_801C3284(char *pDst, const char *pSrc);
extern int fn_801F7ABC(void);
extern void fn_801F7FA8(MemLock_803E92AC *pLock);
extern void fn_801F80D0(MemLock_803E92AC *pLock);
extern int fn_801D2130(MemHeapParams *pParams);
extern int fn_801D2570(int ident);
extern void fn_801F8014(MemLock_803E92AC *pLock);
extern void fn_801F809C(MemLock_803E92AC *pLock);

static MemHeap_801D134C *fn_801D134C(int id)
{
    MemHeap_801D134C *pHeap = lbl_803EBCCC;

    if (id == -1) {
        id = 1;
    }
    if (id == 0 && pHeap) {
        return pHeap;
    }
    for (pHeap = lbl_803EBCC8; pHeap && pHeap->mId != id; pHeap = pHeap->mpNext) {
    }
    return pHeap;
}

static MemHeap_801D134C *fn_801D13A4(char *pAddr)
{
    int lo = 0;
    int hi = lbl_803EBCD0 - 1;
    int mid;
    MemHeap_801D134C *pHeap;
    MemHeap_801D134C *pSub;

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (pAddr < lbl_80384BC0[mid].mpStart) {
            hi = mid - 1;
        } else if (pAddr >= lbl_80384BC0[mid].mpEnd) {
            lo = mid + 1;
        } else {
            pHeap = lbl_80384BC0[mid].mpHeap;
            for (pSub = pHeap->mpSub; pSub; pSub = pSub->mpSub) {
                if (pAddr >= pSub->mpStart && pAddr < pSub->mpEnd) {
                    pHeap = pSub;
                    break;
                }
            }
            return pHeap;
        }
    }
    return 0;
}

static void fn_801D1474(void)
{
    MemHeap_801D134C *pHeap;
    MemRange_801D134C *pRange;
    MemRange_801D134C tmp;
    int i;

    i = 0;
    for (pHeap = lbl_803EBCC8; pHeap; pHeap = pHeap->mpNext) {
        if (!pHeap->mpParent && i < 16) {
            lbl_80384BC0[i].mpStart = pHeap->mpStart;
            lbl_80384BC0[i].mpEnd = pHeap->mpEnd;
            lbl_80384BC0[i].mId = pHeap->mId;
            lbl_80384BC0[i].mpHeap = pHeap;
            i++;
        }
    }
    lbl_803EBCD0 = i;
    for (i = 1; i < lbl_803EBCD0; i++) {
        pRange = &lbl_80384BC0[i - 1];
        if (pRange[0].mpStart > pRange[1].mpStart) {
            tmp = pRange[0];
            pRange[0] = pRange[1];
            pRange[1] = tmp;
            if (i > 1) {
                i -= 2;
            }
        }
    }
}

static void fn_801D1588(MemHeap_801D134C *pHeap, MemNode_801D134C *pNode)
{
    MemNode_801D134C *pParent = &pHeap->mRoot;
    MemNode_801D134C **ppLink = &pHeap->mRoot.mpRight;
    int diff;

    if (*ppLink) {
        do {
            pParent = *ppLink;
            diff = pNode->mSize - pParent->mSize;
            if (diff == 0) {
                diff = pNode - pParent;
            }
            if (diff < 0) {
                ppLink = &pParent->mpLeft;
            } else if (diff > 0) {
                ppLink = &pParent->mpRight;
            }
        } while (*ppLink);
    }
    *ppLink = pNode;
    pNode->mpParent = pParent;
    pNode->mpLeft = 0;
    pNode->mpRight = 0;
    pHeap->mFreeBytes += pNode->mSize;
    if (++pHeap->mNumFree > pHeap->mMaxFree) {
        pHeap->mMaxFree = pHeap->mNumFree;
    }
}

static void fn_801D1620(MemHeap_801D134C *pHeap, MemNode_801D134C *pNode)
{
    MemNode_801D134C *pParent;
    MemNode_801D134C *pSucc;

    pHeap->mFreeBytes -= pNode->mSize;
    pHeap->mNumFree--;
    if (!pNode->mpRight) {
        pParent = pNode->mpParent;
        if (pParent->mpLeft == pNode) {
            pParent->mpLeft = pNode->mpLeft;
        } else {
            pParent->mpRight = pNode->mpLeft;
        }
        if (pNode->mpLeft) {
            pNode->mpLeft->mpParent = pNode->mpParent;
        }
    } else if (!pNode->mpLeft) {
        pParent = pNode->mpParent;
        if (pParent->mpLeft == pNode) {
            pParent->mpLeft = pNode->mpRight;
        } else {
            pParent->mpRight = pNode->mpRight;
        }
        if (pNode->mpRight) {
            pNode->mpRight->mpParent = pNode->mpParent;
        }
    } else if (!pNode->mpLeft->mpRight) {
        pNode->mpLeft->mpRight = pNode->mpRight;
        pNode->mpRight->mpParent = pNode->mpLeft;
        pParent = pNode->mpParent;
        if (pParent->mpLeft == pNode) {
            pParent->mpLeft = pNode->mpLeft;
        } else {
            pParent->mpRight = pNode->mpLeft;
        }
        pNode->mpLeft->mpParent = pNode->mpParent;
    } else {
        pSucc = pNode->mpLeft;
        do {
            pSucc = pSucc->mpRight;
        } while (pSucc->mpRight);
        pSucc->mpParent->mpRight = pSucc->mpLeft;
        if (pSucc->mpLeft) {
            pSucc->mpLeft->mpParent = pSucc->mpParent;
        }
        pParent = pNode->mpParent;
        if (pParent->mpLeft == pNode) {
            pParent->mpLeft = pSucc;
        } else {
            pParent->mpRight = pSucc;
        }
        pSucc->mpParent = pNode->mpParent;
        pSucc->mpLeft = pNode->mpLeft;
        pSucc->mpRight = pNode->mpRight;
        pSucc->mpLeft->mpParent = pSucc;
        pSucc->mpRight->mpParent = pSucc;
    }
}

static int fn_801D177C(MemBlock_801D134C *pBlock, int size)
{
    void **pTail;
    char *pNext;
    int n;
    MemBlock_801D134C *pFree;
    MemNode_801D134C *pNode;
    unsigned int rem;

    if (size < 16) {
        size = 16;
    }
    size = (size + 15) & ~15;
    pTail = pBlock->mpTail;
    n = (char *)pTail - (char *)*pTail;
    n -= size + 4;
    if (n < 32) {
        return -1;
    }
    pNext = (char *)pBlock + size + 0x10;
    n = pBlock->mpHeap->mDebugSize;
    rem = (unsigned int)(pNext + n + 12) & 15;
    if (rem) {
        rem = 16 - rem;
        if (n == 0 && rem < 2) {
            rem += 16;
        }
        n += rem;
    }
    pFree = (MemBlock_801D134C *)(pNext + n);
    pNode = (MemNode_801D134C *)(pFree + 1);
    if ((char *)(pNode + 1) > (char *)pTail) {
        return -1;
    }
    pBlock->mpTail = (void **)(pNext - 4);
    *(void **)(pNext - 4) = &pBlock->mpTail;
    if (pBlock->mpHeap->mFill != 0x80) {
        memset(pNext, pBlock->mpHeap->mFill, (char *)pTail - pNext);
    }
    *(short *)pNext = (char *)pNode - pNext;
    pFree->mOffset = (char *)pNode - pNext;
    pFree->mState = 0;
    pFree->mpHeap = pBlock->mpHeap;
    pFree->mpTail = pTail;
    *pTail = &pFree->mpTail;
    pNode->mSize = (char *)pTail - (char *)pNode;
    fn_801D1588(pBlock->mpHeap, pNode);
    return size;
}

static inline unsigned int fn_801D134C_Mod(char *pAddr, int offset, unsigned int align)
{
    return ((unsigned int)pAddr + offset) % align;
}

static MemBlock_801D134C *fn_801D18A0(MemBlock_801D134C *pBlock, int align, int offset, int size)
{
    char *pStart;
    MemNode_801D134C *pOld;
    unsigned int total;
    unsigned int used;
    MemHeap_801D134C *pHeap;
    unsigned int rem;
    unsigned int extra;
    MemBlock_801D134C *pNew;
    char *pData;
    void **pNewTail;
    char *pRest;
    int restSize;
    MemBlock_801D134C *pRestBlock;
    MemNode_801D134C *pRestNode;
    void **pRestTail;
    int n;

    if (align < 16) {
        align = 16;
    }
    align = (align + 15) & ~15;
    if (size < 16) {
        size = 16;
    }
    size = (size + 15) & ~15;
    if ((unsigned int)pBlock & 3) {
        return 0;
    }
    n = pBlock->mOffset;
    if ((unsigned int)(n - 12) > 500 || (n & 3)) {
        return 0;
    }
    pStart = (char *)pBlock - n + 12;
    pOld = (MemNode_801D134C *)(pStart + n);
    total = (char *)pBlock->mpTail - pStart + 4;
    if (*pBlock->mpTail != &pBlock->mpTail) {
        return 0;
    }
    pHeap = pBlock->mpHeap;
    n = pHeap ? pHeap->mDebugSize : 0;
    rem = fn_801D134C_Mod(pStart + n + 12, offset, align);
    if (rem) {
        extra = align - rem;
        if (n == 0 && extra < 2) {
            extra += align;
        }
        n += extra;
    }
    pNew = (MemBlock_801D134C *)(pStart + n);
    n += 12;
    pData = pStart + n;
    n += size;
    pNewTail = (void **)(pStart + n);
    used = n + 4;
    if (used > total) {
        return 0;
    }
    pRest = pStart + used;
    n = pHeap ? pHeap->mDebugSize : 0;
    rem = (unsigned int)(pRest + n + 12) & 15;
    if (rem) {
        extra = 16 - rem;
        if (n == 0 && extra < 2) {
            extra += 16;
        }
        n += extra;
    }
    restSize = total - used;
    pRestBlock = (MemBlock_801D134C *)(pRest + n);
    n += 12;
    pRestNode = (MemNode_801D134C *)(pRest + n);
    pRestTail = (void **)(pRest + restSize - 4);
    n = (char *)pRestTail - (char *)pRestNode;
    if (n < 16) {
        pNewTail = pRestTail;
        restSize = 0;
    }
    if (pHeap && pBlock->mState == 0) {
        fn_801D1620(pHeap, pOld);
    }
    memset(pStart, 0, pData - pStart);
    *(short *)pStart = pData - pStart;
    pNew->mOffset = pData - pStart;
    pNew->mState = 1;
    pNew->mpHeap = pHeap;
    pNew->mpTail = pNewTail;
    *pNewTail = &pNew->mpTail;
    if (restSize) {
        memset(pRest, 0, (char *)pRestNode - pRest);
        *(short *)pRest = (char *)pRestNode - pRest;
        pRestBlock->mOffset = (char *)pRestNode - pRest;
        pRestBlock->mState = 0;
        pRestBlock->mpHeap = pHeap;
        pRestBlock->mpTail = pRestTail;
        *pRestTail = &pRestBlock->mpTail;
        pRestNode->mSize = (char *)pRestTail - (char *)pRestNode;
        if (pHeap) {
            fn_801D1588(pHeap, pRestNode);
        }
    }
    return pNew;
}

static MemBlock_801D134C *fn_801D1ACC(MemNode_801D134C *pNode, int align, int offset, int size)
{
    MemBlock_801D134C *pResult;

    if (!pNode) {
        return 0;
    }
    if (pNode->mSize >= size) {
        if (pNode->mpLeft && (pResult = fn_801D1ACC(pNode->mpLeft, align, offset, size))) {
            return pResult;
        }
        if ((pResult = fn_801D18A0((MemBlock_801D134C *)pNode - 1, align, offset, size))) {
            return pResult;
        }
    }
    return fn_801D1ACC(pNode->mpRight, align, offset, size);
}

static MemBlock_801D134C *fn_801D1B64(MemHeap_801D134C *pHeap, int align, int offset, unsigned int size)
{
    MemBlock_801D134C *pBlock;
    MemBlock_801D134C *pResult;

    if (!pHeap) {
        return 0;
    }
    pBlock = (MemBlock_801D134C *)(pHeap->mpStart + *(short *)pHeap->mpStart - 12);
    while (pBlock->mState != 3) {
        if ((unsigned int)((char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4) >= size && pBlock->mState == 0) {
            if ((pResult = fn_801D18A0(pBlock, align, offset, size))) {
                return pResult;
            }
        }
        pBlock = (MemBlock_801D134C *)((char *)(pBlock->mpTail + 1) + *(short *)(pBlock->mpTail + 1) - 12);
    }
    return 0;
}

static MemBlock_801D134C *fn_801D1C14(MemBlock_801D134C *pBlock, int align, int offset, int size)
{
    char *pStart;
    MemNode_801D134C *pOld;
    unsigned int total;
    unsigned int used;
    MemHeap_801D134C *pHeap;
    unsigned int rem;
    unsigned int extra;
    unsigned int end;
    int hdr;
    char *pNewStart;
    MemBlock_801D134C *pNew;
    char *pData;
    void **pNewTail;
    int restSize;
    MemBlock_801D134C *pRestBlock;
    MemNode_801D134C *pRestNode;
    void **pRestTail;
    int n;

    if (align < 16) {
        align = 16;
    }
    align = (align + 15) & ~15;
    if ((unsigned int)pBlock & 3) {
        return 0;
    }
    if (size < 16) {
        size = 16;
    }
    size = (size + 15) & ~15;
    n = pBlock->mOffset;
    if ((unsigned int)(n - 12) > 500 || (n & 3)) {
        return 0;
    }
    pStart = (char *)pBlock - n + 12;
    pOld = (MemNode_801D134C *)(pStart + n);
    total = (char *)pBlock->mpTail - pStart + 4;
    if (*pBlock->mpTail != &pBlock->mpTail) {
        return 0;
    }
    end = (unsigned int)pBlock->mpTail - size;
    pData = (char *)(end / align * align);
    pHeap = pBlock->mpHeap;
    n = pHeap ? pHeap->mDebugSize : 0;
    if (n == 0) {
        n = 4;
    }
    hdr = n + 12;
    pNewStart = pData - hdr;
    pNew = (MemBlock_801D134C *)(pNewStart + n);
    n = hdr + (size + end % align);
    pNewTail = (void **)(pNewStart + n);
    n += 4;
    used = n;
    if (used > total) {
        return 0;
    }
    n = pHeap ? pHeap->mDebugSize : 0;
    rem = fn_801D134C_Mod(pStart, n + 12, 16);
    if (rem) {
        extra = 16 - rem;
        if (n == 0 && extra < 2) {
            extra += 16;
        }
        n += extra;
    }
    restSize = total - used;
    pRestBlock = (MemBlock_801D134C *)(pStart + n);
    n += 12;
    pRestNode = (MemNode_801D134C *)(pStart + n);
    pRestTail = (void **)(pStart + restSize - 4);
    n = (char *)pRestTail - (char *)pRestNode;
    if (n < 16) {
        return fn_801D18A0(pBlock, align, offset, size);
    }
    if (pHeap && pBlock->mState == 0) {
        fn_801D1620(pHeap, pOld);
    }
    memset(pNewStart, 0, pData - pNewStart);
    *(short *)pNewStart = pData - pNewStart;
    pNew->mOffset = pData - pNewStart;
    pNew->mState = 1;
    pNew->mpHeap = pHeap;
    pNew->mpTail = pNewTail;
    *pNewTail = &pNew->mpTail;
    if (restSize) {
        memset(pStart, 0, (char *)pRestNode - pStart);
        *(short *)pStart = (char *)pRestNode - pStart;
        pRestBlock->mOffset = (char *)pRestNode - pStart;
        pRestBlock->mState = 0;
        pRestBlock->mpHeap = pHeap;
        pRestBlock->mpTail = pRestTail;
        *pRestTail = &pRestBlock->mpTail;
        pRestNode->mSize = (char *)pRestTail - (char *)pRestNode;
        if (pHeap) {
            fn_801D1588(pHeap, pRestNode);
        }
    }
    return pNew;
}

static MemBlock_801D134C *fn_801D1E30(MemHeap_801D134C *pHeap, int align, int offset, unsigned int size)
{
    MemBlock_801D134C *pBlock;
    MemBlock_801D134C *pResult;

    if (pHeap == 0) {
        return 0;
    }
    for (pBlock = (MemBlock_801D134C *)(pHeap->mpEnd - 0x10); pBlock->mState != 2;
         pBlock = (MemBlock_801D134C *)((char *)((MemBlock_801D134C *)((char *)pBlock - pBlock->mOffset))->mpTail - 8)) {
        if ((unsigned int)((char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4) >= size && pBlock->mState == 0) {
            pResult = fn_801D1C14(pBlock, align, offset, size);
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
        result = fn_801D2130(pParams->mpHeap);
        if (result == 0) {
            lbl_803EBCC4 = pParams->mpHeap->mId;
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
        fn_801D2570(lbl_803EBCC8->mId);
    }
    lbl_803EBCC8 = 0;
    lbl_803EBCCC = 0;
    lbl_803EBCDC = 0;
    fn_801F80D0(&lbl_803E92AC);
    return 0;
}

void *fn_801D2478(int ident, int parentIdent, char *pStart, unsigned int size, int dataSize,
                  MemHeapFuncs_801D134C *pFuncs)
{
    MemHeap_801D134C *pHeap;
    int total;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
        if (ident == pHeap->mId || (pStart < pHeap->mpEnd && pStart + size > pHeap->mpStart)) {
            goto fail;
        }
    }
    if (dataSize == 0) {
        dataSize = 1;
    }
    total = dataSize + sizeof(MemHeap_801D134C);
    pHeap = fn_801D2BB0(parentIdent, total, 0, 0);
    if (pHeap == 0) {
        goto fail;
    }
    memset(pHeap, 0, total);
    pHeap->mId = ident;
    pHeap->mSize = size;
    pHeap->mpEnd = pStart + size;
    pHeap->mDebugSize = lbl_803EBCD8;
    pHeap->mpFuncs = pFuncs;
    pHeap->mpStart = pStart;
    pHeap->mDebug = lbl_803EBCDA;
    pHeap->mpSelf = pHeap;
    pHeap->mpNext = lbl_803EBCC8;
    lbl_803EBCC8 = pHeap;
    fn_801D1474();
    return pHeap + 1;
fail:
    return 0;
}

int fn_801D2570(int ident)
{
    MemHeap_801D134C **ppLink = &lbl_803EBCC8;
    MemHeap_801D134C *pHeap;
    MemHeap_801D134C *pParent;
    int freeStart = 0;
    int ownsMemory;
    char *pStart;

    while ((pHeap = *ppLink) != 0) {
        if (ident == -1 || ident == pHeap->mId) {
            if (pHeap->mpParent != 0) {
                freeStart = 1;
                for (pParent = pHeap->mpParent; pParent != 0; pParent = pParent->mpSub) {
                    if (pParent->mpSub == pHeap) {
                        pParent->mpSub = pHeap->mpSub;
                        break;
                    }
                }
            }
            ownsMemory = pHeap->mOwnsMemory;
            *ppLink = pHeap->mpNext;
            pStart = pHeap->mpStart;
            if (pHeap->mpFuncs != 0) {
                pHeap->mpFuncs->mDestroy(pHeap + 1);
                fn_801D2BD0(pHeap);
            } else if (pHeap->mFill != 0x80) {
                memset(pStart, pHeap->mFill, pHeap->mSize);
            }
            if (freeStart) {
                fn_801D2BD0(pStart);
            }
            if (ownsMemory) {
                fn_801D34CC(pStart);
            }
        } else {
            ppLink = &pHeap->mpNext;
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

int fn_801D26C4(int ident, int flags, const char *pMessage)
{
    if (lbl_803EBCF4 != 0) {
        lbl_803EBCF4(ident, flags | 0x20, pMessage, 0);
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
    MemHeap_801D134C *pHeap;

    for (ident = 1;; ident++) {
        if ((ident & -ident) != ident) {
            for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
                if (pHeap->mId == ident) {
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
    MemHeap_801D134C *pHeap = lbl_803EBCCC;
    int ident = 1;

    if (pHeap != 0) {
        ident = pHeap->mId;
    }
    return ident;
}

char *fn_801D27B8(int ident)
{
    char *pStart = 0;
    MemHeap_801D134C *pHeap = fn_801D134C(ident);

    if (pHeap != 0) {
        pStart = pHeap->mpStart;
    }
    return pStart;
}

unsigned int fn_801D27F4(int ident)
{
    unsigned int largest = 0;
    MemHeap_801D134C *pHeap = fn_801D134C(ident);
    MemNode_801D134C *pNode;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mpFuncs != 0) {
        return pHeap->mpFuncs->mInfo(pHeap + 1, 3);
    }
    for (pNode = pHeap->mRoot.mpRight; pNode != 0; pNode = pNode->mpRight) {
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
    MemHeap_801D134C *pHeap = fn_801D13A4(pAddr);
    MemBlock_801D134C *pBlock;
    int size;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mpFuncs != 0) {
        return pHeap->mpFuncs->mSizeof(pHeap + 1, pAddr);
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
    MemHeap_801D134C *pSrcHeap;
    MemHeap_801D134C *pDstHeap;
    int kind;

    if (size <= 0) {
        return;
    }
    pSrcHeap = fn_801D13A4(pSrc);
    pDstHeap = fn_801D13A4(pDst);
    kind = 0;
    if (pSrcHeap != 0 && pSrcHeap->mpFuncs != 0) {
        kind = 1;
    }
    if (pDstHeap != 0 && pDstHeap->mpFuncs != 0) {
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
    MemHeap_801D134C *pHeap;
    int i;
    char *pOut;

    if (pLabel == 0) {
        pLabel = lbl_802AF9BC;
    }
    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
        if (ident == -1 || ident == pHeap->mId) {
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
    MemHeap_801D134C *pHeap;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
        if (ident == -1 || ident == pHeap->mId) {
            if (pHeap->mLabelDepth < 5) {
                pHeap->mLabelDepth++;
                strcpy(pHeap->mLabels[pHeap->mLabelDepth], pHeap->mLabels[pHeap->mLabelDepth - 1]);
            }
        }
    }
}

void fn_801D342C(int ident)
{
    MemHeap_801D134C *pHeap;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
        if (ident == -1 || ident == pHeap->mId) {
            if (pHeap->mLabelDepth != 0) {
                pHeap->mLabelDepth--;
            }
        }
    }
}

void fn_801D3470(void *pAddr, char *pOut)
{
    MemBlock_801D134C *pBlock = (MemBlock_801D134C *)((char *)pAddr - 0xC);
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
