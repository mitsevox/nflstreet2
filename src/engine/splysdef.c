/* Play option defaults (splysdef.c): fills a play options record with the default volume, pan,
   pitch and priority. */

#include "engine/sndbank.h"

int SNDplaysetdef(SndPlayOpts_t *opts)
{
    // FAKEMATCH: store order found by search; the target's store order (mA, m2, m10, m14, m4, m1, mC, mE, m16, m3, m0, m5, m8) comes out of the scheduler only from this source order
    opts->m2 = 60;
    opts->mC = 4096;
    opts->mE = 4096;
    opts->m10 = 4096;
    opts->m16 = 0;
    opts->m3 = 127;
    opts->m14 = -1;
    opts->m0 = 127;
    opts->m4 = 127;
    opts->m1 = 64;
    opts->m5 = 0;
    opts->m8 = 0;
    opts->mA = 0;
    return 0;
}
