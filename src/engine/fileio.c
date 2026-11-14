/* The engine's file layer: opening files on the disc, memory card or host PC through device
   lists and path prefixes, and reading or writing them in blocks through a priority-ordered
   queue of asynchronous requests, with blocking wrappers for whole-file reads and writes.
   The device-level work is in llfileio.c. */

#include "engine/list.h"
#include "engine/fileio.h"
#include "game/fn_801C68FC.h"
#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include <string.h>

/* Filled in by _FileAsyncCallback when a blocking read or write finishes. */
typedef struct FileWaitResult_t {
    volatile int mCount;
    volatile unsigned char mDone;
} FileWaitResult_t;

static unsigned int _File_uNumOpenFiles = 0;
static unsigned int _File_uMaxFilesOpenedAtOnce = 0;
unsigned char File_ModuleActive = 0;
char File_ModuleID[] = "FileIO";
FileStreamInfo_t *File_StreamInfo = 0;
Lock_801F8014 *File_HandleInUseCS = 0;
static int _File_DefaultDevice = 0;

static FilevDevicePath_t _File_DefaultvDevicePath = { { 4 }, { "" }, 1 };
static FilevDeviceList_t _File_DefaultvDeviceList = { { &_File_DefaultvDevicePath }, 1 };

static FilevDeviceList_t *_File_CurrentvDeviceList = &_File_DefaultvDeviceList;
int File_uMemFlags = 0;

extern void *File_pFileRequestList;
extern void *File_pAsyncRequestList;
extern unsigned char File_AsyncFileCopy;
extern Lock_801F8014 File_RequestListCS;
extern Lock_801F8014 File_AsyncRequestListCS;
extern FileInitParms_t File_InitParms;
extern unsigned char File_AsyncThreadActive[9];
extern Lock_801F8014 File_AsyncThreadActiveCS;

void fn_801F81AC(void);
int MemFill(void *pDest, int size, int value, int width);
int FileQueueAsyncRequest(FileAsyncRequest_t *pAsync);
void FileAsyncWaitStream(int handle);
int FileOpenhDevice(const char *pName, int device, const char *pPrefix);
int FileCloseStream(int handle);
void FileLLInit(FileInitParms_t *pConfig);
void FileLLShutdown(void);

static int _FileRequestInsertFunc(FileAsyncRequest_t *pA, FileAsyncRequest_t *pB)
{
    int diff = pA->mPriority - pB->mPriority;

    if (diff == 0) {
        diff = -1;
    }
    return diff;
}

static void _FileAsyncCallback(int count, int error, FileWaitResult_t *pResult)
{
    pResult->mCount += count;
    pResult->mDone = 1;
}

static FileRequest_t *_GetNewFileRequest(void)
{
    FileRequest_t *pReq;

    for (;;) {
        fn_801F8014(&File_RequestListCS);
        pReq = DSNewNode(File_pFileRequestList);
        fn_801F809C(&File_RequestListCS);
        if (pReq) {
            break;
        }
        fn_801F81AC();
    }
    return pReq;
}

static void _DeleteFileRequestNode(FileRequest_t *pReq)
{
    fn_801F8014(&File_RequestListCS);
    DSDelNode(File_pFileRequestList, pReq);
    fn_801F809C(&File_RequestListCS);
}

FileAsyncRequest_t *_FileGetAsyncRequest(void)
{
    FileAsyncRequest_t *pAsync;

    for (;;) {
        fn_801F8014(&File_AsyncRequestListCS);
        pAsync = fn_801C6A20(File_pAsyncRequestList);
        fn_801F809C(&File_AsyncRequestListCS);
        if (pAsync) {
            break;
        }
        fn_801F81AC();
    }
    return pAsync;
}

