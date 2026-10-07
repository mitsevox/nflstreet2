#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8020E52C.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_8017F584.h"

/* Per-player texture slot state: the wanted texture id and palette, and the
   progress of its load from the texture archive. */
struct TextureSlot_802E6D68 {
    int mId;
    int mPlayer;
    int mSlot;
    unsigned char mDirty;
    unsigned char mRequested;
    unsigned char mReceived;
    int mPalette;
    void *mpData;
};

/* Sort key of fn_80160CDC: the low half of the texture id and the slot's
   player and slot index. */
struct SortEntry_80160CDC {
    unsigned short mId;
    unsigned char mPlayer;
    unsigned char mSlot;
};

struct FontDesc_8019BE30 {
    int mCount;
    const char *mpChars;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

struct Font_8019BE30 {
    char mUnknown0[0x160];
};

extern "C" {
void fn_8004625C(void *p, int id, unsigned char *pColors);
int fn_80049D04(int index);
unsigned char fn_80054D24(int index);
void fn_8015D254(int index);
void fn_8019BE30(Font_8019BE30 *pFont, FontDesc_8019BE30 *pDesc, void *pArchive, int a);
void fn_8019BE94(Font_8019BE30 *pFont);
void fn_801A4B08(Desc_802347EC *pDesc);
void fn_801A4B28(void *pDest, void *pSrc, unsigned int size);
int fn_801C1870(int a, int b, unsigned int size, int count,
                void (*pCallback)(int, void *, TextureSlot_802E6D68 *));
void fn_801C1950(int loader, void *pArchive, int id, TextureSlot_802E6D68 *pSlot);
void fn_801C1B1C(int loader, void *pData);
void fn_801C1B90(int loader, void *pData);
void fn_801C1C1C(int loader);
void fn_801C1C98(int loader);
void fn_801C1FBC(void *pDest, void *pSrc, unsigned int size);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *fn_801C3084(const char *pString, int c);
int fn_801C9DC8(int value);
void *fn_801D2BB0(int a, int size, int c, int d);
int fn_801EFF80(void *pArchive, int id, void *pDest);
int fn_801F0A8C(void *pArchive, char *pName);
int fn_801F0C50(void *pArchive, int id);
int fn_801F1520(int value);
void fn_801F282C(void);
void fn_801F283C(void);
void fn_801F51DC(int a, void *pBase, int count, int size,
                 int (*pCompare)(const SortEntry_80160CDC *, const SortEntry_80160CDC *),
                 int b, int c, int d);
void fn_802347EC(void *pData, Desc_802347EC *pDesc, int a, int b);

extern char lbl_802EC080[];
}

#define TEXTURE_SLOT_NAMES                                                                  \
    {                                                                                       \
        { "GLASSES" }, { "HAT" }, { "DECALHAT" }, { "HATLDCL" }, { "HAIR" }, { "HEAD" },    \
        { "FACIALHAIR" }, { "CHAIN" }, { "MEDALLION" }, { "TORSO" }, { "SHOULDERPAD" },     \
        { "BICEP" }, { "BICEPSWEATBAND" }, { "ELBOW" }, { "FOREARM" }, { "WRIST" },         \
        { "LEFTHAND" }, { "RIGHTHAND" }, { "THIGH" }, { "KNEE" }, { "UPPERSHIN" },          \
        { "LOWERSHIN" }, { "SHOE" }, { "DECALFRONT" }, { "DECALBACK" }, { "TATOOBICEPL" },  \
        { "TATOOBICEPR" }, { "TATOOFOREARML" }, { "TATOOFOREARMR" }, { "TATOOELBOWL" },     \
        { "TATOOELBOWR" }, { "NAMEPLATE" }, { 0 }                                           \
    }

#define TEXTURE_SLOT_IDS                                                                    \
    {                                                                                       \
        { 0x3561 }, { 0x3560 }, { 0x3547 }, { 3 }, { 0x354D }, { 0x354A }, { 0x354B },      \
        { 0x3562 }, { 0x3563 }, { 0x3555 }, { 0x3552 }, { 0x3548 }, { 0x3553 }, { 0x3549 }, \
        { 0x354C }, { 0x3557 }, { 0x354E }, { 0x354E }, { 0x3554 }, { 0x354F }, { 0x3556 }, \
        { 0x3550 }, { 0x3551 }, { 0x3547 }, { 0x3547 }, { 0x3558 }, { 0x3559 }, { 0x355A }, \
        { 0x355B }, { 0x355C }, { 0x355D }, { 2 }                                           \
    }

static Desc_802347EC sTextureDescs[14][33] = {
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
};

static TextureSlot_802E6D68 sSlots[14][32] = {
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
};

static FontDesc_8019BE30 sFontDesc = {
    67, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,-#'.", 32, 32, 16, 3,
};

static unsigned char *sTextures[14][32];
static unsigned char sColors[14][25];
static unsigned int sSizes[32];
static Font_8019BE30 sFont;

static unsigned char sInitialized = 0;
static void *sArchive = 0;
static int sPending = 0;
static unsigned int sPlayerCount = 0;
static unsigned int sMaxSize = 0;
static int sLoader;

extern "C" {

void fn_80160188(void);
void fn_8016032C(void);
void fn_80160F14(int player);
void fn_80160F58(int player, int slot);
int fn_80161048(char *pName);
void fn_80161494(int player, int slot);

void fn_8016014C(int loader, void *pData, TextureSlot_802E6D68 *pSlot)
{
    fn_801C1B1C(loader, pData);
    pSlot->mpData = pData;
    pSlot->mReceived = 1;
}

void fn_80160188(void)
{
    unsigned int player;
    unsigned int slot;
    int busy;

    for (player = 0; player < sPlayerCount; player++) {
        busy = 0;
        for (slot = 0; slot < 32; slot++) {
            if (sSlots[player][slot].mDirty) {
                if (sSlots[player][slot].mReceived) {
                    if (sSlots[player][slot].mRequested) {
                        fn_8020E2B0(sSlots[player][slot].mpData);
                        if (sSlots[player][slot].mPalette != -1) {
                            int index = fn_8020E52C(sSlots[player][slot].mpData, 0)->mUnknown8;

                            fn_8004625C(fn_8020E5F8(sSlots[player][slot].mpData, index),
                                        sSlots[player][slot].mPalette, sColors[player]);
                        }
                        fn_801A4B28(sTextures[player][slot], sSlots[player][slot].mpData,
                                    sSizes[slot]);
                        if (slot == 4) {
                            fn_80161494(player, 4);
                        }
                        fn_801C1B90(sLoader, sSlots[player][slot].mpData);
                        sSlots[player][slot].mpData = 0;
                        sSlots[player][slot].mDirty = 0;
                        sPending--;
                        sSlots[player][slot].mRequested = 0;
                        sSlots[player][slot].mReceived = 0;
                    } else {
                        fn_801C1B90(sLoader, sSlots[player][slot].mpData);
                        sSlots[player][slot].mpData = 0;
                        sSlots[player][slot].mReceived = 0;
                        sPending--;
                    }
                }
                if (sSlots[player][slot].mDirty) {
                    busy = 1;
                }
            }
        }
        if (!busy) {
            fn_8015D254(player);
        }
    }
}

void fn_8016032C(void)
{
    unsigned int player;
    unsigned int i;
    unsigned int other;
    int slot;
    unsigned int id;
    int palette;

    if (sPending == 1) {
        return;
    }

    for (player = 0; player < sPlayerCount; player++) {
        slot = 32;
        id = 0xFFFFFFFF;
        palette = -1;
        for (i = 0; i < 32; i++) {
            if (sSlots[player][i].mDirty && !sSlots[player][i].mRequested) {
                if (slot == 32 || sSlots[player][i].mId < id) {
                    palette = sSlots[player][i].mPalette;
                    id = sSlots[player][i].mId;
                    slot = i;
                }
            }
        }

        if (slot == 32) {
            continue;
        }

        /* Another player may already hold the same texture. */
        for (other = 0; other < sPlayerCount; other++) {
            if (other != player && sSlots[other][slot].mId == id &&
                sSlots[other][slot].mPalette == palette && !sSlots[other][slot].mDirty) {
                break;
            }
        }
        if (other < sPlayerCount) {
            fn_801A4B28(sTextures[player][slot], sTextures[other][slot], sSizes[slot]);
            fn_8020E2B0(sTextures[player][slot]);
            if (sSlots[player][slot].mPalette != -1) {
                int index = fn_8020E52C(sTextures[player][slot], 0)->mUnknown8;

                fn_8004625C(fn_8020E5F8(sTextures[player][slot], index),
                            sSlots[player][slot].mPalette, sColors[player]);
            }
            sSlots[player][slot].mReceived = 0;
            sSlots[player][slot].mDirty = 0;
            sSlots[player][slot].mRequested = 0;
            continue;
        }

        /* Or another slot of the same player. */
        for (other = 0; other < 32; other++) {
            if (other != slot && sSlots[player][other].mId == id &&
                sSlots[player][other].mPalette == palette && !sSlots[player][other].mDirty) {
                break;
            }
        }
        if (other < 32) {
            fn_801A4B28(sTextures[player][slot], sTextures[player][other], sSizes[slot]);
            fn_8020E2B0(sTextures[player][slot]);
            if (sSlots[player][slot].mPalette != -1) {
                int index = fn_8020E52C(sTextures[player][slot], 0)->mUnknown8;

                fn_8004625C(fn_8020E5F8(sTextures[player][slot], index),
                            sSlots[player][slot].mPalette, sColors[player]);
            }
            sSlots[player][slot].mReceived = 0;
            sSlots[player][slot].mDirty = 0;
            sSlots[player][slot].mRequested = 0;
            continue;
        }

        sSlots[player][slot].mRequested = 1;
        sSlots[player][slot].mReceived = 0;
        sPending++;
        fn_801C1950(sLoader, sArchive, sSlots[player][slot].mId, &sSlots[player][slot]);
        if (sPending == 1) {
            return;
        }
    }
}

void fn_8016061C(int player, int slot, void *pData, int shared)
{
    if (!shared) {
        fn_801EFF80(sArchive, sSlots[player][slot].mId, pData);
        fn_8020E2B0(pData);
    }
    fn_801A4B28(sTextures[player][slot], pData, sSizes[slot]);
    if (slot == 4 && fn_80049D04(player)) {
        fn_80161494(player, 4);
    }
    if (sSlots[player][slot].mPalette != -1) {
        fn_8004625C(fn_8020E5F8(sTextures[player][slot], 0), sSlots[player][slot].mPalette,
                    sColors[player]);
    }
    sSlots[player][slot].mRequested = sSlots[player][slot].mReceived =
        sSlots[player][slot].mDirty = 0;
}

void fn_8016074C(int player)
{
    TextureSlot_802E6D68 defaults[32] = TEXTURE_SLOT_IDS;
    int i;

    for (i = 0; i < 32; i++) {
        sSlots[player][i].mDirty = 1;
        sSlots[player][i].mId = defaults[i].mId;
    }
}

void fn_801607F0(int mode)
{
    int saved0 = 0;
    int saved1 = 0;

    if (fn_80027DF0() == 0) {
        saved0 = fn_801F1520(mode);
        saved1 = fn_801C9DC8(mode);
    }
    sArchive = fn_801EEB44(lbl_802EC080, 44);
    if (fn_80027DF0() == 0) {
        fn_801F1520(saved0);
        fn_801C9DC8(saved1);
    }
}

void fn_80160874(unsigned int count)
{
    unsigned int player;
    unsigned int i;
    unsigned int offset;
    unsigned int size;
    unsigned char *pBase;
    int saved0 = 0;
    int saved1 = 0;

    sPlayerCount = count;
    if (sInitialized) {
        return;
    }

    if (sArchive == 0) {
        fn_801607F0(4);
    }
    sInitialized = 1;

    offset = 0;
    for (player = 0; player < sPlayerCount; player++) {
        fn_8016074C(player);
        for (i = 0; i < 32; i++) {
            if (player == 0) {
                size = fn_801F0C50(sArchive, sSlots[0][i].mId);
                sSizes[i] = size;
            } else {
                size = sSizes[i];
            }
            sSlots[player][i].mPlayer = player;
            sSlots[player][i].mSlot = i;
            sTextures[player][i] = (unsigned char *)offset;
            sSlots[player][i].mDirty = 1;
            sSlots[player][i].mRequested = 0;
            sSlots[player][i].mReceived = 0;
            offset += size + 32 - (size & 31);
            sSlots[player][i].mPalette = -1;
            if (size > sMaxSize) {
                sMaxSize = size;
            }
        }
    }

    pBase = (unsigned char *)fn_801D2BB0(1, offset, 2, 0);
    for (player = 0; player < sPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            sTextures[player][i] += (unsigned int)pBase;
        }
    }

    saved0 = fn_801F1520(4);
    saved1 = fn_801C9DC8(4);
    fn_8019BE30(&sFont, &sFontDesc, sArchive, 1);
    fn_801F1520(saved0);
    fn_801C9DC8(saved1);
}

void fn_80160A80(void)
{
    unsigned int i;
    unsigned int player;

    for (i = 0; i < 32; i++) {
        unsigned char *pDest = sTextures[0][i];
        int id = sSlots[0][i].mId;
        unsigned int size = fn_801F0C50(sArchive, id);

        fn_801EFF80(sArchive, id, pDest);
        for (player = 1; player < sPlayerCount; player++) {
            fn_801C1FBC(sTextures[player][i], pDest, size);
        }
        for (player = 0; player < sPlayerCount; player++) {
            fn_8020E2B0(sTextures[player][i]);
        }
    }
}

void fn_80160B6C(void)
{
    unsigned int player;
    int i;

    sInitialized = 0;
    for (player = 0; player < sPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            sSlots[player][i].mDirty = 1;
            sSlots[player][i].mRequested = 0;
            sSlots[player][i].mReceived = 0;
        }
    }
    fn_801D2BD0(sTextures[0][0]);
    fn_8019BE94(&sFont);
}

