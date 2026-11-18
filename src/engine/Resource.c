/* Loads resource directories and their entries from files or memory, including
 * asynchronous reads, decompression, caching and timed request processing. */
#include "engine/Resource.h"
#include "engine/system.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"

typedef struct ResRequest_t {
    ResDoneCallback_t pCallback;
    void *pUser;
    ResFile_t *pRes;
    int mIndex;
    int mDiskSize;
    int mFullSize;
    void *pBuffer;
    int mHeap;
    int mNoStore;
    unsigned short mRaw;
    char unk_0x26[2];
    int mFileOffset;
    unsigned char mCache;
    unsigned char mDone;
    char unk_0x2E[2];
    int mError;
    unsigned int mTime;
} ResRequest_t;

typedef struct ResAsyncEvent_t {
    int mType;
    char *pName;
    unsigned int mFlags;
    void *pBuffer;
    int unk_0x10;
    int mSize;
    unsigned int mTime;
    unsigned int mNow;
} ResAsyncEvent_t;

/* Codec stream buffer (0x1C bytes). */
typedef struct ResCodecBuffer_t {
    void *pData;
    unsigned int mSize;
    unsigned int mPos;
    char unk_0xC[0xC];
    unsigned char mDone;
} ResCodecBuffer_t;

typedef struct ResBlockDecoder_t {
    ResCodecBuffer_t *pSrc;
} ResBlockDecoder_t;

typedef struct ResTerfBlock_t {
    unsigned int mTag;
    unsigned int mSize;
} ResTerfBlock_t;

typedef struct ResTerfHeader_t {
    unsigned short mVersion;
    unsigned char mBigEndian;
    unsigned char unk_0x3;
    unsigned short mAlignment;
    unsigned short mNumRes;
} ResTerfHeader_t;

typedef struct ResTrackOpenDone_t {
    ResFile_t *pRes;
    unsigned int mSize;
} ResTrackOpenDone_t;

typedef struct ResTrackLoadDone_t {
    ResFile_t *pRes;
    int mIndex;
} ResTrackLoadDone_t;

extern int ResQuickloadIsInFile(int file, char *pName, unsigned int id, int *pHandle, int *pOffset);
extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileGetPosition(int handle);
extern int FileGetLength(int handle);
extern int FileGetSize(int handle);
extern void AuxRamUpload(unsigned int dest, void *pSrc, unsigned int size);
extern void *fn_801D310C(void *pAddr, int size, int ident, int flags);

extern int ResLooseFileOpen(ResFile_t *pRes, int index);
extern void AuxRamDownload(void *pDest, unsigned int source, unsigned int length);
extern int fn_801C2D88(char *pBuffer, unsigned int size, const char *pFormat, ...);
extern char _Res_szDiskLabelByHandle[];
extern char _Res_szDiskLabelByName[];
extern char _Res_szRamLabelByHandle[];
extern char _Res_szRamLabelByName[];
extern char _Res_szNameFormat[];
extern char _Res_szAramLabelByHandle[];
extern char _Res_szAramLabelByName[];

extern void *FileReadAsync(int handle, void *pBuffer, int size, int priority,
                         void (*pDone)(int, int, void *), void *pArg);
extern int ResLooseFileExists(ResFile_t *pRes, int index);
extern void *memmove(void *pDst, const void *pSrc, unsigned int size);
extern char _Res_szLoadAllLabelByHandle[];
extern char _Res_szLoadAllLabelByName[];

extern Lock_801F8014 _Res_sAsyncCountLock;
extern Lock_801F8014 _Res_sResourceLock;
extern unsigned char _Res_bModuleActive;
extern int _Res_iAsyncLoadCount;
extern int _Res_iAsyncOverride;
extern void (*_Res_pAsyncDebugProc)(ResFile_t *pRes, int index, ResAsyncEvent_t *pEvent, int a, int b);
extern int _Res_iAsyncDebugParm;
extern void (*_Res_pLoopingCallback)(int type);
extern void (*_Res_pErrorCallback)(char *pName, int err);
extern unsigned char _Res_bCachingEnabled;
extern unsigned char _Res_bLooseFileSupport;
extern unsigned int _Res_uTimedAsyncTick;
extern int _Res_iTimedAsyncPut;
extern int _Res_iTimedAsyncGet;
extern int _Res_uMemAllocFlags;
extern void *_Res_pBlockLoadBuffer;
extern ResCodecBuffer_t _Res_sBlockInput;
extern ResCodecBuffer_t _Res_sBlockOutput;
extern ResBlockDecoder_t *_Res_pBlockDecompressor;
extern int _Res_iBlockBytesRead;
extern ResRequest_t *_Res_pBlockRequest;
extern ResRequest_t *_Res_apTimedAsyncRequests[16];
extern void *_Res_pResourceFileList;
extern char _Res_szIndexFormat[];

extern unsigned int strlen(const char *s);
extern char *strcpy(char *pDst, const char *pSrc);
extern int sprintf(char *s, const char *format, ...);

extern void *fn_801C6B4C(void *pPool, int mode);
extern void *fn_801C6C84(void *pPool, void *pItem);
extern void *fn_801C6A20(void *pPool);
extern void fn_801C6C0C(void *pPool, void *pItem);
extern int fn_801C6DCC(void *pPool, void *pStart, void *pKey, void *pFound, int (*pMatch)(void *, void *, void *));
extern int FilePerformWrite(int file, int offset, void *pBuffer, int size);
extern void FileAsyncWaitStream(int handle);
extern int FileHostCheckActive(void);
extern int FileOpenFileDevice(const char *pName, int device);
extern int FileClose(int handle);
extern int FileReadCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
void fn_801D3318(int ident, const char *pLabel);
void fn_801D339C(int ident);
void fn_801D342C(int ident);
void fn_801D3470(void *pAddr, char *pOut, int size);
int strcmp(const char *pA, const char *pB);
void *FileReadAsyncCyclic(int file, char *pBuffer, int size, int priority, void (*pDone)(int, int, void *), void *pArg,
                  void (*pBlock)(int, char *, int, void *), int blockSize);
ResBlockDecoder_t *GCmpBlockStart(int codec, int mode, ResCodecBuffer_t *pIn, ResCodecBuffer_t *pOut);
unsigned int GCmpBlockProcess(ResBlockDecoder_t *pDecomp);
void GCmpBlockStop(ResBlockDecoder_t *pDecomp);
static int _ResLoadRes(ResFile_t *pRes, unsigned int index, unsigned int *pBuffer);
static int _ResLoadResAsync(ResFile_t *pRes, unsigned int index, void *pBuffer, int heap, int a, ResDoneCallback_t pDone, void *pUser, int mode);
static int _ResInitResourceFile(ResFile_t *pRes, char *pName);
static int _ResInitRamResourceFile(ResFile_t *pRes, char *pName, unsigned int size);
int ResClose(ResFile_t *pRes);
int ResUnLoadAll(ResFile_t *pRes);
static void _ResUnprotectAll(ResFile_t *pRes);
extern void *memset();
extern void *memcpy();
extern int GCmpInit(int a);
extern int GCmpIsBlockCodec(int codec);
extern void GCmpSetLabel(const char *pName);
extern void GCmpDecompress(int codec, ResCodecBuffer_t *pSrc, ResCodecBuffer_t *pDst);
extern void DCFlushRange(void *p, unsigned int size);
extern char _Res_szModuleID[];
extern int GCmpShutdown(void);
extern int GCmpIsActive(void);

void ResClearFlags(ResFile_t *pRes, unsigned int flags);
void ResCallTimedAsync(unsigned int time);
int ResGetNumResources(ResFile_t *pRes);
void ResUnprotect(ResFile_t *pRes, int index);

static void _ResBlockLoadCompFileAsyncBlockCallback(int size, char *pData, int unused, void *pArg);

static void _ResGetDirInfo(ResFile_t *pRes, int index, unsigned int *pOffset, unsigned int *pPrevSize,
                        unsigned int *pSize)
{
    *pPrevSize = 0;
    if (pRes->mDirTag == 0x44495231) {
        *pOffset = pRes->pDir[index].mOffsetOrCodec;
        *pSize = pRes->pDir[index].mSize;
    } else {
        *pOffset = 0;
        *pSize = 0;
    }
    if (pRes->pBlocks != 0) {
        *pPrevSize = *pSize;
        *pSize = pRes->pBlocks[index].mSize;
    }
}

static unsigned int _ResGetBlockOffset(ResFile_t *pRes, int index)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;

    if (!(pRes->pFlags[index] & 8)) {
        _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
    } else {
        offset = ((unsigned int *)pRes->pExtra)[index];
    }
    return offset;
}

static void *_ResBlockLoadCompFileAsync(int file, int unused, int priority, void (*pDone)(int, int, void *), ResRequest_t *pReq)
{
    return FileReadAsyncCyclic(file, _Res_pBlockLoadBuffer, pReq->mDiskSize, priority, pDone, pReq, _ResBlockLoadCompFileAsyncBlockCallback, 0x8000);
}

