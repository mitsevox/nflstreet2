/* Memory card manager: watches the card slots, mounts, formats and checks cards, and runs the asynchronous
   file operations (open, read, write, seek, delete, directory) that the game's save system polls. */
#include "game/fn_801D2B7C.h"
#include "engine/memorycard.h"
#include <dolphin/card.h>
#include <string.h>
#include <stdio.h>

typedef void (*MemCDeviceChangeFunc_t)(int added, int removed);

typedef struct MemCDevices_t {
    int mMounted;
    int mPresent;
    int mAdded;
    int mRemoved;
} MemCDevices_t;

typedef struct MemCOp_t {
    int mPort;
    int mHandle;
    int mState;
    int mResult;
    unsigned char mDone;
    unsigned char mBusy;
    int mSize;
    char mName[32];
    CARDStat mStat;
    CARDFileInfo mFileInfo;
    int mPos;
    char *mCache;
    int mChunkSize;
    int mCachePos;
    int mOffset;
    unsigned char mCacheDirty;
    unsigned char mCacheValid;
    int mLength;
    int mTransferred;
    int mPendingState;
    char *mPendingRead;
    char *mPendingWrite;
    int mPendingLength;
} MemCOp_t;

typedef struct MemCCard_t {
    int mType;
    s32 mMemSize;
    s32 mSectorSize;
    s32 mFreeBytes;
    s32 mFreeFiles;
    int mStatus;
    unsigned int mNumEntries;
} MemCCard_t;


static int _iFileCacheSize = 0;
static MemCDeviceChangeFunc_t _MemCDeviceChangeCallback = 0;
static MemCDevices_t _MemCDevices;
static MemCOp_t _MemCOp;
static MemCCard_t _MemCCard;
static char _MemCWorkArea[2][0xA000] __attribute__((aligned(32)));

extern int DateIsYearLeap(int year);


static void _MemCCacheGetFileOffsetAndChunkSize(int *pOffset, int *pChunkSize)
{
    int chunk;

    *pOffset = _MemCOp.mOffset / _MemCOp.mChunkSize * _MemCOp.mChunkSize;
    chunk = _MemCOp.mLength - *pOffset;
    if (chunk > _MemCOp.mChunkSize) {
        chunk = _MemCOp.mChunkSize;
    }
    *pChunkSize = chunk;
}

static void _MemCDetachCallback(s32 chan, s32 result)
{
    CARDUnmount(chan);
    _MemCDevices.mRemoved |= 1 << chan;
    _MemCDevices.mMounted &= ~(1 << chan);
    _MemCCard.mType = 0;
}

static int _MemCGetTypeFromCapacityAndSectorSize(unsigned int memSize, int sectorSize)
{
    int type = -1;

    if (sectorSize == 0x2000) {
        switch (memSize) {
        case 4:
            type = 1;
            break;
        case 8:
            type = 2;
            break;
        case 16:
            type = 3;
            break;
        case 32:
            type = 4;
            break;
        case 64:
            type = 5;
            break;
        case 128:
            type = 6;
            break;
        }
    } else {
        type = 7;
    }
    return type;
}

static int _MemCExprMatch(const char *pPattern, const char *pName)
{
    int i = 0;
    int match = 1;
    short length = strlen(pPattern);

    while (match && length != 0 && pPattern[i] != '*') {
        if (pPattern[i] != pName[i]) {
            match = 0;
            break;
        }
        length--;
        i++;
    }
    if (match == 1 && pPattern[i] != '*') {
        if (strlen(pPattern) != strlen(pName)) {
            match = 0;
        }
    }
    return match;
}

static void _MemCConvertFileTime(MemCDirEntry_t *pEntry, unsigned int seconds)
{
    unsigned char daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int days;
    unsigned short count;

    pEntry->mSecond = seconds % 60;
    pEntry->mMinute = (unsigned int)(seconds * (1.0f / 60.0f)) % 60;
    pEntry->mHour = (unsigned int)(seconds * (1.0f / 3600.0f)) % 24;
    days = seconds * (1.0f / 86400.0f);
    pEntry->mYear = 0;
    count = 366;
    while (days >= count) {
        days -= count;
        pEntry->mYear++;
        if (DateIsYearLeap(pEntry->mYear)) {
            count = 366;
        } else {
            count = 365;
        }
    }
    pEntry->mYear += 2000;
    daysInMonth[2] = DateIsYearLeap(pEntry->mYear) ? 29 : 28;
    count = 1;
    while (days >= daysInMonth[count]) {
        days -= daysInMonth[count++];
    }
    pEntry->mMonth = count;
    pEntry->mDay = days + 1;
}

static int _MemCHackDetectSharedFile(const char *pGameCode)
{
    if (pGameCode[4] == '-') {
        return 0;
    }
    return 1;
}