void *fn_80160C08(void)
{
    return sArchive;
}

void fn_80160C10(void)
{
    unsigned int player;
    unsigned int i;

    sLoader = fn_801C1870(1, 1, sMaxSize, 100, fn_8016014C);
    for (player = 0; player < sPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            fn_802347EC(sTextures[player][i], &sTextureDescs[player][i], 6, 0);
        }
    }
}

int fn_80160CCC(const SortEntry_80160CDC *pA, const SortEntry_80160CDC *pB)
{
    return pA->mId - pB->mId;
}

void fn_80160CDC(void)
{
    SortEntry_80160CDC entries[14 * 32];
    unsigned int count;
    unsigned int n;
    int i;
    unsigned int player;
    int id;
    int palette;
    void *pBuffer;

    fn_801F282C();
    n = 0;
    for (player = 0; player < sPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            if (sSlots[player][i].mDirty == 1) {
                entries[n].mId = sSlots[player][i].mId;
                entries[n].mSlot = sSlots[player][i].mSlot;
                entries[n].mPlayer = sSlots[player][i].mPlayer;
                n++;
            }
        }
    }

    count = n;
    if (n != 0) {
        fn_801F51DC(0, entries, n, 4, fn_80160CCC, 0, 0, 1);
        id = -1;
        pBuffer = fn_801D2B7C(sMaxSize, 0, 0);
        palette = -1;
        for (n = 0; n < count; n++) {
            i = entries[n].mSlot;
            player = entries[n].mPlayer;
            if (sSlots[player][i].mId == id && sSlots[player][i].mPalette == palette) {
                fn_8016061C(player, i, pBuffer, 1);
            } else {
                fn_8016061C(player, i, pBuffer, 0);
                id = sSlots[player][i].mId;
                palette = sSlots[player][i].mPalette;
            }
        }
        fn_801D2BD0(pBuffer);
    }
    fn_801F283C();
}

