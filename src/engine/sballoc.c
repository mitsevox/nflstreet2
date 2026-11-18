/* Sound bank slots (sballoc.c): finds a free slot in the bank table and the patch at an index of a
   loaded bank. */

#include "engine/sndbank.h"

int SNDBANKI_alloc(void)
{
    int i;

    for (i = 0; i < lbl_803A6C24.m1C.m8; i++) {
        if (lbl_803A6C24.m1D0[i].m0 == 0) {
            return i;
        }
    }
    return -9;
}

void *SNDBANKI_getppatch(BankVer_t *bank, int patch)
{
    int offset;

    if (patch >= bank->m6) {
        return 0;
    }
    offset = bank->m14[patch];
    if (offset == 0) {
        return 0;
    }
    return (char *)&bank->m14[patch] + offset;
}
