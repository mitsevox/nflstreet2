#include "engine/cu_801CB5D4.h"

extern MCFile_801CB5D4 lbl_80381C40;
extern unsigned char lbl_803DD600[];

int fn_80255D04(int chan);
int fn_802565A0(int chan, void *workArea, CARDCallback_801CB5D4 detachCallback);
int fn_80257388(int chan, int fileNo, CARDFileInfo_801CB5D4 *fileInfo);
int fn_8025748C(CARDFileInfo_801CB5D4 *fileInfo);
void fn_801F7BD4(int error);
void fn_801F8758(int a);
void fn_801F8768(void);
int fn_801C2FE4(const char *pString1, const char *pString2);
void *fn_801C1F94();
void *fn_801C1FBC();

int fn_801CBBAC(void);

static int fn_801CB5D4(void)
{
    if (CARDRead(&lbl_80381C40.mFileInfo, lbl_80381C40.mBuffer, 0x2000, lbl_80381C40.mSector) != 0) {
        return -1;
    }
    return 0;
}

void fn_801CB61C(void)
{
    CARDInit();
    lbl_80381C40.mChan = -1;
}

void fn_801CB648(void)
{
}

int fn_801CB64C(int device)
{
    int port = -1;

    switch (device) {
    case 2:
        port = 0;
        break;
    case 3:
        port = 1;
        break;
    }
    return port;
}

int fn_801CB678(unsigned int device)
{
    int slot = -1;

    switch (device) {
    case 2:
    case 3:
        slot = 0;
        break;
    }
    return slot;
}

int fn_801CB698(int chan, int unused, const char *pName, int unused2, int create, unsigned int size)
{
    CARDStat_801CB5D4 stat;
    int bytesFree = 0;
    int filesFree = 0;
    int fileNo;
    int result;

    fileNo = -1;
    if (fn_80255D04(chan)) {
        result = fn_802565A0(chan, lbl_803DD600, 0);
        if (result == 0 || result == -6) {
            result = CARDCheck(chan);
        }
        if (result == 0) {
            if (create) {
                CARDDelete(chan, pName);
                if (CARDCreate(chan, pName, (size + 0x1FFF) & ~0x1FFF, &lbl_80381C40.mFileInfo) == 0) {
                    fn_801F8758(0);
                    fileNo = lbl_80381C40.mFileInfo.fileNo;
                    CARDGetStatus(chan, fileNo, &lbl_80381C40.mStat);
                    lbl_80381C40.mStat.bannerFormat &= ~7;
                    lbl_80381C40.mStat.iconFormat = (lbl_80381C40.mStat.iconFormat & ~3) | 2;
                    lbl_80381C40.mStat.iconSpeed = (lbl_80381C40.mStat.iconSpeed & ~3) | 3;
                    lbl_80381C40.mStat.iconSpeed &= ~0xC;
                    lbl_80381C40.mStat.iconAddr = 0x40;
                    lbl_80381C40.mChan = chan;
                    lbl_80381C40.mDirty = 0;
                    lbl_80381C40.mStat.commentAddr = 0;
                    lbl_80381C40.mSector = 0;
                    lbl_80381C40.mPos = 0;
                    fn_801C1F94(lbl_80381C40.mBuffer, 0, 0x2000);
                }
            } else {
                if (CARDFreeBlocks(chan, &bytesFree, &filesFree) == 0) {
                    for (fileNo = 0; fileNo < 127; fileNo++) {
                        if (CARDGetStatus(chan, fileNo, &stat) == 0 && fn_801C2FE4(stat.fileName, pName) == 0) {
                            break;
                        }
                    }
                }
                if (fileNo < 127) {
                    if (fn_80257388(chan, fileNo, &lbl_80381C40.mFileInfo) == 0) {
                        fn_801F8758(0);
                        fileNo = lbl_80381C40.mFileInfo.fileNo;
                        CARDGetStatus(chan, fileNo, &lbl_80381C40.mStat);
                        lbl_80381C40.mChan = chan;
                        lbl_80381C40.mDirty = 0;
                        lbl_80381C40.mSector = 0;
                        lbl_80381C40.mPos = 0;
                        fn_801C1F94(lbl_80381C40.mBuffer, 0, 0x2000);
                    }
                }
            }
        } else if (result == -6 || result == -13) {
            CARDUnmount(chan);
        }
    }
    return fileNo;
}

