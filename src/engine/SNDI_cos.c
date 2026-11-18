/* Sound math (SNDI_cos.c): the cosine the sound library uses for panning and filter coefficients,
   a Taylor series in x after reducing x below 2*pi. */

#include "engine/sndsys.h"

extern "C" {

float SNDI_cos(float x)
{
    float x2;
    float x4;
    float x6;
    float x8;

    // FAKEMATCH: guarded do-while with a negated <= entry test reproduces the target's cror entry branch
    if (!(x <= 6.2831855f)) {
        do {
            x -= 6.2831855f;
        } while (x > 6.2831855f);
    }
    x2 = x * x;
    x4 = x2 * x2;
    x6 = x2 * x4;
    x8 = x4 * x4;
    return 1.0f - x2 * 0.5f + x4 * 0.041666668f - x6 * 0.0013888889f + x8 * 2.4801588e-05f -
           x2 * x8 * 2.755732e-07f + x6 * x6 * 2.0876758e-09f;
}

}