void MemCInit(void)
{
    CARDInit();
    // FAKEMATCH: reset/cache stores in struct declaration order, chosen by testing (same in MemCAsyncProbe, MemCAsyncFlush, MemCAsyncClose, _MemCAsyncRead)
    _MemCDevices.mMounted = 0;
    _MemCDevices.mPresent = 0;
    _MemCDevices.mAdded = 0;
    _MemCDevices.mRemoved = 0;
    _MemCOp.mState = -1;
    _MemCOp.mPos = 0;
    _MemCOp.mCache = 0;
    _MemCOp.mChunkSize = 0;
    _MemCOp.mCachePos = 0;
    _MemCOp.mCacheDirty = 0;
    _MemCOp.mCacheValid = 0;
    _MemCOp.mPendingState = -1;
    _MemCOp.mPendingRead = 0;
    _MemCOp.mPendingWrite = 0;
    _MemCOp.mPendingLength = 0;
    _MemCDeviceChangeCallback = 0;
}

void MemCShutdown(void)
{
    int tries;
    int chan = 0;

    do {
        tries = 3;
        if ((_MemCDevices.mMounted >> chan) & 1) {
            do {
                tries--;
            } while (MemCUnMount(chan) == -1);
        }
        chan++;
    } while (chan < 2 && tries > 0);
}

int MemCGetPort(int port)
{
    int chan = -1;

    switch (port) {
    case 0:
        chan = 0;
        break;
    case 1:
        chan = 1;
        break;
    }
    return chan;
}

static void _MemCRemoveDevice(int port)
{
    if ((_MemCDevices.mMounted >> _MemCOp.mPort) & 1) {
        // FAKEMATCH: mounted/present bit before the added/removed bit, chosen by testing (all six pairs here and in _MemCAddDevice)
        _MemCDevices.mMounted &= ~(1 << _MemCOp.mPort);
        _MemCDevices.mRemoved |= 1 << _MemCOp.mPort;
    }
    if ((_MemCDevices.mPresent >> _MemCOp.mPort) & 1) {
        _MemCDevices.mPresent &= ~(1 << _MemCOp.mPort);
        _MemCDevices.mRemoved |= 1 << _MemCOp.mPort;
    }
    if (_MemCDeviceChangeCallback != 0) {
        _MemCDeviceChangeCallback(_MemCDevices.mAdded, _MemCDevices.mRemoved);
    }
}

static void _MemCAddDevice(int unused, int mounted)
{
    if (mounted) {
        if ((_MemCDevices.mPresent >> _MemCOp.mPort) & 1) {
            _MemCDevices.mPresent &= ~(1 << _MemCOp.mPort);
            _MemCDevices.mRemoved |= 1 << _MemCOp.mPort;
        }
        if (!((_MemCDevices.mMounted >> _MemCOp.mPort) & 1)) {
            _MemCDevices.mMounted |= 1 << _MemCOp.mPort;
            _MemCDevices.mAdded |= 1 << _MemCOp.mPort;
        }
    } else {
        if ((_MemCDevices.mMounted >> _MemCOp.mPort) & 1) {
            _MemCDevices.mMounted &= ~(1 << _MemCOp.mPort);
            _MemCDevices.mRemoved |= 1 << _MemCOp.mPort;
        }
        if (!((_MemCDevices.mPresent >> _MemCOp.mPort) & 1)) {
            _MemCDevices.mPresent |= 1 << _MemCOp.mPort;
            _MemCDevices.mAdded |= 1 << _MemCOp.mPort;
        }
    }
    if (_MemCDeviceChangeCallback != 0) {
        _MemCDeviceChangeCallback(_MemCDevices.mAdded, _MemCDevices.mRemoved);
    }
}

int MemCGetDeviceChanges(int *pAdded, int *pRemoved)
{
    *pAdded = _MemCDevices.mAdded;
    *pRemoved = _MemCDevices.mRemoved;
    _MemCDevices.mAdded = 0;
    _MemCDevices.mRemoved = 0;
    return *pAdded != 0 || *pRemoved != 0;
}

int MemCAsyncProbe(int port)
{
    int result = -1;
    int status;

    // FAKEMATCH: operation-start order port, state, busy, result chosen by testing four orders; used in all 17 such blocks of this file
    _MemCOp.mPort = port;
    _MemCOp.mState = 1;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    status = CARDProbeEx(MemCGetPort(port), &_MemCCard.mMemSize, &_MemCCard.mSectorSize);
    _MemCOp.mResult = status;
    // FAKEMATCH: case store orders (busy first, result last; mType before mResult for no card) chosen by testing twelve orders
    switch (status) {
    case CARD_RESULT_READY:
        _MemCOp.mBusy = 0;
        _MemCCard.mType = _MemCGetTypeFromCapacityAndSectorSize(_MemCCard.mMemSize, _MemCCard.mSectorSize);
        _MemCOp.mResult = status;
        result = 0;
        break;
    case CARD_RESULT_WRONGDEVICE:
        _MemCOp.mBusy = 0;
        _MemCCard.mType = 8;
        _MemCOp.mResult = 0;
        result = 0;
        break;
    case CARD_RESULT_BUSY:
        _MemCOp.mResult = result;
        _MemCOp.mBusy = 0;
        result = 0;
        break;
    case CARD_RESULT_FATAL_ERROR:
    case CARD_RESULT_NOCARD:
        _MemCOp.mBusy = 0;
        _MemCCard.mType = 0;
        _MemCOp.mResult = 0;
        result = 0;
        break;
    default:
        result = -1;
        break;
    }
    return result;
}

