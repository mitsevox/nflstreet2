#ifndef _MATH_H_
#define _MATH_H_

#ifdef __MWERKS__
#pragma cplusplus on
extern inline float sqrtf(float x)
{
    const double _half = .5;
    const double _three = 3.0;
    volatile float y;
    if (x > 0.0f)
    {
#ifdef __MWERKS__
        double guess = __frsqrte((double)x);   // returns an approximation to
#else
        double guess;
        asm("frsqrte %0, %1" : "=f"(guess) : "f"(x));
#endif
        guess = _half*guess*(_three - guess*guess*x);  // now have 12 sig bits
        guess = _half*guess*(_three - guess*guess*x);  // now have 24 sig bits
        guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
        y = (float)(x*guess);
        return y ;
    }
    return x;
}

#pragma cplusplus reset
#else
#ifdef __cplusplus
extern "C" {
#endif
float sqrtf(float x);
#ifdef __cplusplus
}
#endif
#endif

#endif
