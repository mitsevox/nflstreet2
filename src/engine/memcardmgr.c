/* Memory-card manager: the layer between the game's save and load screens and the memorycard.c
   driver. It keeps the table of save-file types, sorts the card's directory into per-type slot
   tables, runs the asynchronous probe, load, save, delete and format operations as a state
   machine, and gives the screens each save's name, date and status. */

#include "engine/system.h"
#include "game/fn_801D2B7C.h"
#include "engine/memorycard.h"
#include <string.h>

typedef struct MemCardFileType_t {
    int mMaxFiles;
    int mUnknown4;
    char mCode[8];
    char *mPrefix;
} MemCardFileType_t;

typedef struct MemCardSlot_t {
    unsigned char mUsed;
    unsigned char mFlag;
    char mName[18];
    int mIndex;
    MemCDirEntry_t *mEntry;
} MemCardSlot_t;

typedef struct MemCardTypeSlots_t {
    signed char mCount;
    MemCardSlot_t *mSlots;
} MemCardTypeSlots_t;

typedef struct MemCardInfo_t {
    int mUnknown0;
    int mUnknown4;
    int mCardType[2];
    char mTypeName[12];
} MemCardInfo_t;

typedef struct MemCardHeader_t {
    char mData[0x40];
} MemCardHeader_t;

typedef struct MemCardOp_t {
    int mHandle;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mReadLength;
    int mSeekOffset;
    int mSeekWhence;
    unsigned char *mpData;
    char mCode[8];
    int mUnknown28;
    char mTitle[17];
    char mDescription[32];
    char mFileName[0x41];
    char mInfo[0x40];
    char mLastAction[8];
    char mAction[8];
    unsigned char mUnknownEE;
    unsigned char mUnknownEF;
    unsigned char mUnknownF0;
} MemCardOp_t;

typedef int (*MemCardGetNameFunc_t)(char *pBuffer, int size, void *pComment);
typedef void (*MemCardSysInfoFunc_t)(void);
typedef void (*MemCardGetIconFunc_t)(int arg0, unsigned char **ppData, unsigned int *pSize);
typedef void (*MemCardFreeIconFunc_t)(int arg0, int arg1);

static int _MemCardMgr_aModeStates[] = {
    0x1000, 0x1001, 0x1002, 0x1004, 0x100C, 0x100E, 0x1022, 0x1027,
    0x102F, 0x1031, 0x1033, 0x1035, 0x1037, 0x1039, 0x102D,
};

static unsigned int _MemCardMgr_uState = 0x103C;
static int _MemCardMgr_iIdleState = 1;
static signed char _MemCardMgr_cPollDelay = -1;
static int _MemCardMgr_iResult = 0;
static unsigned char _MemCardMgr_bResultReady = 0;
static int _MemCardMgr_iScanIndex = 0;
static unsigned char _MemCardMgr_bScanStarted = 0;
static unsigned char _MemCardMgr_bProbeStarted = 0;
static int _MemCardMgr_iNumTypes = 0;
static MemCardFileType_t *_MemCardMgr_pTypes = 0;
static int _MemCardMgr_iMaxEntries = 0;
static MemCDirEntry_t *_MemCardMgr_pDirEntries = 0;
static MemCardTypeSlots_t *_MemCardMgr_pTypeSlots = 0;
static MemCardGetNameFunc_t _MemCardMgr_pfnGetName = 0;
static MemCardSysInfoFunc_t _MemCardMgr_pfnSysInfo = 0;
static MemCardGetIconFunc_t _MemCardMgr_pfnGetIcon = 0;
static MemCardFreeIconFunc_t _MemCardMgr_pfnFreeIcon = 0;
static unsigned char _MemCardMgr_bUnusedFlag = 1;

static unsigned int _MemCardMgr_uScanPort;
static int _MemCardMgr_iPort;
static MemCardSlot_t **_MemCardMgr_ppEntrySlots;

static MemCardInfo_t _MemCardMgr_CardInfo;
static MemCardOp_t _MemCardMgr_Op;
static char _MemCardMgr_aHeaderBuffer[0x200] __attribute__((aligned(32)));

typedef struct Str3_t {
    char mText[3];
} Str3_t;

typedef struct Str4_t {
    char mText[4];
} Str4_t;

typedef struct Str6_t {
    char mText[6];
} Str6_t;

typedef struct Str5_t {
    char mText[5];
} Str5_t;

typedef struct Str7_t {
    char mText[7];
} Str7_t;


extern int MemCAsyncFormat(int port);
extern int MemCAsyncMount(int port);
extern int MemCAsyncMountAlt(int port, const char *pCode);
extern int MemCAsyncCheck(int port);
extern int MemCAsyncGetFreeSpace(int port);
extern int MemCAsyncGetFreeEntries(int port);
extern int MemCAsyncSeek(int handle, int offset, int whence);
extern int MemCAsyncGetSysInfo(int port, const char *pName, int size);
extern int MemCAsyncGetDir(int port, const char *pGameCode, const char *pPattern, MemCDirEntry_t *pEntries,
                           unsigned int maxEntries);


extern int MemCAsyncProbe(int port);

extern void *memset();
extern int memcmp(const void *pA, const void *pB, unsigned int count);
extern int sprintf(char *pBuffer, const char *pFormat, ...);

void MemCardMgrSetState(int state);
int MemCardMgrGetCardType(int port);
void MemCardMgrMakeFilePath(char *pBuffer, int size, const char *pName, const char *pUnused);
void MemCardMgrMakeEntryPath(char *pBuffer, int size, const char *pName);
void MemCardMgrMakeDirPattern(char *pBuffer, int size, const char *pName);
int MemCardMgrReadHeader(int handle);
int MemCardMgrGetNameFromHeader(int handle, int arg, char *pName, int size, MemCDirEntry_t *pEntry, MemCardGetNameFunc_t pFunc);
int MemCardMgrWriteSysInfo(int handle, int type, char *pTitle, int slot, MemCardSysInfoFunc_t pFunc);
void MemCardMgrFailOperation(int result);
void MemCardMgrFlushFile(void);
void MemCardMgrCloseFile(void);
void MemCardMgrDeleteFile(const char *pName, const char *pExtra);
void MemCardMgrOpenFile(void);
void MemCardMgrCreateFile(int size);
int MemCardMgrIsSlotCorrupt(int slot, int type);
void MemCardMgrBuildSlotTables(int count);
void MemCardMgrUpdateProbe(void);
void MemCardMgrFindFileType(const char *pName, int *pIndex);
void MemCardMgrGetFileSuffix(const char *pName, char *pOut);
void MemCardMgrCopyGameCode(char *pDst, const char *pSrc);
int MemCardMgrCompareGameCode(const char *pA, const char *pB);
void MemCardMgrFormatDate(char *pBuffer, int unused, MemCDirEntry_t *pEntry);
void MemCardMgrFormatCardType(int type, int port, char *pBuffer, int size);

