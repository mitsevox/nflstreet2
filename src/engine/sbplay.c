/* Sound bank play (sbplay.c): starts a patch of a loaded bank. */

#include "engine/sndbank.h"

int SNDBANK_play(int bank, int patch, SndPlayOpts_t *opts)
{
    BankVer_t *hdr;

    SNDI_checkplayopts(opts);
    if (SNDBANKI_valid(bank) < 0) {
        return -8;
    }
    hdr = lbl_803A6C24.m1D0[bank].m0;
    if (patch < 0 || patch >= hdr->m6) {
        return -8;
    }
    return fn_80270B10(hdr, SNDBANKI_getppatch(hdr, patch), bank, patch, opts);
}
