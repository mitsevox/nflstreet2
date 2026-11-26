/* Memory-card manager: the layer between the game's save and load screens and the memorycard.c
   driver. It keeps the table of save-file types, sorts the card's directory into per-type slot
   tables, runs the asynchronous probe, load, save, delete and format operations as a state
   machine, and gives the screens each save's name, date and status. */

#include "engine/system.h"
#include "game/fn_801D2B7C.h"
#include "engine/memorycard.h"
#include <string.h>

typedef struct Struct_803EBD20 {
    int mMaxFiles;
    int mUnknown4;
    char mCode[8];
    char *mPrefix;
} Struct_803EBD20;

typedef struct Struct_803ECF18 {
    unsigned char mUsed;
    unsigned char mFlag;
    char mName[18];
    int mIndex;
    Struct_801D4848 *mEntry;
} Struct_803ECF18;

typedef struct Struct_803EBD2C {
    signed char mCount;
    Struct_803ECF18 *mSlots;
} Struct_803EBD2C;

typedef struct Struct_80398DE0 {
    int mUnknown0;
    int mUnknown4;
    int mCardType[2];
    char mTypeName[12];
} Struct_80398DE0;

typedef struct Struct_801D676C {
    char mData[0x40];
} Struct_801D676C;

typedef struct Struct_80398DFC {
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
} Struct_80398DFC;

typedef int (*Func_803EBD30)(char *pBuffer, int size, void *pComment);
typedef void (*Func_803EBD34)(void);
typedef void (*Func_803EBD38)(int arg0, unsigned char **ppData, unsigned int *pSize);
typedef void (*Func_803EBD3C)(int arg0, int arg1);

static int lbl_802F7B64[] = {
    0x1000, 0x1001, 0x1002, 0x1004, 0x100C, 0x100E, 0x1022, 0x1027,
    0x102F, 0x1031, 0x1033, 0x1035, 0x1037, 0x1039, 0x102D,
};

static unsigned int lbl_803EBD00 = 0x103C;
static int lbl_803EBD04 = 1;
static signed char lbl_803EBD08 = -1;
static int lbl_803EBD0C = 0;
static unsigned char lbl_803EBD10 = 0;
static int lbl_803EBD14 = 0;
static unsigned char lbl_803EBD18 = 0;
static unsigned char lbl_803EBD19 = 0;
static int lbl_803EBD1C = 0;
static Struct_803EBD20 *lbl_803EBD20 = 0;
static int lbl_803EBD24 = 0;
static Struct_801D4848 *lbl_803EBD28 = 0;
static Struct_803EBD2C *lbl_803EBD2C = 0;
static Func_803EBD30 lbl_803EBD30 = 0;
static Func_803EBD34 lbl_803EBD34 = 0;
static Func_803EBD38 lbl_803EBD38 = 0;
static Func_803EBD3C lbl_803EBD3C = 0;
static unsigned char lbl_803EBD40 = 1;

static unsigned int lbl_803ECF10;
static int lbl_803ECF14;
static Struct_803ECF18 **lbl_803ECF18;

static Struct_80398DE0 lbl_80398DE0;
static Struct_80398DFC lbl_80398DFC;
static char lbl_80398F00[0x200] __attribute__((aligned(32)));

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
extern int MemCAsyncGetDir(int port, const char *pGameCode, const char *pPattern, Struct_801D4848 *pEntries,
                           unsigned int maxEntries);


extern int MemCAsyncProbe(int port);

extern void *memset();
extern int memcmp(const void *pA, const void *pB, unsigned int count);
extern int sprintf(char *pBuffer, const char *pFormat, ...);

void fn_801D5D30(int state);
int fn_801D673C(int port);
void fn_801D83F0(char *pBuffer, int size, const char *pName, const char *pUnused);
void fn_801D8428(char *pBuffer, int size, const char *pName);
void fn_801D8460(char *pBuffer, int size, const char *pName);
int fn_801D85B0(int handle);
int fn_801D85DC(int handle, int arg, char *pName, int size, Struct_801D4848 *pEntry, Func_803EBD30 pFunc);
int fn_801D85E4(int handle, int type, char *pTitle, int slot, Func_803EBD34 pFunc);
void fn_801D6294(int result);
void fn_801D6318(void);
void fn_801D6340(void);
void fn_801D6368(const char *pName, const char *pExtra);
void fn_801D63B0(void);
void fn_801D63E8(int size);
int fn_801D6DA8(int slot, int type);
void MemCardMgrBuildSlotTables(int count);
void MemCardMgrUpdateProbe(void);
void fn_801D5D38(const char *pName, int *pIndex);
void fn_801D5E08(const char *pName, char *pOut);
void fn_801D8498(char *pDst, const char *pSrc);
int fn_801D84B8(const char *pA, const char *pB);
void MemCardMgrFormatDate(char *pBuffer, int unused, Struct_801D4848 *pEntry);
void fn_801D868C(int type, int port, char *pBuffer, int size);

void fn_801D5D30(int state)
{
    lbl_803EBD00 = state;
}

void fn_801D5D38(const char *pName, int *pIndex)
{
    const char *pTitle;
    char *pPrefix;
    int length;

    for (*pIndex = 0; *pIndex < lbl_803EBD1C; (*pIndex)++) {
        pTitle = pName + 7;
        if (pTitle != 0) {
            pPrefix = lbl_803EBD20[*pIndex].mPrefix;
            length = strlen(pPrefix);
            if (fn_801D84B8(lbl_803EBD20[*pIndex].mCode, lbl_80398DFC.mCode) == 0
                && strncmp(pTitle, pPrefix, length) == 0) {
                return;
            }
        }
    }
}

