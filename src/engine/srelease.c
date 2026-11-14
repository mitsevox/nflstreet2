/* Sound release (srelease.c): moves every voice of a playing sound into its release envelope stage,
   or stops the sound when a voice has no release stage. */

#include "engine/sndbank.h"

int SNDrelease(int handle)
{
    int index = fn_8026A288(handle);
    int cursor;

    if (index >= 0) {
        cursor = -1;
        while (iSNDpatchkey(index, &cursor) != 0) {
            Record_803A6DF0 *rec = &lbl_803A6C24.m1CC[cursor];
            int i;

            for (i = 0; i < rec->m23; i++) {
                Record_803A6DF0 *voice = &lbl_803A6C24.m1CC[rec->m4[i]];

                if (voice->m5E < 0) {
                    if (voice->m0 >= 0) {
                        fn_80274F5C(cursor);
                        break;
                    }
                } else if (voice->m5D < voice->m5E) {
                    voice->m5D = voice->m5E;
                    voice->m44 = voice->m70[voice->m5E].m0;
                    voice->m3C = ((voice->m70[voice->m5E].m4 << 16) - voice->m40) / voice->m44;
                }
            }
        }
    }
    return index;
}
