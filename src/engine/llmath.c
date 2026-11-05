/* Low-level math helpers: angle-table init and guarded reciprocals. */

void fn_801CF998(void);
float fn_80260B1C(float x);

void MathLLInit(void)
{
    fn_801CF998();
}

float MathInvSqrt(float x)
{
    float s = fn_80260B1C(x);
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
