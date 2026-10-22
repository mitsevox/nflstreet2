#include "game/fn_801D2B7C.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801EF390.h"

typedef struct ResDesc_8020D534 {
    void *mpArchive;
    int mId;
} ResDesc_8020D534;

typedef struct ResFile_8020D534 {
    ResDesc_8020D534 mDesc;
    unsigned int mSize;
    unsigned char *mpWriteBuf;
    unsigned char *mpReadData;
    unsigned int mPos;
    int mState;
} ResFile_8020D534;

typedef struct ResMemDesc_8020D924 {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
} ResMemDesc_8020D924;

typedef struct ResMemFile_8020D924 {
    ResMemDesc_8020D924 mDesc;
    unsigned int mSize;
    unsigned char *mpData;
    unsigned int mPos;
    int mState;
} ResMemFile_8020D924;

extern unsigned int fn_801F0C50(void *pArchive, int id);
extern int fn_801EF92C(void *pArchive, int id, void *pData);
extern int fn_801F1B44(int a, int b, void *pData, unsigned int size, int e);

void fn_8020D858(ResFile_8020D534 *pFile);
void fn_8020D8B4(ResFile_8020D534 *pFile);

int fn_8020D534(ResFile_8020D534 *pFile, unsigned int expectedSize, ResDesc_8020D534 *pDesc, int bAnySize)
{
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

int fn_8020D5D8(ResFile_8020D534 *pFile)
{
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

int fn_8020D674(ResFile_8020D534 *pFile, void *pSrc, unsigned int size, unsigned int *pWritten)
{
    if (pWritten != 0) {
        *pWritten = 0;
    }
    if (pFile == 0 || pSrc == 0) {
        return 3;
    }
    if (pFile->mState == 0) {
        fn_8020D8B4(pFile);
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

int fn_8020D750(ResFile_8020D534 *pFile, void *pDst, unsigned int size, unsigned int *pRead)
{
    if (pRead != 0) {
        *pRead = 0;
    }
    if (pFile == 0 || pDst == 0) {
        return 3;
    }
    if (pFile->mState == 0) {
        fn_8020D858(pFile);
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

int fn_8020D82C(ResFile_8020D534 *pFile, int offset)
{
    if (pFile == 0) {
        return 3;
    }
    pFile->mPos += offset;
    return 0;
}

int fn_8020D850(void)
{
    return 0;
}

void fn_8020D858(ResFile_8020D534 *pFile)
{
    if (pFile != 0) {
        pFile->mpReadData = (unsigned char *)fn_801EF390(pFile->mDesc.mpArchive, pFile->mDesc.mId, 1);
        pFile->mPos = 0;
        pFile->mState = pFile->mpReadData != 0 ? 1 : 3;
    }
}

void fn_8020D8B4(ResFile_8020D534 *pFile)
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

int fn_8020D924(ResMemFile_8020D924 *pFile, unsigned int size, ResMemDesc_8020D924 *pDesc, void *pExtra)
{
    int err = 0;

    if (pFile == 0 || pDesc == 0 || pExtra != 0) {
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

int fn_8020D9D8(ResMemFile_8020D924 *pFile)
{
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

int fn_8020DA70(ResMemFile_8020D924 *pFile, void *pSrc, unsigned int size, unsigned int *pWritten)
{
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

int fn_8020DB2C(void)
{
    return 0x24;
}
