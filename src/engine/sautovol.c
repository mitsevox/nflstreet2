/* Sound auto-volume (sautovol.c): fades every voice of a sound handle to a 0-127 volume over a number of
   ticks, giving each voice its target and per-tick step. */

#include "engine/sndsys.h"

extern "C" {

int SNDautovol(int handle, int time, int vol)
{
    int voice;
    int index;
    int i;
    float target;
    Record_803A6DF0 *rec;
    Record_803A6DF0 *sub;

    voice = SNDVOICEI_get(handle);
    if (voice >= 0) {
        target = vol * (1.0f / 127.0f);
        if (time <= 0) {
            time = 1;
        }
        index = -1;
        while (iSNDpatchkey(voice, &index)) {
            rec = &lbl_803A6C24.m1CC[index];
            for (i = 0; i < rec->m23; i++) {
                sub = &lbl_803A6C24.m1CC[rec->m4[i]];
                sub->m34 = target;
                sub->m30 = (target - sub->m38) / time;
            }
        }
    }
    return voice;
}

}
