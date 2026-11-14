/* Mixer frame query (smixfram.c): asks a mixer voice's decoder node for its current frame, or
   returns -1 when the voice has no frame callback. */

#include "engine/sndlib.h"

int MIX_getframe(int index)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];

    if (record->m44 != 0) {
        return record->m44(record->m48);
    }
    return -1;
}
