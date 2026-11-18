/* Sound bank header size (sbhdrsze.c): the size of a loaded bank's header. */

#include "engine/sndbank.h"

int SNDbankheadersize(int bank)
{
    return lbl_803A6C24.m1D0[bank].m0->m8;
}
