/* Angle difference and interpolation in 24-bit angles. */

#include "engine/fn_801F7BD4.h"

int fn_801CFFD0(int a, int b)
{
    int diff = (a - b) & 0xFFFFFF;
    int other = 0x1000000 - diff;

    if (other < diff) {
        diff = other;
    }
    return diff;
}

int fn_801CFFF0(int a, int b, float t)
{
    int error = 0;
    int result;
    int diff;
    int other;

    if (!(t >= 0.0f)) {
        error = 0x40003;
        result = a;
    } else if (!(t <= 1.0f)) {
        error = 0x40003;
        result = b;
    } else {
        diff = (b - a) & 0xFFFFFF;
        other = 0x1000000 - diff;
        if (other < diff) {
            t = 1.0f - t;
            result = (b + (int)((float)other * t)) & 0xFFFFFF;
        } else {
            result = (a + (int)((float)diff * t)) & 0xFFFFFF;
        }
    }
    fn_801F7BD4(error);
    return result;
}
