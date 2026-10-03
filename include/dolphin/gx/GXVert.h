#ifndef _DOLPHIN_GX_GXVERT_H_
#define _DOLPHIN_GX_GXVERT_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GXFIFO_ADDR 0xCC008000

typedef union {
    u8  u8;
    u16 u16;
    u32 u32;
    u64 u64;
    s8  s8;
    s16 s16;
    s32 s32;
    s64 s64;
    f32 f32;
    f64 f64;
} PPCWGPipe;

#ifdef __MWERKS__
volatile PPCWGPipe GXWGFifo AT_ADDRESS(GXFIFO_ADDR);
#else
#define GXWGFifo (*(volatile PPCWGPipe *)GXFIFO_ADDR)
#endif

#ifdef __cplusplus
}
#endif

#endif
