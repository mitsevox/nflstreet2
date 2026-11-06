/* Texture module of the EA engine: registers the RAW1 and MMAP texture file types, creates
   textures from them, relocates loaded texture files and decompresses their images, so the game
   can turn texture files from disc into images and palettes in memory. */

#include <string.h>
#include "game/fn_801D2B7C.h"
#include "engine/fn_801F7BD4.h"
#include "engine/GCmp.h"
#include "engine/tmlib.h"

typedef struct TexChunk_t {
    int mId;
    int mSize;
    unsigned char mData[1];
} TexChunk_t;

typedef struct TexRawDesc_t {
    int mUnknown00;
    int mUnknown04;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned short mFormat;
    unsigned short mTlutFormat;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    int mStream;
} TexRawDesc_t;

typedef struct TexMipLevel_t {
    unsigned char *mpData;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    int mUnknown14;
} TexMipLevel_t;

typedef struct TexMipHeader_t {
    unsigned int mNumLevels;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    TexMipLevel_t mLevels[1];
} TexMipHeader_t;

typedef struct TexFileType_t {
    int mId;
    int (*mpLoad)(void *pSrc, Texture_t *pTex);
    int (*mpInit)(Texture_t *pTex, void *pSrc, unsigned int flags);
} TexFileType_t;

extern TexChunk_t *fn_801CEEF4(void *pStream, int id, int endId, int flags);
extern char lbl_802B1BC4[];
extern char lbl_802B1BCC[];

extern unsigned char lbl_802F7A00[];
extern unsigned int lbl_802F7A10[];
extern unsigned char lbl_803EBC80[4];
extern TexFileType_t _Tex_RawFileType;
extern TexFileType_t _Tex_MipmapFileType;
extern unsigned char lbl_803EBEB8;
extern int lbl_803EBEC0;
extern TexFileType_t **lbl_803EBEC4;
extern int lbl_803EBEC8;
extern void **lbl_803EBECC;
extern int lbl_803ECFBC;
extern int lbl_803ECFC0;

void *TexDecompressTexture(TexFileImage_t *pImage, void *pDst);
int TexCreateEmpty(Texture_t *pTex, unsigned short width, unsigned short height, unsigned short format, unsigned short tlutFormat);
int TexUpdateFrame(void *pSrc, Texture_t *pTex, int flags);
void TexAddConversionType(TexFileType_t *pHandler);

static int _TexRawConvert(Texture_t *pTex, void *pSrc, unsigned int flags)
{
    TexRawDesc_t *pDesc = pSrc;
    TexChunk_t *pChunk;
    int err;

    pChunk = fn_801CEEF4(&pDesc->mStream, 0x494D4744, 0x454E4444, flags);
    err = 0;
    if (pChunk != 0) {
        memcpy(pTex->mpImage, pChunk->mData, pChunk->mSize - 8);
        if (lbl_802F7A10[pDesc->mFormat] != 0) {
            pChunk = fn_801CEEF4(&pDesc->mStream, 0x434C5554, 0x454E4444, flags);
            if (pChunk != 0) {
                memcpy(pTex->mpPalette, pChunk->mData, pChunk->mSize - 8);
            } else {
                err = 0x100004;
            }
        }
    } else {
        err = 0x100004;
    }
    return err;
}

static int _TexMipmapConvert(Texture_t *pTex, void *pSrc, unsigned int index)
{
    TexFileHeader_t *pFile = pSrc;
    int err = 0;

    if (!(pFile->mFlags & 1)) {
        TexMipmapRelocate(pFile);
    }
    if (index < pFile->mNumMaterials) {
        TexFileMaterial_t *pEntries = pFile->mpMaterials;
        TexFileMaterial_t *pEntry = &pEntries[index];
        TexFileImage_t *pImage = TexGetTextureByIndex(pFile, pEntry->mUnknown4);

        TexDecompressTexture(pImage, pTex->mpImage);
        if (pImage->mType == 4) {
            pTex->mFormat = pImage->mFormat;
            pTex->mWidth = pImage->mWidth;
            pTex->mHeight = pImage->mHeight;
        }
        if (lbl_802F7A10[pImage->mFormat] != 0) {
            if (pEntries[index].mUnknown0 != 0) {
                TexFilePalette_t *pPalette = TexGetPaletteByIndex(pFile, pEntry->mUnknown8);

                unsigned int numEntries = lbl_802F7A10[pPalette->mFormat];

                memcpy(pTex->mpPalette, pPalette->mpUnknown8, (numEntries * lbl_803EBC80[pPalette->mUnknown2]) >> 3);
            } else {
                err = 0x100004;
            }
        }
    } else {
        err = 0x100004;
    }
    return err;
}

