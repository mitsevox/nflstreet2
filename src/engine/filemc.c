/* Memory-card file device of the low-level file layer: opens or creates one save file on a
   GameCube memory card and reads, writes and seeks it through one cached 8 KB sector. */

#include "engine/filemc.h"
#include "engine/SysSetLastErrorFunc.h"
#include <string.h>

unsigned char FileMCWorkArea[0xA000];
static FileMCInfo_t _FileMCCurrentInfo;

void fn_801F8758(int a);
void fn_801F8768(void);
void *memset();
void *memcpy();

int FileMCFlush(void);

static int _FileMCReadCurrentSector(void)
{
    if (CARDRead(&_FileMCCurrentInfo.mFileInfo, _FileMCCurrentInfo.mBuffer, 0x2000, _FileMCCurrentInfo.mSector) != 0) {
        return -1;
    }
    return 0;
}

void FileMCInit(void)
{
    CARDInit();
    _FileMCCurrentInfo.mChan = -1;
}

void FileMCShutdown(void)
{
}

int FileMCGetPort(int device)
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

int FileMCGetSlot(unsigned int device)
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

int FileMCOpen(int chan, int unused, const char *pName, int unused2, int create, unsigned int size)
{
    CARDStat stat;
    s32 filesFree = 0;
    s32 bytesFree = 0;
    int fileNo;
    int result;

    fileNo = -1;
    if (CARDProbe(chan)) {
        result = CARDMount(chan, FileMCWorkArea, 0);
        if (result == 0 || result == -6) {
            result = CARDCheck(chan);
        }
        if (result == 0) {
            if (create) {
                CARDDelete(chan, pName);
                result = CARDCreate(chan, pName, (size + 0x1FFF) & ~0x1FFF, &_FileMCCurrentInfo.mFileInfo);
                if (result == 0) {
                    fn_801F8758(0);
                    fileNo = CARDGetFileNo(&_FileMCCurrentInfo.mFileInfo);
                    result = CARDGetStatus(chan, fileNo, &_FileMCCurrentInfo.mStat);
                    // FAKEMATCH: setter order (as in memorycard.c) and the reset order mChan, mSector, mPos, mDirty chosen by testing
                    _FileMCCurrentInfo.mStat.commentAddr = 0;
                    _FileMCCurrentInfo.mStat.iconAddr = 0x40;
                    CARDSetIconFormat(&_FileMCCurrentInfo.mStat, 0, CARD_STAT_ICON_RGB5A3);
                    CARDSetIconSpeed(&_FileMCCurrentInfo.mStat, 0, CARD_STAT_SPEED_SLOW);
                    CARDSetIconSpeed(&_FileMCCurrentInfo.mStat, 1, CARD_STAT_SPEED_END);
                    CARDSetBannerFormat(&_FileMCCurrentInfo.mStat, CARD_STAT_BANNER_NONE);
                    CARDSetIconAnim(&_FileMCCurrentInfo.mStat, CARD_STAT_ANIM_LOOP);
                    _FileMCCurrentInfo.mChan = chan;
                    _FileMCCurrentInfo.mSector = 0;
                    _FileMCCurrentInfo.mPos = 0;
                    _FileMCCurrentInfo.mDirty = 0;
                    memset(_FileMCCurrentInfo.mBuffer, 0, 0x2000);
                }
            } else {
                if (CARDFreeBlocks(chan, &bytesFree, &filesFree) == 0) {
                    for (fileNo = 0; fileNo < 127; fileNo++) {
                        if (CARDGetStatus(chan, fileNo, &stat) == 0 && strcmp(stat.fileName, pName) == 0) {
                            break;
                        }
                    }
                }
                if (fileNo < 127) {
                    result = CARDFastOpen(chan, fileNo, &_FileMCCurrentInfo.mFileInfo);
                    if (result == 0) {
                        fn_801F8758(0);
                        fileNo = CARDGetFileNo(&_FileMCCurrentInfo.mFileInfo);
                        result = CARDGetStatus(chan, fileNo, &_FileMCCurrentInfo.mStat);
                        // FAKEMATCH: reset order mChan, mSector, mPos, mDirty chosen by testing
                        _FileMCCurrentInfo.mChan = chan;
                        _FileMCCurrentInfo.mSector = 0;
                        _FileMCCurrentInfo.mPos = 0;
                        _FileMCCurrentInfo.mDirty = 0;
                        memset(_FileMCCurrentInfo.mBuffer, 0, 0x2000);
                    }
                }
            }
        } else if (result == -6 || result == -13) {
            CARDUnmount(chan);
        }
    }
    return fileNo;
}

