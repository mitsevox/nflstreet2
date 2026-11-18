/* Play option check (scheckpo.c): clamps a play request's pitch field to 2048-8192. */

#include "engine/sndbank.h"

void SNDI_checkplayopts(SndPlayOpts_t *opts)
{
    if (opts->mE > 8192) {
        opts->mE = 8192;
    } else if (opts->mE < 2048) {
        opts->mE = 2048;
    }
}