static void _ResBlockLoadCompFileAsyncBlockCallback(int size, char *pData, int unused, void *pArg)
{
    ResRequest_t *pReq = pArg;
    ResFile_t *pRes = pReq->pRes;
    int index = pReq->mIndex;
    char info[0x14];

    if (_Res_pBlockDecompressor == 0) {
        _Res_sBlockInput.pData = pData;
        _Res_sBlockInput.mSize = size;
        _Res_sBlockInput.mPos = 0;
        _Res_sBlockInput.mDone = 0;
        _Res_iBlockBytesRead = 0;
        _Res_sBlockOutput.mSize = pReq->mFullSize;
        _Res_sBlockOutput.mPos = 0;
        _Res_sBlockOutput.mDone = 1;
        _Res_sBlockOutput.pData = pReq->pBuffer;
        fn_801D3470(pReq->pBuffer, info, sizeof(info));
        fn_801D339C(pReq->mHeap);
        fn_801D3318(pReq->mHeap, info);
        _Res_pBlockDecompressor = GCmpBlockStart(pRes->pBlocks[index].mOffsetOrCodec, 1, &_Res_sBlockInput, &_Res_sBlockOutput);
        fn_801D342C(pReq->mHeap);
        _Res_pBlockRequest = pReq;
    }
    _Res_iBlockBytesRead += size;
    if (_Res_iBlockBytesRead == pReq->mDiskSize) {
        _Res_pBlockDecompressor->pSrc->mDone = 1;
    }
    _Res_pBlockDecompressor->pSrc->mSize = size;
    _Res_pBlockDecompressor->pSrc->mPos = 0;
    GCmpBlockProcess(_Res_pBlockDecompressor);
    if (_Res_pBlockDecompressor->pSrc->mDone) {
        GCmpBlockStop(_Res_pBlockDecompressor);
        _Res_pBlockDecompressor = 0;
    }
}

static unsigned int _ResCalcPad(unsigned int size, unsigned int align)
{
    unsigned int rem = size % align;

    if (rem != 0) {
        rem = align - rem;
    }
    return rem;
}

static int _ResFileInsertFunc(void *pA, void *pB)
{
    ResFile_t *pResA = pA;
    ResFile_t *pResB = pB;

    return strcmp(pResA->pName, pResB->pName);
}

static int _ResFileSearchByFileNameFunc(void *pItem, void *pKey, void *pFound)
{
    ResFile_t *pRes = pItem;
    ResFile_t **ppFound = pFound;
    int cmp = strcmp(pRes->pName, pKey);

    if (cmp == 0) {
        *ppFound = pRes;
    }
    return cmp;
}

static void _ResAsyncCallbackFunc(int result, int arg, void *pArg)
{
    ResRequest_t *pReq = pArg;
    ResFile_t *pRes;
    int index;
    int err;
    unsigned int codec;
    ResCodecBuffer_t src;
    ResCodecBuffer_t dst;
    ResAsyncEvent_t event;
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    ResTrackLoadDone_t track;

    pRes = pReq->pRes;
    index = pReq->mIndex;
    err = 0;
    if (_Res_pAsyncDebugProc != 0) {
        event.mType = 2;
        event.pName = pRes->pName;
        event.mFlags = pRes->mFlags;
        event.pBuffer = pReq->pBuffer;
        event.mSize = result;
        event.mTime = pReq->mTime;
        event.mNow = _Res_uTimedAsyncTick;
        _Res_pAsyncDebugProc(pRes, index, &event, arg, _Res_iAsyncDebugParm);
    }
    if (result < pReq->mDiskSize) {
        err = fn_801F7C88();
        fn_801D2BD0(pReq->pBuffer);
        pRes->pFlags[index] &= ~0x10;
    } else {
        if (pRes->pBlocks != 0 && pReq->mRaw == 0) {
            codec = pRes->pBlocks[index].mOffsetOrCodec;
        } else {
            codec = 0;
        }
        if (_Res_bCachingEnabled != 0 && pReq->pRes->mCacheHandle >= 0 && pReq->mCache != 0) {
            fn_801F318C(pReq->pRes, pReq->mIndex, pReq->mFileOffset, pReq->pBuffer, pReq->mDiskSize);
        }
        if (codec != 0 && GCmpIsBlockCodec(codec) == 0) {
            memset((void *)&src, 0, 0x1C);
            memset((void *)&dst, 0, 0x1C);
            src.mSize = pReq->mDiskSize;
            src.pData = fn_801D2BB0(1, src.mSize, 0, 0);
            memcpy(src.pData, pReq->pBuffer, src.mSize);
            dst.mSize = pReq->mFullSize;
            dst.pData = pReq->pBuffer;
            GCmpSetLabel(_Res_szModuleID);
            GCmpDecompress(codec, &src, &dst);
            GCmpSetLabel(0);
            fn_801D2BD0(src.pData);
        }
        if (pReq->mNoStore == 0) {
            pRes->pAddrs[index] = (unsigned int)pReq->pBuffer;
            pRes->pFlags[index] |= 6;
        }
        pRes->pFlags[index] &= ~0x10;
        _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
        DCFlushRange(pReq->pBuffer, size);
        if (pReq->pCallback != 0 && pReq->mTime == 0) {
            pReq->pCallback(pRes, index, pReq->pBuffer, 0, pReq->pUser);
        }
    }
    if (pReq->mTime != 0) {
        pReq->mError = err;
        pReq->mDone = 1;
    } else {
        fn_801D2BD0(pReq);
    }
    track.pRes = pRes;
    track.mIndex = index;
    ResTrackResource(3, &track);
    fn_801F8014(&_Res_sAsyncCountLock);
    _Res_iAsyncLoadCount--;
    fn_801F809C(&_Res_sAsyncCountLock);
}

static int _ResGetBaseBlockSize(unsigned int tag, int count)
{
    int size;

    switch (tag) {
    case 0x54455246:
        size = 8;
        break;
    case 0x434F4D50:
    case 0x44495231:
        size = count * 8;
        break;
    case 0x48534831:
        size = count * 4 + 0x10;
        break;
    case 0x48534832:
        size = count * 2 + 0xC;
        break;
    default:
        size = 0;
        break;
    }
    return size;
}

static inline void _ResWaitForLoad(ResFile_t *pRes, unsigned int index, int type)
{
    unsigned int start;
    unsigned int elapsed;

    if (pRes != 0) {
        start = fn_801F7B14();
        while (pRes->pFlags[index] & 0x10) {
            elapsed = fn_801F7B14() - start;
            if (_Res_pLoopingCallback != 0 && elapsed > 0x4650) {
                _Res_pLoopingCallback(type);
            }
            if (FileHostCheckActive() != 0) {
                FileAsyncWaitStream(pRes->mFile);
            } else {
                fn_801F81AC();
            }
        }
    }
}

static inline void _ResFindByName(char *pName, ResFile_t **ppRes)
{
    *ppRes = 0;
    fn_801C6DCC(_Res_pResourceFileList, 0, pName, ppRes, _ResFileSearchByFileNameFunc);
}

