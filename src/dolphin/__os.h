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

#endif
