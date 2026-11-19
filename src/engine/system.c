/* Low-level system services: module init and shutdown, the system timer list and the per-thread
   error codes every engine module reports through, the vsync counter and the time-to-milliseconds
   conversion of the clock record. */

#include "engine/system.h"
#include "engine/dslist.h"

/* Release-build form of the library's assertion check: compiles to an empty statement. */
#define SYS_ASSERT(e) do { } while (0)

typedef struct SysInitParams_t {
    unsigned char mNumTimers;
    unsigned char mNumCallbacks;
    unsigned char mNumThreads;
} SysInitParams_t;

typedef struct SysCallback_t {
    unsigned short mUnknown0;
    unsigned short mPriority;
    int mUnknown4;
} SysCallback_t;

typedef struct SysThreadIndex_t {
    int mUnknown0;
    unsigned int mIndex;
} SysThreadIndex_t;

typedef struct SysErrorEntry_t {
    int mError;
    int mThreadID;
} SysErrorEntry_t;

#define SYS_ERROR_UNUSED 0x8000FFFF

extern void *DSNewListNode(void *pPool);
extern void *DSGetListNode(void *pPool, int mode);
extern void DSDelListNode(void *pPool, void *pItem);
extern int DSTraverseList(void *pPool, int start, void *pKey, void *pOut, int (*pFunc)(void *, void *, void *), int count);
extern int DateGetNumDaysInYear(int year);
extern int DateGetNumDaysInMonth(int month, int year);

static unsigned char _Sys_ModuleActive = 0;
static int _Sys_LastError = 0;
static void *_Sys_ErrorList = 0;
static void *_Sys_ThreadIndexList = 0;
static int _Sys_NumThreads = 0;
static SysTimer_t *_Sys_SystemTimer = 0;
static unsigned int _Sys_uVSyncCounter = 0;
void *_Sys_TimerList;
void *_Sys_CallbackList;
Lock_801F8014 _SysCS;

SysTimer_t *SysAllocTimer(void *pFunc, int a);
void SysFreeTimer(SysTimer_t *pTimer);

static int _SysInsertByPriorityCallback(void *pA, void *pB)
{
    return ((SysCallback_t *)pA)->mPriority - ((SysCallback_t *)pB)->mPriority;
}

static int _SysTraverseErrorList(void *pItem, void *pKey, void *pOut)
{
    SysErrorEntry_t *pError = pItem;
    SysErrorEntry_t **ppFound = pOut;

    if (pError->mThreadID == (int)pKey) {
        *ppFound = pError;
        return 0;
    }
    if (pError->mError == SYS_ERROR_UNUSED) {
        *ppFound = pError;
    }
    return 1;
}

int SysInit(SysInitParams_t *pParms)
{
    int err;
    void *pPool;

    if (!_Sys_ModuleActive) {
        int i = 0;

        // FAKEMATCH: compiled-out assert; its empty do-while keeps i = 0 ahead of the first call
        SYS_ASSERT(pParms != NULL);
        err = fn_801F7E90();
        _Sys_ModuleActive = 1;
        _Sys_TimerList = DSNewList(1, 0, pParms->mNumTimers, sizeof(SysTimer_t), 0, 0);
        _Sys_SystemTimer = SysAllocTimer(0, 3);
        fn_801F7EF8(_Sys_SystemTimer);
        _Sys_CallbackList = DSNewList(1, 0, pParms->mNumCallbacks + 4, sizeof(SysCallback_t), _SysInsertByPriorityCallback, 0);
        _Sys_NumThreads = pParms->mNumThreads;
        _Sys_ThreadIndexList = DSNewList(1, 0, pParms->mNumThreads, sizeof(SysThreadIndex_t), 0, 0);
        for (; i < pParms->mNumThreads; i++) {
            SysThreadIndex_t *pIndex = DSNewListNode(_Sys_ThreadIndexList);

            pIndex->mIndex = i | 0x80000000;
            DSAddListNode(_Sys_ThreadIndexList, pIndex, 0);
        }
        if (pParms->mNumThreads > 1) {
            pPool = DSNewList(1, 0, pParms->mNumThreads, sizeof(SysErrorEntry_t), 0, 0);
            for (i = 0; i < pParms->mNumThreads; i++) {
                SysErrorEntry_t *pError = DSNewListNode(pPool);

                pError->mError = SYS_ERROR_UNUSED;
                DSAddListNode(pPool, pError, 0);
            }
            _Sys_ErrorList = pPool;
        }
        fn_801F7FA8(&_SysCS);
    } else {
        err = 0x20001;
    }
    SysSetLastErrorFunc(err);
    return err;
}

