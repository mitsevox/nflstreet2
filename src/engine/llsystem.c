/* Implements GameCube system timers, recursive locks, the real-time clock and reset handling. */
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/gx.h>
#include <dolphin/pad.h>
#include <dolphin/ai.h>
#include <math.h>
#include "engine/system.h"
#include "engine/llglib.h"
#include "game/fn_801D2B7C.h"

extern void FileAsyncCheckError(void);
extern int GlibGetTvMode(void);
extern int DateIsYearLeap(int year);
extern int DateGetNumDaysInYear(int year);
extern int DateGetNumDaysInMonth(int month, int year);

int _Sys_CriticalSectionCount = 0;
int _Sys_MainThreadID = 1;
unsigned char _Sys_PreviousResetState = 0;
unsigned char _Sys_ResetEnabled = 1;
unsigned char _Sys_ResetPending = 0;
SysResetCallback_t _Sys_ResetCallback = 0;
unsigned char _Sys_MutexNeedsInit = 1;
unsigned int _Sys_ClockVsyncTicks = 0;
unsigned int _Sys_ClockUnixSeconds = 0;
OSMutex _Sys_CriticalSectionMutex;
SysTime_t _Sys_RealTimeClock;


static void _SysVIPreRetraceCallback(u32 retraceCount)
{
    SysIncSystemTime();
    SysUpdateRealTimeClock();
}

static void _SysSetupReset(void)
{
    GlibEnableVIRetraceCallback(0);
    LCDisable();
    PADRecalibrate(0xF0000000);
    PADControlMotor(0, 2);
    PADControlMotor(1, 2);
    PADControlMotor(2, 2);
    PADControlMotor(3, 2);
    AIReset();
    GXAbortFrame();
    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();
}

int SysInitPlatform(void)
{
    _Sys_MainThreadID = SysGetThreadID();
    OSSetThreadPriority((OSThread *)_Sys_MainThreadID, 22);
    VISetPreRetraceCallback(_SysVIPreRetraceCallback);
    return 0;
}

int SysShutdownPlatform(void)
{
    VISetPreRetraceCallback(0);
    return 0;
}

int SysStartTimer(SysTimer_t *pTimer)
{
    if (!(pTimer->mFlags & 4)) {
        if (pTimer->pFunc == 0) {
            pTimer->mCount = 1;
            pTimer->mFlags |= 4;
        } else {
            switch (pTimer->mUnk4) {
            case 0:
                pTimer->mUnknown1C = 1;
                break;
            case 1:
                pTimer->mUnknown1C = 1;
                break;
            case 2:
                pTimer->mUnknown1C = 1;
                break;
            case 3:
                pTimer->mUnknown1C = 1;
                break;
            default:
                pTimer->mUnknown1C = 1;
                break;
            }
            pTimer->mFlags |= 6;
        }
    }
    return 0;
}

int SysStopTimer(SysTimer_t *pTimer)
{
    if (pTimer->mFlags & 4) {
        if (pTimer->mFlags & 2) {
            pTimer->mFlags &= ~2;
        } else {
            pTimer->mUnk8 += 1 - pTimer->mCount;
        }
        pTimer->mFlags &= ~4;
    }
    return 0;
}

void SysInitCriticalSectionFunc(SysCriticalSection_t *pSection)
{
    if (_Sys_MutexNeedsInit) {
        _Sys_MutexNeedsInit = 0;
        OSInitMutex(&_Sys_CriticalSectionMutex);
    }
    _Sys_CriticalSectionCount++;
    OSInitMutex(&pSection->mMutex);
    pSection->mOwner = SysGetThreadID();
    pSection->mCount = 0;
}

void SysEnterCriticalSectionFunc(SysCriticalSection_t *pSection)
{
    int owner;

    OSLockMutex(&_Sys_CriticalSectionMutex);
    owner = pSection->mOwner;
    if (owner != SysGetThreadID() || pSection->mCount == 0) {
        OSUnlockMutex(&_Sys_CriticalSectionMutex);
        OSLockMutex(&pSection->mMutex);
        pSection->mOwner = SysGetThreadID();
        pSection->mCount++;
    } else {
        pSection->mCount++;
        OSUnlockMutex(&_Sys_CriticalSectionMutex);
    }
}

void SysExitCriticalSectionFunc(SysCriticalSection_t *pSection)
{
    if (--pSection->mCount == 0) {
        OSUnlockMutex(&pSection->mMutex);
    }
}

void SysShutdownCriticalSectionFunc(SysCriticalSection_t *pSection)
{
    pSection->mOwner = 0;
    _Sys_CriticalSectionCount--;
}

void SysInitSemaphore(OSMutex **ppMutex)
{
    OSMutex *pMutex = fn_801D2B7C(sizeof(OSMutex), 0, 0);

    *ppMutex = pMutex;
    OSInitMutex(pMutex);
}

int SysLockSemaphore(OSMutex **ppMutex)
{
    OSLockMutex(*ppMutex);
    return 1;
}

void SysUnlockSemaphore(OSMutex **ppMutex)
{
    OSUnlockMutex(*ppMutex);
}

void SysShutdownSemaphore(OSMutex **ppMutex)
{
    fn_801D2BD0(*ppMutex);
    *ppMutex = 0;
}

void SysReleaseTimeFunc(void)
{
    SysCheckReset();
    FileAsyncCheckError();
    OSYieldThread();
}

int SysGetThreadID(void)
{
    return (int)OSGetCurrentThread();
}

