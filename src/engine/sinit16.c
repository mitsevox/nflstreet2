/* Mixer setup (sinit16.c): registers the 16-bit PCM sample unpackers (one-shot, looped and packet
   streamed) and their node sizes in the mixer's constructor tables. */

#include "engine/sndsys.h"

extern "C" {

void MIXI_initunpack16(void)
{
    lbl_803B4E34.m18[0][0] = SFILTER_unpackfinit;
    lbl_803B4E34.m60[0][0] = 44;
    lbl_803B4E34.m18[0][1] = SFILTER_unpacklfinit;
    lbl_803B4E34.m60[0][1] = 48;
    lbl_803B4E34.m18[0][2] = SFILTER_unpackpfinit;
    lbl_803B4E34.m60[0][2] = 52;
}

}
