/* Mixer setup (sinitxa.c): registers the XA ADPCM sample unpackers (one-shot, looped and packet
   streamed) and their node sizes. */

#include "engine/sndsys.h"

extern "C" {

void MIXI_initunpackxa(void)
{
    lbl_803B4E34.m18[1][0] = SFILTER_unpackxafinit;
    lbl_803B4E34.m60[1][0] = 44;
    lbl_803B4E34.m60[1][1] = 84;
    lbl_803B4E34.m18[1][1] = fn_8027B7B0;
    lbl_803B4E34.m18[1][2] = fn_8027BA6C;
    lbl_803B4E34.m60[1][2] = 60;
}

}
