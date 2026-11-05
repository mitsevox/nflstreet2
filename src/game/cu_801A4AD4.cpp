#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "engine/texfile.h"
#include "game/cu_801A4AD4.h"
#include "engine/tmtexlib.h"

#include <string.h>

extern "C" {
Desc_802347EC *fn_8016102C(int player);
Desc_802347EC *fn_802345F8(Desc_802347EC *pDescs, const char *pName);
void fn_80234844(Desc_802347EC *pDesc);
void fn_80239D1C(void *p, unsigned int size);
}

#define TEXTURE_ENTRY(name, flag) { name, flag, { 3, 1, -1.3f, 0, 0, 0 } }

static Entry_802F3488 lbl_802F3488[] = {
    TEXTURE_ENTRY("HAIR", 0),
    TEXTURE_ENTRY("HEAD", 0),
    TEXTURE_ENTRY("TORSO", 0),
    TEXTURE_ENTRY("SHOULDERPAD", 0),
    TEXTURE_ENTRY("BICEP", 0),
    TEXTURE_ENTRY("BICEPSWEATBAND", 0),
    TEXTURE_ENTRY("ELBOW", 0),
    TEXTURE_ENTRY("FOREARM", 0),
    TEXTURE_ENTRY("WRIST", 0),
    TEXTURE_ENTRY("LEFTHAND", 0),
    TEXTURE_ENTRY("RIGHTHAND", 0),
    TEXTURE_ENTRY("THIGH", 0),
    TEXTURE_ENTRY("KNEE", 0),
    TEXTURE_ENTRY("UPPERSHIN", 0),
    TEXTURE_ENTRY("LOWERSHIN", 0),
    TEXTURE_ENTRY("SHOE", 0),
    TEXTURE_ENTRY("DECALFRONT", 1),
    TEXTURE_ENTRY("DECALBACK", 1),
    TEXTURE_ENTRY("DECALHAT", 1),
    TEXTURE_ENTRY("HATLDCL", 1),
    TEXTURE_ENTRY("TATOOBICEPL", 0),
    TEXTURE_ENTRY("TATOOBICEPR", 0),
    TEXTURE_ENTRY("TATOOFOREARML", 0),
    TEXTURE_ENTRY("TATOOFOREARMR", 0),
    TEXTURE_ENTRY("TATOOELBOWL", 0),
    TEXTURE_ENTRY("TATOOELBOWR", 0),
    TEXTURE_ENTRY("HAT", 0),
    TEXTURE_ENTRY("GLASSES", 0),
    TEXTURE_ENTRY("NAMEPLATE", 1),
    TEXTURE_ENTRY(0, 0),
};

extern "C" {

void fn_801A4AD4(Object_8003DEC4 *pPlayer)
{
    pPlayer->mUnknown976 |= 0x10;
}

void *fn_801A4AE4(int player)
{
    return fn_8016102C(player)->mpUnknown24;
}

void fn_801A4B08(Desc_802347EC *pDesc)
{
    fn_80234844(pDesc);
}

/* Copies the image blocks and the +0x1C block selected by header halfword
   +8 of the texture data pSrc into pDest and flushes each copy; size is
   not read. */
void fn_801A4B28(void *pDest, void *pSrc, unsigned int size)
{
    TexFileMaterial_t *pSrcHeader = TexGetMaterialByIndex(pSrc, 0);
    TexFileMaterial_t *pDestHeader = TexGetMaterialByIndex(pDest, 0);
    TexFilePalette_t *pSrcBlock;
    TexFilePalette_t *pDestBlock;
    int i;

    for (i = 0; i < pDestHeader->mUnknown2; i++) {
        TexFileImage_t *pSrcImage = TexGetTextureByIndex(pSrc, pSrcHeader->mUnknown4 + i);
        TexFileImage_t *pDestImage = TexGetTextureByIndex(pDest, pDestHeader->mUnknown4 + i);

        memcpy(pDestImage->mpUnknownC, pSrcImage->mpUnknownC, pDestImage->mUnknown8);
        fn_80239D1C(pDestImage->mpUnknownC, pDestImage->mUnknown8);
    }

    pSrcBlock = TexGetPaletteByIndex(pSrc, pSrcHeader->mUnknown8);
    pDestBlock = TexGetPaletteByIndex(pDest, pDestHeader->mUnknown8);
    memcpy(pDestBlock->mpUnknown8, pSrcBlock->mpUnknown8, pDestBlock->mUnknown4);
    fn_80239D1C(pDestBlock->mpUnknown8, pDestBlock->mUnknown4);
}

/* Applies each entry of pEntries (lbl_802F3488 when null) to the texture of
   the same name in pDescs. */
void fn_801A4C1C(Desc_802347EC *pDescs, Entry_802F3488 *pEntries)
{
    int i;

    if (!pEntries) {
        pEntries = lbl_802F3488;
    }
    for (i = 0; pEntries[i].mpName; i++) {
        Desc_802347EC *pDesc = fn_802345F8(pDescs, pEntries[i].mpName);

        if (pEntries[i].mUnknown4) {
            TMTexWrapDesc_t pair = { 0, 0 };

            TMTexLibSetWrapParm((TMTexLib_t *)pDesc->mpUnknown24, &pair);
        }
        TMTexLibSetFilterParm((TMTexLib_t *)pDesc->mpUnknown24, &pEntries[i].mUnknown8);
    }
}
}
