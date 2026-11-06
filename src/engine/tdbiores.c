/* T3DB I/O devices backed by game resources: one reads a database stored in a resource (or
   rewrites it in place), the other only writes a database out to a resource. */

#include <string.h>
#include "engine/tdbiores.h"
#include "engine/Resource.h"
#include "game/fn_801D2B7C.h"
#include "engine/fn_801F7BD4.h"

typedef struct TDbIOResRef_t {
    void *mpArchive;
    int mId;
} TDbIOResRef_t;

typedef struct TDbIOResFile_t {
    TDbIOResRef_t mDesc;
    unsigned int mSize;
    unsigned char *mpWriteBuf;
    unsigned char *mpReadData;
    unsigned int mPos;
    int mState;
} TDbIOResFile_t;

typedef struct TDbIOResWriteRef_t {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
} TDbIOResWriteRef_t;

typedef struct TDbIOResWriteFile_t {
    TDbIOResWriteRef_t mDesc;
    unsigned int mSize;
    unsigned char *mpData;
    unsigned int mPos;
    int mState;
} TDbIOResWriteFile_t;

extern int fn_801EF92C(void *pArchive, int id, void *pData);
extern int fn_801F1B44(int a, int b, void *pData, unsigned int size, int e);

static void _EnterReadState(TDbIOResFile_t *pFile);
static void _EnterWriteState(TDbIOResFile_t *pFile);

static int _IORes_Open(void *pHandle, unsigned int expectedSize, void *pName, int bAnySize)
{
    TDbIOResFile_t *pFile = pHandle;
    TDbIOResRef_t *pDesc = pName;
    unsigned int size;

    if (pFile == 0 || pDesc == 0) {
        return 3;
    }
    size = fn_801F0C50(pDesc->mpArchive, pDesc->mId);
    if (fn_801F7C88() != 0 || (bAnySize == 0 && size != expectedSize)) {
        return 0x24;
    }
    pFile->mDesc = *pDesc;
    pFile->mSize = size;
    pFile->mpWriteBuf = 0;
    pFile->mPos = 0;
    pFile->mState = 0;
    return 0;
}

static int _IORes_Close(void *pHandle)
{
    TDbIOResFile_t *pFile = pHandle;
    int err = 0;

    if (pFile == 0) {
        return 3;
    }
    if (pFile->mState == 1) {
        fn_801F010C(pFile->mDesc.mpArchive, pFile->mDesc.mId);
    } else if (pFile->mState == 2 && pFile->mpWriteBuf != 0) {
        if (fn_801EF92C(pFile->mDesc.mpArchive, pFile->mDesc.mId, pFile->mpWriteBuf) != 0) {
            err = 0x24;
        }
        fn_801D2BD0(pFile->mpWriteBuf);
        pFile->mpWriteBuf = 0;
    }
    pFile->mState = 3;
    return err;
}

static int _IORes_Write(void *pHandle, void *pSrc, unsigned int size, unsigned int *pWritten)
{
    TDbIOResFile_t *pFile = pHandle;
    if (pWritten != 0) {
        *pWritten = 0;
    }
    if (pFile == 0 || pSrc == 0) {
        return 3;
    }
    if (pFile->mState == 0) {
        _EnterWriteState(pFile);
    } else if (pFile->mState == 1) {
        pFile->mState = 3;
    }
    if (pFile->mState == 3) {
        return 0x24;
    }
    if (pFile->mPos + size > pFile->mSize) {
        return 3;
    }
    memcpy(pFile->mpWriteBuf + pFile->mPos, pSrc, size);
    pFile->mPos += size;
    if (pWritten != 0) {
        *pWritten = size;
    }
    return 0;
}

static int _IORes_Read(void *pHandle, void *pDst, unsigned int size, unsigned int *pRead)
{
    TDbIOResFile_t *pFile = pHandle;
    if (pRead != 0) {
        *pRead = 0;
    }
    if (pFile == 0 || pDst == 0) {
        return 3;
    }
    if (pFile->mState == 0) {
        _EnterReadState(pFile);
    } else if (pFile->mState == 2) {
        pFile->mState = 3;
    }
    if (pFile->mState == 3) {
        return 0x24;
    }
    if (pFile->mPos + size > pFile->mSize) {
        return 3;
    }
    memcpy(pDst, pFile->mpReadData + pFile->mPos, size);
    pFile->mPos += size;
    if (pRead != 0) {
        *pRead = size;
    }
    return 0;
}

