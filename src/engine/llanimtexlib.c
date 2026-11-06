/* GameCube side of the animated texture library: sets up the GX texture objects
   for animated textures and the texture coordinates of each animation cell in
   their grid. */

#include "engine/animTexLib.h"
#include "game/fn_801D2B7C.h"

void _LLAnimTexBuildTexCoords(Texture_801C0928 *texture)
{
    LLAnimTexGX_t *gx = &texture->mGX;
    unsigned short i;

    if (!texture->mAnimated) {
        gx->mFrames = 0;
        return;
    }
    if (gx->mFrames == 0)
        gx->mFrames = fn_801D2B7C(texture->mFrameCount * sizeof(LLAnimTexFrame_t), 0, 0);
    for (i = 0; i < texture->mFrameCount; i++) {
        unsigned short row = i / texture->mColumns;
        unsigned short column = i % texture->mColumns;

        gx->mFrames[i].mU0 = texture->mCellWidth * (unsigned int)column;
        gx->mFrames[i].mV0 = texture->mCellHeight * (unsigned int)row;
        gx->mFrames[i].mU1 = texture->mCellWidth * (unsigned int)(column + 1);
        gx->mFrames[i].mV1 = texture->mCellHeight * (unsigned int)(row + 1);
    }
}

void LLAnimTexCreateTexture(int data, Texture_t *image)
{
    TexCreate((void *)data, image);
}

void LLAnimTexDeleteTexture(Texture_t *image)
{
    TexDelete(image);
}

void LLAnimTexBindTexture(Texture_801C0928 *texture)
{
    if (texture->mImage.mpPalette != 0) {
        unsigned short entries = 256;

        if (texture->mImage.mFormat == GX_TF_C4)
            entries = 16;
        GXInitTlutObj(&texture->mGX.mTlutObj, texture->mImage.mpPalette,
                      texture->mImage.mTlutFormat, entries);
        GXInitTexObjCI(&texture->mGX.mTexObj, texture->mImage.mpImage, texture->mImage.mWidth,
                       texture->mImage.mHeight, texture->mImage.mFormat, GX_CLAMP, GX_CLAMP, 0, 0);
    } else {
        GXInitTexObj(&texture->mGX.mTexObj, texture->mImage.mpImage, texture->mImage.mWidth,
                     texture->mImage.mHeight, texture->mImage.mFormat, GX_CLAMP, GX_CLAMP, 0);
    }
    _LLAnimTexBuildTexCoords(texture);
}

void LLAnimTexAllocTexCoords(Texture_801C0928 *texture)
{
    if (texture->mAnimated) {
        LLAnimTexGX_t *gx = &texture->mGX;
        gx->mFrames = fn_801D2B7C(texture->mFrameCount * sizeof(LLAnimTexFrame_t), 0, 0);
    }
}

void LLAnimTexUnbindTexture(Texture_801C0928 *texture)
{
    LLAnimTexGX_t *gx = &texture->mGX;

    if (texture->mAnimated)
        fn_801D2BD0(gx->mFrames);
}

void LLAnimTexLibInit(void *p)
{
}

void LLAnimTexLibShutdown(void *p)
{
}