void fn_801D5E08(const char *pName, char *pOut)
{
    const char *pTitle = pName + 7;
    char *pPrefix;
    int length;
    int i;

    if (pTitle == 0) {
        return;
    }
    for (i = 0; i < lbl_803EBD1C; i++) {
        pPrefix = lbl_803EBD20[i].mPrefix;
        length = strlen(pPrefix);
        if (fn_801D84B8(lbl_803EBD20[i].mCode, lbl_80398DFC.mCode) == 0 && strncmp(pTitle, pPrefix, length) == 0) {
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

    if (lbl_803EBD2C != 0) {
        for (i = 0; i < lbl_803EBD1C; i++) {
            if (lbl_803EBD2C[i].mSlots != 0) {
                fn_801D2BD0(lbl_803EBD2C[i].mSlots);
                lbl_803EBD2C[i].mSlots = 0;
            }
            lbl_803EBD2C[i].mCount = 0;
        }
    }
    for (i = 0; i < count; i++) {
        fn_801D5D38(lbl_803EBD28[i].mName, &type);
        if (type < lbl_803EBD1C && fn_801D84B8(lbl_803EBD20[type].mCode, lbl_80398DFC.mCode) == 0
            && lbl_803EBD2C[type].mCount < lbl_803EBD20[type].mMaxFiles) {
            lbl_803EBD2C[type].mCount++;
        }
    }
    for (i = 0; i < count; i++) {
        fn_801D5D38(lbl_803EBD28[i].mName, &type);
        if (type < lbl_803EBD1C) {
            if (fn_801D84B8(lbl_803EBD20[type].mCode, lbl_80398DFC.mCode) == 0) {
                if (lbl_803EBD2C[type].mSlots == 0) {
                    lbl_803EBD2C[type].mSlots = fn_801D2B7C(lbl_803EBD2C[type].mCount * sizeof(Struct_803ECF18), 0, 0);
                    lbl_803EBD2C[type].mCount = 0;
                }
                n = lbl_803EBD2C[type].mCount;
                if (n < lbl_803EBD20[type].mMaxFiles) {
                    lbl_803EBD2C[type].mSlots[n].mUsed = 1;
                    lbl_803EBD2C[type].mSlots[n].mFlag = 1;
                    lbl_803EBD2C[type].mSlots[n].mEntry = &lbl_803EBD28[i];
                    lbl_803EBD2C[type].mSlots[n].mIndex = i;
                    lbl_803ECF18[i] = &lbl_803EBD2C[type].mSlots[n];
                    lbl_803EBD2C[type].mCount++;
                }
            }
        } else {
            lbl_803ECF18[i] = 0;
        }
    }
}

void MemCardMgrUpdateProbe(void)
{
    int result = -1;

    switch (lbl_803EBD00) {
    case 0x102F:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            MemCAsyncProbe(lbl_803ECF14);
            fn_801D5D30(0x1030);
        }
        break;
    case 0x1030:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                lbl_80398DE0.mCardType[lbl_803ECF14] = result;
            } else {
                lbl_80398DE0.mCardType[lbl_803ECF14] = 0;
            }
            fn_801D868C(fn_801D673C(lbl_803ECF14), lbl_803ECF14, lbl_80398DE0.mTypeName, sizeof(lbl_80398DE0.mTypeName));
            lbl_803EBD0C = result;
            lbl_803EBD10 = 1;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    }
}

void fn_801D6294(int result)
{
    SysEnableReset(1);
    if (result == -2) {
        lbl_803EBD0C = result;
        lbl_803EBD10 = 1;
        strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
        fn_801D5D30(lbl_803EBD04);
    } else {
        lbl_803EBD0C = result;
        lbl_803EBD10 = 1;
        strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
        fn_801D5D30(lbl_803EBD04);
    }
}

void fn_801D6318(void)
{
    MemCAsyncFlush(lbl_80398DFC.mHandle);
}

void fn_801D6340(void)
{
    MemCAsyncClose(lbl_80398DFC.mHandle);
}

void fn_801D6368(const char *pName, const char *pExtra)
{
    fn_801D83F0(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), pName, pExtra);
    MemCAsyncDelete(lbl_803ECF14, lbl_80398DFC.mFileName);
}

void fn_801D63B0(void)
{
    MemCAsyncOpen(lbl_803ECF14, lbl_80398DFC.mFileName, 4, 0, 0);
}

void fn_801D63E8(int size)
{
    MemCAsyncOpen(lbl_803ECF14, lbl_80398DFC.mFileName, 4, 1, size);
}

unsigned int fn_801D6420(Struct_801D4848 *pEntry)
{
    return ((pEntry->mYear - 2000) << 26) | ((pEntry->mMonth & 0xF) << 22) | ((pEntry->mDay & 0x1F) << 17)
         | ((pEntry->mHour & 0x1F) << 12) | ((pEntry->mMinute & 0x3F) << 6) | (pEntry->mSecond & 0x3F);
}

void fn_801D646C(void)
{
    int i;

    memset(&lbl_80398DFC, 0, sizeof(lbl_80398DFC));
    lbl_803EBD00 = 0x1001;
    lbl_803EBD04 = 0;
    MemCInit();
    for (i = 1; i >= 0; i--) {
        lbl_80398DE0.mCardType[i] = -1;
    }
    lbl_803ECF14 = -1;
    lbl_803EBD18 = 0;
    lbl_803EBD19 = 0;
}

