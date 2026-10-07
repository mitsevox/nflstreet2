#ifndef _DOLPHIN_GX_GXGET_H_
#define _DOLPHIN_GX_GXGET_H_

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXGetCullMode(GXCullMode* mode);

// Texture
GXBool GXGetTexObjMipMap(const GXTexObj* to);
GXTexFmt GXGetTexObjFmt(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
u16 GXGetTexObjHeight(const GXTexObj* to);
GXTexWrapMode GXGetTexObjWrapS(const GXTexObj* to);
GXTexWrapMode GXGetTexObjWrapT(const GXTexObj* to);
void* GXGetTexObjData(const GXTexObj* to);
void GXGetTexObjAll(const GXTexObj* obj, void** image_ptr, u16* width, u16* height, GXTexFmt* format, GXTexWrapMode* wrap_s, GXTexWrapMode* wrap_t, u8* mipmap);
void GXGetTexObjLODAll(const GXTexObj* tex_obj, GXTexFilter* min_filt, GXTexFilter* mag_filt, f32* min_lod, f32* max_lod, f32* lod_bias, u8* bias_clamp, u8* do_edge_lod, GXAnisotropy* max_aniso);
GXTexFilter GXGetTexObjMinFilt(const GXTexObj* tex_obj);
GXTexFilter GXGetTexObjMagFilt(const GXTexObj* tex_obj);
f32 GXGetTexObjMinLOD(const GXTexObj* tex_obj);
f32 GXGetTexObjMaxLOD(const GXTexObj* tex_obj);
f32 GXGetTexObjLODBias(const GXTexObj* tex_obj);
GXBool GXGetTexObjBiasClamp(const GXTexObj* tex_obj);
GXBool GXGetTexObjEdgeLOD(const GXTexObj* tex_obj);
GXAnisotropy GXGetTexObjMaxAniso(const GXTexObj* tex_obj);
u32 GXGetTexObjTlut(const GXTexObj* tex_obj);
void GXGetTlutObjAll(const GXTlutObj* tlut_obj, void** data, GXTlutFmt* format, u16* numEntries);
void* GXGetTlutObjData(const GXTlutObj* tlut_obj);
GXTlutFmt GXGetTlutObjFmt(const GXTlutObj* tlut_obj);
u16 GXGetTlutObjNumEntries(const GXTlutObj* tlut_obj);
void GXGetTexRegionAll(const GXTexRegion* region, u8* is_cached, u8* is_32b_mipmap, u32* tmem_even, u32* size_even, u32* tmem_odd, u32* size_odd);
void GXGetTlutRegionAll(const GXTlutRegion* region, u32* tmem_addr, GXTlutSize* tlut_size);

#ifdef __cplusplus
}
#endif

#endif
