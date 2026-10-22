#include "engine/cu_801C06E8.h"
#include "game/fn_801D2B7C.h"

extern void fn_8020DFD8(int data, Image_8020DFD8 *image);
extern int fn_8020E258(Image_8020DFD8 *image);

void fn_801C0E04(Texture_801C0928 *texture)
{
    TextureGX_801C0E04 *gx = &texture->mGX;
    unsigned short i;

    if (!texture->mAnimated) {
        gx->mFrames = 0;
        return;
    }
    if (gx->mFrames == 0)
        gx->mFrames = fn_801D2B7C(texture->mFrameCount * sizeof(TextureFrame_801C0E04), 0, 0);
    for (i = 0; i < texture->mFrameCount; i++) {
        unsigned short row = i / texture->mColumns;
        unsigned short column = i % texture->mColumns;

        gx->mFrames[i].mU0 = texture->mCellWidth * (unsigned int)column;
        gx->mFrames[i].mV0 = texture->mCellHeight * (unsigned int)row;
        gx->mFrames[i].mU1 = texture->mCellWidth * (unsigned int)(column + 1);
        gx->mFrames[i].mV1 = texture->mCellHeight * (unsigned int)(row + 1);
    }
}

void fn_801C0F64(int data, Image_8020DFD8 *image)
{
    fn_8020DFD8(data, image);
}

void fn_801C0F84(Image_8020DFD8 *image)
{
    fn_8020E258(image);
}

void fn_801C0FA4(Texture_801C0928 *texture)
{
    if (texture->mImage.mpPalette != 0) {
        unsigned short entries = 256;

        if (texture->mImage.mFormat == GX_TF_C4)
            entries = 16;
        GXInitTlutObj(&texture->mGX.mTlutObj, texture->mImage.mpPalette,
                      texture->mImage.mPaletteFormat, entries);
        GXInitTexObjCI(&texture->mGX.mTexObj, texture->mImage.mpPixels, texture->mImage.mWidth,
                       texture->mImage.mHeight, texture->mImage.mFormat, GX_CLAMP, GX_CLAMP, 0, 0);
    } else {
        GXInitTexObj(&texture->mGX.mTexObj, texture->mImage.mpPixels, texture->mImage.mWidth,
                     texture->mImage.mHeight, texture->mImage.mFormat, GX_CLAMP, GX_CLAMP, 0);
    }
    fn_801C0E04(texture);
}

void fn_801C1054(Texture_801C0928 *texture)
{
    if (texture->mAnimated) {
        TextureGX_801C0E04 *gx = &texture->mGX;
        gx->mFrames = fn_801D2B7C(texture->mFrameCount * sizeof(TextureFrame_801C0E04), 0, 0);
    }
}

void fn_801C10A4(Texture_801C0928 *texture)
{
    TextureGX_801C0E04 *gx = &texture->mGX;

    if (texture->mAnimated)
        fn_801D2BD0(gx->mFrames);
}

void fn_801C10D8(void *p)
{
}

void fn_801C10DC(void *p)
{
}
