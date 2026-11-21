/* Mixer setup (sinit16.c): registers the 16-bit PCM sample unpackers (one-shot, looped and packet
   streamed) and their node sizes in the mixer's constructor tables. */

#include "engine/sndsys.h"

extern "C" {

void MIXI_initunpack16(void)
{
    sndmix.m18[0][0] = SFILTER_unpackfinit;
    sndmix.m60[0][0] = 44;
    sndmix.m18[0][1] = SFILTER_unpacklfinit;
    sndmix.m60[0][1] = 48;
    sndmix.m18[0][2] = SFILTER_unpackpfinit;
    sndmix.m60[0][2] = 52;
}

}
