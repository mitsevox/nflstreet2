/* Mixer high-pass (smixhip.c): adds, updates or removes the high-pass filter node of a mixer voice. */

#include "engine/sndlib.h"

void MIX_sethighpass(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node;
    Params_80279D0C params;

    if (value > 0) {
        node = record->m58;
        if (node == 0) {
            record->m58 = (Node_80279D90 *)SNDMEMI_allocz(88);
            record->m58->m4 = 0;
            record->m58->m18 = 80;
            record->m58->m1A = 0;
            fn_80279CB8(record->m58);
            fn_80279D90(&record->m40, record->m58);
        }
        params.m0 = value << 8;
        params.m4 = lbl_803A6C24.m1C.mA << 8;
        fn_80279D0C(record->m58, &params);
    } else if (record->m58 != 0) {
        fn_80279DF8(&record->m40, record->m58);
        SNDMEMI_free(record->m58);
        record->m58 = 0;
    }
}