void fn_801D64EC(void)
{
    int result = 0;

    while (MemCAsyncPoll(&result) == 0) {
    }
    lbl_803EBD00 = 0x103C;
    MemCShutdown();
    lbl_803ECF14 = -1;
    lbl_803EBD18 = 0;
    lbl_803EBD19 = 0;
}

void fn_801D654C(int enable)
{
    int result;

    if (enable) {
        if (lbl_803EBD04 == 0x1000) {
            lbl_803EBD08 = 6;
        } else {
            lbl_803EBD08 = 1;
        }
    } else {
        result = 0;
        while (MemCAsyncPoll(&result) == 0) {
        }
        lbl_803EBD08 = -1;
    }
}

void fn_801D65B4(int mode)
{
    lbl_803EBD04 = lbl_802F7B64[mode];
    if (lbl_803EBD04 == 0x1000 && lbl_803EBD00 != 0x1000) {
        fn_801D5D30(0x1000);
    }
    if (lbl_803EBD04 == 0x1001 && lbl_803EBD00 != 0x1001) {
        fn_801D5D30(0x1001);
    }
}

int fn_801D6620(int *pResult)
{
    if (lbl_803EBD10) {
        *pResult = lbl_803EBD0C;
        lbl_803EBD10 = 0;
        return 1;
    }
    return 0;
}

void fn_801D6650(int mode)
{
    fn_801D5D30(lbl_802F7B64[mode]);
}

void fn_801D6680(int port)
{
    int i;

    if (lbl_803EBD2C != 0) {
        for (i = 0; i < lbl_803EBD1C; i++) {
            if (lbl_803EBD2C[i].mSlots != 0) {
                fn_801D2BD0(lbl_803EBD2C[i].mSlots);
                lbl_803EBD2C[i].mSlots = 0;
            }
            lbl_803EBD2C[i].mCount = 0;
        }
    }
    MemCUnMount(port);
}

void fn_801D6714(int port)
{
    lbl_803ECF14 = port;
}

int fn_801D671C(void)
{
    return lbl_803ECF14;
}

int fn_801D6724(void)
{
    return lbl_80398DE0.mUnknown0;
}

int fn_801D6730(void)
{
    return lbl_80398DE0.mUnknown4;
}

int fn_801D673C(int port)
{
    return lbl_80398DE0.mCardType[port];
}

void fn_801D6754(int value)
{
    lbl_80398DFC.mUnknown4 = value;
}

void fn_801D6760(int value)
{
    lbl_80398DFC.mUnknown8 = value;
}

void fn_801D676C(Struct_801D676C *pInfo)
{
    if (pInfo != 0) {
        *(Struct_801D676C *)lbl_80398DFC.mInfo = *pInfo;
    }
}

void fn_801D67E4(const char *pTitle, const char *pDescription)
{
    if (pTitle != 0) {
        strcpy(lbl_80398DFC.mTitle, pTitle);
    }
    if (pDescription != 0) {
        strcpy(lbl_80398DFC.mDescription, pDescription);
    }
}

void fn_801D6838(int value)
{
    lbl_80398DFC.mUnknownC = value;
}

int fn_801D6844(void)
{
    return lbl_80398DFC.mUnknownC;
}

int fn_801D6850(void)
{
    return lbl_80398DFC.mUnknown4;
}

void fn_801D685C(const char *pCode, int flag)
{
    fn_801D8498(lbl_80398DFC.mCode, pCode);
    lbl_80398DFC.mUnknownEE = flag;
}

void fn_801D689C(const char *pSuffix, const char *pPrefix, int unused, int type, char *pOut, int size)
{
    char name[32];

    strcpy(name, lbl_803EBD20[type].mPrefix);
    sprintf(pOut, "%s%s%s", pPrefix, name, pSuffix);
    /* FAKEMATCH: the target keeps the unreferenced string "%s-%s" (0x802AFED8) right after "%s%s%s";
       this never-executed call keeps it there with no code (see the evidence.tsv source-form row) */
    if (0) {
        sprintf(pOut, "%s-%s", name, pSuffix);
    }
}

void fn_801D6904(int a, int b)
{
    lbl_80398DFC.mUnknownEF = a;
    lbl_80398DFC.mUnknownF0 = b;
}

char *fn_801D6918(void)
{
    return lbl_80398DFC.mLastAction;
}

void fn_801D6924(Func_803EBD30 a, Func_803EBD34 b, Func_803EBD38 c, Func_803EBD3C d)
{
    lbl_803EBD30 = a;
    lbl_803EBD34 = b;
    lbl_803EBD38 = c;
    lbl_803EBD3C = d;
}

