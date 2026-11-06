/* Player model parts: set-up of the model level-of-detail slots and their
   skeletons, and the jersey nameplate texture drawn from the player's name. */
#include "game/Object_8003DEC4.h"
#include "engine/texfile.h"
#include "game/BmFont.h"

/* 0x50-byte object set up by 0x80233CF0, which stores its second argument at
   +0x18 and initializes the block at +0x1C. */
struct PlyrModelLodView {
    int mUnknown0[6];
    void *mpUnknown18;
    char mUnknown1C[0x34];
};

/* 64-byte block copied between the first +0x1C entries of two texture data
   images. */
struct PlyrTexClutBlock {
    unsigned int mUnknown0[16];
};

struct PlyrTexClutEntry {
    int mUnknown0[2];
    PlyrTexClutBlock *mpUnknown8;
};

/* Partial view of the texture data returned by 0x80161094: the entry tables
   at +0x18 (TexGetTextureByIndex) and +0x1C (TexGetPaletteByIndex). */
struct PlyrTexData {
    char mUnknown0[0x18];
    TexFileImage_t *mpUnknown18;
    PlyrTexClutEntry *mpUnknown1C;
};

extern "C" {

unsigned char *fn_80161094(int player, int slot);
void TMModelRemapClusters(void *, void *);
void fn_80233CF0(void *pInstance, void *pModel, void *p);

void PlyrModelLodClear(PlyrModelLodView *pInstance)
{
    pInstance->mpUnknown18 = 0;
}

void PlyrModelLodInit(PlyrModelLodView *pInstance, PlyrModelLodView *pSource, void *p)
{
    fn_80233CF0(pInstance, pSource->mpUnknown18, p);
}

void PlyrModelLodBindSkeleton(PlyrModelLodView *pInstance, void *p)
{
    TMModelRemapClusters(pInstance->mUnknown1C, p);
}

void PlyrModelLodAttach(void)
{
}

/* Draws the string at +0x1058 of the player with the 0x801614C4 font into
   its texture slot 31, then copies the 64-byte +0x1C block of slot 9 over
   that of slot 31. */
void PlyrModelDrawNameplate(Object_8003DEC4 *pPlayer)
{
    unsigned char *pDest =
        ((PlyrTexData *)fn_80161094(pPlayer->mUnknown4971, 31))->mpUnknown18->mpUnknownC;
    PlyrTexClutBlock *pBlock;

    BmFontRenderString(fn_801614C4(), pDest, (const unsigned char *)pPlayer->mUnknown4184);
    pBlock = ((PlyrTexData *)fn_80161094(pPlayer->mUnknown4971, 31))->mpUnknown1C->mpUnknown8;
    *pBlock = *((PlyrTexData *)fn_80161094(pPlayer->mUnknown4971, 9))->mpUnknown1C->mpUnknown8;
}
}
