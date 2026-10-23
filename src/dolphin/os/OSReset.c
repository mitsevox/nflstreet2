#include "__os.h"
extern void Reset(s32 resetCode);
#include "dolphin/os.h"
#include "dolphin/vi.h"
#include "dolphin/hw_regs.h"

volatile u8 DAT_800030e2 : 0x800030e2;
typedef struct OSResetQueue
{
    OSResetFunctionInfo* first;
    OSResetFunctionInfo* last;
} OSResetQueue;

static OSResetQueue ResetFunctionQueue;
static u32 bootThisDol;

void OSRegisterResetFunction(OSResetFunctionInfo* func)
{
    OSResetFunctionInfo* tmp;
    OSResetFunctionInfo* iter;

    for (iter = ResetFunctionQueue.first; iter && iter->priority <= func->priority;
         iter = iter->next)
        ;

    if (iter == NULL)
    {
        tmp = ResetFunctionQueue.last;
        if (tmp == NULL)
        {
            ResetFunctionQueue.first = func;
        }
        else
        {
            tmp->next = func;
        }
        func->prev = tmp;
        func->next = NULL;
        ResetFunctionQueue.last = func;
        return;
    }

    func->next = iter;
    tmp = iter->prev;
    iter->prev = func;
    func->prev = tmp;
    if (tmp == NULL)
    {
        ResetFunctionQueue.first = func;
        return;
    }
    tmp->next = func;
}

inline BOOL __OSCallResetFunctions(u32 arg0)
{
    OSResetFunctionInfo* info;
    s32 err = 0;

    for (info = ResetFunctionQueue.first; info != NULL && err == 0; info = info->next)
    {
        err |= !info->func(arg0);
    }
    err |= !__OSSyncSram();
    if (err)
    {
        return 0;
    }
    return 1;
}





inline void KillThreads(void)
{
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next)
    {
        next = thread->linkActive.next;
        switch (thread->state)
        {
        case 1:
        case 4:
            OSCancelThread(thread);
            break;
        default:
            break;
        }
    }
}

asm void Reset(s32 resetCode)
{
    nofralloc
    b L_jump_0
L_hid0:
    mfspr r8, HID0
    ori r8, r8, 0x8
    mtspr HID0, r8
    isync
    sync
    nop
    b L_wait
L_jump_0:
    b L_jump_1
L_wait:
    mftb r5, 268
L_wait_loop:
    mftb r6, 268
    subf r7, r5, r6
    cmplwi r7, 0x1124
    blt L_wait_loop
    nop
    b L_reset
L_jump_1:
    b L_jump_2
L_reset:
    lis r8, 0xcc00
    ori r8, r8, 0x3000
    li r4, 0x3
    stw r4, 0x24(r8)
    stw r3, 0x24(r8)
    nop
    b L_halt
L_jump_2:
    b L_jump_3
L_halt:
    nop
    b L_halt
L_jump_3:
    b L_hid0
}

void __OSDoHotReset(s32 arg0)
{
    OSDisableInterrupts();
    __VIRegs[1] = 0;
    ICFlashInvalidate();
    Reset(arg0 * 8);
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
    BOOL rc;
    BOOL disableRecalibration;

    OSDisableScheduler();
    __OSStopAudioSystem();

    if (reset == OS_RESET_SHUTDOWN || (reset == OS_RESET_RESTART && bootThisDol != 0))
    {
        disableRecalibration = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallResetFunctions(FALSE))
    {
        ;
    }

    if (reset == OS_RESET_HOTRESET && forceMenu)
    {
        OSSram* sram;

        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(TRUE);

        while (!__OSSyncSram())
        {
            ;
        }
    }

    OSDisableInterrupts();
    __OSCallResetFunctions(TRUE);
    LCDisable();
    if (reset == OS_RESET_HOTRESET)
    {
        __OSDoHotReset(resetCode);
    }
    else if (reset == OS_RESET_RESTART)
    {
        if ((*(u32*)OSPhysicalToCached(0x30EC) = bootThisDol) != 0)
        {
            __PADDisableRecalibration(disableRecalibration);
        }
        KillThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }

    KillThreads();
    memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
    memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
    memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
    memset(OSPhysicalToCached(0x3000), 0, 0xC0);
    memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);
    memset(OSPhysicalToCached(0x30E2), 0, 1);

    __PADDisableRecalibration(disableRecalibration);
}

u32 OSGetResetCode(void)
{
    if (DAT_800030e2 != 0)
    {
        return 0x80000000;
    }
    return ((__PIRegs[9] & ~7) >> 3);
}
