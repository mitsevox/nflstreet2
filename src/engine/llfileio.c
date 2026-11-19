/* Low-level file I/O: opens files on the disc, memory card or host device, runs the queue of
   asynchronous reads and writes, and shows the Nintendo disc error screens (cover open, wrong
   disc, read error) until the drive recovers. */

#include <dolphin/gx/GXManage.h>
#include <dolphin/pad.h>
#include <dolphin/dvd.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXStruct.h>
#include "engine/list.h"
#include "engine/fileio.h"
#include "engine/Font.h"

/* Text position handed to the font renderer as a float vector. */
typedef struct FileFontPos_t {
    float x;
    float y;
    float z;
} FileFontPos_t;
#include "engine/dslist.h"
#include "engine/SysSetLastErrorFunc.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include <string.h>
#include "engine/llglib.h"
#include "engine/llmatrix.h"
#include "engine/viewport.h"

extern FileStreamInfo_t *File_StreamInfo;
extern Lock_801F8014 *File_HandleInUseCS;
extern int File_uMemFlags;
extern FileAsyncRequest_t *lbl_803EBC3C;
extern unsigned char lbl_803EBC40;
extern unsigned char lbl_803EBC41;
extern unsigned char lbl_803EBC42;
extern const char *lbl_803EBC44;
extern void *File_pAsyncRequestList;
extern int lbl_803ECEE8;
extern int lbl_803ECEF4;
extern Font_801CCA64 *lbl_803ECEF8;
extern Lock_801F8014 File_AsyncRequestListCS;
extern FileInitParms_t File_InitParms;
extern Lock_801F8014 File_AsyncThreadActiveCS;
extern FontColor_801CCA64 lbl_802F4A74;
extern unsigned char lbl_802F4AC0[];

void fn_801F8768(void);
int SysGetSystemTime(void);
void SysSetSystemTime(int level);
void FileCreateAbsoluteFileName(char *pDst, const char *pPath, const char *pName, int flags);
FilevDeviceList_t *FileGetDeviceList(void);
int CDVD_init(int unused, int numFiles, int unused2, void (*pReadDone)(int));
int CDVD_open(const char *pName, int unused, int *pHandle);
int CDVD_close(int handle);
int CDVD_read(int handle, void *pDst, int offset, int size);
unsigned int CDVD_getattrfromhandle(int handle, int unused, unsigned int *pSize);
void FileMCInit(void);
void FileMCShutdown(void);
int FileMCGetPort(int device);
int FileMCGetSlot(unsigned int device);
int FileMCOpen(int chan, int unused, const char *pName, int unused2, int create, unsigned int size);
void FileMCClose(int fileNo);
int FileMCSeek(int fileNo, unsigned int offset, int whence);
unsigned int FileMCRead(int fileNo, unsigned char *pDst, unsigned int size);
unsigned int FileMCWrite(int fileNo, unsigned char *pSrc, unsigned int size);
void FileHostInit(int count);
void FileHostShutdown(void);
int FileHostOpen(const char *pName, int mode);
void FileHostClose(int handle);
int FileHostRead(int handle, void *pDst, int size);
int FileHostWrite(int handle, const void *pSrc, int size);
int FileHostLSeek(int handle, int offset, int whence);
int FileHostGetSize(int handle);
void GlibSetClear(unsigned char clear);
void GlibSetVIInt(unsigned char enable);
void GlibSwapBuffers(void);
void PSMTXIdentity(float (*pMtx)[4]);
void GXSetProjection(float (*pMtx)[4], int type);

static int _FileStartIO(int devType);
int FilePerformRead(int handle, int pos, void *pBuffer, int size);
int FilePerformWrite(int handle, int pos, void *pBuffer, int size);
int FileOpenWriteStream(const char *pName);
static int _FileOpenWriteStream(const char *pName, int mode);
void FileAsyncCheckError(void);
void FileDebugProcess(void);

