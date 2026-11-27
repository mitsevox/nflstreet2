/* The engine memory manager: creates the game's heaps over the console arenas, allocates, resizes
   and frees blocks from size-ordered free trees, and keeps debug labels and sentinel hooks. */
#include "game/fn_801D2B7C.h"
#include "engine/Memory.h"
#include "engine/llmemory.h"
#include <string.h>
#include "engine/SysCriticalSection.h"

typedef struct MemHeapRange_t {
    char *mpStart;
    char *mpEnd;
    int mId;
    MemHeap_t *mpHeap;
} MemHeapRange_t;

typedef struct MemDebugInfo_t {
    char mUnknown0[0x4];
    int mSerial;
    unsigned int mSize;
    char mFile[0x2C - 0xC];
    char mLabel[16];
    char mName[16];
    char mGuard[16];
    int mExtra;
} MemDebugInfo_t;

typedef struct MemHeapDesc_t {
    char mName[8];
    int mId;
    char *mStart;
    unsigned int mSize;
    unsigned short mAlign;
} MemHeapDesc_t;

typedef struct MemInitParams_t {
    char mUnknown0[0x40];
    MemHeapDesc_t *mpHeap;
} MemInitParams_t;

extern int lbl_803EBCC4;
extern void (*lbl_803EBCD4)(void);
extern unsigned short lbl_803EBCD8;
extern unsigned char lbl_803EBCDA;
extern unsigned char lbl_803EBCDB;
extern unsigned char lbl_803EBCDC;
extern unsigned char lbl_803EBCE4;
extern int lbl_803EBCE8;
extern MemHeap_t *lbl_803EBCC8;
extern MemHeap_t *lbl_803EBCCC;
extern int lbl_803EBCD0;
static MemHeapRange_t _Mem_pAddrToHeap[16];
extern void (*lbl_803EBCEC)(void);
extern int (*lbl_803EBCF0)(int a, void *pAddr);
extern int (*lbl_803EBCF4)(int ident, int flags, const char *pMessage, int d);
SysCriticalSection_t _Mem_Crit;
extern const char lbl_802AF9BC[];
extern const char lbl_802AF628[];
extern const char lbl_802AF9A4[];
extern const char lbl_802AF9B0[];

extern void *memset(void *pDst, int value, unsigned int size);
extern void *memcpy();
extern int sprintf(char *pDst, const char *pFormat, ...);

static void *_MemAllocInternal(int ident, unsigned int size, int flags, int offset);
void *MemHReallocMem(int ident, void *pAddr, int size, int flags, int offset);
extern int SysGetSystemTime(void);
int fn_801D2130(MemHeapDesc_t *pParams);
extern int fn_801D2570(int ident);

