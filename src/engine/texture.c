#include <string.h>
#include "game/fn_801D2B7C.h"
#include "engine/fn_801F7BD4.h"
#include "engine/cu_8027EFAC.h"
#include "engine/tmlib.h"

typedef struct TexChunk_8020DB34 {
    int mId;
    int mSize;
    unsigned char mData[1];
} TexChunk_8020DB34;

typedef struct TexDesc_8020DB34 {
    int mUnknown00;
    int mUnknown04;
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned short mFormat;
    unsigned short mTlutFormat;
    unsigned char mWrapS;
    unsigned char mWrapT;
    unsigned char mMinFilter;
    unsigned char mMagFilter;
    int mStream;
} TexDesc_8020DB34;

typedef struct TexMipLevel_8020E2B0 {
    unsigned char *mpData;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    int mUnknown14;
} TexMipLevel_8020E2B0;

typedef struct TexMipHeader_8020E2B0 {
    unsigned int mNumLevels;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    TexMipLevel_8020E2B0 mLevels[1];
} TexMipHeader_8020E2B0;

typedef struct TexHandler_8020DFBC {
    int mId;
    int (*mpLoad)(void *pSrc, Texture_8020DB34 *pTex);
    int (*mpInit)(Texture_8020DB34 *pTex, void *pSrc, int flags);
} TexHandler_8020DFBC;

extern TexChunk_8020DB34 *fn_801CEEF4(void *pStream, int id, int endId, int flags);
extern char lbl_802B1BC4[];
extern char lbl_802B1BCC[];

extern unsigned char lbl_802F7A00[];
extern unsigned int lbl_802F7A10[];
extern unsigned char lbl_803EBC80[4];
extern TexHandler_8020DFBC lbl_802F9BF0;
extern TexHandler_8020DFBC lbl_802F9BFC;
extern unsigned char lbl_803EBEB8;
extern int lbl_803EBEC0;
extern TexHandler_8020DFBC **lbl_803EBEC4;
extern int lbl_803EBEC8;
extern void **lbl_803EBECC;
extern int lbl_803ECFBC;
extern int lbl_803ECFC0;

void *fn_8020E6A0(Object_8020E560 *pImage, void *pDst);
int fn_8020E064(Texture_8020DB34 *pTex, unsigned short width, unsigned short height, unsigned short format, unsigned short tlutFormat);
int fn_8020E1B8(void *pSrc, Texture_8020DB34 *pTex, int flags);
void fn_8020DFBC(TexHandler_8020DFBC *pHandler);