int MemCAsyncFormat(int port)
{
    int status;

    _MemCOp.mPort = port;
    _MemCOp.mState = 0;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    status = CARDFormatAsync(port, 0);
    _MemCOp.mResult = status;
    if (status == CARD_RESULT_READY) {
        _MemCOp.mBusy = 1;
    } else {
        _MemCOp.mBusy = 0;
    }
    return 0;
}

int MemCAsyncMount(int port)
{
    int status;

    _MemCOp.mPort = port;
    _MemCOp.mState = 2;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    status = CARDMountAsync(port, _MemCWorkArea[port], _MemCDetachCallback, 0);
    _MemCOp.mResult = status;
    if (status == CARD_RESULT_READY) {
        _MemCOp.mBusy = 1;
    } else {
        _MemCOp.mBusy = 0;
    }
    return 0;
}

int MemCUnMount(int chan)
{
    int status = CARDUnmount(chan);

    if (status == CARD_RESULT_READY || status == CARD_RESULT_NOCARD) {
        status = 0;
    } else if (status == CARD_RESULT_BUSY) {
        status = -1;
    } else if (status == CARD_RESULT_FATAL_ERROR) {
        status = -100;
    } else if (status == CARD_RESULT_NOENT) {
        status = 0;
    }
    return status;
}

int MemCAsyncMountAlt(int port)
{
    _MemCOp.mPort = port;
    _MemCOp.mState = 4;
    _MemCOp.mResult = 0;
    _MemCOp.mBusy = 0;
    return 0;
}

int MemCUnMountAlt(int slot)
{
    return 0;
}

int MemCAsyncCheck(int port)
{
    int status;

    _MemCOp.mPort = port;
    _MemCOp.mState = 6;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    status = CARDCheckAsync(port, 0);
    _MemCOp.mResult = status;
    if (status == CARD_RESULT_BROKEN) {
        _MemCOp.mBusy = 0;
        return 0;
    }
    if (status == CARD_RESULT_READY) {
        _MemCOp.mBusy = 1;
    } else {
        _MemCOp.mBusy = 0;
    }
    return 0;
}

int MemCAsyncGetFreeSpace(int port)
{
    _MemCOp.mPort = port;
    _MemCOp.mState = 8;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mResult = CARDFreeBlocks(port, &_MemCCard.mFreeBytes, &_MemCCard.mFreeFiles);
    _MemCOp.mBusy = 0;
    return 0;
}

int MemCAsyncGetFreeEntries(int port)
{
    _MemCOp.mPort = port;
    _MemCOp.mState = 9;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mResult = CARDFreeBlocks(port, &_MemCCard.mFreeBytes, &_MemCCard.mFreeFiles);
    _MemCOp.mBusy = 0;
    return 0;
}

int MemCAsyncGetDir(int port, const char *pGameCode, const char *pPattern, MemCDirEntry_t *pEntries,
                unsigned int maxEntries)
{
    CARDStat stat;
    char code[12];
    unsigned int fileNo;
    int status;
    int found;
    int cmp;

    _MemCOp.mResult = 0;
    _MemCOp.mPort = port;
    _MemCOp.mState = 12;
    _MemCOp.mBusy = 1;
    _MemCCard.mNumEntries = 0;
    for (fileNo = 0; fileNo <= 126 && _MemCCard.mNumEntries < maxEntries; fileNo++) {
        status = CARDGetStatus(port, fileNo, &stat);
        if (status == CARD_RESULT_READY) {
            strncpy(code, (char *)stat.gameName, 4);
            code[4] = '-';
            strncpy(&code[5], (char *)stat.company, 2);
            code[7] = 0;
            if (_MemCHackDetectSharedFile(pGameCode) == 0) {
                found = 0;
                cmp = strncmp(code, pGameCode, 7);
            } else {
                cmp = strncmp((char *)stat.company, "69", 2);
                found = 0;
            }
            if (cmp == 0 && _MemCExprMatch(pPattern, stat.fileName)) {
                found = 1;
            }
            if (found) {
                _MemCConvertFileTime(&pEntries[_MemCCard.mNumEntries], stat.time);
                strncpy(pEntries[_MemCCard.mNumEntries].mName, stat.fileName, 32);
                pEntries[_MemCCard.mNumEntries].mName[31] = 0;
                pEntries[_MemCCard.mNumEntries].mLength = stat.length;
                pEntries[_MemCCard.mNumEntries].mIconAddr = stat.iconAddr;
                _MemCCard.mNumEntries++;
            }
        } else if (status != CARD_RESULT_NOFILE && status != CARD_RESULT_NOPERM) {
            _MemCOp.mResult = status;
            break;
        }
    }
    _MemCOp.mBusy = 0;
    return 0;
}

static void _MemCOpenDeleteCB(s32 chan, s32 result);
static void _MemCOpenCreateCB(s32 chan, s32 result);

