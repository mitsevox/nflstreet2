#include <dolphin/gx/GXStruct.h>
#include "engine/cu_801C665C.h"
#include "engine/cu_801C8F14.h"
#include "engine/cu_801CCA64.h"

/* Text position handed to the font renderer as a float vector. */
typedef struct FontPos_801C9DD8 {
    float x;
    float y;
    float z;
} FontPos_801C9DD8;
#include "game/fn_801C68FC.h"

extern FileEntry_801C8F14 *lbl_803EBC24;
extern unsigned char *lbl_803EBC28;
extern int lbl_803EBC34;
extern FileAsync_801C8F14 *lbl_803EBC3C;
extern unsigned char lbl_803EBC40;
extern unsigned char lbl_803EBC41;
extern unsigned char lbl_803EBC42;
extern const char *lbl_803EBC44;
extern void *lbl_803ED62C;
extern int lbl_803ECEE8;
extern int lbl_803ECEF4;
extern Font_801CCA64 *lbl_803ECEF8;
extern unsigned char lbl_803D5188[];
extern FileConfig_801C8F14 lbl_803D51A8;
extern unsigned char lbl_803D55C0[];
extern FontColor_801CCA64 lbl_802F4A74;
extern unsigned char lbl_802F4AC0[];

void fn_801F8014(void *pMutex);
void fn_801F809C(void *pMutex);
void fn_801F7BD4(int error);
int fn_801F7C88(void);
void fn_801F8768(void);
int fn_801F7ABC(void);
void fn_801F7AD4(int level);
void *fn_801D2BB0(int heap, int size, int flags, int a);
void fn_801D2BD0(void *p);
char *fn_801C2EB4(char *pDest, const char *pSource);
int fn_801C3180(const char *pString);
void fn_801C92B8(char *pDst, const char *pPath, const char *pName, int flags);
FileDevTable_801C8F14 *fn_801C9D64(void);
int fn_801CB2E0(int unused, int numFiles, int unused2, void (*pReadDone)(int));
int fn_801CB3D0(const char *pName, int unused, int *pHandle);
int fn_801CB4A0(int handle);
int fn_801CB4EC(int handle, void *pDst, int offset, int size);
unsigned int fn_801CB5A8(int handle, int unused, unsigned int *pSize);
void fn_801CB61C(void);
void fn_801CB648(void);
int fn_801CB64C(int device);
int fn_801CB678(unsigned int device);
int fn_801CB698(int chan, int unused, const char *pName, int unused2, int create, unsigned int size);
void fn_801CB8C8(int fileNo);
int fn_801CB92C(int fileNo, unsigned int offset, int whence);
unsigned int fn_801CBA0C(int fileNo, unsigned char *pDst, unsigned int size);
unsigned int fn_801CBAD8(int fileNo, unsigned char *pSrc, unsigned int size);
void fn_801CBC1C(int count);
void fn_801CBC20(void);
int fn_801CBC24(const char *pName, int mode);
void fn_801CBC2C(int handle);
int fn_801CBC30(int handle, void *pDst, int size);
int fn_801CBC38(int handle, const void *pSrc, int size);
int fn_801CBC40(int handle, int offset, int whence);
int fn_801CBC48(int handle);
void fn_801CEA7C(unsigned char clear);
void fn_801CE908(unsigned char enable);
void fn_801CE2B8(int enable);
void fn_801CE82C(void);
void fn_801D0470(unsigned int index);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0D94(float x, float y, float z);
int fn_80228668(void);
int fn_8024151C(void);
void fn_8024E450(void);
void fn_802476F8(int a, int b);
void fn_8024A9EC(float (*pMtx)[4]);
void fn_802523A4(float (*pMtx)[4], int a);
void fn_8025251C(float (*pMtx)[4], int a);
void fn_8025256C(float (*pMtx)[4], int a);
void fn_802525BC(int a);
void fn_802525F0(float (*pMtx)[4], int a, int b);
void fn_8025278C(float x, float y, float w, float h, float n, float f);
void fn_8024EB6C(int a);
void fn_8024EB28(int a);
void fn_802527F8(int x, int y, int w, int h);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_8024FA68(int a, GXColor color);
void fn_8024FB58(int a, GXColor color);
void fn_8024D418(void);
void fn_8024CB90(int a, int b);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DF64(int a);
void fn_80251CC4(int a);

