#ifndef ENGINE_POLYNOMIAL_H
#define ENGINE_POLYNOMIAL_H

#ifdef __cplusplus
extern "C" {
#endif

int FindPolynomialRoots(float *pCoef, int degree, float lo, int includeLo, float hi, int includeHi, float *pRoots);

#ifdef __cplusplus
}
#endif

#endif