int _FileReqDoNextBlock(int unused, int arg, FileRequest_t *pReq)
{
    int done = 0;
    FileAsyncRequest_t *pAsync = pReq->mpAsync;
    int size;

    if (pReq->mpBlockFn) {
        pReq->mpBlockFn(pAsync->mSize, pAsync->mpBuffer, arg, pReq->mpArg);
    }
    if (pReq->mSize != pReq->mDone) {
        int step = pAsync->mSize;

        if (!pReq->mCyclic) {
            pAsync->mpBuffer += step;
        }
        pAsync->mPos += step;
        size = pReq->mSize - pReq->mDone;
        if (size > pReq->mBlockSize) {
            size = pReq->mBlockSize;
        }
        pAsync->mSize = size;
        File_StreamInfo[pReq->mHandle].mAsyncPos += size;
        if (pAsync->mType == 2 && File_StreamInfo[pReq->mHandle].mAsyncPos > File_StreamInfo[pReq->mHandle].mLength) {
            File_StreamInfo[pReq->mHandle].mLength = File_StreamInfo[pReq->mHandle].mAsyncPos;
        }
        pReq->mDone += pAsync->mSize;
    } else {
        if (pReq->mpDoneFn) {
            pReq->mpDoneFn(pReq->mSize, 0, pReq->mpArg);
        }
        done = 1;
        _DeleteFileRequestNode(pReq);
    }
    return done;
}

FileRequest_t *_FileRequest(FileRequest_t *pSrc, int type)
{
    FileRequest_t *pReq = _GetNewFileRequest();
    FileAsyncRequest_t *pAsync;
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
    pAsync = _FileGetAsyncRequest();
    pReq->mpAsync = pAsync;
    pAsync->mType = type;
    pAsync->mState = state;
    pAsync->mpStep = (int (*)(int, int, void *))_FileReqDoNextBlock;
    pAsync->mpReq = pReq;
    pAsync->mHandle = pReq->mHandle;
    pAsync->mPos = File_StreamInfo[pReq->mHandle].mPos;
    pAsync->mpBuffer = pReq->mpBuffer;
    size = pReq->mSize;
    if (size > pReq->mBlockSize) {
        size = pReq->mBlockSize;
    }
    pAsync->mSize = size;
    pAsync->mPriority = pReq->mPriority;
    File_StreamInfo[pReq->mHandle].mPos += pReq->mSize;
    pReq->mDone = pAsync->mSize;
    if (pAsync->mType == 2 && File_StreamInfo[pReq->mHandle].mPos > File_StreamInfo[pReq->mHandle].mLength) {
        File_StreamInfo[pReq->mHandle].mLength = File_StreamInfo[pReq->mHandle].mPos;
    }
    fn_801F7BD4(FileQueueAsyncRequest(pAsync));
    return pReq;
}

void FileCreateAbsoluteFileName(char *pDst, const char *pPath, const char *pName, int flags)
{
    char prefix[128];
    int len;

    switch (flags & 0xF) {
    case 1:
        strcpy(prefix, File_InitParms.mPath1);
        break;
    case 4:
        strcpy(prefix, File_InitParms.mPath0);
        break;
    case 3:
        strcpy(prefix, File_InitParms.mPath3);
        break;
    case 8:
        strcpy(prefix, File_InitParms.mPath8);
        break;
    default:
        strcpy(prefix, File_InitParms.mPath0);
        break;
    }
    len = strlen(pPath);
    len += strlen(pName);
    len += strlen(prefix);
    if (len != -1 && pDst) {
        strcpy(pDst, prefix);
        strcat(pDst, pPath);
        strcat(pDst, pName);
    }
}

int FileInit(FileInitParms_t *pConfig)
{
    int error = 0;
    int i;
    int j;

    if (!File_ModuleActive) {
        File_InitParms = *pConfig;
        File_StreamInfo = fn_801D2B7C(i = File_InitParms.mNumFiles * sizeof(FileStreamInfo_t), 0, 0);
        MemFill(File_StreamInfo, i, 0, 1);
        File_HandleInUseCS = fn_801D2B7C(i = File_InitParms.mNumFiles * 0x20, 0, 0);
        MemFill(File_HandleInUseCS, i, 0, 1);
        for (i = 0; i < 9; i++) {
            File_AsyncThreadActive[i] = 0;
        }
        fn_801F7FA8(&File_AsyncThreadActiveCS);
        for (j = 0; j < File_InitParms.mNumFiles; j++) {
            fn_801F7FA8(&File_HandleInUseCS[j]);
        }
        File_pAsyncRequestList = fn_801C68FC(1, 0, 0x40, sizeof(FileAsyncRequest_t), (int (*)(void *, void *))_FileRequestInsertFunc, 0);
        fn_801F7FA8(&File_AsyncRequestListCS);
        File_AsyncFileCopy = 0;
        File_pFileRequestList = DSNewNodeHandler(1, 0x40, sizeof(FileRequest_t), 0);
        fn_801F7FA8(&File_RequestListCS);
        FileLLInit(&File_InitParms);
        _File_uNumOpenFiles = 0;
        File_uMemFlags = 0;
        File_ModuleActive = 1;
    } else {
        error = 0xA0001;
    }
    fn_801F7BD4(error);
    return error;
}

