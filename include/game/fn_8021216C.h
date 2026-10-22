#ifndef GAME_FN_8021216C_H
#define GAME_FN_8021216C_H

/* Filter descriptor read by fn_80212310 through fn_8021216C: fn_80212310
   passes the words +0 and +4, the float +8, the bytes +0x10 and +0x11 and the
   word +0xC to fn_80212234, which hands them to GXInitTexObjLOD as min/mag
   filter, LOD bias, bias clamp, edge LOD and max anisotropy. */
typedef struct Desc_802EE9E4 {
    int mMinFilter;
    int mMagFilter;
    float mLodBias;
    int mMaxAniso;
    unsigned char mbBiasClamp;
    unsigned char mbEdgeLod;
} Desc_802EE9E4;

/* Wrap descriptor read by fn_80212374 through fn_802121D0; fn_80212374
   passes its two words to GXInitTexObjWrapMode as the S and T wrap modes. */
typedef struct TexWrapDesc_80212374 {
    int mWrapS;
    int mWrapT;
} TexWrapDesc_80212374;

typedef struct TexLib_802119C4 TexLib_802119C4;

#ifdef __cplusplus
extern "C" {
#endif
void fn_8021216C(TexLib_802119C4 *pLib, Desc_802EE9E4 *pDesc);
void fn_802121D0(TexLib_802119C4 *pLib, TexWrapDesc_80212374 *pDesc);
#ifdef __cplusplus
}
#endif

#endif
