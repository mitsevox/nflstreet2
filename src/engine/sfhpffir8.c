/* Sound filter (sfhpffir8.c): the 8-tap FIR high-pass filter and its create. The modify function is
   not reconstructed yet. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_hpfFIR8(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    int n;

    if (node->m8 != 0) {
        n = node->m8->m0(node->m8, count, b, a, node->m1A);
        if (n <= 0) {
            return n;
        }
    } else {
        n = count;
    }
    SNDI_fir8(&((SndHpfState_t *)node)->m1C, n, a, b);
    return n;
}

int SFILTER_createHPFFIR8(Node_80279D90 *node)
{
    node->m8 = 0;
    node->mC = 0;
    node->m10 = 0;
    node->m14 = 0;
    node->m1B = 0;
    node->m4 = 0;
    node->m0 = SFILTER_hpfFIR8;
    SNDI_fir8init(&((SndHpfState_t *)node)->m1C);
    return 0;
}

}
