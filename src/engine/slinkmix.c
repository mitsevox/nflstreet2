/* Main-CPU mixer link (slinkmix.c): installs the software mixer's create, destroy, audio-slice,
   play-init, play, stop and pitch functions in the sound system's mixer hooks. */

#include "engine/sndlib.h"

void SNDSYS_linkmaincpumixer(void)
{
    MIXinitfn = MIX_create;
    MIXrestorefn = MIX_destroy;
    MIXaudioslicefn = MIX_audioslice;
    MIXplayinitfn = MIX_playinit;
    MIXplayfn = MIX_play;
    MIXstopfn = MIX_stop;
    MIXsetpitchfn = MIX_setpitch;
}
