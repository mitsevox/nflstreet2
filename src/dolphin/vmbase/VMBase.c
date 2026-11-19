/* Nintendo Dolphin SDK virtual-memory base layer (vmbase.a, VMBase.o): owns the CPU's hashed page
 * table and the lock and reverse tables, maps the virtual window 0x7E000000-0x80000000 through
 * segment register 7, and patches the DSI and ISI exception vectors so that page faults in that
 * window reach the VM library's page-in handler. The game's virtual memory (vm.a) sits on top. */
#include <dolphin/types.h>
#include <dolphin/os.h>
#include <dolphin/__vm.h>

#define OS_CURRENTCONTEXT_PADDR 0x00C0
#define OS_CURRENTCONTEXT 0x00D4

static inline void ICBI(register void* p) {
    register int zero = 0;
    asm {
        isync
        icbi p, zero
    }
}

static u32 sSavedSDR1;
static u32 sSavedSR7;
static BOOL sInitialized;
static void (*sPageFaultHandler)(u32);
static u8* sLockedPageTable;
static u32* sReversePageTable;
static u32* sPageTable;

void VMBASEInit(void (*pageFaultHandler)(u32));
void VMBASESetPageTableEntry(u32 virtualAddr, u32 physAddr, u32 physPage);
void VMBASEClearPageTableEntry(u32 virtualAddr, u32 physPage);
BOOL __VMBASEIsPageValid(u32 virtualAddr);
BOOL __VMBASEIsPageReferenced(u32 virtualAddr);
BOOL __VMBASEIsPageChanged(u32 virtualAddr);
void VMBASESetPageReferenced(u32 virtualAddr, BOOL referenced);
void __VMBASEInvalidateTLBEntry(register u32 virtualAddr);
u32 __VMBASEGetVirtualAddr(u32 physPage);
void __VMBASESetVirtualAddr(u32 physPage, u32 virtualAddr);
BOOL __VMBASEIsPageLocked(u32 physPage);
void __VMBASESetPageLocked(u32 physPage, BOOL locked);
void __VMBASESetPageFaultHandler(void (*handler)(u32));
void __VMBASEInitPageTable(void);
void __VMBASEInitLockedPageTable(void);
void __VMBASEInitReversePageTable(void);
void __VMBASEInvalidatePageTable(void);
void __VMBASEInvalidateLockedPageTable(void);
void __VMBASEInvalidateReversePageTable(void);
u32* __VMBASEGetPTE(u32 virtualAddr);
void __VMBASEInvalidateEntireTLB(void);
void __VMBASESetupVMRegisters(void);
void __VMBASESetMSRAndSDR1(register u32 msr, register u32 sdr1, register u32 unused);
void __VMBASESetMSRAndSDR1_RealMode(void);
void __VMBASESetMSRAndSDR1_Done(void);
void __VMBASESetMSRAndSDR1_Return(void);
void __VMBASESetupExceptionHandlers(void);
void __VMBASEDSIExceptionHandler(void);
void __VMBASEDSIExceptionHandler_OriginalInstruction(void);
void __VMBASEDSIExceptionHandler_SetBranchBack(void);
void __VMBASEDSIExceptionHandler_Service(void);
void __VMBASEDSIServiceException(OSContext* context, u32 dar);
void __VMBASEISIExceptionHandler(void);
void __VMBASEISIExceptionHandler_OriginalInstruction(void);
void __VMBASEISIExceptionHandler_SetBranchBack(void);
void __VMBASEISIExceptionHandler_Service(void);
void __VMBASEISIServiceException(OSContext* context);

void VMBASEInit(void (*pageFaultHandler)(u32)) {
    BOOL enabled;
    u32 slack;

    if (!sInitialized) {
        enabled = OSDisableInterrupts();
        sInitialized = TRUE;
        __VMBASESetPageFaultHandler(pageFaultHandler);
        slack = 0x10000 - ((u32)OSGetArenaLo() & 0xFFFF);
        if (slack >= 0x5000) {
            __VMBASEInitLockedPageTable();
            __VMBASEInitReversePageTable();
            __VMBASEInitPageTable();
        } else if (slack >= 0x4000) {
            __VMBASEInitReversePageTable();
            __VMBASEInitPageTable();
            __VMBASEInitLockedPageTable();
        } else if (slack >= 0x1000) {
            __VMBASEInitLockedPageTable();
            __VMBASEInitPageTable();
            __VMBASEInitReversePageTable();
        } else {
            __VMBASEInitPageTable();
            __VMBASEInitLockedPageTable();
            __VMBASEInitReversePageTable();
        }
        __VMBASESetupExceptionHandlers();
        __VMBASESetupVMRegisters();
        __VMBASEInvalidateEntireTLB();
        OSRestoreInterrupts(enabled);
    }
}

