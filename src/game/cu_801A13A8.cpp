#include "game/Object_8003DEC4.h"
#include "game/Object_8020E52C.h"
#include "game/Font_8019BE30.h"

/* 0x50-byte object set up by 0x80233CF0, which stores its second argument at
   +0x18 and initializes the block at +0x1C. */
struct Instance_801A13A8 {
    int mUnknown0[6];
    void *mpUnknown18;
    char mUnknown1C[0x34];
};

/* 64-byte block copied between the first +0x1C entries of two texture data
   images. */
struct Colors_801A1400 {
    unsigned int mUnknown0[16];
};

struct TextureEntry1C_801A1400 {
    int mUnknown0[2];
    Colors_801A1400 *mpUnknown8;
};

/* Partial view of the texture data returned by 0x80161094: the entry tables
   at +0x18 (fn_8020E560) and +0x1C (fn_8020E5F8). */
struct Texture_801A1400 {
    char mUnknown0[0x18];
    Object_8020E560 *mpUnknown18;
    TextureEntry1C_801A1400 *mpUnknown1C;
};

extern "C" {

unsigned char *fn_80161094(int player, int slot);
void fn_8020F824(void *, void *);
void fn_80233CF0(void *pInstance, void *pModel, void *p);

void fn_801A13A8(Instance_801A13A8 *pInstance)
{
    pInstance->mpUnknown18 = 0;
}

void fn_801A13B4(Instance_801A13A8 *pInstance, Instance_801A13A8 *pSource, void *p)
{
    fn_80233CF0(pInstance, pSource->mpUnknown18, p);
}

void fn_801A13D8(Instance_801A13A8 *pInstance, void *p)
{
    fn_8020F824(pInstance->mUnknown1C, p);
}

void fn_801A13FC(void)
{
}

/* Draws the string at +0x1058 of the player with the 0x801614C4 font into
   its texture slot 31, then copies the 64-byte +0x1C block of slot 9 over
   that of slot 31. */
void fn_801A1400(Object_8003DEC4 *pPlayer)
{
    unsigned char *pDest =
        ((Texture_801A1400 *)fn_80161094(pPlayer->mUnknown4971, 31))->mpUnknown18->mpUnknownC;
    Colors_801A1400 *pColors;

    fn_8019BC50(fn_801614C4(), pDest, (const unsigned char *)pPlayer->mUnknown4184);
    pColors = ((Texture_801A1400 *)fn_80161094(pPlayer->mUnknown4971, 31))->mpUnknown1C->mpUnknown8;
    *pColors = *((Texture_801A1400 *)fn_80161094(pPlayer->mUnknown4971, 9))->mpUnknown1C->mpUnknown8;
}
}
