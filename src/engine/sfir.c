/* Sound FIR design (sfir.c): computes the five coefficients of the symmetric 8-tap FIR filters
   (windowed sinc, Hamming window) for a low-pass (type 2), high-pass (type 3) or band-pass (type 4)
   response at the state cutoffs +0x34/+0x38, normalized to unit gain. */

#include "engine/sndsys.h"

extern "C" {

float SNDI_sin(float x);
float SNDI_cos(float x);

void calcFIRCoeffs(SndFirState_t *state, int type)
{
    int half = 4;
    int i;
    float w;
    float t;
    float s;
    float sum;
    float step;

    if ((unsigned int)(type - 3) <= 1 && !(state->m34 <= 0.8f)) {
        state->m34 = 0.8f;
    }
    switch (type) {
    case 2:
        state->m20[half] = state->m38;
        for (i = 1; i <= half; i++) {
            w = (float)i * 3.1415927f;
            state->m20[half - i] = SNDI_sin(state->m38 * w) / w;
        }
        break;
    case 3:
        state->m20[half] = state->m34;
        for (i = 1; i <= half; i++) {
            w = (float)i * 3.1415927f;
            state->m20[half - i] = SNDI_sin(state->m34 * w) / w;
        }
        break;
    case 4:
        state->m20[half] = state->m38 - state->m34;
        for (i = 1; i <= half; i++) {
            w = (float)i * 3.1415927f;
            t = w * 0.5f;
            s = SNDI_sin((state->m38 - state->m34) * t);
            state->m20[half - i] = (s + s) * SNDI_cos((state->m38 + state->m34) * t) / w;
        }
        break;
    }
    step = 0.7853982f;
    sum = 0.0f;
    for (i = 0; i <= half; i++) {
        if (type == 2 || type == 4) {
            state->m20[i] *= 0.54f - SNDI_cos(step * (float)i) * 0.46f;
            sum += state->m20[i];
        } else if (type == 3) {
            state->m20[i] *= SNDI_cos(step * (float)i) * 0.46f - 0.54f;
            if (i & 1) {
                sum -= state->m20[i];
            } else {
                sum += state->m20[i];
            }
        }
    }
    if (type == 3) {
        state->m20[half] += 1.0f;
        sum += 1.0f;
    }
    sum = sum + sum - state->m20[half];
    if (!(sum >= 0.0f)) {
        sum = -sum;
    }
    for (i = 0; i <= half; i++) {
        state->m20[i] /= sum;
    }
}

}
