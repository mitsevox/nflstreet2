/* Reduced-angle binary32 sine with an optional low-part correction. */
#ifndef ENGINE_KERNEL_SINF_H
#define ENGINE_KERNEL_SINF_H

#ifdef __cplusplus
extern "C" {
#endif

float __kernel_sinf(float x, float y, int iy);

#ifdef __cplusplus
}
#endif

#endif
