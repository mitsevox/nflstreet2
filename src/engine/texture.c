#include "game/fn_801D2B7C.h"
#include "engine/fn_801F7BD4.h"

typedef struct Texture_8020DB34 {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned char mWrapS;
    unsigned char mWrapT;
    unsigned char mMinFilter;
    unsigned char mMagFilter;
    int mFormat;
    void *mpImage;
    int mUnknown10;
    void *mpPalette;
    int mUnknown18;
    unsigned char mbDirty;
} Texture_8020DB34;

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

typedef struct TexImage_8020DC10 {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned short mFormat;
    unsigned short mType;
    int mSize;
    unsigned char *mpData;
} TexImage_8020DC10;

typedef struct TexPalette_8020DC10 {
    unsigned short mFormat;
    unsigned short mTlutFormat;
    int mSize;
    unsigned char *mpData;
} TexPalette_8020DC10;

typedef struct TexExtra_8020E53C {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
} TexExtra_8020E53C;

typedef struct TexInfo_8020E2B0 {
    int mUnknown00;
    unsigned char *mpData;
} TexInfo_8020E2B0;

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

typedef struct TexEntry_8020DC10 {
    unsigned short mbHasPalette;
    unsigned short mUnknown02;
    unsigned short mImage;
    unsigned short mUnknown06;
    unsigned short mPalette;
    unsigned short mUnknown0A;
} TexEntry_8020DC10;

typedef struct TexFile_8020DC10 {
    int mMagic;
    unsigned short mVersion;
    unsigned short mFlags;
    unsigned char mWrapS;
    unsigned char mWrapT;
    unsigned char mMinFilter;
    unsigned char mMagFilter;
    unsigned short mNumEntries;
    unsigned short mNumImages;
    unsigned short mNumPalettes;
    unsigned short mUnknown12;
    TexEntry_8020DC10 *mpEntries;
    TexImage_8020DC10 *mpImages;
    TexPalette_8020DC10 *mpPalettes;
    TexExtra_8020E53C *mpExtras;
    TexInfo_8020E2B0 *mpInfo;
} TexFile_8020DC10;

typedef struct TexHandler_8020DFBC {
    int mId;
    int (*mpLoad)(void *pDesc, void *pArg);
    int (*mpInit)(Texture_8020DB34 *pTex, void *pSrc, int flags);
} TexHandler_8020DFBC;

typedef struct TexDecodeBuf_8020E6A0 {
    void *mpData;
    int mSize;
    int mUnknown08;
    unsigned short mWidth;
    unsigned short mHeight;
    int mUnknown10;
    short mUnknown14;
    unsigned short mBits;
    int mUnknown18;
    int mUnknown1C;
} TexDecodeBuf_8020E6A0;

extern void fn_8027F3A4(int type, TexDecodeBuf_8020E6A0 *pSrc, TexDecodeBuf_8020E6A0 *pDst);
extern TexChunk_8020DB34 *fn_801CEEF4(void *pStream, int id, int endId, int flags);
extern int fn_801C1FEC(const void *pA, const void *pB, int size);
extern char lbl_802B1BC4[];
extern char lbl_802B1BCC[];
extern void fn_801D34D0(void *p, unsigned int size, int c, int d);

extern unsigned char lbl_802F7A00[];
extern unsigned int lbl_802F7A10[];
extern unsigned char lbl_803EBC80[4];
extern TexHandler_8020DFBC lbl_802F9BF0;
extern TexHandler_8020DFBC lbl_802F9BFC;
extern unsigned char lbl_803EBEB8;
extern int lbl_803EBEBC;
extern int lbl_803EBEC0;
extern TexHandler_8020DFBC **lbl_803EBEC4;
extern int lbl_803EBEC8;
extern void **lbl_803EBECC;
extern int lbl_803ECFBC;
extern int lbl_803ECFC0;

void fn_8020E2B0(TexFile_8020DC10 *pFile);
TexImage_8020DC10 *fn_8020E560(TexFile_8020DC10 *pFile, unsigned short index);
TexPalette_8020DC10 *fn_8020E5F8(TexFile_8020DC10 *pFile, unsigned short index);
void *fn_8020E6A0(TexImage_8020DC10 *pImage, void *pDst);
int fn_8020E064(Texture_8020DB34 *pTex, unsigned short width, unsigned short height, unsigned short format, unsigned short tlutFormat);
int fn_8020E1B8(void *pSrc, Texture_8020DB34 *pTex, int flags);
void fn_8020DFBC(TexHandler_8020DFBC *pHandler);

