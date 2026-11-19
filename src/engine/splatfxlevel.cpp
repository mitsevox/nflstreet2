/* Effect-send level of a sound voice: scales the voice's level by the per-slot send table and
   applies it to each of the voice's hardware channels, through the DSP mixer's auxiliary bus or
   the software mixer's wet gain. */

#include "engine/sndlib.h"


int SNDPLATFORM_setfxlevel(int index, int slot)
{
    Record_803A6DF0 *pRec = &lbl_803A6C24.m1CC[index];
    float level;
    int i;

    if (pRec->m24 & 0x200) {
        level = pRec->m48 * pRec->m64[slot];
        for (i = 0; i < pRec->m23; i++) {
            if (i == 5) {
                level = 0.0f;
            }
            SNDDRV_DSPMixerSetAuxBus(lbl_803A8D60.m0[pRec->m4[i]].m3C, (unsigned short)(level * 32767.0f), 1);
        }
    } else if (pRec->m24 & 4) {
        level = pRec->m48 * pRec->m64[slot];
        for (i = 0; i < pRec->m23; i++) {
            if (i == 5) {
                level = 0.0f;
            }
            SNDMIX_setwetgain(pRec->m4[i] - lbl_803A6C24.m1C.m12, slot, level);
        }
    } else {
        return -15;
    }
    return 0;
}