int FileShutdown(void)
{
    int error = 0;
    int i;

    if (File_ModuleActive) {
        FileLLShutdown();
        for (i = 0; i < File_InitParms.mNumFiles; i++) {
            if (i >= 0 && i < File_InitParms.mNumFiles && File_StreamInfo[i].mInUse) {
                FileAsyncWaitStream(i);
            }
            fn_801F80D0(&File_HandleInUseCS[i]);
        }
        fn_801C69E4(File_pAsyncRequestList);
        fn_801F80D0(&File_AsyncRequestListCS);
        fn_801F80D0(&File_AsyncThreadActiveCS);
        DSDelNodeHandler(File_pFileRequestList);
        fn_801F80D0(&File_RequestListCS);
        fn_801D2BD0(File_StreamInfo);
        fn_801D2BD0(File_HandleInUseCS);
        File_StreamInfo = 0;
        File_HandleInUseCS = 0;
        File_uMemFlags = 0;
        File_ModuleActive = 0;
    } else {
        error = 0xA0002;
    }
    fn_801F7BD4(error);
    return error;
}

int FileOpenFileDevice(const char *pName, int device)
{
    int handle = 0;
    int error = 0;
    FilevDevicePath_t *pList;
    int count;
    int i;

    if (device == 0x2C) {
        device = _File_DefaultDevice;
    }
    if (device <= 0) {
        pList = _File_CurrentvDeviceList->mpList[-device];
        error = 0xA0003;
        count = pList->mCount;
        for (i = 0; error == 0xA0003 && i < count; i++) {
            if ((handle = FileOpenhDevice(pName, pList->mDevice[i], pList->mpPrefix[i])) >= 0) {
                error = 0;
            }
        }
    } else {
        if ((handle = FileOpenhDevice(pName, device, "")) < 0) {
            error = 0xA0003;
        }
    }
    fn_801F7BD4(error);
    if (error == 0) {
        _File_uNumOpenFiles++;
        _File_uMaxFilesOpenedAtOnce = _File_uMaxFilesOpenedAtOnce < _File_uNumOpenFiles ? _File_uNumOpenFiles : _File_uMaxFilesOpenedAtOnce;
        return handle;
    }
    return -1;
}

int FileClose(int handle)
{
    int error;

    FileAsyncWaitStream(handle);
    error = FileCloseStream(handle);
    fn_801F7BD4(error);
    if (error == 0) {
        _File_uNumOpenFiles--;
    }
    return error;
}

int FileSeek(int handle, int offset, unsigned int whence)
{
    int error = 0;
    FileStreamInfo_t *pFile;

    switch (whence) {
    case 0:
        File_StreamInfo[handle].mPos = offset;
        break;
    case 1:
        File_StreamInfo[handle].mPos += offset;
        break;
    case 2:
        File_StreamInfo[handle].mPos = File_StreamInfo[handle].mLength - offset;
        break;
    }
    if (File_StreamInfo[handle].mPos < 0) {
        File_StreamInfo[handle].mPos = 0;
        error = 0xA0004;
    } else if (File_StreamInfo[handle].mPos > File_StreamInfo[handle].mLength) {
        File_StreamInfo[handle].mPos = File_StreamInfo[handle].mLength;
        error = 0xA0004;
    }
    fn_801F7BD4(error);
    return error;
}

int FileExistsFileDevice(const char *pName, int device)
{
    int handle = FileOpenFileDevice(pName, device);
    int error;

    if (handle < 0) {
        error = 0xA0003;
    } else {
        error = FileClose(handle);
    }
    fn_801F7BD4(error);
    return error;
}

