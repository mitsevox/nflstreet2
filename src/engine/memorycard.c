#include "game/fn_801D2B7C.h"
#include "engine/memorycard.h"

typedef void (*CARDCallback)(int chan, int result);

typedef struct CARDFileInfo {
    int chan;
    int fileNo;
    int offset;
    int length;
    unsigned short iBlock;
} CARDFileInfo;

typedef struct CARDStat {
    char fileName[32];
    unsigned int length;
    unsigned int time;
    unsigned char gameName[4];
    unsigned char company[2];
    unsigned char bannerFormat;
    unsigned int iconAddr;
    unsigned short iconFormat;
    unsigned short iconSpeed;
    unsigned int commentAddr;
    unsigned int offsetBanner;
    unsigned int offsetBannerTlut;
    unsigned int offsetIcon[8];
    unsigned int offsetIconTlut;
    unsigned int offsetData;
} CARDStat;

#define CARD_STAT_ICON_RGB5A3 2
#define CARD_STAT_ICON_MASK 3
#define CARD_STAT_BANNER_NONE 0
#define CARD_STAT_BANNER_MASK 3
#define CARD_STAT_ANIM_LOOP 0x00
#define CARD_STAT_ANIM_MASK 0x04
#define CARD_STAT_SPEED_END 0
#define CARD_STAT_SPEED_SLOW 3
#define CARD_STAT_SPEED_MASK 3

#define CARDSetBannerFormat(stat, f) \
    ((stat)->bannerFormat = (unsigned char)(((stat)->bannerFormat & ~CARD_STAT_BANNER_MASK) | (f)))
#define CARDSetIconAnim(stat, f) \
    ((stat)->bannerFormat = (unsigned char)(((stat)->bannerFormat & ~CARD_STAT_ANIM_MASK) | (f)))
