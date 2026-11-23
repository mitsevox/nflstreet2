/* Keeps cached resource data and its saved resource-size index in sync. */

#include "engine/Resource.h"
#include "game/fn_801D2B7C.h"

typedef struct ResCacheWrite_t {
    ResFile_t *pFile;
    int mIndex;
    void *pBuffer;
    int mSize;
} ResCacheWrite_t;

extern int sprintf(char *buffer, const char *format, ...);
extern void *memset(void *dest, int value, unsigned int count);
extern int FileOpenFileDevice(const char *pName, int device);
extern int FileClose(int handle);
extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileReadCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int FileWriteCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int FileWriteAsync(int handle, void *pBuffer, int size, int priority,
                       void (*pCallback)(int, int, void *), void *pContext);
extern void FileAsyncWaitStream(int handle);
extern int FileGetSize(char handle);
extern int FileCompareModificationTime(int device);
extern int FileSetLength(int handle, int value);

static unsigned char _ResCache_bSync = 1;
static int _ResCache_Device = 0;

static void _ResCacheWriteCallback(int result, int error, void *pContext)
{
    ResCacheWrite_t *pWrite = pContext;

    fn_801D2BD0(pWrite->pBuffer);
    if (error == 0 && result == pWrite->mSize) {
        pWrite->pFile->pCache[pWrite->mIndex] = result;
    } else {
        pWrite->pFile->pCache[pWrite->mIndex] = 0;
    }
    fn_801D2BD0(pWrite);
}

void ResCacheSetDevice(int mode)
{
    _ResCache_Device = mode;
}

void ResCacheOpen(ResFile_t *pFile, char *pName)
{
    char name[128];
    int invalid = 0;
    int handle;
    int size;
    int file;

    if (FileGetSize(pFile->mFile) > 0x10B07600) {
        pFile->mCacheHandle = -1;
        return;
    }
    handle = FileOpenFileDevice(pName, _ResCache_Device);
    pFile->mCacheHandle = handle;
    if (handle < 0) {
        invalid = 1;
    } else if (FileCompareModificationTime(pFile->mFile) == 1) {
        invalid = 1;
        FileClose(pFile->mCacheHandle);
        pFile->mCacheHandle = -1;
    } else if (FileGetSize(pFile->mFile) != FileGetSize(pFile->mCacheHandle)) {
        invalid = 1;
    }
    if (invalid) {
        handle = FileOpenFileDevice(pName, _ResCache_Device | 0x20);
        pFile->mCacheHandle = handle;
        if (handle < 0) {
            return;
        }
        if (FileSetLength(handle, FileGetSize(pFile->mFile)) == 0) {
            pFile->pCache = fn_801D2BB0(1, pFile->mNumRes * 4, 0, 0);
            if (pFile->pCache != 0) {
                memset(pFile->pCache, 0, pFile->mNumRes * 4);
                return;
            }
        }
    } else {
        size = pFile->mNumRes * 4;
        pFile->pCache = fn_801D2BB0(1, size, 0, 0);
        if (pFile->pCache != 0) {
            sprintf(name, "CST%s", pName);
            name[127] = 0;
            file = FileOpenFileDevice(name, _ResCache_Device);
            if (file < 0) {
                memset(pFile->pCache, 0, size);
            } else {
                if (FileReadCallback(file, pFile->pCache, size, 0) != size) {
                    memset(pFile->pCache, 0, size);
                }
                FileClose(file);
            }
            return;
        }
    }
    FileClose(pFile->mCacheHandle);
    pFile->mCacheHandle = -1;
}

void ResCacheClose(ResFile_t *pFile)
{
    fn_801D2BD0(pFile->pCache);
    FileClose(pFile->mCacheHandle);
}

void ResCacheUpdateState(ResFile_t *pFile)
{
    char name[128];
    int handle = 0;

    FileAsyncWaitStream(pFile->mCacheHandle);
    sprintf(name, "CST%s", pFile->pName);
    name[127] = 0;
    handle = FileOpenFileDevice(name, _ResCache_Device | 0x20);
    if (handle >= 0) {
        FileWriteCallback(handle, pFile->pCache, pFile->mNumRes * 4, 0);
        FileClose(handle);
    }
}

void ResCacheWrite(ResFile_t *pFile, int index, int offset, void *pData, int size)
{
    /* FAKEMATCH: Keep the already-zero seek result and the write context in one local slot. */
    union {
        int seekResult;
        ResCacheWrite_t *pWrite;
    } result;
    void *pBuffer;
    unsigned char sync = _ResCache_bSync;

    if (sync) {
        result.seekResult = FileSeek(pFile->mCacheHandle, offset, 0);
        if (result.seekResult == 0) {
            if (FileWriteCallback(pFile->mCacheHandle, pData, size, 0) != size) {
                goto clearWrite;
            }
            pFile->pCache[index] = size;
        } else {
            pFile->pCache[index] = 0;
        }
    } else {
        pBuffer = fn_801D2BB0(1, size, 0, 0);
        if (pBuffer != 0) {
            result.pWrite = fn_801D2BB0(1, sizeof(ResCacheWrite_t), 0, 0);
            if (result.pWrite != 0) {
                memcpy(pBuffer, pData, size);
                result.pWrite->pFile = pFile;
                result.pWrite->mIndex = index;
                result.pWrite->pBuffer = pBuffer;
                result.pWrite->mSize = size;
                if (FileSeek(pFile->mCacheHandle, offset, 0) != 0 ||
                    FileWriteAsync(pFile->mCacheHandle, pBuffer, size, 100, _ResCacheWriteCallback, result.pWrite) == 0) {
                    fn_801D2BD0(result.pWrite);
                    fn_801D2BD0(pBuffer);
                    pFile->pCache[index] = 0;
                }
            } else {
                fn_801D2BD0(pBuffer);
                result.seekResult = 0;
            clearWrite:
                pFile->pCache[index] = result.seekResult;
            }
        } else {
            pFile->pCache[index] = 0;
        }
    }
}
