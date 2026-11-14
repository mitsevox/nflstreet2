#ifndef ENGINE_FILEIO_H
#define ENGINE_FILEIO_H

/* Open-file record, one per file handle. */
typedef struct FileStreamInfo_t {
    int mDevHandle;
    int mDevType;
    int mLength;
    int mInUse;
    volatile int mAsyncPos;
    int mPos;
    char *mpName;
    int mMode;
    int mUnk20;
} FileStreamInfo_t;

/* Queued asynchronous transfer, 0x24-byte list nodes. */
typedef struct FileAsyncRequest_t {
    int mType;
    int mState;
    int (*mpStep)(int, int, void *);
    struct FileRequest_t *mpReq;
    int mHandle;
    int mPos;
    char *mpBuffer;
    int mSize;
    int mPriority;
} FileAsyncRequest_t;

typedef void (*FileBlockFn_t)(int, char *, int, void *);
typedef void (*FileDoneFn_t)(int, int, void *);

/* Read/write request, 0x2C-byte nodes. */
typedef struct FileRequest_t {
    int mHandle;
    char *mpBuffer;
    int mSize;
    int mBlockSize;
    int mPriority;
    FileBlockFn_t mpBlockFn;
    FileDoneFn_t mpDoneFn;
    void *mpArg;
    FileAsyncRequest_t *mpAsync;
    int mDone;
    unsigned char mCyclic;
} FileRequest_t;

/* Start-up parameters the file module keeps a copy of: path prefixes, file count, host flag. */
typedef struct FileInitParms_t {
    char mPath0[0x80];
    char mPath1[0x80];
    char mUnk100[0x100];
    char mPath3[0x80];
    char mPath8[0x80];
    char mUnk300[0x100];
    int mUnk400;
    unsigned int mNumFiles;
    unsigned char mHostEnabled;
} FileInitParms_t;

/* A list of devices and path prefixes that an open tries in order. */
typedef struct FilevDevicePath_t {
    int mDevice[8];
    char *mpPrefix[8];
    int mCount;
} FilevDevicePath_t;

/* Table of device lists: opening on device -n searches list n. */
typedef struct FilevDeviceList_t {
    FilevDevicePath_t *mpList[8];
    int mCount;
} FilevDeviceList_t;

#endif
