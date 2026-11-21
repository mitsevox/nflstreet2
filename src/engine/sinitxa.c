/* Mixer setup (sinitxa.c): registers the XA ADPCM sample unpackers (one-shot, looped and packet
   streamed) and their node sizes. */

#include "engine/sndsys.h"

extern "C" {

void MIXI_initunpackxa(void)
{
    sndmix.m18[1][0] = SFILTER_unpackxafinit;
    sndmix.m60[1][0] = 44;
    sndmix.m60[1][1] = 84;
    sndmix.m18[1][1] = SFILTER_unpackxalfinit;
    sndmix.m18[1][2] = SFILTER_unpackxapfinit;
    sndmix.m60[1][2] = 60;
}

}