void MemCardMgrSetState(int state)
{
    _MemCardMgr_uState = state;
}

void MemCardMgrFindFileType(const char *pName, int *pIndex)
{
    const char *pTitle;
    char *pPrefix;
    int length;

    for (*pIndex = 0; *pIndex < _MemCardMgr_iNumTypes; (*pIndex)++) {
        pTitle = pName + 7;
        if (pTitle != 0) {
            pPrefix = _MemCardMgr_pTypes[*pIndex].mPrefix;
            length = strlen(pPrefix);
            if (MemCardMgrCompareGameCode(_MemCardMgr_pTypes[*pIndex].mCode, _MemCardMgr_Op.mCode) == 0
                && strncmp(pTitle, pPrefix, length) == 0) {
                return;
            }
        }
    }
}

void MemCardMgrGetFileSuffix(const char *pName, char *pOut)
{
    const char *pTitle = pName + 7;
    char *pPrefix;
    int length;
    int i;

    if (pTitle == 0) {
        return;
    }
    for (i = 0; i < _MemCardMgr_iNumTypes; i++) {
        pPrefix = _MemCardMgr_pTypes[i].mPrefix;
        length = strlen(pPrefix);
        if (MemCardMgrCompareGameCode(_MemCardMgr_pTypes[i].mCode, _MemCardMgr_Op.mCode) == 0 && strncmp(pTitle, pPrefix, length) == 0) {
            strcpy(pOut, pTitle + length);
            return;
        }
    }
}

void MemCardMgrBuildSlotTables(int count)
{
    int i;
    int type;
    int n;

    if (_MemCardMgr_pTypeSlots != 0) {
        for (i = 0; i < _MemCardMgr_iNumTypes; i++) {
            if (_MemCardMgr_pTypeSlots[i].mSlots != 0) {
                fn_801D2BD0(_MemCardMgr_pTypeSlots[i].mSlots);
                _MemCardMgr_pTypeSlots[i].mSlots = 0;
            }
            _MemCardMgr_pTypeSlots[i].mCount = 0;
        }
    }
    for (i = 0; i < count; i++) {
        MemCardMgrFindFileType(_MemCardMgr_pDirEntries[i].mName, &type);
        if (type < _MemCardMgr_iNumTypes && MemCardMgrCompareGameCode(_MemCardMgr_pTypes[type].mCode, _MemCardMgr_Op.mCode) == 0
            && _MemCardMgr_pTypeSlots[type].mCount < _MemCardMgr_pTypes[type].mMaxFiles) {
            _MemCardMgr_pTypeSlots[type].mCount++;
        }
    }
    for (i = 0; i < count; i++) {
        MemCardMgrFindFileType(_MemCardMgr_pDirEntries[i].mName, &type);
        if (type < _MemCardMgr_iNumTypes) {
            if (MemCardMgrCompareGameCode(_MemCardMgr_pTypes[type].mCode, _MemCardMgr_Op.mCode) == 0) {
                if (_MemCardMgr_pTypeSlots[type].mSlots == 0) {
                    _MemCardMgr_pTypeSlots[type].mSlots = fn_801D2B7C(_MemCardMgr_pTypeSlots[type].mCount * sizeof(MemCardSlot_t), 0, 0);
                    _MemCardMgr_pTypeSlots[type].mCount = 0;
                }
                n = _MemCardMgr_pTypeSlots[type].mCount;
                if (n < _MemCardMgr_pTypes[type].mMaxFiles) {
                    _MemCardMgr_pTypeSlots[type].mSlots[n].mUsed = 1;
                    _MemCardMgr_pTypeSlots[type].mSlots[n].mFlag = 1;
                    _MemCardMgr_pTypeSlots[type].mSlots[n].mEntry = &_MemCardMgr_pDirEntries[i];
                    _MemCardMgr_pTypeSlots[type].mSlots[n].mIndex = i;
                    _MemCardMgr_ppEntrySlots[i] = &_MemCardMgr_pTypeSlots[type].mSlots[n];
                    _MemCardMgr_pTypeSlots[type].mCount++;
                }
            }
        } else {
            _MemCardMgr_ppEntrySlots[i] = 0;
        }
    }
}

void MemCardMgrUpdateProbe(void)
{
    int result = -1;

    switch (_MemCardMgr_uState) {
    case 0x102F:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            MemCAsyncProbe(_MemCardMgr_iPort);
            MemCardMgrSetState(0x1030);
        }
        break;
    case 0x1030:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                _MemCardMgr_CardInfo.mCardType[_MemCardMgr_iPort] = result;
            } else {
                _MemCardMgr_CardInfo.mCardType[_MemCardMgr_iPort] = 0;
            }
            MemCardMgrFormatCardType(MemCardMgrGetCardType(_MemCardMgr_iPort), _MemCardMgr_iPort, _MemCardMgr_CardInfo.mTypeName, sizeof(_MemCardMgr_CardInfo.mTypeName));
            _MemCardMgr_iResult = result;
            _MemCardMgr_bResultReady = 1;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    }
}

void MemCardMgrFailOperation(int result)
{
    SysEnableReset(1);
    if (result == -2) {
        _MemCardMgr_iResult = result;
        _MemCardMgr_bResultReady = 1;
        strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
        MemCardMgrSetState(_MemCardMgr_iIdleState);
    } else {
        _MemCardMgr_iResult = result;
        _MemCardMgr_bResultReady = 1;
        strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
        MemCardMgrSetState(_MemCardMgr_iIdleState);
    }
}

void MemCardMgrFlushFile(void)
{
    MemCAsyncFlush(_MemCardMgr_Op.mHandle);
}

void MemCardMgrCloseFile(void)
{
    MemCAsyncClose(_MemCardMgr_Op.mHandle);
}

void MemCardMgrDeleteFile(const char *pName, const char *pExtra)
{
    MemCardMgrMakeFilePath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), pName, pExtra);
    MemCAsyncDelete(_MemCardMgr_iPort, _MemCardMgr_Op.mFileName);
}

void MemCardMgrOpenFile(void)
{
    MemCAsyncOpen(_MemCardMgr_iPort, _MemCardMgr_Op.mFileName, 4, 0, 0);
}

