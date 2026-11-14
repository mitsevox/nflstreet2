/* Sound bank header copy (sbhdrcpy.c): copies a loaded bank's header to a new buffer and points the
   bank table at the copy. */

#include "engine/sndbank.h"

int SNDbankheadercopy(void *dst, int bank)
{
    int result = 0;
    int size = SNDbankheadersize(bank);

    if (size < 0) {
        result = size;
    } else {
        fn_801C2030(dst, lbl_803A6C24.m1D0[bank].m0, size);
        lbl_803A6C24.m1D0[bank].m0 = (BankVer_t *)dst;
    }
    return result;
}
