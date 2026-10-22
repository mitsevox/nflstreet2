#include <dolphin/os.h>
#include <dolphin/os/OSMemory.h>

#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))
#define ROUND(n, a) (((u32)(n) + (a)-1) & ~((a)-1))

#include "__os.h"

void __OSInitMemoryProtection(void);
extern void Config24MB(void);
extern void Config48MB(void);
extern void RealMode(u32 addr);

static BOOL OnReset(BOOL final);

static OSResetFunctionInfo ResetFunctionInfo = {
    OnReset,
    127,
};

static BOOL OnReset(BOOL final)
{
    if (final != FALSE)
    {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xf0000000);
    }
    return TRUE;
}

static void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    u32 addr;
    u32 cause;

    cause = __MEMRegs[0xf];
    addr = (((u32)__MEMRegs[0x12] & 0x3ff) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;

    if (__OSErrorTable[OS_ERROR_PROTECTION])
    {
        __OSErrorTable[OS_ERROR_PROTECTION](OS_ERROR_PROTECTION, context, cause, addr);
        return;
    }

    __OSUnhandledException(OS_ERROR_PROTECTION, context, cause, addr);
}







asm void Config24MB(void)
{
    nofralloc
    li r7, 0x0
    lis r4, 0x0
    addi r4, r4, 0x2
    lis r3, 0x8000
    addi r3, r3, 0x1ff
    lis r6, 0x100
    addi r6, r6, 0x2
    lis r5, 0x8100
    addi r5, r5, 0xff
    isync
    mtdbatu 0, r7
    mtdbatl 0, r4
    mtdbatu 0, r3
    isync
    mtibatu 0, r7
    mtibatl 0, r4
    mtibatu 0, r3
    isync
    mtdbatu 2, r7
    mtdbatl 2, r6
    mtdbatu 2, r5
    isync
    mtibatu 2, r7
    mtibatl 2, r6
    mtibatu 2, r5
    isync
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    mflr r3
    mtsrr0 r3
    rfi
}

asm void Config48MB(void)
{
    nofralloc
    li r7, 0x0
    lis r4, 0x0
    addi r4, r4, 0x2
    lis r3, 0x8000
    addi r3, r3, 0x3ff
    lis r6, 0x200
    addi r6, r6, 0x2
    lis r5, 0x8200
    addi r5, r5, 0x1ff
    isync
    mtdbatu 0, r7
    mtdbatl 0, r4
    mtdbatu 0, r3
    isync
    mtibatu 0, r7
    mtibatl 0, r4
    mtibatu 0, r3
    isync
    mtdbatu 2, r7
    mtdbatl 2, r6
    mtdbatu 2, r5
    isync
    mtibatu 2, r7
    mtibatl 2, r6
    mtibatu 2, r5
    isync
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    mflr r3
    mtsrr0 r3
    rfi
}

asm void RealMode(register u32 addr)
{
    nofralloc
    clrlwi addr, addr, 2
    mtsrr0 addr
    mfmsr addr
    rlwinm addr, addr, 0, 28, 25
    mtsrr1 addr
    rfi
}

void __OSInitMemoryProtection(void)
{
    u32 simulatedSize;
    BOOL enabled;
    simulatedSize = *(u32*)(OSPhysicalToCached(0x00F0));
    enabled = OSDisableInterrupts();

    __MEMRegs[16] = 0;
    __MEMRegs[8] = 0xFF;

    __OSMaskInterrupts(OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1 | OS_INTERRUPTMASK_MEM_2 |
                       OS_INTERRUPTMASK_MEM_3);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_0, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_1, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_2, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_3, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_ADDRESS, MEMIntrruptHandler);
    OSRegisterResetFunction(&ResetFunctionInfo);

    if (*(u32*)(OSPhysicalToCached(0x00F0)) < *(u32*)(OSPhysicalToCached(0x0028)) &&
        *(u32*)(OSPhysicalToCached(0x00F0)) == 0x1800000)
    {
        DCInvalidateRange((void*)0x81800000, 0x1800000);
        __MEMRegs[20] = 2;
    }

    if (simulatedSize <= 0x1800000)
    {
        RealMode((u32)&Config24MB);
    }
    else if (simulatedSize <= 0x3000000)
    {
        RealMode((u32)&Config48MB);
    }

    __OSUnmaskInterrupts(OS_INTERRUPTMASK_MEM_ADDRESS);
    OSRestoreInterrupts(enabled);
}