void MemCardMgrCreateFile(int size)
{
    MemCAsyncOpen(_MemCardMgr_iPort, _MemCardMgr_Op.mFileName, 4, 1, size);
}

unsigned int MemCardMgrPackDate(MemCDirEntry_t *pEntry)
{
    return ((pEntry->mYear - 2000) << 26) | ((pEntry->mMonth & 0xF) << 22) | ((pEntry->mDay & 0x1F) << 17)
         | ((pEntry->mHour & 0x1F) << 12) | ((pEntry->mMinute & 0x3F) << 6) | (pEntry->mSecond & 0x3F);
}

void MemCardMgrInit(void)
{
    int i;

    memset(&_MemCardMgr_Op, 0, sizeof(_MemCardMgr_Op));
    _MemCardMgr_uState = 0x1001;
    _MemCardMgr_iIdleState = 0;
    MemCInit();
    for (i = 1; i >= 0; i--) {
        _MemCardMgr_CardInfo.mCardType[i] = -1;
    }
    _MemCardMgr_iPort = -1;
    _MemCardMgr_bScanStarted = 0;
    _MemCardMgr_bProbeStarted = 0;
}

void MemCardMgrShutdown(void)
{
    int result = 0;

    while (MemCAsyncPoll(&result) == 0) {
    }
    _MemCardMgr_uState = 0x103C;
    MemCShutdown();
    _MemCardMgr_iPort = -1;
    _MemCardMgr_bScanStarted = 0;
    _MemCardMgr_bProbeStarted = 0;
}

void MemCardMgrEnablePolling(int enable)
{
    int result;

    if (enable) {
        if (_MemCardMgr_iIdleState == 0x1000) {
            _MemCardMgr_cPollDelay = 6;
        } else {
            _MemCardMgr_cPollDelay = 1;
        }
    } else {
        // FAKEMATCH: dead test and increment of the flag; the join it leaves
        // ends cse's jump equivalence enable == 0, so the zero is stored with li.
        if (_MemCardMgr_iIdleState) enable++;
        result = 0;
        while (MemCAsyncPoll(&result) == 0) {
        }
        _MemCardMgr_cPollDelay = -1;
    }
}

void MemCardMgrSetIdleMode(int mode)
{
    _MemCardMgr_iIdleState = _MemCardMgr_aModeStates[mode];
    if (_MemCardMgr_iIdleState == 0x1000 && _MemCardMgr_uState != 0x1000) {
        MemCardMgrSetState(0x1000);
    }
    if (_MemCardMgr_iIdleState == 0x1001 && _MemCardMgr_uState != 0x1001) {
        MemCardMgrSetState(0x1001);
    }
}

int MemCardMgrGetResult(int *pResult)
{
    if (_MemCardMgr_bResultReady) {
        *pResult = _MemCardMgr_iResult;
        _MemCardMgr_bResultReady = 0;
        return 1;
    }
    return 0;
}

void MemCardMgrStartOperation(int mode)
{
    MemCardMgrSetState(_MemCardMgr_aModeStates[mode]);
}

void MemCardMgrUnmount(int port)
{
    int i;

    if (_MemCardMgr_pTypeSlots != 0) {
        for (i = 0; i < _MemCardMgr_iNumTypes; i++) {
            if (_MemCardMgr_pTypeSlots[i].mSlots != 0) {
                fn_801D2BD0(_MemCardMgr_pTypeSlots[i].mSlots);
                _MemCardMgr_pTypeSlots[i].mSlots = 0;
            }
            _MemCardMgr_pTypeSlots[i].mCount = 0;
        }
    }
    MemCUnMount(port);
}

void MemCardMgrSetPort(int port)
{
    _MemCardMgr_iPort = port;
}

int MemCardMgrGetPort(void)
{
    return _MemCardMgr_iPort;
}

int MemCardMgrGetFreeSpace(void)
{
    return _MemCardMgr_CardInfo.mUnknown0;
}

int MemCardMgrGetFreeEntries(void)
{
    return _MemCardMgr_CardInfo.mUnknown4;
}

int MemCardMgrGetCardType(int port)
{
    return _MemCardMgr_CardInfo.mCardType[port];
}

void MemCardMgrSetFileType(int value)
{
    _MemCardMgr_Op.mUnknown4 = value;
}

void MemCardMgrSetFileSize(int value)
{
    _MemCardMgr_Op.mUnknown8 = value;
}

void MemCardMgrSetFileHeader(MemCardHeader_t *pInfo)
{
    if (pInfo != 0) {
        *(MemCardHeader_t *)_MemCardMgr_Op.mInfo = *pInfo;
    }
}

void MemCardMgrSetFileStrings(const char *pTitle, const char *pDescription)
{
    if (pTitle != 0) {
        strcpy(_MemCardMgr_Op.mTitle, pTitle);
    }
    if (pDescription != 0) {
        strcpy(_MemCardMgr_Op.mDescription, pDescription);
    }
}

void MemCardMgrSetSlot(int value)
{
    _MemCardMgr_Op.mUnknownC = value;
}

int MemCardMgrGetSlot(void)
{
    return _MemCardMgr_Op.mUnknownC;
}

int MemCardMgrGetFileType(void)
{
    return _MemCardMgr_Op.mUnknown4;
}

void MemCardMgrSetGameCode(const char *pCode, int flag)
{
    MemCardMgrCopyGameCode(_MemCardMgr_Op.mCode, pCode);
    _MemCardMgr_Op.mUnknownEE = flag;
}

void MemCardMgrBuildFileName(const char *pSuffix, const char *pPrefix, int unused, int type, char *pOut, int size)
{
    char name[32];

    strcpy(name, _MemCardMgr_pTypes[type].mPrefix);
    sprintf(pOut, "%s%s%s", pPrefix, name, pSuffix);
    /* FAKEMATCH: the target keeps the unreferenced string "%s-%s" (0x802AFED8) right after "%s%s%s";
       this never-executed call keeps it there with no code (see the evidence.tsv source-form row) */
    if (0) {
        sprintf(pOut, "%s-%s", name, pSuffix);
    }
}

void MemCardMgrSetFileOptions(int a, int b)
{
    _MemCardMgr_Op.mUnknownEF = a;
    _MemCardMgr_Op.mUnknownF0 = b;
}

char *MemCardMgrGetLastAction(void)
{
    return _MemCardMgr_Op.mLastAction;
}

