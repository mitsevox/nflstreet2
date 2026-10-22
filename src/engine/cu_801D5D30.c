#include "game/fn_801D2B7C.h"
#include "engine/memorycard.h"
#include "game/fn_801C3284.h"

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
    char mUnknown14[0x20 - 0x14];
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

extern unsigned int lbl_803EBD00;
extern int lbl_803EBD04;
extern signed char lbl_803EBD08;
extern int lbl_803EBD0C;
extern unsigned char lbl_803EBD10;
extern unsigned char lbl_803EBD18;
extern unsigned char lbl_803EBD19;
extern int lbl_803EBD1C;
extern Struct_803EBD20 *lbl_803EBD20;
extern int lbl_803EBD24;
extern Struct_801D4848 *lbl_803EBD28;
extern Struct_803EBD2C *lbl_803EBD2C;
typedef int (*Func_803EBD30)(char *pBuffer, int size, void *pComment);
typedef void (*Func_803EBD34)(void);
typedef void (*Func_803EBD38)(int arg0, unsigned char **ppData, unsigned int *pSize);
typedef void (*Func_803EBD3C)(int arg0);

extern Func_803EBD30 lbl_803EBD30;
extern Func_803EBD34 lbl_803EBD34;
extern Func_803EBD38 lbl_803EBD38;
extern Func_803EBD3C lbl_803EBD3C;
extern int lbl_803ECF14;
extern Struct_803ECF18 **lbl_803ECF18;
extern Struct_80398DE0 lbl_80398DE0;
extern Struct_80398DFC lbl_80398DFC;
extern char lbl_80398F00[0x200];
extern int lbl_802F7B64[];
extern const char lbl_802AFED0[];
extern const char lbl_802AFF0C[];
extern const char lbl_802AFF14[];
extern const char lbl_802AFF18[];

extern void *memset();
extern unsigned int strlen(const char *pString);
extern char *strcpy(char *pDst, const char *pSrc);
extern int strcmp(const char *pA, const char *pB);
extern int strncmp(const char *pA, const char *pB, unsigned int count);
extern int memcmp(const void *pA, const void *pB, unsigned int count);
extern int sprintf(char *pBuffer, const char *pFormat, ...);
extern void fn_801F8758(int value);

void fn_801D5D30(int state);
int fn_801D673C(int port);
void fn_801D83F0(char *pBuffer, int size, const char *pName, const char *pUnused);
void fn_801D8498(char *pDst, const char *pSrc);
int fn_801D84B8(const char *pA, const char *pB);
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

void fn_801D6294(int result)
{
    fn_801F8758(1);
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
    fn_801D4E6C(lbl_80398DFC.mHandle);
}

void fn_801D6340(void)
{
    fn_801D4F58(lbl_80398DFC.mHandle);
}

void fn_801D6368(const char *pName, const char *pExtra)
{
    fn_801D83F0(lbl_80398DFC.mFileName, sizeof(lbl_80398DFC.mFileName), pName, pExtra);
    fn_801D4FF4(lbl_803ECF14, lbl_80398DFC.mFileName);
}

void fn_801D63B0(void)
{
    fn_801D4A3C(lbl_803ECF14, lbl_80398DFC.mFileName, 4, 0, 0);
}

void fn_801D63E8(int size)
{
    fn_801D4A3C(lbl_803ECF14, lbl_80398DFC.mFileName, 4, 1, size);
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
    fn_801D4120();
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

    while (fn_801D5840(&result) == 0) {
    }
    lbl_803EBD00 = 0x103C;
    fn_801D4198();
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
        while (fn_801D5840(&result) == 0) {
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
    fn_801D466C(port);
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
    sprintf(pOut, lbl_802AFED0, pPrefix, name, pSuffix);
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

int fn_801D6C70(int slot, int type, char *pDst, int count)
{
    return (int)fn_801C3284(pDst, lbl_803EBD2C[type].mSlots[slot].mEntry->mName, count);
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
        fn_801D56A0(lbl_80398DFC.mHandle, pBuffer, length);
        fn_801D5D30(0x1012);
    }
}

void fn_801D6E54(char *pBuffer, int length)
{
    if (lbl_803EBD00 == 0x1006) {
        lbl_80398DFC.mReadLength = length;
        fn_801D5440(lbl_80398DFC.mHandle, pBuffer, length);
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
        fn_801D4E6C(lbl_80398DFC.mHandle);
        fn_801D5D30(0x1015);
    } else if (lbl_803EBD00 == 0x1006) {
        fn_801D4E6C(lbl_80398DFC.mHandle);
        fn_801D5D30(0x100A);
    }
}

void fn_801D83F0(char *pBuffer, int size, const char *pName, const char *pUnused)
{
    sprintf(pBuffer, lbl_802AFF0C, lbl_802AFF14, pName);
}

void fn_801D8428(char *pBuffer, int size, const char *pName, const char *pUnused)
{
    sprintf(pBuffer, lbl_802AFF0C, lbl_802AFF14, pName);
}

void fn_801D8460(char *pBuffer, int size, const char *pName, const char *pUnused)
{
    sprintf(pBuffer, lbl_802AFF18, lbl_802AFF14, pName);
}

void fn_801D8498(char *pDst, const char *pSrc)
{
    strcpy(pDst, pSrc);
}

int fn_801D84B8(const char *pA, const char *pB)
{
    return memcmp(pA, pB, 8);
}

int fn_801D85A8(int unused)
{
    return 1;
}

int fn_801D85B0(int handle)
{
    return fn_801D5440(handle, lbl_80398F00, sizeof(lbl_80398F00));
}

int fn_801D85DC(void)
{
    return 0;
}

int fn_801D85E4(int handle)
{
    unsigned int info[2];

    info[0] = 0x40;
    info[1] = 0;
    return fn_801D56D4(handle, info);
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
    return fn_801D8618(unused, dataSize, headerSize) - 0x40 - headerSize;
}

void fn_801D868C(int type, int port, char *pBuffer, int size)
{
    fn_801D5764(type, pBuffer, size);
}
