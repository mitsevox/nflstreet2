#include "__os.h"
#include <dolphin/os.h>

#define OS_SYSTEMTIME_BASE 0x30D8

asm OSTime OSGetTime(void)
{
jump:
    nofralloc

    mftbu r3
    mftb r4

    mftbu r5
    cmpw r3, r5
    bne jump

    blr
}

asm OSTick OSGetTick(void)
{
    nofralloc

    mftb r3
    blr
}

OSTime __OSGetSystemTime(void)
{
    BOOL enabled;
    OSTime* timeAdjustAddr = (OSTime*)(OS_BASE_CACHED + OS_SYSTEMTIME_BASE);
    OSTime result;

    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + OSGetTime();
    OSRestoreInterrupts(enabled);

    return result;
}

