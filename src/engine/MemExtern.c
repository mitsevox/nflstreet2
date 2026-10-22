#include "engine/Memory.h"

typedef struct ExternHeap {
    int mIdent;
    unsigned char mKind;
    char *mBase;
    unsigned int mSize;
    unsigned int mAlign;
    int mNumAllocs;
    int mUnknown18;
    unsigned int mUsed;
    int mUnknown20;
    int mNumBlocks;
    int mMaxBlocks;
    int mUnknown2C;
    int mUnknown30;
    unsigned int mBlocks[1];
} ExternHeap;

#define BLOCK_FREE 0x80000000
#define BLOCK_SIZE(block) ((block) & 0x7FFFFFFF)
#define BLOCK_END 0xFFFFFFFF

static void fn_801D36E8(void *pHeapData)
{
}

static int fn_801D36EC(void *pHeapData, int flags)
{
    return 0;
}

static int fn_801D36F4(void *pHeapData)
{
    ExternHeap *pHeap = pHeapData;
    unsigned int *pBlock;
    unsigned int total = 0;

    for (pBlock = pHeap->mBlocks; *pBlock != BLOCK_END; pBlock++) {
        total += BLOCK_SIZE(*pBlock);
    }
    if (pHeap->mSize == total) {
        return 0;
    }
    fn_801D26C4(pHeap->mIdent, 0, "MEMEXTERN.C: memory map corrupted");
    return -1;
}

static int fn_801D3768(void *pHeapData, void *pAddr)
{
    ExternHeap *pHeap = pHeapData;
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

static int fn_801D37AC(void *pHeapData, int what)
{
    ExternHeap *pHeap = pHeapData;
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

static void *fn_801D3820(void *pHeapData, int size, int align, int flags)
{
    ExternHeap *pHeap = pHeapData;
    unsigned int *pBlock;
    unsigned int *pScan;
    unsigned int want;
    unsigned int block;
    unsigned int offset;
    unsigned int scanOffset;
    unsigned int carry;
    unsigned int next;
    unsigned int numBlocks;
    unsigned int maxBlocks;

    if (size == 0) {
        size = 1;
    }
    size = (size - 1 + pHeap->mAlign) & -pHeap->mAlign;
    want = size | BLOCK_FREE;
    offset = 0;
    for (pBlock = pHeap->mBlocks; *pBlock < want; pBlock++) {
        offset += *pBlock;
    }
    block = *pBlock;
    if (block == BLOCK_END) {
        return 0;
    }
    numBlocks = pHeap->mNumBlocks;
    maxBlocks = pHeap->mMaxBlocks;
    if (pHeap->mKind == 'b') {
        pScan = pBlock;
        scanOffset = offset + block;
        while (*++pScan != BLOCK_END) {
            next = *pScan;
            if (next >= want && next < *pBlock) {
                pBlock = pScan;
                offset = scanOffset;
            }
            scanOffset += next;
            block = *pBlock;
        }
    }
    if (numBlocks >= maxBlocks || BLOCK_SIZE(block) < size + 0x100) {
        *pBlock = BLOCK_SIZE(block);
    } else {
        *pBlock = BLOCK_SIZE(size);
        carry = (BLOCK_SIZE(block) - size) | BLOCK_FREE;
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

static int fn_801D399C(void *pHeapData, void *pAddr)
{
    ExternHeap *pHeap = pHeapData;
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

static int fn_801D3ABC(void *pHeapData, void *pAddr, int size)
{
    return 0;
}

static int fn_801D3AC4(void *pHeapData, void *pAddr)
{
    ExternHeap *pHeap = pHeapData;
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

static MemHeapFuncs_801D134C lbl_802F7B40 = {
    fn_801D36E8, fn_801D36EC, fn_801D36F4, fn_801D3768, fn_801D37AC,
    fn_801D3820, fn_801D399C, fn_801D3ABC, fn_801D3AC4,
};

int fn_801D3B0C(int ident, int parentIdent, char *pStart, unsigned int size, unsigned int maxBlocks,
                unsigned int align)
{
    ExternHeap *pHeap;

    if (maxBlocks < 8) {
        maxBlocks = 8;
    }
    pHeap = fn_801D2478(ident, parentIdent, pStart, size, maxBlocks * 8 + sizeof(ExternHeap), &lbl_802F7B40);
    if (pHeap == 0) {
        return 0;
    }
    memset(pHeap, 0, sizeof(ExternHeap));
    pHeap->mBlocks[1] = BLOCK_END;
    pHeap->mAlign = align;
    pHeap->mIdent = ident;
    pHeap->mKind = 'b';
    pHeap->mNumBlocks = 2;
    pHeap->mMaxBlocks = maxBlocks * 2;
    pHeap->mSize = size;
    pHeap->mBlocks[0] = size | BLOCK_FREE;
    pHeap->mBase = pStart;
    return 0;
}
