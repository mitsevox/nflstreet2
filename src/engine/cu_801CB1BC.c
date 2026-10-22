/* Disc file client: up to N open files, one asynchronous read in flight at a time. */

#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSSemaphore.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/dvd.h>
#include "game/fn_801D2B7C.h"
#include "engine/cu_801C1F54.h"

typedef struct FsClient_801CB1BC {
    int mNumFiles;
    void (*mpReadDone)(int);
    DVDFileInfo *mpFiles;
    DVDFileInfo *mpReadFile;
    void *mpReadDst;
    int mReadOffset;
    int mReadSize;
} FsClient_801CB1BC;

extern FsClient_801CB1BC lbl_803D55E0;
extern unsigned char lbl_803D5600[];
extern int lbl_803EBC34;
extern OSThread lbl_8037F8C0;
extern unsigned char lbl_8037FC00[0x2000];
extern OSSemaphore lbl_80381C00;
extern OSSemaphore lbl_80381C0C;

int fn_801D34D0(void *pDest, int size, int value, int width);
void *fn_801C1FBC();

static DVDFileInfo *fn_801CB1BC(void)
{
    int i;

    for (i = 0; i < lbl_803D55E0.mNumFiles && lbl_803D55E0.mpFiles[i].length != 0; i++) {
    }
    if (i < lbl_803D55E0.mNumFiles) {
        return &lbl_803D55E0.mpFiles[i];
    }
    return 0;
}

static void fn_801CB240(s32 result, DVDFileInfo *pFileInfo)
{
    if (result >= 0) {
        OSSignalSemaphore(&lbl_80381C0C);
    }
}

static void *fn_801CB270(void *pParam)
{
    for (;;) {
        OSWaitSemaphore(&lbl_80381C0C);
        fn_801C1FBC(lbl_803D55E0.mpReadDst, lbl_803D5600, lbl_803D55E0.mReadSize);
        DCFlushRange(lbl_803D55E0.mpReadDst, lbl_803D55E0.mReadSize);
        OSSignalSemaphore(&lbl_80381C00);
        if (lbl_803D55E0.mpReadDone) {
            lbl_803D55E0.mpReadDone(1);
        }
    }
}

int fn_801CB2E0(int unused, int numFiles, int unused2, void (*pReadDone)(int))
{
    int size = numFiles * sizeof(DVDFileInfo);
    DVDFileInfo *pFiles;

    pFiles = fn_801D2BB0(1, size, lbl_803EBC34, 0);
    fn_801D34D0(&lbl_803D55E0, sizeof(FsClient_801CB1BC), 0, 4);
    lbl_803D55E0.mpFiles = pFiles;
    fn_801D34D0(pFiles, size, 0, 4);
    lbl_803D55E0.mNumFiles = numFiles;
    OSInitSemaphore(&lbl_80381C0C, 10);
    OSInitSemaphore(&lbl_80381C00, 10);
    if (OSCreateThread(&lbl_8037F8C0, fn_801CB270, 0, lbl_8037FC00 + sizeof(lbl_8037FC00), 0x2000, 12, 1)) {
        OSResumeThread(&lbl_8037F8C0);
    }
    lbl_803D55E0.mpReadDone = pReadDone;
    OSSignalSemaphore(&lbl_80381C00);
    return lbl_803D55E0.mNumFiles;
}

int fn_801CB3D0(const char *pName, int unused, int *pHandle)
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
            *pOut = fn_801C1F54(*pName);
        }
    }
    *pOut = 0;
    pFileInfo = fn_801CB1BC();
    if (pFileInfo) {
        *pHandle = pFileInfo - lbl_803D55E0.mpFiles + 1;
        DVDOpen(path, pFileInfo);
        result = 1;
    } else {
        *pHandle = 0;
        result = 0;
    }
    return result;
}

int fn_801CB4A0(int handle)
{
    DVDFileInfo *pFileInfo = &lbl_803D55E0.mpFiles[handle - 1];

    DVDClose(pFileInfo);
    pFileInfo->length = 0;
    return 0;
}

int fn_801CB4EC(int handle, void *pDst, int offset, int size)
{
    DVDFileInfo *pFileInfo = &lbl_803D55E0.mpFiles[handle - 1];

    if (size > (int)(pFileInfo->length - offset) || size <= 0 || offset < 0) {
        size = pFileInfo->length - offset;
    }
    OSWaitSemaphore(&lbl_80381C00);
    lbl_803D55E0.mpReadDst = pDst;
    lbl_803D55E0.mpReadFile = pFileInfo;
    lbl_803D55E0.mReadOffset = offset;
    lbl_803D55E0.mReadSize = size;
    DVDReadAsyncPrio(pFileInfo, lbl_803D5600, (size + 0x1F) & ~0x1F, offset, fn_801CB240, 2);
    return size;
}

unsigned int fn_801CB5A8(int handle, int unused, unsigned int *pSize)
{
    DVDFileInfo *pFileInfo = &lbl_803D55E0.mpFiles[handle - 1];

    if (pSize) {
        *pSize = pFileInfo->length;
    }
    return pFileInfo->length;
}
