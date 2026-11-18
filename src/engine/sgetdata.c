/* Tag data reader (sgetdata.c): reads a big-endian integer of one to four bytes and sign-extends the
   one-, two- and three-byte forms. */

#include "engine/sndsys.h"

extern "C" {

int SNDI_getb(unsigned char *p, int size)
{
    int value;
    int i;

    value = 0;
    i = size;
    while (i-- != 0) {
        value = (value << 8) + *p++;
    }
    if (size == 1 && value > 0x7F) {
        value -= 0x100;
    } else if (size == 2 && value > 0x7FFF) {
        value -= 0x10000;
    } else if (size == 3 && value > 0x7FFFFF) {
        value -= 0x1000000;
    }
    return value;
}

}