void fn_80160E94(int player, int slot, int id, int palette, int force)
{
    if (id == -1) {
        return;
    }
    if (!force && id == sSlots[player][slot].mId && palette == sSlots[player][slot].mPalette) {
        return;
    }
    sSlots[player][slot].mPalette = palette;
    sSlots[player][slot].mId = id;
    sSlots[player][slot].mRequested = 0;
    sSlots[player][slot].mDirty = 1;
}

void fn_80160F14(int player)
{
    unsigned int i;

    for (i = 0; i < 32; i++) {
        fn_80160F58(player, i);
    }
}

void fn_80160F58(int player, int slot)
{
    if (sSlots[player][slot].mId == -1) {
        return;
    }
    sSlots[player][slot].mRequested = 0;
    sSlots[player][slot].mDirty = 1;
}

void fn_80160F98(void)
{
    unsigned int player;
    unsigned int i;

    fn_801C1C1C(sLoader);
    fn_801C1C98(sLoader);
    sPending = 0;
    for (player = 0; player < sPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            fn_801A4B08(&sTextureDescs[player][i]);
        }
    }
}

Desc_802347EC *fn_8016102C(int player)
{
    return sTextureDescs[player];
}

int fn_80161048(char *pName)
{
    char *pSpace = fn_801C3084(pName, ' ');

    if (pSpace) {
        *pSpace = 0;
    }
    return fn_801F0A8C(sArchive, pName);
}