#define CARDSetIconFormat(stat, n, f) \
    ((stat)->iconFormat = \
         (unsigned short)(((stat)->iconFormat & ~(CARD_STAT_ICON_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconSpeed(stat, n, f) \
    ((stat)->iconSpeed = \
         (unsigned short)(((stat)->iconSpeed & ~(CARD_STAT_SPEED_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconAddress(stat, addr) ((stat)->iconAddr = (unsigned int)(addr))
#define CARDSetCommentAddress(stat, addr) ((stat)->commentAddr = (unsigned int)(addr))
#define CARDGetFileNo(fileInfo) ((fileInfo)->fileNo)

#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY -1
#define CARD_RESULT_WRONGDEVICE -2
#define CARD_RESULT_NOCARD -3
#define CARD_RESULT_NOFILE -4
#define CARD_RESULT_BROKEN -6
#define CARD_RESULT_NOPERM -10
#define CARD_RESULT_NOENT -8
#define CARD_RESULT_FATAL_ERROR -128

extern void CARDInit(void);
extern int CARDUnmount(int chan);
extern int CARDCheckAsync(int chan, CARDCallback callback);
extern int CARDFreeBlocks(int chan, int *byteNotUsed, int *filesNotUsed);
extern int CARDGetStatus(int chan, int fileNo, CARDStat *stat);

typedef void (*MemCDeviceCallback)(int added, int removed);

typedef struct MemCDevices {
    int mMounted;
    int mPresent;
    int mAdded;
    int mRemoved;
} MemCDevices;

typedef struct MemCOp {
    int mPort;
    int mHandle;
    int mState;
    int mResult;
    unsigned char mUnknown10;
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
    int mUnknownD4;
    int mPendingState;
    char *mPendingRead;
    char *mPendingWrite;
    int mPendingLength;
} MemCOp;

typedef struct MemCCard {
    int mType;
    int mMemSize;
    int mSectorSize;
    int mFreeBytes;
    int mFreeFiles;
    int mUnknown14;
    unsigned int mNumEntries;
} MemCCard;


extern MemCDevices lbl_80384CC0;
extern MemCOp lbl_80384CD0;
extern MemCCard lbl_80384DB8;
extern char lbl_80384DE0[2][0xA000];
extern MemCDeviceCallback lbl_803EBCFC;
extern int lbl_803EBCF8;

extern int fn_80255D3C(int chan, int *memSize, int *sectorSize);
extern int fn_80256400(int chan, void *workArea, CARDCallback detachCallback, CARDCallback attachCallback);
extern int CARDFormatAsync(int chan, CARDCallback callback);
extern unsigned int strlen(const char *pString);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int count);
extern int strncmp(const char *pA, const char *pB, unsigned int count);
extern const char lbl_802AFCF8[];
extern const char lbl_802AFCFC[];
extern const char lbl_802AFE50[];
extern const char lbl_802AFE5C[];
extern const char lbl_802AFE6C[];
extern int sprintf(char *pBuffer, const char *pFormat, ...);
extern int memcmp(const void *pA, const void *pB, unsigned int count);
extern void *memcpy();
extern int CARDCreateAsync(int chan, const char *fileName, unsigned int size, CARDFileInfo *fileInfo,
                           CARDCallback callback);
extern int CARDFastDelete(int chan, int fileNo);
extern int CARDFastDeleteAsync(int chan, int fileNo, CARDCallback callback);
extern int fn_80257388(int chan, int fileNo, CARDFileInfo *fileInfo);
extern int fn_8025748C(CARDFileInfo *fileInfo);
extern int CARDReadAsync(CARDFileInfo *fileInfo, void *buf, int length, int offset, CARDCallback callback);
extern int CARDWriteAsync(CARDFileInfo *fileInfo, void *buf, int length, int offset, CARDCallback callback);
extern int fn_8027EFAC(int year);
extern int CARDSetStatusAsync(int chan, int fileNo, CARDStat *stat, CARDCallback callback);


static void fn_801D3C68(int *pOffset, int *pChunkSize)
{
    int chunk;

    *pOffset = lbl_80384CD0.mOffset / lbl_80384CD0.mChunkSize * lbl_80384CD0.mChunkSize;
    chunk = lbl_80384CD0.mLength - *pOffset;
    if (chunk > lbl_80384CD0.mChunkSize) {
        chunk = lbl_80384CD0.mChunkSize;
    }
    *pChunkSize = chunk;
}

static void fn_801D3CA4(int chan, int result)
{
    CARDUnmount(chan);
    lbl_80384CC0.mRemoved |= 1 << chan;
    lbl_80384CC0.mMounted &= ~(1 << chan);
    lbl_80384DB8.mType = 0;
}

static int fn_801D3D04(unsigned int memSize, int sectorSize)
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

static int fn_801D3D98(const char *pPattern, const char *pName)
{
    int i = 0;
    int match = 1;
    short length = strlen(pPattern);

    while (match && length != 0 && pPattern[i] != '*') {
        if (pPattern[i] == pName[i]) {
            length--;
            i++;
        } else {
            match = 0;
        }
    }
    if (match == 1 && pPattern[i] != '*') {
        if (strlen(pPattern) != strlen(pName)) {
            match = 0;
        }
    }
    return match;
}

static void fn_801D3E6C(MemCDirEntry *pEntry, unsigned int seconds)
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
        if (fn_8027EFAC(pEntry->mYear)) {
            count = 366;
        } else {
            count = 365;
        }
    }
    pEntry->mYear += 2000;
    daysInMonth[2] = fn_8027EFAC(pEntry->mYear) ? 29 : 28;
    count = 1;
    while (days >= daysInMonth[count]) {
        days -= daysInMonth[count++];
    }
    pEntry->mMonth = count;
    pEntry->mDay = days + 1;
}

static int fn_801D4108(const char *pGameCode)
{
    if (pGameCode[4] == '-') {
        return 0;
    }
    return 1;
}

void fn_801D4120(void)
{
    CARDInit();
    lbl_80384CC0.mMounted = 0;
    lbl_80384CC0.mRemoved = 0;
    lbl_80384CD0.mPendingState = -1;
    lbl_80384CD0.mPendingLength = 0;
    lbl_803EBCFC = 0;
    lbl_80384CC0.mPresent = 0;
    lbl_80384CC0.mAdded = 0;
    lbl_80384CD0.mState = -1;
    lbl_80384CD0.mPos = 0;
    lbl_80384CD0.mCache = 0;
    lbl_80384CD0.mChunkSize = 0;
    lbl_80384CD0.mCachePos = 0;
    lbl_80384CD0.mCacheDirty = 0;
    lbl_80384CD0.mCacheValid = 0;
    lbl_80384CD0.mPendingRead = 0;
    lbl_80384CD0.mPendingWrite = 0;
}

void fn_801D4198(void)
{
    int tries = 3;
    int chan;

    for (chan = 0; chan < 2 && tries > 0; chan++) {
        if ((lbl_80384CC0.mMounted >> chan) & 1) {
            do {
                tries--;
            } while (fn_801D466C(chan) == -1);
        }
    }
}

int fn_801D4204(int port)
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

static void fn_801D4230(void)
{
    if ((lbl_80384CC0.mMounted >> lbl_80384CD0.mPort) & 1) {
        lbl_80384CC0.mRemoved |= 1 << lbl_80384CD0.mPort;
        lbl_80384CC0.mMounted &= ~(1 << lbl_80384CD0.mPort);
    }
    if ((lbl_80384CC0.mPresent >> lbl_80384CD0.mPort) & 1) {
        lbl_80384CC0.mRemoved |= 1 << lbl_80384CD0.mPort;
        lbl_80384CC0.mPresent &= ~(1 << lbl_80384CD0.mPort);
    }
    if (lbl_803EBCFC != 0) {
        lbl_803EBCFC(lbl_80384CC0.mAdded, lbl_80384CC0.mRemoved);
    }
}

static void fn_801D42D4(int unused, int mounted)
{
    if (mounted) {
        if ((lbl_80384CC0.mPresent >> lbl_80384CD0.mPort) & 1) {
            lbl_80384CC0.mRemoved |= 1 << lbl_80384CD0.mPort;
            lbl_80384CC0.mPresent &= ~(1 << lbl_80384CD0.mPort);
        }
        if (!((lbl_80384CC0.mMounted >> lbl_80384CD0.mPort) & 1)) {
            lbl_80384CC0.mAdded |= 1 << lbl_80384CD0.mPort;
            lbl_80384CC0.mMounted |= 1 << lbl_80384CD0.mPort;
        }
    } else {
        if ((lbl_80384CC0.mMounted >> lbl_80384CD0.mPort) & 1) {
            lbl_80384CC0.mRemoved |= 1 << lbl_80384CD0.mPort;
            lbl_80384CC0.mMounted &= ~(1 << lbl_80384CD0.mPort);
        }
        if (!((lbl_80384CC0.mPresent >> lbl_80384CD0.mPort) & 1)) {
            lbl_80384CC0.mAdded |= 1 << lbl_80384CD0.mPort;
            lbl_80384CC0.mPresent |= 1 << lbl_80384CD0.mPort;
        }
    }
    if (lbl_803EBCFC != 0) {
        lbl_803EBCFC(lbl_80384CC0.mAdded, lbl_80384CC0.mRemoved);
    }
}

int fn_801D4400(int *pAdded, int *pRemoved)
{
    *pAdded = lbl_80384CC0.mAdded;
    *pRemoved = lbl_80384CC0.mRemoved;
    lbl_80384CC0.mAdded = 0;
    lbl_80384CC0.mRemoved = 0;
    return *pAdded != 0 || *pRemoved != 0;
}

int fn_801D444C(int port)
{
    int result = -1;
    int status;

    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mState = 1;
    status = fn_80255D3C(fn_801D4204(port), &lbl_80384DB8.mMemSize, &lbl_80384DB8.mSectorSize);
    lbl_80384CD0.mResult = status;
    switch (status) {
    case CARD_RESULT_READY:
        lbl_80384CD0.mBusy = 0;
        result = 0;
        lbl_80384DB8.mType = fn_801D3D04(lbl_80384DB8.mMemSize, lbl_80384DB8.mSectorSize);
        lbl_80384CD0.mResult = status;
        break;
    case CARD_RESULT_WRONGDEVICE:
        lbl_80384DB8.mType = 8;
        result = 0;
        lbl_80384CD0.mResult = 0;
        lbl_80384CD0.mBusy = 0;
        break;
    case CARD_RESULT_BUSY:
        lbl_80384CD0.mResult = result;
        lbl_80384CD0.mBusy = 0;
        result = 0;
        break;
    case CARD_RESULT_FATAL_ERROR:
    case CARD_RESULT_NOCARD:
        lbl_80384CD0.mResult = 0;
        lbl_80384CD0.mBusy = 0;
        result = 0;
        lbl_80384DB8.mType = 0;
        break;
    default:
        result = -1;
        break;
    }
    return result;
}

int fn_801D4570(int port)
{
    int status;

    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mState = 0;
    lbl_80384CD0.mBusy = 1;
    status = CARDFormatAsync(port, 0);
    lbl_80384CD0.mResult = status;
    if (status == CARD_RESULT_READY) {
        lbl_80384CD0.mBusy = 1;
    } else {
        lbl_80384CD0.mBusy = 0;
    }
    return 0;
}

int fn_801D45DC(int port)
{
    int status;

    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 2;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mBusy = 1;
    status = fn_80256400(port, lbl_80384DE0[port], fn_801D3CA4, 0);
    lbl_80384CD0.mResult = status;
    if (status == CARD_RESULT_READY) {
        lbl_80384CD0.mBusy = 1;
    } else {
        lbl_80384CD0.mBusy = 0;
    }
    return 0;
}

int fn_801D466C(int chan)
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

int fn_801D46C0(int port)
{
    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 4;
    lbl_80384CD0.mResult = 0;
    lbl_80384CD0.mBusy = 0;
    return 0;
}

int fn_801D46E8(void)
{
    return 0;
}

int fn_801D46F0(int port)
{
    int status;

    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 6;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mBusy = 1;
    status = CARDCheckAsync(port, 0);
    lbl_80384CD0.mResult = status;
    if (status == CARD_RESULT_BROKEN) {
        lbl_80384CD0.mBusy = 0;
        return 0;
    }
    if (status == CARD_RESULT_READY) {
        lbl_80384CD0.mBusy = 1;
    } else {
        lbl_80384CD0.mBusy = 0;
    }
    return 0;
}

int fn_801D4778(int port)
{
    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 8;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mResult = CARDFreeBlocks(port, &lbl_80384DB8.mFreeBytes, &lbl_80384DB8.mFreeFiles);
    lbl_80384CD0.mBusy = 0;
    return 0;
}

int fn_801D47E0(int port)
{
    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 9;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mResult = CARDFreeBlocks(port, &lbl_80384DB8.mFreeBytes, &lbl_80384DB8.mFreeFiles);
    lbl_80384CD0.mBusy = 0;
    return 0;
}

int fn_801D4848(int port, const char *pGameCode, const char *pPattern, MemCDirEntry *pEntries,
                unsigned int maxEntries)
{
    CARDStat stat;
    char code[8];
    unsigned int fileNo;
    int status;
    int found;
    int cmp;

    lbl_80384CD0.mResult = 0;
    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 12;
    lbl_80384CD0.mBusy = 1;
    lbl_80384DB8.mNumEntries = 0;
    for (fileNo = 0; fileNo < maxEntries; fileNo++) {
        status = CARDGetStatus(port, fileNo, &stat);
        if (status == CARD_RESULT_READY) {
            strncpy(code, (char *)stat.gameName, 4);
            code[4] = '-';
            strncpy(&code[5], (char *)stat.company, 2);
            code[7] = 0;
            if (fn_801D4108(pGameCode) == 0) {
                found = 0;
                cmp = strncmp(code, pGameCode, 7);
            } else {
                cmp = strncmp((char *)stat.company, lbl_802AFCF8, 2);
                found = 0;
            }
            if (cmp == 0 && fn_801D3D98(pPattern, stat.fileName)) {
                found = 1;
            }
            if (found) {
                fn_801D3E6C(&pEntries[lbl_80384DB8.mNumEntries], stat.time);
                strncpy(pEntries[lbl_80384DB8.mNumEntries].mName, stat.fileName, 32);
                pEntries[lbl_80384DB8.mNumEntries].mName[31] = 0;
                pEntries[lbl_80384DB8.mNumEntries].mLength = stat.length;
                pEntries[lbl_80384DB8.mNumEntries].mIconAddr = stat.iconAddr;
                lbl_80384DB8.mNumEntries++;
            }
        } else if (status != CARD_RESULT_NOFILE && status != CARD_RESULT_NOPERM) {
            lbl_80384CD0.mResult = status;
            break;
        }
        if (fileNo + 1 > 126) {
            break;
        }
        if (lbl_80384DB8.mNumEntries >= maxEntries) {
            break;
        }
    }
    lbl_80384CD0.mBusy = 0;
    return 0;
}

static void fn_801D4D08(int chan, int result);
static void fn_801D4D90(int chan, int result);

int fn_801D4A3C(int port, const char *pName, int unused, int flags, int size)
{
    int fileNo;
    int cmp;

    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 13;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mSize = (size + 0x1FFF) & ~0x1FFF;
    sprintf(lbl_80384CD0.mName, lbl_802AFCFC, pName);
    lbl_80384CD0.mPos = 0;
    lbl_80384CD0.mLength = lbl_80384CD0.mSize;
    if (lbl_80384CD0.mCache != 0) {
        fn_801D2BD0(lbl_80384CD0.mCache);
        lbl_80384CD0.mCache = 0;
        lbl_80384CD0.mCachePos = 0;
        lbl_80384CD0.mCacheDirty = 0;
        lbl_80384CD0.mCacheValid = 0;
    }
    if (lbl_803EBCF8 != 0) {
        lbl_80384CD0.mCache = fn_801D2B7C(lbl_803EBCF8, 0, 0);
        lbl_80384CD0.mCacheValid = 0;
        lbl_80384CD0.mChunkSize = lbl_803EBCF8;
        lbl_80384CD0.mOffset = 0;
        lbl_80384CD0.mCachePos = 0;
        lbl_80384CD0.mCacheDirty = 0;
        if (lbl_80384CD0.mCache == 0) {
            return -1;
        }
    }
    if (flags & 1) {
        lbl_80384CD0.mUnknown10 = 0;
        for (fileNo = 0; fileNo < 127; fileNo++) {
            lbl_80384CD0.mResult = CARDGetStatus(port, fileNo, &lbl_80384CD0.mStat);
            if (lbl_80384CD0.mResult != CARD_RESULT_READY && lbl_80384CD0.mResult != CARD_RESULT_NOFILE) {
                goto fail;
            }
            if (lbl_80384CD0.mResult != CARD_RESULT_NOFILE) {
                if (memcmp(lbl_80384CD0.mStat.company, lbl_802AFCF8, 2) == 0
                    && (cmp = strncmp(lbl_80384CD0.mStat.fileName, pName, 32)) == 0) {
                    lbl_80384CD0.mResult = CARDFastDelete(port, fileNo);
                    if (lbl_80384CD0.mResult == CARD_RESULT_READY
                        || lbl_80384CD0.mResult == CARD_RESULT_NOFILE) {
                        goto create;
                    }
                    if (lbl_80384CD0.mResult == CARD_RESULT_NOCARD) {
                        goto nocard;
                    }
                    return -1;
                }
                lbl_80384CD0.mResult = CARD_RESULT_NOFILE;
            }
        }
        if (lbl_80384CD0.mResult != CARD_RESULT_NOFILE) {
        fail:
            lbl_80384CD0.mBusy = 0;
            lbl_80384CD0.mUnknown10 = 1;
        } else {
        create:
            fn_801D4D08(port, 0);
        }
        return 0;
    nocard:
        lbl_80384CD0.mBusy = 0;
        lbl_80384CD0.mUnknown10 = 1;
        return 0;
    }
    for (fileNo = 0; fileNo < 127; fileNo++) {
        lbl_80384CD0.mResult = CARDGetStatus(port, fileNo, &lbl_80384CD0.mStat);
        if (lbl_80384CD0.mResult != CARD_RESULT_READY && lbl_80384CD0.mResult != CARD_RESULT_NOFILE) {
            break;
        }
        if (lbl_80384CD0.mResult != CARD_RESULT_NOFILE) {
            if (memcmp(lbl_80384CD0.mStat.company, lbl_802AFCF8, 2) == 0
                && strncmp(lbl_80384CD0.mStat.fileName, pName, 32) == 0) {
                lbl_80384CD0.mResult = fn_80257388(port, fileNo, &lbl_80384CD0.mFileInfo);
                if (lbl_80384CD0.mResult == CARD_RESULT_READY) {
                    lbl_80384CD0.mResult = fileNo;
                    lbl_80384CD0.mLength = lbl_80384CD0.mStat.length;
                }
                break;
            }
            lbl_80384CD0.mResult = CARD_RESULT_NOFILE;
        }
    }
    lbl_80384CD0.mBusy = 0;
    lbl_80384CD0.mUnknown10 = 1;
    return 0;
}

static void fn_801D4D08(int chan, int result)
{
    if (result == CARD_RESULT_NOFILE || result == CARD_RESULT_READY) {
        lbl_80384CD0.mResult = CARDCreateAsync(chan, lbl_80384CD0.mName, lbl_80384CD0.mSize,
                                               &lbl_80384CD0.mFileInfo, fn_801D4D90);
        if (lbl_80384CD0.mResult != CARD_RESULT_READY) {
            lbl_80384CD0.mUnknown10 = 1;
        }
    } else {
        lbl_80384CD0.mResult = result;
        lbl_80384CD0.mBusy = 0;
        lbl_80384CD0.mUnknown10 = 1;
    }
}

static void fn_801D4D90(int chan, int result)
{
    int fileNo = 0;

    if (result == CARD_RESULT_READY) {
        fileNo = CARDGetFileNo(&lbl_80384CD0.mFileInfo);
        lbl_80384CD0.mResult = CARDGetStatus(chan, fileNo, &lbl_80384CD0.mStat);
        if (lbl_80384CD0.mResult == CARD_RESULT_READY) {
            if (fn_801D4108(lbl_80384CD0.mName) == 0) {
                CARDSetBannerFormat(&lbl_80384CD0.mStat, CARD_STAT_BANNER_NONE);
                CARDSetIconAnim(&lbl_80384CD0.mStat, CARD_STAT_ANIM_LOOP);
                CARDSetCommentAddress(&lbl_80384CD0.mStat, 0);
                CARDSetIconAddress(&lbl_80384CD0.mStat, 0x40);
                CARDSetIconFormat(&lbl_80384CD0.mStat, 0, CARD_STAT_ICON_RGB5A3);
                CARDSetIconSpeed(&lbl_80384CD0.mStat, 0, CARD_STAT_SPEED_SLOW);
                CARDSetIconSpeed(&lbl_80384CD0.mStat, 1, CARD_STAT_SPEED_END);
            }
            lbl_80384CD0.mResult = fileNo;
        }
        lbl_80384CD0.mBusy = 0;
        lbl_80384CD0.mUnknown10 = 1;
    } else {
        lbl_80384CD0.mResult = result;
        lbl_80384CD0.mBusy = 0;
        lbl_80384CD0.mUnknown10 = 1;
    }
}

int fn_801D4E6C(int handle)
{
    int offset;
    int chunk;
    int status;

    if (lbl_80384CD0.mCache != 0) {
        if (lbl_80384CD0.mCacheDirty) {
            fn_801D3C68(&offset, &chunk);
            lbl_80384CD0.mState = 21;
            lbl_80384CD0.mBusy = 1;
            lbl_80384CD0.mResult = -99;
            lbl_80384CD0.mSize = chunk;
            lbl_80384CD0.mHandle = handle;
            status = CARDWriteAsync(&lbl_80384CD0.mFileInfo, lbl_80384CD0.mCache, chunk, offset, 0);
            lbl_80384CD0.mResult = status;
            lbl_80384CD0.mBusy = status == CARD_RESULT_READY;
            lbl_80384CD0.mCacheValid = 0;
            lbl_80384CD0.mCachePos = 0;
            lbl_80384CD0.mCacheDirty = 0;
            return 0;
        }
        lbl_80384CD0.mCacheDirty = 0;
        lbl_80384CD0.mCacheValid = 0;
        lbl_80384CD0.mCachePos = 0;
    }
    lbl_80384CD0.mBusy = 0;
    lbl_80384CD0.mHandle = handle;
    lbl_80384CD0.mState = 16;
    lbl_80384CD0.mResult = 0;
    return 0;
}

int fn_801D4F58(int handle)
{
    if (lbl_80384CD0.mCache != 0) {
        fn_801D2BD0(lbl_80384CD0.mCache);
        lbl_80384CD0.mPendingState = -1;
        lbl_80384CD0.mPendingLength = 0;
        lbl_80384CD0.mPendingWrite = 0;
        lbl_80384CD0.mCache = 0;
        lbl_80384CD0.mCachePos = 0;
        lbl_80384CD0.mCacheDirty = 0;
        lbl_80384CD0.mCacheValid = 0;
        lbl_80384CD0.mPendingRead = 0;
    }
    lbl_80384CD0.mState = 15;
    lbl_80384CD0.mHandle = handle;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mResult = fn_8025748C(&lbl_80384CD0.mFileInfo);
    lbl_80384CD0.mBusy = 0;
    return 0;
}

int fn_801D4FF4(int port, const char *pName)
{
    int fileNo;

    lbl_80384CD0.mPort = port;
    lbl_80384CD0.mState = 17;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    for (fileNo = 0; fileNo < 127; fileNo++) {
        lbl_80384CD0.mResult = CARDGetStatus(port, fileNo, &lbl_80384CD0.mStat);
        if (lbl_80384CD0.mResult == CARD_RESULT_READY || lbl_80384CD0.mResult == CARD_RESULT_NOFILE) {
            if (lbl_80384CD0.mResult != CARD_RESULT_NOFILE) {
                if (memcmp(lbl_80384CD0.mStat.company, lbl_802AFCF8, 2) != 0
                    || strncmp(lbl_80384CD0.mStat.fileName, pName, 32) != 0) {
                    lbl_80384CD0.mResult = CARD_RESULT_NOFILE;
                } else {
                    lbl_80384CD0.mResult = CARDFastDeleteAsync(port, fileNo, 0);
                    if (lbl_80384CD0.mResult == CARD_RESULT_READY) {
                        lbl_80384CD0.mBusy = 1;
                        return 0;
                    }
                    lbl_80384CD0.mUnknown10 = 1;
                    lbl_80384CD0.mBusy = 0;
                    return 0;
                }
            }
        } else {
            lbl_80384CD0.mUnknown10 = 1;
            lbl_80384CD0.mBusy = 0;
            return 0;
        }
    }
    lbl_80384CD0.mUnknown10 = 1;
    lbl_80384CD0.mBusy = 0;
    return 0;
}

int fn_801D512C(int handle, int offset, int whence)
{
    int fileOffset;
    int chunk;
    int status;

    if (lbl_80384CD0.mCache != 0) {
        if (whence == 1) {
            offset += lbl_80384CD0.mOffset;
        }
        lbl_80384CD0.mCacheDirty = 0;
        lbl_80384CD0.mCacheValid = 0;
        lbl_80384CD0.mOffset = offset;
        lbl_80384CD0.mCachePos = offset % lbl_80384CD0.mChunkSize;
        fn_801D3C68(&fileOffset, &chunk);
        lbl_80384CD0.mState = 20;
        lbl_80384CD0.mResult = -99;
        lbl_80384CD0.mHandle = handle;
        lbl_80384CD0.mBusy = 1;
        status = CARDReadAsync(&lbl_80384CD0.mFileInfo, lbl_80384CD0.mCache, chunk, fileOffset, 0);
        lbl_80384CD0.mResult = status;
        lbl_80384CD0.mCacheValid = 1;
        lbl_80384CD0.mBusy = status == CARD_RESULT_READY;
        return 0;
    }
    lbl_80384CD0.mHandle = handle;
    lbl_80384CD0.mState = 19;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mResult = -99;
    if (whence == 1) {
        lbl_80384CD0.mPos += offset;
    } else if (whence == 0) {
        lbl_80384CD0.mPos = offset;
    } else {
        lbl_80384CD0.mPos = lbl_80384CD0.mLength - offset;
    }
    if (lbl_80384CD0.mPos < 0 || lbl_80384CD0.mPos > lbl_80384CD0.mLength) {
        lbl_80384CD0.mResult = -11;
    } else {
        lbl_80384CD0.mResult = 0;
    }
    lbl_80384CD0.mBusy = 0;
    return 0;
}

static int fn_801D5288(int handle, char *pBuffer, int length)
{
    int offset;
    int chunk;
    int count;
    int status;

    if (lbl_80384CD0.mCache != 0) {
        if (lbl_80384CD0.mCacheValid) {
            count = lbl_80384CD0.mChunkSize - lbl_80384CD0.mCachePos;
            if (count > length) {
                count = length;
            }
            if (count > 0) {
                memcpy(pBuffer, lbl_80384CD0.mCache + lbl_80384CD0.mCachePos, count);
                lbl_80384CD0.mCachePos += count;
            }
            pBuffer += count;
            length -= count;
            lbl_80384CD0.mOffset += count;
            lbl_80384CD0.mUnknownD4 += count;
        }
        if (length == 0) {
            lbl_80384CD0.mBusy = 0;
            lbl_80384CD0.mHandle = handle;
            lbl_80384CD0.mState = 20;
            lbl_80384CD0.mResult = 0;
            return 0;
        }
        fn_801D3C68(&offset, &chunk);
        lbl_80384CD0.mResult = -99;
        lbl_80384CD0.mHandle = handle;
        lbl_80384CD0.mState = 20;
        lbl_80384CD0.mBusy = 1;
        lbl_80384CD0.mSize = length;
        status = CARDReadAsync(&lbl_80384CD0.mFileInfo, lbl_80384CD0.mCache, chunk, offset, 0);
        lbl_80384CD0.mPendingLength = length;
        lbl_80384CD0.mBusy = status == CARD_RESULT_READY;
        lbl_80384CD0.mCacheValid = 1;
        lbl_80384CD0.mPendingState = 20;
        lbl_80384CD0.mPendingRead = pBuffer;
        lbl_80384CD0.mPendingWrite = 0;
        lbl_80384CD0.mResult = status;
        lbl_80384CD0.mCachePos = 0;
        lbl_80384CD0.mCacheDirty = 0;
        return 0;
    }
    lbl_80384CD0.mHandle = handle;
    lbl_80384CD0.mState = 20;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mSize = length;
    lbl_80384CD0.mResult = CARDReadAsync(&lbl_80384CD0.mFileInfo, pBuffer, length, lbl_80384CD0.mPos, 0);
    if (lbl_80384CD0.mResult == CARD_RESULT_READY) {
        lbl_80384CD0.mBusy = 1;
    } else {
        lbl_80384CD0.mBusy = 0;
    }
    return 0;
}

int fn_801D5440(int handle, char *pBuffer, int length)
{
    lbl_80384CD0.mUnknownD4 = 0;
    return fn_801D5288(handle, pBuffer, length);
}

static int fn_801D546C(int handle, char *pBuffer, int length)
{
    int offset;
    int chunk;
    int count;
    int status;

    if (lbl_80384CD0.mCache != 0) {
        fn_801D3C68(&offset, &chunk);
        count = 0;
        if (!lbl_80384CD0.mCacheValid) {
            lbl_80384CD0.mState = 20;
            lbl_80384CD0.mResult = -99;
            lbl_80384CD0.mHandle = handle;
            lbl_80384CD0.mBusy = 1;
            status = CARDReadAsync(&lbl_80384CD0.mFileInfo, lbl_80384CD0.mCache, chunk, offset, 0);
            lbl_80384CD0.mCacheValid = 1;
            lbl_80384CD0.mBusy = status == CARD_RESULT_READY;
            lbl_80384CD0.mPendingState = 21;
            lbl_80384CD0.mPendingRead = 0;
            lbl_80384CD0.mPendingWrite = pBuffer;
            lbl_80384CD0.mPendingLength = length;
            lbl_80384CD0.mResult = status;
            return 0;
        }
        count = lbl_80384CD0.mChunkSize - lbl_80384CD0.mCachePos;
        if (count > length) {
            count = length;
        }
        memcpy(lbl_80384CD0.mCache + lbl_80384CD0.mCachePos, pBuffer, count);
        lbl_80384CD0.mCachePos += count;
        lbl_80384CD0.mOffset += count;
        lbl_80384CD0.mUnknownD4 += count;
        lbl_80384CD0.mCacheDirty = 1;
        if (lbl_80384CD0.mCachePos < lbl_80384CD0.mChunkSize) {
            lbl_80384CD0.mBusy = 0;
            lbl_80384CD0.mHandle = handle;
            lbl_80384CD0.mState = 21;
            lbl_80384CD0.mResult = 0;
            return 0;
        }
        lbl_80384CD0.mResult = -99;
        lbl_80384CD0.mSize = chunk;
        lbl_80384CD0.mHandle = handle;
        pBuffer += count;
        lbl_80384CD0.mBusy = 1;
        lbl_80384CD0.mState = 21;
        status = CARDWriteAsync(&lbl_80384CD0.mFileInfo, lbl_80384CD0.mCache, chunk, offset, 0);
        lbl_80384CD0.mResult = status;
        lbl_80384CD0.mBusy = status == CARD_RESULT_READY;
        lbl_80384CD0.mCachePos = 0;
        lbl_80384CD0.mCacheDirty = 0;
        lbl_80384CD0.mCacheValid = 0;
        length -= count;
        if (length != 0) {
            lbl_80384CD0.mPendingLength = length;
            lbl_80384CD0.mPendingState = 21;
            lbl_80384CD0.mPendingRead = 0;
            lbl_80384CD0.mPendingWrite = pBuffer;
        } else {
            lbl_80384CD0.mPendingLength = 0;
            lbl_80384CD0.mPendingState = -1;
            lbl_80384CD0.mPendingRead = 0;
            lbl_80384CD0.mPendingWrite = 0;
        }
        return 0;
    }
    lbl_80384CD0.mHandle = handle;
    lbl_80384CD0.mState = 21;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mSize = length;
    lbl_80384CD0.mResult = CARDWriteAsync(&lbl_80384CD0.mFileInfo, pBuffer, length, lbl_80384CD0.mPos, 0);
    if (lbl_80384CD0.mResult == CARD_RESULT_READY) {
        lbl_80384CD0.mBusy = 1;
    } else {
        lbl_80384CD0.mBusy = 0;
    }
    return 0;
}

int fn_801D56A0(int handle, char *pBuffer, int length)
{
    lbl_80384CD0.mUnknownD4 = 0;
    return fn_801D546C(handle, pBuffer, length);
}

int fn_801D56CC(void)
{
    return -1;
}

int fn_801D56D4(int handle, unsigned int *pSysInfo)
{
    lbl_80384CD0.mState = 23;
    lbl_80384CD0.mResult = -99;
    lbl_80384CD0.mHandle = handle;
    lbl_80384CD0.mBusy = 1;
    lbl_80384CD0.mStat.iconAddr = pSysInfo[0];
    lbl_80384CD0.mStat.commentAddr = pSysInfo[1];
    lbl_80384CD0.mResult = CARDSetStatusAsync(lbl_80384CD0.mPort, handle, &lbl_80384CD0.mStat, 0);
    if (lbl_80384CD0.mResult == CARD_RESULT_READY) {
        lbl_80384CD0.mBusy = 1;
    } else {
        lbl_80384CD0.mBusy = 0;
    }
    return 0;
}

void fn_801D5764(int type, char *pBuffer, int size)
{
    switch (type) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        sprintf(pBuffer, lbl_802AFE50);
        break;
    case 7:
        sprintf(pBuffer, lbl_802AFE50);
        break;
    case -1:
    case 0:
        sprintf(pBuffer, lbl_802AFE50);
        break;
    case 8:
        sprintf(pBuffer, lbl_802AFE5C);
        break;
    }
}

void fn_801D57E0(int port, char *pBuffer)
{
    sprintf(pBuffer, lbl_802AFE6C, fn_801D4204(port) + 'A');
}

int fn_801D5824(int enable, int size)
{
    if (enable) {
        lbl_803EBCF8 = size;
    } else {
        lbl_803EBCF8 = 0;
    }
    return 0;
}
