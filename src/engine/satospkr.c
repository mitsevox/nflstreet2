/* Azimuth to speaker gains (satospkr.c): the table that turns a voice's azimuth into per-speaker
   volumes for the output speaker layout. Only the table release is reconstructed. */

#include "engine/sndsys.h"

extern "C" {

extern void *lbl_803B5044;
extern int lbl_803B5048[6];

void SNDI_freespkrtable(void)
{
    SNDSYS_entercritical();
    if (lbl_803B5048 != 0) {
        SNDMEMI_free(lbl_803B5044);
    }
    SNDSYS_leavecritical();
}

}