void FileMCClose(int fileNo)
{
    FileMCFlush();
    CARDSetStatus(_FileMCCurrentInfo.mChan, fileNo, &_FileMCCurrentInfo.mStat);
    CARDClose(&_FileMCCurrentInfo.mFileInfo);
    CARDUnmount(_FileMCCurrentInfo.mChan);
    _FileMCCurrentInfo.mChan = -1;
    fn_801F8758(1);
}

int FileMCSeek(int fileNo, unsigned int offset, int whence)
{
    FileMCInfo_t *pFile;
    int result = 0;
    int error = 0;

    if (FileMCFlush()) {
        SysSetLastErrorFunc(0xA0008);
        return -1;
    }
    pFile = &_FileMCCurrentInfo;
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
    if (_FileMCCurrentInfo.mPos > _FileMCCurrentInfo.mStat.length) {
        _FileMCCurrentInfo.mPos = _FileMCCurrentInfo.mStat.length;
        error = 0xA0004;
        result = -1;
    }
    _FileMCCurrentInfo.mSector = _FileMCCurrentInfo.mPos & ~0x1FFF;
    SysSetLastErrorFunc(error);
    return result;
}

unsigned int FileMCRead(int fileNo, unsigned char *pDst, unsigned int size)
{
    unsigned int total = 0;
    unsigned int offset;
    unsigned int count;

    while (size) {
        if (_FileMCReadCurrentSector()) {
            return 0;
        }
        offset = _FileMCCurrentInfo.mPos - _FileMCCurrentInfo.mSector;
        count = 0x2000 - offset;
        if (count > size) {
            count = size;
        }
        memcpy(pDst, _FileMCCurrentInfo.mBuffer + offset, count);
        total += count;
        size -= count;
        pDst += count;
        _FileMCCurrentInfo.mPos += count;
        if (!(_FileMCCurrentInfo.mPos & 0x1FFF)) {
            _FileMCCurrentInfo.mSector += 0x2000;
            if (_FileMCCurrentInfo.mSector >= _FileMCCurrentInfo.mStat.length) {
                size = 0;
            }
        }
        fn_801F8768();
    }
    return total;
}

unsigned int FileMCWrite(int fileNo, unsigned char *pSrc, unsigned int size)
{
    unsigned int total = 0;
    unsigned int offset;
    unsigned int count;

    while (size) {
        if (!_FileMCCurrentInfo.mDirty) {
            if (_FileMCReadCurrentSector()) {
                return 0;
            }
        }
        offset = _FileMCCurrentInfo.mPos - _FileMCCurrentInfo.mSector;
        count = 0x2000 - offset;
        if (count > size) {
            count = size;
        }
        memcpy(_FileMCCurrentInfo.mBuffer + offset, pSrc, count);
        total += count;
        size -= count;
        pSrc += count;
        _FileMCCurrentInfo.mDirty = 1;
        _FileMCCurrentInfo.mPos += count;
        if (!(_FileMCCurrentInfo.mPos & 0x1FFF)) {
            if (FileMCFlush()) {
                return 0;
            }
        }
        fn_801F8768();
    }
    return total;
}

int FileMCFlush(void)
{
    int result;

    if (_FileMCCurrentInfo.mDirty) {
        result = CARDWrite(&_FileMCCurrentInfo.mFileInfo, _FileMCCurrentInfo.mBuffer, 0x2000, _FileMCCurrentInfo.mSector);
        if (result != 0) {
            return -1;
        }
        _FileMCCurrentInfo.mDirty = 0;
        _FileMCCurrentInfo.mSector += 0x2000;
    }
    return 0;
}
