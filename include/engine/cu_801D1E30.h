#ifndef ENGINE_CU_801D1E30_H
#define ENGINE_CU_801D1E30_H

/* Heap records kept by the 0x801D1xxx-0x801D34C4 allocator and its extern-heap hooks. */

typedef struct MemHeapFuncs_801D1E30 {
    void (*mDestroy)(void *pHeapData);
    int (*mDisplay)(void *pHeapData, int flags);
    int (*mVerify)(void *pHeapData);
    int (*mVerifyAddr)(void *pHeapData, void *pAddr);
    int (*mInfo)(void *pHeapData, int what);
    void *(*mAlloc)(void *pHeapData, int size, int align, int flags);
    int (*mFree)(void *pHeapData, void *pAddr);
    int (*mResize)(void *pHeapData, void *pAddr, int size);
    int (*mSizeof)(void *pHeapData, void *pAddr);
} MemHeapFuncs_801D1E30;

typedef struct MemHeap_801D1E30 MemHeap_801D1E30;

struct MemHeap_801D1E30 {
    int mIdent;
    MemHeap_801D1E30 *mSelf;
    MemHeap_801D1E30 *mNext;
    MemHeap_801D1E30 *mParent;
    MemHeap_801D1E30 *mSibling;
    char *mStart;
    char *mEnd;
    unsigned int mSize;
    unsigned int mAlign;
    char mUnknown24[0x2C - 0x24];
    int mUnknown2C;
    char mUnknown30[0x3C - 0x30];
    void *mFreeList;
    char mUnknown40[0x48 - 0x40];
    int mUnknown48;
    char mUnknown4C[0x60 - 0x4C];
    unsigned int mUnknown60;
    char mUnknown64[0x6C - 0x64];
    int mUnknown6C;
    char mUnknown70[0x74 - 0x70];
    int mUnknown74;
    char mUnknown78[0x84 - 0x78];
    char mName[8];
    unsigned int mLabelDepth;
    char mLabels[6][16];
    short mDebugSize;
    unsigned char mDebug;
    unsigned char mFillByte;
    unsigned char mOwnsMemory;
    char mUnknownF5[0xF8 - 0xF5];
    MemHeapFuncs_801D1E30 *mFuncs;
    void (*mCopy)(void *pDst, int dstExtern, void *pSrc, int srcExtern, int size);
};

#endif
