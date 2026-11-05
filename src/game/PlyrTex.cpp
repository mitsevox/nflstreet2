/* Player textures: nameplate redraw request, the player texture library,
   texture copies between players and the per-body-part filter settings. */
#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8020E52C.h"
#include "game/PlyrTex.h"
#include "game/fn_8021216C.h"

#include <string.h>

extern "C" {
Desc_802347EC *fn_8016102C(int player);
Desc_802347EC *fn_802345F8(Desc_802347EC *pDescs, const char *pName);
void fn_80234844(Desc_802347EC *pDesc);
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
    return fn_8016102C(player)->mpUnknown24;
}

void PlyrTexFreeDesc(Desc_802347EC *pDesc)
{
    fn_80234844(pDesc);
}

/* Copies the image blocks and the +0x1C block selected by header halfword
   +8 of the texture data pSrc into pDest and flushes each copy; size is
   not read. */
void PlyrTexCopy(void *pDest, void *pSrc, unsigned int size)
{
    Object_8020E52C *pSrcHeader = fn_8020E52C(pSrc, 0);
    Object_8020E52C *pDestHeader = fn_8020E52C(pDest, 0);
    Object_8020E5F8 *pSrcBlock;
    Object_8020E5F8 *pDestBlock;
    int i;

    for (i = 0; i < pDestHeader->mUnknown2; i++) {
        Object_8020E560 *pSrcImage = fn_8020E560(pSrc, pSrcHeader->mUnknown4 + i);
        Object_8020E560 *pDestImage = fn_8020E560(pDest, pDestHeader->mUnknown4 + i);

        memcpy(pDestImage->mpUnknownC, pSrcImage->mpUnknownC, pDestImage->mUnknown8);
        fn_80239D1C(pDestImage->mpUnknownC, pDestImage->mUnknown8);
    }

    pSrcBlock = fn_8020E5F8(pSrc, pSrcHeader->mUnknown8);
    pDestBlock = fn_8020E5F8(pDest, pDestHeader->mUnknown8);
    memcpy(pDestBlock->mpUnknown8, pSrcBlock->mpUnknown8, pDestBlock->mUnknown4);
    fn_80239D1C(pDestBlock->mpUnknown8, pDestBlock->mUnknown4);
}

/* Applies each entry of pEntries (_PlyrTex_aPartFilters when null) to the texture of
   the same name in pDescs. */
void PlyrTexApplyFilters(Desc_802347EC *pDescs, PlyrTexPartFilter *pEntries)
{
    int i;

    if (!pEntries) {
        pEntries = _PlyrTex_aPartFilters;
    }
    for (i = 0; pEntries[i].mpName; i++) {
        Desc_802347EC *pDesc = fn_802345F8(pDescs, pEntries[i].mpName);

        if (pEntries[i].mUnknown4) {
            TexWrapDesc_80212374 pair = { 0, 0 };

            fn_802121D0((TexLib_802119C4 *)pDesc->mpUnknown24, &pair);
        }
        fn_8021216C((TexLib_802119C4 *)pDesc->mpUnknown24, &pEntries[i].mUnknown8);
    }
}
}
