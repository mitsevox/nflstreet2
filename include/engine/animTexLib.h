#ifndef ENGINE_ANIMTEXLIB_H
#define ENGINE_ANIMTEXLIB_H

#include <dolphin/gx/GXTexture.h>
#include "engine/texture.h"

typedef struct LLAnimTexFrame_t {
    float mU0;
    float mV0;
    float mU1;
    float mV1;
} LLAnimTexFrame_t;

typedef struct LLAnimTexGX_t {
    unsigned char unk_0x0[4];
    GXTexObj mTexObj;
    GXTlutObj mTlutObj;
    LLAnimTexFrame_t *mFrames;
} LLAnimTexGX_t;

typedef struct AnimTex_t {
    char mName[32];
    int mIndex;
    unsigned char unk_0x24[4];
    Texture_t mImage;
    unsigned char mAnimated;
    unsigned char mBound;
    unsigned short mFrameCount;
    unsigned short mRows;
    unsigned short mColumns;
    float mCoords[8];
    float mCellWidth;
    float mCellHeight;
    LLAnimTexGX_t mGX;
} AnimTex_t;

typedef union AnimTexData_t {
    unsigned int mOffset;
    void *mpData;
} AnimTexData_t;

typedef struct AnimTexDesc_t {
    char mName[32];
    unsigned char mAnimated;
    unsigned char mRelocated;
    unsigned short mFrameCount;
    unsigned short mRows;
    unsigned short mColumns;
    AnimTexData_t mData;
} AnimTexDesc_t;

typedef struct AnimTexConfig_t {
    unsigned short mCapacity;
    unsigned char unk_0x2[2];
    unsigned char unk_0x4;
    unsigned char unk_0x5;
} AnimTexConfig_t;

typedef struct AnimTexFile_t {
    void *mData;
    int mIndex;
} AnimTexFile_t;

typedef struct AnimTexManager_t {
    unsigned char mInitialized;
    unsigned short mCount;
    unsigned short mCapacity;
    AnimTex_t **mTextures;
    AnimTex_t *mPool;
} AnimTexManager_t;

extern AnimTexManager_t _AnimTexLib_sManager;

#ifdef __cplusplus
extern "C" {
#endif
void AnimTexLibInit(AnimTexConfig_t *config);
void AnimTexLibShutdown(void);
void AnimTexInitCoords(AnimTex_t *texture);
void AnimTexInitTexture(AnimTex_t *texture, AnimTexDesc_t *desc);
void AnimTexBind(AnimTex_t *texture);
void AnimTexUnbind(AnimTex_t *texture);
void AnimTexGetCoords(AnimTex_t *texture, unsigned int time, unsigned int frame, unsigned int rate, float *coords);
AnimTex_t *AnimTexLoadResource(AnimTexFile_t *file, int load);
AnimTex_t *AnimTexLoad(AnimTexDesc_t *desc, void **pData, int load);
void AnimTexFree(AnimTex_t *texture);
AnimTex_t *AnimTexFind(const char *name);
void _LLAnimTexBuildTexCoords(AnimTex_t *texture);
void LLAnimTexCreateTexture(void *data, Texture_t *image);
void LLAnimTexDeleteTexture(Texture_t *image);
void LLAnimTexBindTexture(AnimTex_t *texture);
void LLAnimTexAllocTexCoords(AnimTex_t *texture);
void LLAnimTexUnbindTexture(AnimTex_t *texture);
void LLAnimTexLibInit(void *p, AnimTexConfig_t *config);
void LLAnimTexLibShutdown(void *p);
#ifdef __cplusplus
}
#endif

#endif
