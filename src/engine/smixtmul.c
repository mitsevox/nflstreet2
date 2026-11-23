/* Mixer time multiplier (smixtmul.c): passes a new ratio to a mixer voice's time-stretch node. */

#include "engine/sndlib.h"

void MIX_settimemult(int index, int value)
{
    SndMixVoice_t *record = &sndmix.m1DC[index];

    if (record->m4C != 0) {
        SFILTER_timestretchsetratio(record->m4C, value);
    }
}
