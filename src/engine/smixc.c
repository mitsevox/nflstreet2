/* Mixer (smixc.c): adds one float buffer, scaled by a gain, into another. */

#include "engine/sndsys.h"

extern "C" {

void mixc(int count, float *src, float *dst, float gain)
{
    int i;

    for (i = 0; i < count; i++) {
        dst[i] = src[i] * gain + dst[i];
    }
}

}
