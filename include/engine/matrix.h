#ifndef ENGINE_MATRIX_H
#define ENGINE_MATRIX_H

typedef float MatMatrix_t[16];

typedef struct MatStack_t {
    unsigned int mDepth;
    int mTop;
    MatMatrix_t *mpMatrices;
} MatStack_t;

MatStack_t *MatGetStackPtrFromIndex(unsigned int index);

#endif
