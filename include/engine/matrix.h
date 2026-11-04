#ifndef ENGINE_MATRIX_H
#define ENGINE_MATRIX_H

typedef float Mtx_801D0110[16];

typedef struct MatStack_801D0110 {
    unsigned int mDepth;
    int mTop;
    Mtx_801D0110 *mpMatrices;
} MatStack_801D0110;

MatStack_801D0110 *fn_801D0110(unsigned int index);

#endif
