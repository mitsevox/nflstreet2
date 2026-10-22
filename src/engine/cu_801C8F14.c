#include "engine/cu_801C665C.h"
#include "engine/cu_801C8F14.h"
#include "game/fn_801C68FC.h"
#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include "engine/cu_801C2EB4.h"

typedef struct FileWaitResult_801C8F14 {
    int mCount;
    unsigned char mDone;
} FileWaitResult_801C8F14;

extern unsigned char lbl_803EBC18;
extern FileEntry_801C8F14 *lbl_803EBC24;
extern Lock_801F8014 *lbl_803EBC28;
extern int lbl_803EBC2C;
extern FileDevTable_801C8F14 *lbl_803EBC30;
extern int lbl_803EBC34;
extern unsigned int lbl_803EBC10;
extern unsigned int lbl_803EBC14;
extern void *lbl_803ED628;
extern void *lbl_803ED62C;
extern unsigned char lbl_803ED630;
extern Lock_801F8014 lbl_803D5168;
extern Lock_801F8014 lbl_803D5188;
extern FileConfig_801C8F14 lbl_803D51A8;
extern unsigned char lbl_803D55B4[9];
extern Lock_801F8014 lbl_803D55C0;
extern FileDevTable_801C8F14 lbl_802F4A50;

void fn_801F81AC(void);
int fn_801D34D0(void *pDest, int size, int value, int width);
int fn_801CA760(FileAsync_801C8F14 *pAsync);
void fn_801CA834(int handle);
int fn_801CA364(const char *pName, int device, const char *pPrefix);
int fn_801CA468(int handle);
void fn_801CB00C(FileConfig_801C8F14 *pConfig);
void fn_801CB0EC(void);

static int fn_801C8F14(FileAsync_801C8F14 *pA, FileAsync_801C8F14 *pB)
{
    int diff = pA->mPriority - pB->mPriority;

    if (diff == 0) {
        diff = -1;
    }
    return diff;
}

static void fn_801C8F2C(int count, int error, FileWaitResult_801C8F14 *pResult)
{
    pResult->mCount += count;
    pResult->mDone = 1;
}

static FileReq_801C8F14 *fn_801C8F44(void)
{
    FileReq_801C8F14 *pReq;

    for (;;) {
        fn_801F8014(&lbl_803D5168);
        pReq = fn_801C75F0(lbl_803ED628);
        fn_801F809C(&lbl_803D5168);
        if (pReq) {
            break;
        }
        fn_801F81AC();
    }
    return pReq;
}

static void fn_801C8F9C(FileReq_801C8F14 *pReq)
{
    fn_801F8014(&lbl_803D5168);
    fn_801C7650(lbl_803ED628, pReq);
    fn_801F809C(&lbl_803D5168);
}

FileAsync_801C8F14 *fn_801C8FE4(void)
{
    FileAsync_801C8F14 *pAsync;

    for (;;) {
        fn_801F8014(&lbl_803D5188);
        pAsync = fn_801C6A20(lbl_803ED62C);
        fn_801F809C(&lbl_803D5188);
        if (pAsync) {
            break;
        }
        fn_801F81AC();
    }
    return pAsync;
}

int fn_801C903C(int unused, int arg, FileReq_801C8F14 *pReq)
{
    int done = 0;
    FileAsync_801C8F14 *pAsync = pReq->mpAsync;
    int size;

    if (pReq->mpBlockFn) {
        pReq->mpBlockFn(pAsync->mSize, pAsync->mpBuffer, arg, pReq->mpArg);
    }
    if (pReq->mSize != pReq->mDone) {
        size = pAsync->mSize;
        if (!pReq->mCyclic) {
            pAsync->mpBuffer += size;
        }
        pAsync->mPos += size;
        size = pReq->mSize - pReq->mDone;
        if (size > pReq->mBlockSize) {
            size = pReq->mBlockSize;
        }
        pAsync->mSize = size;
        lbl_803EBC24[pReq->mHandle].mAsyncPos += size;
        if (pAsync->mType == 2 && lbl_803EBC24[pReq->mHandle].mAsyncPos > lbl_803EBC24[pReq->mHandle].mLength) {
            lbl_803EBC24[pReq->mHandle].mLength = lbl_803EBC24[pReq->mHandle].mAsyncPos;
        }
        pReq->mDone += pAsync->mSize;
    } else {
        if (pReq->mpDoneFn) {
            pReq->mpDoneFn(pReq->mSize, 0, pReq->mpArg);
        }
        done = 1;
        fn_801C8F9C(pReq);
    }
    return done;
}