int MemCAsyncOpen(int port, const char *pName, int unused, int flags, int size)
{
    int fileNo;
    int cmp;

    _MemCOp.mPort = port;
    _MemCOp.mState = 13;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mSize = (size + 0x1FFF) & ~0x1FFF;
    sprintf(_MemCOp.mName, "%s", pName);
    _MemCOp.mPos = 0;
    _MemCOp.mLength = _MemCOp.mSize;
    if (_MemCOp.mCache != 0) {
        fn_801D2BD0(_MemCOp.mCache);
        _MemCOp.mCache = 0;
        _MemCOp.mCachePos = 0;
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 0;
    }
    if (_iFileCacheSize != 0) {
        // FAKEMATCH: unused trace message; its string stays in .rodata where the target keeps it
        const char *pDebugMsg = "Allocated FileCache in MemCAsyncOpen()";

        _MemCOp.mCache = fn_801D2B7C(_iFileCacheSize, 0, 0);
        // FAKEMATCH: mCacheValid cleared last (search over the 120 orders of the five clears; same Dirty-then-Valid order as the other cache resets)
        _MemCOp.mChunkSize = _iFileCacheSize;
        _MemCOp.mOffset = 0;
        _MemCOp.mCachePos = 0;
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 0;
        if (_MemCOp.mCache == 0) {
            return -1;
        }
    }
    if (flags & 1) {
        _MemCOp.mDone = 0;
        for (fileNo = 0; fileNo < 127; fileNo++) {
            _MemCOp.mResult = CARDGetStatus(port, fileNo, &_MemCOp.mStat);
            if (_MemCOp.mResult != CARD_RESULT_READY && _MemCOp.mResult != CARD_RESULT_NOFILE) {
                goto fail;
            }
            if (_MemCOp.mResult != CARD_RESULT_NOFILE) {
                if (memcmp(_MemCOp.mStat.company, "69", 2) != 0
                    || (cmp = strncmp(_MemCOp.mStat.fileName, pName, 32)) != 0) {
                    _MemCOp.mResult = CARD_RESULT_NOFILE;
                } else {
                    _MemCOp.mResult = CARDFastDelete(port, fileNo);
                    if (_MemCOp.mResult == CARD_RESULT_READY
                        || _MemCOp.mResult == CARD_RESULT_NOFILE) {
                        goto create;
                    }
                    if (_MemCOp.mResult == CARD_RESULT_NOCARD) {
                        goto nocard;
                    }
                    return -1;
                }
            }
        }
        if (_MemCOp.mResult != CARD_RESULT_NOFILE) {
        fail:
            _MemCOp.mDone = 1;
            _MemCOp.mBusy = 0;
        } else {
        create:
            _MemCOpenDeleteCB(port, 0);
        }
    out:
        return 0;
    nocard:
        _MemCOp.mBusy = 0;
        _MemCOp.mDone = 1;
        goto out;
    }
    for (fileNo = 0; fileNo < 127; fileNo++) {
        _MemCOp.mResult = CARDGetStatus(port, fileNo, &_MemCOp.mStat);
        if (_MemCOp.mResult != CARD_RESULT_READY && _MemCOp.mResult != CARD_RESULT_NOFILE) {
            goto done;
        }
        if (_MemCOp.mResult != CARD_RESULT_NOFILE) {
            if (memcmp(_MemCOp.mStat.company, "69", 2) != 0) {
                _MemCOp.mResult = CARD_RESULT_NOFILE;
            } else if (strncmp(_MemCOp.mStat.fileName, pName, 32) != 0) {
                _MemCOp.mResult = CARD_RESULT_NOFILE;
            } else {
                _MemCOp.mResult = CARDFastOpen(port, fileNo, &_MemCOp.mFileInfo);
                if (_MemCOp.mResult == CARD_RESULT_READY) {
                    _MemCOp.mResult = fileNo;
                    _MemCOp.mLength = _MemCOp.mStat.length;
                }
                break;
            }
        }
    }
done:
    _MemCOp.mDone = 1;
    _MemCOp.mBusy = 0;
    return 0;
}

static void _MemCOpenDeleteCB(s32 chan, s32 result)
{
    if (result == CARD_RESULT_NOFILE || result == CARD_RESULT_READY) {
        _MemCOp.mResult = CARDCreateAsync(chan, _MemCOp.mName, _MemCOp.mSize,
                                               &_MemCOp.mFileInfo, _MemCOpenCreateCB);
        if (_MemCOp.mResult != CARD_RESULT_READY) {
            _MemCOp.mDone = 1;
        }
    } else {
        _MemCOp.mResult = result;
        _MemCOp.mBusy = 0;
        _MemCOp.mDone = 1;
    }
}

