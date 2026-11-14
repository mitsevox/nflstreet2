/* Patch key iteration (spatkey.c): steps through the voice records that belong to one playing
   sound (same key byte), or yields the sound's own record once when it has no key. */

#include "engine/sndbank.h"

int iSNDpatchkey(int handle, int *cursor)
{
/*V*/    unsigned char key = lbl_803A6C24.m1CC[handle].m26;
/*V*/
    if (key != 0) {
        for ((*cursor)++; *cursor < lbl_803A6C24.m16C; (*cursor)++) {
            Record_803A6DF0 *rec = &lbl_803A6C24.m1CC[*cursor];

            if (rec->m26 == key && rec->m6D == 1 && rec->m0 >= 0) {
                return 1;
            }
        }
    } else if (*cursor < 0) {
        *cursor = handle;
        return 1;
    }
    return 0;
}