int fn_8020DB34(Texture_8020DB34 *pTex, TexDesc_8020DB34 *pDesc, int flags)
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

int fn_8020DC10(Texture_8020DB34 *pTex, TexFile_8020DC10 *pFile, unsigned int index)
{
    int err = 0;

    if (!(pFile->mFlags & 1)) {
        fn_8020E2B0(pFile);
    }
    if (index < pFile->mNumEntries) {
        TexEntry_8020DC10 *pEntries = pFile->mpEntries;
        TexEntry_8020DC10 *pEntry = &pEntries[index];
        TexImage_8020DC10 *pImage = fn_8020E560(pFile, pEntry->mImage);

        fn_8020E6A0(pImage, pTex->mpImage);
        if (pImage->mType == 4) {
            pTex->mFormat = pImage->mFormat;
            pTex->mWidth = pImage->mWidth;
            pTex->mHeight = pImage->mHeight;
        }
        if (lbl_802F7A10[pImage->mFormat] != 0) {
            if (pEntries[index].mbHasPalette != 0) {
                TexPalette_8020DC10 *pPalette = fn_8020E5F8(pFile, pEntry->mPalette);

                unsigned int bpp = lbl_802F7A10[pPalette->mFormat];

                memcpy(pTex->mpPalette, pPalette->mpData, (bpp * lbl_803EBC80[pPalette->mTlutFormat]) >> 3);
            } else {
                err = 0x100004;
            }
        }
    } else {
        err = 0x100004;
    }
    return err;
}

int fn_8020DD24(TexDesc_8020DB34 *pDesc, Texture_8020DB34 *pTex)
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

