#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

/* render.c (0x801DB7D4-0x801DB900): movie frame placement and YUV plane output. */

#ifdef __cplusplus
extern "C" {
#endif

void yuvrenderinit(int x, int y, int width, int height, int unknown4, int unused);
void yuvrenderDoubleYLines(unsigned char **ppPlanes);
void yuvrenderVP6YLines(unsigned char **ppPlanes);

#ifdef __cplusplus
}
#endif

#endif
