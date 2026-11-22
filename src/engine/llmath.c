/* Low-level math helpers: angle-table init and guarded reciprocals. */

#include <math.h>

void fn_801CF998(void);

void MathLLInit(void)
{
    fn_801CF998();
}

float MathInvSqrt(float x)
{
    float s = sqrtf(x);
    float result;

    if (!(s <= 1e-07f)) {
        result = 1.0f / s;
    } else {
        result = 0.0f;
    }
    return result;
}

float MathInverse(float x)
{
    float result = 0.0f;

    if (!(x <= 1e-07f)) {
        result = 1.0f / x;
    }
    return result;
}