/* File, mapped-memory and ARAM sources share the same entry-loading interface. */
static int _ResLoadRes(ResFile_t *pRes, unsigned int index, unsigned int *pBuffer)
{
    ResCodecBuffer_t src;
    ResCodecBuffer_t dst;
    unsigned int size;
    unsigned int offset;
    unsigned int compressedSize;
    int file;
    int err = 0;
    int cache = 0;
    int quick = 0;
    unsigned int originalOffset;
    unsigned int codec;
    unsigned int address;

    if (_Res_bLooseFileSupport != 0 && ResLooseFileGetSize(pRes, index, &size) != 0) {
        file = ResLooseFileOpen(pRes, index);
        if (file < 0) {
            err = fn_801F7C88();
        } else {
            if (FileReadCallback(file, (void *)*pBuffer, size, 0) != (int)size) {
                err = fn_801F7C88();
            }
            FileClose(file);
        }
        return err;
    }
    _ResGetDirInfo(pRes, index, &offset, &compressedSize, &size);
    offset += pRes->mBaseOffset;
    originalOffset = offset;
    if (pRes->pBlocks != 0) {
        codec = pRes->pBlocks[index].mOffsetOrCodec;
    } else {
        codec = 0;
    }
    if (pRes->mState != 2 && pRes->mState != 3) {
        ResTrackLoadInfo_t track;
        ResTrackLoadDone_t done;
        int result;

        if (_Res_bCachingEnabled != 0 && pRes->mCacheHandle >= 0) {
            if (pRes->pCache[index] != 0) {
                file = pRes->mCacheHandle;
                cache = 0;
            } else {
                file = pRes->mFile;
                quick = ResQuickloadIsInFile(1, pRes->pName, index, &file, (int *)&offset);
                cache = 1;
            }
        } else {
            file = pRes->mFile;
            quick = ResQuickloadIsInFile(1, pRes->pName, index, &file, (int *)&offset);
        }
        track.mAsync = 0;
        track.mOffset = offset;
        track.pRes = pRes;
        track.mIndex = index;
        track.mDiskSize = codec ? compressedSize : size;
        track.mFullSize = size;
        track.mMode = quick ? 'Q' : '-';
        ResTrackResource(2, &track);
        FileSeek(file, offset, 0);
        if (codec != 0) {
            if (GCmpIsBlockCodec(codec)) {
                if (_Res_bCachingEnabled != 0 && cache != 0) {
                    void *pCompressed;
                    ResBlockDecoder_t *pDecomp;
                    unsigned int position;

                    memset(&src, 0, sizeof(src));
                    memset(&dst, 0, sizeof(dst));
                    src.mSize = compressedSize;
                    pCompressed = fn_801D2BB0(1, src.mSize, _Res_uMemAllocFlags, 0);
                    src.pData = pCompressed;
                    src.mDone = 0;
                    dst.mSize = size;
                    dst.pData = (void *)*pBuffer;
                    dst.mDone = 1;
                    if (FileReadCallback(file, pCompressed, compressedSize, 0) < (int)compressedSize) {
                        return fn_801F7C88();
                    }
                    fn_801F318C(pRes, index, originalOffset, src.pData, compressedSize);
                    cache = 0;
                    pDecomp = GCmpBlockStart(codec, 1, &src, &dst);
                    position = 0;
                    while (src.mDone == 0) {
                        position += pDecomp->pSrc->mPos;
                        pDecomp->pSrc->mSize = compressedSize - position > 0x8000 ? 0x8000 : compressedSize - position;
                        if (position + pDecomp->pSrc->mSize >= compressedSize) {
                            pDecomp->pSrc->mDone = 1;
                        }
                        pDecomp->pSrc->pData = (char *)pCompressed + position;
                        pDecomp->pSrc->mPos = 0;
                        GCmpBlockProcess(pDecomp);
                    }
                    GCmpBlockStop(pDecomp);
                    fn_801D2BD0(pCompressed);
                } else {
                    ResRequest_t request;

                    memset(&request, 0, sizeof(request));
                    request.pCallback = 0;
                    request.pUser = 0;
                    request.pRes = pRes;
                    request.mIndex = index;
                    request.mDiskSize = compressedSize;
                    request.mFullSize = size;
                    request.pBuffer = (void *)*pBuffer;
                    request.mHeap = 1;
                    request.mNoStore = 0;
                    request.mCache = 0;
                    request.mTime = 0;
                    _ResBlockLoadCompFileAsync(file, compressedSize, 100, 0, &request);
                    FileAsyncWaitStream(file);
                }
            } else {
                char label[32];

                memset(&src, 0, sizeof(src));
                memset(&dst, 0, sizeof(dst));
                src.mSize = compressedSize;
                src.pData = fn_801D2BB0(1, src.mSize, _Res_uMemAllocFlags, 0);
                dst.mSize = size;
                dst.pData = (void *)*pBuffer;
                if (FileReadCallback(file, src.pData, compressedSize, 0) < (int)compressedSize) {
                    return fn_801F7C88();
                }
                if (_Res_bCachingEnabled != 0 && cache != 0) {
                    fn_801F318C(pRes, index, originalOffset, src.pData, compressedSize);
                    cache = 0;
                }
                if (pRes->pName == 0) {
                    fn_801C2D88(label, sizeof(label), _Res_szDiskLabelByHandle, index, pRes->mFile);
                } else {
                    fn_801C2D88(label, sizeof(label), _Res_szDiskLabelByName, index, pRes->pName);
                }
                label[31] = 0;
                GCmpSetLabel(label);
                GCmpDecompress(codec, &src, &dst);
                GCmpSetLabel(0);
                if ((int)dst.mSize != (int)size) {
                    fn_801D2BD0(src.pData);
                    return fn_801F7C88();
                }
                fn_801D2BD0(src.pData);
            }
            result = size;
        } else {
            result = FileReadCallback(file, (void *)*pBuffer, size, 0);
        }
        if (result < (int)size) {
            err = fn_801F7C88();
        }
        if (_Res_bCachingEnabled != 0 && cache != 0) {
            fn_801F318C(pRes, index, originalOffset, (void *)*pBuffer, size);
        }
        done.pRes = pRes;
        done.mIndex = index;
        ResTrackResource(3, &done);
    } else if (pRes->mState == 2) {
        address = pRes->mBaseAddr + pRes->mBaseOffset + _ResGetBlockOffset(pRes, index);
        if (codec != 0) {
            char label[32];

            memset(&src, 0, sizeof(src));
            memset(&dst, 0, sizeof(dst));
            src.pData = (void *)*pBuffer;
            src.mSize = compressedSize;
            src.mPos = 0;
            dst.mSize = size;
            if (pRes->pName == 0) {
                fn_801C2D88(label, sizeof(label), _Res_szRamLabelByHandle, index, pRes->mFile);
            } else {
                fn_801C2D88(label, sizeof(label), _Res_szRamLabelByName, index, pRes->pName);
            }
            label[31] = 0;
            GCmpSetLabel(label);
            GCmpDecompress(codec, &src, &dst);
            GCmpSetLabel(0);
            if ((int)dst.mSize != (int)size) {
                fn_801D2BD0(dst.pData);
                return fn_801F7C88();
            }
            if (address != *pBuffer) {
                memcpy((void *)*pBuffer, dst.pData, dst.mSize);
                fn_801D2BD0(dst.pData);
            } else {
                *pBuffer = (unsigned int)dst.pData;
            }
        } else if (address != *pBuffer) {
            memcpy((void *)*pBuffer, (void *)address, size);
        } else {
            pRes->pFlags[index] |= 0x20;
        }
    } else if (pRes->mState == 3) {
        char name[16];

        fn_801C2D88(name, 15, _Res_szNameFormat, pRes->pName);
        name[9] = name[12];
        name[10] = name[13];
        name[11] = 0;
        sprintf(name + strlen(name), _Res_szIndexFormat, index);
        address = pRes->mBaseAddr + pRes->mBaseOffset + _ResGetBlockOffset(pRes, index);
        if (codec != 0) {
            unsigned int alignedSize;
            int flags;
            char label[32];

            memset(&src, 0, sizeof(src));
            memset(&dst, 0, sizeof(dst));
            alignedSize = (compressedSize + 31) & ~31;
            if (_Res_uMemAllocFlags & 4) {
                flags = (_Res_uMemAllocFlags & ~4) | 2;
            } else {
                flags = (_Res_uMemAllocFlags & ~2) | 4;
            }
            src.pData = fn_801D2BB0(1, alignedSize, flags, 0);
            AuxRamDownload(src.pData, pRes->mBaseOffset + _ResGetBlockOffset(pRes, index), alignedSize);
            src.mSize = compressedSize;
            src.mPos = 0;
            dst.mSize = size;
            dst.pData = fn_801D2BB0(1, dst.mSize, _Res_uMemAllocFlags, 0);
            if (pRes->pName == 0) {
                fn_801C2D88(label, sizeof(label), _Res_szAramLabelByHandle, index, pRes->mFile);
            } else {
                fn_801C2D88(label, sizeof(label), _Res_szAramLabelByName, index, pRes->pName);
            }
            label[31] = 0;
            GCmpSetLabel(label);
            GCmpDecompress(codec, &src, &dst);
            GCmpSetLabel(0);
            fn_801D2BD0(src.pData);
            if ((int)dst.mSize != (int)size) {
                fn_801D2BD0(dst.pData);
                return fn_801F7C88();
            }
            if (address != *pBuffer) {
                memcpy((void *)*pBuffer, dst.pData, dst.mSize);
                fn_801D2BD0(dst.pData);
            } else {
                *pBuffer = (unsigned int)dst.pData;
            }
        } else {
            unsigned int alignedSize = (size + 31) & ~31;
            void *pData = fn_801D2BB0(1, alignedSize, _Res_uMemAllocFlags, 0);

            AuxRamDownload(pData, pRes->mBaseOffset + _ResGetBlockOffset(pRes, index), alignedSize);
            if (address != *pBuffer) {
                memcpy((void *)*pBuffer, pData, size);
                fn_801D2BD0(pData);
            } else {
                *pBuffer = (unsigned int)pData;
            }
        }
    }
    DCFlushRange((void *)*pBuffer, size);
    return err;
}