static int _TexRawCreate(void *pSrc, Texture_t *pTex)
{
    TexRawDesc_t *pDesc = pSrc;
    int result = TexCreateEmpty(pTex, pDesc->mWidth, pDesc->mHeight, pDesc->mFormat, pDesc->mTlutFormat);

    pTex->mUnknown4 = pDesc->mUnknown10;
    pTex->mUnknown5 = pDesc->mUnknown11;
    pTex->mUnknown6 = pDesc->mUnknown12;
    pTex->mUnknown7 = pDesc->mUnknown13;
    pTex->mUnknown1C = 1;
    if (result == 0) {
        result = TexUpdateFrame(pDesc, pTex, 0);
    }
    return result;
}

static int _TexMipmapCreate(void *pSrc, Texture_t *pTex)
{
    TexFileHeader_t *pFile = pSrc;
    TexFileMaterial_t *pEntry;
    TexFileImage_t *pImage;
    unsigned short format;
    unsigned short tlutFormat;
    int result;

    if (!(pFile->mFlags & 1)) {
        TexMipmapRelocate(pFile);
    }
    pEntry = pFile->mpMaterials;
    pImage = TexGetTextureByIndex(pFile, pEntry->mUnknown4);
    format = pImage->mFormat;
    if (pEntry->mUnknown0 != 0) {
        TexFilePalette_t *pPalette = TexGetPaletteByIndex(pFile, pEntry->mUnknown8);

        tlutFormat = pPalette->mUnknown2;
        pPalette->mFormat = pImage->mFormat;
    } else {
        tlutFormat = 3;
        if (pImage->mType == 4) {
            format = 0xE;
        }
    }
    result = TexCreateEmpty(pTex, pImage->mWidth, pImage->mHeight, format, tlutFormat);
    pTex->mUnknown4 = pFile->mUnknown8;
    pTex->mUnknown5 = pFile->mUnknown9;
    pTex->mUnknown6 = pFile->mUnknownA;
    pTex->mUnknown7 = pFile->mUnknownB;
    pTex->mUnknown1C = 1;
    if (result == 0) {
        result = TexUpdateFrame(pFile, pTex, 0);
    }
    return result;
}

int TexInit(int heap, int count, int unknown)
{
    int err = 0;

    if (lbl_803EBEB8 == 0) {
        int capacity = count + 2;

        lbl_803EBEBC = heap;
        lbl_803ECFBC = capacity;
        lbl_803EBEC0 = 0;
        lbl_803EBEC4 = fn_801D2BB0(1, capacity * 4, 0, 0);
        lbl_803ECFC0 = capacity;
        lbl_803EBEC8 = 0;
        lbl_803EBECC = fn_801D2BB0(1, capacity * 4, 0, 0);
        lbl_803EBEB8 = 1;
        TexAddConversionType(&_Tex_RawFileType);
        TexAddConversionType(&_Tex_MipmapFileType);
    } else {
        err = 0x100001;
    }
    fn_801F7BD4(err);
    return err;
}

int TexShutdown(void)
{
    int err = 0;

    if (lbl_803EBEB8 != 0) {
        if (lbl_803EBEC4 != 0) {
            fn_801D2BD0(lbl_803EBEC4);
            lbl_803EBEC4 = 0;
        }
        if (lbl_803EBECC != 0) {
            fn_801D2BD0(lbl_803EBECC);
            lbl_803EBECC = 0;
        }
        lbl_803EBEB8 = 0;
    } else {
        err = 0x100002;
    }
    fn_801F7BD4(err);
    return err;
}

void TexAddConversionType(TexFileType_t *pHandler)
{
    lbl_803EBEC4[lbl_803EBEC0] = pHandler;
    lbl_803EBEC0++;
}

int TexCreate(void *pSrc, Texture_t *pTex)
{
    int result = 0;
    unsigned int i;

    for (i = 0; i < lbl_803EBEC0; i++) {
        TexFileType_t *pHandler = lbl_803EBEC4[i];

        if (*(int *)pSrc == pHandler->mId) {
            result = pHandler->mpLoad(pSrc, pTex);
        }
    }
    return result;
}

