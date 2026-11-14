/* Pitch bend (sbend.c): sets the pitch-bend value of every voice of a sound handle and recomputes
   their pitch. */

#include "engine/sndsys.h"

extern "C" {

int SNDpitchbend(int handle, int value)
{
    int index;
    Record_803A6DF0 *record;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            record = &lbl_803A6C24.m1CC[index];
            if (record->m68 == value || record->m86 == 0) {
                return 0;
            }
            record->m68 = value;
            record->m8A = 0;
            iSNDcalcpitch(index);
            fn_80274B50(index);
        }
    }
    return handle;
}

}
