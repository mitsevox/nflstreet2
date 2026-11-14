/* Mixer time multiplier (smixtmul.c): passes a new ratio to a mixer voice's time-stretch node. */

#include "engine/sndlib.h"

void MIX_settimemult(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];

    if (record->m4C != 0) {
        fn_80277240(record->m4C);
    }
}