static void _MemCOpenCreateCB(s32 chan, s32 result)
{
    int fileNo = 0;

    if (result == CARD_RESULT_READY) {
        fileNo = CARDGetFileNo(&_MemCOp.mFileInfo);
        _MemCOp.mResult = CARDGetStatus(chan, fileNo, &_MemCOp.mStat);
        if (_MemCOp.mResult == CARD_RESULT_READY) {
            if (_MemCHackDetectSharedFile(_MemCOp.mName) == 0) {
                // FAKEMATCH: setter order (addresses first, banner last) chosen by testing; plain field stores for the two addresses
                _MemCOp.mStat.commentAddr = 0;
                _MemCOp.mStat.iconAddr = 0x40;
                CARDSetIconFormat(&_MemCOp.mStat, 0, CARD_STAT_ICON_RGB5A3);
                CARDSetIconSpeed(&_MemCOp.mStat, 0, CARD_STAT_SPEED_SLOW);
                CARDSetIconSpeed(&_MemCOp.mStat, 1, CARD_STAT_SPEED_END);
                CARDSetBannerFormat(&_MemCOp.mStat, CARD_STAT_BANNER_NONE);
                CARDSetIconAnim(&_MemCOp.mStat, CARD_STAT_ANIM_LOOP);
            }
            _MemCOp.mResult = fileNo;
        }
        _MemCOp.mBusy = 0;
        _MemCOp.mDone = 1;
    } else {
        _MemCOp.mResult = result;
        _MemCOp.mBusy = 0;
        _MemCOp.mDone = 1;
    }
}

int MemCAsyncFlush(int handle)
{
    // FAKEMATCH: unused trace message; the string stays in .rodata where the target keeps it
    const char *pDebugMsg = "MemCAsyncFlush: writing cache";
    int offset;
    int chunk;
    int status;

    if (_MemCOp.mCache != 0) {
        if (_MemCOp.mCacheDirty) {
            _MemCCacheGetFileOffsetAndChunkSize(&offset, &chunk);
            _MemCOp.mHandle = handle;
            _MemCOp.mState = 21;
            _MemCOp.mBusy = 1;
            _MemCOp.mResult = -99;
            _MemCOp.mSize = chunk;
            status = CARDWriteAsync(&_MemCOp.mFileInfo, _MemCOp.mCache, chunk, offset, 0);
            _MemCOp.mResult = status;
            _MemCOp.mBusy = status == CARD_RESULT_READY;
            _MemCOp.mCachePos = 0;
            _MemCOp.mCacheDirty = 0;
            _MemCOp.mCacheValid = 0;
            return 0;
        }
        _MemCOp.mCachePos = 0;
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 0;
    }
    _MemCOp.mHandle = handle;
    _MemCOp.mState = 16;
    _MemCOp.mResult = 0;
    _MemCOp.mBusy = 0;
    return 0;
}

int MemCAsyncClose(int handle)
{
    if (_MemCOp.mCache != 0) {
        fn_801D2BD0(_MemCOp.mCache);
        _MemCOp.mCache = 0;
        _MemCOp.mCachePos = 0;
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 0;
        _MemCOp.mPendingState = -1;
        _MemCOp.mPendingRead = 0;
        _MemCOp.mPendingWrite = 0;
        _MemCOp.mPendingLength = 0;
    }
    _MemCOp.mHandle = handle;
    _MemCOp.mState = 15;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mResult = CARDClose(&_MemCOp.mFileInfo);
    _MemCOp.mBusy = 0;
    return 0;
}

int MemCAsyncDelete(int port, const char *pName)
{
    int fileNo;

    _MemCOp.mPort = port;
    _MemCOp.mState = 17;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    for (fileNo = 0; fileNo < 127; fileNo++) {
        _MemCOp.mResult = CARDGetStatus(port, fileNo, &_MemCOp.mStat);
        if (_MemCOp.mResult == CARD_RESULT_READY || _MemCOp.mResult == CARD_RESULT_NOFILE) {
            if (_MemCOp.mResult != CARD_RESULT_NOFILE) {
                if (memcmp(_MemCOp.mStat.company, "69", 2) != 0) {
                    _MemCOp.mResult = CARD_RESULT_NOFILE;
                } else if (strncmp(_MemCOp.mStat.fileName, pName, 32) != 0) {
                    _MemCOp.mResult = CARD_RESULT_NOFILE;
                } else {
                    _MemCOp.mResult = CARDFastDeleteAsync(port, fileNo, 0);
                    if (_MemCOp.mResult == CARD_RESULT_READY) {
                        _MemCOp.mBusy = 1;
                        return 0;
                    }
                    _MemCOp.mDone = 1;
                    _MemCOp.mBusy = 0;
                    return 0;
                }
            }
        } else {
            _MemCOp.mDone = 1;
            _MemCOp.mBusy = 0;
            return 0;
        }
    }
    _MemCOp.mDone = 1;
    _MemCOp.mBusy = 0;
    return 0;
}

