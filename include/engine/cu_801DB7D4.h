#ifndef ENGINE_CU_801DB7D4_H
#define ENGINE_CU_801DB7D4_H

/* render.c (0x801DB7D4-0x801DB900): movie frame placement and YUV plane output. */

#ifdef __cplusplus
extern "C" {
#endif

void fn_801DB7D8(int x, int y, int width, int height, int mode, int unused);
void fn_801DB838(unsigned char **ppPlanes);
void fn_801DB89C(unsigned char **ppPlanes);

#ifdef __cplusplus
}
#endif

#endif
