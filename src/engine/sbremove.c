/* Sound bank remove (sbremove.c): stops a bank's voices, releases its patches and ARAM copy and frees
   its bank-table slot; bank -1 removes every bank. */

#include "engine/sndbank.h"

int SNDbankremove(int bank)
{
    Struct_80270E04 info;
    char *cursor;
    BankVer_t *hdr;
    int i;
    int more;

    if (bank == -1) {
        for (i = 0; i < lbl_803A6C24.m1C.m8; i++) {
            SNDbankremove(i);
        }
        return 0;
    }
    if (SNDBANKI_valid(bank) != 0) {
        return -8;
    }
    SNDSYS_entercritical();
    hdr = lbl_803A6C24.m1D0[bank].m0;
    for (i = 0; i < lbl_803A6C24.m16C; i++) {
        if (lbl_803A6C24.m1CC[i].m4[7] == bank) {
            fn_8026EDC4(lbl_803A6C24.m1CC[i].m0);
        }
    }
    for (i = 0; i < hdr->m6; i++) {
        cursor = (char *)SNDBANKI_getppatch(hdr, i);
        if (cursor != 0) {
            cursor += 4;
            do {
                more = fn_80270E04(&cursor, &info);
                fn_8026A40C(&info, 2);
            } while (more != 0);
        }
    }
    if (lbl_803A6C24.m1D0[bank].m4 != 0) {
        fn_80275194(8, (void *)lbl_803A6C24.m1D0[bank].m4);
    }
    lbl_803A6C24.m1D0[bank].m0 = 0;
    lbl_803A6C24.m1D0[bank].m8 = 0;
    SNDSYS_leavecritical();
    return 0;
}
