#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8020E52C.h"
#include "game/fn_8021216C.h"

#include <string.h>

/* Two words passed by address to fn_802121D0, which hands them to
   fn_80212374 for each of its elements. */
struct Pair_802121D0 {
    int mUnknown0;
    int mUnknown4;
};

/* Entry of the table walked by fn_801A4C1C: a texture name looked up with
   fn_802345F8, a flag, and the descriptor passed to fn_8021216C. */
struct Entry_802F3488 {
    const char *mpName;
    unsigned char mUnknown4;
    Desc_802EE9E4 mUnknown8;
};

extern "C" {
Desc_802347EC *fn_8016102C(int player);
void fn_802121D0(void *p, Pair_802121D0 *pPair);
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

/* Copies the image blocks and the first +0x1C block of the texture data
   pSrc into pDest and flushes each copy; size is not read. */
void fn_801A4B28(void *pDest, void *pSrc, unsigned int size)
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
            Pair_802121D0 pair = { 0, 0 };

            fn_802121D0(pDesc->mpUnknown24, &pair);
        }
        fn_8021216C(pDesc->mpUnknown24, &pEntries[i].mUnknown8);
    }
}
}
