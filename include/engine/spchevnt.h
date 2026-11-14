#ifndef ENGINE_SPCHEVNT_H
#define ENGINE_SPCHEVNT_H

/* Declarations of src/engine/spchevnt.c used by several game units. */
extern "C" {
extern int (*gSPCH_AddEvent)(int, int, ...);

int fn_801AE5D4(int a, int b, int c);
void fn_801AF2CC(unsigned int channel);
int fn_801AF364(unsigned int channel);
}

#endif
