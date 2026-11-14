/* External-region heap: tracks allocated and free spans in a separate block map.
   The Sys module uses this allocator for auxiliary RAM. */
#include "engine/Memory.h"
#include "engine/MemExtern.h"

typedef struct MemExternHeap_t {
    int mIdent;
    unsigned char mKind;
    char *mBase;
    unsigned int mSize;
    unsigned int mAlign;
    int mNumAllocs;
    int unk_0x18;
    unsigned int mUsed;
    int unk_0x20;
    int mNumBlocks;
    int mMaxBlocks;
    int unk_0x2C;
    int unk_0x30;
    unsigned int mBlocks[1];
} MemExternHeap_t;

#define BLOCK_FREE 0x80000000
#define BLOCK_SIZE(block) ((block) & 0x7FFFFFFF)
#define BLOCK_END 0xFFFFFFFF

static const char _MemExtern_aCorruptMapMessage[] = "MEMEXTERN.C: memory map corrupted";

/* The parent memory manager owns and releases the map storage. */
static void _MemExternDestroyHeap(void *pHeapData)
{
}

/* External heaps have no display implementation. */
static int _MemExternDisplayHeap(void *pHeapData, int flags)
{
    return 0;
}

/* Check that the map spans cover the registered region. */
static int _MemExternVerifyHeap(void *pHeapData)
{
    MemExternHeap_t *pHeap = pHeapData;
    unsigned int *pBlock;
    unsigned int total = 0;

    for (pBlock = pHeap->mBlocks; *pBlock != BLOCK_END; pBlock++) {
        total += BLOCK_SIZE(*pBlock);
    }
    if (pHeap->mSize == total) {
        return 0;
    }
    fn_801D26C4(pHeap->mIdent, 0, _MemExtern_aCorruptMapMessage);
    return -1;
}

/* Accept only the beginning of an allocated span. */
static int _MemExternVerifyAddr(void *pHeapData, void *pAddr)
{
    MemExternHeap_t *pHeap = pHeapData;
    unsigned int *pBlock = pHeap->mBlocks;
    int offset = (char *)pAddr - pHeap->mBase;

    while (offset > 0) {
        offset -= BLOCK_SIZE(*pBlock);
        pBlock++;
    }
    if (offset == 0 && (int)*pBlock >= 0) {
        return 0;
    }
    return -1;
}

/* Query free or used bytes; mode 3 retains its sentinel-derived result. */
static int _MemExternHeapInfo(void *pHeapData, int what)
{
    MemExternHeap_t *pHeap = pHeapData;
    unsigned int *pBlock;
    unsigned int largest;

    if (what == 1) {
        return pHeap->mSize - pHeap->mUsed;
    }
    if (what == 2) {
        return pHeap->mUsed;
    }
    if (what == 3) {
        largest = 0;
        for (pBlock = pHeap->mBlocks; *pBlock != BLOCK_END; pBlock++) {
            if (*pBlock > largest) {
                largest = *pBlock;
            }
        }
        return BLOCK_SIZE(*pBlock);
    }
    return -1;
}

/* Select a fitting span, splitting only when space and map capacity permit. */
static void *_MemExternAlloc(void *pHeapData, int size, int flags, const char *pGroup,
                             const char *pContext0, const char *pContext1, int contextValue)
{
    MemExternHeap_t *pHeap = pHeapData;
    unsigned int *pBlock;
    unsigned int want;
    unsigned int rounded;
    unsigned int offset;
    unsigned int numBlocks;
    unsigned int maxBlocks;

    if (size == 0) {
        size = 1;
    }
    rounded = size - 1;
    size = (rounded + pHeap->mAlign) & -pHeap->mAlign;
    want = size | BLOCK_FREE;
    offset = 0;
    for (pBlock = pHeap->mBlocks; *pBlock < want; pBlock++) {
        offset += *pBlock;
    }
    if (*pBlock == BLOCK_END) {
        return 0;
    }
    numBlocks = pHeap->mNumBlocks;
    maxBlocks = pHeap->mMaxBlocks;
    if (pHeap->mKind == 'b') {
        unsigned int *pScan = pBlock;
        unsigned int scanOffset;

        scanOffset = offset + *pBlock;
        while (*++pScan != BLOCK_END) {
            if (*pScan >= want && *pScan < *pBlock) {
                pBlock = pScan;
                offset = scanOffset;
            }
            scanOffset += *pScan;
        }
    }
    if (numBlocks >= maxBlocks || BLOCK_SIZE(*pBlock) < size + 0x100) {
        *pBlock = BLOCK_SIZE(*pBlock);
    } else {
        unsigned int *pScan;
        unsigned int carry;
        unsigned int next;

        carry = (BLOCK_SIZE(*pBlock) - size) | BLOCK_FREE;
        *pBlock = BLOCK_SIZE(size);
        for (pScan = pBlock + 1; *pScan != BLOCK_END; pScan++) {
            next = *pScan;
            *pScan = carry;
            carry = next;
        }
        pScan[0] = carry;
        pScan[1] = BLOCK_END;
        pHeap->mNumBlocks++;
    }
    pHeap->mNumAllocs++;
    pHeap->mUsed += BLOCK_SIZE(*pBlock);
    return pHeap->mBase + BLOCK_SIZE(offset);
}

