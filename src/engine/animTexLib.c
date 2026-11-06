/* Manages the animated textures used by particle effects, including loading, binding and frame coordinates. */

#include <string.h>
#include "engine/llmemory.h"
#include "engine/animTexLib.h"
#include "game/fn_801D2B7C.h"
#include "engine/Resource.h"


AnimTexManager_t _AnimTexLib_sManager = { 0 };

/* Free records start at the back of the table and enter its active prefix as textures are loaded. */
void AnimTexLibInit(AnimTexConfig_t *config)
{
    AnimTex_t *pool;
    unsigned short i;

    _AnimTexLib_sManager.mCapacity = config->mCapacity;
    _AnimTexLib_sManager.mCount = 0;
    LLAnimTexLibInit(&_AnimTexLib_sManager + 1, config);
    _AnimTexLib_sManager.mTextures = fn_801D2B7C(_AnimTexLib_sManager.mCapacity * sizeof(AnimTex_t *), 0, 0);
    MemFill((char *)_AnimTexLib_sManager.mTextures, _AnimTexLib_sManager.mCapacity * sizeof(AnimTex_t *), 0, 1);
    _AnimTexLib_sManager.mPool = fn_801D2B7C(_AnimTexLib_sManager.mCapacity * sizeof(AnimTex_t), 0, 0);
    MemFill((char *)_AnimTexLib_sManager.mPool, _AnimTexLib_sManager.mCapacity * sizeof(AnimTex_t), 0, 1);
    pool = _AnimTexLib_sManager.mPool;
    for (i = 0; i < _AnimTexLib_sManager.mCapacity; i++)
        _AnimTexLib_sManager.mTextures[i] = &pool[i];
    _AnimTexLib_sManager.mInitialized = 1;
}

void AnimTexLibShutdown(void)
{
    unsigned short i;

    for (i = 0; i < _AnimTexLib_sManager.mCount; i++) {
        AnimTex_t *texture = _AnimTexLib_sManager.mTextures[i];
        LLAnimTexDeleteTexture(&texture->mImage);
        if (texture->mBound)
            AnimTexUnbind(texture);
    }
    fn_801D2BD0(_AnimTexLib_sManager.mTextures);
    _AnimTexLib_sManager.mTextures = 0;
    fn_801D2BD0(_AnimTexLib_sManager.mPool);
    _AnimTexLib_sManager.mPool = 0;
    LLAnimTexLibShutdown(&_AnimTexLib_sManager + 1);
    LLAnimTexLibShutdown(&_AnimTexLib_sManager + 1);
    _AnimTexLib_sManager.mCount = 0;
    _AnimTexLib_sManager.mCapacity = 0;
    _AnimTexLib_sManager.mInitialized = 0;
}

void AnimTexInitCoords(AnimTex_t *texture)
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

void AnimTexInitTexture(AnimTex_t *texture, AnimTexDesc_t *desc)
{
    MemFill((char *)texture, sizeof(AnimTex_t), 0, 1);
    strcpy(texture->mName, desc->mName);
    texture->mAnimated = desc->mAnimated;
    texture->mFrameCount = desc->mFrameCount;
    texture->mRows = desc->mRows;
    texture->mColumns = desc->mColumns;
    if (!desc->mRelocated) {
        desc->mRelocated = 1;
        desc->mData.mpData = (char *)desc + desc->mData.mOffset;
    }
    AnimTexInitCoords(texture);
}

void AnimTexBind(AnimTex_t *texture)
{
    if (!texture->mBound) {
        LLAnimTexBindTexture(texture);
        texture->mBound = 1;
    }
}

void AnimTexUnbind(AnimTex_t *texture)
{
    if (texture->mBound == 1) {
        LLAnimTexUnbindTexture(texture);
        texture->mBound = 0;
    }
}

void AnimTexGetCoords(AnimTex_t *texture, unsigned int time, unsigned int frame,
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

AnimTex_t *AnimTexLoadResource(AnimTexFile_t *file, int load)
{
    void *data;
    AnimTex_t *texture;

    texture = AnimTexLoad((AnimTexDesc_t *)fn_801EF390(file->mData, file->mIndex, 1), &data, load);
    texture->mIndex = file->mIndex;
    if (load)
        fn_801F010C(file->mData, file->mIndex);
    return texture;
}

AnimTex_t *AnimTexLoad(AnimTexDesc_t *desc, void **pData, int load)
{
    AnimTexManager_t *manager = &_AnimTexLib_sManager;
    AnimTex_t *texture = manager->mTextures[manager->mCount];

    AnimTexInitTexture(texture, desc);
    if (load && !texture->mBound)
        LLAnimTexAllocTexCoords(texture);
    *pData = desc->mData.mpData;
    LLAnimTexCreateTexture(*pData, &texture->mImage);
    AnimTexBind(texture);
    if (load)
        LLAnimTexDeleteTexture(&texture->mImage);
    _AnimTexLib_sManager.mCount++;
    return texture;
}

void AnimTexFree(AnimTex_t *texture)
{
    int last = _AnimTexLib_sManager.mCount - 1;
    int i;

    for (i = 0; i < _AnimTexLib_sManager.mCount; i++) {
        if (_AnimTexLib_sManager.mTextures[i] == texture) {
            if (i < last) {
                _AnimTexLib_sManager.mTextures[i] = _AnimTexLib_sManager.mTextures[last];
                _AnimTexLib_sManager.mTextures[last] = texture;
            }
            break;
        }
    }
    LLAnimTexDeleteTexture(&texture->mImage);
    if (texture->mBound)
        AnimTexUnbind(texture);
    _AnimTexLib_sManager.mCount--;
}

AnimTex_t *AnimTexFind(const char *name)
{
    AnimTex_t *texture = 0;
    unsigned short i;

    for (i = 0; i < _AnimTexLib_sManager.mCount; i++) {
        if (strcmp(_AnimTexLib_sManager.mTextures[i]->mName, name) == 0) {
            texture = _AnimTexLib_sManager.mTextures[i];
            break;
        }
    }
    return texture;
}