void VMBASESetPageTableEntry(u32 virtualAddr, u32 physAddr, u32 physPage) {
    u32* pte;
    BOOL enabled;

    pte = __VMBASEGetPTE(virtualAddr);
    enabled = OSDisableInterrupts();
    pte[0] = 0x80000000 | ((virtualAddr >> 22) & 0x3F);
    pte[1] = physAddr & 0x0FFFF000;
    DCStoreRange(pte, 8);
    __VMBASEInvalidateTLBEntry(virtualAddr);
    __VMBASESetVirtualAddr(physPage, virtualAddr);
    OSRestoreInterrupts(enabled);
}

void VMBASEClearPageTableEntry(u32 virtualAddr, u32 physPage) {
    BOOL enabled;
    u32* pte;

    enabled = OSDisableInterrupts();
    pte = __VMBASEGetPTE(virtualAddr);
    pte[0] = 0;
    pte[1] = 0;
    DCStoreRange(pte, 8);
    __VMBASEInvalidateTLBEntry(virtualAddr);
    __VMBASESetVirtualAddr(physPage, 0);
    __VMBASESetPageLocked(physPage, FALSE);
    OSRestoreInterrupts(enabled);
}

BOOL __VMBASEIsPageValid(u32 virtualAddr) {
    return __VMBASEGetPTE(virtualAddr)[0] >> 31;
}

BOOL __VMBASEIsPageReferenced(u32 virtualAddr) {
    return (__VMBASEGetPTE(virtualAddr)[1] >> 8) & 1;
}

BOOL __VMBASEIsPageChanged(u32 virtualAddr) {
    return (__VMBASEGetPTE(virtualAddr)[1] >> 7) & 1;
}

void VMBASESetPageReferenced(u32 virtualAddr, BOOL referenced) {
    BOOL enabled;
    u32* pte;

    enabled = OSDisableInterrupts();
    pte = __VMBASEGetPTE(virtualAddr);
    if (referenced) {
        pte[1] |= 0x100;
    } else {
        pte[1] &= 0xFFFFFEFF;
    }
    DCStoreRange(&pte[1], 4);
    __VMBASEInvalidateTLBEntry(virtualAddr);
    OSRestoreInterrupts(enabled);
}

asm void __VMBASEInvalidateTLBEntry(register u32 virtualAddr) {
    nofralloc
    rlwinm r0, virtualAddr, 0, 14, 19
    tlbsync
    tlbie r0
    blr
}

u32 __VMBASEGetVirtualAddr(u32 physPage) {
    return sReversePageTable[physPage];
}

void __VMBASESetVirtualAddr(u32 physPage, u32 virtualAddr) {
    sReversePageTable[physPage] = virtualAddr;
}

BOOL __VMBASEIsPageLocked(u32 physPage) {
    return sLockedPageTable[physPage];
}

void __VMBASESetPageLocked(u32 physPage, BOOL locked) {
    if (locked) {
        sLockedPageTable[physPage] = TRUE;
    } else {
        sLockedPageTable[physPage] = FALSE;
    }
}

void __VMBASESetPageFaultHandler(void (*handler)(u32)) {
    sPageFaultHandler = handler;
}

void __VMBASEInitPageTable(void) {
    u32 arenaLo = (u32)OSGetArenaLo();

    sPageTable = (u32*)(arenaLo + 0x10000 - (arenaLo & 0xFFFF));
    OSSetArenaLo((u8*)sPageTable + 0x10000);
    __VMBASEInvalidatePageTable();
}

void __VMBASEInitLockedPageTable(void) {
    sLockedPageTable = OSGetArenaLo();
    OSSetArenaLo(sLockedPageTable + 0x1000);
    __VMBASEInvalidateLockedPageTable();
}

void __VMBASEInitReversePageTable(void) {
    sReversePageTable = OSGetArenaLo();
    OSSetArenaLo(sReversePageTable + 0x1000);
    __VMBASEInvalidateReversePageTable();
}

void __VMBASEInvalidatePageTable(void) {
    BOOL enabled;
    u32 i;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 0x10000; i += 8) {
        *(u32*)((u8*)sPageTable + i) = 0;
        *(u32*)((u8*)sPageTable + i + 4) = 0;
    }
    DCStoreRange(sPageTable, 0x10000);
    __VMBASEInvalidateEntireTLB();
    OSRestoreInterrupts(enabled);
}

void __VMBASEInvalidateLockedPageTable(void) {
    u32 i;

    for (i = 0; i < 0x1000; i++) {
        *(u8*)((u8*)sLockedPageTable + i) = FALSE;
    }
}

void __VMBASEInvalidateReversePageTable(void) {
    u32 i;

    for (i = 0; i < 0x1000 * 4; i += 4) {
        *(u32*)((u8*)sReversePageTable + i) = 0;
    }
}