int MemCAsyncSeek(int handle, int offset, int whence)
{
    // FAKEMATCH: unused trace message; the string stays in .rodata where the target keeps it
    const char *pDebugMsg = "MemCAsyncSeek: prefetching cache";
    int fileOffset;
    int chunk;
    int status;

    if (_MemCOp.mCache != 0) {
        if (whence == 1) {
            offset += _MemCOp.mOffset;
        }
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 0;
        _MemCOp.mOffset = offset;
        _MemCOp.mCachePos = offset % _MemCOp.mChunkSize;
        _MemCCacheGetFileOffsetAndChunkSize(&fileOffset, &chunk);
        _MemCOp.mHandle = handle;
        _MemCOp.mState = 20;
        _MemCOp.mBusy = 1;
        _MemCOp.mResult = -99;
        status = CARDReadAsync(&_MemCOp.mFileInfo, _MemCOp.mCache, chunk, fileOffset, 0);
        _MemCOp.mResult = status;
        _MemCOp.mCacheValid = 1;
        _MemCOp.mBusy = status == CARD_RESULT_READY;
        return 0;
    }
    _MemCOp.mHandle = handle;
    _MemCOp.mState = 19;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    if (whence == 1) {
        _MemCOp.mPos += offset;
    } else if (whence == 0) {
        _MemCOp.mPos = offset;
    } else {
        _MemCOp.mPos = _MemCOp.mLength - offset;
    }
    if (_MemCOp.mPos < 0 || _MemCOp.mPos > _MemCOp.mLength) {
        _MemCOp.mResult = -11;
    } else {
        _MemCOp.mResult = 0;
    }
    _MemCOp.mBusy = 0;
    return 0;
}

static int _MemCAsyncRead(int handle, char *pBuffer, int length)
{
    // FAKEMATCH: unused trace messages; the strings stay in .rodata where the target keeps them
    const char *pDebugMsg0 = "MemCAsyncRead: cache hit";
    const char *pDebugMsg1 = "MemCAsyncRead: loading cache & add queued read";
    int offset;
    int chunk;
    int count;
    int status;

    if (_MemCOp.mCache != 0) {
        if (_MemCOp.mCacheValid) {
            count = _MemCOp.mChunkSize - _MemCOp.mCachePos;
            if (count > length) {
                count = length;
            }
            if (count > 0) {
                memcpy(pBuffer, _MemCOp.mCache + _MemCOp.mCachePos, count);
                _MemCOp.mCachePos += count;
            }
            pBuffer += count;
            length -= count;
            _MemCOp.mOffset += count;
            _MemCOp.mTransferred += count;
        }
        if (length == 0) {
            _MemCOp.mHandle = handle;
            _MemCOp.mState = 20;
            _MemCOp.mResult = 0;
            _MemCOp.mBusy = 0;
            return 0;
        }
        _MemCCacheGetFileOffsetAndChunkSize(&offset, &chunk);
        _MemCOp.mHandle = handle;
        _MemCOp.mState = 20;
        _MemCOp.mBusy = 1;
        _MemCOp.mResult = -99;
        _MemCOp.mSize = length;
        status = CARDReadAsync(&_MemCOp.mFileInfo, _MemCOp.mCache, chunk, offset, 0);
        _MemCOp.mResult = status;
        _MemCOp.mBusy = status == CARD_RESULT_READY;
        _MemCOp.mCachePos = 0;
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 1;
        _MemCOp.mPendingState = 20;
        _MemCOp.mPendingRead = pBuffer;
        _MemCOp.mPendingWrite = 0;
        _MemCOp.mPendingLength = length;
        return 0;
    }
    _MemCOp.mHandle = handle;
    _MemCOp.mState = 20;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mSize = length;
    _MemCOp.mResult = CARDReadAsync(&_MemCOp.mFileInfo, pBuffer, length, _MemCOp.mPos, 0);
    if (_MemCOp.mResult == CARD_RESULT_READY) {
        _MemCOp.mBusy = 1;
    } else {
        _MemCOp.mBusy = 0;
    }
    return 0;
}

int MemCAsyncRead(int handle, char *pBuffer, int length)
{
    _MemCOp.mTransferred = 0;
    return _MemCAsyncRead(handle, pBuffer, length);
}

