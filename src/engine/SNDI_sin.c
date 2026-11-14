/* Sound math (SNDI_sin.c): the sine the sound library uses for panning and filter coefficients,
   a Taylor series in x after reducing x below 2*pi. */

#include "engine/sndsys.h"

extern "C" {

float SNDI_sin(float x)
{
    float x2;
    float x3;
    float x5;
    float x7;
    float x9;
    float x11;

    // FAKEMATCH: guarded do-while with a negated <= entry test reproduces the target's cror entry branch
    if (!(x <= 6.2831855f)) {
        do {
            x -= 6.2831855f;
        } while (x > 6.2831855f);
    }
    x2 = x * x;
    x3 = x2 * x;
    x5 = x2 * x3;
    x7 = x2 * x5;
    x9 = x2 * x7;
    x11 = x2 * x9;
    return x - x3 * 0.16666667f + x5 * 0.00833333f - x7 * 0.0001984127f + x9 * 2.7557319e-06f -
           x11 * 2.5052108e-08f + x2 * x11 * 1.6059e-10f;
}

}