FileReq_801C8F14 *fn_801C9174(FileReq_801C8F14 *pSrc, int type)
{
    FileReq_801C8F14 *pReq = fn_801C8F44();
    FileAsync_801C8F14 *pAsync;
    int state = 0;
    int size;

    pReq->mHandle = pSrc->mHandle;
    pReq->mpBuffer = pSrc->mpBuffer;
    pReq->mSize = pSrc->mSize;
    pReq->mBlockSize = pSrc->mBlockSize;
    pReq->mPriority = pSrc->mPriority;
    pReq->mpDoneFn = pSrc->mpDoneFn;
    pReq->mpArg = pSrc->mpArg;
    pReq->mpBlockFn = pSrc->mpBlockFn;
    pReq->mCyclic = pSrc->mCyclic;
    pAsync = fn_801C8FE4();
    pReq->mpAsync = pAsync;
    pAsync->mType = type;
    pAsync->mState = state;
    pAsync->mpStep = (int (*)(int, int, void *))fn_801C903C;
    pAsync->mpReq = pReq;
    pAsync->mHandle = pReq->mHandle;
    pAsync->mPos = lbl_803EBC24[pReq->mHandle].mPos;
    pAsync->mpBuffer = pReq->mpBuffer;
    size = pReq->mSize;
    if (size > pReq->mBlockSize) {
        size = pReq->mBlockSize;
    }
    pAsync->mSize = size;
    pAsync->mPriority = pReq->mPriority;
    lbl_803EBC24[pReq->mHandle].mPos += pReq->mSize;
    pReq->mDone = pAsync->mSize;
    if (pAsync->mType == 2 && lbl_803EBC24[pReq->mHandle].mPos > lbl_803EBC24[pReq->mHandle].mLength) {
        lbl_803EBC24[pReq->mHandle].mLength = lbl_803EBC24[pReq->mHandle].mPos;
    }
    fn_801F7BD4(fn_801CA760(pAsync));
    return pReq;
}

void fn_801C92B8(char *pDst, const char *pPath, const char *pName, int flags)
{
    char prefix[128];
    int len;

    switch (flags & 0xF) {
    case 1:
        fn_801C2EB4(prefix, lbl_803D51A8.mPath1);
        break;
    case 4:
        fn_801C2EB4(prefix, lbl_803D51A8.mPath0);
        break;
    case 3:
        fn_801C2EB4(prefix, lbl_803D51A8.mPath3);
        break;
    case 8:
        fn_801C2EB4(prefix, lbl_803D51A8.mPath8);
        break;
    default:
        fn_801C2EB4(prefix, lbl_803D51A8.mPath0);
        break;
    }
    len = fn_801C3180(pPath);
    len += fn_801C3180(pName);
    len += fn_801C3180(prefix);
    if (len != -1 && pDst) {
        fn_801C2EB4(pDst, prefix);
        fn_801C2F2C(pDst, pPath);
        fn_801C2F2C(pDst, pName);
    }
}