void fn_801D6938(Struct_803EBD20 *pTypes, int count)
{
    int i;

    if (lbl_803EBD28 != 0) {
        fn_801D2BD0(lbl_803EBD28);
        lbl_803EBD28 = 0;
    }
    if (lbl_803ECF18 != 0) {
        fn_801D2BD0(lbl_803ECF18);
        lbl_803ECF18 = 0;
    }
    if (lbl_803EBD2C != 0) {
        for (i = 0; i < lbl_803EBD1C; i++) {
            if (lbl_803EBD2C[i].mSlots != 0) {
                fn_801D2BD0(lbl_803EBD2C[i].mSlots);
                lbl_803EBD2C[i].mSlots = 0;
            }
        }
        fn_801D2BD0(lbl_803EBD2C);
        lbl_803EBD2C = 0;
    }
    lbl_803EBD1C = count;
    lbl_803EBD24 = 0;
    lbl_803EBD20 = pTypes;
    for (i = 0; i < count; i++) {
        lbl_803EBD24 += pTypes[i].mMaxFiles;
    }
    lbl_803EBD28 = fn_801D2B7C(lbl_803EBD24 * sizeof(Struct_801D4848), 0, 0);
    lbl_803ECF18 = fn_801D2B7C(lbl_803EBD24 * sizeof(Struct_803ECF18 *), 0, 0);
    lbl_803EBD2C = fn_801D2B7C(lbl_803EBD1C * sizeof(Struct_803EBD2C), 0, 0);
    memset(lbl_803EBD28, 0, lbl_803EBD24 * sizeof(Struct_801D4848));
    memset(lbl_803ECF18, 0, lbl_803EBD24 * sizeof(Struct_803ECF18 *));
    memset(lbl_803EBD2C, 0, lbl_803EBD1C * sizeof(Struct_803EBD2C));
}

int fn_801D6AC8(int type)
{
    int count;
    int i;

    if (type == -1) {
        count = 0;
        for (i = 0; i < lbl_803EBD24; i++) {
            count += lbl_803EBD2C[i].mCount;
        }
        return count;
    }
    return lbl_803EBD2C[type].mCount;
}

int fn_801D6B14(int type)
{
    return lbl_803EBD20[type].mMaxFiles;
}

void fn_801D6B24(char *pDst, int size)
{
    strcpy(pDst, lbl_80398DFC.mTitle);
}

void fn_801D6B4C(char *pDst, int size)
{
    strcpy(pDst, lbl_80398DFC.mDescription);
}

int MemCardMgrGetSlotInfo(int slot, int type, char *pName, int nameSize, char *pDate, int dateArg, unsigned char *pFlag)
{
    int used = 0;
    Struct_803ECF18 *pSlot;

    if (slot < lbl_803EBD2C[type].mCount) {
        if (lbl_803EBD2C[type].mSlots[slot].mUsed) {
            pSlot = &lbl_803EBD2C[type].mSlots[slot];
            used = pSlot->mUsed;
            if (pName != 0) {
                if (pSlot->mFlag) {
                    *(Str4_t *)pName = *(const Str4_t *)"???";
                } else {
                    strcpy(pName, pSlot->mName);
                }
            }
            if (pDate != 0) {
                MemCardMgrFormatDate(pDate, dateArg, lbl_803EBD2C[type].mSlots[slot].mEntry);
            }
            if (pFlag != 0) {
                *pFlag = lbl_803EBD2C[type].mSlots[slot].mFlag;
            }
        }
    }
    return used;
}

int fn_801D6C70(int slot, int type, char *pDst, int count)
{
    return (int)strnzcpy(pDst, lbl_803EBD2C[type].mSlots[slot].mEntry->mName, count);
}

unsigned int fn_801D6CB8(int slot, int type)
{
    return fn_801D6420(lbl_803EBD2C[type].mSlots[slot].mEntry);
}

int fn_801D6CF4(const char *pName, int type, unsigned char *pFlag)
{
    signed char i;

    for (i = 0; i < lbl_803EBD2C[type].mCount; i++) {
        if (strcmp(lbl_803EBD2C[type].mSlots[i].mName, pName) == 0) {
            *pFlag = lbl_803EBD2C[type].mSlots[i].mFlag;
            return i;
        }
    }
    *pFlag = 0;
    return -1;
}

int fn_801D6DA8(int slot, int type)
{
    if (slot < lbl_803EBD2C[type].mCount) {
        return lbl_803EBD2C[type].mSlots[slot].mFlag;
    }
    return 0;
}

void fn_801D6DE0(int slot, int type)
{
    lbl_803EBD2C[type].mSlots[slot].mFlag = 1;
}

void fn_801D6E04(int value)
{
    lbl_80398DFC.mUnknown28 = value;
}

void fn_801D6E10(char *pBuffer, int length)
{
    if (lbl_803EBD00 == 0x1011) {
        MemCAsyncWrite(lbl_80398DFC.mHandle, pBuffer, length);
        fn_801D5D30(0x1012);
    }
}

void fn_801D6E54(char *pBuffer, int length)
{
    if (lbl_803EBD00 == 0x1006) {
        lbl_80398DFC.mReadLength = length;
        MemCAsyncRead(lbl_80398DFC.mHandle, pBuffer, length);
        fn_801D5D30(0x1007);
    }
}

