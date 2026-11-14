/* Player texture cache: keeps, for every player on the field, the 32 body-part textures
   (glasses, hat, hair, head, torso, shoes, decals, tattoos, nameplate) read from the
   "platex.dat" archive. Appearance code sets a slot's texture id and palette; the cache
   streams changed textures in the background, or loads them all at once, sharing a
   texture already loaded for another slot or player, and applies the player colours. */

#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/BmFont.h"
#include "engine/texfile.h"
#include "game/PlyrTex.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/GameModeType.h"

/* Per-player texture slot state: the wanted texture id and palette, and the
   progress of its load from the texture archive. */
struct PlaTexCacheSlot_t {
    int mId;
    int mPlayer;
    int mSlot;
    unsigned char mDirty;
    unsigned char mRequested;
    unsigned char mReceived;
    int mPalette;
    void *mpData;
};

/* Sort key of PlaTexCacheLoadAllNow: the low half of the texture id and the slot's
   player and slot index. */
struct PlaTexCacheSortEntry_t {
    unsigned short mId;
    unsigned char mPlayer;
    unsigned char mSlot;
};

extern "C" {
void PlaDynClutApplyColors(void *p, int id, unsigned char *pColors);
int PlayerLookShowsHair(int index);
unsigned char CheatFlagsIsSet(int index);
void FEPlyrLoadFinish(int index);
int ResStreamOpen(int a, int b, unsigned int size, int count,
                void (*pCallback)(int, void *, PlaTexCacheSlot_t *));
void ResStreamQueueRead(int loader, void *pArchive, int id, PlaTexCacheSlot_t *pSlot);
void ResStreamHoldBuffer(int loader, void *pData);
void ResStreamReleaseBuffer(int loader, void *pData);
void ResStreamReleaseAllBuffers(int loader);
void ResStreamClose(int loader);
void memcpy(void *pDest, void *pSrc, unsigned int size);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *strchr(const char *pString, int c);
int FileSetMemAllocFlags(int value);
void *fn_801D2BB0(int a, int size, int c, int d);
int ResCopyToBuffer(void *pArchive, int id, void *pDest);
int ResFindIndexByName(void *pArchive, char *pName);
int ResGetSize(void *pArchive, int id);
int ResSetMemFlags(int value);
void ResTrackPause(void);
void ResTrackResume(void);
void SortArray(int a, void *pBase, int count, int size,
                 int (*pCompare)(const PlaTexCacheSortEntry_t *, const PlaTexCacheSortEntry_t *),
                 int b, int c, int d);
void fn_802347EC(void *pData, ModelTexSlot_t *pDesc, int a, int b);

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

static ModelTexSlot_t _PlaTexCache_aDescs[14][33] = {
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
    TEXTURE_SLOT_NAMES, TEXTURE_SLOT_NAMES,
};

static PlaTexCacheSlot_t _PlaTexCache_aSlots[14][32] = {
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
    TEXTURE_SLOT_IDS, TEXTURE_SLOT_IDS,
};

static BmFontDesc _PlaTexCache_FontDesc = {
    67, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,-#'.", 32, 32, 16, 3,
};

static unsigned char *_PlaTexCache_apTextures[14][32];
static unsigned char _PlaTexCache_auColors[14][25];
static unsigned int _PlaTexCache_auSizes[32];
static BmFont _PlaTexCache_Font;

static unsigned char _PlaTexCache_bInitialized = 0;
static void *_PlaTexCache_pArchive = 0;
static int _PlaTexCache_iPending = 0;
static unsigned int _PlaTexCache_uPlayerCount = 0;
static unsigned int _PlaTexCache_uMaxSize = 0;
static int _PlaTexCache_iStream;

extern "C" {

void PlaTexCacheFinishReads(void);
void PlaTexCacheRequestNext(void);
void PlaTexCacheInvalidatePlayer(int player);
void PlaTexCacheInvalidateSlot(int player, int slot);
int PlaTexCacheFindTexture(char *pName);
void PlaTexCacheOnHairLoaded(int player, int slot);

void PlaTexCacheOnStreamRead(int loader, void *pData, PlaTexCacheSlot_t *pSlot)
{
    ResStreamHoldBuffer(loader, pData);
    pSlot->mpData = pData;
    pSlot->mReceived = 1;
}

void PlaTexCacheFinishReads(void)
{
    unsigned int player;
    unsigned int slot;
    int busy;

    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        busy = 0;
        for (slot = 0; slot < 32; slot++) {
            if (_PlaTexCache_aSlots[player][slot].mDirty) {
                if (_PlaTexCache_aSlots[player][slot].mReceived) {
                    if (_PlaTexCache_aSlots[player][slot].mRequested) {
                        TexMipmapRelocate(_PlaTexCache_aSlots[player][slot].mpData);
                        if (_PlaTexCache_aSlots[player][slot].mPalette != -1) {
                            int index = TexGetMaterialByIndex(_PlaTexCache_aSlots[player][slot].mpData, 0)->mUnknown8;

                            PlaDynClutApplyColors(TexGetPaletteByIndex(_PlaTexCache_aSlots[player][slot].mpData, index),
                                        _PlaTexCache_aSlots[player][slot].mPalette, _PlaTexCache_auColors[player]);
                        }
                        PlyrTexCopy(_PlaTexCache_apTextures[player][slot], _PlaTexCache_aSlots[player][slot].mpData,
                                    _PlaTexCache_auSizes[slot]);
                        if (slot == 4) {
                            PlaTexCacheOnHairLoaded(player, 4);
                        }
                        ResStreamReleaseBuffer(_PlaTexCache_iStream, _PlaTexCache_aSlots[player][slot].mpData);
                        _PlaTexCache_aSlots[player][slot].mpData = 0;
                        _PlaTexCache_aSlots[player][slot].mDirty = 0;
                        _PlaTexCache_iPending--;
                        _PlaTexCache_aSlots[player][slot].mRequested = 0;
                        _PlaTexCache_aSlots[player][slot].mReceived = 0;
                    } else {
                        ResStreamReleaseBuffer(_PlaTexCache_iStream, _PlaTexCache_aSlots[player][slot].mpData);
                        _PlaTexCache_aSlots[player][slot].mpData = 0;
                        _PlaTexCache_aSlots[player][slot].mReceived = 0;
                        _PlaTexCache_iPending--;
                    }
                }
                if (_PlaTexCache_aSlots[player][slot].mDirty) {
                    busy = 1;
                }
            }
        }
        if (!busy) {
            FEPlyrLoadFinish(player);
        }
    }
}

void PlaTexCacheRequestNext(void)
{
    unsigned int player;
    unsigned int i;
    unsigned int other;
    int slot;
    unsigned int id;
    int palette;

    if (_PlaTexCache_iPending == 1) {
        return;
    }

    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        slot = 32;
        id = 0xFFFFFFFF;
        palette = -1;
        for (i = 0; i < 32; i++) {
            if (_PlaTexCache_aSlots[player][i].mDirty && !_PlaTexCache_aSlots[player][i].mRequested) {
                if (slot == 32 || _PlaTexCache_aSlots[player][i].mId < id) {
                    palette = _PlaTexCache_aSlots[player][i].mPalette;
                    id = _PlaTexCache_aSlots[player][i].mId;
                    slot = i;
                }
            }
        }

        if (slot == 32) {
            continue;
        }

        /* Another player may already hold the same texture. */
        for (other = 0; other < _PlaTexCache_uPlayerCount; other++) {
            if (other != player && _PlaTexCache_aSlots[other][slot].mId == id &&
                _PlaTexCache_aSlots[other][slot].mPalette == palette && !_PlaTexCache_aSlots[other][slot].mDirty) {
                break;
            }
        }
        if (other < _PlaTexCache_uPlayerCount) {
            PlyrTexCopy(_PlaTexCache_apTextures[player][slot], _PlaTexCache_apTextures[other][slot], _PlaTexCache_auSizes[slot]);
            TexMipmapRelocate(_PlaTexCache_apTextures[player][slot]);
            if (_PlaTexCache_aSlots[player][slot].mPalette != -1) {
                int index = TexGetMaterialByIndex(_PlaTexCache_apTextures[player][slot], 0)->mUnknown8;

                PlaDynClutApplyColors(TexGetPaletteByIndex(_PlaTexCache_apTextures[player][slot], index),
                            _PlaTexCache_aSlots[player][slot].mPalette, _PlaTexCache_auColors[player]);
            }
            _PlaTexCache_aSlots[player][slot].mReceived = 0;
            _PlaTexCache_aSlots[player][slot].mDirty = 0;
            _PlaTexCache_aSlots[player][slot].mRequested = 0;
            continue;
        }

        /* Or another slot of the same player. */
        for (other = 0; other < 32; other++) {
            if (other != slot && _PlaTexCache_aSlots[player][other].mId == id &&
                _PlaTexCache_aSlots[player][other].mPalette == palette && !_PlaTexCache_aSlots[player][other].mDirty) {
                break;
            }
        }
        if (other < 32) {
            PlyrTexCopy(_PlaTexCache_apTextures[player][slot], _PlaTexCache_apTextures[player][other], _PlaTexCache_auSizes[slot]);
            TexMipmapRelocate(_PlaTexCache_apTextures[player][slot]);
            if (_PlaTexCache_aSlots[player][slot].mPalette != -1) {
                int index = TexGetMaterialByIndex(_PlaTexCache_apTextures[player][slot], 0)->mUnknown8;

                PlaDynClutApplyColors(TexGetPaletteByIndex(_PlaTexCache_apTextures[player][slot], index),
                            _PlaTexCache_aSlots[player][slot].mPalette, _PlaTexCache_auColors[player]);
            }
            _PlaTexCache_aSlots[player][slot].mReceived = 0;
            _PlaTexCache_aSlots[player][slot].mDirty = 0;
            _PlaTexCache_aSlots[player][slot].mRequested = 0;
            continue;
        }

        _PlaTexCache_aSlots[player][slot].mRequested = 1;
        _PlaTexCache_aSlots[player][slot].mReceived = 0;
        _PlaTexCache_iPending++;
        ResStreamQueueRead(_PlaTexCache_iStream, _PlaTexCache_pArchive, _PlaTexCache_aSlots[player][slot].mId, &_PlaTexCache_aSlots[player][slot]);
        if (_PlaTexCache_iPending == 1) {
            return;
        }
    }
}