static MemHeap_t *_FindHeapByIdent(int id)
{
    MemHeap_t *pHeap = lbl_803EBCCC;

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

static MemHeap_t *_FindHeapByAddr(char *pAddr)
{
    int lo = 0;
    int hi = lbl_803EBCD0 - 1;
    int mid;
    MemHeap_t *pHeap;
    MemHeap_t *pSub;

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (pAddr < _Mem_pAddrToHeap[mid].mpStart) {
            hi = mid - 1;
        } else if (pAddr >= _Mem_pAddrToHeap[mid].mpEnd) {
            lo = mid + 1;
        } else {
            pHeap = _Mem_pAddrToHeap[mid].mpHeap;
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

static void _BuildHeapAddrTable(void)
{
    MemHeap_t *pHeap;
    MemHeapRange_t *pRange;
    MemHeapRange_t *pPrev;
    MemHeapRange_t tmp;
    int i;

    i = 0;
    for (pHeap = lbl_803EBCC8; pHeap; pHeap = pHeap->mpNext) {
        if (!pHeap->mpParent && i < 16) {
            _Mem_pAddrToHeap[i].mpStart = pHeap->mpStart;
            _Mem_pAddrToHeap[i].mpEnd = pHeap->mpEnd;
            _Mem_pAddrToHeap[i].mId = pHeap->mId;
            _Mem_pAddrToHeap[i].mpHeap = pHeap;
            i++;
        }
    }
    lbl_803EBCD0 = i;
    for (i = 1; i < lbl_803EBCD0; i++) {
        pRange = &_Mem_pAddrToHeap[i];
        pPrev = &_Mem_pAddrToHeap[i - 1];
        if (pPrev->mpStart > pRange->mpStart) {
            tmp = *pPrev;
            *pPrev = *pRange;
            *pRange = tmp;
            if (i > 1) {
                i -= 2;
            }
        }
    }
}

static void _FreeListInsert(MemHeap_t *pHeap, MemNode_t *pNode)
{
    MemNode_t *pParent = &pHeap->mRoot;
    MemNode_t **ppLink = &pHeap->mRoot.mpRight;
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

static void _FreeListDelete(MemHeap_t *pHeap, MemNode_t *pNode)
{
    MemNode_t *pParent;
    MemNode_t *pPred;

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
        pPred = pNode->mpLeft;
        do {
            pPred = pPred->mpRight;
        } while (pPred->mpRight);
        pPred->mpParent->mpRight = pPred->mpLeft;
        if (pPred->mpLeft) {
            pPred->mpLeft->mpParent = pPred->mpParent;
        }
        pParent = pNode->mpParent;
        if (pParent->mpLeft == pNode) {
            pParent->mpLeft = pPred;
        } else {
            pParent->mpRight = pPred;
        }
        pPred->mpParent = pNode->mpParent;
        pPred->mpLeft = pNode->mpLeft;
        pPred->mpRight = pNode->mpRight;
        pPred->mpLeft->mpParent = pPred;
        pPred->mpRight->mpParent = pPred;
    }
}

static int _ShortenBlock(MemBlock_t *pBlock, int size)
{
    void **pTail;
    char *pNext;
    int n;
    MemBlock_t *pFree;
    MemNode_t *pNode;
    unsigned int rem;
    int need;

    if (size < 16) {
        size = 16;
    }
    size = (size + 15) & ~15;
    pTail = pBlock->mpTail;
    need = size + 4;
    n = (char *)pTail - (char *)*pTail - need;
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
    pFree = (MemBlock_t *)(pNext + n);
    pNode = (MemNode_t *)(pFree + 1);
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
    _FreeListInsert(pBlock->mpHeap, pNode);
    return size;
}

static MemBlock_t *_SplitBlock(MemBlock_t *pBlock, int align, int offset, int size)
{
    char *pStart;
    MemNode_t *pOld;
    unsigned int total;
    unsigned int used;
    MemHeap_t *pHeap;
    unsigned int rem;
    unsigned int extra;
    MemBlock_t *pNew;
    char *pData;
    void **pNewTail;
    char *pRest;
    int restSize;
    MemBlock_t *pRestBlock;
    MemNode_t *pRestNode;
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
    pOld = (MemNode_t *)(pStart + n);
    total = (char *)pBlock->mpTail - pStart + 4;
    if (*pBlock->mpTail != &pBlock->mpTail) {
        return 0;
    }
    pHeap = pBlock->mpHeap;
    n = pHeap ? pHeap->mDebugSize : 0;
    rem = ((unsigned int)(pStart + n + 12) + offset) % (unsigned int)align;
    if (rem) {
        extra = align - rem;
        if (n == 0 && extra < 2) {
            extra += align;
        }
        n += extra;
    }
    pNew = (MemBlock_t *)(pStart + n);
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
    pRestBlock = (MemBlock_t *)(pRest + n);
    n += 12;
    pRestNode = (MemNode_t *)(pRest + n);
    pRestTail = (void **)(pRest + restSize - 4);
    n = (char *)pRestTail - (char *)pRestNode;
    if (n < 16) {
        pNewTail = pRestTail;
        restSize = 0;
    }
    if (pHeap && pBlock->mState == 0) {
        _FreeListDelete(pHeap, pOld);
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
            _FreeListInsert(pHeap, pRestNode);
        }
    }
    return pNew;
}

static MemBlock_t *_FindAndSplit(MemNode_t *pNode, int align, int offset, int size)
{
    MemBlock_t *pResult;

    if (!pNode) {
        return 0;
    }
    if (pNode->mSize >= size) {
        if (pNode->mpLeft && (pResult = _FindAndSplit(pNode->mpLeft, align, offset, size))) {
            return pResult;
        }
        if ((pResult = _SplitBlock((MemBlock_t *)pNode - 1, align, offset, size))) {
            return pResult;
        }
    }
    return _FindAndSplit(pNode->mpRight, align, offset, size);
}

static MemBlock_t *_FindAndSplitHead(MemHeap_t *pHeap, int align, int offset, unsigned int size)
{
    MemBlock_t *pBlock;
    MemBlock_t *pResult;

    if (!pHeap) {
        return 0;
    }
    pBlock = (MemBlock_t *)(pHeap->mpStart + *(short *)pHeap->mpStart - 12);
    while (pBlock->mState != 3) {
        if ((unsigned int)((char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4) >= size && pBlock->mState == 0) {
            if ((pResult = _SplitBlock(pBlock, align, offset, size))) {
                return pResult;
            }
        }
        pBlock = (MemBlock_t *)((char *)(pBlock->mpTail + 1) + *(short *)(pBlock->mpTail + 1) - 12);
    }
    return 0;
}

static MemBlock_t *_SplitBlockTail(MemBlock_t *pBlock, int align, int offset, int size)
{
    char *pStart;
    MemNode_t *pOld;
    unsigned int total;
    unsigned int used;
    MemHeap_t *pHeap;
    unsigned int rem;
    unsigned int extra;
    unsigned int end;
    int hdr;
    char *pNewStart;
    MemBlock_t *pNew;
    char *pData;
    void **pNewTail;
    int restSize;
    MemBlock_t *pRestBlock;
    MemNode_t *pRestNode;
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
    pOld = (MemNode_t *)(pStart + n);
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
    pNew = (MemBlock_t *)(pNewStart + n);
    n = hdr + (size + end % align);
    pNewTail = (void **)(pNewStart + n);
    n += 4;
    used = n;
    if (used > total) {
        return 0;
    }
    n = pHeap ? pHeap->mDebugSize : 0;
    rem = ((unsigned int)pStart + (n + 12)) % 16u;
    if (rem) {
        extra = 16 - rem;
        if (n == 0 && extra < 2) {
            extra += 16;
        }
        n += extra;
    }
    restSize = total - used;
    pRestBlock = (MemBlock_t *)(pStart + n);
    n += 12;
    pRestNode = (MemNode_t *)(pStart + n);
    pRestTail = (void **)(pStart + restSize - 4);
    n = (char *)pRestTail - (char *)pRestNode;
    if (n < 16) {
        return _SplitBlock(pBlock, align, offset, size);
    }
    if (pHeap && pBlock->mState == 0) {
        _FreeListDelete(pHeap, pOld);
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
            _FreeListInsert(pHeap, pRestNode);
        }
    }
    return pNew;
}

static MemBlock_t *_FindAndSplitTail(MemHeap_t *pHeap, int align, int offset, unsigned int size)
{
    MemBlock_t *pBlock;
    MemBlock_t *pResult;

    if (pHeap == 0) {
        return 0;
    }
    for (pBlock = (MemBlock_t *)(pHeap->mpEnd - 0x10); pBlock->mState != 2;
         pBlock = (MemBlock_t *)((char *)((MemBlock_t *)((char *)pBlock - pBlock->mOffset))->mpTail - 8)) {
        if ((unsigned int)((char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4) >= size && pBlock->mState == 0) {
            pResult = _SplitBlockTail(pBlock, align, offset, size);
            if (pResult != 0) {
                return pResult;
            }
        }
    }
    return 0;
}

static void _DebugSetup(MemDebugInfo_t *pInfo, const char *pFile, unsigned int line, const char *pLabel,
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
        pInfo->mSerial = SysGetSystemTime();
    }
}

static void _PrintDefault(void)
{
}

int MemInit(MemInitParams_t *pParams)
{
    int result = 0;

    SysInitCriticalSectionFunc(&_Mem_Crit);
    lbl_803EBCC8 = 0;
    lbl_803EBCCC = 0;
    lbl_803EBCD4 = _PrintDefault;
    if (pParams != 0) {
        result = fn_801D2130(pParams->mpHeap);
        if (result == 0) {
            lbl_803EBCC4 = pParams->mpHeap->mId;
        }
    }
    return result;
}

int MemShutdown(void)
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
    SysShutdownCriticalSectionFunc(&_Mem_Crit);
    return 0;
}

int fn_801D2130(MemHeapDesc_t *pParams)
{
    int ownsMemory = 0;
    int ident = pParams->mId;
    unsigned int align = pParams->mAlign;
    char *pStart = pParams->mStart;
    unsigned int size = pParams->mSize;
    MemHeap_t *pScan;
    MemHeap_t *pHeap;
    MemHeap_t *pParent;
    MemBlock_t *pBlock;
    MemDebugInfo_t *pInfo;
    unsigned int misalign;
    char *pEnd;
    char *pData;

    for (pScan = lbl_803EBCC8; pScan != 0; pScan = pScan->mpNext) {
        if (ident == pScan->mId) {
            return 0x10004;
        }
    }
    if (pStart == (char *)-1) {
        ownsMemory = 1;
        pStart = MemGetMemLL(size);
        if (pStart == 0) {
            size = 0;
        }
    }
    pParent = _FindHeapByIdent((int)pStart);
    if (pParent != 0) {
        pStart = fn_801D2BB0(pParent->mId, size, 0, 0);
        if (pStart == 0) {
            size = 0;
        }
    } else {
        for (pScan = lbl_803EBCC8; pScan != 0; pScan = pScan->mpNext) {
            if (pStart < pScan->mpEnd && pStart + size > pScan->mpStart) {
                size = 0;
                break;
            }
        }
    }
    misalign = (unsigned int)pStart & 15;
    if (misalign != 0 || size <= 0xFF) {
        if (pParent != 0 && pStart != 0) {
            fn_801D2BD0(pStart);
        }
        return 0x10009;
    }
    memset(pStart, 0, size);
    pEnd = pStart + size;
    pBlock = (MemBlock_t *)(pEnd - 0x10);
    pBlock->mOffset = 12;
    pBlock->mState = 3;
    pBlock->mpTail = (void **)(pEnd - 4);
    *(void ***)(pEnd - 4) = &pBlock->mpTail;
    pBlock = (MemBlock_t *)pStart;
    pBlock->mOffset = 12;
    pBlock->mState = 2;
    pBlock->mpTail = (void **)(pEnd - 0x14);
    *(void ***)(pEnd - 0x14) = &pBlock->mpTail;
    if (_SplitBlock(pBlock, 16, 0, sizeof(MemHeap_t)) == 0) {
        return 0x10006;
    }
    pHeap = (MemHeap_t *)(pStart + pBlock->mOffset);
    pBlock = (MemBlock_t *)pHeap - 1;
    pBlock->mState = 2;
    pBlock->mpHeap = pHeap;
    pHeap->mId = ident;
    pHeap->mAlign = (align + 15) & ~15;
    pHeap->mpStart = pStart;
    pHeap->mpEnd = pEnd;
    pHeap->mDebugBytes = 0;
    pHeap->mUnk74 = 0x7FFFFFFF;
    pHeap->mDebugSize = lbl_803EBCD8;
    pHeap->mpSelf = pHeap;
    pHeap->mSize = size;
    pHeap->mDebug = lbl_803EBCDA;
    pHeap->mMinLargestFree = size;
    pHeap->mOwnsMemory = ownsMemory;
    pHeap->mFill = lbl_803EBCDB;
    strcpy(pHeap->mName, pParams->mName);
    if (pBlock->mOffset > 0x6B) {
        pInfo = (MemDebugInfo_t *)((char *)pBlock - (pBlock->mOffset - 0xC));
    } else {
        pInfo = 0;
    }
    if (pInfo != 0) {
        memset(pInfo->mGuard, '*', sizeof(pInfo->mGuard));
        memcpy(pInfo->mLabel, lbl_802AF9A4, 11);
        memcpy(pInfo->mName, lbl_802AF9A4, 11);
        memcpy(pInfo->mFile, lbl_802AF9B0, 11);
    }
    pData = (char *)pBlock->mpTail + (*(short *)((char *)pBlock->mpTail + 4) + 4);
    pBlock = (MemBlock_t *)(pData - 0xC);
    pBlock->mpHeap = pHeap;
    _FreeListInsert(pHeap, (MemNode_t *)pData);
    pHeap->mUsedBytes = pHeap->mSize - pHeap->mFreeBytes;
    ((MemBlock_t *)((char *)pBlock->mpTail + 4 + *(short *)((char *)pBlock->mpTail + 4)) - 1)->mpHeap = pHeap;
    pHeap->mpNext = lbl_803EBCC8;
    lbl_803EBCC8 = pHeap;
    if (pParent != 0) {
        pHeap->mpSub = pParent->mpSub;
        pParent->mpSub = pHeap;
    } else {
        pHeap->mpSub = 0;
    }
    pHeap->mpParent = pParent;
    _BuildHeapAddrTable();
    if (lbl_803EBCCC == 0) {
        lbl_803EBCCC = pHeap;
    }
    return 0;
}

void *MemCustomHeap(int ident, int parentIdent, char *pStart, unsigned int size, int dataSize,
                  MemHeapFuncs_t *pFuncs)
{
    MemHeap_t *pHeap;
    int total;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
        if (ident == pHeap->mId || (pStart < pHeap->mpEnd && pStart + size > pHeap->mpStart)) {
            goto fail;
        }
    }
    if (dataSize == 0) {
        dataSize = 1;
    }
    total = dataSize + sizeof(MemHeap_t);
    pHeap = fn_801D2BB0(parentIdent, total, 0, 0);
    if (pHeap == 0) {
        goto fail;
    }
    memset(pHeap, 0, total);
    pHeap->mId = ident;
    pHeap->mpSelf = pHeap;
    pHeap->mpStart = pStart;
    pHeap->mSize = size;
    pHeap->mpEnd = pStart + size;
    pHeap->mDebugSize = lbl_803EBCD8;
    pHeap->mDebug = lbl_803EBCDA;
    pHeap->mpFuncs = pFuncs;
    pHeap->mpNext = lbl_803EBCC8;
    lbl_803EBCC8 = pHeap;
    _BuildHeapAddrTable();
    return pHeap + 1;
fail:
    return 0;
}