void MemCardMgrSetCallbacks(MemCardGetNameFunc_t a, MemCardSysInfoFunc_t b, MemCardGetIconFunc_t c, MemCardFreeIconFunc_t d)
{
    _MemCardMgr_pfnGetName = a;
    _MemCardMgr_pfnSysInfo = b;
    _MemCardMgr_pfnGetIcon = c;
    _MemCardMgr_pfnFreeIcon = d;
}

void MemCardMgrSetFileTypes(MemCardFileType_t *pTypes, int count)
{
    int i;

    if (_MemCardMgr_pDirEntries != 0) {
        fn_801D2BD0(_MemCardMgr_pDirEntries);
        _MemCardMgr_pDirEntries = 0;
    }
    if (_MemCardMgr_ppEntrySlots != 0) {
        fn_801D2BD0(_MemCardMgr_ppEntrySlots);
        _MemCardMgr_ppEntrySlots = 0;
    }
    if (_MemCardMgr_pTypeSlots != 0) {
        for (i = 0; i < _MemCardMgr_iNumTypes; i++) {
            if (_MemCardMgr_pTypeSlots[i].mSlots != 0) {
                fn_801D2BD0(_MemCardMgr_pTypeSlots[i].mSlots);
                _MemCardMgr_pTypeSlots[i].mSlots = 0;
            }
        }
        fn_801D2BD0(_MemCardMgr_pTypeSlots);
        _MemCardMgr_pTypeSlots = 0;
    }
    _MemCardMgr_iNumTypes = count;
    _MemCardMgr_iMaxEntries = 0;
    _MemCardMgr_pTypes = pTypes;
    for (i = 0; i < count; i++) {
        _MemCardMgr_iMaxEntries += pTypes[i].mMaxFiles;
    }
    _MemCardMgr_pDirEntries = fn_801D2B7C(_MemCardMgr_iMaxEntries * sizeof(MemCDirEntry_t), 0, 0);
    _MemCardMgr_ppEntrySlots = fn_801D2B7C(_MemCardMgr_iMaxEntries * sizeof(MemCardSlot_t *), 0, 0);
    _MemCardMgr_pTypeSlots = fn_801D2B7C(_MemCardMgr_iNumTypes * sizeof(MemCardTypeSlots_t), 0, 0);
    memset(_MemCardMgr_pDirEntries, 0, _MemCardMgr_iMaxEntries * sizeof(MemCDirEntry_t));
    memset(_MemCardMgr_ppEntrySlots, 0, _MemCardMgr_iMaxEntries * sizeof(MemCardSlot_t *));
    memset(_MemCardMgr_pTypeSlots, 0, _MemCardMgr_iNumTypes * sizeof(MemCardTypeSlots_t));
}

int MemCardMgrCountFiles(int type)
{
    int count;
    int i;

    if (type == -1) {
        count = 0;
        for (i = 0; i < _MemCardMgr_iMaxEntries; i++) {
            count += _MemCardMgr_pTypeSlots[i].mCount;
        }
        return count;
    }
    return _MemCardMgr_pTypeSlots[type].mCount;
}

int MemCardMgrGetMaxFiles(int type)
{
    return _MemCardMgr_pTypes[type].mMaxFiles;
}

void MemCardMgrGetFileTitle(char *pDst, int size)
{
    strcpy(pDst, _MemCardMgr_Op.mTitle);
}

void MemCardMgrGetFileName(char *pDst, int size)
{
    strcpy(pDst, _MemCardMgr_Op.mDescription);
}

int MemCardMgrGetSlotInfo(int slot, int type, char *pName, int nameSize, char *pDate, int dateArg, unsigned char *pFlag)
{
    int used = 0;
    MemCardSlot_t *pSlot;

    if (slot < _MemCardMgr_pTypeSlots[type].mCount) {
        if (_MemCardMgr_pTypeSlots[type].mSlots[slot].mUsed) {
            pSlot = &_MemCardMgr_pTypeSlots[type].mSlots[slot];
            used = pSlot->mUsed;
            if (pName != 0) {
                if (pSlot->mFlag) {
                    *(Str4_t *)pName = *(const Str4_t *)"???";
                } else {
                    strcpy(pName, pSlot->mName);
                }
            }
            if (pDate != 0) {
                MemCardMgrFormatDate(pDate, dateArg, _MemCardMgr_pTypeSlots[type].mSlots[slot].mEntry);
            }
            if (pFlag != 0) {
                *pFlag = _MemCardMgr_pTypeSlots[type].mSlots[slot].mFlag;
            }
        }
    }
    return used;
}

int MemCardMgrGetSlotEntryName(int slot, int type, char *pDst, int count)
{
    return (int)strnzcpy(pDst, _MemCardMgr_pTypeSlots[type].mSlots[slot].mEntry->mName, count);
}

unsigned int MemCardMgrGetSlotDate(int slot, int type)
{
    return MemCardMgrPackDate(_MemCardMgr_pTypeSlots[type].mSlots[slot].mEntry);
}

int MemCardMgrFindSlot(const char *pName, int type, unsigned char *pFlag)
{
    signed char i;

    for (i = 0; i < _MemCardMgr_pTypeSlots[type].mCount; i++) {
        if (strcmp(_MemCardMgr_pTypeSlots[type].mSlots[i].mName, pName) == 0) {
            *pFlag = _MemCardMgr_pTypeSlots[type].mSlots[i].mFlag;
            return i;
        }
    }
    *pFlag = 0;
    return -1;
}

int MemCardMgrIsSlotCorrupt(int slot, int type)
{
    if (slot < _MemCardMgr_pTypeSlots[type].mCount) {
        return _MemCardMgr_pTypeSlots[type].mSlots[slot].mFlag;
    }
    return 0;
}

void MemCardMgrMarkSlotCorrupt(int slot, int type)
{
    _MemCardMgr_pTypeSlots[type].mSlots[slot].mFlag = 1;
}

void MemCardMgrSetStreamError(int value)
{
    _MemCardMgr_Op.mUnknown28 = value;
}

void MemCardMgrStreamWrite(char *pBuffer, int length)
{
    if (_MemCardMgr_uState == 0x1011) {
        MemCAsyncWrite(_MemCardMgr_Op.mHandle, pBuffer, length);
        MemCardMgrSetState(0x1012);
    }
}

void MemCardMgrStreamRead(char *pBuffer, int length)
{
    if (_MemCardMgr_uState == 0x1006) {
        _MemCardMgr_Op.mReadLength = length;
        MemCAsyncRead(_MemCardMgr_Op.mHandle, pBuffer, length);
        MemCardMgrSetState(0x1007);
    }
}

