/* Patch resolve (sresopat.c): walks a patch's tagged records and resolves the ones of the requested
   kinds against the bank's ARAM base. */

#include "engine/sndbank.h"

int SNDBANKI_asyncresolvepatch(int mask, void *patch, int base, int *count)
{
    SNDIPATCHHEADER info;
    char *cursor = (char *)patch + 4;
    int more;

    do {
        more = SNDI_parsetimbre(&cursor, &info);
        if (info.m18 & mask) {
            SNDPLATFORM_asyncresolvetimbre(&info, base, count);
            SNDBANKI_userdatacallback(&info, 0);
        }
    } while (more != 0);
    return 0;
}
