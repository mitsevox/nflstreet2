#ifndef ENGINE_LLMATRIX_H
#define ENGINE_LLMATRIX_H

#include "engine/matrix.h"

/* Matrix stack operations on the current stack and matrix helpers. */
#ifdef __cplusplus
extern "C" {
#endif

void MatMakeUnitMatrix(float *pMatrix);
void MatCopyMatrix(float *pDst, float *pSrc);
float *MatGetCurMatrixPtr(void);
void MatSetStack(unsigned int index);
void MatResetStack(void);
void MatPush(void);
void MatPushUnit(void);
void MatPop(void);
void MatMakeUnit(void);
void MatMulMatrices(float *pDst, float *pA, float *pB);
void MatMulMatrices4x4(float *pDst, float *pA, float *pB);
void MatCat(float *pMatrix);
void MatCat4x4(float *pMatrix);
void MatLoad(float *pMatrix);
void MatLLInit(void);
void MatRotAxis(float *pAxis, int angle);
void MatRotQuat(float *pQuat);
void MatRotX(int angle);
void MatRotY(int angle);
void MatRotZ(int angle);
void MatRotZYX(int z, int y, int x);
void MatSetAxes(float *pMatrix, float *pX, float *pY, float *pZ);
void MatTranslate(float *pPos);
void MatScale(float scale);
void MatScaleCol(float x, float y, float z);
void MatScalePos(float scale);
void MatTranspose(void);
void MatInvertRigid(void);
void MatStore(float *pMatrix);
void MatGetPos(float *pPos);
void MatGetRotFromMatrixZYX(int *pAngles, float *pMatrix);
void MatGetRotFromMatrixYZX(int *pAngles, float *pMatrix);
void MatGetRotByOrder(int *pAngles, unsigned int order);
void MatSetSlot(int slot, float *pMatrix);
void MatGetSlot(int slot, float *pMatrix);
void MatLoadSlot(int slot);
void MatStoreSlot(int slot);
void MatCatSlot(int slot);

#ifdef __cplusplus
}
#endif

#endif