void SysCopyRealTimeClock(SysTime_t *pTime)
{
    unsigned char enabled = OSDisableInterrupts();

    *pTime = _Sys_RealTimeClock;
    OSRestoreInterrupts(enabled);
}

void SysInitRealTimeClock(void)
{
    unsigned char aDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long long secs;
    long long days;
    unsigned char enabled;
    unsigned int daysInYear;
    unsigned short month;
    int year;
    int m;

    secs = OSTicksToSeconds(OSGetTime());
    enabled = OSDisableInterrupts();
    _Sys_RealTimeClock.mSeconds = secs % 60;
    _Sys_RealTimeClock.mMinutes = (long long)floorf(secs * (1.0f / 60.0f)) % 60;
    _Sys_RealTimeClock.mHours = (long long)floorf(secs * (1.0f / 3600.0f)) % 24;
    days = floorf(secs * (1.0f / 86400.0f));
    _Sys_RealTimeClock.mYear = 0;
    daysInYear = 366;
    while (days >= daysInYear) {
        days -= daysInYear;
        _Sys_RealTimeClock.mYear++;
        daysInYear = DateIsYearLeap(_Sys_RealTimeClock.mYear) ? 366 : 365;
    }
    _Sys_RealTimeClock.mYear += 2000;
    aDays[2] = DateIsYearLeap(_Sys_RealTimeClock.mYear) ? 29 : 28;
    month = 1;
    while (days >= aDays[month]) {
        days -= aDays[month++];
    }
    _Sys_RealTimeClock.mMonth = month;
    _Sys_RealTimeClock.mDays = days + 1;
    _Sys_RealTimeClock.mHundredths = 0;
    _Sys_ClockVsyncTicks = 0;
    _Sys_ClockUnixSeconds = 0;
    for (year = 1970; year < _Sys_RealTimeClock.mYear; year++) {
        _Sys_ClockUnixSeconds += DateGetNumDaysInYear(year) * 86400;
    }
    for (m = 1; m < _Sys_RealTimeClock.mMonth; m++) {
        _Sys_ClockUnixSeconds += DateGetNumDaysInMonth(m, _Sys_RealTimeClock.mYear) * 86400;
    }
    _Sys_ClockUnixSeconds = _Sys_ClockUnixSeconds + (_Sys_RealTimeClock.mDays - 1) * 86400 + _Sys_RealTimeClock.mHours * 3600 + _Sys_RealTimeClock.mMinutes * 60 + _Sys_RealTimeClock.mSeconds;
    OSRestoreInterrupts(enabled);
}

void SysUpdateRealTimeClock(void)
{
    unsigned char enabled = OSDisableInterrupts();
    unsigned int ms;
    unsigned int days;

    _Sys_ClockVsyncTicks++;
    switch (GlibGetTvMode()) {
    case 1:
        ms = _Sys_ClockVsyncTicks * 20;
        break;
    case 0:
    default:
        ms = _Sys_ClockVsyncTicks * 1000 / 60;
        break;
    }
    _Sys_RealTimeClock.mHundredths = ms / 10;
    if (ms > 999) {
        _Sys_ClockVsyncTicks = 0;
        _Sys_ClockUnixSeconds++;
        _Sys_RealTimeClock.mHundredths = 0;
        if (++_Sys_RealTimeClock.mSeconds > 59) {
            _Sys_RealTimeClock.mSeconds = 0;
            if (++_Sys_RealTimeClock.mMinutes > 59) {
                _Sys_RealTimeClock.mMinutes = 0;
                if (++_Sys_RealTimeClock.mHours > 23) {
                    _Sys_RealTimeClock.mHours = 0;
                    _Sys_RealTimeClock.mDays++;
                    switch (_Sys_RealTimeClock.mMonth) {
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        days = 30;
                        break;
                    case 2:
                        days = DateIsYearLeap(_Sys_RealTimeClock.mYear) ? 29 : 28;
                        break;
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        days = 31;
                        break;
                    default:
                        days = 31;
                        break;
                    }
                    if (_Sys_RealTimeClock.mDays > days) {
                        _Sys_RealTimeClock.mDays = 1;
                        if (++_Sys_RealTimeClock.mMonth > 12) {
                            _Sys_RealTimeClock.mMonth = 1;
                            _Sys_RealTimeClock.mYear++;
                        }
                    }
                }
            }
        }
    }
    OSRestoreInterrupts(enabled);
}

int SysEnableReset(int enable)
{
    unsigned char previous = _Sys_ResetEnabled;

    _Sys_ResetEnabled = enable;
    return previous;
}

void SysCheckReset(void)
{
    unsigned char pressed = OSGetResetButtonState();

    if (_Sys_ResetPending || (!pressed && _Sys_PreviousResetState)) {
        int reset = 1;

        if (_Sys_ResetCallback) {
            reset = _Sys_ResetCallback(1);
        }
        if (reset && _Sys_ResetEnabled) {
            SysResetSystem(0);
            _Sys_ResetPending = 0;
        } else {
            _Sys_ResetPending = 1;
        }
    }
    _Sys_PreviousResetState = pressed;
}

void SysResetSystem(int code)
{
    _SysSetupReset();
    OSResetSystem(0, 1, code);
}

void SysHotResetSystem(void)
{
    _SysSetupReset();
    OSResetSystem(1, 1, 1);
}

SysResetCallback_t SysSetResetCallback(SysResetCallback_t pCallback)
{
    SysResetCallback_t pPrevious = _Sys_ResetCallback;

    _Sys_ResetCallback = pCallback;
    return pPrevious;
}