int fn_801D6EA0(unsigned char *pIdle)
{
    if (pIdle != 0) {
        switch (lbl_803EBD00) {
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
    return lbl_803EBD00 == 0x1011 || lbl_803EBD00 == 0x1006;
}

void fn_801D6EFC(void)
{
    if (lbl_803EBD00 == 0x1011) {
        MemCAsyncFlush(lbl_80398DFC.mHandle);
        fn_801D5D30(0x1015);
    } else if (lbl_803EBD00 == 0x1006) {
        MemCAsyncFlush(lbl_80398DFC.mHandle);
        fn_801D5D30(0x100A);
    }
}

void MemCardMgrUpdate(void)
{
    int error;
    Struct_803ECF18 *pSlot;
    char name[65];
    int poll = -1;
    int result = -1;
    unsigned int size;
    unsigned int writeSize;
    unsigned int headerSize;
    int type;

    SysCheckReset();
    switch (lbl_803EBD00) {
    case 0x1000:
        if (lbl_803EBD08 == 0) {
            poll = MemCAsyncPoll(&result);
            if (!lbl_803EBD19 && poll == 1) {
                poll = -1;
            }
            if (poll == 1) {
                if (lbl_803ECF14 >= 0 && lbl_803ECF14 <= 1) {
                    lbl_803EBD19 = poll;
                    MemCAsyncProbe(lbl_803ECF14);
                }
            } else if (poll == -1) {
                if (lbl_803ECF14 >= 0 && lbl_803ECF14 <= 1) {
                    lbl_803EBD19 = 1;
                    MemCAsyncProbe(lbl_803ECF14);
                }
            }
            lbl_803EBD08 = 6;
        } else if (lbl_803EBD08 > 0) {
            lbl_803EBD08--;
        }
        break;
    case 0x1001:
        *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
        if (lbl_803EBD08 == 0) {
            poll = MemCAsyncPoll(&result);
            if (!lbl_803EBD18 && poll == 1) {
                poll = -1;
            }
            if (poll == 1) {
                if (result >= 0) {
                    lbl_80398DE0.mCardType[lbl_803ECF10] = result;
                    if (lbl_803ECF14 == -1) {
                        lbl_803ECF14 = lbl_803ECF10;
                    }
                } else {
                    lbl_80398DE0.mCardType[lbl_803ECF10] = 0;
                }
                lbl_803ECF10++;
                if (lbl_803ECF10 > 1) {
                    lbl_803ECF10 = 0;
                }
                lbl_803EBD18 = 1;
                MemCAsyncProbe(lbl_803ECF10);
            } else if (poll == -1) {
                lbl_803ECF10 = 0;
                lbl_803EBD18 = 1;
                MemCAsyncProbe(0);
            }
            lbl_803EBD08 = 1;
        } else if (lbl_803EBD08 > 0) {
            lbl_803EBD08--;
        }
        break;
    case 0x1002:
        if (MemCAsyncPoll(&result)) {
            *(Str7_t *)lbl_80398DFC.mAction = *(const Str7_t *)"Format";
            lbl_803EBD0C = 0;
            MemCAsyncFormat(lbl_803ECF14);
            fn_801D5D30(0x1003);
        }
        break;
    case 0x1003:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                lbl_803EBD10 = 1;
                lbl_803EBD0C = 1;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1004:
        if (MemCAsyncPoll(&result)) {
            *(Str5_t *)lbl_80398DFC.mAction = *(const Str5_t *)"Load";
            lbl_803EBD0C = 0;
            fn_801D83F0(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), lbl_80398DFC.mDescription,
                        lbl_80398DFC.mDescription);
            fn_801D63B0();
            fn_801D5D30(0x1005);
        }
        break;
    case 0x1005:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                lbl_80398DFC.mHandle = result;
                lbl_80398DFC.mUnknown28 = 0;
                size = 0;
                if (lbl_80398DFC.mUnknownF0) {
                    lbl_803EBD38(lbl_80398DFC.mUnknown4, 0, &size);
                }
                if (lbl_80398DFC.mUnknownEF) {
                    size += 0x40;
                }
                if ((int)size > 0) {
                    lbl_80398DFC.mSeekWhence = 0;
                    lbl_80398DFC.mSeekOffset = size;
                    fn_801D6318();
                    fn_801D5D30(0x1008);
                } else {
                    fn_801D5D30(0x1006);
                }
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1006:
        break;
    case 0x1007:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                if (result == lbl_80398DFC.mReadLength) {
                    fn_801D5D30(0x1006);
                    break;
                }
                lbl_803EBD2C[lbl_80398DFC.mUnknown4].mSlots[lbl_80398DFC.mUnknownC].mFlag = poll;
                fn_801D6318();
                fn_801D5D30(0x100A);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x100B);
            }
        }
        break;
    case 0x1008:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCAsyncSeek(lbl_80398DFC.mHandle, lbl_80398DFC.mSeekOffset, lbl_80398DFC.mSeekWhence);
                fn_801D5D30(0x1009);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x100B);
            }
        }
        break;
    case 0x1009:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                fn_801D5D30(0x1006);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x100B);
            }
        }
        break;
    case 0x100A:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                lbl_803EBD0C = result;
            }
            fn_801D6340();
            fn_801D5D30(0x100B);
        }
        break;
    case 0x100B:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                if ((error = lbl_803EBD0C) != 0) {
                    fn_801D6294(error);
                    break;
                }
                if (lbl_80398DFC.mUnknown28 != 0) {
                    fn_801D6294(lbl_80398DFC.mUnknown28);
                    break;
                }
                if (fn_801D6DA8(lbl_80398DFC.mUnknownC, lbl_80398DFC.mUnknown4) == 0) {
                    lbl_803EBD0C = error;
                } else {
                    lbl_803EBD0C = -100;
                }
                lbl_803EBD10 = 1;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else {
                if ((error = lbl_803EBD0C) != 0) {
                    fn_801D6294(error);
                } else {
                    fn_801D6294(result);
                }
            }
        }
        break;
    case 0x100C:
        if (MemCAsyncPoll(&result)) {
            *(Str5_t *)lbl_80398DFC.mAction = *(const Str5_t *)"Save";
            lbl_803EBD0C = 0;
            SysEnableReset(0);
            fn_801D6368(lbl_80398DFC.mDescription, "");
            fn_801D5D30(0x100D);
        }
        break;
    case 0x100D:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                fn_801D83F0(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), lbl_80398DFC.mDescription,
                            lbl_80398DFC.mDescription);
                fn_801D63E8(lbl_80398DFC.mUnknown8);
                fn_801D5D30(0x1010);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x100E:
        if (MemCAsyncPoll(&result)) {
            *(Str5_t *)lbl_80398DFC.mAction = *(const Str5_t *)"Save";
            lbl_803EBD0C = 0;
            SysEnableReset(0);
            fn_801D5D30(0x100F);
        }
        break;
    case 0x100F:
        result = 0;
        fn_801D83F0(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), lbl_80398DFC.mDescription,
                    lbl_80398DFC.mDescription);
        fn_801D63E8(lbl_80398DFC.mUnknown8);
        fn_801D5D30(0x1010);
        break;
    case 0x1010:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                lbl_80398DFC.mHandle = result;
                lbl_80398DFC.mUnknown28 = 0;
                if (lbl_80398DFC.mUnknownEF) {
                    MemCAsyncWrite(lbl_80398DFC.mHandle, lbl_80398DFC.mInfo, sizeof(lbl_80398DFC.mInfo));
                    fn_801D5D30(0x101B);
                } else {
                    fn_801D5D30(0x1011);
                }
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1011:
        break;
    case 0x1012:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                fn_801D5D30(0x1011);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x1016);
            }
        }
        break;
    case 0x1013:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCAsyncSeek(lbl_80398DFC.mHandle, lbl_80398DFC.mSeekOffset, lbl_80398DFC.mSeekWhence);
                fn_801D5D30(0x1014);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x1016);
            }
        }
        break;
    case 0x1014:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                fn_801D5D30(0x1011);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x1016);
            }
        }
        break;
    case 0x1015:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                fn_801D85E4(lbl_80398DFC.mHandle, lbl_80398DFC.mUnknown4, lbl_80398DFC.mTitle, lbl_80398DFC.mUnknownC,
                            lbl_803EBD34);
                fn_801D5D30(0x101F);
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x1016);
            }
        }
        break;
    case 0x1016:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                if ((error = lbl_803EBD0C) != 0) {
                    fn_801D6294(error);
                    break;
                }
                if (lbl_80398DFC.mUnknown28 != 0) {
                    fn_801D6294(lbl_80398DFC.mUnknown28);
                    break;
                }
                SysEnableReset(1);
                lbl_803EBD10 = poll;
                lbl_803EBD0C = poll;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else {
                if ((error = lbl_803EBD0C) != 0) {
                    fn_801D6294(error);
                } else {
                    fn_801D6294(result);
                }
            }
        }
        break;
    case 0x1017:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                lbl_80398DFC.mHandle = result;
                lbl_803EBD38(lbl_80398DFC.mUnknown4, &lbl_80398DFC.mpData, &writeSize);
                MemCAsyncWrite(lbl_80398DFC.mHandle, (char *)lbl_80398DFC.mpData, writeSize);
                fn_801D5D30(0x1018);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1018:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                if (lbl_80398DFC.mUnknownF0) {
                    lbl_803EBD3C(lbl_80398DFC.mUnknown4, (int)lbl_80398DFC.mpData);
                    lbl_80398DFC.mpData = 0;
                    fn_801D5D30(0x1011);
                } else {
                    fn_801D6318();
                    fn_801D5D30(0x1019);
                }
            } else {
                lbl_803EBD3C(lbl_80398DFC.mUnknown4, (int)lbl_80398DFC.mpData);
                lbl_80398DFC.mpData = 0;
                lbl_803EBD0C = result;
                fn_801D6340();
                if (lbl_80398DFC.mUnknownF0) {
                    fn_801D5D30(0x1016);
                } else {
                    fn_801D5D30(0x101A);
                }
            }
        }
        break;
    case 0x1019:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                lbl_803EBD3C(lbl_80398DFC.mUnknown4, (int)lbl_80398DFC.mpData);
                lbl_80398DFC.mpData = 0;
                lbl_803EBD0C = result;
            }
            fn_801D6340();
            fn_801D5D30(0x101A);
        }
        break;
    case 0x101A:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                error = lbl_803EBD0C;
                if (error == 0) {
                    lbl_803EBD3C(lbl_80398DFC.mUnknown4, (int)lbl_80398DFC.mpData);
                    lbl_80398DFC.mpData = (unsigned char *)error;
                    SysEnableReset(1);
                    lbl_803EBD10 = poll;
                    lbl_803EBD0C = poll;
                    strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                    fn_801D5D30(lbl_803EBD04);
                    break;
                }
            }
            lbl_803EBD3C(lbl_80398DFC.mUnknown4, (int)lbl_80398DFC.mpData);
            lbl_80398DFC.mpData = 0;
            if (lbl_803EBD0C != 0) {
                fn_801D6294(lbl_803EBD0C);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x101C:
        fn_801D83F0(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), lbl_80398DFC.mDescription,
                    lbl_80398DFC.mDescription);
        MemCAsyncGetSysInfo(lbl_803ECF14, lbl_80398DFC.mFileName, 11);
        fn_801D5D30(0x101D);
        break;
    case 0x101D:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                fn_801D8428(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), lbl_80398DFC.mDescription);
                fn_801D63E8(0);
                fn_801D5D30(0x101E);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x101E:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                lbl_80398DFC.mHandle = result;
                fn_801D85E4(lbl_80398DFC.mHandle, lbl_80398DFC.mUnknown4, lbl_80398DFC.mTitle, lbl_80398DFC.mUnknownC,
                            lbl_803EBD34);
                fn_801D5D30(0x101F);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x101F:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                lbl_803EBD0C = result;
            }
            fn_801D6340();
            fn_801D5D30(0x1016);
        }
        break;
    case 0x101B:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                if (lbl_80398DFC.mUnknownF0) {
                    lbl_803EBD38(lbl_80398DFC.mUnknown4, &lbl_80398DFC.mpData, &headerSize);
                    MemCAsyncWrite(lbl_80398DFC.mHandle, (char *)lbl_80398DFC.mpData, headerSize);
                    fn_801D5D30(0x1018);
                } else {
                    fn_801D5D30(0x1011);
                }
            } else {
                lbl_803EBD0C = result;
                fn_801D6340();
                fn_801D5D30(0x1016);
            }
        }
        break;
    case 0x1020:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                lbl_803EBD0C = result;
            }
            fn_801D6340();
            fn_801D5D30(0x1021);
        }
        break;
    case 0x1021:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                if ((error = lbl_803EBD0C) != 0) {
                    fn_801D6294(error);
                    break;
                }
                SysEnableReset(1);
                lbl_803EBD10 = poll;
                lbl_803EBD0C = poll;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else {
                if ((error = lbl_803EBD0C) != 0) {
                    fn_801D6294(error);
                } else {
                    fn_801D6294(result);
                }
            }
        }
        break;
    case 0x1022:
        if (MemCAsyncPoll(&result)) {
            *(Str7_t *)lbl_80398DFC.mAction = *(const Str7_t *)"Delete";
            lbl_803EBD0C = 0;
            SysEnableReset(0);
            fn_801D6368(lbl_80398DFC.mDescription, lbl_80398DFC.mDescription);
            fn_801D5D30(0x1025);
        }
        break;
    case 0x1023:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0 && result != -3) {
                fn_801D6294(result);
                break;
            }
            fn_801D6368(lbl_80398DFC.mDescription, "");
            fn_801D5D30(0x1024);
        }
        break;
    case 0x1024:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0 && result != -3) {
                fn_801D6294(result);
                break;
            }
            fn_801D6368(lbl_80398DFC.mDescription, lbl_80398DFC.mDescription);
            fn_801D5D30(0x1025);
        }
        break;
    case 0x1025:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                SysEnableReset(1);
                lbl_803EBD10 = poll;
                lbl_803EBD0C = poll;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else if (result == -3) {
                SysEnableReset(1);
                lbl_803EBD10 = poll;
                lbl_803EBD0C = poll;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1026:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            if (result >= 0) {
                SysEnableReset(1);
                lbl_803EBD10 = poll;
                lbl_803EBD0C = poll;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else if (result == -3) {
                SysEnableReset(1);
                lbl_803EBD10 = poll;
                lbl_803EBD0C = poll;
                strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
                fn_801D5D30(lbl_803EBD04);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1027:
    case 0x102D:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            memset(lbl_803EBD28, 0, lbl_803EBD24 * sizeof(Struct_801D4848));
            fn_801D8460(name, sizeof(name), lbl_80398DFC.mCode);
            if (lbl_803EBD00 == 0x1027) {
                MemCAsyncGetDir(lbl_803ECF14, name, name, lbl_803EBD28, lbl_803EBD24);
                fn_801D5D30(0x1028);
            } else {
                char pattern[1] = "*";

                MemCAsyncGetDir(lbl_803ECF14, name, pattern, lbl_803EBD28, lbl_803EBD24);
                fn_801D5D30(0x102E);
            }
        }
        break;
    case 0x1028:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                MemCardMgrBuildSlotTables(result);
                lbl_803EBD10 = 0;
                lbl_803EBD0C = result;
                lbl_803EBD14 = 0;
                fn_801D5D30(0x1029);
            } else {
                fn_801D6294(result);
            }
        }
        break;
    case 0x1029:
        if (lbl_803EBD14 < lbl_803EBD0C) {
            pSlot = lbl_803ECF18[lbl_803EBD14];
            if (pSlot != 0) {
                pSlot->mFlag = 1;
                fn_801D5E08(lbl_803EBD28[lbl_803EBD14].mName, pSlot->mName);
                fn_801D8428(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), lbl_803EBD28[lbl_803EBD14].mName);
                fn_801D63B0();
                fn_801D5D30(0x102A);
            } else {
                lbl_803EBD14++;
                fn_801D5D30(0x1029);
            }
        } else {
            lbl_803EBD10 = 1;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    case 0x102A:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                lbl_80398DFC.mHandle = result;
                fn_801D85B0(result);
                fn_801D5D30(0x102B);
                break;
            }
            if (result == -2) {
                fn_801D6294(-2);
                break;
            }
            lbl_803EBD14++;
            fn_801D5D30(0x1029);
        }
        break;
    case 0x102B:
        if (MemCAsyncPoll(&result) == 1) {
            if (result >= 0) {
                type = 0;
                pSlot = lbl_803ECF18[lbl_803EBD14];
                fn_801D5D38(pSlot->mEntry->mName, &type);
                pSlot->mFlag = fn_801D85DC(result, lbl_803EBD20[type].mUnknown4, pSlot->mName, 17, pSlot->mEntry,
                                           lbl_803EBD30);
            }
            fn_801D6340();
            fn_801D5D30(0x102C);
        }
        break;
    case 0x102C:
        if (MemCAsyncPoll(&result) == 1) {
            if (result < 0) {
                if (result == -2) {
                    fn_801D6294(-2);
                    break;
                }
            }
            lbl_803EBD14++;
            fn_801D5D30(0x1029);
        }
        break;
    case 0x102E:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            lbl_803EBD0C = result;
            lbl_803EBD10 = poll;
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    case 0x102F:
    case 0x1030:
        MemCardMgrUpdateProbe();
        break;
    case 0x1031:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            MemCAsyncMount(lbl_803ECF14);
            fn_801D5D30(0x1032);
        }
        break;
    case 0x1032:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            fn_801D868C(fn_801D673C(lbl_803ECF14), lbl_803ECF14, lbl_80398DE0.mTypeName, sizeof(lbl_80398DE0.mTypeName));
            lbl_803EBD10 = poll;
            lbl_803EBD0C = result;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    case 0x1033:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            MemCAsyncMountAlt(lbl_803ECF14, lbl_80398DFC.mCode);
            fn_801D5D30(0x1034);
        }
        break;
    case 0x1034:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            lbl_803EBD10 = poll;
            lbl_803EBD0C = result;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    case 0x1035:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            MemCAsyncCheck(lbl_803ECF14);
            fn_801D5D30(0x1036);
        }
        break;
    case 0x1036:
        poll = MemCAsyncPoll(&result);
        if (poll == 1) {
            lbl_803EBD10 = poll;
            lbl_803EBD0C = result;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    case 0x1037:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            MemCAsyncGetFreeSpace(lbl_803ECF14);
            fn_801D5D30(0x1038);
        }
        break;
    case 0x1038:
        if (MemCAsyncPoll(&result) == 1) {
            lbl_803EBD0C = result;
            if (result >= 0) {
                lbl_80398DE0.mUnknown0 = result;
            } else {
                lbl_80398DE0.mUnknown0 = 0;
            }
            lbl_803EBD10 = 1;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    case 0x1039:
        if (MemCAsyncPoll(&result)) {
            *(Str6_t *)lbl_80398DFC.mAction = *(const Str6_t *)"Check";
            lbl_803EBD0C = 0;
            MemCAsyncGetFreeEntries(lbl_803ECF14);
            fn_801D5D30(0x103A);
        }
        break;
    case 0x103A:
        if (MemCAsyncPoll(&result) == 1) {
            lbl_803EBD0C = result;
            if (result >= 0) {
                lbl_80398DE0.mUnknown4 = result;
            } else {
                lbl_80398DE0.mUnknown4 = 0;
            }
            lbl_803EBD10 = 1;
            strcpy(lbl_80398DFC.mLastAction, lbl_80398DFC.mAction);
            fn_801D5D30(lbl_803EBD04);
        }
        break;
    }
}