/* Timed requests retain their buffers and completion records until dispatch. */
static int _ResLoadResAsync(ResFile_t *pRes, unsigned int index, void *pBuffer, int heap, int priority,
                 ResDoneCallback_t pDone, void *pUser, int mode)
{
    unsigned int size;
    unsigned int offset;
    unsigned int prevSize;
    ResRequest_t *pReq;
    int file;
    unsigned int codec;
    void *pRead;
    int err;

    prevSize = 0;
    size = 0;
    pReq = fn_801D2BB0(1, sizeof(ResRequest_t), 0, 0);
    err = 0;
    if (pReq != 0) {
        pReq->pCallback = pDone;
        pReq->pUser = pUser;
        pReq->mHeap = heap;
        pReq->mNoStore = mode;
        pReq->pRes = pRes;
        pReq->mIndex = index;
        pReq->mCache = 0;
        pReq->mTime = 0;
        fn_801F8014(&_Res_sAsyncCountLock);
        _Res_iAsyncLoadCount++;
        fn_801F809C(&_Res_sAsyncCountLock);
        if (_Res_bLooseFileSupport != 0 && ResLooseFileGetSize(pRes, index, &size) != 0) {
            pReq->pBuffer = pBuffer;
            pReq->mDiskSize = size;
            pReq->mFullSize = size;
            pReq->mFileOffset = 0;
            pReq->mRaw = 1;
            file = ResLooseFileOpen(pRes, index);
            if (file >= 0) {
                if (FileReadAsync(file, pBuffer, size, priority, _ResAsyncCallbackFunc, pReq) == 0) {
                    err = fn_801F7C88();
                }
            } else {
                err = fn_801F7C88();
            }
            return err;
        }
        pReq->mRaw = 0;
        if (pRes->mMinDelay != 0 && _Res_uTimedAsyncTick != 0) {
            if ((_Res_iTimedAsyncPut + 1) % 16 == _Res_iTimedAsyncGet) {
                ResRequest_t *pOld = _Res_apTimedAsyncRequests[_Res_iTimedAsyncGet];
                if (pOld->mDone == 0) {
                    ResFile_t *pOldRes = pOld->pRes;
                    int oldIndex = pOld->mIndex;
                    _ResWaitForLoad(pOldRes, oldIndex, 1);
                }
                if (_Res_pAsyncDebugProc != 0) {
                    ResAsyncEvent_t event;
                    event.mType = 4;
                    event.pName = pOld->pRes->pName;
                    event.mFlags = pOld->pRes->mFlags;
                    event.mSize = pOld->mFullSize;
                    event.pBuffer = pOld->pBuffer;
                    event.mTime = pOld->mTime;
                    event.mNow = _Res_uTimedAsyncTick;
                    _Res_pAsyncDebugProc(pOld->pRes, pOld->mIndex, &event, 0, _Res_iAsyncDebugParm);
                }
                _Res_iTimedAsyncGet = (_Res_iTimedAsyncGet + 1) & 0xF;
                pOld->pCallback(pOld->pRes, pOld->mIndex, pOld->pBuffer, pOld->mError, pOld->pUser);
                fn_801D2BD0(pOld);
            }
            pReq->mDone = 0;
            pReq->mError = 0;
            if (size <= pRes->mMinSize) {
                pReq->mTime = pRes->mMinDelay;
            } else if (size >= pRes->mMaxSize) {
                pReq->mTime = pRes->mMaxDelay;
            } else {
                pReq->mTime = pRes->mMinDelay + (size - pRes->mMinSize) *
                             (pRes->mMaxDelay - pRes->mMinDelay) / (pRes->mMaxSize - pRes->mMinSize);
            }
            pReq->mTime += _Res_uTimedAsyncTick;
            _Res_apTimedAsyncRequests[_Res_iTimedAsyncPut] = pReq;
            _Res_iTimedAsyncPut = (_Res_iTimedAsyncPut + 1) & 0xF;
        }
        if (_Res_pAsyncDebugProc != 0) {
            ResAsyncEvent_t event;
            event.mType = 1;
            event.pName = pRes->pName;
            event.mFlags = pRes->mFlags;
            event.mSize = size;
            event.pBuffer = pReq->pBuffer;
            event.mTime = pReq->mTime;
            event.mNow = _Res_uTimedAsyncTick;
            _Res_pAsyncDebugProc(pRes, index, &event, 0, _Res_iAsyncDebugParm);
        }
        _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
        offset += pRes->mBaseOffset;
        pReq->mFileOffset = offset;
        if (_Res_bCachingEnabled != 0 && pRes->mCacheHandle >= 0) {
            file = pRes->mCacheHandle;
            if (pRes->pCache[index] == 0) {
                file = pRes->mFile;
                pReq->mCache = 1;
            }
        } else {
            file = pRes->mFile;
        }
        FileSeek(file, offset, 0);
        if (pRes->pBlocks != 0) {
            codec = pRes->pBlocks[index].mOffsetOrCodec;
        } else {
            codec = 0;
        }
        {
            ResTrackLoadInfo_t track;
            track.pRes = pRes;
            track.mIndex = index;
            track.mOffset = offset;
            track.mAsync = 1;
            if (codec == 0) {
                track.mDiskSize = size;
            } else {
                track.mDiskSize = prevSize;
            }
            track.mFullSize = size;
            track.mMode = '-';
            ResTrackResource(2, &track);
        }
        if (codec != 0) {
            pReq->pBuffer = pBuffer;
            pReq->mDiskSize = prevSize;
            pReq->mFullSize = size;
            if (GCmpIsBlockCodec(codec) != 0) {
                pReq->mCache = 0;
                pRead = _ResBlockLoadCompFileAsync(file, prevSize, priority, _ResAsyncCallbackFunc, pReq);
            } else {
                pRead = FileReadAsync(file, pBuffer, prevSize, priority, _ResAsyncCallbackFunc, pReq);
            }
        } else {
            pReq->pBuffer = pBuffer;
            pReq->mDiskSize = size;
            pReq->mFullSize = size;
            pRead = FileReadAsync(file, pBuffer, size, priority, _ResAsyncCallbackFunc, pReq);
        }
        if (pRead == 0) {
            err = fn_801F7C88();
        }
    } else {
        err = fn_801F7C88();
    }
    fn_801F7BD4(err);
    if (pRes->mMinDelay != 0 && _Res_uTimedAsyncTick == 0) {
        _ResWaitForLoad(pRes, index, 1);
    }
    return err;
}

static unsigned int _ResLockRes(ResFile_t *pRes, int index)
{
    if (!(pRes->pFlags[index] & 4)) {
        if (!(pRes->pFlags[index] & 8)) {
            pRes->pFlags[index] |= 4;
        } else {
            pRes->mNumLocked++;
            pRes->pAddrs[index] = pRes->mBaseAddr + _ResGetBlockOffset(pRes, index);
            pRes->pFlags[index] |= 4;
        }
    }
    return pRes->pAddrs[index];
}

static unsigned int _ResUnlockRes(ResFile_t *pRes, int index)
{
    if (pRes->pFlags[index] & 4) {
        if (pRes->pFlags[index] & 1) {
            if (!(pRes->pFlags[index] & 8)) {
                pRes->pFlags[index] &= ~4;
            } else {
                pRes->mNumLocked--;
                pRes->pAddrs[index] = 0;
                pRes->pFlags[index] &= ~4;
            }
            return pRes->pAddrs[index];
        }
        return 0;
    }
    return pRes->pAddrs[index];
}

static int _ResReadTerfBlock(int file, void *pBuffer)
{
    int err;

    err = 0;
    if (FileReadCallback(file, pBuffer, 8, 0) < 8) {
        err = fn_801F7C88();
    }
    return err;
}

static int _ResReadBlock(int file, void *pBuffer, int size)
{
    int err;

    err = 0;
    if (FileReadCallback(file, pBuffer, size, 0) < size) {
        err = fn_801F7C88();
    }
    return err;
}

/* File-backed resources own copies of the directory and hash metadata. */
static int _ResInitResourceFile(ResFile_t *pRes, char *pName)
{
    int file;
    int position;
    ResTrackOpenInfo_t trackOpen;
    ResTerfBlock_t block;
    ResTerfHeader_t header;
    ResTrackOpenDone_t trackDone;
    int quickload;
    int err;
    unsigned int headerSize;
    unsigned int fileSize;
    unsigned int tag;
    int size;

    file = pRes->mFile;
    quickload = 0;
    if (ResQuickloadIsInFile(0, pName, 0, &file, &position) != 0) {
        quickload = 1;
        FileSeek(file, position, 0);
    }
    trackOpen.pName = pName;
    trackOpen.mMode = quickload ? 'Q' : '-';
    ResTrackResource(0, &trackOpen);
    position = FileGetPosition(file);
    err = _ResReadTerfBlock(file, &block);
    if (err != 0) {
        goto done;
    }
    if (block.mTag != 0x54455246) {
        err = 0xF0005;
        goto done;
    }
    err = _ResReadBlock(file, &header, sizeof(header));
    if (err != 0) {
        goto done;
    }
    FileSeek(file, position + block.mSize, 0);
    headerSize = block.mSize;
    header.unk_0x3 = 6;
    memset(&pRes->mEndPad, 0, 0x38);
    pRes->mNumRes = header.mNumRes;
    pRes->mAlignment = header.mAlignment;
    pRes->mBigEndian = header.mBigEndian;
    pRes->unk_0x12 = header.unk_0x3;
    pRes->pSlots = 0;
    pRes->unk_0x21 = 0;
    pRes->mCompressed = 0;
    pRes->mEndPad = FileGetSize((signed char)pRes->mFile);
    pRes->mNumWritten = 0;
    pRes->mPosition = 0;
    pRes->pCache = 0;
    pRes->mVersion = header.mVersion;
    pRes->pName = fn_801D2BB0(1, strlen(pName) + 1, _Res_uMemAllocFlags, 0);
    if (pRes->pName == 0) {
        err = fn_801F7C88();
        goto done;
    }
    strcpy(pRes->pName, pName);
    size = header.mNumRes * sizeof(*pRes->pAddrs);
    pRes->pAddrs = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
    if (pRes->pAddrs == 0) {
        err = fn_801F7C88();
        goto done;
    }
    memset(pRes->pAddrs, 0, size);
    size = header.mNumRes * sizeof(*pRes->pFlags);
    pRes->pFlags = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
    if (pRes->pFlags == 0) {
        err = fn_801F7C88();
        goto done;
    }
    memset((void *)pRes->pFlags, 0, size);
    position = FileGetPosition(file);
    fileSize = FileGetLength(file);
    while ((unsigned int)position < fileSize) {
        err = _ResReadTerfBlock(file, &block);
        if (err != 0) {
            goto done;
        }
        tag = block.mTag;
        switch (tag) {
        case 0x44495231:
            if (pRes->mDirTag == 0) {
                size = _ResGetBaseBlockSize(0x44495231, pRes->mNumRes);
                pRes->mDirTag = tag;
                pRes->mDirSize = size;
                pRes->mDirOffset = position;
                pRes->pDir = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
                if (pRes->pDir == 0) {
                    err = fn_801F7C88();
                    goto done;
                }
                err = _ResReadBlock(file, pRes->pDir, size);
                if (err != 0) {
                    goto done;
                }
            }
            break;
        case 0x434F4D50:
            size = _ResGetBaseBlockSize(0x434F4D50, pRes->mNumRes);
            pRes->pBlocks = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
            if (pRes->pBlocks == 0) {
                err = fn_801F7C88();
                goto done;
            }
            err = _ResReadBlock(file, pRes->pBlocks, size);
            if (err != 0) {
                goto done;
            }
            pRes->mCompressed = 1;
            pRes->mCompOffset = position;
            pRes->mCompSize = size;
            break;
        case 0x48534831:
        case 0x48534832:
            if (pRes->mHashTag == 0) {
                size = _ResGetBaseBlockSize(tag, pRes->mNumRes);
                pRes->mHashTag = tag;
                pRes->mHashSize = size;
                pRes->mHashOffset = position;
                pRes->pHash = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
                if (pRes->pHash == 0) {
                    err = fn_801F7C88();
                    goto done;
                }
                err = _ResReadBlock(file, pRes->pHash, size);
                if (err != 0) {
                    goto done;
                }
                pRes->pHashParams = (unsigned int *)(pRes->pHash + 1);
                pRes->pHashTable = (char *)pRes->pHashParams + pRes->pHash->mParamSize;
            }
            break;
        case 0x44415441:
            if (pRes->mBaseOffset == 0) {
                if (quickload != 0) {
                    pRes->mBaseOffset = headerSize;
                } else {
                    pRes->mBaseOffset = FileGetPosition(file) - sizeof(block);
                }
                pRes->mDataSize = block.mSize;
                if (quickload != 0) {
                    position = fileSize;
                    block.mSize = 0;
                }
            }
            break;
        default:
            err = 0xF0005;
            goto cleanup;
        case 0x54455246:
            break;
        }
        FileSeek(file, position + block.mSize, 0);
        position = FileGetPosition(file);
        if (tag != 0x44415441) {
            headerSize += block.mSize;
        }
    }
    trackDone.pRes = pRes;
    trackDone.mSize = headerSize;
    ResTrackResource(1, &trackDone);
    if (pRes->mBaseOffset == 0 || pRes->mDirTag == 0) {
        err = 0xF0005;
    }
done:
    if (err != 0) {
cleanup:
        if (pRes->pAddrs != 0) {
            fn_801D2BD0(pRes->pAddrs);
            pRes->pAddrs = 0;
        }
        if (pRes->pFlags != 0) {
            fn_801D2BD0((void *)pRes->pFlags);
            pRes->pFlags = 0;
        }
        if (pRes->pName != 0) {
            fn_801D2BD0(pRes->pName);
            pRes->pName = 0;
        }
        if (pRes->pDir != 0) {
            fn_801D2BD0(pRes->pDir);
            pRes->pDir = 0;
            pRes->mDirTag = 0;
        }
        if (pRes->pBlocks != 0) {
            fn_801D2BD0(pRes->pBlocks);
            pRes->pBlocks = 0;
        }
        if (pRes->pHash != 0) {
            fn_801D2BD0(pRes->pHash);
            pRes->pHash = 0;
            pRes->pHashTable = 0;
            pRes->pHashParams = 0;
            pRes->mHashTag = 0;
        }
    }
    fn_801F7BD4(err);
    return err;
}

