/* TM renderer textures: initialises GX texture and palette (CLUT) objects, their filter and wrap
   modes, and the plain white null texture. */

#include <dolphin/gx/GXGet.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/os/OSCache.h>
#include "engine/tmlib.h"

extern unsigned int lbl_803E9780[64];

void TMTextureSetFilter(TMTexture_t *pTexture, int minFilter, int magFilter, float lodBias, unsigned char bBiasClamp, unsigned char bEdgeLod, int maxAniso)
{
    float maxLod;

    if (pTexture != 0) {
        maxLod = pTexture->mNumMips - 1;
        if ((unsigned int)(GXGetTexObjFmt(&pTexture->mObj) - GX_TF_C4) <= GX_TF_C8 - GX_TF_C4) {
            if (minFilter == GX_NEAR_MIP_LIN) {
                minFilter = GX_NEAR_MIP_NEAR;
            }
            if (minFilter == GX_LIN_MIP_LIN) {
                minFilter = GX_LIN_MIP_NEAR;
            }
            maxAniso = GX_ANISO_1;
        }
        GXInitTexObjLOD(&pTexture->mObj, minFilter, magFilter, 0.0f, maxLod, lodBias, bBiasClamp, bEdgeLod, maxAniso);
    }
}

void TMTextureSetFilterParm(TMTexture_t *pTexture, TMTexFilterDesc_t *pDesc)
{
    TMTextureSetFilter(pTexture, pDesc->mMinFilter, pDesc->mMagFilter, pDesc->mLodBias, pDesc->mbBiasClamp, pDesc->mbEdgeLod, pDesc->mMaxAniso);
}

void TMTextureSetWrap(TMTexture_t *pTexture, int wrapS, int wrapT)
{
    if (pTexture != 0) {
        GXInitTexObjWrapMode(&pTexture->mObj, wrapS, wrapT);
    }
}

void TMTextureSetWrapParm(TMTexture_t *pTexture, TMTexWrapDesc_t *pDesc)
{
    TMTextureSetWrap(pTexture, pDesc->mWrapS, pDesc->mWrapT);
}

void TMTextureTexNew(TMTexture_t *pTexture, void *pData, int width, int height, int format, int numMips, unsigned int size, TMClut_t *pClut)
{
    TMTextureSetTexData(pTexture, pData, width, height, format, numMips, size, pClut);
    TMTextureSetFilter(pTexture, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, 0, 0, 0);
    TMTextureSetWrap(pTexture, (width & (width - 1)) == 0, (height & (height - 1)) == 0);
    pTexture->mSize = size;
    pTexture->mWidth = width;
    pTexture->mHeight = height;
}

void TMTextureSetTexData(TMTexture_t *pTexture, void *pData, int width, int height, int format, int numMips, unsigned int size, TMClut_t *pClut)
{
    GXBool bMipmap;

    bMipmap = numMips > 1;
    pTexture->mWidth = width;
    pTexture->mSize = size;
    pTexture->mNumMips = numMips;
    pTexture->mHeight = height;
    DCStoreRange(pData, GXGetTexBufferSize(width, height, format, bMipmap, numMips));
    if ((unsigned int)(format - GX_TF_C4) <= GX_TF_C8 - GX_TF_C4) {
        GXInitTexObjCI(&pTexture->mObj, pData, width, height, format, GX_REPEAT, GX_REPEAT, bMipmap, 0);
    } else {
        GXInitTexObj(&pTexture->mObj, pData, width, height, format, GX_REPEAT, GX_REPEAT, bMipmap);
    }
    TMTextureSetFilter(pTexture, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, 0, 0, 0);
}

void TMTextureTexDelete(TMTexture_t *pTexture)
{
}

void TMTextureClutNew(TMClut_t *pClut, void *pData, int format, int numEntries, unsigned int size)
{
    int dim;

    DCStoreRange(pData, numEntries * 4);
    if (format <= GX_TL_RGB5A3) {
        pClut->mType = 0;
        GXInitTlutObj(&pClut->u.maTlut[0], pData, format, numEntries);
    } else if (format == GX_TF_RGBA8) {
        pClut->mType = 1;
        dim = numEntries == 16 ? 4 : 16;
        GXInitTexObj(&pClut->u.mObj, pData, dim, dim, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&pClut->u.mObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else {
        pClut->mType = 2;
        GXInitTlutObj(&pClut->u.maTlut[0], pData, GX_TL_IA8, numEntries);
        GXInitTlutObj(&pClut->u.maTlut[1], (unsigned char *)pData + size / 2, GX_TL_IA8, numEntries);
    }
    pClut->mSize = size;
}

void TMTextureClutDelete(TMClut_t *pClut)
{
}

void TMTextureMakeNullTexture(TMTexture_t *pTexture)
{
    int i;

    for (i = 0; i < 64; i++) {
        lbl_803E9780[i] = 0xFFFFFFFF;
    }
    TMTextureTexNew(pTexture, lbl_803E9780, 8, 8, GX_TF_I8, 0, 0, 0);
}

void TMTextureSetTexName(TMTexture_t *pTexture, const char *pName)
{
}