static int _MemCAsyncWrite(int handle, char *pBuffer, int length)
{
    // FAKEMATCH: unused trace messages; the strings stay in .rodata where the target keeps them
    const char *pDebugMsg0 = "MemCAsyncWrite: prefetching cache & add queued write";
    const char *pDebugMsg1 = "MemCAsyncWrite: cache full; flushing & add queued write";
    const char *pDebugMsg2 = "MemCAsyncWrite: cache full; flushing";
    int offset;
    int chunk;
    int count;
    int status;

    if (_MemCOp.mCache != 0) {
        _MemCCacheGetFileOffsetAndChunkSize(&offset, &chunk);
        count = 0;
        if (!_MemCOp.mCacheValid) {
            _MemCOp.mHandle = handle;
            _MemCOp.mState = 20;
            _MemCOp.mBusy = 1;
            _MemCOp.mResult = -99;
            status = CARDReadAsync(&_MemCOp.mFileInfo, _MemCOp.mCache, chunk, offset, 0);
            _MemCOp.mCacheValid = 1;
            _MemCOp.mBusy = status == CARD_RESULT_READY;
            _MemCOp.mPendingState = 21;
            _MemCOp.mPendingRead = 0;
            _MemCOp.mPendingWrite = pBuffer;
            _MemCOp.mPendingLength = length;
            _MemCOp.mResult = status;
            return 0;
        }
        count = _MemCOp.mChunkSize - _MemCOp.mCachePos;
        if (count > length) {
            count = length;
        }
        memcpy(_MemCOp.mCache + _MemCOp.mCachePos, pBuffer, count);
        _MemCOp.mCachePos += count;
        _MemCOp.mOffset += count;
        _MemCOp.mTransferred += count;
        _MemCOp.mCacheDirty = 1;
        if (_MemCOp.mCachePos < _MemCOp.mChunkSize) {
            _MemCOp.mBusy = 0;
            _MemCOp.mHandle = handle;
            _MemCOp.mState = 21;
            _MemCOp.mResult = 0;
            return 0;
        }
        _MemCOp.mResult = -99;
        _MemCOp.mSize = chunk;
        _MemCOp.mHandle = handle;
        pBuffer += count;
        _MemCOp.mBusy = 1;
        _MemCOp.mState = 21;
        status = CARDWriteAsync(&_MemCOp.mFileInfo, _MemCOp.mCache, chunk, offset, 0);
        _MemCOp.mResult = status;
        _MemCOp.mBusy = status == CARD_RESULT_READY;
        _MemCOp.mCachePos = 0;
        _MemCOp.mCacheDirty = 0;
        _MemCOp.mCacheValid = 0;
        length -= count;
        if (length != 0) {
            _MemCOp.mPendingLength = length;
            _MemCOp.mPendingState = 21;
            _MemCOp.mPendingRead = 0;
            _MemCOp.mPendingWrite = pBuffer;
        } else {
            _MemCOp.mPendingLength = 0;
            _MemCOp.mPendingState = -1;
            _MemCOp.mPendingRead = 0;
            _MemCOp.mPendingWrite = 0;
        }
        return 0;
    }
    _MemCOp.mHandle = handle;
    _MemCOp.mState = 21;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mSize = length;
    _MemCOp.mResult = CARDWriteAsync(&_MemCOp.mFileInfo, pBuffer, length, _MemCOp.mPos, 0);
    if (_MemCOp.mResult == CARD_RESULT_READY) {
        _MemCOp.mBusy = 1;
    } else {
        _MemCOp.mBusy = 0;
    }
    return 0;
}

int MemCAsyncWrite(int handle, char *pBuffer, int length)
{
    _MemCOp.mTransferred = 0;
    return _MemCAsyncWrite(handle, pBuffer, length);
}

int MemCAsyncGetSysInfo(void)
{
    return -1;
}

int MemCAsyncSetSysInfo(int handle, unsigned int *pSysInfo)
{
    _MemCOp.mHandle = handle;
    _MemCOp.mState = 23;
    _MemCOp.mBusy = 1;
    _MemCOp.mResult = -99;
    _MemCOp.mStat.iconAddr = pSysInfo[0];
    _MemCOp.mStat.commentAddr = pSysInfo[1];
    _MemCOp.mResult = CARDSetStatusAsync(_MemCOp.mPort, handle, &_MemCOp.mStat, 0);
    if (_MemCOp.mResult == CARD_RESULT_READY) {
        _MemCOp.mBusy = 1;
    } else {
        _MemCOp.mBusy = 0;
    }
    return 0;
}

void MemCFormatCardType(int type, char *pBuffer, int size)
{
    switch (type) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        sprintf(pBuffer, "Memory Card");
        break;
    case 7:
        sprintf(pBuffer, "Memory Card");
        break;
    case -1:
    case 0:
        sprintf(pBuffer, "Memory Card");
        break;
    case 8:
        sprintf(pBuffer, "other device");
        break;
    }
}

int MemCFormatPort(int port, char *pBuffer, int size)
{
    return sprintf(pBuffer, "Slot %c", MemCGetPort(port) + 'A');
}

int MemCEnableCache(int enable, int size)
{
    if (enable) {
        _iFileCacheSize = size;
    } else {
        _iFileCacheSize = 0;
    }
    return 0;
}