int TexCreateEmpty(Texture_t *pTex, unsigned short width, unsigned short height, unsigned short format, unsigned short tlutFormat)
{
    int err = 0;
    unsigned int size;

    pTex->mpImage = 0;
    pTex->mUnknown18 = 0;
    pTex->mWidth = width;
    pTex->mHeight = height;
    pTex->mpPalette = 0;
    if (tlutFormat != 3 && lbl_802F7A10[format] != 0) {
        size = (lbl_802F7A10[format] * lbl_803EBC80[tlutFormat]) >> 3;
        pTex->mpPalette = fn_801D2BB0(lbl_803EBEBC, size, 0, 0);
        if (pTex->mpPalette != 0) {
            fn_801D34D0(pTex->mpPalette, size, 0, 1);
        } else {
            err = fn_801F7C88();
        }
    }
    if (err == 0) {
        pTex->mFormat = format;
        size = (width * height * lbl_802F7A00[format]) >> 3;
        pTex->mpImage = fn_801D2BB0(lbl_803EBEBC, size, 0, 0);
        if (pTex->mpImage != 0) {
            fn_801D34D0(pTex->mpImage, size, 0, 1);
            pTex->mTlutFormat = tlutFormat;
        } else {
            fn_801D2BD0(pTex->mpPalette);
            pTex->mpPalette = 0;
            err = fn_801F7C88();
        }
    }
    pTex->mUnknown4 = 0;
    pTex->mUnknown5 = 1;
    pTex->mUnknown6 = 2;
    pTex->mUnknown7 = 3;
    pTex->mUnknown1C = 1;
    return err;
}

int TexUpdateFrame(void *pSrc, Texture_t *pTex, int flags)
{
    int result = 0x100003;
    unsigned int i;

    for (i = 0; i < lbl_803EBEC0; i++) {
        TexFileType_t *pHandler = lbl_803EBEC4[i];

        if (*(int *)pSrc == pHandler->mId) {
            result = pHandler->mpInit(pTex, pSrc, flags);
            pTex->mUnknown1C = 1;
        }
    }
    return result;
}

int TexDelete(Texture_t *pTex)
{
    int err = 0;

    if (pTex->mpImage != 0) {
        fn_801D2BD0(pTex->mpImage);
        pTex->mpImage = 0;
    }
    if (pTex->mpPalette != 0) {
        fn_801D2BD0(pTex->mpPalette);
        pTex->mpPalette = 0;
    }
    return err;
}

void TexMipmapRelocate(void *p)
{
    TexFileHeader_t *pFile = p;
    unsigned short i;
    TexFilePalette_t *pPalette;

    if (pFile->mFlags & 1) {
        return;
    }
    if (memcmp(pFile, lbl_802B1BC4, 4) == 0) {
        if (pFile->mVersion != 2) {
            pFile->mpMaterials = 0;
            pFile->mpTextures = 0;
            pFile->mpPalettes = 0;
            pFile->mNumMaterials = 0;
            pFile->mNumTextures = 0;
            pFile->mNumPalettes = 0;
            pFile->mFlags |= 1;
            return;
        }
        pFile->mpMaterials = (TexFileMaterial_t *)((int)pFile->mpMaterials + (int)pFile);
        pFile->mpTextures = (TexFileImage_t *)((int)pFile->mpTextures + (int)pFile);
        pFile->mpPalettes = (TexFilePalette_t *)((int)pFile->mpPalettes + (int)pFile);
        for (i = 0; i < pFile->mNumTextures; i++) {
            TexFileImage_t *pImage = TexGetTextureByIndex(pFile, i);

            if (pImage->mUnknown8 != 0) {
                pImage->mpUnknownC = pImage->mpUnknownC + (int)pFile;
            } else {
                pImage->mpUnknownC = 0;
            }
        }
        for (i = 0; i < pFile->mNumPalettes; i++) {
            pPalette = TexGetPaletteByIndex(pFile, i);

            pPalette->mpUnknown8 = pPalette->mpUnknown8 + (int)pFile;
        }
    } else if (memcmp(pFile, lbl_802B1BCC, 4) == 0) {
        pFile->mpMaterials = (TexFileMaterial_t *)((int)pFile->mpMaterials + (int)pFile);
        pFile->mpTextures = (TexFileImage_t *)((int)pFile->mpTextures + (int)pFile);
        pFile->mpPalettes = (TexFilePalette_t *)((int)pFile->mpPalettes + (int)pFile);
        for (i = 0; i < pFile->mNumTextures; i++) {
            TexFileImage_t *pImage = TexGetTextureByIndex(pFile, i);

            pImage->mpUnknownC = pImage->mpUnknownC + (int)pFile;
            if (pImage->mUnknown8 == 0) {
                TexMipHeader_t *pHeader = (TexMipHeader_t *)pImage->mpUnknownC;
                unsigned short j;

                for (j = 0; j < pHeader->mNumLevels; j++) {
                    pHeader->mLevels[j].mpData = pHeader->mLevels[j].mpData + (int)pFile;
                }
            }
        }
        for (i = 0; i < pFile->mNumPalettes; i++) {
            pPalette = TexGetPaletteByIndex(pFile, i);

            pPalette->mpUnknown8 = pPalette->mpUnknown8 + (int)pFile;
        }
    } else {
        return;
    }
    if (pFile->mVersion != 0) {
        pFile->mpNames = (char (*)[16])((int)pFile->mpNames + (int)pFile);
        if (pFile->mpInfo != 0) {
            pFile->mpInfo = (TexFileInfo_t *)((int)pFile->mpInfo + (int)pFile);
            pFile->mpInfo->mpData = pFile->mpInfo->mpData + (int)pFile;
        }
    }
    pFile->mFlags |= 1;
}

