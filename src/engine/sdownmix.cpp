/* Default speaker azimuths (sdownmix.cpp): gives each channel of a multichannel sound its default
   azimuth for the current output mode. */

#include "engine/sndsys.h"

extern "C" {

extern const unsigned char lbl_802C1F68[][6][6];

void SetDefaultAzimuths(Record_803A6DF0 *p)
{
    const unsigned char *table = lbl_802C1F68[lbl_803A772C][p->m23 - 1];
    int i;

    for (i = 0; i < p->m23; i++) {
        lbl_803A6C24.m1CC[p->m4[i]].m1C = table[i] << 8;
    }
}

}
