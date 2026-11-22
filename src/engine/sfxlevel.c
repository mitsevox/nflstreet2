/* Changes the effect-bus send level of every voice associated with a sound handle. */

#include "engine/sndlib.h"

extern "C" int SNDfxlevel(int handle, int bus, int level)
{
    int voice = SNDVOICEI_get(handle);
    int index;

    if (voice >= 0) {
        index = -1;
        while (iSNDpatchkey(voice, &index)) {
            lbl_803A6C24.m1CC[index].m64[bus] = (float)level * (1.0f / 127.0f);
            SNDPLATFORM_setfxlevel(index, bus);
        }
    }
    return voice;
}
