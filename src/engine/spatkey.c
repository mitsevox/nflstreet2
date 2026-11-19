/* Patch key iteration (spatkey.c): steps through the voice records that belong to one playing
   sound (same key byte), or yields the sound's own record once when it has no key. */

#include "engine/sndbank.h"

int iSNDpatchkey(int handle, int *cursor)
{
    // FAKEMATCH: one record-pointer local, set for the handle here and reused for each cursor position below;
    // it keeps the target's add order (array base first, index offset second)
    Record_803A6DF0 *rec = &lbl_803A6C24.m1CC[handle];
    unsigned char key = rec->m26;

    if (key != 0) {
        for ((*cursor)++; *cursor < lbl_803A6C24.m16C; (*cursor)++) {
            // FAKEMATCH: reuse of the handle's record-pointer local (see above)
            rec = &lbl_803A6C24.m1CC[*cursor];
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