/* Memory-backed resources borrow metadata; state 3 moves only the DATA area to ARAM. */
static int _ResInitRamResourceFile(ResFile_t *pRes, char *pName, unsigned int fileSize)
{
    ResTerfBlock_t block;
    ResTerfHeader_t header;
    char *pData;
    unsigned int position;
    unsigned int tag;
    void *pCopy;
    int size;
    int err;

    memcpy(&block, (void *)pRes->mBaseAddr, sizeof(block));
    err = 0;
    if (block.mTag != 0x54455246) {
        err = 0xF0005;
        goto done;
    }
    memcpy(&header, (void *)(pRes->mBaseAddr + sizeof(block)), sizeof(header));
    header.unk_0x3 = 6;
    memset(&pRes->mEndPad, 0, 0x38);
    pRes->mNumRes = header.mNumRes;
    pRes->mAlignment = header.mAlignment;
    pRes->mBigEndian = header.mBigEndian;
    pRes->unk_0x12 = header.unk_0x3;
    pRes->mVersion = header.mVersion;
    pRes->pName = pName;
    pRes->pSlots = 0;
    pRes->unk_0x21 = 0;
    pRes->mCompressed = 0;
    pRes->mEndPad = 0;
    pRes->mNumWritten = 0;
    pRes->mPosition = 0;
    pRes->pCache = 0;
    pRes->pAddrs = 0;
    pRes->pFlags = 0;
    position = block.mSize;
    pData = (char *)pRes->mBaseAddr + position;
    while (position < fileSize) {
        memcpy(&block, pData, sizeof(block));
        pData += sizeof(block);
        tag = block.mTag;
        switch (tag) {
        case 0x44495231:
            if (pRes->mDirTag == 0) {
                size = _ResGetBaseBlockSize(0x44495231, pRes->mNumRes);
                pRes->mDirTag = tag;
                pRes->mDirSize = size;
                pRes->pDir = (ResBlockEntry_t *)pData;
                pRes->mDirOffset = position;
            }
            break;
        case 0x434F4D50:
            size = _ResGetBaseBlockSize(0x434F4D50, pRes->mNumRes);
            pRes->pBlocks = (ResBlockEntry_t *)pData;
            pRes->mCompressed = 1;
            pRes->mCompSize = size;
            pRes->mCompOffset = position;
            break;
        case 0x48534831:
        case 0x48534832:
            if (pRes->mHashTag == 0) {
                size = _ResGetBaseBlockSize(tag, pRes->mNumRes);
                pRes->mHashTag = tag;
                pRes->mHashSize = size;
                pRes->mHashOffset = position;
                pRes->pHash = (ResHashHeader_t *)pData;
                pRes->pHashParams = (unsigned int *)(pRes->pHash + 1);
                pRes->pHashTable = (char *)pRes->pHashParams + pRes->pHash->mParamSize;
            }
            break;
        case 0x44415441:
            if (pRes->mBaseOffset == 0) {
                pRes->mDataSize = block.mSize;
                if (pRes->mState == 3) {
                    pCopy = fn_801D2BB0(pRes->mMode, block.mSize, _Res_uMemAllocFlags, 0);
                    AuxRamUpload((unsigned int)pCopy, (void *)(pRes->mBaseAddr + position), block.mSize);
                    fn_801D310C((void *)pRes->mBaseAddr, position, 0, 0);
                    pRes->mBaseOffset = (unsigned int)pCopy;
                } else {
                    pRes->mBaseOffset = position;
                }
            }
            break;
        case 0x54455246:
        default:
            break;
        }
        position += block.mSize;
        pData = (char *)pRes->mBaseAddr + position;
    }
    size = header.mNumRes * sizeof(*pRes->pAddrs);
    pRes->pAddrs = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
    if (pRes->pAddrs == 0) {
        err = fn_801F7C88();
        goto done;
    }
    memset(pRes->pAddrs, 0, size);
    size = header.mNumRes * sizeof(*pRes->pFlags);
    pRes->pFlags = fn_801D2BB0(1, size, _Res_uMemAllocFlags, 0);
    if (pRes->pFlags == 0) {
        err = fn_801F7C88();
        goto done;
    }
    memset((void *)pRes->pFlags, 0, size);
    if (pRes->mBaseOffset == 0 || pRes->mDirTag == 0) {
        err = 0xF0005;
    }
done:
    if (err != 0) {
        if (pRes->pAddrs != 0) {
            fn_801D2BD0(pRes->pAddrs);
            pRes->pAddrs = 0;
        }
        if (pRes->pFlags != 0) {
            fn_801D2BD0((void *)pRes->pFlags);
            pRes->pFlags = 0;
        }
        if (pRes->pName != 0) {
            fn_801D2BD0(pRes->pName);
            pRes->pName = 0;
        }
    }
    fn_801F7BD4(err);
    return err;
}

static void *_ResGetResourceBuffer(ResFile_t *pRes, unsigned int index, int heap, unsigned int *pBuffer, int noFlags)
{
    char name[0x10];
    unsigned int size;
    unsigned int offset;
    unsigned int prevSize;
    void *p;

    *pBuffer = 0;
    if (_Res_bLooseFileSupport != 0 && ResLooseFileGetSize(pRes, index, &size) != 0) {
        if (pRes->pDir[index].mSize < size) {
            strnzcpy(name, pRes->pName, 0xB);
            sprintf(name + strlen(name), _Res_szIndexFormat, index);
            if (noFlags != 0) {
                p = fn_801D2BB0(heap, size, 0, 0);
            } else {
                p = fn_801D2BB0(heap, size, _Res_uMemAllocFlags, 0);
            }
            if (p != 0) {
                pRes->mFlags |= 0x40;
                *pBuffer = (unsigned int)p;
            }
            return p;
        }
        if (pRes->mState == 2) {
            pRes->pFlags[index] = 0x20;
        }
    }
    if (pRes->mState == 1 && pRes->mBaseAddr != 0 && heap == pRes->mHeap) {
        pRes->pFlags[index] = 8;
        *pBuffer = _ResLockRes(pRes, index);
    } else if (pRes->mState == 2 || pRes->mState == 3) {
        *pBuffer = pRes->mBaseAddr + pRes->mBaseOffset + _ResGetBlockOffset(pRes, index);
    } else {
        _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
        strnzcpy(name, pRes->pName, 0xB);
        sprintf(name + strlen(name), _Res_szIndexFormat, index);
        if (noFlags != 0) {
            p = fn_801D2BB0(heap, size, 0, 0);
        } else {
            p = fn_801D2BB0(heap, size, _Res_uMemAllocFlags, 0);
        }
        if (p != 0) {
            *pBuffer = (unsigned int)p;
        }
    }
    return pBuffer;
}

static void _ResUnprotectAll(ResFile_t *pRes)
{
    int i;
    int count;

    count = ResGetNumResources(pRes);
    for (i = 0; i < count; i++) {
        ResUnprotect(pRes, i);
    }
}

int ResInit(int maxResources)
{
    int err;

    err = 0;
    if (GCmpIsActive() == 0) {
        GCmpInit(0);
    }
    if (_Res_bModuleActive == 0) {
        fn_801F7FA8(&_Res_sResourceLock);
        fn_801F7FA8(&_Res_sAsyncCountLock);
        fn_801F8014(&_Res_sResourceLock);
        _Res_pResourceFileList = fn_801C68FC(1, 1, maxResources, 0xA4, _ResFileInsertFunc, 0);
        _Res_pBlockLoadBuffer = fn_801D2BB0(1, 0x8000, _Res_uMemAllocFlags, 0);
        _Res_bModuleActive = 1;
        _Res_bCachingEnabled = 0;
        fn_801F2ED8(0);
        fn_801F809C(&_Res_sResourceLock);
    } else {
        err = 0xF0001;
    }
    _Res_iTimedAsyncPut = 0;
    _Res_iTimedAsyncGet = 0;
    _Res_uTimedAsyncTick = 0;
    fn_801F7BD4(err);
    return err;
}

