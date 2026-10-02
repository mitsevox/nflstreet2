#ifndef DOLPHIN_OS_INTERNAL_H
#define DOLPHIN_OS_INTERNAL_H

#include <dolphin/os.h>

void __OSInitSystemCall(void);
OSSram* __OSLockSram(void);
OSSramEx* __OSLockSramEx(void);
int __OSUnlockSram(BOOL commit);
int __OSUnlockSramEx(BOOL commit);

#endif
