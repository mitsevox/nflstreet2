#ifndef ENGINE_CU_801D03D0_H
#define ENGINE_CU_801D03D0_H

#include "engine/cu_801D0110.h"

/* Matrix stack operations on the current stack and matrix helpers. */
#ifdef __cplusplus
extern "C" {
#endif

void fn_801D03D0(float *pMatrix);
void fn_801D0424(float *pDst, float *pSrc);
float *fn_801D0444(void);
void fn_801D0470(unsigned int index);
void fn_801D0494(void);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0558(void);
void fn_801D058C(float *pDst, float *pA, float *pB);
void fn_801D05BC(float *pDst, float *pA, float *pB);
void fn_801D0664(float *pMatrix);
void fn_801D069C(float *pMatrix);
void fn_801D06D4(float *pMatrix);
void fn_801D070C(void);
void fn_801D0710(float *pAxis, int angle);
void fn_801D0860(float *pQuat);
void fn_801D08FC(int angle);
void fn_801D09EC(int angle);
void fn_801D0ADC(int angle);
void fn_801D0BCC(int z, int y, int x);
void fn_801D0C0C(float *pMatrix, float *pX, float *pY, float *pZ);
void fn_801D0C58(float *pPos);
void fn_801D0CFC(float scale);
void fn_801D0D94(float x, float y, float z);
void fn_801D0E44(float scale);
void fn_801D0E94(void);
void fn_801D0EE4(void);
void fn_801D0F80(float *pMatrix);
void fn_801D0FB8(float *pPos);
void fn_801D0FFC(int *pAngles, float *pMatrix);
void fn_801D10F8(int *pAngles, float *pMatrix);
void fn_801D11F4(int *pAngles, unsigned int order);
void fn_801D1258(int slot, float *pMatrix);
void fn_801D1288(int slot, float *pMatrix);
void fn_801D12BC(int slot);
void fn_801D12EC(int slot);
void fn_801D131C(int slot);

#ifdef __cplusplus
}
#endif

#endif