int MemCAsyncPoll(int *pResult)
{
    // FAKEMATCH: unused trace messages; the strings stay in .rodata where the target keeps them
    const char *pDebugMsg0 = "Dispatching Deferred read";
    const char *pDebugMsg1 = "Dispatching Deferred write";
    const char *pDebugMsg2 = "Dispatching Deferred flush";
    int state = _MemCOp.mState;
    int done = -1;
    int result = 0;

    if (state != -1) {
        if (_MemCOp.mBusy) {
            done = 1;
            result = CARDGetResultCode(_MemCOp.mPort);
            if (result == CARD_RESULT_BUSY) {
                done = 0;
            }
        } else {
            result = _MemCOp.mResult;
            done = 1;
        }
        switch (_MemCOp.mState) {
        case 13:
            result = _MemCOp.mResult;
            done = (signed char)_MemCOp.mDone;
            break;
        case 1:
            if (_MemCOp.mResult == -1) {
                MemCAsyncProbe(_MemCOp.mPort);
                if (_MemCOp.mResult == -1) {
                    done = 0;
                } else {
                    result = _MemCOp.mResult;
                    done = 1;
                }
            }
            break;
        }
        if (done != 1) {
            goto pending;
        }
        switch (_MemCOp.mState) {
        case 2:
            switch (result) {
            case CARD_RESULT_IOERROR:
            case CARD_RESULT_FATAL_ERROR:
                _MemCCard.mStatus = 4;
                result = 0;
                break;
            case CARD_RESULT_BROKEN:
                _MemCCard.mStatus = 1;
                result = 0;
                break;
            case CARD_RESULT_ENCODING:
                _MemCCard.mStatus = 3;
                result = 0;
                break;
            case CARD_RESULT_NOCARD:
            case CARD_RESULT_WRONGDEVICE:
            case CARD_RESULT_BUSY:
                break;
            case CARD_RESULT_READY:
                _MemCCard.mStatus = 0;
                break;
            }
            break;
        case 6:
            switch (result) {
            case CARD_RESULT_IOERROR:
            case CARD_RESULT_FATAL_ERROR:
                _MemCCard.mStatus = 4;
                result = 0;
                break;
            case CARD_RESULT_BROKEN:
                _MemCCard.mStatus = 2;
                result = 0;
                break;
            case CARD_RESULT_ENCODING:
                _MemCCard.mStatus = 3;
                result = 0;
                break;
            case CARD_RESULT_NOCARD:
            case CARD_RESULT_BUSY:
                break;
            case CARD_RESULT_READY:
                _MemCCard.mStatus = 0;
                break;
            }
            break;
        case 20:
        case 21:
            if (result == CARD_RESULT_LIMIT) {
                _MemCOp.mSize = 0;
                result = 0;
            }
            break;
        }
        if (result < 0) {
            // FAKEMATCH: pending-clear order length, state, write, read chosen by testing all 24 orders
            _MemCOp.mPendingLength = 0;
            _MemCOp.mPendingState = -1;
            _MemCOp.mPendingWrite = 0;
            _MemCOp.mPendingRead = 0;
            switch (result) {
            case CARD_RESULT_BUSY:
                break;
            case CARD_RESULT_WRONGDEVICE:
                result = -9;
                break;
            case CARD_RESULT_NOCARD:
                result = -2;
                break;
            case CARD_RESULT_NOFILE:
                result = -3;
                break;
            case CARD_RESULT_NOENT:
                result = -5;
                break;
            case CARD_RESULT_INSSPACE:
                result = -4;
                break;
            case CARD_RESULT_NOPERM:
                result = -7;
                break;
            case CARD_RESULT_EXIST:
            case CARD_RESULT_LIMIT:
                result = -99;
                break;
            case CARD_RESULT_NAMETOOLONG: // FAKEMATCH: own copy of the -99 body so -12 and -11 stay separate case nodes (target jump tree)
                result = -99;
                break;
            case CARD_RESULT_ENCODING:
                result = -8;
                break;
            case CARD_RESULT_BROKEN:
            case CARD_RESULT_CANCELED:
                result = -100;
                break;
            case CARD_RESULT_IOERROR:
            case CARD_RESULT_FATAL_ERROR:
                result = -10;
                break;
            }
        } else {
            switch (_MemCOp.mState) {
            case 8:
                result = _MemCCard.mFreeBytes;
                break;
            case 9:
                result = _MemCCard.mFreeFiles;
                break;
            case 12:
                result = _MemCCard.mNumEntries;
                break;
            case 1:
                result = _MemCCard.mType;
                if (result == 8) {
                    _MemCAddDevice(_MemCOp.mPort, 0);
                } else if (result == 0) {
                    result = -2;
                    _MemCRemoveDevice(_MemCOp.mPort);
                } else {
                    _MemCAddDevice(_MemCOp.mPort, 1);
                }
                break;
            case 2:
            case 6:
                result = _MemCCard.mStatus;
                break;
            case 20:
            case 21:
                result = _MemCOp.mSize;
                break;
            case 19:
                result = _MemCOp.mPos;
                break;
            }
        }
        // FAKEMATCH: completion reset order state, busy, result chosen by testing all six orders
        _MemCOp.mState = -1;
        _MemCOp.mBusy = 0;
        _MemCOp.mResult = -99;
    }
pending:
    if (_MemCOp.mCache != 0 && done == 1 && result >= 0) {
        int pendingState = _MemCOp.mPendingState;
        char *pRead = _MemCOp.mPendingRead;
        char *pWrite = _MemCOp.mPendingWrite;
        int length = _MemCOp.mPendingLength;

        _MemCOp.mBusy = 0;
        _MemCOp.mResult = -99;
        _MemCOp.mPendingState = -1;
        _MemCOp.mPendingLength = 0;
        _MemCOp.mState = -1;
        _MemCOp.mPendingRead = 0;
        _MemCOp.mPendingWrite = 0;
        if (pendingState != -1) {
            switch (pendingState) {
            case 20:
                _MemCAsyncRead(_MemCOp.mHandle, pRead, length);
                break;
            case 21:
                _MemCAsyncWrite(_MemCOp.mHandle, pWrite, length);
                break;
            case 16:
                MemCAsyncFlush(_MemCOp.mHandle);
                break;
            case 19:
                break;
            }
            return 0;
        }
        switch (state) {
        case 20:
        case 21:
            result = _MemCOp.mTransferred;
            break;
        }
    }
out:
    *pResult = result;
    return done;
}