int MemCardMgrIsStreamReady(unsigned char *pIdle)
{
    if (pIdle != 0) {
        switch (_MemCardMgr_uState) {
        case 0x1006:
        case 0x1007:
        case 0x1008:
        case 0x1009:
        case 0x1011:
        case 0x1012:
        case 0x1013:
        case 0x1014:
            *pIdle = 0;
            break;
        default:
            *pIdle = 1;
            break;
        }
    }
    return _MemCardMgr_uState == 0x1011 || _MemCardMgr_uState == 0x1006;
}

void MemCardMgrEndStream(void)
{
    if (_MemCardMgr_uState == 0x1011) {
        MemCAsyncFlush(_MemCardMgr_Op.mHandle);
        MemCardMgrSetState(0x1015);
    } else if (_MemCardMgr_uState == 0x1006) {
        MemCAsyncFlush(_MemCardMgr_Op.mHandle);
        MemCardMgrSetState(0x100A);
    }
}

void MemCardMgrUpdate(void)
{
    int error;
    MemCardSlot_t *pSlot;
    char name[65];
    int poll = -1;
    int result = -1;
    unsigned int size;
    unsigned int writeSize;
    unsigned int headerSize;
    int type;

    SysCheckReset();
    switch (_MemCardMgr_uState) {
    case 0x1000:
        if (_MemCardMgr_cPollDelay == 0) {
            poll = MemCAsyncPoll(&result);
            if (!_MemCardMgr_bProbeStarted && poll == 1) {
                poll = -1;
            }
            if (poll == 1) {
                if (_MemCardMgr_iPort >= 0 && _MemCardMgr_iPort <= 1) {
                    _MemCardMgr_bProbeStarted = poll;
                    MemCAsyncProbe(_MemCardMgr_iPort);
                }
            } else if (poll == -1) {
                if (_MemCardMgr_iPort >= 0 && _MemCardMgr_iPort <= 1) {
                    _MemCardMgr_bProbeStarted = 1;
                    MemCAsyncProbe(_MemCardMgr_iPort);
                }
            }
            _MemCardMgr_cPollDelay = 6;
        } else if (_MemCardMgr_cPollDelay > 0) {
            _MemCardMgr_cPollDelay--;
        }
        break;
    case 0x1001:
        *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
        if (_MemCardMgr_cPollDelay == 0) {
            poll = MemCAsyncPoll(&result);
            if (!_MemCardMgr_bScanStarted && poll == 1) {
                poll = -1;
            }
            if (poll == 1) {
                if (result >= 0) {
                    _MemCardMgr_CardInfo.mCardType[_MemCardMgr_uScanPort] = result;
                    if (_MemCardMgr_iPort == -1) {
                        _MemCardMgr_iPort = _MemCardMgr_uScanPort;
                    }
                } else {
                    _MemCardMgr_CardInfo.mCardType[_MemCardMgr_uScanPort] = 0;
                }
                _MemCardMgr_uScanPort++;
                if (_MemCardMgr_uScanPort > 1) {
                    _MemCardMgr_uScanPort = 0;
                }
                _MemCardMgr_bScanStarted = 1;
                MemCAsyncProbe(_MemCardMgr_uScanPort);
            } else if (poll == -1) {
                _MemCardMgr_uScanPort = 0;
                _MemCardMgr_bScanStarted = 1;
                MemCAsyncProbe(0);
            }
            _MemCardMgr_cPollDelay = 1;
        } else if (_MemCardMgr_cPollDelay > 0) {
            _MemCardMgr_cPollDelay--;
        }
        break;
    case 0x1002:
        if (MemCAsyncPoll(&result)) {
            *(Str7_t *)_MemCardMgr_Op.mAction = *(const Str7_t *)"Format";
            _MemCardMgr_iResult = 0;
            MemCAsyncFormat(_MemCardMgr_iPort);
            MemCardMgrSetState(0x1003);
        }
        break;
    case 0x1003:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                _MemCardMgr_bResultReady = 1;
                _MemCardMgr_iResult = 1;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1004:
        if (MemCAsyncPoll(&result)) {
            *(Str5_t *)_MemCardMgr_Op.mAction = *(const Str5_t *)"Load";
            _MemCardMgr_iResult = 0;
            MemCardMgrMakeFilePath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), _MemCardMgr_Op.mDescription,
                        _MemCardMgr_Op.mDescription);
            MemCardMgrOpenFile();
            MemCardMgrSetState(0x1005);
        }
        break;
    case 0x1005:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                _MemCardMgr_Op.mHandle = result;
                _MemCardMgr_Op.mUnknown28 = 0;
                size = 0;
                if (_MemCardMgr_Op.mUnknownF0) {
                    _MemCardMgr_pfnGetIcon(_MemCardMgr_Op.mUnknown4, 0, &size);
                }
                if (_MemCardMgr_Op.mUnknownEF) {
                    size += 0x40;
                }
                if ((int)size > 0) {
                    _MemCardMgr_Op.mSeekWhence = 0;
                    _MemCardMgr_Op.mSeekOffset = size;
                    MemCardMgrFlushFile();
                    MemCardMgrSetState(0x1008);
                } else {
                    MemCardMgrSetState(0x1006);
                }
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1006:
        break;
    case 0x1007:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                if (result == _MemCardMgr_Op.mReadLength) {
                    MemCardMgrSetState(0x1006);
                    break;
                }
                _MemCardMgr_pTypeSlots[_MemCardMgr_Op.mUnknown4].mSlots[_MemCardMgr_Op.mUnknownC].mFlag = poll;
                MemCardMgrFlushFile();
                MemCardMgrSetState(0x100A);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x100B);
            }
        }
        break;
    case 0x1008:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCAsyncSeek(_MemCardMgr_Op.mHandle, _MemCardMgr_Op.mSeekOffset, _MemCardMgr_Op.mSeekWhence);
                MemCardMgrSetState(0x1009);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x100B);
            }
        }
        break;
    case 0x1009:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrSetState(0x1006);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x100B);
            }
        }
        break;
    case 0x100A:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                _MemCardMgr_iResult = result;
            }
            MemCardMgrCloseFile();
            MemCardMgrSetState(0x100B);
        }
        break;
    case 0x100B:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                if ((error = _MemCardMgr_iResult) != 0) {
                    MemCardMgrFailOperation(error);
                    break;
                }
                if (_MemCardMgr_Op.mUnknown28 != 0) {
                    MemCardMgrFailOperation(_MemCardMgr_Op.mUnknown28);
                    break;
                }
                if (MemCardMgrIsSlotCorrupt(_MemCardMgr_Op.mUnknownC, _MemCardMgr_Op.mUnknown4) == 0) {
                    _MemCardMgr_iResult = error;
                } else {
                    _MemCardMgr_iResult = -100;
                }
                _MemCardMgr_bResultReady = 1;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else {
                if ((error = _MemCardMgr_iResult) != 0) {
                    MemCardMgrFailOperation(error);
                } else {
                    MemCardMgrFailOperation(result);
                }
            }
        }
        break;
    case 0x100C:
        if (MemCAsyncPoll(&result)) {
            *(Str5_t *)_MemCardMgr_Op.mAction = *(const Str5_t *)"Save";
            _MemCardMgr_iResult = 0;
            SysEnableReset(0);
            MemCardMgrDeleteFile(_MemCardMgr_Op.mDescription, "");
            MemCardMgrSetState(0x100D);
        }
        break;
    case 0x100D:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrMakeFilePath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), _MemCardMgr_Op.mDescription,
                            _MemCardMgr_Op.mDescription);
                MemCardMgrCreateFile(_MemCardMgr_Op.mUnknown8);
                MemCardMgrSetState(0x1010);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x100E:
        if (MemCAsyncPoll(&result)) {
            *(Str5_t *)_MemCardMgr_Op.mAction = *(const Str5_t *)"Save";
            _MemCardMgr_iResult = 0;
            SysEnableReset(0);
            MemCardMgrSetState(0x100F);
        }
        break;
    case 0x100F:
        result = 0;
        MemCardMgrMakeFilePath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), _MemCardMgr_Op.mDescription,
                    _MemCardMgr_Op.mDescription);
        MemCardMgrCreateFile(_MemCardMgr_Op.mUnknown8);
        MemCardMgrSetState(0x1010);
        break;
    case 0x1010:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                _MemCardMgr_Op.mHandle = result;
                _MemCardMgr_Op.mUnknown28 = 0;
                if (_MemCardMgr_Op.mUnknownEF) {
                    MemCAsyncWrite(_MemCardMgr_Op.mHandle, _MemCardMgr_Op.mInfo, sizeof(_MemCardMgr_Op.mInfo));
                    MemCardMgrSetState(0x101B);
                } else {
                    MemCardMgrSetState(0x1011);
                }
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1011:
        break;
    case 0x1012:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrSetState(0x1011);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x1016);
            }
        }
        break;
    case 0x1013:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCAsyncSeek(_MemCardMgr_Op.mHandle, _MemCardMgr_Op.mSeekOffset, _MemCardMgr_Op.mSeekWhence);
                MemCardMgrSetState(0x1014);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x1016);
            }
        }
        break;
    case 0x1014:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrSetState(0x1011);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x1016);
            }
        }
        break;
    case 0x1015:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrWriteSysInfo(_MemCardMgr_Op.mHandle, _MemCardMgr_Op.mUnknown4, _MemCardMgr_Op.mTitle, _MemCardMgr_Op.mUnknownC,
                            _MemCardMgr_pfnSysInfo);
                MemCardMgrSetState(0x101F);
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x1016);
            }
        }
        break;
    case 0x1016:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                if ((error = _MemCardMgr_iResult) != 0) {
                    MemCardMgrFailOperation(error);
                    break;
                }
                if (_MemCardMgr_Op.mUnknown28 != 0) {
                    MemCardMgrFailOperation(_MemCardMgr_Op.mUnknown28);
                    break;
                }
                SysEnableReset(1);
                _MemCardMgr_bResultReady = poll;
                _MemCardMgr_iResult = poll;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else {
                if ((error = _MemCardMgr_iResult) != 0) {
                    MemCardMgrFailOperation(error);
                } else {
                    MemCardMgrFailOperation(result);
                }
            }
        }
        break;
    case 0x1017:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                _MemCardMgr_Op.mHandle = result;
                _MemCardMgr_pfnGetIcon(_MemCardMgr_Op.mUnknown4, &_MemCardMgr_Op.mpData, &writeSize);
                MemCAsyncWrite(_MemCardMgr_Op.mHandle, (char *)_MemCardMgr_Op.mpData, writeSize);
                MemCardMgrSetState(0x1018);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1018:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                if (_MemCardMgr_Op.mUnknownF0) {
                    _MemCardMgr_pfnFreeIcon(_MemCardMgr_Op.mUnknown4, (int)_MemCardMgr_Op.mpData);
                    _MemCardMgr_Op.mpData = 0;
                    MemCardMgrSetState(0x1011);
                } else {
                    MemCardMgrFlushFile();
                    MemCardMgrSetState(0x1019);
                }
            } else {
                _MemCardMgr_pfnFreeIcon(_MemCardMgr_Op.mUnknown4, (int)_MemCardMgr_Op.mpData);
                _MemCardMgr_Op.mpData = 0;
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                if (_MemCardMgr_Op.mUnknownF0) {
                    MemCardMgrSetState(0x1016);
                } else {
                    MemCardMgrSetState(0x101A);
                }
            }
        }
        break;
    case 0x1019:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                _MemCardMgr_pfnFreeIcon(_MemCardMgr_Op.mUnknown4, (int)_MemCardMgr_Op.mpData);
                _MemCardMgr_Op.mpData = 0;
                _MemCardMgr_iResult = result;
            }
            MemCardMgrCloseFile();
            MemCardMgrSetState(0x101A);
        }
        break;
    case 0x101A:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                error = _MemCardMgr_iResult;
                if (error == 0) {
                    _MemCardMgr_pfnFreeIcon(_MemCardMgr_Op.mUnknown4, (int)_MemCardMgr_Op.mpData);
                    _MemCardMgr_Op.mpData = (unsigned char *)error;
                    SysEnableReset(1);
                    _MemCardMgr_bResultReady = poll;
                    _MemCardMgr_iResult = poll;
                    strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                    MemCardMgrSetState(_MemCardMgr_iIdleState);
                    break;
                }
            }
            _MemCardMgr_pfnFreeIcon(_MemCardMgr_Op.mUnknown4, (int)_MemCardMgr_Op.mpData);
            _MemCardMgr_Op.mpData = 0;
            if (_MemCardMgr_iResult != 0) {
                MemCardMgrFailOperation(_MemCardMgr_iResult);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x101C:
        MemCardMgrMakeFilePath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), _MemCardMgr_Op.mDescription,
                    _MemCardMgr_Op.mDescription);
        MemCAsyncGetSysInfo(_MemCardMgr_iPort, _MemCardMgr_Op.mFileName, 11);
        MemCardMgrSetState(0x101D);
        break;
    case 0x101D:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrMakeEntryPath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), _MemCardMgr_Op.mDescription);
                MemCardMgrCreateFile(0);
                MemCardMgrSetState(0x101E);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x101E:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                _MemCardMgr_Op.mHandle = result;
                MemCardMgrWriteSysInfo(_MemCardMgr_Op.mHandle, _MemCardMgr_Op.mUnknown4, _MemCardMgr_Op.mTitle, _MemCardMgr_Op.mUnknownC,
                            _MemCardMgr_pfnSysInfo);
                MemCardMgrSetState(0x101F);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x101F:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                _MemCardMgr_iResult = result;
            }
            MemCardMgrCloseFile();
            MemCardMgrSetState(0x1016);
        }
        break;
    case 0x101B:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                if (_MemCardMgr_Op.mUnknownF0) {
                    _MemCardMgr_pfnGetIcon(_MemCardMgr_Op.mUnknown4, &_MemCardMgr_Op.mpData, &headerSize);
                    MemCAsyncWrite(_MemCardMgr_Op.mHandle, (char *)_MemCardMgr_Op.mpData, headerSize);
                    MemCardMgrSetState(0x1018);
                } else {
                    MemCardMgrSetState(0x1011);
                }
            } else {
                _MemCardMgr_iResult = result;
                MemCardMgrCloseFile();
                MemCardMgrSetState(0x1016);
            }
        }
        break;
    case 0x1020:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                _MemCardMgr_iResult = result;
            }
            MemCardMgrCloseFile();
            MemCardMgrSetState(0x1021);
        }
        break;
    case 0x1021:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                if ((error = _MemCardMgr_iResult) != 0) {
                    MemCardMgrFailOperation(error);
                    break;
                }
                SysEnableReset(1);
                _MemCardMgr_bResultReady = poll;
                _MemCardMgr_iResult = poll;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else {
                if ((error = _MemCardMgr_iResult) != 0) {
                    MemCardMgrFailOperation(error);
                } else {
                    MemCardMgrFailOperation(result);
                }
            }
        }
        break;
    case 0x1022:
        if (MemCAsyncPoll(&result)) {
            *(Str7_t *)_MemCardMgr_Op.mAction = *(const Str7_t *)"Delete";
            _MemCardMgr_iResult = 0;
            SysEnableReset(0);
            MemCardMgrDeleteFile(_MemCardMgr_Op.mDescription, _MemCardMgr_Op.mDescription);
            MemCardMgrSetState(0x1025);
        }
        break;
    case 0x1023:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0 && result != -3) {
                MemCardMgrFailOperation(result);
                break;
            }
            MemCardMgrDeleteFile(_MemCardMgr_Op.mDescription, "");
            MemCardMgrSetState(0x1024);
        }
        break;
    case 0x1024:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0 && result != -3) {
                MemCardMgrFailOperation(result);
                break;
            }
            MemCardMgrDeleteFile(_MemCardMgr_Op.mDescription, _MemCardMgr_Op.mDescription);
            MemCardMgrSetState(0x1025);
        }
        break;
    case 0x1025:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                SysEnableReset(1);
                _MemCardMgr_bResultReady = poll;
                _MemCardMgr_iResult = poll;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else if (result == -3) {
                SysEnableReset(1);
                _MemCardMgr_bResultReady = poll;
                _MemCardMgr_iResult = poll;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1026:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                SysEnableReset(1);
                _MemCardMgr_bResultReady = poll;
                _MemCardMgr_iResult = poll;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else if (result == -3) {
                SysEnableReset(1);
                _MemCardMgr_bResultReady = poll;
                _MemCardMgr_iResult = poll;
                strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
                MemCardMgrSetState(_MemCardMgr_iIdleState);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1027:
    case 0x102D:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            memset(_MemCardMgr_pDirEntries, 0, _MemCardMgr_iMaxEntries * sizeof(MemCDirEntry_t));
            MemCardMgrMakeDirPattern(name, sizeof(name), _MemCardMgr_Op.mCode);
            if (_MemCardMgr_uState == 0x1027) {
                MemCAsyncGetDir(_MemCardMgr_iPort, name, name, _MemCardMgr_pDirEntries, _MemCardMgr_iMaxEntries);
                MemCardMgrSetState(0x1028);
            } else {
                char pattern[1] = "*";

                MemCAsyncGetDir(_MemCardMgr_iPort, name, pattern, _MemCardMgr_pDirEntries, _MemCardMgr_iMaxEntries);
                MemCardMgrSetState(0x102E);
            }
        }
        break;
    case 0x1028:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrBuildSlotTables(result);
                _MemCardMgr_bResultReady = 0;
                _MemCardMgr_iResult = result;
                _MemCardMgr_iScanIndex = 0;
                MemCardMgrSetState(0x1029);
            } else {
                MemCardMgrFailOperation(result);
            }
        }
        break;
    case 0x1029:
        if (_MemCardMgr_iScanIndex < _MemCardMgr_iResult) {
            pSlot = _MemCardMgr_ppEntrySlots[_MemCardMgr_iScanIndex];
            if (pSlot != 0) {
                pSlot->mFlag = 1;
                MemCardMgrGetFileSuffix(_MemCardMgr_pDirEntries[_MemCardMgr_iScanIndex].mName, pSlot->mName);
                MemCardMgrMakeEntryPath(_MemCardMgr_Op.mFileName, sizeof(_MemCardMgr_Op.mFileName), _MemCardMgr_pDirEntries[_MemCardMgr_iScanIndex].mName);
                MemCardMgrOpenFile();
                MemCardMgrSetState(0x102A);
            } else {
                _MemCardMgr_iScanIndex++;
                MemCardMgrSetState(0x1029);
            }
        } else {
            _MemCardMgr_bResultReady = 1;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    case 0x102A:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                _MemCardMgr_Op.mHandle = result;
                MemCardMgrReadHeader(result);
                MemCardMgrSetState(0x102B);
                break;
            }
            if (result == -2) {
                MemCardMgrFailOperation(-2);
                break;
            }
            _MemCardMgr_iScanIndex++;
            MemCardMgrSetState(0x1029);
        }
        break;
    case 0x102B:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                type = 0;
                pSlot = _MemCardMgr_ppEntrySlots[_MemCardMgr_iScanIndex];
                MemCardMgrFindFileType(pSlot->mEntry->mName, &type);
                pSlot->mFlag = MemCardMgrGetNameFromHeader(result, _MemCardMgr_pTypes[type].mUnknown4, pSlot->mName, 17, pSlot->mEntry,
                                           _MemCardMgr_pfnGetName);
            }
            MemCardMgrCloseFile();
            MemCardMgrSetState(0x102C);
        }
        break;
    case 0x102C:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                if (result == -2) {
                    MemCardMgrFailOperation(-2);
                    break;
                }
            }
            _MemCardMgr_iScanIndex++;
            MemCardMgrSetState(0x1029);
        }
        break;
    case 0x102E:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            _MemCardMgr_iResult = result;
            _MemCardMgr_bResultReady = poll;
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    case 0x102F:
    case 0x1030:
        MemCardMgrUpdateProbe();
        break;
    case 0x1031:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            MemCAsyncMount(_MemCardMgr_iPort);
            MemCardMgrSetState(0x1032);
        }
        break;
    case 0x1032:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            MemCardMgrFormatCardType(MemCardMgrGetCardType(_MemCardMgr_iPort), _MemCardMgr_iPort, _MemCardMgr_CardInfo.mTypeName, sizeof(_MemCardMgr_CardInfo.mTypeName));
            _MemCardMgr_bResultReady = poll;
            _MemCardMgr_iResult = result;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    case 0x1033:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            MemCAsyncMountAlt(_MemCardMgr_iPort, _MemCardMgr_Op.mCode);
            MemCardMgrSetState(0x1034);
        }
        break;
    case 0x1034:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            _MemCardMgr_bResultReady = poll;
            _MemCardMgr_iResult = result;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    case 0x1035:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            MemCAsyncCheck(_MemCardMgr_iPort);
            MemCardMgrSetState(0x1036);
        }
        break;
    case 0x1036:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            _MemCardMgr_bResultReady = poll;
            _MemCardMgr_iResult = result;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    case 0x1037:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            MemCAsyncGetFreeSpace(_MemCardMgr_iPort);
            MemCardMgrSetState(0x1038);
        }
        break;
    case 0x1038:
        if (MemCAsyncPoll(&result) == 1) {
            _MemCardMgr_iResult = result;
            if (result >= 0) {
                _MemCardMgr_CardInfo.mUnknown0 = result;
            } else {
                _MemCardMgr_CardInfo.mUnknown0 = 0;
            }
            _MemCardMgr_bResultReady = 1;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    case 0x1039:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)_MemCardMgr_Op.mAction = *(const Str6_t *)"Check";
            _MemCardMgr_iResult = 0;
            MemCAsyncGetFreeEntries(_MemCardMgr_iPort);
            MemCardMgrSetState(0x103A);
        }
        break;
    case 0x103A:
        if (MemCAsyncPoll(&result) == 1) {
            _MemCardMgr_iResult = result;
            if (result >= 0) {
                _MemCardMgr_CardInfo.mUnknown4 = result;
            } else {
                _MemCardMgr_CardInfo.mUnknown4 = 0;
            }
            _MemCardMgr_bResultReady = 1;
            strcpy(_MemCardMgr_Op.mLastAction, _MemCardMgr_Op.mAction);
            MemCardMgrSetState(_MemCardMgr_iIdleState);
        }
        break;
    }
}

