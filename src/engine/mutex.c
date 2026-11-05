/* Mutex hooks for the file streaming system, built on the engine semaphores. */

#include "engine/system.h"

void _StreamMUTEX_init(void)
{
}

struct OSMutex *_StreamMUTEX_alloc(void)
{
    struct OSMutex *pMutex;

    fn_801F80E8(&pMutex);
    return pMutex;
}

void _StreamMUTEX_free(struct OSMutex *pMutex)
{
    fn_801F8174(&pMutex);
}

void _StreamMUTEX_lock(struct OSMutex *pMutex)
{
    fn_801F8128(&pMutex);
}

void _StreamMUTEX_unlock(struct OSMutex *pMutex)
{
    fn_801F8150(&pMutex);
}
