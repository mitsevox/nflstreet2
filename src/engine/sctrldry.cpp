/* Dry level control (sctrldry.cpp): sets the dry (unprocessed) mix level of every voice of a playing
   sound. */

#include "engine/sndbank.h"

int SNDCTRL_drylevel(int handle, int level)
{
    int index = fn_8026A288(handle);
    int cursor;

    if (index >= 0) {
        cursor = -1;
        while (iSNDpatchkey(index, &cursor) != 0) {
            Record_803A6DF0 *rec = &lbl_803A6C24.m1CC[cursor];
            int i;

            for (i = 0; i < rec->m23; i++) {
                short voice = rec->m4[i];

                lbl_803A6C24.m1CC[voice].m5F = level;
                fn_80274924(voice);
            }
        }
    }
    return index;
}