int fn_801C93D0(FileConfig_801C8F14 *pConfig)
{
    int error = 0;
    int size;
    int i;
    int j;

    if (!lbl_803EBC18) {
        lbl_803D51A8 = *pConfig;
        lbl_803EBC24 = fn_801D2B7C(size = lbl_803D51A8.mNumFiles * sizeof(FileEntry_801C8F14), 0, 0);
        fn_801D34D0(lbl_803EBC24, size, 0, 1);
        lbl_803EBC28 = fn_801D2B7C(size = lbl_803D51A8.mNumFiles * 0x20, 0, 0);
        fn_801D34D0(lbl_803EBC28, size, 0, 1);
        for (j = 0; j < 9; j++) {
            lbl_803D55B4[j] = 0;
        }
        fn_801F7FA8(&lbl_803D55C0);
        for (i = 0; i < lbl_803D51A8.mNumFiles; i++) {
            fn_801F7FA8(&lbl_803EBC28[i]);
        }
        lbl_803ED62C = fn_801C68FC(1, 0, 0x40, sizeof(FileAsync_801C8F14), (int (*)(void *, void *))fn_801C8F14, 0);
        fn_801F7FA8(&lbl_803D5188);
        lbl_803ED630 = 0;
        lbl_803ED628 = fn_801C750C(1, 0x40, sizeof(FileReq_801C8F14), 0);
        fn_801F7FA8(&lbl_803D5168);
        fn_801CB00C(&lbl_803D51A8);
        lbl_803EBC10 = 0;
        lbl_803EBC34 = 0;
        lbl_803EBC18 = 1;
    } else {
        error = 0xA0001;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C95C4(void)
{
    int error = 0;
    int i;

    if (lbl_803EBC18) {
        fn_801CB0EC();
        for (i = 0; i < lbl_803D51A8.mNumFiles; i++) {
            if (i >= 0 && i < lbl_803D51A8.mNumFiles && lbl_803EBC24[i].mInUse) {
                fn_801CA834(i);
            }
            fn_801F80D0(&lbl_803EBC28[i]);
        }
        fn_801C69E4(lbl_803ED62C);
        fn_801F80D0(&lbl_803D5188);
        fn_801F80D0(&lbl_803D55C0);
        fn_801C75B8(lbl_803ED628);
        fn_801F80D0(&lbl_803D5168);
        fn_801D2BD0(lbl_803EBC24);
        fn_801D2BD0(lbl_803EBC28);
        lbl_803EBC24 = 0;
        lbl_803EBC28 = 0;
        lbl_803EBC34 = 0;
        lbl_803EBC18 = 0;
    } else {
        error = 0xA0002;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C96E4(const char *pName, int device)
{
    int handle = 0;
    int error = 0;
    FileDevList_801C8F14 *pList;
    int count;
    int i;

    if (device == 0x2C) {
        device = lbl_803EBC2C;
    }
    if (device <= 0) {
        pList = lbl_803EBC30->mpList[-device];
        error = 0xA0003;
        count = pList->mCount;
        for (i = 0; error == 0xA0003 && i < count; i++) {
            if ((handle = fn_801CA364(pName, pList->mDevice[i], pList->mpPrefix[i])) >= 0) {
                error = 0;
            }
        }
    } else {
        if ((handle = fn_801CA364(pName, device, "")) < 0) {
            error = 0xA0003;
        }
    }
    fn_801F7BD4(error);
    if (error == 0) {
        lbl_803EBC10++;
        lbl_803EBC14 = lbl_803EBC14 < lbl_803EBC10 ? lbl_803EBC10 : lbl_803EBC14;
        return handle;
    }
    return -1;
}

int fn_801C97F0(int handle)
{
    int error;

    fn_801CA834(handle);
    error = fn_801CA468(handle);
    fn_801F7BD4(error);
    if (error == 0) {
        lbl_803EBC10--;
    }
    return error;
}

int fn_801C9844(int handle, int offset, unsigned int whence)
{
    int error = 0;
    FileEntry_801C8F14 *pFile;

    switch (whence) {
    case 0:
        lbl_803EBC24[handle].mPos = offset;
        break;
    case 1:
        lbl_803EBC24[handle].mPos += offset;
        break;
    case 2:
        lbl_803EBC24[handle].mPos = lbl_803EBC24[handle].mLength - offset;
        break;
    }
    if (lbl_803EBC24[handle].mPos < 0) {
        lbl_803EBC24[handle].mPos = 0;
        error = 0xA0004;
    } else if (lbl_803EBC24[handle].mPos > lbl_803EBC24[handle].mLength) {
        lbl_803EBC24[handle].mPos = lbl_803EBC24[handle].mLength;
        error = 0xA0004;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C9910(const char *pName, int device)
{
    int handle = fn_801C96E4(pName, device);
    int error;

    if (handle < 0) {
        error = 0xA0003;
    } else {
        error = fn_801C97F0(handle);
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C9960(int handle, char *pBuffer, int size, void (*callback)(int, int, int))
{
    FileReq_801C8F14 req;
    FileWaitResult_801C8F14 result;
    int error = 0;
    int count;

    result.mCount = 0;
    result.mDone = 0;
    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mBlockSize = 0x8000;
    req.mPriority = 100;
    req.mpBlockFn = 0;
    req.mpDoneFn = (FileDoneFn_801C8F14)fn_801C8F2C;
    req.mpArg = &result;
    req.mCyclic = 0;
    fn_801C9174(&req, 1);
    fn_801CA834(handle);
    count = result.mCount;
    if (count < 0 || count != size) {
        error = 0xA0007;
    }
    if (callback) {
        callback(count, error, 0);
    }
    if (error) {
        count = -1;
    }
    fn_801F7BD4(error);
    return count;
}

int fn_801C9A3C(int handle, char *pBuffer, int size, void (*callback)(int, int, int))
{
    FileReq_801C8F14 req;
    FileWaitResult_801C8F14 result;
    int error = 0;
    int count;

    result.mCount = 0;
    result.mDone = 0;
    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mBlockSize = 0x8000;
    req.mPriority = 100;
    req.mpBlockFn = 0;
    req.mpDoneFn = (FileDoneFn_801C8F14)fn_801C8F2C;
    req.mpArg = &result;
    req.mCyclic = 0;
    fn_801C9174(&req, 2);
    fn_801CA834(handle);
    count = result.mCount;
    if (count < 0 || count != size) {
        error = fn_801F7C88();
    }
    if (callback) {
        callback(count, error, 0);
    }
    if (error) {
        count = -1;
    }
    fn_801F7BD4(error);
    return count;
}

FileReq_801C8F14 *fn_801C9B18(int handle, char *pBuffer, int size, int priority, FileDoneFn_801C8F14 doneFn,
                              void *pArg)
{
    FileReq_801C8F14 req;
    FileReq_801C8F14 *pReq;
    int error = 0;

    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mBlockSize = 0x8000;
    req.mpDoneFn = doneFn;
    req.mpArg = pArg;
    req.mPriority = priority;
    req.mCyclic = 0;
    req.mpBlockFn = 0;
    if (!(pReq = fn_801C9174(&req, 1))) {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return pReq;
}

FileReq_801C8F14 *fn_801C9B94(int handle, char *pBuffer, int size, int priority, FileDoneFn_801C8F14 doneFn,
                              void *pArg, FileBlockFn_801C8F14 blockFn, int blockSize)
{
    FileReq_801C8F14 req;
    FileReq_801C8F14 *pReq;
    int error = 0;

    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mpDoneFn = doneFn;
    req.mpArg = pArg;
    req.mpBlockFn = blockFn;
    req.mPriority = priority;
    req.mBlockSize = blockSize;
    req.mCyclic = 1;
    if (!(pReq = fn_801C9174(&req, 1))) {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return pReq;
}

FileReq_801C8F14 *fn_801C9C0C(int handle, char *pBuffer, int size, int priority, FileDoneFn_801C8F14 doneFn,
                              void *pArg)
{
    FileReq_801C8F14 req;
    FileReq_801C8F14 *pReq;
    int error = 0;

    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mBlockSize = 0x8000;
    req.mpDoneFn = doneFn;
    req.mpArg = pArg;
    req.mPriority = priority;
    req.mCyclic = 0;
    req.mpBlockFn = 0;
    if (!(pReq = fn_801C9174(&req, 2))) {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return pReq;
}

FileReq_801C8F14 *fn_801C9C88(FileReq_801C8F14 *pReq, int priority)
{
    if (pReq) {
        fn_801F8014(&lbl_803D5188);
        if (pReq->mpAsync) {
            pReq->mPriority = priority;
            if (pReq->mpAsync->mState == 0) {
                pReq->mpAsync->mPriority = priority;
                fn_801C6BC0(lbl_803ED62C, pReq->mpAsync);
                fn_801C6AA4(lbl_803ED62C, pReq->mpAsync, 0);
            } else {
                pReq->mpAsync->mPriority = priority;
            }
        }
        fn_801F809C(&lbl_803D5188);
    }
    return pReq;
}

int fn_801C9D18(int handle)
{
    return lbl_803EBC24[handle].mLength;
}

int fn_801C9D2C(int handle)
{
    return lbl_803EBC24[handle].mPos;
}

int fn_801C9D40(FileDevTable_801C8F14 *pTable)
{
    if (pTable) {
        lbl_803EBC30 = pTable;
    } else {
        lbl_803EBC30 = &lbl_802F4A50;
    }
    return 0;
}

FileDevTable_801C8F14 *fn_801C9D64(void)
{
    return lbl_803EBC30;
}

int fn_801C9D6C(int device)
{
    lbl_803EBC2C = device;
    return 0;
}

void fn_801C9D78(void)
{
    fn_801F8014(&lbl_803D5188);
}

void fn_801C9DA0(void)
{
    fn_801F809C(&lbl_803D5188);
}

int fn_801C9DC8(int flags)
{
    int old = lbl_803EBC34;

    lbl_803EBC34 = flags;
    return old;
}