int fn_8020DDA8(TexFile_8020DC10 *pFile, Texture_8020DB34 *pTex)
{
    TexEntry_8020DC10 *pEntry;
    TexImage_8020DC10 *pImage;
    unsigned short format;
    unsigned short tlutFormat;
    int result;

    if (!(pFile->mFlags & 1)) {
        fn_8020E2B0(pFile);
    }
    pEntry = pFile->mpEntries;
    pImage = fn_8020E560(pFile, pEntry->mImage);
    format = pImage->mFormat;
    if (pEntry->mbHasPalette != 0) {
        TexPalette_8020DC10 *pPalette = fn_8020E5F8(pFile, pEntry->mPalette);

        tlutFormat = pPalette->mTlutFormat;
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

int fn_8020DFD8(TexDesc_8020DB34 *pDesc, void *pArg)
{
    int result = 0;
    unsigned int i;

    for (i = 0; i < lbl_803EBEC0; i++) {
        TexHandler_8020DFBC *pHandler = lbl_803EBEC4[i];

        if (pDesc->mUnknown00 == pHandler->mId) {
            result = pHandler->mpLoad(pDesc, pArg);
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
            pTex->mUnknown10 = tlutFormat;
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

void fn_8020E2B0(TexFile_8020DC10 *pFile)
{
    unsigned short i;

    if (pFile->mFlags & 1) {
        return;
    }
    if (fn_801C1FEC(pFile, lbl_802B1BC4, 4) == 0) {
        if (pFile->mVersion != 2) {
            pFile->mpEntries = 0;
            pFile->mpImages = 0;
            pFile->mpPalettes = 0;
            pFile->mNumEntries = 0;
            pFile->mNumImages = 0;
            pFile->mNumPalettes = 0;
            pFile->mFlags |= 1;
            return;
        }
        pFile->mpEntries = (TexEntry_8020DC10 *)((int)pFile->mpEntries + (int)pFile);
        pFile->mpImages = (TexImage_8020DC10 *)((int)pFile->mpImages + (int)pFile);
        pFile->mpPalettes = (TexPalette_8020DC10 *)((int)pFile->mpPalettes + (int)pFile);
        for (i = 0; i < pFile->mNumImages; i++) {
            TexImage_8020DC10 *pImage = fn_8020E560(pFile, i);

            if (pImage->mSize != 0) {
                pImage->mpData = pImage->mpData + (int)pFile;
            } else {
                pImage->mpData = 0;
            }
        }
        for (i = 0; i < pFile->mNumPalettes; i++) {
            TexPalette_8020DC10 *pPalette = fn_8020E5F8(pFile, i);

            pPalette->mpData = pPalette->mpData + (int)pFile;
        }
    } else if (fn_801C1FEC(pFile, lbl_802B1BCC, 4) == 0) {
        pFile->mpEntries = (TexEntry_8020DC10 *)((int)pFile->mpEntries + (int)pFile);
        pFile->mpImages = (TexImage_8020DC10 *)((int)pFile->mpImages + (int)pFile);
        pFile->mpPalettes = (TexPalette_8020DC10 *)((int)pFile->mpPalettes + (int)pFile);
        for (i = 0; i < pFile->mNumImages; i++) {
            TexImage_8020DC10 *pImage = fn_8020E560(pFile, i);

            pImage->mpData = pImage->mpData + (int)pFile;
            if (pImage->mSize == 0) {
                TexMipHeader_8020E2B0 *pHeader = (TexMipHeader_8020E2B0 *)pImage->mpData;
                unsigned short j;

                for (j = 0; j < pHeader->mNumLevels; j++) {
                    pHeader->mLevels[j].mpData = pHeader->mLevels[j].mpData + (int)pFile;
                }
            }
        }
        for (i = 0; i < pFile->mNumPalettes; i++) {
            TexPalette_8020DC10 *pPalette = fn_8020E5F8(pFile, i);

            pPalette->mpData = pPalette->mpData + (int)pFile;
        }
    } else {
        return;
    }
    if (pFile->mVersion != 0) {
        pFile->mpExtras = (TexExtra_8020E53C *)((int)pFile->mpExtras + (int)pFile);
        if (pFile->mpInfo != 0) {
            pFile->mpInfo = (TexInfo_8020E2B0 *)((int)pFile->mpInfo + (int)pFile);
            pFile->mpInfo->mpData = pFile->mpInfo->mpData + (int)pFile;
        }
    }
    pFile->mFlags |= 1;
}

unsigned short fn_8020E51C(TexFile_8020DC10 *pFile)
{
    return pFile->mNumEntries;
}

unsigned short fn_8020E524(TexFile_8020DC10 *pFile)
{
    return pFile->mNumPalettes;
}

TexEntry_8020DC10 *fn_8020E52C(TexFile_8020DC10 *pFile, int index)
{
    return &pFile->mpEntries[index];
}

TexExtra_8020E53C *fn_8020E53C(TexFile_8020DC10 *pFile, int index)
{
    if (pFile->mVersion != 0) {
        return &pFile->mpExtras[index];
    }
    return 0;
}

TexImage_8020DC10 *fn_8020E560(TexFile_8020DC10 *pFile, unsigned short index)
{
    TexImage_8020DC10 *pImage;

    if (pFile->mVersion <= 1 && fn_801C1FEC(pFile, lbl_802B1BCC, 4) != 0) {
        unsigned int i;

        pImage = pFile->mpImages;
        for (i = 0; i < index; i++) {
            unsigned char *pNext = pImage->mpData;
            int pad;

            pNext += pImage->mSize;
            pad = (int)pNext & 3;
            if (pad != 0) {
                pNext += 4 - pad;
            }
            pImage = (TexImage_8020DC10 *)pNext;
        }
    } else {
        pImage = &pFile->mpImages[index];
    }
    return pImage;
}

TexPalette_8020DC10 *fn_8020E5F8(TexFile_8020DC10 *pFile, unsigned short index)
{
    TexPalette_8020DC10 *pPalette = 0;

    if (pFile->mVersion <= 1 && fn_801C1FEC(pFile, lbl_802B1BCC, 4) != 0) {
        unsigned int i;
        unsigned char *pNext = (unsigned char *)pFile->mpPalettes;

        for (i = 0; i < index; i++) {
            int pad;

            pPalette = (TexPalette_8020DC10 *)pNext;
            pNext = pPalette->mpData;
            pNext += pPalette->mSize;
            pad = (int)pNext & 3;
            if (pad != 0) {
                pNext += 4 - pad;
            }
        }
        pPalette = (TexPalette_8020DC10 *)pNext;
    } else {
        pPalette = &pFile->mpPalettes[index];
    }
    return pPalette;
}

void *fn_8020E6A0(TexImage_8020DC10 *pImage, void *pDst)
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
        memcpy(pDst, pImage->mpData, size);
    } else {
        TexDecodeBuf_8020E6A0 src;
        TexDecodeBuf_8020E6A0 dst;

        src.mpData = pImage->mpData;
        src.mSize = pImage->mSize;
        src.mWidth = pImage->mWidth;
        src.mHeight = pImage->mHeight;
        src.mBits = 16;
        dst.mpData = pDst;
        fn_8027F3A4(pImage->mType, &src, &dst);
        if (pImage->mType != 4) {
            int bpp = lbl_802F7A00[pImage->mFormat];

            dst.mSize = pImage->mWidth * pImage->mHeight * bpp / 8;
        } else {
            dst.mSize = pImage->mSize = pImage->mWidth * pImage->mHeight * 2;
        }
    }
    return pDst;
}
