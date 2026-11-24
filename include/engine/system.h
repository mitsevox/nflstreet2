#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

#include "engine/SysSetLastErrorFunc.h"
#include "engine/SysCriticalSection.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SysTimer_t {
    void *pFunc;
    unsigned int mUnk4;
    unsigned int mUnk8;
    unsigned short mFlags;
    int mUnknown10;
    char mUnknown14[8];
    int mUnknown1C;
    unsigned int mCount;
} SysTimer_t;

typedef struct SysTime_t {
    unsigned char mSeconds;
    unsigned char mMinutes;
    unsigned char mHours;
    unsigned char mDays;
    unsigned char mMonth;
    unsigned short mYear;
    unsigned int mHundredths;
} SysTime_t;

/* system.c */
unsigned int SysGetSystemTime(void);
void SysIncSystemTime(void);
unsigned int SysGetVsyncCounter(void);

/* mutex.c */
struct OSMutex *_StreamMUTEX_alloc(void);
void _StreamMUTEX_free(struct OSMutex *pMutex);
void _StreamMUTEX_lock(struct OSMutex *pMutex);
void _StreamMUTEX_unlock(struct OSMutex *pMutex);

typedef int (*SysResetCallback_t)(int resetRequested);

/* llsystem.c */
int SysInitPlatform(void);
int SysShutdownPlatform(void);
int SysStartTimer(SysTimer_t *pTimer);
int SysStopTimer(SysTimer_t *pTimer);
void SysInitSemaphore(struct OSMutex **ppMutex);
int SysLockSemaphore(struct OSMutex **ppMutex);
void SysUnlockSemaphore(struct OSMutex **ppMutex);
void SysShutdownSemaphore(struct OSMutex **ppMutex);
void SysReleaseTimeFunc(void);
int SysGetThreadID(void);
void SysCopyRealTimeClock(SysTime_t *pTime);
void SysInitRealTimeClock(void);
void SysUpdateRealTimeClock(void);
int SysEnableReset(int enable);
void SysCheckReset(void);
void SysResetSystem(int forceMenu);
void SysHotResetSystem(void);
SysResetCallback_t SysSetResetCallback(SysResetCallback_t callback);

#ifdef __cplusplus
}
#endif

#endif
