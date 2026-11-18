/* Tag reader (sgettag.c): steps a tagged sound header to its next tag and reads the tag's size and
   value. */

#include "engine/sndsys.h"

extern "C" {

int SNDI_gettag(Parser_8027823C *p)
{
    while (*p->m0 == 0xFC) {
        p->m0++;
    }
    p->m4 = *p->m0;
    if (p->m4 == 0xFF) {
        return 0;
    }
    p->m0++;
    if (p->m4 == 0xFD) {
        return 1;
    }
    if (p->m4 == 0xFE) {
        return 1;
    }
    p->m10 = *p->m0;
    if (p->m10 == 0xFF) {
        p->m10 = SNDI_getb(p->m0 + 1, 4);
        p->m0 += 4;
    }
    p->m0++;
    p->mC = p->m0;
    if (p->m10 <= 4) {
        p->m8 = SNDI_getb(p->m0, p->m10);
    }
    p->m0 += p->m10;
    return 1;
}

}
