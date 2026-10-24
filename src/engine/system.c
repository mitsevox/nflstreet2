#include "engine/system.h"
#include "game/fn_801C68FC.h"

typedef struct SysInitParms_801F7824 {
    unsigned char mNumTimers;
    unsigned char mNumCallbacks;
    unsigned char mNumThreads;
} SysInitParms_801F7824;

typedef struct SysCallback_801F77DC {
    unsigned short mUnknown0;
    unsigned short mPriority;
    int mUnknown4;
} SysCallback_801F77DC;

typedef struct SysThreadIndex_801F7824 {
    int mUnknown0;
    unsigned int mIndex;
} SysThreadIndex_801F7824;

typedef struct SysError_801F77EC {
    int mError;
    int mThreadID;
} SysError_801F77EC;

#define SYS_ERROR_UNUSED 0x8000FFFF

extern void *fn_801C6A20(void *pPool);
extern void *fn_801C6B4C(void *pPool, int mode);
extern void fn_801C6C0C(void *pPool, void *pItem);
extern int fn_801C6D34(void *pPool, int start, void *pKey, void *pOut, int (*pFunc)(void *, void *, void *), int count);
extern int fn_8027F000(int year);
extern int fn_8027F030(int month, int year);

extern unsigned char lbl_803EBE30;
extern int lbl_803EBE34;
extern void *lbl_803EBE38;
extern void *lbl_803EBE3C;
extern int lbl_803EBE40;
extern SysTimer_801F7B1C *lbl_803EBE44;
extern unsigned int lbl_803EBE48;
extern void *lbl_803ECFA4;
extern void *lbl_803ECFA8;
extern Lock_801F8014 lbl_8039B3F8;

SysTimer_801F7B1C *fn_801F7B1C(void *pFunc, int a);
void fn_801F7B9C(SysTimer_801F7B1C *pTimer);

static int fn_801F77DC(void *pA, void *pB)
{
    return ((SysCallback_801F77DC *)pA)->mPriority - ((SysCallback_801F77DC *)pB)->mPriority;
}

static int fn_801F77EC(void *pItem, void *pKey, void *pOut)
{
    SysError_801F77EC *pError = pItem;
    SysError_801F77EC **ppFound = pOut;

    if (pError->mThreadID == (int)pKey) {
        *ppFound = pError;
        return 0;
    }
    if (pError->mError == SYS_ERROR_UNUSED) {
        *ppFound = pError;
    }
    return 1;
}

