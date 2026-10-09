/* 0x50-byte object set up by 0x80233CF0, which stores its second argument at
   +0x18 and initializes the block at +0x1C. */
struct Instance_801A13A8 {
    int mUnknown0[6];
    void *mpUnknown18;
    char mUnknown1C[0x34];
};

/* Partial view of a texture image returned by 0x80161094: the words at +0x18
   and +0x1C point to blocks whose +0xC and +8 words are read here. */
struct TextureEntry18_801A1400 {
    int mUnknown0[3];
    void *mpUnknownC;
};

struct Colors_801A1400 {
    unsigned int mUnknown0[16];
};

struct TextureEntry1C_801A1400 {
    int mUnknown0[2];
    Colors_801A1400 *mpUnknown8;
};

struct Texture_801A1400 {
    char mUnknown0[0x18];
    TextureEntry18_801A1400 *mpUnknown18;
    TextureEntry1C_801A1400 *mpUnknown1C;
};

struct Object_801A1400 {
    char mUnknown0[0x1058];
    char mUnknown1058[0x20];
    char mUnknown1078[0x2F3];
    unsigned char mUnknown136B;
};

struct Font_8019BE30;

extern "C" {

unsigned char *fn_80161094(int player, int slot);
Font_8019BE30 *fn_801614C4(void);
void fn_8019BC50(Font_8019BE30 *pFont, void *pDest, const char *pText);
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

/* Draws the text at +0x1058 with the 0x801614C4 font into texture slot 31 of
   the player at +0x136B, then copies the 64-byte +0x1C block of slot 9 over
   that of slot 31. */
void fn_801A1400(Object_801A1400 *pObject)
{
    void *pDest = ((Texture_801A1400 *)fn_80161094(pObject->mUnknown136B, 31))->mpUnknown18->mpUnknownC;
    Colors_801A1400 *pColors;

    fn_8019BC50(fn_801614C4(), pDest, pObject->mUnknown1058);
    pColors = ((Texture_801A1400 *)fn_80161094(pObject->mUnknown136B, 31))->mpUnknown1C->mpUnknown8;
    *pColors = *((Texture_801A1400 *)fn_80161094(pObject->mUnknown136B, 9))->mpUnknown1C->mpUnknown8;
}
}
