#ifndef ENGINE_MEMORY_H
#define ENGINE_MEMORY_H

/* Heap records of Memory.c (0x801D134C-0x801D34C4) and the extern-heap hooks MemExtern.c installs. */

/* Free-list tree node; lives 0xC bytes into a free block (right after its header). */
typedef struct MemNode_801D134C {
    int mSize;
    struct MemNode_801D134C *mpParent;
    struct MemNode_801D134C *mpLeft;
    struct MemNode_801D134C *mpRight;
} MemNode_801D134C;

struct MemHeap_801D134C;

/* 12-byte block header; mOffset is the distance from the region start to the block data. */
typedef struct MemBlock_801D134C {
    short mOffset;
    unsigned char mState;
    unsigned char mUnk3;
    struct MemHeap_801D134C *mpHeap;
    void **mpTail;
} MemBlock_801D134C;

typedef struct MemHeapFuncs_801D134C {
    void (*mDestroy)(void *pHeapData);
    int (*mDisplay)(void *pHeapData, int flags);
    int (*mVerify)(void *pHeapData);
    int (*mVerifyAddr)(void *pHeapData, void *pAddr);
    int (*mInfo)(void *pHeapData, int what);
    void *(*mAlloc)(void *pHeapData, int size, int align, int flags);
    int (*mFree)(void *pHeapData, void *pAddr);
    int (*mResize)(void *pHeapData, void *pAddr, int size);
    int (*mSizeof)(void *pHeapData, void *pAddr);
} MemHeapFuncs_801D134C;

/* 0x100-byte heap record; extern heaps keep their own data right after it. */
typedef struct MemHeap_801D134C {
    int mId;
    struct MemHeap_801D134C *mpSelf;
    struct MemHeap_801D134C *mpNext;
    struct MemHeap_801D134C *mpParent;
    struct MemHeap_801D134C *mpSub;
    char *mpStart;
    char *mpEnd;
    unsigned int mSize;
    unsigned int mAlign;
    unsigned int mNumFree;
    unsigned int mMaxFree;
    int mFreeBytes;
    MemNode_801D134C mRoot;
    char mUnk40[0x84 - 0x40];
    char mName[8];
    unsigned int mLabelDepth;
    char mLabels[6][16];
    short mDebugSize;
    unsigned char mDebug;
    unsigned char mFill;
    unsigned char mOwnsMemory;
    char mUnkF5[0xF8 - 0xF5];
    MemHeapFuncs_801D134C *mpFuncs;
    void (*mCopy)(void *pDst, int dstExtern, void *pSrc, int srcExtern, int size);
} MemHeap_801D134C;

void *fn_801D2BB0(int a, int size, int ident, int flags);
int fn_801D26C4(int ident, int flags, const char *pMessage);
void *fn_801D2478(int ident, int parentIdent, char *pStart, unsigned int size, int dataSize,
                  MemHeapFuncs_801D134C *pFuncs);

#endif