/* FAKEMATCH: the empty root of the card file names is spelled as a two-byte literal so that it stays
   a constant of its own, apart from the empty extra name of the save and delete states (the target
   keeps two empty strings in this file's .rodata) */
#define MCM_CARD_ROOT "\0"

void MemCardMgrMakeFilePath(char *pBuffer, int size, const char *pName, const char *pUnused)
{
    sprintf(pBuffer, "%s%s", MCM_CARD_ROOT, pName);
}

void MemCardMgrMakeEntryPath(char *pBuffer, int size, const char *pName)
{
    sprintf(pBuffer, "%s%s", MCM_CARD_ROOT, pName);
}

void MemCardMgrMakeDirPattern(char *pBuffer, int size, const char *pName)
{
    sprintf(pBuffer, "%s%s*", MCM_CARD_ROOT, pName);
}

void MemCardMgrCopyGameCode(char *pDst, const char *pSrc)
{
    strcpy(pDst, pSrc);
}

int MemCardMgrCompareGameCode(const char *pA, const char *pB)
{
    return memcmp(pA, pB, 8);
}

void MemCardMgrFormatDate(char *pBuffer, int unused, MemCDirEntry_t *pEntry)
{
    Str3_t suffix;
    unsigned short hour;
    int minute, month, day, year;

    minute = pEntry->mMinute;
    month = pEntry->mMonth;
    day = pEntry->mDay;
    year = pEntry->mYear;
    hour = pEntry->mHour;

    if (hour == 0) {
        hour = 12;
        suffix = *(const Str3_t *)"AM";
    } else if (hour <= 11) {
        suffix = *(const Str3_t *)"AM";
    } else if (hour == 12) {
        suffix = *(const Str3_t *)"PM";
    } else {
        hour -= 12;
        suffix = *(const Str3_t *)"PM";
    }
    sprintf(pBuffer, "%d/%d/%d  %d:%02d %s", month, day, year, hour, minute, suffix.mText);
}