static int _FileOpenStream(int device, const char *pName, int mode)
{
    int handle;
    int size;
    int error = 0;
    int port;
    int slot;
    int i;
    int found;
    char *pCopy;

    i = 0;
    size = 0;
    switch (device) {
    case 4:
        if (!(handle = FileHostOpen(pName, mode))) {
            error = 0xA0003;
        } else {
            size = FileHostGetSize(handle);
        }
        break;
    case 1:
        if (CDVD_open(pName, 0, &handle) == 0) {
            error = 0xA0003;
        } else {
            CDVD_getattrfromhandle(handle, 0, &size);
        }
        break;
    case 2:
    case 3:
        port = FileMCGetPort(device);
        slot = FileMCGetSlot(device);
        if ((handle = FileMCOpen(port, slot, pName, mode, 0, 0)) < 0) {
            if ((handle = FileMCOpen(port, slot, pName, mode, 1, 0)) < 0) {
                error = SysGetLastError();
            }
        }
        break;
    }
    if (size <= 0) {
        error = 0xA0003;
    }
    if (error == 0) {
        found = 0;
        for (i = 0; error == 0 && i < File_InitParms.mNumFiles && !found; i++) {
            if (!File_StreamInfo[i].mInUse) {
                if (!(pCopy = fn_801D2BB0(1, strlen(pName) + 1, File_uMemFlags, 0))) {
                    error = SysGetLastError();
                } else {
                    strcpy(pCopy, pName);
                    // FAKEMATCH: field order found by compiling all 120 orders of the first five stores
                    File_StreamInfo[i].mInUse = 1;
                    File_StreamInfo[i].mDevHandle = handle;
                    File_StreamInfo[i].mAsyncPos = 0;
                    File_StreamInfo[i].mPos = 0;
                    File_StreamInfo[i].mpName = pCopy;
                    found = 1;
                    File_StreamInfo[i].mMode = mode;
                    File_StreamInfo[i].mLength = size;
                    File_StreamInfo[i].mDevType = device;
                }
            }
        }
        i--;
        if (!found) {
            error = 0xA0005;
        }
    }
    if (error) {
        i = -1;
    }
    SysSetLastErrorFunc(error);
    return i;
}

static int _FileStartAsyncRequest(FileAsyncRequest_t *pAsync)
{
    int result = 0;
    int error = 0;
    int busy;

    switch (pAsync->mType) {
    case 1:
        busy = 1;
        if (File_StreamInfo[pAsync->mHandle].mDevType == 1 || File_StreamInfo[pAsync->mHandle].mDevType == 4) {
            busy = 0;
        }
        if (!busy) {
            File_StreamInfo[pAsync->mHandle].mAsyncPos = pAsync->mPos;
            if (pAsync->mSize > File_StreamInfo[pAsync->mHandle].mLength - pAsync->mPos) {
                pAsync->mSize = File_StreamInfo[pAsync->mHandle].mLength - pAsync->mPos;
            }
            lbl_803EBC3C = pAsync;
            pAsync->mState = 1;
            if ((result = FilePerformRead(pAsync->mHandle, pAsync->mPos, pAsync->mpBuffer, pAsync->mSize)) < 0) {
                pAsync->mState = busy;
                if (!(error = SysGetLastError())) {
                    error = 0xA0007;
                }
            }
        }
        break;
    case 2:
        File_StreamInfo[pAsync->mHandle].mAsyncPos = pAsync->mPos;
        if ((result = FilePerformWrite(pAsync->mHandle, pAsync->mPos, pAsync->mpBuffer, pAsync->mSize)) >= 0) {
            pAsync->mState = 1;
        } else if (!(error = SysGetLastError())) {
            error = 0xA0008;
        }
        break;
    }
    SysSetLastErrorFunc(error);
    return result;
}

