/* Mixer frame query (smixfram.c): asks a mixer voice's decoder node for its current frame, or
   returns -1 when the voice has no frame callback. */

#include "engine/sndlib.h"

int MIX_getframe(int index)
{
    SndMixVoice_t *record = &sndmix.m1DC[index];

    if (record->m44 != 0) {
        return record->m44(record->m48);
    }
    return -1;
}