static int fn_8020DB34(Texture_8020DB34 *pTex, TexDesc_8020DB34 *pDesc, int flags)
{
    TexChunk_8020DB34 *pChunk;
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

static int fn_8020DC10(Texture_8020DB34 *pTex, TexHeader_8020E2B0 *pFile, unsigned int index)
{
    int err = 0;

    if (!(pFile->mFlags & 1)) {
        fn_8020E2B0(pFile);
    }
    if (index < pFile->mNumMaterials) {
        Object_8020E52C *pEntries = pFile->mpMaterials;
        Object_8020E52C *pEntry = &pEntries[index];
        Object_8020E560 *pImage = fn_8020E560(pFile, pEntry->mUnknown4);

        fn_8020E6A0(pImage, pTex->mpImage);
        if (pImage->mType == 4) {
            pTex->mFormat = pImage->mFormat;
            pTex->mWidth = pImage->mWidth;
            pTex->mHeight = pImage->mHeight;
        }
        if (lbl_802F7A10[pImage->mFormat] != 0) {
            if (pEntries[index].mUnknown0 != 0) {
                Object_8020E5F8 *pPalette = fn_8020E5F8(pFile, pEntry->mUnknown8);

                unsigned int bpp = lbl_802F7A10[pPalette->mFormat];

                memcpy(pTex->mpPalette, pPalette->mpUnknown8, (bpp * lbl_803EBC80[pPalette->mUnknown2]) >> 3);
            } else {
                err = 0x100004;
            }
        }
    } else {
        err = 0x100004;
    }
    return err;
}

static int fn_8020DD24(TexDesc_8020DB34 *pDesc, Texture_8020DB34 *pTex)
{
    int result = fn_8020E064(pTex, pDesc->mWidth, pDesc->mHeight, pDesc->mFormat, pDesc->mTlutFormat);

    pTex->mWrapS = pDesc->mWrapS;
    pTex->mWrapT = pDesc->mWrapT;
    pTex->mMinFilter = pDesc->mMinFilter;
    pTex->mMagFilter = pDesc->mMagFilter;
    pTex->mbDirty = 1;
    if (result == 0) {
        result = fn_8020E1B8(pDesc, pTex, 0);
    }
    return result;
}

static int fn_8020DDA8(TexHeader_8020E2B0 *pFile, Texture_8020DB34 *pTex)
{
    Object_8020E52C *pEntry;
    Object_8020E560 *pImage;
    unsigned short format;
    unsigned short tlutFormat;
    int result;

    if (!(pFile->mFlags & 1)) {
        fn_8020E2B0(pFile);
    }
    pEntry = pFile->mpMaterials;
    pImage = fn_8020E560(pFile, pEntry->mUnknown4);
    format = pImage->mFormat;
    if (pEntry->mUnknown0 != 0) {
        Object_8020E5F8 *pPalette = fn_8020E5F8(pFile, pEntry->mUnknown8);

        tlutFormat = pPalette->mUnknown2;
        pPalette->mFormat = pImage->mFormat;
    } else {
        tlutFormat = 3;
        if (pImage->mType == 4) {
            format = 0xE;
        }
    }
    result = fn_8020E064(pTex, pImage->mWidth, pImage->mHeight, format, tlutFormat);
    pTex->mWrapS = pFile->mWrapS;
    pTex->mWrapT = pFile->mWrapT;
    pTex->mMinFilter = pFile->mMinFilter;
    pTex->mMagFilter = pFile->mMagFilter;
    pTex->mbDirty = 1;
    if (result == 0) {
        result = fn_8020E1B8(pFile, pTex, 0);
    }
    return result;
}

int fn_8020DE8C(int heap, int count)
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
        fn_8020DFBC(&lbl_802F9BF0);
        fn_8020DFBC(&lbl_802F9BFC);
    } else {
        err = 0x100001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_8020DF44(void)
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

void fn_8020DFBC(TexHandler_8020DFBC *pHandler)
{
    lbl_803EBEC4[lbl_803EBEC0] = pHandler;
    lbl_803EBEC0++;
}

int fn_8020DFD8(void *pSrc, Texture_8020DB34 *pTex)
{
    int result = 0;
    unsigned int i;

    for (i = 0; i < lbl_803EBEC0; i++) {
        TexHandler_8020DFBC *pHandler = lbl_803EBEC4[i];

        if (*(int *)pSrc == pHandler->mId) {
            result = pHandler->mpLoad(pSrc, pTex);
        }
    }
    return result;
}

int fn_8020E064(Texture_8020DB34 *pTex, unsigned short width, unsigned short height, unsigned short format, unsigned short tlutFormat)
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
    pTex->mWrapS = 0;
    pTex->mWrapT = 1;
    pTex->mMinFilter = 2;
    pTex->mMagFilter = 3;
    pTex->mbDirty = 1;
    return err;
}

int fn_8020E1B8(void *pSrc, Texture_8020DB34 *pTex, int flags)
{
    int result = 0x100003;
    unsigned int i;

    for (i = 0; i < lbl_803EBEC0; i++) {
        TexHandler_8020DFBC *pHandler = lbl_803EBEC4[i];

        if (*(int *)pSrc == pHandler->mId) {
            result = pHandler->mpInit(pTex, pSrc, flags);
            pTex->mbDirty = 1;
        }
    }
    return result;
}

int fn_8020E258(Texture_8020DB34 *pTex)
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

