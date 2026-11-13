/* Disc file client used by the game's file system: opens files on the game disc by path, keeps a
   table of open files, and runs one asynchronous disc read at a time through a 32 KB aligned buffer,
   which a helper thread copies to the caller's destination before signalling the next request. */

#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSSemaphore.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/dvd.h>
#include "game/fn_801D2B7C.h"
#include "engine/ctype.h"

typedef struct CdInfo_t {
    int mNumFiles;
    void (*mpReadDone)(int);
    DVDFileInfo *mpFiles;
    DVDFileInfo *mpReadFile;
    void *mpReadDst;
    int mReadOffset;
    int mReadSize;
} CdInfo_t;

extern CdInfo_t Cdinfo;
extern unsigned char _CDVDAlignedBuffer[];
extern int lbl_803EBC34;

static OSThread _CdReadCompleteThread;
static unsigned char CdReadCompleteThreadStack[0x2000] __attribute__((aligned(64)));
static OSSemaphore _File_SubmitReadRequest;
static OSSemaphore _File_ReadSemaphore;

int MemFill(void *pDest, int size, int value, int width);
void *memcpy();

static DVDFileInfo *_fsFindOpenFile(void)
{
    int i;

    for (i = 0; i < Cdinfo.mNumFiles && Cdinfo.mpFiles[i].length != 0; i++) {
    }
    if (i < Cdinfo.mNumFiles) {
        return &Cdinfo.mpFiles[i];
    }
    return 0;
}

static void _fsReadEndFunc(s32 result, DVDFileInfo *pFileInfo)
{
    if (result >= 0) {
        OSSignalSemaphore(&_File_ReadSemaphore);
    }
}

static void *_CdReadCompleteThreadFunc(void *pParam)
{
    for (;;) {
        OSWaitSemaphore(&_File_ReadSemaphore);
        memcpy(Cdinfo.mpReadDst, _CDVDAlignedBuffer, Cdinfo.mReadSize);
        DCFlushRange(Cdinfo.mpReadDst, Cdinfo.mReadSize);
        OSSignalSemaphore(&_File_SubmitReadRequest);
        if (Cdinfo.mpReadDone) {
            Cdinfo.mpReadDone(1);
        }
    }
}

int CDVD_init(int unused, int numFiles, int unused2, void (*pReadDone)(int))
{
    int size = numFiles * sizeof(DVDFileInfo);
    DVDFileInfo *pFiles;

    pFiles = fn_801D2BB0(1, size, lbl_803EBC34, 0);
    MemFill(&Cdinfo, sizeof(CdInfo_t), 0, 4);
    Cdinfo.mpFiles = pFiles;
    MemFill(pFiles, size, 0, 4);
    Cdinfo.mNumFiles = numFiles;
    OSInitSemaphore(&_File_ReadSemaphore, 10);
    OSInitSemaphore(&_File_SubmitReadRequest, 10);
    if ((unsigned char)OSCreateThread(&_CdReadCompleteThread, _CdReadCompleteThreadFunc, 0, CdReadCompleteThreadStack + sizeof(CdReadCompleteThreadStack), 0x2000, 12, 1)) {
        OSResumeThread(&_CdReadCompleteThread);
    }
    Cdinfo.mpReadDone = pReadDone;
    OSSignalSemaphore(&_File_SubmitReadRequest);
    return Cdinfo.mNumFiles;
}

int CDVD_open(const char *pName, int unused, int *pHandle)
{
    char path[64];
    char *pOut = path;
    DVDFileInfo *pFileInfo;
    int result;

    if (*pName == '/') {
        pName++;
    }
    for (; *pName; pName++, pOut++) {
        if (*pName == '\\') {
            *pOut = '/';
        } else {
            *pOut = toupper(*pName);
        }
    }
    *pOut = 0;
    pFileInfo = _fsFindOpenFile();
    if (pFileInfo) {
        *pHandle = pFileInfo - Cdinfo.mpFiles + 1;
        DVDOpen(path, pFileInfo);
        result = 1;
    } else {
        *pHandle = 0;
        result = 0;
    }
    return result;
}

int CDVD_close(int handle)
{
    DVDFileInfo *pFileInfo = &Cdinfo.mpFiles[handle - 1];

    DVDClose(pFileInfo);
    pFileInfo->length = 0;
    return 0;
}

int CDVD_read(int handle, void *pDst, int offset, int size)
{
    DVDFileInfo *pFileInfo = &Cdinfo.mpFiles[handle - 1];

    if (size > (int)(pFileInfo->length - offset) || size <= 0 || offset < 0) {
        size = pFileInfo->length - offset;
    }
    OSWaitSemaphore(&_File_SubmitReadRequest);
    Cdinfo.mpReadFile = pFileInfo;
    Cdinfo.mReadOffset = offset;
    Cdinfo.mReadSize = size;
    Cdinfo.mpReadDst = pDst;
    DVDReadAsyncPrio(pFileInfo, _CDVDAlignedBuffer, (size + 0x1F) & ~0x1F, offset, _fsReadEndFunc, 2);
    return size;
}

unsigned int CDVD_getattrfromhandle(int handle, int unused, unsigned int *pSize)
{
    DVDFileInfo *pFileInfo = &Cdinfo.mpFiles[handle - 1];

    if (pSize) {
        *pSize = pFileInfo->length;
    }
    return pFileInfo->length;
}
