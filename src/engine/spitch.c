/* Pitch multiplier (spitch.c): sets the pitch multiplier of every voice of a playing sound and
   pushes the change to the driver. */

#include "engine/sndbank.h"

int SNDpitchmult(int handle, int pitch)
{
    int index = fn_8026A288(handle);
    int cursor;

    if (index >= 0) {
        cursor = -1;
        while (iSNDpatchkey(index, &cursor) != 0) {
            Record_803A6DF0 *rec = &lbl_803A6C24.m1CC[cursor];

            if (rec->m8C == pitch) {
                return 0;
            }
            rec->m8C = pitch;
            iSNDcalcpitch(cursor);
            fn_80274B50(cursor);
        }
    }
    return index;
}