u32* __VMBASEGetPTE(u32 virtualAddr) {
    return (u32*)((u32)sPageTable | ((virtualAddr >> 6) & 0xFFC0) | ((virtualAddr >> 19) & 0x38));
}

void __VMBASEInvalidateEntireTLB(void) {
    register u32 addr;
    int i;

    addr = 0;
    asm { tlbsync }
    for (i = 0; i < 64; i++) {
        asm { tlbie addr }
        addr += 0x1000;
    }
}

void __VMBASESetupVMRegisters(void) {
    register u32 sr7;
    register u32 zero;
    register u32 msr;
    register u32 sdr1;

    zero = 0;
    asm {
        mfsr sr7, 7
        mtsr 7, zero
    }
    sSavedSR7 = sr7;
    asm {
        mfmsr msr
        mfsdr1 sdr1
    }
    sSavedSDR1 = sdr1;
    sdr1 = (sdr1 & 0xFFFF) + ((u32)sPageTable & 0x7FFF0000);
    __VMBASESetMSRAndSDR1(msr & ~0x30, sdr1, 0);
}

asm void __VMBASESetMSRAndSDR1(register u32 msr, register u32 sdr1, register u32 unused) {
    nofralloc
    mtsrr1 msr
    lis r5, __VMBASESetMSRAndSDR1_RealMode@ha
    addi r5, r5, __VMBASESetMSRAndSDR1_RealMode@l
    clrlwi r5, r5, 1
    mtsrr0 r5
    rfi
}

asm void __VMBASESetMSRAndSDR1_RealMode(void) {
    nofralloc
    sync
    mtsdr1 r4
    sync
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    lis r5, __VMBASESetMSRAndSDR1_Done@ha
    addi r5, r5, __VMBASESetMSRAndSDR1_Done@l
    mtsrr0 r5
    rfi
entry __VMBASESetMSRAndSDR1_Done
    nop
}

asm void __VMBASESetMSRAndSDR1_Return(void) {
    nofralloc
    blr
}

void __VMBASESetupExceptionHandlers(void) {
    u32* addr;

    {
        u32 original;
        u32 offset;
        u32 back;

        original = *(u32*)OSPhysicalToCached(0x300);
        offset = OSCachedToPhysical(__VMBASEDSIExceptionHandler);
        offset -= 0x300;
        *(u32*)OSPhysicalToCached(0x300) = 0x48000000 | offset;
        DCFlushRangeNoSync(OSPhysicalToCached(0x300), 4);
        __sync();
        ICBI(OSPhysicalToCached(0x300));
        addr = (u32*)__VMBASEDSIExceptionHandler_OriginalInstruction;
        *addr = original;
        DCFlushRangeNoSync(addr, 4);
        __sync();
        ICBI(addr);
        addr = (u32*)__VMBASEDSIExceptionHandler_SetBranchBack;
        back = OSCachedToPhysical(addr);
        back -= 0x304;
        *addr = 0x48000000 | (-back & 0x03FFFFFF);
        DCFlushRangeNoSync(addr, 4);
        __sync();
        ICBI(addr);
    }
    {
        u32 original;
        u32 offset;
        u32 back;

        original = *(u32*)OSPhysicalToCached(0x400);
        offset = OSCachedToPhysical(__VMBASEISIExceptionHandler);
        offset -= 0x400;
        *(u32*)OSPhysicalToCached(0x400) = 0x48000000 | offset;
        DCFlushRangeNoSync(OSPhysicalToCached(0x400), 4);
        __sync();
        ICBI(OSPhysicalToCached(0x400));
        addr = (u32*)__VMBASEISIExceptionHandler_OriginalInstruction;
        *addr = original;
        DCFlushRangeNoSync(addr, 4);
        __sync();
        ICBI(addr);
        addr = (u32*)__VMBASEISIExceptionHandler_SetBranchBack;
        back = OSCachedToPhysical(addr);
        back -= 0x404;
        *addr = 0x48000000 | (-back & 0x03FFFFFF);
        DCFlushRangeNoSync(addr, 4);
        __sync();
        ICBI(addr);
    }
}

