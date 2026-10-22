#include "engine/cu_801C06E8.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"

extern int fn_801D34D0(void *dest, int size, int value, int width);
extern char *strcpy();
extern int strcmp();

void fn_801C06E8(TextureConfig_801C06E8 *config)
{
    Texture_801C0928 *pool;
    unsigned short i;

    lbl_802F4870.mCount = 0;
    lbl_802F4870.mCapacity = config->mCapacity;
    fn_801C10D8(lbl_802F4870.mUnknown10);
    lbl_802F4870.mTextures = fn_801D2B7C(lbl_802F4870.mCapacity * sizeof(Texture_801C0928 *), 0, 0);
    fn_801D34D0(lbl_802F4870.mTextures, lbl_802F4870.mCapacity * sizeof(Texture_801C0928 *), 0, 1);
    lbl_802F4870.mPool = fn_801D2B7C(lbl_802F4870.mCapacity * sizeof(Texture_801C0928), 0, 0);
    fn_801D34D0(lbl_802F4870.mPool, lbl_802F4870.mCapacity * sizeof(Texture_801C0928), 0, 1);
    pool = lbl_802F4870.mPool;
    for (i = 0; i < lbl_802F4870.mCapacity; i++)
        lbl_802F4870.mTextures[i] = &pool[i];
    lbl_802F4870.mInitialized = 1;
}

void fn_801C07DC(void)
{
    unsigned short i;

    for (i = 0; i < lbl_802F4870.mCount; i++) {
        Texture_801C0928 *texture = lbl_802F4870.mTextures[i];
        fn_801C0F84(&texture->mImage);
        if (texture->mLoaded)
            fn_801C09F8(texture);
    }
    fn_801D2BD0(lbl_802F4870.mTextures);
    lbl_802F4870.mTextures = 0;
    fn_801D2BD0(lbl_802F4870.mPool);
    lbl_802F4870.mPool = 0;
    fn_801C10DC(lbl_802F4870.mUnknown10);
    fn_801C10DC(lbl_802F4870.mUnknown10);
    lbl_802F4870.mCount = 0;
    lbl_802F4870.mCapacity = 0;
    lbl_802F4870.mInitialized = 0;
}

void fn_801C089C(Texture_801C0928 *texture)
{
    unsigned int columns = texture->mColumns;
    unsigned int rows = texture->mRows;
    float width = 1.0f / columns;
    float height = 1.0f / rows;

    texture->mCoords[0] = 0.0f;
    texture->mCoords[1] = 0.0f;
    texture->mCoords[2] = width;
    texture->mCoords[3] = 0.0f;
    texture->mCoords[4] = width;
    texture->mCoords[5] = height;
    texture->mCoords[6] = 0.0f;
    texture->mCoords[7] = height;
    texture->mCellWidth = width;
    texture->mCellHeight = height;
}

void fn_801C0928(Texture_801C0928 *texture, TextureDesc_801C0928 *desc)
{
    fn_801D34D0(texture, sizeof(Texture_801C0928), 0, 1);
    strcpy(texture->mName, desc->mName);
    texture->mAnimated = desc->mAnimated;
    texture->mFrameCount = desc->mFrameCount;
    texture->mRows = desc->mRows;
    texture->mColumns = desc->mColumns;
    if (!desc->mRelocated) {
        desc->mRelocated = 1;
        desc->mData = (int)desc + desc->mData;
    }
    fn_801C089C(texture);
}

void fn_801C09B8(Texture_801C0928 *texture)
{
    if (!texture->mLoaded) {
        fn_801C0FA4(texture);
        texture->mLoaded = 1;
    }
}

void fn_801C09F8(Texture_801C0928 *texture)
{
    if (texture->mLoaded == 1) {
        fn_801C10A4(texture);
        texture->mLoaded = 0;
    }
}

void fn_801C0A38(Texture_801C0928 *texture, unsigned int time, unsigned int frame,
                 unsigned int rate, float *coords)
{
    unsigned int count = texture->mFrameCount;

    if (count > 1) {
        unsigned int row;
        unsigned int column;

        if (texture->mAnimated && rate != 0)
            frame += (time / rate) % count;
        column = frame % texture->mColumns;
        row = frame / texture->mColumns;
        if (row >= texture->mRows)
            row %= texture->mRows;
        coords[0] = texture->mCellWidth * column;
        coords[1] = texture->mCellHeight * row;
        coords[2] = texture->mCellWidth * (column + 1);
        coords[3] = texture->mCellHeight * row;
        coords[4] = texture->mCellWidth * (column + 1);
        coords[5] = texture->mCellHeight * (row + 1);
        coords[6] = texture->mCellWidth * column;
        coords[7] = texture->mCellHeight * (row + 1);
    } else {
        coords[0] = 0.0f;
        coords[1] = 0.0f;
        coords[2] = 1.0f;
        coords[3] = 0.0f;
        coords[4] = 1.0f;
        coords[5] = 1.0f;
        coords[6] = 0.0f;
        coords[7] = 1.0f;
    }
}

Texture_801C0928 *fn_801C0BA8(TextureFile_801C0BA8 *file, int load)
{
    int data;
    Texture_801C0928 *texture;

    texture = fn_801C0C14((TextureDesc_801C0928 *)fn_801EF390(file->mData, file->mIndex, 1), &data, load);
    texture->mIndex = file->mIndex;
    if (load)
        fn_801F010C(file->mData, file->mIndex);
    return texture;
}

Texture_801C0928 *fn_801C0C14(TextureDesc_801C0928 *desc, int *pData, int load)
{
    TextureManager_802F4870 *manager = &lbl_802F4870;
    Texture_801C0928 *texture = manager->mTextures[manager->mCount];

    fn_801C0928(texture, desc);
    if (load && !texture->mLoaded)
        fn_801C1054(texture);
    *pData = desc->mData;
    fn_801C0F64(*pData, &texture->mImage);
    fn_801C09B8(texture);
    if (load)
        fn_801C0F84(&texture->mImage);
    lbl_802F4870.mCount++;
    return texture;
}

void fn_801C0CCC(Texture_801C0928 *texture)
{
    int last = lbl_802F4870.mCount - 1;
    int i;

    for (i = 0; i < lbl_802F4870.mCount; i++) {
        if (lbl_802F4870.mTextures[i] == texture) {
            if (i < last) {
                lbl_802F4870.mTextures[i] = lbl_802F4870.mTextures[last];
                lbl_802F4870.mTextures[last] = texture;
            }
            break;
        }
    }
    fn_801C0F84(&texture->mImage);
    if (texture->mLoaded)
        fn_801C09F8(texture);
    lbl_802F4870.mCount--;
}

Texture_801C0928 *fn_801C0D8C(const char *name)
{
    Texture_801C0928 *texture = 0;
    unsigned short i;

    for (i = 0; i < lbl_802F4870.mCount; i++) {
        if (strcmp(lbl_802F4870.mTextures[i]->mName, name) == 0) {
            texture = lbl_802F4870.mTextures[i];
            break;
        }
    }
    return texture;
}
