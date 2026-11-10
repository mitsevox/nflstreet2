/* Player textures: nameplate redraw request, the player texture library,
   texture copies between players and the per-body-part filter settings. */
#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "engine/texfile.h"
#include "game/PlyrTex.h"
#include "engine/tmtexlib.h"

#include <string.h>

extern "C" {
ModelTexSlot_t *PlaTexCacheGetDescs(int player);
ModelTexSlot_t *fn_802345F8(ModelTexSlot_t *pDescs, const char *pName);
void fn_80234844(ModelTexSlot_t *pDesc);
void fn_80239D1C(void *p, unsigned int size);
}

#define TEXTURE_ENTRY(name, flag) { name, flag, { 3, 1, -1.3f, 0, 0, 0 } }

static PlyrTexPartFilter _PlyrTex_aPartFilters[] = {
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

void PlyrTexRequestNameplate(Object_8003DEC4 *pPlayer)
{
    pPlayer->mUnknown976 |= 0x10;
}

void *PlyrTexGetLib(int player)
{
    return PlaTexCacheGetDescs(player)->mpUnknown24;
}

void PlyrTexFreeDesc(ModelTexSlot_t *pDesc)
{
    fn_80234844(pDesc);
}

/* Copies the image blocks and the +0x1C block selected by header halfword
   +8 of the texture data pSrc into pDest and flushes each copy; size is
   not read. */
void PlyrTexCopy(void *pDest, void *pSrc, unsigned int size)
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

/* Applies each entry of pEntries (_PlyrTex_aPartFilters when null) to the texture of
   the same name in pDescs. */
void PlyrTexApplyFilters(ModelTexSlot_t *pDescs, PlyrTexPartFilter *pEntries)
{
    int i;

    if (!pEntries) {
        pEntries = _PlyrTex_aPartFilters;
    }
    for (i = 0; pEntries[i].mpName; i++) {
        ModelTexSlot_t *pDesc = fn_802345F8(pDescs, pEntries[i].mpName);

        if (pEntries[i].mUnknown4) {
            TMTexWrapDesc_t pair = { 0, 0 };

            TMTexLibSetWrapParm((TMTexLib_t *)pDesc->mpUnknown24, &pair);
        }
        TMTexLibSetFilterParm((TMTexLib_t *)pDesc->mpUnknown24, &pEntries[i].mUnknown8);
    }
}
}
