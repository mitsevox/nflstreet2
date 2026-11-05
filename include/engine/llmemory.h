#ifndef ENGINE_LLMEMORY_H
#define ENGINE_LLMEMORY_H

/* llmemory.c (0x801D34C4-0x801D36E8): low-level heap memory hooks and the pattern fill. */

#ifdef __cplusplus
extern "C" {
#endif

void *MemGetMemLL(unsigned int size);
void MemFreeMemLL(void *pAddr);
int MemFill(char *pDst, unsigned int size, int value, unsigned int width);

#ifdef __cplusplus
}
#endif

#endif
