/* Main-CPU mixer link (slinkmix.c): installs the software mixer's create, destroy, audio-slice,
   play-init, play, stop and pitch functions in the sound system's mixer hooks. */

#include "engine/sndlib.h"

void SNDSYS_linkmaincpumixer(void)
{
    lbl_803B5028 = MIX_create;
    lbl_803B502C = fn_80275E7C;
    lbl_803B5030 = fn_802763E0;
    lbl_803B5034 = MIX_playinit;
    lbl_803B5038 = fn_80276194;
    lbl_803B503C = MIX_stop;
    lbl_803B5040 = MIX_setpitch;
}
