/* Play option defaults (splysdef.c): fills a play options record with the default volume, pan,
   pitch and priority. */

#include "engine/sndbank.h"

int SNDplaysetdef(SndPlayOpts_t *opts)
{
    opts->mA = 0;
    opts->m2 = 60;
    opts->m10 = 4096;
    opts->m14 = -1;
    opts->m4 = 127;
    opts->m1 = 64;
    opts->mC = 4096;
    opts->mE = 4096;
    opts->m16 = 0;
    opts->m3 = 127;
    opts->m0 = 127;
    opts->m5 = 0;
    opts->m8 = 0;
    return 0;
}