unsigned short TexGetNumMaterials(TexFileHeader_t *pFile)
{
    return pFile->mNumMaterials;
}

unsigned short TexGetNumPalettes(TexFileHeader_t *pFile)
{
    return pFile->mNumPalettes;
}

TexFileMaterial_t *TexGetMaterialByIndex(void *p, unsigned short index)
{
    TexFileHeader_t *pFile = p;

    return &pFile->mpMaterials[index];
}

const char *TexGetMaterialNameByIndex(TexFileHeader_t *pFile, unsigned short index)
{
    if (pFile->mVersion != 0) {
        return pFile->mpNames[index];
    }
    return 0;
}

TexFileImage_t *TexGetTextureByIndex(void *p, unsigned short index)
{
    TexFileHeader_t *pFile = p;
    TexFileImage_t *pImage;

    if (pFile->mVersion <= 1 && memcmp(pFile, lbl_802B1BCC, 4) != 0) {
        unsigned int i;

        pImage = pFile->mpTextures;
        for (i = 0; i < index; i++) {
            unsigned char *pNext = pImage->mpUnknownC;
            int pad;

            pNext += pImage->mUnknown8;
            pad = (int)pNext & 3;
            if (pad != 0) {
                pNext += 4 - pad;
            }
            pImage = (TexFileImage_t *)pNext;
        }
    } else {
        pImage = &pFile->mpTextures[index];
    }
    return pImage;
}

TexFilePalette_t *TexGetPaletteByIndex(void *p, unsigned short index)
{
    TexFileHeader_t *pFile = p;
    TexFilePalette_t *pPalette = 0;

    if (pFile->mVersion <= 1 && memcmp(pFile, lbl_802B1BCC, 4) != 0) {
        unsigned int i;
        unsigned char *pNext = (unsigned char *)pFile->mpPalettes;

        for (i = 0; i < index; i++) {
            int pad;

            pPalette = (TexFilePalette_t *)pNext;
            pNext = pPalette->mpUnknown8;
            pNext += pPalette->mUnknown4;
            pad = (int)pNext & 3;
            if (pad != 0) {
                pNext += 4 - pad;
            }
        }
        pPalette = (TexFilePalette_t *)pNext;
    } else {
        pPalette = &pFile->mpPalettes[index];
    }
    return pPalette;
}

void *TexDecompressTexture(TexFileImage_t *pImage, void *pDst)
{
    int size;

    if (pImage->mType != 4) {
        size = (pImage->mWidth * pImage->mHeight * lbl_802F7A00[pImage->mFormat]) >> 3;
    } else {
        pImage->mFormat = 0xE;
        size = pImage->mWidth * pImage->mHeight * 2;
    }
    if (pDst == 0) {
        pDst = fn_801D2BB0(lbl_803EBEBC, size, 0, 0);
    }
    if (pImage->mType == 0) {
        memcpy(pDst, pImage->mpUnknownC, size);
    } else {
        GCmpBuffer_t src;
        GCmpBuffer_t dst;

        src.mpData = pImage->mpUnknownC;
        src.mSize = pImage->mUnknown8;
        src.mWidth = pImage->mWidth;
        src.mHeight = pImage->mHeight;
        src.mBits = 16;
        dst.mpData = pDst;
        GCmpDecompress(pImage->mType, &src, &dst);
        if (pImage->mType != 4) {
            int bpp = lbl_802F7A00[pImage->mFormat];

            dst.mSize = pImage->mWidth * pImage->mHeight * bpp / 8;
        } else {
            dst.mSize = pImage->mUnknown8 = pImage->mWidth * pImage->mHeight * 2;
        }
    }
    return pDst;
}

TexFileType_t _Tex_RawFileType = {0x52415731, _TexRawCreate, _TexRawConvert};
TexFileType_t _Tex_MipmapFileType = {0x4D4D4150, _TexMipmapCreate, _TexMipmapConvert};