void PlaTexCacheLoadSlotNow(int player, int slot, void *pData, int shared)
{
    if (!shared) {
        ResCopyToBuffer(_PlaTexCache_pArchive, _PlaTexCache_aSlots[player][slot].mId, pData);
        TexMipmapRelocate(pData);
    }
    PlyrTexCopy(_PlaTexCache_apTextures[player][slot], pData, _PlaTexCache_auSizes[slot]);
    if (slot == 4 && PlayerLookShowsHair(player)) {
        PlaTexCacheOnHairLoaded(player, 4);
    }
    if (_PlaTexCache_aSlots[player][slot].mPalette != -1) {
        PlaDynClutApplyColors(TexGetPaletteByIndex(_PlaTexCache_apTextures[player][slot], 0), _PlaTexCache_aSlots[player][slot].mPalette,
                    _PlaTexCache_auColors[player]);
    }
    _PlaTexCache_aSlots[player][slot].mRequested = _PlaTexCache_aSlots[player][slot].mReceived =
        _PlaTexCache_aSlots[player][slot].mDirty = 0;
}

void PlaTexCacheResetIds(int player)
{
    PlaTexCacheSlot_t defaults[32] = TEXTURE_SLOT_IDS;
    int i;

    for (i = 0; i < 32; i++) {
        _PlaTexCache_aSlots[player][i].mDirty = 1;
        _PlaTexCache_aSlots[player][i].mId = defaults[i].mId;
    }
}

