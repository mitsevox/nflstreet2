/* Mutex hooks for the file streaming system, built on the engine semaphores. */

#include "engine/system.h"

void _StreamMUTEX_init(void)
{
}

struct OSMutex *_StreamMUTEX_alloc(void)
{
    struct OSMutex *pMutex;

    SysInitSemaphore(&pMutex);
    return pMutex;
}

void _StreamMUTEX_free(struct OSMutex *pMutex)
{
    SysShutdownSemaphore(&pMutex);
}

void _StreamMUTEX_lock(struct OSMutex *pMutex)
{
    SysLockSemaphore(&pMutex);
}

void _StreamMUTEX_unlock(struct OSMutex *pMutex)
{
    SysUnlockSemaphore(&pMutex);
}