int fn_801F7824(SysInitParms_801F7824 *pParms)
{
    int err;
    int i = 0;
    void *pPool;

    if (!lbl_803EBE30) {
        err = fn_801F7E90();
        lbl_803EBE30 = 1;
        lbl_803ECFA4 = fn_801C68FC(1, 0, pParms->mNumTimers, sizeof(SysTimer_801F7B1C), 0, 0);
        lbl_803EBE44 = fn_801F7B1C(0, 3);
        fn_801F7EF8(lbl_803EBE44);
        lbl_803ECFA8 = fn_801C68FC(1, 0, pParms->mNumCallbacks + 4, sizeof(SysCallback_801F77DC), fn_801F77DC, 0);
        lbl_803EBE40 = pParms->mNumThreads;
        lbl_803EBE3C = fn_801C68FC(1, 0, pParms->mNumThreads, sizeof(SysThreadIndex_801F7824), 0, 0);
        for (; i < pParms->mNumThreads; i++) {
            SysThreadIndex_801F7824 *pIndex = fn_801C6A20(lbl_803EBE3C);

            pIndex->mIndex = i | 0x80000000;
            fn_801C6AA4(lbl_803EBE3C, pIndex, 0);
        }
        if (pParms->mNumThreads > 1) {
            pPool = fn_801C68FC(1, 0, pParms->mNumThreads, sizeof(SysError_801F77EC), 0, 0);
            for (i = 0; i < pParms->mNumThreads; i++) {
                SysError_801F77EC *pError = fn_801C6A20(pPool);

                pError->mError = SYS_ERROR_UNUSED;
                fn_801C6AA4(pPool, pError, 0);
            }
            lbl_803EBE38 = pPool;
        }
        fn_801F7FA8(&lbl_8039B3F8);
    } else {
        err = 0x20001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801F79C0(void)
{
    int err = 0;
    void *p;

    if (lbl_803EBE30) {
        if (lbl_803EBE44) {
            fn_801F7B9C(lbl_803EBE44);
            lbl_803EBE44 = 0;
        }
        if (lbl_803ECFA4) {
            while ((p = fn_801C6B4C(lbl_803ECFA4, 2)) != 0) {
                fn_801F7B9C(p);
            }
            fn_801C69E4(lbl_803ECFA4);
            lbl_803ECFA4 = 0;
        }
        if (lbl_803ECFA8) {
            fn_801C69E4(lbl_803ECFA8);
            lbl_803ECFA8 = 0;
        }
        if (lbl_803EBE3C) {
            fn_801C69E4(lbl_803EBE3C);
            lbl_803EBE3C = 0;
        }
        if (lbl_803EBE38) {
            p = lbl_803EBE38;
            lbl_803EBE38 = 0;
            fn_801C69E4(p);
        }
        err = fn_801F7ED0();
        fn_801F80D0(&lbl_8039B3F8);
        lbl_803EBE30 = 0;
    } else {
        err = 0x20002;
    }
    fn_801F7BD4(err);
    return err;
}

unsigned int fn_801F7ABC(void)
{
    if (lbl_803EBE44) {
        return lbl_803EBE44->mCount;
    }
    return 0;
}

void fn_801F7AD4(unsigned int count)
{
    if (lbl_803EBE44) {
        lbl_803EBE44->mCount = count;
    }
}

void fn_801F7AE8(void)
{
    if (lbl_803EBE44) {
        lbl_803EBE44->mCount++;
    }
}

void fn_801F7B04(void)
{
    lbl_803EBE48++;
}

unsigned int fn_801F7B14(void)
{
    return lbl_803EBE48;
}

SysTimer_801F7B1C *fn_801F7B1C(void *pFunc, int a)
{
    int err = 0;
    SysTimer_801F7B1C *pTimer = fn_801C6A20(lbl_803ECFA4);

    if (pTimer) {
        pTimer->pFunc = pFunc;
        pTimer->mUnk4 = a;
        pTimer->mUnk8 = err;
        pTimer->mUnknown10 = err;
        pTimer->mFlags = 1;
        fn_801C6AA4(lbl_803ECFA4, pTimer, 0);
    } else {
        err = 0x20003;
    }
    fn_801F7BD4(err);
    return pTimer;
}

void fn_801F7B9C(SysTimer_801F7B1C *pTimer)
{
    fn_801F7F60(pTimer);
    fn_801C6C0C(lbl_803ECFA4, pTimer);
}

int fn_801F7BD4(int err)
{
    SysError_801F77EC *pError;
    int threadID;

    if (lbl_803EBE38) {
        pError = 0;
        threadID = fn_801F81D4();
        fn_801F8014(&lbl_8039B3F8);
        fn_801C6D34(lbl_803EBE38, 0, (void *)threadID, &pError, fn_801F77EC, 1);
        if (pError) {
            if (pError->mError == SYS_ERROR_UNUSED) {
                pError->mThreadID = threadID;
            }
            pError->mError = err;
        }
        fn_801F809C(&lbl_8039B3F8);
    } else {
        lbl_803EBE34 = err;
    }
    return err;
}

int fn_801F7C88(void)
{
    SysError_801F77EC *pError;
    int threadID;
    int err;

    if (lbl_803EBE38) {
        pError = 0;
        err = 0;
        threadID = fn_801F81D4();
        fn_801F8014(&lbl_8039B3F8);
        fn_801C6D34(lbl_803EBE38, 0, (void *)threadID, &pError, fn_801F77EC, 1);
        if (pError && pError->mError != SYS_ERROR_UNUSED) {
            err = pError->mError;
        }
        fn_801F809C(&lbl_8039B3F8);
        return err;
    }
    return lbl_803EBE34;
}

unsigned long long fn_801F7D34(SysTime_8039B430 *pTime)
{
    unsigned int monthDays = fn_8027F030(pTime->mMonth, pTime->mYear);
    unsigned int yearDays = fn_8027F000(pTime->mYear);

    return pTime->mHundredths * 10 + pTime->mSeconds * 1000 + pTime->mMinutes * 60000 + pTime->mHours * 3600000 +
           pTime->mDays * 86400000 + pTime->mMonth * 86400000 * monthDays + pTime->mYear * 86400000 * yearDays;
}
