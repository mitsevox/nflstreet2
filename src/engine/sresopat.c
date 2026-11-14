/* Patch resolve (sresopat.c): walks a patch's tagged records and resolves the ones of the requested
   kinds against the bank's ARAM base. */

#include "engine/sndbank.h"

int SNDBANKI_asyncresolvepatch(int mask, void *patch, int base, int *count)
{
    Struct_80270E04 info;
    char *cursor = (char *)patch + 4;
    int more;

    do {
        more = fn_80270E04(&cursor, &info);
        if (info.m18 & mask) {
            fn_80273DC0(&info, base, count);
            fn_8026A40C(&info, 0);
        }
    } while (more != 0);
    return 0;
}