int fn_801CA180(int devType);
int fn_801CA530(int handle, int pos, void *pBuffer, int size);
int fn_801CA648(int handle, int pos, void *pBuffer, int size);
int fn_801CA504(const char *pName);
static int fn_801CA528(const char *pName, int mode);
void fn_801CAB30(void);
void fn_801CAF24(void);

static int fn_801C9DD8(int device, const char *pName, int mode)
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
        if (!(handle = fn_801CBC24(pName, mode))) {
            error = 0xA0003;
        } else {
            size = fn_801CBC48(handle);
        }
        break;
    case 1:
        if (fn_801CB3D0(pName, 0, &handle) == 0) {
            error = 0xA0003;
        } else {
            fn_801CB5A8(handle, 0, &size);
        }
        break;
    case 2:
    case 3:
        port = fn_801CB64C(device);
        slot = fn_801CB678(device);
        if ((handle = fn_801CB698(port, slot, pName, mode, 0, 0)) < 0) {
            if ((handle = fn_801CB698(port, slot, pName, mode, 1, 0)) < 0) {
                error = fn_801F7C88();
            }
        }
        break;
    }
    if (size <= 0) {
        error = 0xA0003;
    }
    if (error == 0) {
        found = 0;
        for (i = 0; error == 0 && i < lbl_803D51A8.mNumFiles && !found; i++) {
            if (!lbl_803EBC24[i].mInUse) {
                if (!(pCopy = fn_801D2BB0(1, fn_801C3180(pName) + 1, lbl_803EBC34, 0))) {
                    error = fn_801F7C88();
                } else {
                    fn_801C2EB4(pCopy, pName);
                    lbl_803EBC24[i].mInUse = 1;
                    lbl_803EBC24[i].mPos = 0;
                    lbl_803EBC24[i].mDevHandle = handle;
                    lbl_803EBC24[i].mpName = pCopy;
                    lbl_803EBC24[i].mAsyncPos = 0;
                    found = 1;
                    lbl_803EBC24[i].mMode = mode;
                    lbl_803EBC24[i].mLength = size;
                    lbl_803EBC24[i].mDevType = device;
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
    fn_801F7BD4(error);
    return i;
}

static int fn_801CA020(FileAsync_801C8F14 *pAsync)
{
    int result = 0;
    int error = 0;
    int busy;

    switch (pAsync->mType) {
    case 1:
        busy = 1;
        if (lbl_803EBC24[pAsync->mHandle].mDevType == 1 || lbl_803EBC24[pAsync->mHandle].mDevType == 4) {
            busy = 0;
        }
        if (!busy) {
            lbl_803EBC24[pAsync->mHandle].mAsyncPos = pAsync->mPos;
            if (pAsync->mSize > lbl_803EBC24[pAsync->mHandle].mLength - pAsync->mPos) {
                pAsync->mSize = lbl_803EBC24[pAsync->mHandle].mLength - pAsync->mPos;
            }
            lbl_803EBC3C = pAsync;
            pAsync->mState = 1;
            if ((result = fn_801CA530(pAsync->mHandle, pAsync->mPos, pAsync->mpBuffer, pAsync->mSize)) < 0) {
                pAsync->mState = busy;
                if (!(error = fn_801F7C88())) {
                    error = 0xA0007;
                }
            }
        }
        break;
    case 2:
        lbl_803EBC24[pAsync->mHandle].mAsyncPos = pAsync->mPos;
        if ((result = fn_801CA648(pAsync->mHandle, pAsync->mPos, pAsync->mpBuffer, pAsync->mSize)) >= 0) {
            pAsync->mState = 1;
        } else if (!(error = fn_801F7C88())) {
            error = 0xA0008;
        }
        break;
    }
    fn_801F7BD4(error);
    return result;
}

int fn_801CA180(int devType)
{
    int found = 0;
    FileAsync_801C8F14 *pAsync;

    fn_801F8014(lbl_803D5188);
    for (pAsync = fn_801C6B4C(lbl_803ED62C, 0); pAsync; pAsync = fn_801C6C84(lbl_803ED62C, pAsync)) {
        if (lbl_803EBC24[pAsync->mHandle].mDevType == devType && pAsync->mState == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        fn_801CA020(pAsync);
    }
    fn_801F809C(lbl_803D5188);
    return found;
}

void fn_801CA224(FileAsync_801C8F14 *pAsync)
{
    int done = 1;
    int devType = lbl_803EBC24[pAsync->mHandle].mDevType;
    int busy;

    if (pAsync->mpStep) {
        done = pAsync->mpStep(pAsync->mSize, 0, pAsync->mpReq);
    }
    fn_801F8014(lbl_803D5188);
    if (done) {
        pAsync->mState = 2;
        pAsync->mpReq->mpAsync = 0;
        fn_801C6C0C(lbl_803ED62C, pAsync);
    } else {
        pAsync->mState = done;
    }
    busy = 0;
    for (pAsync = fn_801C6B4C(lbl_803ED62C, 0); pAsync; pAsync = fn_801C6C84(lbl_803ED62C, pAsync)) {
        if (pAsync->mState == 1) {
            busy = 1;
        }
    }
    if (!busy) {
        fn_801CA180(devType);
    }
    fn_801F809C(lbl_803D5188);
}

static void fn_801CA31C(int result)
{
    fn_801F8014(lbl_803D5188);
    lbl_803EBC40 = 1;
    fn_801CA224(lbl_803EBC3C);
    fn_801F809C(lbl_803D5188);
}

int fn_801CA364(const char *pName, int device, const char *pPrefix)
{
    int handle = 0;
    int error = 0;

    switch (device) {
    case 1:
    case 4: {
        char path[128] = "";

        fn_801C92B8(path, pPrefix, pName, device);
        handle = fn_801C9DD8(device, path, 0);
        if (handle < 0) {
            error = fn_801F7C88();
        }
        break;
    }
    case 2:
    case 3:
        handle = fn_801C9DD8(device, pName, 3);
        if (handle < 0) {
            error = fn_801F7C88();
        }
        break;
    case 0x2A:
        handle = fn_801CA504(pName);
        break;
    case 5:
    default:
        error = 0xA000A;
        break;
    }
    if (error) {
        handle = -1;
    }
    fn_801F7BD4(error);
    return handle;
}

int fn_801CA468(int handle)
{
    int error = 0;

    fn_801D2BD0(lbl_803EBC24[handle].mpName);
    lbl_803EBC24[handle].mInUse = 0;
    switch (lbl_803EBC24[handle].mDevType) {
    case 4:
        fn_801CBC2C(lbl_803EBC24[handle].mDevHandle);
        break;
    case 1:
        fn_801CB4A0(lbl_803EBC24[handle].mDevHandle);
        break;
    case 2:
        fn_801CB8C8(handle);
        break;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CA504(const char *pName)
{
    return fn_801CA528(pName, 4);
}

static int fn_801CA528(const char *pName, int mode)
{
    return 0;
}

int fn_801CA530(int handle, int pos, void *pBuffer, int size)
{
    int result = 0;
    int error = 0;

    switch (lbl_803EBC24[handle].mDevType) {
    case 1:
        lbl_803EBC40 = result;
        result = fn_801CB4EC(lbl_803EBC24[handle].mDevHandle, pBuffer, pos, size);
        if (result != size) {
            error = 0xA0007;
        }
        break;
    case 4:
        fn_801CBC40(lbl_803EBC24[handle].mDevHandle, pos, 0);
        if ((result = fn_801CBC30(lbl_803EBC24[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0007;
        } else {
            result = size;
        }
        break;
    case 2:
    case 3:
        fn_801CB92C(lbl_803EBC24[handle].mDevHandle, pos, 0);
        if ((result = fn_801CBA0C(lbl_803EBC24[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0007;
        }
        break;
    }
    if (error) {
        result = -1;
    }
    fn_801F7BD4(error);
    return result;
}

int fn_801CA648(int handle, int pos, void *pBuffer, int size)
{
    int result = 0;
    int error;

    fn_801F8014(lbl_803EBC28 + handle * 0x20);
    error = 0;
    switch (lbl_803EBC24[handle].mDevType) {
    case 1:
    case 4:
        fn_801CBC40(lbl_803EBC24[handle].mDevHandle, pos, 0);
        if ((result = fn_801CBC38(lbl_803EBC24[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0008;
        } else {
            result = size;
        }
        break;
    case 2:
    case 3:
        fn_801CB92C(lbl_803EBC24[handle].mDevHandle, pos, 0);
        if ((result = fn_801CBAD8(lbl_803EBC24[handle].mDevHandle, pBuffer, size)) < 0) {
            error = 0xA0008;
        }
        break;
    }
    fn_801F809C(lbl_803EBC28 + handle * 0x20);
    if (error) {
        result = -1;
    }
    fn_801F7BD4(error);
    return result;
}

int fn_801CA760(FileAsync_801C8F14 *pAsync)
{
    int busy = 0;
    FileAsync_801C8F14 *pNode;

    fn_801F8014(lbl_803D5188);
    fn_801F8014(lbl_803D55C0);
    fn_801C6AA4(lbl_803ED62C, pAsync, 0);
    for (pNode = fn_801C6B4C(lbl_803ED62C, 0); pNode; pNode = fn_801C6C84(lbl_803ED62C, pNode)) {
        if (pNode->mState == 1) {
            busy = 1;
            break;
        }
    }
    if (!busy) {
        lbl_803ECEE8 = lbl_803EBC24[pAsync->mHandle].mDevType;
        if (lbl_803ECEE8 != 4) {
            fn_801CA180(lbl_803ECEE8);
        }
    }
    fn_801F809C(lbl_803D55C0);
    fn_801F809C(lbl_803D5188);
    fn_801F7BD4(0);
    return 0;
}

void fn_801CA834(int handle)
{
    int busy;
    FileAsync_801C8F14 *pAsync;
    FileAsync_801C8F14 *pNext;

    do {
        fn_801F8768();
        busy = 0;
        fn_801CAB30();
        fn_801F8014(lbl_803D5188);
        for (pAsync = fn_801C6B4C(lbl_803ED62C, 0); pAsync; pAsync = pNext) {
            pNext = fn_801C6C84(lbl_803ED62C, pAsync);
            if (pAsync->mHandle == handle && pAsync->mState != 2) {
                busy = 1;
                break;
            }
        }
        if (busy) {
            fn_801CAF24();
        }
        fn_801F809C(lbl_803D5188);
    } while (busy);
}

void fn_801CA8D4(const char *pName)
{
    lbl_803EBC44 = pName;
}

static void fn_801CA8DC(FontPos_801C9DD8 *pPos, unsigned int status)
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

void fn_801CAB30(void)
{
    float mtx[3][4];
    FontPos_801C9DD8 pos = {0.0f, 0.0f, -0.4f};
    GXColor white = {255, 255, 255, 255};
    GXColor black = {0, 0, 0, 0};
    int status;
    int current;
    int level;

    status = fn_8024151C();
    if ((unsigned int)(status - 4) <= 2 || status == 11 || status == -1) {
        level = fn_801F7ABC();
        fn_8024E450();
        fn_802476F8(0, 2);
        fn_802476F8(1, 2);
        fn_802476F8(2, 2);
        fn_802476F8(3, 2);
        fn_8024A9EC(mtx);
        fn_802523A4(mtx, 0);
        fn_8025251C(mtx, 0);
        fn_8025256C(mtx, 0);
        fn_802525BC(0);
        fn_802525F0(mtx, 0x3C, 0);
        fn_8025278C(0.0f, 0.0f, 640.0f, 448.0f, 0.0f, 1.0f);
        fn_8024EB6C(0);
        fn_8024EB28(0);
        fn_802527F8(0, 0, 640, 448);
        fn_8024FC48(0);
        fn_8024FC84(4, 0, 0, 1, 0, 0, 2);
        fn_8024FA68(4, black);
        fn_8024FB58(4, white);
        fn_8024FC84(5, 0, 0, 1, 0, 0, 2);
        fn_8024FA68(5, black);
        fn_8024FB58(5, white);
        fn_8024D418();
        fn_8024CB90(9, 1);
        fn_8024CB90(11, 1);
        fn_8024CB90(13, 1);
        fn_8024D450(0, 9, 1, 4, 0);
        fn_8024D450(0, 11, 1, 5, 0);
        fn_8024D450(0, 13, 1, 4, 0);
        fn_8024DF64(0);
        fn_80251CC4(1);
        fn_801CEA7C(1);
        fn_801CE908(0);
        fn_801CE2B8(0);
        fn_801D0470(fn_80228668());
        fn_801D0508();
        fn_801D0D94(0.0014705883f, -0.002232143f, 1.0f);
        do {
            if (status != -1) {
                fn_801F8768();
            }
            current = fn_8024151C();
            fn_801CD2A4();
            fn_801CD308(0, lbl_802F4A74);
            fn_801CDD18();
            fn_801CA8DC(&pos, status);
            fn_801CE82C();
        } while (current == status);
        fn_801CD2A4();
        fn_801CD308(0, lbl_802F4A74);
        fn_801CDD18();
        pos.y = 0.0f;
        fn_801CDB5C(lbl_803ECEF8, "Loading...", 1, 0.0f, &pos.x);
        fn_801CE82C();
        fn_801D0544();
        fn_801F7AD4(level);
        fn_801CE908(1);
        fn_801CE2B8(1);
    }
}

void fn_801CAEC8(void)
{
    if (!lbl_803EBC42) {
        fn_801CCF74(0, 0, (FontHeader_801CCA64 *)lbl_802F4AC0);
        lbl_803ECEF8 = fn_801CD130(0);
        fn_801CD20C(lbl_803ECEF8, 0);
        lbl_803EBC42 = 1;
    }
}

void fn_801CAF24(void)
{
    FileAsync_801C8F14 *pFirst = 0;
    int found = 0;
    FileAsync_801C8F14 *pAsync;

    fn_801F8014(lbl_803D5188);
    for (pAsync = fn_801C6B4C(lbl_803ED62C, 0); pAsync; pAsync = fn_801C6C84(lbl_803ED62C, pAsync)) {
        if (pAsync->mState == 1) {
            if (lbl_803EBC24[pAsync->mHandle].mDevType == 4) {
                fn_801CA224(pAsync);
            }
            found = 1;
            break;
        }
        if (!pFirst) {
            pFirst = pAsync;
        }
    }
    if (!found && pFirst && pFirst->mState == 0 && lbl_803EBC24[pFirst->mHandle].mDevType == 4) {
        fn_801CA180(4);
    }
    fn_801F809C(lbl_803D5188);
}

void fn_801CB00C(FileConfig_801C8F14 *pConfig)
{
    FileDevTable_801C8F14 *pTable;
    FileDevList_801C8F14 *pList;
    int done = 0;
    int i;
    int j;

    lbl_803EBC41 = 1;
    pTable = fn_801C9D64();
    for (i = 0; i < pTable->mCount; i++) {
        pList = pTable->mpList[i];
        for (j = 0; j < pList->mCount; j++) {
            if (pList->mDevice[j] == 1) {
                done = 1;
                fn_801CB2E0(pConfig->mNumFiles, pConfig->mUnk400, lbl_803ECEF4, fn_801CA31C);
                lbl_803EBC41 = 0;
                break;
            }
        }
        if (done) {
            break;
        }
    }
    fn_801CB61C();
    if (lbl_803D51A8.mHostEnabled) {
        fn_801CBC1C(lbl_803D51A8.mNumFiles);
    }
}

void fn_801CB0EC(void)
{
    if (lbl_803D51A8.mHostEnabled) {
        fn_801CBC20();
    }
    fn_801CB648();
}

int fn_801CB120(void)
{
    fn_801F8768();
    fn_801CAB30();
    return lbl_803EBC41;
}

int fn_801CB148(int handle)
{
    int size;

    switch (lbl_803EBC24[handle].mDevType) {
    case 1:
        fn_801CB5A8(lbl_803EBC24[handle].mDevHandle, 0, &size);
        break;
    case 4:
        size = fn_801CBC48(lbl_803EBC24[handle].mDevHandle);
        break;
    }
    return size;
}

int fn_801CB1AC(void)
{
    return 0;
}

int fn_801CB1B4(void)
{
    return 0;
}