void PlaTexCacheOpenArchive(int mode)
{
    int saved0 = 0;
    int saved1 = 0;

    if (FELoopIsMainFEActive() == 0) {
        saved0 = ResSetMemFlags(mode);
        saved1 = FileSetMemAllocFlags(mode);
    }
    _PlaTexCache_pArchive = ResOpenDevice(lbl_802EC080, 44);
    if (FELoopIsMainFEActive() == 0) {
        ResSetMemFlags(saved0);
        FileSetMemAllocFlags(saved1);
    }
}

void PlaTexCacheInit(unsigned int count)
{
    unsigned int player;
    unsigned int i;
    unsigned int offset;
    unsigned int size;
    unsigned char *pBase;
    int saved0 = 0;
    int saved1 = 0;

    _PlaTexCache_uPlayerCount = count;
    if (_PlaTexCache_bInitialized) {
        return;
    }

    if (_PlaTexCache_pArchive == 0) {
        PlaTexCacheOpenArchive(4);
    }
    _PlaTexCache_bInitialized = 1;

    offset = 0;
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        PlaTexCacheResetIds(player);
        for (i = 0; i < 32; i++) {
            if (player == 0) {
                size = ResGetSize(_PlaTexCache_pArchive, _PlaTexCache_aSlots[0][i].mId);
                _PlaTexCache_auSizes[i] = size;
            } else {
                size = _PlaTexCache_auSizes[i];
            }
            _PlaTexCache_aSlots[player][i].mPlayer = player;
            _PlaTexCache_aSlots[player][i].mSlot = i;
            _PlaTexCache_apTextures[player][i] = (unsigned char *)offset;
            _PlaTexCache_aSlots[player][i].mDirty = 1;
            _PlaTexCache_aSlots[player][i].mRequested = 0;
            _PlaTexCache_aSlots[player][i].mReceived = 0;
            offset += size + 32 - (size & 31);
            _PlaTexCache_aSlots[player][i].mPalette = -1;
            if (size > _PlaTexCache_uMaxSize) {
                _PlaTexCache_uMaxSize = size;
            }
        }
    }

    pBase = (unsigned char *)fn_801D2BB0(1, offset, 2, 0);
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            _PlaTexCache_apTextures[player][i] += (unsigned int)pBase;
        }
    }

    saved0 = ResSetMemFlags(4);
    saved1 = FileSetMemAllocFlags(4);
    BmFontLoad(&_PlaTexCache_Font, &_PlaTexCache_FontDesc, _PlaTexCache_pArchive, 1);
    ResSetMemFlags(saved0);
    FileSetMemAllocFlags(saved1);
}

