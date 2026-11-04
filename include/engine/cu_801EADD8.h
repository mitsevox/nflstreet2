#ifndef ENGINE_CU_801EADD8_H
#define ENGINE_CU_801EADD8_H

#include "engine/vec.h"

/* Axis-aligned box. */
class Class_801EADD8 {
public:
    Class_801EADD8();
    virtual ~Class_801EADD8();
    void fn_801EAE44(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax);
    void fn_801EAE7C(Vec3_801DE1E0 *pPoint);
    void fn_801EAEB4(Vec3_801DE1E0 *pPoint);
    void fn_801EAF60(float (*m)[4], Class_801EADD8 *pOut);
    void fn_801EB134(int a, int b, int c);

    Vec3_801DE1E0 mMin;
    Vec3_801DE1E0 mMax;
};

#endif
