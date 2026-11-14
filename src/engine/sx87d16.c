/* 16-bit sample decode (sx87d16.c): converts a block of signed 16-bit samples into floats for the
   software mixer. */

#include "engine/sndsys.h"

extern "C" {

void decode16x87(int count, short *src, float *dst)
{
    int i;

    for (i = 0; i < count; i++) {
        dst[i] = src[i];
    }
}

}
