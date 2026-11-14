/* Quickload archives: a resource file opened whole, its FILS (file names) and DTLS (resource offsets)
   chunks parsed once, so resource lookups can find a resource's offset without seeking the archive. */
#include "engine/Resource.h"
#include "engine/bsearch.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"

typedef struct ResQuickloadChunk_t {
    unsigned int mID;
    int mSize;
} ResQuickloadChunk_t;

typedef struct ResQuickloadKey_t {
    unsigned short mFile;
    unsigned short mType;
    unsigned int mID;
    unsigned int mOffset;
} ResQuickloadKey_t;

typedef struct ResQuickloadEntry_t {
    int mKey;
    int mID;
    unsigned int mOffset;
} ResQuickloadEntry_t;

typedef struct ResQuickloadDetails_t {
    unsigned int mID;
    int mSize;
    int mCount;
    ResQuickloadEntry_t mEntries[1];
} ResQuickloadDetails_t;

typedef struct ResQuickloadFiles_t {
    unsigned int mID;
    int mSize;
    int mCount;
    char mEntries[1][0x30];
} ResQuickloadFiles_t;

typedef struct ResQuickload_t {
    int mHandle;
    char *pName;
    char *pData;
    ResQuickloadFiles_t *pFiles;
    ResQuickloadDetails_t *pDetails;
    int mDataOffset;
    int mPosition;
} ResQuickload_t;

typedef struct ResQuickloadAlias_t {
    char *pFrom;
    char *pTo;
} ResQuickloadAlias_t;

extern int strcmp(const char *a, const char *b);
extern void *fn_801C6A20(void *pPool);
extern void *fn_801C6B4C(void *pPool, int mode);
extern void fn_801C6C0C(void *pPool, void *pItem);
extern void *fn_801C6C84(void *pPool, void *pItem);
extern int FileOpenFileDevice(const char *pName, int device);
extern int FileClose(int handle);
extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileReadCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int FileGetPosition(int handle);

static void *_ResQuickload_pFileList = 0;
static ResQuickloadAlias_t *_aFilenameRemappings = 0;

int ResQuickloadClose(char *pName);

static void _ResQuickloadReadFileInfo(int handle, ResQuickload_t *pQuickload)
{
    int header[3];
    int size;
    ResQuickloadChunk_t *pChunk;

    FileReadCallback(handle, header, sizeof(header), 0);
    size = header[2];
    pQuickload->mDataOffset = size;
    pQuickload->mPosition = size;
    pQuickload->pData = fn_801D2BB0(1, size, ResGetMemAllocFlags(), 0);
    FileSeek(handle, 0, 0);
    FileReadCallback(handle, pQuickload->pData, size, 0);
    for (pChunk = (ResQuickloadChunk_t *)pQuickload->pData; (char *)pChunk < pQuickload->pData + size;
         pChunk = (ResQuickloadChunk_t *)((char *)pChunk + pChunk->mSize)) {
        switch (pChunk->mID) {
        case 0x46494C53:
            pQuickload->pFiles = (ResQuickloadFiles_t *)pChunk;
            break;
        case 0x44544C53:
            pQuickload->pDetails = (ResQuickloadDetails_t *)pChunk;
            break;
        // FAKEMATCH: an empty third case above 'FILS' (any such value) gives the target's case tree;
        // it adds no behaviour
        case 0x7FFFFFFF:
            break;
        }
    }
}

static int _ResQuickloadCompareFile1T(const void *pKey, const void *pEntry)
{
    return strcmp(pKey, pEntry);
}

static ResQuickload_t *_ResQuickloadGetFile(char *pName, int *pIndex)
{
    ResQuickload_t *pQuickload;
    ResQuickloadFiles_t *pFiles;
    char *pFound;

    for (pQuickload = fn_801C6B4C(_ResQuickload_pFileList, 0); pQuickload != 0;
         pQuickload = fn_801C6C84(_ResQuickload_pFileList, pQuickload)) {
        pFiles = pQuickload->pFiles;
        pFound = bsearch(pName, pFiles->mEntries, pFiles->mCount, sizeof(pFiles->mEntries[0]),
                         _ResQuickloadCompareFile1T);
        if (pFound != 0) {
            *pIndex = (pFound - (char *)pFiles->mEntries) / sizeof(pFiles->mEntries[0]);
            break;
        }
    }
    return pQuickload;
}

static int _ResQuickloadCompareDataEntry(const void *pKey, const void *pEntry)
{
    const ResQuickloadKey_t *a = pKey;
    const ResQuickloadKey_t *b = pEntry;
    int result;

    if (a->mFile > b->mFile) {
        result = 1;
    } else if (a->mFile < b->mFile) {
        result = -1;
    } else if (a->mType > b->mType) {
        result = 1;
    } else if (a->mType < b->mType) {
        result = -1;
    } else if (a->mID > b->mID) {
        result = 1;
    } else if (a->mID < b->mID) {
        result = -1;
    } else {
        result = 0;
    }
    return result;
}

