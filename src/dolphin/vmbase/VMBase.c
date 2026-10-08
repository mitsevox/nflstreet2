#include <dolphin/types.h>

static u32* sPageTable;
static u32* sReversePageTable;
static u8* sLockedPageTable;
static void (*sPageFaultHandler)(u32);

u32 __VMBASEGetVirtualAddr(u32 physPage);
void __VMBASESetVirtualAddr(u32 physPage, u32 virtualAddr);
BOOL __VMBASEIsPageLocked(u32 physPage);
void __VMBASESetPageLocked(u32 physPage, BOOL locked);
void __VMBASESetPageFaultHandler(void (*handler)(u32));
u32* __VMBASEGetPTE(u32 virtualAddr);

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

u32* __VMBASEGetPTE(u32 virtualAddr) {
    return (u32*)((u32)sPageTable | ((virtualAddr >> 6) & 0xFFC0) | ((virtualAddr >> 19) & 0x38));
}
