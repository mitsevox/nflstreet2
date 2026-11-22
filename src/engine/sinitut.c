/* Mixer setup (sinitut.c): registers the MT-compressed sample unpackers (one-shot, looped and packet
   streamed) and their node sizes for both MT formats. */

#include "engine/sndsys.h"

extern "C" {

void MIXI_initunpackmt(void)
{
    sndmix.m18[2][0] = SFILTER_unpackmtfinit;
    sndmix.m60[2][0] = 44;
    sndmix.m18[2][2] = SFILTER_unpackmtpfinit;
    sndmix.m60[2][2] = 60;
    sndmix.m18[2][1] = SFILTER_unpackmtlfinit;
    sndmix.m60[2][1] = 48;
    sndmix.m18[3][0] = SFILTER_unpackmtfinit;
    sndmix.m60[3][0] = 44;
    sndmix.m18[3][2] = SFILTER_unpackmtpfinit;
    sndmix.m60[3][2] = 60;
    sndmix.m18[3][1] = SFILTER_unpackmtlfinit;
    sndmix.m60[3][1] = 48;
}

}