void fn_801CB8C8(int fileNo)
{
    fn_801CBBAC();
    CARDSetStatus(lbl_80381C40.mChan, fileNo, &lbl_80381C40.mStat);
    fn_8025748C(&lbl_80381C40.mFileInfo);
    CARDUnmount(lbl_80381C40.mChan);
    lbl_80381C40.mChan = -1;
    fn_801F8758(1);
}

int fn_801CB92C(int fileNo, unsigned int offset, int whence)
{
    MCFile_801CB5D4 *pFile;
    int result = 0;
    int error = 0;

    if (fn_801CBBAC()) {
        fn_801F7BD4(0xA0008);
        return -1;
    }
    pFile = &lbl_80381C40;
    switch (whence) {
    case 0:
        pFile->mPos = offset;
        break;
    case 1:
        pFile->mPos += offset;
        break;
    case 2:
        pFile->mPos = pFile->mStat.length - offset;
        break;
    }
    if (lbl_80381C40.mPos > lbl_80381C40.mStat.length) {
        lbl_80381C40.mPos = lbl_80381C40.mStat.length;
        error = 0xA0004;
        result = -1;
    }
    lbl_80381C40.mSector = lbl_80381C40.mPos & ~0x1FFF;
    fn_801F7BD4(error);
    return result;
}

unsigned int fn_801CBA0C(int fileNo, unsigned char *pDst, unsigned int size)
{
    unsigned int total = 0;
    unsigned int offset;
    unsigned int count;

    while (size) {
        if (fn_801CB5D4()) {
            return 0;
        }
        offset = lbl_80381C40.mPos - lbl_80381C40.mSector;
        count = 0x2000 - offset;
        if (count > size) {
            count = size;
        }
        fn_801C1FBC(pDst, lbl_80381C40.mBuffer + offset, count);
        total += count;
        size -= count;
        pDst += count;
        lbl_80381C40.mPos += count;
        if (!(lbl_80381C40.mPos & 0x1FFF)) {
            lbl_80381C40.mSector += 0x2000;
            if (lbl_80381C40.mSector >= lbl_80381C40.mStat.length) {
                size = 0;
            }
        }
        fn_801F8768();
    }
    return total;
}

unsigned int fn_801CBAD8(int fileNo, unsigned char *pSrc, unsigned int size)
{
    unsigned int total = 0;
    unsigned int offset;
    unsigned int count;

    while (size) {
        if (!lbl_80381C40.mDirty) {
            if (fn_801CB5D4()) {
                return 0;
            }
        }
        offset = lbl_80381C40.mPos - lbl_80381C40.mSector;
        count = 0x2000 - offset;
        if (count > size) {
            count = size;
        }
        fn_801C1FBC(lbl_80381C40.mBuffer + offset, pSrc, count);
        total += count;
        size -= count;
        pSrc += count;
        lbl_80381C40.mDirty = 1;
        lbl_80381C40.mPos += count;
        if (!(lbl_80381C40.mPos & 0x1FFF)) {
            if (fn_801CBBAC()) {
                return 0;
            }
        }
        fn_801F8768();
    }
    return total;
}

int fn_801CBBAC(void)
{
    int result;

    if (lbl_80381C40.mDirty) {
        result = CARDWrite(&lbl_80381C40.mFileInfo, lbl_80381C40.mBuffer, 0x2000, lbl_80381C40.mSector);
        if (result != 0) {
            return -1;
        }
        lbl_80381C40.mDirty = result;
        lbl_80381C40.mSector += 0x2000;
    }
    return 0;
}
