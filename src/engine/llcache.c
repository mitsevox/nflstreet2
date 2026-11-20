/* Locked cache: turns the CPU's locked data cache on once when the engine
   needs it and off again unless it is being held on. */

#include <dolphin/os/OSCache.h>

static unsigned char _LLCache_bLocked = 0;
static unsigned char _LLCache_bHold = 0;

void LLCacheLockedEnable(void)
{
    if (_LLCache_bLocked == 0) {
        LCEnable();
        _LLCache_bLocked = 1;
    }
}

void LLCacheLockedDisable(void)
{
    if (_LLCache_bLocked != 0 && _LLCache_bHold == 0) {
        LCDisable();
        _LLCache_bLocked = 0;
    }
}
