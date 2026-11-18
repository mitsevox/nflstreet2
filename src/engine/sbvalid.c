/* Sound bank check (sbvalid.c): whether a bank index names a loaded bank that is not still loading. */

#include "engine/sndbank.h"

int SNDBANKI_valid(int bank)
{
    if (bank < 0 || bank >= lbl_803A6C24.m1C.m8) {
        return -8;
    }
    if (lbl_803A6C24.m1D0[bank].m0 == 0) {
        return -8;
    }
    if (lbl_803A6C24.m1D0[bank].m8 != 0) {
        return -18;
    }
    return 0;
}
