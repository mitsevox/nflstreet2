/* Asynchronous bank load from memory (sbasyncm.c): copies a bank's sample data to ARAM in
   64 KiB steps from the 100 Hz server, then resolves the bank's patches against the ARAM copy. */

#include "engine/sndbank.h"

typedef struct SndBankAsyncMem_t {
    unsigned char m0;
    unsigned char unk_0x1;
    unsigned short m2;
    int m4;
    unsigned char unk_0x8[8];
    int m10;
} SndBankAsyncMem_t;

static SndBankAsyncMem_t sndbams;

void SNDBANKI_asyncloadmemresolve(void)
{
    SndBankSlot_t *slot = &lbl_803A6C24.m1D0[sndbams.m2];
    BankVer_t *bank = slot->m0;
    int count;
    int i;

    if (bank->mC != 0) {
        count = 0;
        for (i = 0; i < bank->m6; i++) {
            int offset = bank->m14[i];

            if (offset != 0) {
                SNDBANKI_asyncresolvepatch(512, (char *)&bank->m14[i] + offset, slot->m4, &count);
            }
        }
    }
    slot->m8 = 0;
    sndbams.m0 = 0;
}

void SNDBANKI_asyncloadmem100hz(void)
{
    SndBankAsyncMem_t *state = &sndbams;

    if (fn_80275288(state->m4) != 0 || state->m4 <= 0) {
        SndBankSlot_t *slot = &lbl_803A6C24.m1D0[state->m2];
        BankVer_t *bank = slot->m0;
        int size;

        if (slot->m4 != 0 && (size = bank->mC - state->m10) != 0) {
            if (size > 0x10000) {
                size = 0x10000;
            }
            state->m4 = fn_80275234(512, (unsigned int)((char *)bank + bank->m8 + bank->m10 + state->m10),
                                    slot->m4 + state->m10, size);
            state->m10 += size;
        } else {
            SNDBANKI_asyncloadmemresolve();
            SNDSYS_remove100hzclient(SNDBANKI_asyncloadmem100hz);
        }
    }
}

int SNDBANK_asyncloadmem(int *handle, BankVer_t *bank)
{
    int result = 0;
    SndBankSlot_t *slot;

    lbl_803A6C24.m1C0 = SNDbankremove;
    SNDSYS_entercritical();
    *handle = SNDBANKI_alloc();
    sndbams.m2 = *handle;
    slot = &lbl_803A6C24.m1D0[*handle];
    slot->m0 = bank;
    slot->m4 = 0;
    if (bank->mC != 0) {
        if ((slot->m4 = (int)fn_80275150(512, bank->mC + 48)) == 0) {
            slot->m0 = 0;
            result = -6;
            goto out;
        }
    }
    if (bank->mC != 0 || bank->m10 != 0) {
        slot->m8 = 1;
        sndbams.m0 = 1;
        sndbams.m10 = 0;
        result = 7;
        SNDSYS_add100hzclient(SNDBANKI_asyncloadmem100hz);
    } else {
        SNDBANKI_asyncloadmemresolve();
        result = 8;
    }
out:
    SNDSYS_leavecritical();
    return result;
}

int SNDBANK_asyncloadmemdone(void)
{
    return sndbams.m0 == 0;
}
