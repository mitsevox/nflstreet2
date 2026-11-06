#ifndef ENGINE_VRAM_H
#define ENGINE_VRAM_H

/* Argument of VramInit. */
typedef struct VramInitBlock_t {
    unsigned short mUnknown0;
    unsigned char mUnknown2[2];
} VramInitBlock_t;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/vram.c */
int VramInit(VramInitBlock_t *pDesc);
int VramShutdown(void);

#ifdef __cplusplus
}
#endif

#endif
