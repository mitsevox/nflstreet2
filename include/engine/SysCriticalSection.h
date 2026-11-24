#ifndef ENGINE_SYS_CRITICAL_SECTION_H
#define ENGINE_SYS_CRITICAL_SECTION_H

#include <dolphin/os/OSMutex.h>

/* Recursive engine lock: OS mutex, owning thread and recursion depth. */
typedef struct SysCriticalSection_t {
    OSMutex mMutex;
    int mOwner;
    int mCount;
} SysCriticalSection_t;

#ifdef __cplusplus
extern "C" {
#endif
void SysInitCriticalSectionFunc(SysCriticalSection_t *pLock);
void SysEnterCriticalSectionFunc(SysCriticalSection_t *pLock);
void SysExitCriticalSectionFunc(SysCriticalSection_t *pLock);
void SysShutdownCriticalSectionFunc(SysCriticalSection_t *pLock);
#ifdef __cplusplus
}
#endif

#endif
