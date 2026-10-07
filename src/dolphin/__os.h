#ifndef DOLPHIN_OS_INTERNAL_H
#define DOLPHIN_OS_INTERNAL_H

#include <dolphin/os.h>

void __OSInitSystemCall(void);
OSSram* __OSLockSram(void);
OSSramEx* __OSLockSramEx(void);
int __OSUnlockSram(BOOL commit);
int __OSUnlockSramEx(BOOL commit);

void __OSResetSWInterruptHandler(s16 exception, OSContext* context);
void __OSSetResetButtonTimer(u8 min);

void __OSReschedule(void);

void __OSUnhandledException(__OSException exception, OSContext* context, u32 dsisr, u32 dar);

OSTime __OSTimeToSystemTime(OSTime time);
void __OSInterruptInit(void);
u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current);
void DMAErrorHandler(OSError error, OSContext* context, ...);
void __OSContextInit(void);
void OSSwitchFPUContext(__OSException exception, OSContext* context);
void __OSDoHotReset(s32 resetCode);
void __OSStopAudioSystem(void);
BOOL __OSSyncSram(void);
BOOL __PADDisableRecalibration(BOOL disable);
void __OSModuleInit(void);
void __OSInitSram(void);
void __OSThreadInit(void);
void __OSInitAudioSystem(void);
void __OSInitMemoryProtection(void);
void EnableMetroTRKInterrupts(void);
#endif
