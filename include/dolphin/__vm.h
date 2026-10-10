#ifndef _DOLPHIN_VM_INTERNAL_H_
#define _DOLPHIN_VM_INTERNAL_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*VMLogStatsCallback)(u32 virtualAddr, u32 physicalAddr, u32 pageNumber, u32 pageMissLatency, BOOL pageSwappedOut);

void VMInit(u32 mramSize, u32 aramStart, u32 aramSize);
void VMSetLogStatsCallback(VMLogStatsCallback callback);
u32 __VMGetMRAMPages(void);
u32 __VMGetARAMSize(void);
u32 __VMGetARAMStart(void);
void __VMAllocMRAMSwapSpace(void);
void __VMSwapPageIn(u32 virtualAddr);
void __VMSwapPageOut(u32 virtualAddr);
void VMStoreAllPages(void);

u32 __VMGetPageToReplace(void);
u32 __VMPageReplacementLRU(void);
u32 __VMPageReplacementRandom(void);
u32 __VMPageReplacementFIFO(void);

BOOL VMAlloc(u32 virtualAddr, u32 size);
u32 __VMTranslateVMPageToARAMPage(u32 virtualAddr);
BOOL __VMIsPageMapped(u32 virtualAddr);
void __VMMappingErrorAlert(u32 virtualAddr);
void __VMSetPageInARAM(u32 virtualAddr);
BOOL __VMIsPageInARAM(u32 virtualAddr);
void __VMAllocVirtualToARAMLUT(void);
void __VMAllocARAMToVirtualLUT(void);

void VMBASEInit(void (*pageFaultHandler)(u32 virtualAddr));
void VMBASESetPageTableEntry(u32 virtualAddr, u32 physAddr, u32 physPage);
void VMBASEClearPageTableEntry(u32 virtualAddr, u32 physPage);
BOOL __VMBASEIsPageValid(u32 virtualAddr);
BOOL __VMBASEIsPageReferenced(u32 virtualAddr);
BOOL __VMBASEIsPageChanged(u32 virtualAddr);
void VMBASESetPageReferenced(u32 virtualAddr, BOOL referenced);
u32 __VMBASEGetPhysicalAddr(u32 virtualAddr);
u32 __VMBASEGetVirtualAddr(u32 physPage);
BOOL __VMBASEIsPageLocked(u32 physPage);
void VMBASEStoreAllPages(void (*storePage)(u32 virtualAddr));

#ifdef __cplusplus
}
#endif

#endif
