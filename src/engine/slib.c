/* Recalculates a voice's volume from its programmed level, envelope, curves and master volume. */

#include "engine/cu_802714A8.h"
#include "engine/sndstrm.h"
#include "engine/sndvoice.h"

extern "C" void iSNDcalcvol(int index)
{
    Record_803A6DF0 *voice = &lbl_803A6C24.m1CC[index];
    voice->m48 = (float)(signed char)voice->m2B * voice->m38 * (float)(voice->m40 >> 16)
               * (1.0f / (127.0f * 127.0f));

    const signed char *curve = (const signed char *)voice->m7C;
    if (curve != 0) {
        voice->m48 = voice->m48 * (float)curve[voice->m6B] * (1.0f / 127.0f);
    }

    if (voice->m74 != 0) {
        float level = voice->m48 * 127.0f;
        int entry;
        if (!(level < 0.0f)) {
            entry = (int)(level + 0.5f);
        } else {
            entry = (int)(level - 0.5f);
        }
        voice->m48 = (float)((const signed char *)voice->m74)[entry];
    }

    voice->m48 *= lbl_80300028;
}
