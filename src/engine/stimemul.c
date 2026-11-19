/* Time-multiplier control (stimemul.c): clamps a time multiplier to 2048..8192 and sets it on every
   voice of a sound handle. */

#include "engine/sndsys.h"
#include "engine/sndlib.h"

extern "C" {

int SNDCTRL_timemult(int handle, int mult)
{
    int voice;
    int index;

    if (mult > 8192) {
        mult = 8192;
    } else if (mult < 2048) {
        mult = 2048;
    }
    voice = fn_8026A288(handle);
    if (voice >= 0) {
        index = -1;
        while (iSNDpatchkey(voice, &index)) {
            lbl_803A6C24.m1CC[index].m6E = mult;
            fn_80274CA8(index, mult);
        }
    }
    return 0;
}

}
