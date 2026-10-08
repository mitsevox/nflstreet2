#include <dolphin/types.h>
#include <dolphin/os.h>
#include <dolphin/__vm.h>

static u32* sPageTable;
static u32* sReversePageTable;
static u8* sLockedPageTable;
static void (*sPageFaultHandler)(u32);
static BOOL sInitialized;

void VMBASEInit(void (*pageFaultHandler)(u32));
void VMBASESetPageTableEntry(u32 virtualAddr, u32 physAddr, u32 physPage);
void VMBASEClearPageTableEntry(u32 virtualAddr, u32 physPage);
BOOL __VMBASEIsPageValid(u32 virtualAddr);
BOOL __VMBASEIsPageReferenced(u32 virtualAddr);
BOOL __VMBASEIsPageChanged(u32 virtualAddr);
void VMBASESetPageReferenced(u32 virtualAddr, BOOL referenced);
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
void __VMBASEDSIServiceException(OSContext* context, u32 dar);
void __VMBASEISIServiceException(OSContext* context);
void __VMBASEInvalidateTLBEntry(u32 virtualAddr);
void __VMBASESetupExceptionHandlers(void);
void __VMBASESetupVMRegisters(void);
void __VMBASEInvalidateEntireTLB(void);

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
        pte[1] &= ~0x100;
    }
    DCStoreRange(&pte[1], 4);
    __VMBASEInvalidateTLBEntry(virtualAddr);
    OSRestoreInterrupts(enabled);
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
    OSSetArenaLo(sReversePageTable + 0x1000 * 4);
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

void __VMBASEDSIServiceException(OSContext* context, u32 dar) {
    OSContext exceptionContext;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    sPageFaultHandler(dar);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}

void __VMBASEISIServiceException(OSContext* context) {
    OSContext exceptionContext;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    sPageFaultHandler(context->srr0);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}