void PlaTexCacheLoadDefaults(void)
{
    unsigned int i;
    unsigned int player;

    for (i = 0; i < 32; i++) {
        unsigned char *pDest = _PlaTexCache_apTextures[0][i];
        int id = _PlaTexCache_aSlots[0][i].mId;
        unsigned int size = ResGetSize(_PlaTexCache_pArchive, id);

        ResCopyToBuffer(_PlaTexCache_pArchive, id, pDest);
        for (player = 1; player < _PlaTexCache_uPlayerCount; player++) {
            memcpy(_PlaTexCache_apTextures[player][i], pDest, size);
        }
        for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
            TexMipmapRelocate(_PlaTexCache_apTextures[player][i]);
        }
    }
}

void PlaTexCacheShutdown(void)
{
    unsigned int player;
    int i;

    _PlaTexCache_bInitialized = 0;
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            _PlaTexCache_aSlots[player][i].mDirty = 1;
            _PlaTexCache_aSlots[player][i].mRequested = 0;
            _PlaTexCache_aSlots[player][i].mReceived = 0;
        }
    }
    fn_801D2BD0(_PlaTexCache_apTextures[0][0]);
    BmFontFree(&_PlaTexCache_Font);
}

void *PlaTexCacheGetArchive(void)
{
    return _PlaTexCache_pArchive;
}

