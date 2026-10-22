#ifndef ENGINE_CU_801C06E8_H
#define ENGINE_CU_801C06E8_H

#include <dolphin/gx/GXTexture.h>
#include "engine/texture.h"

typedef struct TextureFrame_801C0E04 {
    float mU0;
    float mV0;
    float mU1;
    float mV1;
} TextureFrame_801C0E04;

typedef struct TextureGX_801C0E04 {
    unsigned char mUnknown0[4];
    GXTexObj mTexObj;
    GXTlutObj mTlutObj;
    TextureFrame_801C0E04 *mFrames;
} TextureGX_801C0E04;

typedef struct Texture_801C0928 {
    char mName[32];
    int mIndex;
    unsigned char mUnknown24[4];
    Texture_8020DB34 mImage;
    unsigned char mAnimated;
    unsigned char mLoaded;
    unsigned short mFrameCount;
    unsigned short mRows;
    unsigned short mColumns;
    float mCoords[8];
    float mCellWidth;
    float mCellHeight;
    TextureGX_801C0E04 mGX;
} Texture_801C0928;

typedef struct TextureDesc_801C0928 {
    char mName[32];
    unsigned char mAnimated;
    unsigned char mRelocated;
    unsigned short mFrameCount;
    unsigned short mRows;
    unsigned short mColumns;
    int mData;
} TextureDesc_801C0928;

/* Configuration passed to fn_801C06E8, which reads only the capacity +0. The
   game's instance at 0x803EB22A (src/game/cu_801444D8.cpp) is 6 bytes,
   initialized {8, 0, 0, 0}, and the byte +4 is stored before the call. */
typedef struct TextureConfig_801C06E8 {
    unsigned short mCapacity;
    unsigned short mUnknown2;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
} TextureConfig_801C06E8;

typedef struct TextureFile_801C0BA8 {
    void *mData;
    int mIndex;
} TextureFile_801C0BA8;

typedef struct TextureManager_802F4870 {
    unsigned char mInitialized;
    unsigned short mCount;
    unsigned short mCapacity;
    Texture_801C0928 **mTextures;
    Texture_801C0928 *mPool;
    unsigned char mUnknown10[16];
} TextureManager_802F4870;

extern TextureManager_802F4870 lbl_802F4870;

#ifdef __cplusplus
extern "C" {
#endif
void fn_801C06E8(TextureConfig_801C06E8 *config);
void fn_801C07DC(void);
void fn_801C089C(Texture_801C0928 *texture);
void fn_801C0928(Texture_801C0928 *texture, TextureDesc_801C0928 *desc);
void fn_801C09B8(Texture_801C0928 *texture);
void fn_801C09F8(Texture_801C0928 *texture);
void fn_801C0A38(Texture_801C0928 *texture, unsigned int time, unsigned int frame, unsigned int rate, float *coords);
Texture_801C0928 *fn_801C0BA8(TextureFile_801C0BA8 *file, int load);
Texture_801C0928 *fn_801C0C14(TextureDesc_801C0928 *desc, int *pData, int load);
void fn_801C0CCC(Texture_801C0928 *texture);
void fn_801C0E04(Texture_801C0928 *texture);
void fn_801C0F64(int data, Texture_8020DB34 *image);
void fn_801C0F84(Texture_8020DB34 *image);
void fn_801C0FA4(Texture_801C0928 *texture);
void fn_801C1054(Texture_801C0928 *texture);
void fn_801C10A4(Texture_801C0928 *texture);
void fn_801C10D8(void *p);
void fn_801C10DC(void *p);
#ifdef __cplusplus
}
#endif

#endif
