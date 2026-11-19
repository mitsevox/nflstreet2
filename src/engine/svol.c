/* Sound volume (svol.c): sets the volume level (0-127) of every voice of a sound handle,
   refreshes the voices whose level changed and then re-applies the handle's effect-send levels. */

#include "engine/sndlib.h"

extern "C" {

void fn_80278598(int index);

int SNDvol(int id, int value)
{
    int handle;
    int index;
    float level;
    int changed;
    int i;
    int voice;
    Record_803A6DF0 *pRecord;
    Record_803A6DF0 *pVoice;

    handle = fn_8026A288(id);
    if (handle >= 0) {
        level = (float)value * (1.0f / 127.0f);
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            pRecord = &lbl_803A6C24.m1CC[index];
            changed = 0;
            for (i = 0; i < pRecord->m23; i++) {
                voice = pRecord->m4[i];
                pVoice = &lbl_803A6C24.m1CC[voice];
                pVoice->m30 = 0.0f;
                if (pVoice->m38 != level) {
                    pVoice->m38 = level;
                    fn_80278598(voice);
                    changed = 1;
                    fn_802747D8(voice);
                }
            }
            if (changed) {
                if (pRecord->m24 & 4) {
                    for (i = 0; i < lbl_8030002C; i++) {
                        SNDPLATFORM_setfxlevel(handle, i);
                    }
                } else {
                    SNDPLATFORM_setfxlevel(handle, 0);
                }
            }
        }
    }
    return handle;
}

}