unsigned char *fn_80161094(int player, int slot)
{
    return sTextures[player][slot];
}

void fn_801610B0(int player, unsigned char *pColors)
{
    int tint = 0;
    int other = 0;
    int i;

    for (i = 0; i < 25; i++) {
        if (sColors[player][i] != pColors[i]) {
            sColors[player][i] = pColors[i];
            switch (i) {
            case 18:
            case 19:
                tint = 1;
                break;
            default:
                other = 1;
                break;
            }
        }
    }

    if (other) {
        fn_80160F14(player);
    } else if (tint) {
        fn_80160F58(player, 4);
        fn_80160F58(player, 6);
    }
}

void fn_80161168(void)
{
    fn_80160188();
    fn_8016032C();
}

void fn_8016118C(void)
{
    while (sPending > 0) {
        fn_80160188();
    }
}

void fn_801611BC(int player, const char *pName, int force)
{
    char name[38];
    int id;

    name[0] = 0;
    fn_801C2D88(name, sizeof(name), "PLATEX_FACE_%s", pName);
    id = fn_80161048(name);
    if (id == -1) {
        id = fn_80161048("PLATEX_TEMPLATE_FACE");
    }
    if (fn_80054D24(38) && fn_8017F584() == 0) {
        id = fn_80161048("PLATEX_TEMPLATE_FACE");
    } else {
        fn_80160E94(player, 5, id, -1, force);
        fn_80160E94(player, 6, 0x354B, -1, force);
    }
}