/* FAKEMATCH: the empty root of the card file names is spelled as a two-byte literal so that it stays
   a constant of its own, apart from the empty extra name of the save and delete states (the target
   keeps two empty strings in this file's .rodata) */
#define MCM_CARD_ROOT "\0"

void fn_801D83F0(char *pBuffer, int size, const char *pName, const char *pUnused)
{
    sprintf(pBuffer, "%s%s", MCM_CARD_ROOT, pName);
}

void fn_801D8428(char *pBuffer, int size, const char *pName)
{
    sprintf(pBuffer, "%s%s", MCM_CARD_ROOT, pName);
}

void fn_801D8460(char *pBuffer, int size, const char *pName)
{
    sprintf(pBuffer, "%s%s*", MCM_CARD_ROOT, pName);
}

void fn_801D8498(char *pDst, const char *pSrc)
{
    strcpy(pDst, pSrc);
}

int fn_801D84B8(const char *pA, const char *pB)
{
    return memcmp(pA, pB, 8);
}

void MemCardMgrFormatDate(char *pBuffer, int unused, Struct_801D4848 *pEntry)
{
    Str3_t suffix;
    unsigned short hour = pEntry->mHour;
    int minute = pEntry->mMinute;
    int month = pEntry->mMonth;
    int day = pEntry->mDay;
    int year;

    year = pEntry->mYear;

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

int fn_801D85A8(int unused)
{
    return 1;
}

int fn_801D85B0(int handle)
{
    return MemCAsyncRead(handle, lbl_80398F00, sizeof(lbl_80398F00));
}

int fn_801D85DC(int handle, int arg, char *pName, int size, Struct_801D4848 *pEntry, Func_803EBD30 pFunc)
{
    return 0;
}

int fn_801D85E4(int handle, int type, char *pTitle, int slot, Func_803EBD34 pFunc)
{
    unsigned int info[2];

    info[0] = 0x40;
    info[1] = 0;
    return MemCAsyncSetSysInfo(handle, info);
}

int fn_801D8618(int unused, int dataSize, int headerSize)
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

int fn_801D8658(int unused, int dataSize, int headerSize)
{
    return fn_801D8618(unused, dataSize, headerSize) - (0x40 + headerSize);
}

void fn_801D868C(int type, int port, char *pBuffer, int size)
{
    MemCFormatCardType(type, pBuffer, size);
}