void PlaTexCacheStart(void)
{
    unsigned int player;
    unsigned int i;

    _PlaTexCache_iStream = ResStreamOpen(1, 1, _PlaTexCache_uMaxSize, 100, PlaTexCacheOnStreamRead);
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            fn_802347EC(_PlaTexCache_apTextures[player][i], &_PlaTexCache_aDescs[player][i], 6, 0);
        }
    }
}

int PlaTexCacheCompareIds(const PlaTexCacheSortEntry_t *pA, const PlaTexCacheSortEntry_t *pB)
{
    return pA->mId - pB->mId;
}

void PlaTexCacheLoadAllNow(void)
{
    PlaTexCacheSortEntry_t entries[14 * 32];
    unsigned int count;
    unsigned int n;
    int i;
    unsigned int player;
    int id;
    int palette;
    void *pBuffer;

    ResTrackPause();
    n = 0;
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            if (_PlaTexCache_aSlots[player][i].mDirty == 1) {
                entries[n].mId = _PlaTexCache_aSlots[player][i].mId;
                entries[n].mSlot = _PlaTexCache_aSlots[player][i].mSlot;
                entries[n].mPlayer = _PlaTexCache_aSlots[player][i].mPlayer;
                n++;
            }
        }
    }

    count = n;
    if (n != 0) {
        SortArray(0, entries, n, 4, PlaTexCacheCompareIds, 0, 0, 1);
        id = -1;
        pBuffer = fn_801D2B7C(_PlaTexCache_uMaxSize, 0, 0);
        palette = -1;
        for (n = 0; n < count; n++) {
            i = entries[n].mSlot;
            player = entries[n].mPlayer;
            if (_PlaTexCache_aSlots[player][i].mId == id && _PlaTexCache_aSlots[player][i].mPalette == palette) {
                PlaTexCacheLoadSlotNow(player, i, pBuffer, 1);
            } else {
                PlaTexCacheLoadSlotNow(player, i, pBuffer, 0);
                id = _PlaTexCache_aSlots[player][i].mId;
                palette = _PlaTexCache_aSlots[player][i].mPalette;
            }
        }
        fn_801D2BD0(pBuffer);
    }
    ResTrackResume();
}

void PlaTexCacheSetSlot(int player, int slot, int id, int palette, int force)
{
    if (id == -1) {
        return;
    }
    if (!force && id == _PlaTexCache_aSlots[player][slot].mId && palette == _PlaTexCache_aSlots[player][slot].mPalette) {
        return;
    }
    _PlaTexCache_aSlots[player][slot].mPalette = palette;
    _PlaTexCache_aSlots[player][slot].mId = id;
    _PlaTexCache_aSlots[player][slot].mRequested = 0;
    _PlaTexCache_aSlots[player][slot].mDirty = 1;
}

void PlaTexCacheInvalidatePlayer(int player)
{
    unsigned int i;

    for (i = 0; i < 32; i++) {
        PlaTexCacheInvalidateSlot(player, i);
    }
}

void PlaTexCacheInvalidateSlot(int player, int slot)
{
    if (_PlaTexCache_aSlots[player][slot].mId == -1) {
        return;
    }
    _PlaTexCache_aSlots[player][slot].mRequested = 0;
    _PlaTexCache_aSlots[player][slot].mDirty = 1;
}

void PlaTexCacheStop(void)
{
    unsigned int player;
    unsigned int i;

    ResStreamReleaseAllBuffers(_PlaTexCache_iStream);
    ResStreamClose(_PlaTexCache_iStream);
    _PlaTexCache_iPending = 0;
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            PlyrTexFreeDesc(&_PlaTexCache_aDescs[player][i]);
        }
    }
}

ModelTexSlot_t *PlaTexCacheGetDescs(int player)
{
    return _PlaTexCache_aDescs[player];
}