int ResShutdown(void)
{
    ResFile_t *pRes;
    ResFile_t *pNext;
    int err;

    err = 0;
    if (_Res_bModuleActive != 0) {
        fn_801F8014(&_Res_sResourceLock);
        pNext = fn_801C6B4C(_Res_pResourceFileList, 0);
        while (pNext != 0) {
            pRes = pNext;
            ResClearFlags(pRes, 1);
            pNext = fn_801C6C84(_Res_pResourceFileList, pRes);
            ResClose(pRes);
        }
        fn_801C69E4(_Res_pResourceFileList);
        fn_801D2BD0(_Res_pBlockLoadBuffer);
        fn_801F809C(&_Res_sResourceLock);
        fn_801F80D0(&_Res_sResourceLock);
        fn_801F80D0(&_Res_sAsyncCountLock);
        _Res_bModuleActive = 0;
    } else {
        err = 0xF0002;
    }
    if (GCmpIsActive() != 0) {
        GCmpShutdown();
    }
    fn_801F7BD4(err);
    return err;
}

ResFile_t *ResOpenDevice(char *pName, int mode)
{
    ResFile_t *pRes;
    int err;

    pRes = 0;
    fn_801F8014(&_Res_sResourceLock);
    err = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else {
        _ResFindByName(pName, &pRes);
        if (pRes == 0) {
            pRes = fn_801C6A20(_Res_pResourceFileList);
            if (pRes == 0) {
                err = fn_801F7C88();
                goto done;
            }
            memset(pRes, 0, sizeof(ResFile_t));
            pRes->mFile = FileOpenFileDevice(pName, mode);
            if (pRes->mFile < 0) {
                err = fn_801F7C88();
                goto done;
            }
            err = _ResInitResourceFile(pRes, pName);
            if (err != 0) {
                FileClose(pRes->mFile);
                goto done;
            }
            if (_Res_bCachingEnabled != 0) {
                fn_801F2EE0(pRes, pName);
            }
            fn_801C6AA4(_Res_pResourceFileList, pRes, 0);
        }
        pRes->mOpenCount++;
    }
done:
    if (err != 0) {
        if (pRes != 0) {
            fn_801C6C0C(_Res_pResourceFileList, pRes);
            pRes = 0;
        }
        if (_Res_pErrorCallback != 0) {
            _Res_pErrorCallback(pName, err);
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return pRes;
}

ResFile_t *ResOpenRam(ResFile_t *pParent, unsigned int index, int heap, int mode)
{
    ResFile_t *pRes;
    char *pName;
    int err;
    unsigned int digits;
    unsigned int j;
    int len;
    unsigned int offset;
    unsigned int value;

    pRes = 0;
    fn_801F8014(&_Res_sResourceLock);
    err = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else {
        digits = 0;
        pRes = 0;
        for (j = pParent->mNumRes; j != 0; j /= 10) {
            digits++;
        }
        pName = fn_801D2BB0(1, strlen(pParent->pName) + 1 + digits, _Res_uMemAllocFlags, 0);
        if (pName == 0) {
            err = fn_801F7C88();
            goto done;
        }
        strcpy(pName, pParent->pName);
        pName[0xC] = 0;
        len = strlen(pName);
        value = index;
        for (j = 0; j < digits; j++) {
            pName[len + digits - 1 - j] = value % 10 + '0';
            value /= 10;
        }
        pName[len + digits] = 0;
        fn_801C6DCC(_Res_pResourceFileList, 0, pName, &pRes, _ResFileSearchByFileNameFunc);
        if (pRes == 0) {
            pRes = fn_801C6A20(_Res_pResourceFileList);
            if (pRes == 0) {
                err = fn_801F7C88();
                goto done;
            }
            memset(pRes, 0, sizeof(ResFile_t));
            pRes->mFile = -1;
            if (mode != 1) {
                pRes->mState = 3;
            } else {
                pRes->mState = 2;
            }
            pRes->mMode = mode;
            pRes->mBaseAddr = ResLoad(pParent, index, heap);
            pRes->pExtra = pParent;
            pRes->mIndex = index;
            err = _ResInitRamResourceFile(pRes, pName, ResGetSize(pRes->pExtra, pRes->mIndex));
            if (err != 0) {
                goto done;
            }
            for (index = 0; index < pRes->mNumRes; index++) {
                pRes->pAddrs[index] = 0;
                _ResGetDirInfo(pRes, index, &offset, &value, &value);
            }
            fn_801C6AA4(_Res_pResourceFileList, pRes, 0);
        } else {
            fn_801D2BD0(pName);
        }
        pRes->mOpenCount++;
    }
done:
    if (err != 0 && pRes != 0) {
        fn_801C6C0C(_Res_pResourceFileList, pRes);
        pRes = 0;
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return pRes;
}

int ResClose(ResFile_t *pRes)
{
    ResFile_t *pFound;
    unsigned int i;
    int err;
    int close;
    int flush;

    err = 0;
    close = 1;
    flush = 1;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes->pName == 0) {
        err = 0xF0006;
    } else {
        _ResFindByName(pRes->pName, &pFound);
        if (pFound != 0 && pFound == pRes) {
            if (pRes->mOpenCount != 0 && --pRes->mOpenCount != 0 && (pRes->mFlags & 1)) {
                close = 0;
                if (pRes->mFlags & 2) {
                    flush = 1;
                } else {
                    flush = 0;
                }
            }
            if (pRes->mState == 2) {
                if ((pRes->mFlags & 0x40) && pRes->unk_0x21 == 0) {
                    _ResUnprotectAll(pRes);
                    err = ResUnLoadAll(pRes);
                }
                if (pRes->pExtra == 0) {
                    err = ResUnLoadAll(pRes);
                }
                if (pRes->pName != 0) {
                    fn_801D2BD0(pRes->pName);
                }
                if (pRes->pAddrs != 0) {
                    fn_801D2BD0(pRes->pAddrs);
                    pRes->pAddrs = 0;
                }
                if (pRes->pFlags != 0) {
                    fn_801D2BD0((void *)pRes->pFlags);
                    pRes->pFlags = 0;
                }
                if (pRes->pExtra != 0) {
                    ResUnprotect(pRes->pExtra, pRes->mIndex);
                    ResUnLoad(pRes->pExtra, pRes->mIndex);
                }
            } else if (pRes->mState == 3) {
                if ((pRes->mFlags & 0x40) && pRes->unk_0x21 == 0) {
                    _ResUnprotectAll(pRes);
                    err = ResUnLoadAll(pRes);
                }
                if (pRes->pExtra == 0) {
                    err = ResUnLoadAll(pRes);
                }
                if (pRes->pName != 0) {
                    fn_801D2BD0(pRes->pName);
                }
                if (pRes->pAddrs != 0) {
                    fn_801D2BD0(pRes->pAddrs);
                    pRes->pAddrs = 0;
                }
                if (pRes->pFlags != 0) {
                    fn_801D2BD0((void *)pRes->pFlags);
                    pRes->pFlags = 0;
                }
                if (pRes->pExtra != 0) {
                    ResUnprotect(pRes->pExtra, pRes->mIndex);
                    ResUnLoad(pRes->pExtra, pRes->mIndex);
                }
                if (pRes->mBaseOffset != 0) {
                    fn_801D2BD0((void *)pRes->mBaseOffset);
                }
            } else {
                if (_Res_bCachingEnabled != 0 && pRes->mCacheHandle >= 0) {
                    fn_801F3104(pRes);
                    if (close) {
                        fn_801F30CC(pRes);
                    }
                }
                if (flush == 1 && pRes->unk_0x21 == 0) {
                    if (close) {
                        _ResUnprotectAll(pRes);
                    }
                    err = ResUnLoadAll(pRes);
                }
                if (pRes->unk_0x21 != 0) {
                    err = fn_801F1B6C(pRes);
                }
                if (close == 1) {
                    if (pRes->pSlots != 0) {
                        for (i = 0; i < pRes->mNumRes; i++) {
                            if (pRes->pSlots[i] != 0) {
                                fn_801D2BD0(pRes->pSlots[i]);
                            }
                        }
                        fn_801D2BD0(pRes->pSlots);
                    }
                    if (pRes->pName != 0) {
                        fn_801D2BD0(pRes->pName);
                    }
                    if (pRes->pDir != 0) {
                        fn_801D2BD0(pRes->pDir);
                    }
                    if (pRes->pHash != 0) {
                        fn_801D2BD0(pRes->pHash);
                    }
                    if (pRes->pBlocks != 0) {
                        fn_801D2BD0(pRes->pBlocks);
                    }
                    if (pRes->pAddrs != 0) {
                        fn_801D2BD0(pRes->pAddrs);
                        pRes->pAddrs = 0;
                    }
                    if (pRes->pFlags != 0) {
                        fn_801D2BD0((void *)pRes->pFlags);
                        pRes->pFlags = 0;
                    }
                    FileClose(pRes->mFile);
                }
            }
            if (close) {
                fn_801C6C0C(_Res_pResourceFileList, pRes);
            }
        } else {
            err = 0xF0005;
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

unsigned int ResLoad(ResFile_t *pRes, unsigned int index, int heap)
{
    unsigned int buffer;
    void *p;
    int err;

    buffer = 0;
    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            p = _ResGetResourceBuffer(pRes, index, heap, &buffer, 0);
            if (buffer != 0) {
                err = _ResLoadRes(pRes, index, &buffer);
            } else {
                err = fn_801F7C88();
            }
            if (err == 0) {
                pRes->pAddrs[index] = buffer;
                pRes->pFlags[index] |= 7;
            } else {
                if (p != 0) {
                    fn_801D2BD0(p);
                }
                buffer = 0;
            }
        } else {
            buffer = _ResLockRes(pRes, index);
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return buffer;
}

unsigned int ResLoadAsync(ResFile_t *pRes, unsigned int index, int heap, int a, ResDoneCallback_t pDone,
                         void *pUser)
{
    unsigned int buffer;
    void *p;
    int err;

    buffer = 0;
    fn_801F8014(&_Res_sResourceLock);
    err = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            p = _ResGetResourceBuffer(pRes, index, heap, &buffer, 1);
            if (buffer != 0) {
                pRes->pFlags[index] |= 0x11;
                err = _ResLoadResAsync(pRes, index, (void *)buffer, heap, a, pDone, pUser, 0);
            } else {
                err = fn_801F7C88();
            }
            if (err != 0) {
                if (p != 0) {
                    fn_801D2BD0(p);
                }
                buffer = 0;
            }
        } else {
            buffer = _ResLockRes(pRes, index);
            if (pDone != 0) {
                pDone(pRes, index, (void *)buffer, 0, pUser);
            }
        }
        if (_Res_iAsyncOverride > 0 && !(pRes->mFlags & 4)) {
            _ResWaitForLoad(pRes, index, 1);
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return buffer;
}

unsigned int ResLoadToBuffer(ResFile_t *pRes, unsigned int index, void *pBuffer)
{
    unsigned int buffer = (unsigned int)pBuffer;
    int err;

    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
        buffer = 0;
    } else if (index > pRes->mNumRes) {
        err = 0xF0006;
        buffer = 0;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            err = _ResLoadRes(pRes, index, &buffer);
            if (err == 0) {
                pRes->pAddrs[index] = buffer;
                pRes->pFlags[index] = 6;
            } else {
                buffer = 0;
            }
        } else {
            buffer = _ResLockRes(pRes, index);
            err = 0xF0007;
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return buffer;
}

int ResWriteFromBuffer(ResFile_t *pRes, unsigned int index, void *pBuffer)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    int err;

    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index > pRes->mNumRes) {
        err = 0xF0006;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (pRes->pFlags[index] & 2) {
            err = 0xF000B;
        } else {
            _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
            if (size != prevSize) {
                err = 0xF000C;
            } else if (pRes->mState != 2 && pRes->mState != 3) {
                err = FilePerformWrite(pRes->mFile, offset + pRes->mBaseOffset, pBuffer, size);
            } else {
                memcpy((void *)(pRes->mBaseAddr + pRes->mBaseOffset + _ResGetBlockOffset(pRes, index)), pBuffer, size);
            }
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

unsigned int ResLoadAsyncToBuffer(ResFile_t *pRes, unsigned int index, int heap, void *pBuffer, int a,
                         ResDoneCallback_t pDone, void *pUser)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    int err;

    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
            if (pBuffer != 0) {
                pRes->pFlags[index] |= 0x10;
                err = _ResLoadResAsync(pRes, index, pBuffer, heap, a, pDone, pUser, 0);
            } else {
                err = fn_801F7C88();
            }
            if (err != 0) {
                pBuffer = 0;
            }
        } else {
            pBuffer = (void *)_ResLockRes(pRes, index);
            err = 0xF0007;
            pDone(pRes, index, pBuffer, 0xF0007, pUser);
        }
        if (_Res_iAsyncOverride > 0 && !(pRes->mFlags & 4)) {
            _ResWaitForLoad(pRes, index, 1);
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return (unsigned int)pBuffer;
}

unsigned int ResCopyAsyncToBuffer(ResFile_t *pRes, unsigned int index, int heap, void *pBuffer, int a,
                         ResDoneCallback_t pDone, void *pUser)
{
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    int err;

    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (!(pRes->pFlags[index] & 2)) {
            _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
            if (pBuffer != 0) {
                pRes->pFlags[index] |= 0x10;
                err = _ResLoadResAsync(pRes, index, pBuffer, heap, a, pDone, pUser, 1);
            } else {
                err = fn_801F7C88();
            }
            if (err != 0) {
                pBuffer = 0;
            }
        } else {
            pBuffer = (void *)_ResLockRes(pRes, index);
            err = 0xF0007;
            pDone(pRes, index, pBuffer, 0xF0007, pUser);
        }
        if (_Res_iAsyncOverride > 0 && !(pRes->mFlags & 4)) {
            _ResWaitForLoad(pRes, index, 1);
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return (unsigned int)pBuffer;
}

int ResCopyToBuffer(ResFile_t *pRes, unsigned int index, void *pBuffer)
{
    unsigned int buffer = (unsigned int)pBuffer;
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    unsigned int src;
    int err;

    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
        buffer = 0;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
        buffer = 0;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if (pRes->pFlags[index] & 2) {
            _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
            if (pRes->pFlags[index] & 4) {
                src = pRes->pAddrs[index];
            } else {
                src = *(unsigned int *)pRes->pAddrs[index];
            }
            memcpy((void *)buffer, (void *)src, size);
        } else {
            err = _ResLoadRes(pRes, index, &buffer);
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

int ResUnLoad(ResFile_t *pRes, unsigned int index)
{
    int err;

    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else {
        _ResWaitForLoad(pRes, index, 1);
        if ((pRes->pFlags[index] & 2) && !(pRes->pFlags[index] & 0x40)) {
            if ((pRes->pFlags[index] & 1) && !(pRes->pFlags[index] & 0x20)) {
                if (!(pRes->pFlags[index] & 8)) {
                    err = fn_801D2BD0((void *)pRes->pAddrs[index]);
                } else {
                    _ResUnlockRes(pRes, index);
                }
            }
            if (pRes->mState != 2 && pRes->mState != 3) {
                pRes->pAddrs[index] = 0;
                pRes->pFlags[index] = 0;
            } else {
                pRes->pFlags[index] = 0;
                pRes->pAddrs[index] = 0;
            }
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

/* Bulk loading expands entries backwards so later entries keep their source bytes. */
int ResLoadAll(ResFile_t *pRes, int heap, int bulk)
{
    ResCodecBuffer_t src;
    ResCodecBuffer_t dst;
    ResTrackLoadInfo_t track;
    char label[32];
    unsigned int index;
    unsigned int offset;
    unsigned int prevSize;
    unsigned int size;
    unsigned int totalSize;
    int file;
    char *pBuffer;
    int result;
    int err = 0;

    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        if (bulk != 0) {
            for (index = 0; index < pRes->mNumRes; index++) {
                _ResWaitForLoad(pRes, index, 1);
                if (pRes->pFlags[index] & 2) {
                    bulk = 0;
                    break;
                }
                if (_Res_bLooseFileSupport != 0 && ResLooseFileExists(pRes, index) != 0) {
                    bulk = 0;
                    break;
                }
            }
        }
        if (bulk == 0) {
            for (index = 0; index < pRes->mNumRes; index++) {
                if (!(pRes->pFlags[index] & 2)) {
                    if (ResLoad(pRes, index, heap) == 0) {
                        err = fn_801F7C88();
                    } else {
                        pRes->pFlags[index] = 7;
                        _ResUnlockRes(pRes, index);
                    }
                }
            }
        } else {
            file = pRes->mFile;
            if (pRes->mBaseAddr != 0) {
                err = fn_801D2BD0((void *)pRes->mBaseAddr);
                pRes->mBaseAddr = 0;
            }
            if (pRes->pBlocks != 0) {
                _ResGetDirInfo(pRes, 0, &offset, &prevSize, &size);
                totalSize = offset;
                for (index = 0; index < pRes->mNumRes; index++) {
                    totalSize += pRes->pBlocks[index].mSize;
                    totalSize += _ResCalcPad(pRes->pBlocks[index].mSize, pRes->mAlignment);
                }
            } else {
                totalSize = pRes->mDataSize;
            }
            pBuffer = fn_801D2BB0(heap, totalSize, _Res_uMemAllocFlags, 0);
            if (pBuffer == 0) {
                err = fn_801F7C88();
                goto done;
            }
            pRes->mState = 1;
            pRes->mBaseAddr = (unsigned int)pBuffer;
            pRes->mHeap = heap;
            pRes->mNumLocked = 0;
            offset = pRes->mBaseOffset;
            result = ResQuickloadIsInFile(2, pRes->pName, -1, &file, (int *)&offset);
            {
                track.pRes = pRes;
                track.mIndex = -1;
                track.mAsync = 0;
                track.mOffset = pRes->mBaseOffset;
                track.mDiskSize = pRes->mDataSize;
                track.mFullSize = pRes->mDataSize;
                track.mMode = result != 0 ? 'Q' : '-';
                ResTrackResource(2, &track);
            }
            FileSeek(file, offset, 0);
            result = FileReadCallback(file, pBuffer, pRes->mDataSize, 0);
            {
                ResTrackLoadDone_t track;
                track.pRes = pRes;
                track.mIndex = -1;
                ResTrackResource(3, &track);
            }
            if (result < (int)pRes->mDataSize) {
                err = fn_801F7C88();
                fn_801D2BD0(pBuffer);
                pRes->mBaseAddr = 0;
                goto done;
            }
            pRes->pExtra = fn_801D2BB0(heap, pRes->mNumRes * sizeof(unsigned int), _Res_uMemAllocFlags, 0);
            memset(pRes->pExtra, 0, pRes->mNumRes * sizeof(unsigned int));
            if (pRes->pBlocks != 0) {
                _ResGetDirInfo(pRes, 0, &offset, &prevSize, &size);
                ((unsigned int *)pRes->pExtra)[0] = offset;
                for (index = 1; index < pRes->mNumRes; index++) {
                    _ResGetDirInfo(pRes, index - 1, &offset, &prevSize, &size);
                    ((unsigned int *)pRes->pExtra)[index] = ((unsigned int *)pRes->pExtra)[index - 1] + size;
                    ((unsigned int *)pRes->pExtra)[index] += _ResCalcPad(size, pRes->mAlignment);
                }
            } else {
                for (index = 0; index < pRes->mNumRes; index++) {
                    _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
                    ((unsigned int *)pRes->pExtra)[index] = offset;
                }
            }
            if (pRes->pBlocks != 0) {
                for (index = pRes->mNumRes; index > 0; index--) {
                    unsigned int codec = pRes->pBlocks[index - 1].mOffsetOrCodec;
                    char *pSrc;
                    char *pDst;
                    _ResGetDirInfo(pRes, index - 1, &offset, &prevSize, &size);
                    pSrc = pBuffer + offset;
                    pDst = pBuffer + ((unsigned int *)pRes->pExtra)[index - 1];
                    if (codec != 0) {
                        memset((void *)&src, 0, sizeof(src));
                        memset((void *)&dst, 0, sizeof(dst));
                        src.mSize = prevSize;
                        src.pData = fn_801D2BB0(1, src.mSize, _Res_uMemAllocFlags, 0);
                        memcpy(src.pData, pSrc, src.mSize);
                        dst.mSize = size;
                        dst.pData = pDst;
                        if (pRes->pName == 0) {
                            fn_801C2D88(label, sizeof(label), _Res_szLoadAllLabelByHandle, index, pRes->mFile);
                        } else {
                            fn_801C2D88(label, sizeof(label), _Res_szLoadAllLabelByName, index, pRes->pName);
                        }
                        label[31] = 0;
                        GCmpSetLabel(label);
                        GCmpDecompress(codec, &src, &dst);
                        GCmpSetLabel(0);
                        fn_801D2BD0(src.pData);
                    } else if (pSrc != pDst) {
                        memmove(pDst, pSrc, size);
                    }
                }
            }
            for (index = 0; index < pRes->mNumRes; index++) {
                pRes->pFlags[index] = 0xB;
                pRes->pAddrs[index] = 0;
            }
        }
    }
done:
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

int ResUnLoadAll(ResFile_t *pRes)
{
    unsigned int index;
    int result;
    int err;

    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        for (index = 0; index < pRes->mNumRes; index++) {
            _ResWaitForLoad(pRes, index, 1);
            if (pRes->pFlags[index] & 2) {
                result = ResUnLoad(pRes, index);
                if (result != 0) {
                    err = result;
                }
            }
        }
        if (pRes->mState == 1 && pRes->mBaseAddr != 0) {
            result = fn_801D2BD0((void *)pRes->mBaseAddr);
            if (result != 0) {
                err = result;
            }
            result = fn_801D2BD0(pRes->pExtra);
            if (result != 0) {
                err = result;
            }
            pRes->mBaseAddr = 0;
            pRes->pExtra = 0;
            pRes->mHeap = 0;
            pRes->mNumLocked = 0;
        }
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

int ResFindIndexByName(ResFile_t *pRes, char *pName)
{
    ResHashHeader_t *pHash;
    int err;
    int index;
    int hash;
    int value;

    pHash = pRes->pHash;
    index = -1;
    fn_801F8014(&_Res_sResourceLock);
    err = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pHash == 0 || pRes->pHashTable == 0 || pRes->mHashTag == 0) {
        err = 0xF000A;
    } else {
        switch (pHash->mType) {
        case 1:
            hash = ProcHashHSH1(pName, strlen(pName), pRes->pHashParams);
            break;
        case 2:
            hash = ProcHashHSH2((unsigned char *)pName, strlen(pName), pRes->pHashParams);
            break;
        default:
            index = -1;
            err = 0xF000A;
            goto done;
        }
        for (index = 0; index < pRes->mNumRes; index++) {
            switch (pHash->mWidth) {
            case 1:
                value = ((unsigned char *)pRes->pHashTable)[index];
                break;
            case 2:
                value = ((unsigned short *)pRes->pHashTable)[index];
                break;
            case 4:
                value = ((int *)pRes->pHashTable)[index];
                break;
            default:
                index = -1;
                err = 0xF000A;
                goto done;
            }
            if (value == hash) {
                break;
            }
        }
        if (index >= pRes->mNumRes) {
            index = -1;
        }
    }
done:
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return index;
}

unsigned int ResGetSize(ResFile_t *pRes, unsigned int index)
{
    unsigned int size;
    unsigned int offset;
    unsigned int prevSize;
    int err;

    prevSize = 0;
    size = 0;
    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (_Res_bLooseFileSupport == 0 || ResLooseFileGetSize(pRes, index, &size) == 0) {
        _ResGetDirInfo(pRes, index, &offset, &prevSize, &size);
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return size;
}

int ResGetNumResources(ResFile_t *pRes)
{
    int count;
    int err;

    count = 0;
    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        count = pRes->mNumRes;
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return count;
}

int ResIsLoaded(ResFile_t *pRes, unsigned int index)
{
    int err;
    int loaded;

    err = 0;
    loaded = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pRes->pFlags[index] & 2) {
        loaded = 1;
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return loaded;
}

int ResIsLoading(ResFile_t *pRes, unsigned int index)
{
    int err;
    int loading;

    err = 0;
    loading = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pRes->pFlags[index] & 0x10) {
        loading = 1;
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return loading;
}

int ResSync(int noWait)
{
    unsigned int start;
    unsigned int elapsed;

    if (noWait == 0) {
        start = fn_801F7B14();
        while (_Res_iAsyncLoadCount != 0) {
            elapsed = fn_801F7B14() - start;
            if (_Res_pLoopingCallback != 0 && elapsed > 0x4650) {
                _Res_pLoopingCallback(2);
            }
            fn_801F81AC();
        }
        ResCallTimedAsync(-1);
    }
    return _Res_iAsyncLoadCount;
}

int ResIsOpen(char *pName)
{
    ResFile_t *pFound;
    int open;

    pFound = 0;
    open = 0;
    if (_Res_bModuleActive != 0) {
        fn_801C6DCC(_Res_pResourceFileList, 0, pName, &pFound, _ResFileSearchByFileNameFunc);
        if (pFound != 0) {
            open = 1;
        }
    }
    return open;
}

int ResIsMemoryBacked(ResFile_t *pRes)
{
    ResFile_t *pFound;
    int err;
    int result;

    err = 0;
    result = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else {
        _ResFindByName(pRes->pName, &pFound);
        if (pFound != 0 && pFound == pRes) {
            result = pFound->mState == 2 || pFound->mState == 3;
        } else {
            err = 0xF0005;
        }
    }
    fn_801F7BD4(err);
    return result;
}

int ResGetStreamInfo(ResFile_t *pRes, unsigned int index, unsigned int *pSize, unsigned int *pOffset, int *pFile)
{
    unsigned int offset;
    unsigned int prevSize;
    int err;

    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else if (index >= pRes->mNumRes) {
        err = 0xF0006;
    } else if (pRes->pBlocks != 0 && pRes->pBlocks[index].mOffsetOrCodec != 0) {
        err = 0xF000E;
    } else {
        _ResGetDirInfo(pRes, index, &offset, &prevSize, pSize);
        *pOffset = offset + pRes->mBaseOffset;
        *pFile = pRes->mFile;
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return err;
}

void ResSetFlags(ResFile_t *pRes, unsigned int flags)
{
    int err;

    err = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        fn_801F8014(&_Res_sResourceLock);
        pRes->mFlags |= flags;
        fn_801F809C(&_Res_sResourceLock);
    }
    fn_801F7BD4(err);
}

void ResClearFlags(ResFile_t *pRes, unsigned int flags)
{
    int err;

    err = 0;
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        fn_801F8014(&_Res_sResourceLock);
        pRes->mFlags &= ~flags;
        fn_801F809C(&_Res_sResourceLock);
    }
    fn_801F7BD4(err);
}

void ResCallTimedAsync(unsigned int time)
{
    ResRequest_t *pReq;
    ResFile_t *pRes;
    ResAsyncEvent_t event;
    int index;

    fn_801F8014(&_Res_sResourceLock);
    if (time != -1) {
        _Res_uTimedAsyncTick = time;
    }
    if (time == 0) {
        time = -1;
    }
    while (_Res_iTimedAsyncGet != _Res_iTimedAsyncPut && time >= _Res_apTimedAsyncRequests[_Res_iTimedAsyncGet]->mTime) {
        pReq = _Res_apTimedAsyncRequests[_Res_iTimedAsyncGet];
        if (pReq->mDone == 0) {
            pRes = pReq->pRes;
            index = pReq->mIndex;
            _ResWaitForLoad(pRes, index, 1);
        }
        _Res_iTimedAsyncGet = (_Res_iTimedAsyncGet + 1) & 0xF;
        if (_Res_pAsyncDebugProc != 0) {
            event.mType = 3;
            event.pName = pReq->pRes->pName;
            event.mFlags = pReq->pRes->mFlags;
            event.mSize = pReq->mFullSize;
            event.pBuffer = pReq->pBuffer;
            event.mTime = pReq->mTime;
            event.mNow = _Res_uTimedAsyncTick;
            _Res_pAsyncDebugProc(pReq->pRes, pReq->mIndex, &event, 0, _Res_iAsyncDebugParm);
        }
        pReq->pCallback(pReq->pRes, pReq->mIndex, pReq->pBuffer, pReq->mError, pReq->pUser);
        fn_801D2BD0(pReq);
    }
    fn_801F809C(&_Res_sResourceLock);
}

void ResUnprotect(ResFile_t *pRes, int index)
{
    pRes->pFlags[index] &= ~0x40;
}

int ResGetAlignment(ResFile_t *pRes)
{
    int alignment;
    int err;

    alignment = 0;
    err = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
    } else if (pRes == 0) {
        err = 0xF0005;
    } else {
        alignment = pRes->mAlignment;
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return alignment;
}

int ResSetMemFlags(int flags)
{
    int old;

    old = _Res_uMemAllocFlags;
    _Res_uMemAllocFlags = flags;
    return old;
}

int ResGetMemAllocFlags(void)
{
    return _Res_uMemAllocFlags;
}