static int _FileStartIO(int devType)
{
    int found = 0;
    FileAsyncRequest_t *pAsync;

    fn_801F8014(&File_AsyncRequestListCS);
    for (pAsync = DSGetListNode(File_pAsyncRequestList, 0); pAsync; pAsync = DSNextListNode(File_pAsyncRequestList, pAsync)) {
        if (File_StreamInfo[pAsync->mHandle].mDevType == devType && pAsync->mState == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        _FileStartAsyncRequest(pAsync);
    }
    fn_801F809C(&File_AsyncRequestListCS);
    return found;
}

void _FileProcessRequestFinish(FileAsyncRequest_t *pAsync)
{
    int done = 1;
    int devType = File_StreamInfo[pAsync->mHandle].mDevType;
    int busy;

    if (pAsync->mpStep) {
        done = pAsync->mpStep(pAsync->mSize, 0, pAsync->mpReq);
    }
    fn_801F8014(&File_AsyncRequestListCS);
    if (done) {
        pAsync->mState = 2;
        pAsync->mpReq->mpAsync = 0;
        DSDelListNode(File_pAsyncRequestList, pAsync);
    } else {
        pAsync->mState = done;
    }
    busy = 0;
    for (pAsync = DSGetListNode(File_pAsyncRequestList, 0); pAsync; pAsync = DSNextListNode(File_pAsyncRequestList, pAsync)) {
        if (pAsync->mState == 1) {
            busy = 1;
        }
    }
    if (!busy) {
        _FileStartIO(devType);
    }
    fn_801F809C(&File_AsyncRequestListCS);
}

static void _FileCDVDCallback(int result)
{
    fn_801F8014(&File_AsyncRequestListCS);
    lbl_803EBC40 = 1;
    _FileProcessRequestFinish(lbl_803EBC3C);
    fn_801F809C(&File_AsyncRequestListCS);
}

int FileOpenhDevice(const char *pName, int device, const char *pPrefix)
{
    int handle = 0;
    int error = 0;

    switch (device) {
    case 1:
    case 4: {
        char path[128] = "";

        FileCreateAbsoluteFileName(path, pPrefix, pName, device);
        handle = _FileOpenStream(device, path, 0);
        if (handle < 0) {
            error = SysGetLastError();
        }
        break;
    }
    case 2:
    case 3:
        handle = _FileOpenStream(device, pName, 3);
        if (handle < 0) {
            error = SysGetLastError();
        }
        break;
    case 0x2A:
        handle = FileOpenWriteStream(pName);
        break;
    case 5:
    default:
        error = 0xA000A;
        break;
    }
    if (error) {
        handle = -1;
    }
    SysSetLastErrorFunc(error);
    return handle;
}

int FileCloseStream(int handle)
{
    int error = 0;

    fn_801D2BD0(File_StreamInfo[handle].mpName);
    File_StreamInfo[handle].mInUse = 0;
    switch (File_StreamInfo[handle].mDevType) {
    case 4:
        FileHostClose(File_StreamInfo[handle].mDevHandle);
        break;
    case 1:
        CDVD_close(File_StreamInfo[handle].mDevHandle);
        break;
    case 2:
        FileMCClose(handle);
        break;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FileOpenWriteStream(const char *pName)
{
    return _FileOpenWriteStream(pName, 4);
}

static int _FileOpenWriteStream(const char *pName, int mode)
{
    return 0;
}

int FilePerformRead(int handle, int pos, void *pBuffer, int size)
{
    int result = 0;
    int error = 0;

    switch (File_StreamInfo[handle].mDevType) {
    case 1:
        lbl_803EBC40 = 0;
        result = CDVD_read(File_StreamInfo[handle].mDevHandle, pBuffer, pos, size);
        if (result != size) {
            error = 0xA0007;
        }
        break;
    case 4:
        FileHostLSeek(File_StreamInfo[handle].mDevHandle, pos, 0);
        if ((result = FileHostRead(File_StreamInfo[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0007;
        } else {
            result = size;
        }
        break;
    case 2:
    case 3:
        FileMCSeek(File_StreamInfo[handle].mDevHandle, pos, 0);
        if ((result = FileMCRead(File_StreamInfo[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0007;
        }
        break;
    }
    if (error) {
        result = -1;
    }
    SysSetLastErrorFunc(error);
    return result;
}

int FilePerformWrite(int handle, int pos, void *pBuffer, int size)
{
    int result = 0;
    int error;

    fn_801F8014(&File_HandleInUseCS[handle]);
    error = 0;
    switch (File_StreamInfo[handle].mDevType) {
    case 1:
    case 4:
        FileHostLSeek(File_StreamInfo[handle].mDevHandle, pos, 0);
        if ((result = FileHostWrite(File_StreamInfo[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0008;
        } else {
            result = size;
        }
        break;
    case 2:
    case 3:
        FileMCSeek(File_StreamInfo[handle].mDevHandle, pos, 0);
        if ((result = FileMCWrite(File_StreamInfo[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0008;
        }
        break;
    }
    fn_801F809C(&File_HandleInUseCS[handle]);
    if (error) {
        result = -1;
    }
    SysSetLastErrorFunc(error);
    return result;
}

int FileQueueAsyncRequest(FileAsyncRequest_t *pAsync)
{
    int busy = 0;
    FileAsyncRequest_t *pNode;

    fn_801F8014(&File_AsyncRequestListCS);
    fn_801F8014(&File_AsyncThreadActiveCS);
    DSAddListNode(File_pAsyncRequestList, pAsync, 0);
    for (pNode = DSGetListNode(File_pAsyncRequestList, 0); pNode; pNode = DSNextListNode(File_pAsyncRequestList, pNode)) {
        if (pNode->mState == 1) {
            busy = 1;
            break;
        }
    }
    if (!busy) {
        lbl_803ECEE8 = File_StreamInfo[pAsync->mHandle].mDevType;
        if (lbl_803ECEE8 != 4) {
            _FileStartIO(lbl_803ECEE8);
        }
    }
    fn_801F809C(&File_AsyncThreadActiveCS);
    fn_801F809C(&File_AsyncRequestListCS);
    SysSetLastErrorFunc(0);
    return 0;
}

void FileAsyncWaitStream(int handle)
{
    int busy;
    FileAsyncRequest_t *pAsync;
    FileAsyncRequest_t *pNext;

    do {
        fn_801F8768();
        busy = 0;
        FileAsyncCheckError();
        fn_801F8014(&File_AsyncRequestListCS);
        for (pAsync = DSGetListNode(File_pAsyncRequestList, 0); pAsync; pAsync = pNext) {
            pNext = DSNextListNode(File_pAsyncRequestList, pAsync);
            if (pAsync->mHandle == handle && pAsync->mState != 2) {
                busy = 1;
                break;
            }
        }
        if (busy) {
            FileDebugProcess();
        }
        fn_801F809C(&File_AsyncRequestListCS);
    } while (busy);
}

void FileAsyncSetErrorGameName(const char *pName)
{
    lbl_803EBC44 = pName;
}

static void _FileDisplayErrorString(FileFontPos_t *pPos, unsigned int status)
{
    switch (status) {
    case 5:
        pPos->y = -40.0f;
        fn_801CDB5C(lbl_803ECEF8, "The Disc Cover is open.", 1, 0.0f, &pPos->x);
        pPos->y = 0.0f;
        fn_801CDB5C(lbl_803ECEF8, "If you want to continue the game,", 1, 0.0f, &pPos->x);
        pPos->y = 40.0f;
        fn_801CDB5C(lbl_803ECEF8, "please close the Disc Cover.", 1, 0.0f, &pPos->x);
        break;
    case 4:
    case 6:
        pPos->y = -40.0f;
        fn_801CDB5C(lbl_803ECEF8, "Please insert the", 1, 0.0f, &pPos->x);
        pPos->y = 0.0f;
        if (lbl_803EBC44) {
            fn_801CDB5C(lbl_803ECEF8, lbl_803EBC44, 1, 0.0f, &pPos->x);
        } else {
            fn_801CDB5C(lbl_803ECEF8, "appropriate", 1, 0.0f, &pPos->x);
        }
        pPos->y = 40.0f;
        fn_801CDB5C(lbl_803ECEF8, "Game Disc.", 1, 0.0f, &pPos->x);
        break;
    case 11:
        pPos->y = -40.0f;
        fn_801CDB5C(lbl_803ECEF8, "The Game Disc could not be read.", 1, 0.0f, &pPos->x);
        pPos->y = 0.0f;
        fn_801CDB5C(lbl_803ECEF8, "Please read the Nintendo GameCube\260", 1, 0.0f, &pPos->x);
        pPos->y = 40.0f;
        fn_801CDB5C(lbl_803ECEF8, "Instruction Booklet for more information.", 1, 0.0f, &pPos->x);
        break;
    case -1:
        pPos->y = -40.0f;
        fn_801CDB5C(lbl_803ECEF8, "An error has occurred.", 1, 0.0f, &pPos->x);
        pPos->y = 0.0f;
        fn_801CDB5C(lbl_803ECEF8, "Turn the power off and refer to the Nintendo GameCube\260", 1, 0.0f, &pPos->x);
        pPos->y = 40.0f;
        fn_801CDB5C(lbl_803ECEF8, "Instruction Booklet for further instructions.", 1, 0.0f, &pPos->x);
        break;
    }
}

void FileAsyncCheckError(void)
{
    float mtx[3][4];
    FileFontPos_t pos = {0.0f, 0.0f, -0.4f};
    GXColor white = {255, 255, 255, 255};
    GXColor black = {0, 0, 0, 0};
    int status;
    int current;
    int level;

    status = DVDGetDriveStatus();
    if ((unsigned int)(status - 4) <= 2 || status == 11 || status == -1) {
        level = SysGetSystemTime();
        GXDrawDone();
        PADControlMotor(0, 2);
        PADControlMotor(1, 2);
        PADControlMotor(2, 2);
        PADControlMotor(3, 2);
        PSMTXIdentity(mtx);
        GXSetProjection(mtx, 0);
        GXLoadPosMtxImm(mtx, 0);
        GXLoadNrmMtxImm(mtx, 0);
        GXSetCurrentMtx(0);
        GXLoadTexMtxImm(mtx, 0x3C, 0);
        GXSetViewport(0.0f, 0.0f, 640.0f, 448.0f, 0.0f, 1.0f);
        GXSetCoPlanar(0);
        GXSetCullMode(0);
        GXSetScissor(0, 0, 640, 448);
        GXSetNumChans(0);
        GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
        GXSetChanAmbColor(4, black);
        GXSetChanMatColor(4, white);
        GXSetChanCtrl(5, 0, 0, 1, 0, 0, 2);
        GXSetChanAmbColor(5, black);
        GXSetChanMatColor(5, white);
        GXClearVtxDesc();
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(11, 1);
        GXSetVtxDesc(13, 1);
        GXSetVtxAttrFmt(0, 9, 1, 4, 0);
        GXSetVtxAttrFmt(0, 11, 1, 5, 0);
        GXSetVtxAttrFmt(0, 13, 1, 4, 0);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GlibSetClear(1);
        GlibSetVIInt(0);
        GlibEnableVIRetraceCallback(0);
        MatSetStack(VptGetMatrixStack());
        MatPushUnit();
        MatScaleCol(0.0014705883f, -0.002232143f, 1.0f);
        do {
            if (status != -1) {
                fn_801F8768();
            }
            current = DVDGetDriveStatus();
            fn_801CD2A4();
            fn_801CD308(0, lbl_802F4A74);
            fn_801CDD18();
            _FileDisplayErrorString(&pos, status);
            GlibSwapBuffers();
        } while (current == status);
        fn_801CD2A4();
        fn_801CD308(0, lbl_802F4A74);
        fn_801CDD18();
        pos.y = 0.0f;
        fn_801CDB5C(lbl_803ECEF8, "Loading...", 1, 0.0f, &pos.x);
        GlibSwapBuffers();
        MatPop();
        SysSetSystemTime(level);
        GlibSetVIInt(1);
        GlibEnableVIRetraceCallback(1);
    }
}

void FileInitErrorMessages(void)
{
    if (!lbl_803EBC42) {
        fn_801CCF74(0, 0, (FontHeader_801CCA64 *)lbl_802F4AC0);
        lbl_803ECEF8 = fn_801CD130(0);
        fn_801CD20C(lbl_803ECEF8, 0);
        lbl_803EBC42 = 1;
    }
}

void FileDebugProcess(void)
{
    FileAsyncRequest_t *pFirst = 0;
    int found = 0;
    FileAsyncRequest_t *pAsync;

    fn_801F8014(&File_AsyncRequestListCS);
    for (pAsync = DSGetListNode(File_pAsyncRequestList, 0); pAsync; pAsync = DSNextListNode(File_pAsyncRequestList, pAsync)) {
        if (pAsync->mState == 1) {
            if (File_StreamInfo[pAsync->mHandle].mDevType == 4) {
                _FileProcessRequestFinish(pAsync);
            }
            found = 1;
            break;
        }
        if (!pFirst) {
            pFirst = pAsync;
        }
    }
    if (!found && pFirst && pFirst->mState == 0 && File_StreamInfo[pFirst->mHandle].mDevType == 4) {
        _FileStartIO(4);
    }
    fn_801F809C(&File_AsyncRequestListCS);
}

void FileLLInit(FileInitParms_t *pConfig)
{
    FilevDeviceList_t *pTable;
    FilevDevicePath_t *pList;
    int done = 0;
    int i;
    int j;

    lbl_803EBC41 = 1;
    pTable = FileGetDeviceList();
    for (i = 0; i < pTable->mCount; i++) {
        pList = pTable->mpList[i];
        for (j = 0; j < pList->mCount; j++) {
            if (pList->mDevice[j] == 1) {
                done = 1;
                CDVD_init(pConfig->mNumFiles, pConfig->mUnk400, lbl_803ECEF4, _FileCDVDCallback);
                lbl_803EBC41 = 0;
                break;
            }
        }
        if (done) {
            break;
        }
    }
    FileMCInit();
    if (File_InitParms.mHostEnabled) {
        FileHostInit(File_InitParms.mNumFiles);
    }
}

void FileLLShutdown(void)
{
    if (File_InitParms.mHostEnabled) {
        FileHostShutdown();
    }
    FileMCShutdown();
}

int FileHostCheckActive(void)
{
    fn_801F8768();
    FileAsyncCheckError();
    return lbl_803EBC41;
}

int FileGetSize(int handle)
{
    int size;

    switch (File_StreamInfo[handle].mDevType) {
    case 1:
        CDVD_getattrfromhandle(File_StreamInfo[handle].mDevHandle, 0, &size);
        break;
    case 4:
        size = FileHostGetSize(File_StreamInfo[handle].mDevHandle);
        break;
    }
    return size;
}

int FileCompareModificationTime(void)
{
    return 0;
}

int FileSetLength(void)
{
    return 0;
}
