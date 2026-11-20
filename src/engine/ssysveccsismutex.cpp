/* Sound system CSIS mutex hookup (ssysveccsismutex.cpp): points the sound system's lock and
   unlock vector at the CSIS mutex, so sound calls share the CSIS critical section. */

#include "engine/sndstrm.h"
#include "engine/csis.h"
#include "engine/ssys.h"

namespace Snd {

void CsisMutexLock(void)
{
    Csis::System::Lock();
}

void CsisMutexUnlock(void)
{
    Csis::System::Unlock();
}

int System::VectorToCsisMutex(void)
{
    if (gMutexLockFn == CsisMutexLock) {
        return 0;
    }
    gMutexLockFn = CsisMutexLock;
    gMutexUnlockFn = CsisMutexUnlock;
    return 0;
}

}
