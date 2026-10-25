/* Comparison fragment of src/engine/cu_8021A438.c: fn_8021F77C, fn_8021F82C and their literal pools. */
#include "engine/cu_8021A438.h"

Uint8 fn_8021F77C(Uint32 a, Uint32 b, Uint32 c, Uint32 d, Float32 s, Float32 t)
{
    Float32 lo = a + (Int32)(b - a) * s;
    Float32 hi = d + (Int32)(c - d) * s;

    return lo + (hi - lo) * t;
}

Int16 fn_8021F82C(Int16 a, Int16 b, Int16 c, Int16 d, Float32 s, Float32 t)
{
    Float32 lo = a + (b - a) * s;
    Float32 hi = d + (c - d) * s;

    return lo + (hi - lo) * t;
}