// FAKEMATCH: the distance as an inline helper (not an expression macro) and the separate pPrev walk pointer
// below were found by search for the target's registers; the logic is the plain absolute difference.
static inline unsigned int _ResQuickloadDistance(unsigned int a, unsigned int b)
{
    return a > b ? a - b : b - a;
}

static ResQuickloadEntry_t *_ResQuickloadGetData(ResQuickloadDetails_t *pDetails, int file, int type,
                                               unsigned int id, unsigned int offset)
{
    ResQuickloadKey_t key;
    ResQuickloadEntry_t *pEntry;
    ResQuickloadEntry_t *pNext;
    ResQuickloadEntry_t *pPrev;

    key.mFile = file;
    key.mType = type;
    key.mID = id;
    key.mOffset = offset;
    pEntry = bsearch(&key, pDetails->mEntries, pDetails->mCount, sizeof(ResQuickloadEntry_t),
                     _ResQuickloadCompareDataEntry);
    if (pEntry != 0) {
        while (pEntry > pDetails->mEntries) {
            pPrev = pEntry - 1;
            if (pEntry->mKey != pPrev->mKey || pEntry->mID != pPrev->mID ||
                _ResQuickloadDistance(offset, pPrev->mOffset) >= _ResQuickloadDistance(offset, pEntry->mOffset)) {
                break;
            }
            pEntry = pPrev;
        }
        while (pEntry < &pDetails->mEntries[pDetails->mCount - 1]) {
            pNext = pEntry + 1;
            if (pEntry->mKey != pNext->mKey || pEntry->mID != pNext->mID ||
                _ResQuickloadDistance(offset, pNext->mOffset) >= _ResQuickloadDistance(offset, pEntry->mOffset)) {
                break;
            }
            pEntry = pNext;
        }
    }
    return pEntry;
}

static int _ResQuickloadIsActive(void)
{
    if (_ResQuickload_pFileList == 0) {
        return 0;
    }
    return 1;
}

void ResQuickloadInit(int count)
{
    _ResQuickload_pFileList = fn_801C68FC(1, 0, count, sizeof(ResQuickload_t), 0, 0);
    _aFilenameRemappings = 0;
}

void ResQuickloadShutdown(void)
{
    ResQuickload_t *pQuickload;

    for (pQuickload = fn_801C6B4C(_ResQuickload_pFileList, 0); pQuickload != 0;
         pQuickload = fn_801C6C84(_ResQuickload_pFileList, pQuickload)) {
        ResQuickloadClose(pQuickload->pName);
    }
    fn_801C69E4(_ResQuickload_pFileList);
    _ResQuickload_pFileList = 0;
}

int ResQuickloadOpenDevice(char *pName, int mode)
{
    int result = 0;
    int handle;
    ResQuickload_t *pQuickload;

    handle = FileOpenFileDevice(pName, mode);
    if (handle >= 0) {
        pQuickload = fn_801C6A20(_ResQuickload_pFileList);
        if (pQuickload != 0) {
            pQuickload->pName = pName;
            pQuickload->mHandle = handle;
            result = 1;
            _ResQuickloadReadFileInfo(handle, pQuickload);
            fn_801C6AA4(_ResQuickload_pFileList, pQuickload, 0);
        } else {
            FileClose(handle);
        }
    }
    return result;
}

int ResQuickloadClose(char *pName)
{
    int result = 0;
    ResQuickload_t *pQuickload;

    for (pQuickload = fn_801C6B4C(_ResQuickload_pFileList, 0); pQuickload != 0;
         pQuickload = fn_801C6C84(_ResQuickload_pFileList, pQuickload)) {
        if (strcmp(pQuickload->pName, pName) == 0) {
            fn_801D2BD0(pQuickload->pData);
            FileClose(pQuickload->mHandle);
            fn_801C6C0C(_ResQuickload_pFileList, pQuickload);
            result = 1;
            break;
        }
    }
    return result;
}

int ResQuickloadIsInFile(int file, char *pName, unsigned int id, int *pHandle, int *pOffset)
{
    int result = 0;
    int index = 0;
    ResQuickloadAlias_t *pAlias;
    ResQuickload_t *pQuickload;
    ResQuickloadEntry_t *pEntry;

    if (_ResQuickloadIsActive()) {
        if (_aFilenameRemappings != 0) {
            for (pAlias = _aFilenameRemappings; pAlias->pFrom != 0; pAlias++) {
                if (strcmp(pName, pAlias->pFrom) == 0) {
                    pName = pAlias->pTo;
                    break;
                }
            }
        }
        pQuickload = _ResQuickloadGetFile(pName, &index);
        if (pQuickload != 0) {
            pEntry = _ResQuickloadGetData(pQuickload->pDetails, file, index, id,
                                 FileGetPosition(pQuickload->mHandle) - pQuickload->mDataOffset);
            if (pEntry != 0) {
                result = 1;
                *pHandle = pQuickload->mHandle;
                pQuickload->mPosition = *pOffset = pQuickload->mDataOffset + pEntry->mOffset;
            }
        }
    }
    return result;
}
