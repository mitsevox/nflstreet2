/* Sound filter (sflpf.c): the one-pole RC low-pass filter: its processing callback, create and modify
   (coefficients from the cutoff and sample rate pair, scaled by the level). */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_lpfRC(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndRcState_t *rc;
    int n;
    int i;

    if (node->m8 != 0) {
        n = node->m8->m0(node->m8, count, b, a, node->m1A);
        if (n <= 0) {
            return n;
        }
    }
    rc = &((SndLpfState_t *)node)->m1C;
    for (i = 0; i < count; i++) {
        rc->m0 = rc->m0 * rc->m4 + rc->m8 * a[i];
        b[i] = rc->m0;
    }
    return count;
}

int SFILTER_createLPFRC(Node_80279D90 *node)
{
    node->m8 = 0;
    node->mC = 0;
    node->m10 = 0;
    node->m14 = 0;
    node->m1B = 0;
    node->m4 = 0;
    node->m0 = SFILTER_lpfRC;
    ((SndLpfState_t *)node)->m1C.m0 = 0.0f;
    return 0;
}

void SFILTER_modifyLPFRC(Node_80279D90 *node, int *params)
{
    SndLpfState_t *s = (SndLpfState_t *)node;

    s->m1C.m8 = (2.0f * (float)params[0]) / (float)params[1];
    s->m1C.m4 = 1.0f - s->m1C.m8;
    s->m1C.m8 = s->m1C.m8 * 0.00390625f * (float)params[2];
    s->m1C.m4 = s->m1C.m4 * 0.00390625f * (float)params[2];
}

}
