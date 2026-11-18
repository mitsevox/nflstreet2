/* Mixer setup (sinitut.c): registers the MT-compressed sample unpackers (one-shot, looped and packet
   streamed) and their node sizes for both MT formats. */

#include "engine/sndsys.h"

extern "C" {

void MIXI_initunpackmt(void)
{
    lbl_803B4E34.m18[2][0] = SFILTER_unpackmtfinit;
    lbl_803B4E34.m60[2][0] = 44;
    lbl_803B4E34.m18[2][2] = SFILTER_unpackmtpfinit;
    lbl_803B4E34.m60[2][2] = 60;
    lbl_803B4E34.m18[2][1] = SFILTER_unpackmtlfinit;
    lbl_803B4E34.m60[2][1] = 48;
    lbl_803B4E34.m18[3][0] = SFILTER_unpackmtfinit;
    lbl_803B4E34.m60[3][0] = 44;
    lbl_803B4E34.m18[3][2] = SFILTER_unpackmtpfinit;
    lbl_803B4E34.m60[3][2] = 60;
    lbl_803B4E34.m18[3][1] = SFILTER_unpackmtlfinit;
    lbl_803B4E34.m60[3][1] = 48;
}

}