int PlaTexCacheFindTexture(char *pName)
{
    char *pSpace = strchr(pName, ' ');

    if (pSpace) {
        *pSpace = 0;
    }
    return ResFindIndexByName(_PlaTexCache_pArchive, pName);
}

unsigned char *PlaTexCacheGetTexture(int player, int slot)
{
    return _PlaTexCache_apTextures[player][slot];
}

void PlaTexCacheSetColors(int player, unsigned char *pColors)
{
    int tint = 0;
    int other = 0;
    int i;

    for (i = 0; i < 25; i++) {
        if (_PlaTexCache_auColors[player][i] != pColors[i]) {
            _PlaTexCache_auColors[player][i] = pColors[i];
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
        PlaTexCacheInvalidatePlayer(player);
    } else if (tint) {
        PlaTexCacheInvalidateSlot(player, 4);
        PlaTexCacheInvalidateSlot(player, 6);
    }
}

void PlaTexCacheUpdate(void)
{
    PlaTexCacheFinishReads();
    PlaTexCacheRequestNext();
}

void PlaTexCacheWaitReads(void)
{
    while (_PlaTexCache_iPending > 0) {
        PlaTexCacheFinishReads();
    }
}

void PlaTexCacheSetFace(int player, const char *pName, int force)
{
    char name[38];
    int id;

    name[0] = 0;
    fn_801C2D88(name, sizeof(name), "PLATEX_FACE_%s", pName);
    id = PlaTexCacheFindTexture(name);
    if (id == -1) {
        id = PlaTexCacheFindTexture("PLATEX_TEMPLATE_FACE");
    }
    if (CheatFlagsIsSet(38) && GameModeTypeGet() == 0) {
        id = PlaTexCacheFindTexture("PLATEX_TEMPLATE_FACE");
    } else {
        PlaTexCacheSetSlot(player, 5, id, -1, force);
        PlaTexCacheSetSlot(player, 6, 0x354B, -1, force);
    }
}

int PlaTexCacheGetCapFaceId(int index)
{
    char name[32];
    int id;

    if (CheatFlagsIsSet(38) && GameModeTypeGet() == 0) {
        id = PlaTexCacheFindTexture("PLATEX_TEMPLATE_FACE");
    } else {
        name[0] = 0;
        fn_801C2D88(name, 24, "PLATEX_FACE_CAP%02d", index);
        id = PlaTexCacheFindTexture(name);
    }
    return id;
}

void PlaTexCacheSetCapFace(int player, int index, int row, int column, int force)
{
    int id = PlaTexCacheGetCapFaceId(index);

    if (id == -1) {
        id = PlaTexCacheFindTexture("PLATEX_TEMPLATE_FACE");
    }
    row = row * 3 + column + 0x33BA;
    PlaTexCacheSetSlot(player, 5, id, -1, force);
    PlaTexCacheSetSlot(player, 6, row, 0xA7, force);
}

void PlaTexCacheGetHairTexture(int style, int *pId, int *pPalette)
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

void PlaTexCacheDiscardRequests(void)
{
    unsigned int player;
    int i;

    while (_PlaTexCache_iPending > 0) {
        PlaTexCacheFinishReads();
    }
    for (player = 0; player < _PlaTexCache_uPlayerCount; player++) {
        for (i = 0; i < 32; i++) {
            if (_PlaTexCache_aSlots[player][i].mDirty && !_PlaTexCache_aSlots[player][i].mRequested) {
                _PlaTexCache_aSlots[player][i].mDirty = 0;
                _PlaTexCache_aSlots[player][i].mId = -1;
                _PlaTexCache_aSlots[player][i].mPalette = -1;
            }
        }
    }
}

void PlaTexCacheOnHairLoaded(int player, int slot)
{
}

void PlaTexCacheCloseArchive(void)
{
    ResClose(_PlaTexCache_pArchive);
    _PlaTexCache_pArchive = 0;
}

BmFont *PlaTexCacheGetFont(void)
{
    return &_PlaTexCache_Font;
}

}
