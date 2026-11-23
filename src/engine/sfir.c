/* Builds the symmetric coefficients for a nine-tap sound filter.
   Low-pass and band-pass normalize at DC. High-pass adds a unit impulse at the center tap
   and uses an alternating coefficient sum to normalize at Nyquist. */

#include "engine/sndsys.h"

extern "C" {

void calcFIRCoeffs(SndFirState_t *state, int type)
{
    const int center = 4;
    int half = center;
    int i;
    float w;
    float t;
    float s;
    float sum;

    if ((unsigned int)type - 3u <= 1u && !(state->m34 <= 0.8f)) {
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
    w = 0.7853982f;
    sum = 0.0f;
    for (i = 0; i <= half; i++) {
        if (type == 2 || type == 4) {
            state->m20[i] *= 0.54f - SNDI_cos(w * (float)i) * 0.46f;
            sum += state->m20[i];
        } else if (type == 3) {
            state->m20[i] *= SNDI_cos(w * (float)i) * 0.46f - 0.54f;
            sum = (i & 1) == 0 ? sum + state->m20[i] : sum - state->m20[i];
        }
    }
    if (type == 3) {
        state->m20[half] += 1.0f;
        sum += 1.0f;
    }
    t = state->m20[center];
    sum += sum;
    sum -= t;
    if (!(sum >= 0.0f)) {
        sum = -sum;
    }
    for (i = 0; i <= half; i++) {
        state->m20[i] /= sum;
    }
}

}
