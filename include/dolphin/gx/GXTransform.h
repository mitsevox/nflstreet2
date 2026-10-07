#ifndef _DOLPHIN_GX_GXTRANSFORM_H_
#define _DOLPHIN_GX_GXTRANSFORM_H_

#include <dolphin/types.h>
#include <dolphin/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXLoadPosMtxImm(f32 mtx[3][4], u32 id);
void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(f32 mtx[][4], u32 id, GXTexMtxType type);
void GXSetCurrentMtx(u32 id);
void GXSetProjectionv(const f32* ptr);
void GXSetClipMode(GXClipMode mode);
void GXSetScissorBoxOffset(s32 x_off, s32 y_off);
void GXSetScissor(u32 left,u32 top,u32 wd,u32 ht);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field);
void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);

#ifdef __cplusplus
}
#endif

#endif
