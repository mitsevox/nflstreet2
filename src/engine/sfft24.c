/* Sound filter (sfft24.c): the output stage that converts float samples to integers clamped to the
   16-bit range, and its init. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_ft24_32(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    int i;
    int value;
    int clamped;

    for (i = 0; i < count; i++) {
        value = (int)a[i];
        if (value < -32767) {
            clamped = -32767;
        } else if (value > 32767) {
            clamped = 32767;
        } else {
            clamped = value;
        }
        ((int *)b)[i] = clamped;
    }
    return count;
}

void SFILTER_ft24_32init(Node_80279D90 *node)
{
    node->m0 = SFILTER_ft24_32;
    node->m4 = 0;
}

}