static int _IORes_Seek(void *pHandle, int offset)
{
    TDbIOResFile_t *pFile = pHandle;
    if (pFile == 0) {
        return 3;
    }
    pFile->mPos += offset;
    return 0;
}

static unsigned int _IORes_CalcPadding(unsigned int size)
{
    return 0;
}

static void _EnterReadState(TDbIOResFile_t *pFile)
{
    if (pFile != 0) {
        pFile->mpReadData = (unsigned char *)fn_801EF390(pFile->mDesc.mpArchive, pFile->mDesc.mId, 1);
        pFile->mPos = 0;
        pFile->mState = pFile->mpReadData != 0 ? 1 : 3;
    }
}

static void _EnterWriteState(TDbIOResFile_t *pFile)
{
    if (pFile != 0) {
        pFile->mpWriteBuf = fn_801D2BB0(1, pFile->mSize, 0, 0);
        pFile->mPos = 0;
        if (pFile->mpWriteBuf != 0) {
            memset(pFile->mpWriteBuf, 0, pFile->mSize);
            pFile->mState = 2;
        } else {
            pFile->mState = 3;
        }
    }
}

static int _IOWrite_Open(void *pHandle, unsigned int size, void *pName, int mode)
{
    TDbIOResWriteFile_t *pFile = pHandle;
    TDbIOResWriteRef_t *pDesc = pName;
    int err = 0;

    if (pFile == 0 || pDesc == 0 || mode != 0) {
        return 3;
    }
    pFile->mDesc = *pDesc;
    pFile->mSize = size;
    pFile->mpData = 0;
    pFile->mPos = 0;
    pFile->mpData = fn_801D2BB0(1, size, 0, 0);
    if (pFile->mpData != 0) {
        memset(pFile->mpData, 0, pFile->mSize);
        pFile->mState = 2;
    } else {
        pFile->mState = 3;
        err = 0x24;
    }
    return err;
}

static int _IOWrite_Close(void *pHandle)
{
    TDbIOResWriteFile_t *pFile = pHandle;
    int err = 0;

    if (pFile == 0 || pFile->mpData == 0 || pFile->mState != 2) {
        return 3;
    }
    if (fn_801F1B44(pFile->mDesc.mUnknown00, pFile->mDesc.mUnknown08, pFile->mpData, pFile->mSize, pFile->mDesc.mUnknown04) == 0 && pFile->mSize != 0) {
        err = 0x24;
    }
    fn_801D2BD0(pFile->mpData);
    pFile->mpData = 0;
    pFile->mState = 3;
    return err;
}

static int _IOWrite_Write(void *pHandle, void *pSrc, unsigned int size, unsigned int *pWritten)
{
    TDbIOResWriteFile_t *pFile = pHandle;
    if (pWritten != 0) {
        *pWritten = 0;
    }
    if (pFile == 0 || pSrc == 0) {
        return 3;
    }
    if (pFile->mState == 3) {
        return 0x24;
    }
    if (pFile->mPos + size > pFile->mSize) {
        return 3;
    }
    memcpy(pFile->mpData + pFile->mPos, pSrc, size);
    pFile->mPos += size;
    if (pWritten != 0) {
        *pWritten = size;
    }
    return 0;
}

static int _IOWrite_Read(void *pHandle, void *pData, unsigned int size, unsigned int *pDone)
{
    return 0x24;
}

TDbIODevice_t tdbioresCallback = {
    _IORes_Open,
    _IORes_Close,
    _IORes_Read,
    _IORes_Write,
    _IORes_Seek,
    _IORes_CalcPadding,
    0x1C
};

TDbIODevice_t tdbioreswriteCallback = {
    _IOWrite_Open,
    _IOWrite_Close,
    _IOWrite_Read,
    _IOWrite_Write,
    _IORes_Seek,
    _IORes_CalcPadding,
    0x1C
};