/* Release a span, merge adjacent free spans, and compact the map. */
static int _MemExternFree(void *pHeapData, void *pAddr)
{
    MemExternHeap_t *pHeap = pHeapData;
    unsigned int *pBlock = pHeap->mBlocks;
    unsigned int *pOut;
    int offset = (char *)pAddr - pHeap->mBase;

    while (offset > 0) {
        offset -= BLOCK_SIZE(*pBlock);
        pBlock++;
    }
    if (offset != 0 || (*pBlock & BLOCK_FREE)) {
        return -1;
    }
    *pBlock |= BLOCK_FREE;
    pHeap->mNumAllocs--;
    pHeap->mUsed -= BLOCK_SIZE(*pBlock);
    if (pBlock[1] != BLOCK_END && (int)pBlock[1] < 0) {
        pBlock[0] += BLOCK_SIZE(pBlock[1]);
        pBlock[1] = 0;
        pHeap->mNumBlocks--;
    }
    if (pBlock != pHeap->mBlocks && (int)pBlock[-1] < 0) {
        pBlock--;
        pBlock[0] += BLOCK_SIZE(pBlock[1]);
        pBlock[1] = 0;
        pHeap->mNumBlocks--;
    }
    for (pOut = pBlock; *pBlock != BLOCK_END; pBlock++) {
        if (*pBlock != 0) {
            *pOut++ = *pBlock;
        }
    }
    *pOut = BLOCK_END;
    return 0;
}

/* External spans cannot be resized through this hook. */
static void *_MemExternResize(void *pHeapData, void *pAddr, int size, int flags)
{
    return 0;
}

/* Return the occupied span length for an allocated start address. */
static int _MemExternSizeof(void *pHeapData, void *pAddr)
{
    MemExternHeap_t *pHeap = pHeapData;
    unsigned int *pBlock = pHeap->mBlocks;
    int offset = (char *)pAddr - pHeap->mBase;

    while (offset > 0) {
        offset -= BLOCK_SIZE(*pBlock);
        pBlock++;
    }
    if (offset != 0 || (int)*pBlock < 0) {
        return -1;
    }
    return BLOCK_SIZE(*pBlock);
}

static MemHeapFuncs_t _MemExtern_sHeapFuncs = {
    _MemExternDestroyHeap, _MemExternDisplayHeap, _MemExternVerifyHeap, _MemExternVerifyAddr, _MemExternHeapInfo,
    _MemExternAlloc, _MemExternFree, _MemExternResize, _MemExternSizeof,
};

/* Register a best-fit map for the region; both exit paths return zero. */
int MemInitExternHeap(int ident, int parentIdent, char *pStart, unsigned int size, unsigned int maxBlocks,
                      unsigned int align)
{
    MemExternHeap_t *pHeap;

    if (maxBlocks < 8) {
        maxBlocks = 8;
    }
    pHeap = fn_801D2478(ident, parentIdent, pStart, size, maxBlocks * 8 + sizeof(MemExternHeap_t), &_MemExtern_sHeapFuncs);
    if (pHeap == 0) {
        return 0;
    }
    memset(pHeap, 0, sizeof(MemExternHeap_t));
    {
        // FAKEMATCH: kind and count held in block locals only so the -1 constant is loaded after them, as in the target
        int kind = 'b';
        int numBlocks = 2;

        pHeap->mBlocks[1] = BLOCK_END;
        pHeap->mAlign = align;
        pHeap->mIdent = ident;
        pHeap->mKind = kind;
        pHeap->mNumBlocks = numBlocks;
        pHeap->mMaxBlocks = maxBlocks * 2;
        pHeap->mSize = size;
        pHeap->mBlocks[0] = size | BLOCK_FREE;
        pHeap->mBase = pStart;
    }
    return 0;
}