int SysShutdown(void)
{
    int err = 0;
    void *p;

    if (_Sys_ModuleActive) {
        if (_Sys_SystemTimer) {
            SysFreeTimer(_Sys_SystemTimer);
            _Sys_SystemTimer = 0;
        }
        if (_Sys_TimerList) {
            while ((p = DSGetListNode(_Sys_TimerList, 2)) != 0) {
                SysFreeTimer(p);
            }
            DSDelList(_Sys_TimerList);
            _Sys_TimerList = 0;
        }
        if (_Sys_CallbackList) {
            DSDelList(_Sys_CallbackList);
            _Sys_CallbackList = 0;
        }
        if (_Sys_ThreadIndexList) {
            DSDelList(_Sys_ThreadIndexList);
            _Sys_ThreadIndexList = 0;
        }
        if (_Sys_ErrorList) {
            p = _Sys_ErrorList;
            _Sys_ErrorList = 0;
            DSDelList(p);
        }
        err = fn_801F7ED0();
        fn_801F80D0(&_SysCS);
        _Sys_ModuleActive = 0;
    } else {
        err = 0x20002;
    }
    SysSetLastErrorFunc(err);
    return err;
}

unsigned int SysGetSystemTime(void)
{
    if (_Sys_SystemTimer) {
        return _Sys_SystemTimer->mCount;
    }
    return 0;
}

void SysSetSystemTime(unsigned int count)
{
    if (_Sys_SystemTimer) {
        _Sys_SystemTimer->mCount = count;
    }
}

void SysIncSystemTime(void)
{
    if (_Sys_SystemTimer) {
        _Sys_SystemTimer->mCount++;
    }
}

void SysIncVsyncCounter(void)
{
    _Sys_uVSyncCounter++;
}

unsigned int SysGetVsyncCounter(void)
{
    return _Sys_uVSyncCounter;
}

SysTimer_t *SysAllocTimer(void *pFunc, int a)
{
    int err = 0;
    SysTimer_t *pTimer = DSNewListNode(_Sys_TimerList);

    if (pTimer) {
        pTimer->pFunc = pFunc;
        pTimer->mUnk4 = a;
        pTimer->mUnk8 = err;
        pTimer->mUnknown10 = err;
        pTimer->mFlags = 1;
        DSAddListNode(_Sys_TimerList, pTimer, 0);
    } else {
        err = 0x20003;
    }
    SysSetLastErrorFunc(err);
    return pTimer;
}

void SysFreeTimer(SysTimer_t *pTimer)
{
    fn_801F7F60(pTimer);
    DSDelListNode(_Sys_TimerList, pTimer);
}

int SysSetLastErrorFunc(int err)
{
    SysErrorEntry_t *pError;
    int threadID;

    if (_Sys_ErrorList) {
        pError = 0;
        threadID = fn_801F81D4();
        fn_801F8014(&_SysCS);
        DSTraverseList(_Sys_ErrorList, 0, (void *)threadID, &pError, _SysTraverseErrorList, 1);
        if (pError) {
            if (pError->mError == SYS_ERROR_UNUSED) {
                pError->mThreadID = threadID;
            }
            pError->mError = err;
        }
        fn_801F809C(&_SysCS);
    } else {
        _Sys_LastError = err;
    }
    return err;
}

int SysGetLastError(void)
{
    SysErrorEntry_t *pError;
    int threadID;
    int err;

    if (_Sys_ErrorList) {
        pError = 0;
        err = 0;
        threadID = fn_801F81D4();
        fn_801F8014(&_SysCS);
        DSTraverseList(_Sys_ErrorList, 0, (void *)threadID, &pError, _SysTraverseErrorList, 1);
        if (pError && pError->mError != SYS_ERROR_UNUSED) {
            err = pError->mError;
        }
        fn_801F809C(&_SysCS);
        return err;
    }
    return _Sys_LastError;
}

unsigned long long SysTimeToMilliseconds(SysTime_t *pTime)
{
    unsigned int monthDays = DateGetNumDaysInMonth(pTime->mMonth, pTime->mYear);
    unsigned int yearDays = DateGetNumDaysInYear(pTime->mYear);

    return pTime->mHundredths * 10 + pTime->mSeconds * 1000 + pTime->mMinutes * 60000 + pTime->mHours * 3600000 +
           pTime->mDays * 86400000 + pTime->mMonth * 86400000u * monthDays + pTime->mYear * 86400000u * yearDays;
}
