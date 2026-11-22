/* Sets or removes the low-pass filter on a software-mixed sound voice. */

#include "engine/sndlib.h"
#include "engine/sndsys.h"

void MIX_setlowpass(int index, float cutoff)
{
    Record_803B5010 *record = &sndmix.m1DC[index];
    int params[3];

    if (!(cutoff >= 1.0f)) {
        if (record->m54 == 0) {
            record->m54 = (Node_80279D90 *)SNDMEMI_allocz(sizeof(SndLpfState_t));
            record->m54->m4 = 0;
            record->m54->m18 = sizeof(SndLpfState_t);
            record->m54->m1A = 0;
            SFILTER_createLPFRC(record->m54);
            SFILTER_add(&record->m40, record->m54);
        }

        int sampleRate = lbl_803A6C24.m1C.mA;
        float scaledCutoff = cutoff * (float)sampleRate;
        params[1] = sampleRate << 8;
        // FAKEMATCH: negating the comparison makes subtraction the branch target.
        int roundedCutoff = !(scaledCutoff < 0.0f) ? (int)(scaledCutoff + 0.5f) : (int)(scaledCutoff - 0.5f);
        params[0] = (int)((unsigned int)roundedCutoff << 7);
        params[2] = 256;
        SFILTER_modifyLPFRC(record->m54, params);
    } else if (record->m54 != 0) {
        SFILTER_remove(&record->m40, record->m54);
        SNDMEMI_free(record->m54);
        record->m54 = 0;
    }
}
