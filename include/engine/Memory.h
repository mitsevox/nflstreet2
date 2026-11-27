#ifndef ENGINE_MEMORY_H
#define ENGINE_MEMORY_H

/* Heap records of Memory.c (0x801D134C-0x801D34C4) and the extern-heap hooks MemExtern.c installs. */

/* Free-list tree node; lives 0xC bytes into a free block (right after its header). */
typedef struct MemNode_t {
    int mSize;
    struct MemNode_t *mpParent;
    struct MemNode_t *mpLeft;
    struct MemNode_t *mpRight;
} MemNode_t;

struct MemHeap_t;

/* 12-byte block header; mOffset is the distance from the region start to the block data. */
typedef struct MemBlock_t {
    short mOffset;
    unsigned char mState;
    unsigned char mUnk3;
    struct MemHeap_t *mpHeap;
    void **mpTail;
} MemBlock_t;

typedef struct MemHeapFuncs_t {
    void (*mDestroy)(void *pHeapData);
    int (*mDisplay)(void *pHeapData, int flags);
    int (*mVerify)(void *pHeapData);
    int (*mVerifyAddr)(void *pHeapData, void *pAddr);
    int (*mInfo)(void *pHeapData, int what);
    void *(*mAlloc)(void *pHeapData, int size, int flags, const char *pGroup,
                    const char *pContext0, const char *pContext1, int contextValue);
    int (*mFree)(void *pHeapData, void *pAddr);
    void *(*mResize)(void *pHeapData, void *pAddr, int size, int flags);
    int (*mSizeof)(void *pHeapData, void *pAddr);
} MemHeapFuncs_t;

/* 0x100-byte heap record; extern heaps keep their own data right after it. */
typedef struct MemHeap_t {
    int mId;
    struct MemHeap_t *mpSelf;
    struct MemHeap_t *mpNext;
    struct MemHeap_t *mpParent;
    struct MemHeap_t *mpSub;
    char *mpStart;
    char *mpEnd;
    unsigned int mSize;
    unsigned int mAlign;
    unsigned int mNumFree;
    unsigned int mMaxFree;
    int mFreeBytes;
    MemNode_t mRoot;
    unsigned int mNumUsed;
    unsigned int mMaxUsed;
    unsigned int mUsedBytes;
    unsigned int mMaxUsedBytes;
    char mUnk50[0x60 - 0x50];
    unsigned int mMinLargestFree;
    int mAllocCount;
    int mFreeCount;
    unsigned int mDebugBytes;
    unsigned int mMaxDebugBytes;
    int mUnk74;
    char mUnk78[0x7C - 0x78];
    int mDebugExtra;
    void (*mpFailHook)(int ident, unsigned int size);
    char mName[8];
    unsigned int mLabelDepth;
    char mLabels[6][16];
    short mDebugSize;
    unsigned char mDebug;
    unsigned char mFill;
    unsigned char mOwnsMemory;
    char mUnkF5[0xF8 - 0xF5];
    MemHeapFuncs_t *mpFuncs;
    void (*mCopy)(void *pDst, int dstExtern, void *pSrc, int srcExtern, int size);
} MemHeap_t;

int MemHeapBreakdown(int ident, int flags, const char *pMessage);
void *MemCustomHeap(int ident, int parentIdent, char *pStart, unsigned int size, int dataSize,
                  MemHeapFuncs_t *pFuncs);
void MemGetGroupLabelByAddr(void *pAddr, char *pOut, int size);

#endif
