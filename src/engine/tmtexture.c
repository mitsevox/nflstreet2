#include <dolphin/gx/GXGet.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/os/OSCache.h>
#include "engine/tmlib.h"

extern u32 fn_8024FDA0(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
extern void fn_8024FFC4(GXTexObj *obj, void *image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
extern void fn_80250210(GXTexObj *obj, void *image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name);
extern void fn_80250258(GXTexObj *obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp, GXBool do_edge_lod, GXAnisotropy max_aniso);
extern void fn_802503BC(GXTexObj *obj, GXTexWrapMode s, GXTexWrapMode t);
extern GXTexFmt fn_8025040C(const GXTexObj *pObj);
extern void fn_802505FC(GXTlutObj *tlut_obj, void *lut, GXTlutFmt fmt, u16 n_entries);

extern unsigned int lbl_803E9780[64];

void fn_80212234(Texture_80212234 *pTexture, int minFilter, int magFilter, float lodBias, unsigned char bBiasClamp, unsigned char bEdgeLod, int maxAniso)
{
    float maxLod;

    if (pTexture != 0) {
        maxLod = pTexture->mNumMips - 1;
        if ((unsigned int)(fn_8025040C(&pTexture->mObj) - GX_TF_C4) <= GX_TF_C8 - GX_TF_C4) {
            if (minFilter == GX_NEAR_MIP_LIN) {
                minFilter = GX_NEAR_MIP_NEAR;
            }
            if (minFilter == GX_LIN_MIP_LIN) {
                minFilter = GX_LIN_MIP_NEAR;
            }
            maxAniso = GX_ANISO_1;
        }
        fn_80250258(&pTexture->mObj, minFilter, magFilter, 0.0f, maxLod, lodBias, bBiasClamp, bEdgeLod, maxAniso);
    }
}

void fn_80212310(Texture_80212234 *pTexture, TexFilterDesc_80212310 *pDesc)
{
    fn_80212234(pTexture, pDesc->mMinFilter, pDesc->mMagFilter, pDesc->mLodBias, pDesc->mbBiasClamp, pDesc->mbEdgeLod, pDesc->mMaxAniso);
}

void fn_8021234C(Texture_80212234 *pTexture, int wrapS, int wrapT)
{
    if (pTexture != 0) {
        fn_802503BC(&pTexture->mObj, wrapS, wrapT);
    }
}

void fn_80212374(Texture_80212234 *pTexture, TexWrapDesc_80212374 *pDesc)
{
    fn_8021234C(pTexture, pDesc->mWrapS, pDesc->mWrapT);
}

void fn_8021239C(Texture_80212234 *pTexture, void *pData, int width, int height, int format, int numMips, void *pBuffer, Clut_80212534 *pClut)
{
    fn_8021242C(pTexture, pData, width, height, format, numMips, pBuffer, pClut);
    fn_80212234(pTexture, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, 0, 0, 0);
    fn_8021234C(pTexture, (width & (width - 1)) == 0, (height & (height - 1)) == 0);
    pTexture->mpData = pBuffer;
    pTexture->mWidth = width;
    pTexture->mHeight = height;
}

void fn_8021242C(Texture_80212234 *pTexture, void *pData, int width, int height, int format, int numMips, void *pBuffer, Clut_80212534 *pClut)
{
    GXBool bMipmap;

    bMipmap = numMips > 1;
    pTexture->mWidth = width;
    pTexture->mpData = pBuffer;
    pTexture->mNumMips = numMips;
    pTexture->mHeight = height;
    DCStoreRange(pData, fn_8024FDA0(width, height, format, bMipmap, numMips));
    if ((unsigned int)(format - GX_TF_C4) <= GX_TF_C8 - GX_TF_C4) {
        fn_80250210(&pTexture->mObj, pData, width, height, format, GX_REPEAT, GX_REPEAT, bMipmap, 0);
    } else {
        fn_8024FFC4(&pTexture->mObj, pData, width, height, format, GX_REPEAT, GX_REPEAT, bMipmap);
    }
    fn_80212234(pTexture, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, 0, 0, 0);
}

void fn_80212530(Texture_80212234 *pTexture)
{
}

void fn_80212534(Clut_80212534 *pClut, void *pData, int format, int numEntries, unsigned int size)
{
    int dim;

    DCStoreRange(pData, numEntries * 4);
    if (format <= GX_TL_RGB5A3) {
        pClut->mType = 0;
        fn_802505FC(&pClut->u.maTlut[0], pData, format, numEntries);
    } else if (format == GX_TF_RGBA8) {
        pClut->mType = 1;
        dim = numEntries == 16 ? 4 : 16;
        fn_8024FFC4(&pClut->u.mObj, pData, dim, dim, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        fn_80250258(&pClut->u.mObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else {
        pClut->mType = 2;
        fn_802505FC(&pClut->u.maTlut[0], pData, GX_TL_IA8, numEntries);
        fn_802505FC(&pClut->u.maTlut[1], (unsigned char *)pData + size / 2, GX_TL_IA8, numEntries);
    }
    pClut->mSize = size;
}

void fn_80212654(Clut_80212534 *pClut)
{
}

void fn_80212658(Texture_80212234 *pTexture)
{
    int i;

    for (i = 0; i < 64; i++) {
        lbl_803E9780[i] = 0xFFFFFFFF;
    }
    fn_8021239C(pTexture, lbl_803E9780, 8, 8, GX_TF_I8, 0, 0, 0);
}

void fn_802126BC(Texture_80212234 *pTexture, const char *pName)
{
}