int MemCardMgrGetEntriesPerFile(int unused)
{
    return 1;
}

int MemCardMgrReadHeader(int handle)
{
    return MemCAsyncRead(handle, _MemCardMgr_aHeaderBuffer, sizeof(_MemCardMgr_aHeaderBuffer));
}

int MemCardMgrGetNameFromHeader(int handle, int arg, char *pName, int size, MemCDirEntry_t *pEntry, MemCardGetNameFunc_t pFunc)
{
    return 0;
}

int MemCardMgrWriteSysInfo(int handle, int type, char *pTitle, int slot, MemCardSysInfoFunc_t pFunc)
{
    unsigned int info[2];

    info[0] = 0x40;
    info[1] = 0;
    return MemCAsyncSetSysInfo(handle, info);
}

int MemCardMgrGetFileSize(int unused, int dataSize, int headerSize)
{
    int size = dataSize + headerSize + 0x40;
    int total;

    if (size % 0x2000) {
        total = size / 0x2000 * 0x2000 + 0x2000;
    } else {
        total = size / 0x2000 * 0x2000;
    }
    return total;
}

int MemCardMgrGetFileCapacity(int unused, int dataSize, int headerSize)
{
    return MemCardMgrGetFileSize(unused, dataSize, headerSize) - (0x40 + headerSize);
}

void MemCardMgrFormatCardType(int type, int port, char *pBuffer, int size)
{
    MemCFormatCardType(type, pBuffer, size);
}
