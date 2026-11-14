/* Sound filter (sfir8.c): the 8-tap FIR state used by the FIR filters: clear the history and run the
   filter over a buffer. */

#include "engine/sndsys.h"

extern "C" {

void SNDI_fir8init(SndFirState_t *state)
{
    state->m0[0] = 0.0f;
    state->m0[1] = 0.0f;
    state->m0[2] = 0.0f;
    state->m0[3] = 0.0f;
    state->m0[4] = 0.0f;
    state->m0[5] = 0.0f;
    state->m0[6] = 0.0f;
    state->m0[7] = 0.0f;
}

void SNDI_fir8(SndFirState_t *state, int count, float *in, float *out)
{
    int i;
    for (i = 0; i < count; i++) {
        out[i] = state->m20 * (in[i] + state->m0[7]) +
                 state->m24 * (state->m0[0] + state->m0[6]) +
                 state->m28 * (state->m0[1] + state->m0[5]) +
                 state->m2C * (state->m0[2] + state->m0[4]) +
                 state->m30 * state->m0[3];
        state->m0[7] = state->m0[6];
        state->m0[6] = state->m0[5];
        state->m0[5] = state->m0[4];
        state->m0[4] = state->m0[3];
        state->m0[3] = state->m0[2];
        state->m0[2] = state->m0[1];
        state->m0[1] = state->m0[0];
        state->m0[0] = in[i];
    }
}

}