asm void __VMBASEDSIExceptionHandler(void) {
    nofralloc
    mtsprg 0, r4
    mtsprg 1, r5
    mtsprg 2, r6
    mfcr r4
    mtsprg 3, r4
    mfdar r5
    li r6, 0x7E
    slwi r6, r6, 24
    cmplw r5, r6
    blt @notvm
    mfdar r5
    li r6, 0x80
    slwi r6, r6, 24
    cmplw r5, r6
    bge @notvm
    mfdsisr r5
    rlwinm r6, r5, 0, 1, 1
    cmplwi r6, 0
    beq @notvm
    mfsprg r4, 3
    mtcrf 0xFF, r4
    mfsprg r4, 0
    mfsprg r5, 1
    mfsprg r6, 2
    mtsprg 0, r4
    lwz r4, OS_CURRENTCONTEXT_PADDR
    stw r3, OS_CONTEXT_R3(r4)
    mfsprg r3, 0
    stw r3, OS_CONTEXT_R4(r4)
    stw r5, OS_CONTEXT_R5(r4)
    lhz r3, OS_CONTEXT_STATE(r4)
    ori r3, r3, OS_CONTEXT_STATE_EXC
    sth r3, OS_CONTEXT_STATE(r4)
    mfcr r3
    stw r3, OS_CONTEXT_CR(r4)
    mflr r3
    stw r3, OS_CONTEXT_LR(r4)
    mfctr r3
    stw r3, OS_CONTEXT_CTR(r4)
    mfxer r3
    stw r3, OS_CONTEXT_XER(r4)
    mfsrr0 r3
    stw r3, OS_CONTEXT_SRR0(r4)
    mfsrr1 r3
    stw r3, OS_CONTEXT_SRR1(r4)
    mr r5, r3
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    lwz r3, OS_CURRENTCONTEXT
    lis r5, __VMBASEDSIExceptionHandler_Service@ha
    addi r5, r5, __VMBASEDSIExceptionHandler_Service@l
    mtsrr0 r5
    rfi
@notvm:
    mfsprg r4, 3
    mtcrf 0xFF, r4
    mfsprg r4, 0
    mfsprg r5, 1
    mfsprg r6, 2
entry __VMBASEDSIExceptionHandler_OriginalInstruction
    nop
entry __VMBASEDSIExceptionHandler_SetBranchBack
    nop
entry __VMBASEDSIExceptionHandler_Service
    OS_EXCEPTION_SAVE_GPRS(r3)
    mfdar r4
    b __VMBASEDSIServiceException
}

void __VMBASEDSIServiceException(OSContext* context, u32 dar) {
    OSContext exceptionContext;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    sPageFaultHandler(dar);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}

asm void __VMBASEISIExceptionHandler(void) {
    nofralloc
    mtsprg 0, r4
    mtsprg 1, r5
    mtsprg 2, r6
    mfcr r4
    mtsprg 3, r4
    mfsrr0 r5
    li r6, 0x7E
    slwi r6, r6, 24
    cmplw r5, r6
    blt @notvm
    mfsrr0 r5
    li r6, 0x80
    slwi r6, r6, 24
    cmplw r5, r6
    bge @notvm
    mfsrr1 r5
    rlwinm r6, r5, 0, 1, 1
    cmplwi r6, 0
    beq @notvm
    mfsprg r4, 3
    mtcrf 0xFF, r4
    mfsprg r4, 0
    mfsprg r5, 1
    mfsprg r6, 2
    mtsprg 0, r4
    lwz r4, OS_CURRENTCONTEXT_PADDR
    stw r3, OS_CONTEXT_R3(r4)
    mfsprg r3, 0
    stw r3, OS_CONTEXT_R4(r4)
    stw r5, OS_CONTEXT_R5(r4)
    lhz r3, OS_CONTEXT_STATE(r4)
    ori r3, r3, OS_CONTEXT_STATE_EXC
    sth r3, OS_CONTEXT_STATE(r4)
    mfcr r3
    stw r3, OS_CONTEXT_CR(r4)
    mflr r3
    stw r3, OS_CONTEXT_LR(r4)
    mfctr r3
    stw r3, OS_CONTEXT_CTR(r4)
    mfxer r3
    stw r3, OS_CONTEXT_XER(r4)
    mfsrr0 r3
    stw r3, OS_CONTEXT_SRR0(r4)
    mfsrr1 r3
    stw r3, OS_CONTEXT_SRR1(r4)
    mr r5, r3
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    lwz r3, OS_CURRENTCONTEXT
    lis r5, __VMBASEISIExceptionHandler_Service@ha
    addi r5, r5, __VMBASEISIExceptionHandler_Service@l
    mtsrr0 r5
    rfi
@notvm:
    mfsprg r4, 3
    mtcrf 0xFF, r4
    mfsprg r4, 0
    mfsprg r5, 1
    mfsprg r6, 2
entry __VMBASEISIExceptionHandler_OriginalInstruction
    nop
entry __VMBASEISIExceptionHandler_SetBranchBack
    nop
entry __VMBASEISIExceptionHandler_Service
    OS_EXCEPTION_SAVE_GPRS(r3)
    b __VMBASEISIServiceException
}

void __VMBASEISIServiceException(OSContext* context) {
    OSContext exceptionContext;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    sPageFaultHandler(context->srr0);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}
