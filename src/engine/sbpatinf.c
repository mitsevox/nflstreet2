/* Sound bank patch info (sbpatinf.c): decodes a patch of a loaded bank into its sample format,
   attributes and description, releasing the per-channel buffers the decode allocates. */

#include "engine/sndbank.h"

int SNDBANK_patchinfo(int bank, int patch, SndSampleFormat_t *format, SndSampleAttr_t *attr, void *desc)
{
    void *p;
    int i;

    if (SNDBANKI_valid(bank) < 0 || (p = SNDBANKI_getppatch(lbl_803A6C24.m1D0[bank].m0, patch)) == 0) {
        return -8;
    }
    SNDSYS_entercritical();
    SNDI_patchtohdr(lbl_803A6C24.m1D0[bank].m0, (unsigned char *)p, format, attr, (SndSampleDesc_t *)desc, 0);
    for (i = 0; i < format->mChannels; i++) {
        if (attr->m18[i] != 0) {
            SNDMEMI_free(attr->m18[i]);
            attr->m18[i] = 0;
            attr->m30[i] = 0;
        }
    }
    SNDSYS_leavecritical();
    return 0;
}