void fn_8020E2B0(void *p)
{
    TexHeader_8020E2B0 *pFile = p;
    unsigned short i;

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
        pFile->mpMaterials = (Object_8020E52C *)((int)pFile->mpMaterials + (int)pFile);
        pFile->mpTextures = (Object_8020E560 *)((int)pFile->mpTextures + (int)pFile);
        pFile->mpPalettes = (Object_8020E5F8 *)((int)pFile->mpPalettes + (int)pFile);
        for (i = 0; i < pFile->mNumTextures; i++) {
            Object_8020E560 *pImage = fn_8020E560(pFile, i);

            if (pImage->mUnknown8 != 0) {
                pImage->mpUnknownC = pImage->mpUnknownC + (int)pFile;
            } else {
                pImage->mpUnknownC = 0;
            }
        }
        for (i = 0; i < pFile->mNumPalettes; i++) {
            Object_8020E5F8 *pPalette = fn_8020E5F8(pFile, i);

            pPalette->mpUnknown8 = pPalette->mpUnknown8 + (int)pFile;
        }
    } else if (memcmp(pFile, lbl_802B1BCC, 4) == 0) {
        pFile->mpMaterials = (Object_8020E52C *)((int)pFile->mpMaterials + (int)pFile);
        pFile->mpTextures = (Object_8020E560 *)((int)pFile->mpTextures + (int)pFile);
        pFile->mpPalettes = (Object_8020E5F8 *)((int)pFile->mpPalettes + (int)pFile);
        for (i = 0; i < pFile->mNumTextures; i++) {
            Object_8020E560 *pImage = fn_8020E560(pFile, i);

            pImage->mpUnknownC = pImage->mpUnknownC + (int)pFile;
            if (pImage->mUnknown8 == 0) {
                TexMipHeader_8020E2B0 *pHeader = (TexMipHeader_8020E2B0 *)pImage->mpUnknownC;
                unsigned short j;

                for (j = 0; j < pHeader->mNumLevels; j++) {
                    pHeader->mLevels[j].mpData = pHeader->mLevels[j].mpData + (int)pFile;
                }
            }
        }
        for (i = 0; i < pFile->mNumPalettes; i++) {
            Object_8020E5F8 *pPalette = fn_8020E5F8(pFile, i);

            pPalette->mpUnknown8 = pPalette->mpUnknown8 + (int)pFile;
        }
    } else {
        return;
    }
    if (pFile->mVersion != 0) {
        pFile->mpNames = (char (*)[16])((int)pFile->mpNames + (int)pFile);
        if (pFile->mpInfo != 0) {
            pFile->mpInfo = (TexInfo_8020E2B0 *)((int)pFile->mpInfo + (int)pFile);
            pFile->mpInfo->mpData = pFile->mpInfo->mpData + (int)pFile;
        }
    }
    pFile->mFlags |= 1;
}

unsigned short fn_8020E51C(TexHeader_8020E2B0 *pFile)
{
    return pFile->mNumMaterials;
}

unsigned short fn_8020E524(TexHeader_8020E2B0 *pFile)
{
    return pFile->mNumPalettes;
}

Object_8020E52C *fn_8020E52C(void *p, unsigned short index)
{
    TexHeader_8020E2B0 *pFile = p;

    return &pFile->mpMaterials[index];
}

const char *fn_8020E53C(TexHeader_8020E2B0 *pFile, unsigned short index)
{
    if (pFile->mVersion != 0) {
        return pFile->mpNames[index];
    }
    return 0;
}

Object_8020E560 *fn_8020E560(void *p, unsigned short index)
{
    TexHeader_8020E2B0 *pFile = p;
    Object_8020E560 *pImage;

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
            pImage = (Object_8020E560 *)pNext;
        }
    } else {
        pImage = &pFile->mpTextures[index];
    }
    return pImage;
}

Object_8020E5F8 *fn_8020E5F8(void *p, unsigned short index)
{
    TexHeader_8020E2B0 *pFile = p;
    Object_8020E5F8 *pPalette = 0;

    if (pFile->mVersion <= 1 && memcmp(pFile, lbl_802B1BCC, 4) != 0) {
        unsigned int i;
        unsigned char *pNext = (unsigned char *)pFile->mpPalettes;

        for (i = 0; i < index; i++) {
            int pad;

            pPalette = (Object_8020E5F8 *)pNext;
            pNext = pPalette->mpUnknown8;
            pNext += pPalette->mUnknown4;
            pad = (int)pNext & 3;
            if (pad != 0) {
                pNext += 4 - pad;
            }
        }
        pPalette = (Object_8020E5F8 *)pNext;
    } else {
        pPalette = &pFile->mpPalettes[index];
    }
    return pPalette;
}

void *fn_8020E6A0(Object_8020E560 *pImage, void *pDst)
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
        Buffer_8027F9AC src;
        Buffer_8027F9AC dst;

        src.mpData = pImage->mpUnknownC;
        src.mSize = pImage->mUnknown8;
        src.mWidth = pImage->mWidth;
        src.mHeight = pImage->mHeight;
        src.mBits = 16;
        dst.mpData = pDst;
        fn_8027F3A4(pImage->mType, &src, &dst);
        if (pImage->mType != 4) {
            int bpp = lbl_802F7A00[pImage->mFormat];

            dst.mSize = pImage->mWidth * pImage->mHeight * bpp / 8;
        } else {
            dst.mSize = pImage->mUnknown8 = pImage->mWidth * pImage->mHeight * 2;
        }
    }
    return pDst;
}