int FileReadCallback(int handle, char *pBuffer, int size, void (*callback)(int, int, int))
{
    FileRequest_t req;
    FileWaitResult_t result;
    int error = 0;
    int count;

    result.mCount = 0;
    result.mDone = 0;
    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mPriority = 100;
    req.mBlockSize = 0x8000;
    req.mpDoneFn = (FileDoneFn_t)_FileAsyncCallback;
    req.mpArg = &result;
    req.mCyclic = 0;
    req.mpBlockFn = 0;
    _FileRequest(&req, 1);
    FileAsyncWaitStream(handle);
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

int FileWriteCallback(int handle, char *pBuffer, int size, void (*callback)(int, int, int))
{
    FileRequest_t req;
    FileWaitResult_t result;
    int error = 0;
    int count;

    result.mCount = 0;
    result.mDone = 0;
    req.mHandle = handle;
    req.mpBuffer = pBuffer;
    req.mSize = size;
    req.mPriority = 100;
    req.mBlockSize = 0x8000;
    req.mpDoneFn = (FileDoneFn_t)_FileAsyncCallback;
    req.mpArg = &result;
    req.mCyclic = 0;
    req.mpBlockFn = 0;
    _FileRequest(&req, 2);
    FileAsyncWaitStream(handle);
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

FileRequest_t *FileReadAsync(int handle, char *pBuffer, int size, int priority, FileDoneFn_t doneFn,
                              void *pArg)
{
    FileRequest_t req;
    FileRequest_t *pReq;
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
    if (!(pReq = _FileRequest(&req, 1))) {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return pReq;
}

FileRequest_t *FileReadAsyncCyclic(int handle, char *pBuffer, int size, int priority, FileDoneFn_t doneFn,
                              void *pArg, FileBlockFn_t blockFn, int blockSize)
{
    FileRequest_t req;
    FileRequest_t *pReq;
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
    if (!(pReq = _FileRequest(&req, 1))) {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return pReq;
}

FileRequest_t *FileWriteAsync(int handle, char *pBuffer, int size, int priority, FileDoneFn_t doneFn,
                              void *pArg)
{
    FileRequest_t req;
    FileRequest_t *pReq;
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
    if (!(pReq = _FileRequest(&req, 2))) {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return pReq;
}

FileRequest_t *FileRePrioritizeAsync(FileRequest_t *pReq, int priority)
{
    if (pReq) {
        fn_801F8014(&File_AsyncRequestListCS);
        if (pReq->mpAsync) {
            pReq->mPriority = priority;
            if (pReq->mpAsync->mState == 0) {
                pReq->mpAsync->mPriority = priority;
                fn_801C6BC0(File_pAsyncRequestList, pReq->mpAsync);
                fn_801C6AA4(File_pAsyncRequestList, pReq->mpAsync, 0);
            } else {
                pReq->mpAsync->mPriority = priority;
            }
        }
        fn_801F809C(&File_AsyncRequestListCS);
    }
    return pReq;
}

int FileGetLength(int handle)
{
    return File_StreamInfo[handle].mLength;
}

int FileGetPosition(int handle)
{
    return File_StreamInfo[handle].mPos;
}

int FileSetDeviceList(FilevDeviceList_t *pTable)
{
    if (pTable) {
        _File_CurrentvDeviceList = pTable;
    } else {
        _File_CurrentvDeviceList = &_File_DefaultvDeviceList;
    }
    return 0;
}

FilevDeviceList_t *FileGetDeviceList(void)
{
    return _File_CurrentvDeviceList;
}

int FileSetDefaultDevice(int device)
{
    _File_DefaultDevice = device;
    return 0;
}

void FileLockAsyncRequestList(void)
{
    fn_801F8014(&File_AsyncRequestListCS);
}

void FileUnlockAsyncRequestList(void)
{
    fn_801F809C(&File_AsyncRequestListCS);
}

int FileSetMemAllocFlags(int flags)
{
    int old = File_uMemFlags;

    File_uMemFlags = flags;
    return old;
}