int fn_8016128C(int index)
{
    char name[32];
    int id;

    if (fn_80054D24(38) && fn_8017F584() == 0) {
        id = fn_80161048("PLATEX_TEMPLATE_FACE");
    } else {
        name[0] = 0;
        fn_801C2D88(name, 24, "PLATEX_FACE_CAP%02d", index);
        id = fn_80161048(name);
    }
    return id;
}

void fn_8016130C(int player, int index, int row, int column, int force)
{
    int id = fn_8016128C(index);

    if (id == -1) {
        id = fn_80161048("PLATEX_TEMPLATE_FACE");
    }
    row = row * 3 + column + 0x33BA;
    fn_80160E94(player, 5, id, -1, force);
    fn_80160E94(player, 6, row, 0xA7, force);
}

void fn_8016139C(int style, int *pId, int *pPalette)
{
    unsigned int id = style + 0x3564;

    *pId = id;
    switch (id) {
    case 0x3564:
    case 0x3565:
    case 0x3567:
    case 0x3569:
    case 0x358A:
        *pPalette = -1;
        break;
    default:
        *pPalette = 0xA6;
        break;
    }
}

void fn_801613F0(void)
{
    unsigned int player;
    int i;

    while (sPending > 0) {
        fn_80160188();
    }
    for (player = 0; player < sPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            if (sSlots[player][i].mDirty && !sSlots[player][i].mRequested) {
                sSlots[player][i].mDirty = 0;
                sSlots[player][i].mId = -1;
                sSlots[player][i].mPalette = -1;
            }
        }
    }
}

void fn_80161494(int player, int slot)
{
}

void fn_80161498(void)
{
    fn_801EEFAC(sArchive);
    sArchive = 0;
}

Font_8019BE30 *fn_801614C4(void)
{
    return &sFont;
}

}
