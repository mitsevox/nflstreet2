#ifndef ENGINE_TMTEXLIB_H
#define ENGINE_TMTEXLIB_H

/* Filter descriptor read by TMTextureSetFilterParm through TMTexLibSetFilterParm: TMTextureSetFilterParm
   passes the words +0 and +4, the float +8, the bytes +0x10 and +0x11 and the
   word +0xC to TMTextureSetFilter, which hands them to GXInitTexObjLOD as min/mag
   filter, LOD bias, bias clamp, edge LOD and max anisotropy. */
typedef struct TMTexFilterDesc_t {
    int mMinFilter;
    int mMagFilter;
    float mLodBias;
    int mMaxAniso;
    unsigned char mbBiasClamp;
    unsigned char mbEdgeLod;
} TMTexFilterDesc_t;

/* Wrap descriptor read by TMTextureSetWrapParm through TMTexLibSetWrapParm; TMTextureSetWrapParm
   passes its two words to GXInitTexObjWrapMode as the S and T wrap modes. */
typedef struct TMTexWrapDesc_t {
    int mWrapS;
    int mWrapT;
} TMTexWrapDesc_t;

typedef struct TMTexLib_t TMTexLib_t;

#ifdef __cplusplus
extern "C" {
#endif
void TMTexLibSetFilterParm(TMTexLib_t *pLib, TMTexFilterDesc_t *pDesc);
void TMTexLibSetWrapParm(TMTexLib_t *pLib, TMTexWrapDesc_t *pDesc);
#ifdef __cplusplus
}
#endif

#endif
