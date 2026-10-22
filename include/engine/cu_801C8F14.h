#ifndef ENGINE_CU_801C8F14_H
#define ENGINE_CU_801C8F14_H

/* Open-file record, 0x24 bytes each in the table at r13-0x667C. */
typedef struct FileEntry_801C8F14 {
    int mDevHandle;
    int mDevType;
    int mLength;
    int mInUse;
    volatile int mAsyncPos;
    int mPos;
    char *mpName;
    int mMode;
    int mUnk20;
} FileEntry_801C8F14;

/* Queued asynchronous transfer, 0x24-byte list nodes. */
typedef struct FileAsync_801C8F14 {
    int mType;
    int mState;
    int (*mpStep)(int, int, void *);
    struct FileReq_801C8F14 *mpReq;
    int mHandle;
    int mPos;
    char *mpBuffer;
    int mSize;
    int mPriority;
} FileAsync_801C8F14;

typedef void (*FileBlockFn_801C8F14)(int, char *, int, void *);
typedef void (*FileDoneFn_801C8F14)(int, int, void *);

/* Read/write request, 0x2C-byte nodes. */
typedef struct FileReq_801C8F14 {
    int mHandle;
    char *mpBuffer;
    int mSize;
    int mBlockSize;
    int mPriority;
    FileBlockFn_801C8F14 mpBlockFn;
    FileDoneFn_801C8F14 mpDoneFn;
    void *mpArg;
    FileAsync_801C8F14 *mpAsync;
    int mDone;
    unsigned char mCyclic;
} FileReq_801C8F14;

/* Configuration copied by FileInit (0x40C bytes at 0x803D51A8). */
typedef struct FileConfig_801C8F14 {
    char mPath0[0x80];
    char mPath1[0x80];
    char mUnk100[0x100];
    char mPath3[0x80];
    char mPath8[0x80];
    char mUnk300[0x100];
    int mUnk400;
    unsigned int mNumFiles;
    unsigned char mHostEnabled;
} FileConfig_801C8F14;

typedef struct FileDevList_801C8F14 {
    int mDevice[8];
    char *mpPrefix[8];
    int mCount;
} FileDevList_801C8F14;

/* Device search table (default at 0x802F4A50): device lists tried in order. */
typedef struct FileDevTable_801C8F14 {
    FileDevList_801C8F14 *mpList[8];
    int mCount;
} FileDevTable_801C8F14;

#endif