int fn_801D2570(int ident)
{
    MemHeap_t **ppLink = &lbl_803EBCC8;
    MemHeap_t *pHeap;
    MemHeap_t *pParent;
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
                MemFreeMemLL(pStart);
            }
        } else {
            ppLink = &pHeap->mpNext;
        }
    }
    _BuildHeapAddrTable();
    return 0;
}

void MemCheckSentinelAll(int ident)
{
    if (lbl_803EBCEC != 0) {
        lbl_803EBCEC();
    }
}

int MemHeapBreakdown(int ident, int flags, const char *pMessage)
{
    if (lbl_803EBCF4 != 0) {
        lbl_803EBCF4(ident, flags | 0x20, pMessage, 0);
    }
    return 0;
}

int MemHeapActive(int ident)
{
    return _FindHeapByIdent(ident) != 0;
}

int fn_801D2730(void)
{
    int ident;
    MemHeap_t *pHeap;

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

void MemSetDefaultHeap(int ident)
{
    lbl_803EBCCC = _FindHeapByIdent(ident);
}

int fn_801D27A0(void)
{
    MemHeap_t *pHeap = lbl_803EBCCC;
    int ident = 1;

    if (pHeap != 0) {
        ident = pHeap->mId;
    }
    return ident;
}

char *MemGetHeapStart(int ident)
{
    char *pStart = 0;
    MemHeap_t *pHeap = _FindHeapByIdent(ident);

    if (pHeap != 0) {
        pStart = pHeap->mpStart;
    }
    return pStart;
}

unsigned int fn_801D27F4(int ident)
{
    unsigned int largest = 0;
    MemHeap_t *pHeap = _FindHeapByIdent(ident);
    MemNode_t *pNode;

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

int MemCheckSentinel(int a, void *pAddr)
{
    if (lbl_803EBCF0 != 0) {
        lbl_803EBCF0(a, pAddr);
    }
    return 0;
}

static void *_MemAllocInternal(int ident, unsigned int size, int flags, int offset)
{
    MemHeap_t *pHeap = _FindHeapByIdent(ident);
    const char *pName = lbl_802AF9BC;
    const char *pContext = pName;
    const char *pFile = pContext;
    MemBlock_t *pBlock;
    MemDebugInfo_t *pInfo;
    void *pResult;
    unsigned int align;
    unsigned int used;
    unsigned int largest;

    if (pHeap == 0 || size > pHeap->mSize) {
        goto fail;
    }
    if (size == 0) {
        size = 1;
    }
    pName = pHeap->mLabels[pHeap->mLabelDepth];
    if (pHeap->mpFuncs != 0) {
        pResult = pHeap->mpFuncs->mAlloc(pHeap + 1, size, flags, pName, pContext, pContext, 0);
        if (pResult == 0 && pHeap->mpFailHook != 0) {
            pHeap->mpFailHook(pHeap->mId, size);
        }
        return pResult;
    }
    if (pHeap->mDebug) {
        MemCheckSentinelAll(pHeap->mId);
    }
    SysEnterCriticalSectionFunc(&_Mem_Crit);
    align = 16;
    if (flags & 0x20) {
        align = 32;
    }
    if (flags & 0x40) {
        align = 64;
    }
    if (flags & 0x80) {
        align = 128;
    }
    if (flags & 0x100) {
        align = 256;
    }
    if (align < pHeap->mAlign) {
        align = pHeap->mAlign;
    }
    if (flags & 2) {
        pBlock = _FindAndSplitHead(pHeap, align, offset, size);
    } else if (flags & 4) {
        pBlock = _FindAndSplitTail(pHeap, align, offset, size);
    } else {
        pBlock = _FindAndSplit(&pHeap->mRoot, align, offset, size);
    }
    if (pBlock == 0) {
        if (lbl_803EBCF4 != 0) {
            lbl_803EBCF4(pHeap->mId, 18, 0, size);
        }
        SysExitCriticalSectionFunc(&_Mem_Crit);
    fail:
        if (pHeap->mpFailHook != 0) {
            pHeap->mpFailHook(pHeap->mId, size);
        }
        return 0;
    }
    used = ((char *)pBlock->mpTail - (char *)*pBlock->mpTail) + pBlock->mOffset;
    pHeap->mUsedBytes += used;
    pHeap->mNumUsed++;
    if (pHeap->mUsedBytes > pHeap->mMaxUsedBytes) {
        pHeap->mMaxUsedBytes = pHeap->mUsedBytes;
    }
    if (pHeap->mNumUsed > pHeap->mMaxUsed) {
        pHeap->mMaxUsed = pHeap->mNumUsed;
    }
    largest = fn_801D27F4(pHeap->mId);
    if (pHeap->mMinLargestFree > largest) {
        pHeap->mMinLargestFree = largest;
    }
    pHeap->mAllocCount++;
    if (pBlock->mOffset > 0x6B) {
        pInfo = (MemDebugInfo_t *)((char *)pBlock - (pBlock->mOffset - 0xC));
    } else {
        pInfo = 0;
    }
    if (pInfo != 0) {
        _DebugSetup(pInfo, pFile, 0, pContext, pName, pHeap->mDebugExtra);
        pInfo->mSize = (char *)pBlock->mpTail - (char *)*pBlock->mpTail + 12;
        pHeap->mDebugBytes += pInfo->mSize;
        if (pHeap->mDebugBytes > pHeap->mMaxDebugBytes) {
            pHeap->mMaxDebugBytes = pHeap->mDebugBytes;
        }
    }
    SysExitCriticalSectionFunc(&_Mem_Crit);
    return pBlock + 1;
}

void *fn_801D2B7C(int size, int a, int b)
{
    return _MemAllocInternal(0, size, a, b);
}

void *fn_801D2BB0(int a, int size, int ident, int flags)
{
    return _MemAllocInternal(a, size, ident, flags);
}

int fn_801D2BD0(void *pAddr)
{
    MemHeap_t *pHeap = _FindHeapByAddr(pAddr);
    MemBlock_t *pBlock;
    MemBlock_t *pNext;
    MemBlock_t *pPrev;
    char *pData;
    void **pLink;
    MemDebugInfo_t *pInfo;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mpFuncs != 0) {
        return pHeap->mpFuncs->mFree(pHeap + 1, pAddr);
    }
    pBlock = (MemBlock_t *)((char *)pAddr - 0xC);
    if (pBlock->mState != 1) {
        return 0x10009;
    }
    if (pBlock->mpHeap != pHeap) {
        return 0x10003;
    }
    if (pHeap->mDebug) {
        MemCheckSentinel(pHeap->mId, pAddr);
        MemCheckSentinelAll(pHeap->mId);
    }
    SysEnterCriticalSectionFunc(&_Mem_Crit);
    pHeap->mUsedBytes -= ((char *)pBlock->mpTail - (char *)*pBlock->mpTail) + pBlock->mOffset;
    pHeap->mNumUsed--;
    pHeap->mFreeCount++;
    if (pBlock->mOffset > 0x6B) {
        pInfo = (MemDebugInfo_t *)((char *)pBlock - (pBlock->mOffset - 0xC));
    } else {
        pInfo = 0;
    }
    if (pInfo != 0) {
        pHeap->mDebugBytes -= pInfo->mSize;
    }
    if (pHeap->mFill != 0x80) {
        memset(pBlock + 1, pHeap->mFill, (char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4);
    }
    pData = (char *)pBlock->mpTail + (*(short *)((char *)pBlock->mpTail + 4) + 4);
    pNext = (MemBlock_t *)(pData - 0xC);
    if (pNext->mState == 0) {
        _FreeListDelete(pHeap, (MemNode_t *)pData);
        pBlock->mpTail = pNext->mpTail;
        *pBlock->mpTail = &pBlock->mpTail;
        memset((char *)pNext - pNext->mOffset + 0xC, pHeap->mFill, pNext->mOffset);
    }
    pLink = ((MemBlock_t *)((char *)pBlock - pBlock->mOffset))->mpTail;
    pPrev = (MemBlock_t *)((char *)pLink - 8);
    if (pPrev->mState == 0) {
        _FreeListDelete(pHeap, (MemNode_t *)(pLink + 1));
        pPrev->mpTail = pBlock->mpTail;
        *pPrev->mpTail = pLink;
        memset((char *)pBlock - pBlock->mOffset + 0xC, pHeap->mFill, pBlock->mOffset);
        pBlock = pPrev;
    }
    if (pBlock->mOffset > 0x6B) {
        pInfo = (MemDebugInfo_t *)((char *)pBlock - (pBlock->mOffset - 0xC));
    } else {
        pInfo = 0;
    }
    if (pInfo != 0) {
        memset(pInfo->mGuard, '*', sizeof(pInfo->mGuard));
        if (pInfo->mLabel[0] != 0) {
            pInfo->mLabel[0] = '*';
        }
        if (pInfo->mName[0] != 0) {
            pInfo->mName[0] = '*';
        }
        if (pInfo->mFile[0] != 0) {
            pInfo->mFile[0] = '*';
        }
    }
    pBlock->mState = 0;
    ((MemNode_t *)(pBlock + 1))->mSize = (char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4;
    _FreeListInsert(pHeap, (MemNode_t *)(pBlock + 1));
    SysExitCriticalSectionFunc(&_Mem_Crit);
    return 0;
}

void *MemHReallocMem(int ident, void *pAddr, int size, int flags, int offset)
{
    MemHeap_t *pHeap = _FindHeapByAddr(pAddr);
    MemBlock_t *pBlock;
    MemBlock_t *pNext;
    MemDebugInfo_t *pInfo;
    void *pNew;
    int oldSize;
    int avail;
    int need;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mpFuncs != 0) {
        return pHeap->mpFuncs->mResize(pHeap + 1, pAddr, size, flags);
    }
    pBlock = (MemBlock_t *)((char *)pAddr - 0xC);
    if (pBlock->mState != 1 || pBlock->mpHeap != pHeap) {
        return 0;
    }
    if (pHeap->mDebug) {
        MemCheckSentinel(ident, pAddr);
        MemCheckSentinelAll(pHeap->mId);
    }
    SysEnterCriticalSectionFunc(&_Mem_Crit);
    pNext = (MemBlock_t *)((char *)pBlock->mpTail + 4 + *(short *)((char *)pBlock->mpTail + 4)) - 1;
    oldSize = (char *)pBlock->mpTail - (char *)*pBlock->mpTail - 4;
    if (pNext->mState == 0) {
        if (pBlock->mOffset > 0x6B) {
            pInfo = (MemDebugInfo_t *)((char *)pBlock - (pBlock->mOffset - 0xC));
        } else {
            pInfo = 0;
        }
        if (pInfo != 0) {
            pInfo->mSize += ((char *)pNext->mpTail - (char *)*pNext->mpTail) + pNext->mOffset;
            pHeap->mDebugBytes += ((char *)pNext->mpTail - (char *)*pNext->mpTail) + pNext->mOffset;
        }
        pHeap->mUsedBytes += ((char *)pNext->mpTail - (char *)*pNext->mpTail) + pNext->mOffset;
        _FreeListDelete(pHeap, (MemNode_t *)(pNext + 1));
        pBlock->mpTail = pNext->mpTail;
        *pBlock->mpTail = &pBlock->mpTail;
        memset((char *)pNext - pNext->mOffset + 0xC, 0, pNext->mOffset);
    }
    avail = (char *)pBlock->mpTail - (char *)*pBlock->mpTail;
    need = size + 4;
    if (avail - need < 0) {
        pNew = _MemAllocInternal(ident, size, flags, offset);
        if (pNew == 0) {
            fn_801D2BD0(pAddr);
            SysExitCriticalSectionFunc(&_Mem_Crit);
            return 0;
        }
        memcpy(pNew, pAddr, oldSize);
        fn_801D2BD0(pAddr);
        pAddr = pNew;
    } else {
        pHeap->mUsedBytes -= avail + pBlock->mOffset;
        _ShortenBlock(pBlock, size);
        pHeap->mUsedBytes += ((char *)pBlock->mpTail - (char *)*pBlock->mpTail) + pBlock->mOffset;
        if (pBlock->mOffset > 0x6B) {
            pInfo = (MemDebugInfo_t *)((char *)pBlock - (pBlock->mOffset - 0xC));
        } else {
            pInfo = 0;
        }
        if (pInfo != 0) {
            pHeap->mDebugBytes -= pInfo->mSize;
            pInfo->mSize = (char *)pBlock->mpTail - (char *)*pBlock->mpTail + 12;
            pHeap->mDebugBytes += pInfo->mSize;
        }
    }
    SysExitCriticalSectionFunc(&_Mem_Crit);
    return pAddr;
}

void *MemReallocMem(void *pAddr, int size, int ident, int flags)
{
    return MemHReallocMem(0, pAddr, size, ident, flags);
}

int MemGetSizeByAddr(int a, void *pAddr)
{
    MemHeap_t *pHeap = _FindHeapByAddr(pAddr);
    void **pTail;
    int size;

    if (pHeap == 0) {
        return 0;
    }
    if (pHeap->mpFuncs != 0) {
        return pHeap->mpFuncs->mSizeof(pHeap + 1, pAddr);
    }
    if (pHeap->mDebug) {
        MemCheckSentinel(a, pAddr);
    }
    SysEnterCriticalSectionFunc(&_Mem_Crit);
    pTail = ((void ***)pAddr)[-1];
    size = (char *)pTail - (char *)*pTail - 4;
    SysExitCriticalSectionFunc(&_Mem_Crit);
    return size;
}

void MemCopy(void *pDst, void *pSrc, int size)
{
    MemHeap_t *pSrcHeap;
    MemHeap_t *pDstHeap;
    int kind;

    if (size <= 0) {
        return;
    }
    pSrcHeap = _FindHeapByAddr(pSrc);
    pDstHeap = _FindHeapByAddr(pDst);
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
    MemHeap_t *pHeap;
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
    MemHeap_t *pHeap;

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
    MemHeap_t *pHeap;

    for (pHeap = lbl_803EBCC8; pHeap != 0; pHeap = pHeap->mpNext) {
        if (ident == -1 || ident == pHeap->mId) {
            if (pHeap->mLabelDepth != 0) {
                pHeap->mLabelDepth--;
            }
        }
    }
}

void MemGetGroupLabelByAddr(void *pAddr, char *pOut, int size)
{
    MemBlock_t *pBlock = (MemBlock_t *)((char *)pAddr - 0xC);
    char *pDebug;

    if (pBlock->mOffset > 0x6B) {
        pDebug = (char *)pBlock - (pBlock->mOffset - 0xC);
    } else {
        pDebug = 0;
    }
    if (pDebug != 0) {
        strnzcpy(pOut, pDebug + 0x3C, size);
    }
}
