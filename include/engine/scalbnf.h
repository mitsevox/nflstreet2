/* Binary32 power-of-two scaling and its canonical sign-copy dependency. */
#ifndef ENGINE_SCALBNF_H
#define ENGINE_SCALBNF_H

#ifdef __cplusplus
extern "C" {
#endif

float scalbnf(float x, int n);
float copysignf(float x, float y);

#ifdef __cplusplus
}
#endif

#endif
