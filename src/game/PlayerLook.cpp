/* Player looks and player objects: the appearance record of each on-field player (name, skin,
   head, hair, number, body type, gear and decals), how it is read from the roster and applied to
   the player model, and the player object type. */
#include "engine/viewport.h"
#include "game/FaceFeatures.h"
#include "game/FELoop.h"
#include "game/PlyrNameTag.h"
#include "game/DbCursor.h"
#include "game/Object_8003DEC4.h"
#include "game/PlayerObjInit.h"
#include "game/Object_8008044C.h"
#include "game/PlayerLookRecord.h"
#include "game/GearDb.h"
#include "game/PlayerLook.h"
#include "game/PlaTex.h"
#include "game/StoryPlayerScreen.h"
#include "game/GameModeType.h"
#include <string.h>
#include <string.h>
#include "game/SyncRandGetRange.h"

/* Four bytes copied as one word from _PlayerLook_aDecalColors and passed by value. */
struct PlayerLookColors_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

/* Three bytes read by TeamDbGetColors. */
struct TeamColorRow_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

/* Key/value pair for PlyrSwitchSet; a key of 0xFFFF ends a list. */
struct PlayerLookSwitch_t {
    unsigned short mKey;
    unsigned short mValue;
};

/* Element of gPlayerLookBonuses (14 records of 0x18 bytes). */
struct PlayerLookBonuses_t {
    int mId;
    short mValues[10];
};

extern "C" unsigned char gPlayerLookColorRemap[18] = {
    0x14, 0x15, 0xF1, 0xF1, 0x14, 0x15, 0x16, 0x14, 0x15, 0x16, 0x14, 0x14, 0x14, 0x14, 0x14, 0x15, 0x14, 0x15,
};

static PlayerLookSwitch_t _PlayerLook_aDefaultSwitches[27] = {
    {5, 0}, {6, 0xFF}, {7, 0}, {8, 0}, {9, 0}, {0xA, 0}, {0xB, 0}, {0xC, 0}, {0xD, 0},
    {0xE, 0}, {0xF, 0}, {0x10, 0}, {0x11, 0}, {0x12, 0}, {0x13, 0xFF}, {0x14, 0xFF}, {0x1B, 0xFF}, {0, 0},
    {0x1C, 0xFF}, {0x19, 0xFF}, {0x15, 0xFF}, {0x16, 0xFF}, {0x17, 0xFF}, {0x18, 0xFF}, {0x1D, 0xFF}, {0x1E, 0xFF}, {0xFFFF, 0xFF},
};

static PlayerLookSwitch_t _PlayerLook_aaItemSwitches[45][9] = {
    {{5, 4}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 5}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 6}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 7}, {7, 2}, {8, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 7}, {6, 3}, {7, 2}, {8, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 0xA}, {7, 6}, {8, 6}, {0x18, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 0xB}, {7, 7}, {8, 7}, {9, 6}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 9}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 0xC}, {6, 2}, {7, 8}, {8, 8}, {9, 7}, {0xA, 5}, {0xB, 5}, {0xFFFF, 0xFF}, {0, 0}},
    {{5, 7}, {7, 4}, {8, 4}, {9, 4}, {0xA, 3}, {0xB, 3}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}},
    {{5, 7}, {6, 3}, {7, 4}, {8, 4}, {9, 4}, {0xA, 3}, {0xB, 3}, {0xFFFF, 0xFF}, {0, 0}},
    {{5, 8}, {7, 5}, {8, 5}, {9, 5}, {0xA, 4}, {0xB, 4}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}},
    {{5, 8}, {6, 1}, {7, 5}, {8, 5}, {9, 5}, {0xA, 4}, {0xB, 4}, {0xFFFF, 0xFF}, {0, 0}},
    {{5, 8}, {6, 0}, {7, 5}, {8, 5}, {9, 5}, {0xA, 4}, {0xB, 4}, {0, 0xFF}, {0xFFFF, 0xFF}},
    {{0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 3}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 0}, {7, 0}, {8, 0}, {9, 0}, {0xA, 0}, {0xB, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}},
    {{5, 0}, {7, 0}, {8, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{5, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{7, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{8, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{9, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{9, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xA, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xB, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xA, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xB, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{9, 9}, {0xA, 6}, {0xB, 6}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{9, 8}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xE, 1}, {0xF, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xE, 0}, {0xF, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0xE, 3}, {0xF, 4}, {0x10, 2}, {0x11, 2}, {0x12, 2}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}},
    {{0xE, 2}, {0xF, 3}, {0x10, 1}, {0x11, 1}, {0x12, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}},
    {{0x11, 3}, {0x12, 3}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x12, 4}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x11, 4}, {0x12, 5}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x1B, 0}, {0, 1}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x1B, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x1C, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x1D, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0x1E, 0}, {0xFFFF, 0xFF}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
};

static int _PlayerLook_aiItemSwitchList[54] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 255, 24, 25, 255, 255, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 40, 40, 41, 41, 40, 40, 40, 42, 42, 42, 42, 42, 255, 255, 43, 44,
};

static PlayerLookColors_t _PlayerLook_aDecalColors[22] = {
    {0x11, 0x10, 0x10, 0x13}, {0xFF, 0xFF, 0xFF, 0x17}, {0x19, 0x18, 0x1A, 0x1B}, {0x1D, 0x1C, 0x1E, 0x1F}, {0x1D, 0x1C, 0x1E, 0x1F}, {0xFF, 0xFF, 0xFF, 0xFF}, {0x2D, 0x2C, 0x2E, 0xFF}, {0x25, 0x24, 0x26, 0xFF},
    {0x31, 0x30, 0x30, 0x33}, {0x1D, 0x1C, 0x1E, 0x1F}, {0x1D, 0x1C, 0x1E, 0x1F}, {0x21, 0x20, 0x20, 0x23}, {0x21, 0x20, 0x20, 0x23}, {0x21, 0x20, 0x20, 0x23}, {0xFF, 0xFF, 0xFF, 3}, {0xD, 0xC, 0xE, 0xFF},
    {1, 0, 2, 3}, {1, 0, 2, 3}, {1, 0, 2, 3}, {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}, {9, 8, 0xA, 0xB},
};

static int _PlayerLook_aiListLogoKind[22] = {
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 0,
};

extern "C" {
extern PlayerLook_t gPlayerLooks[14];
extern PlayerLookBonuses_t gPlayerLookBonuses[14];
extern unsigned char gPlayerObjDrawReady;

int MsgPlayerPickupIsOpen(void);
int PlyrObjsGetCount(void);
void PlyrPoseInit(Object_8003DEC4 *pPlayer, int a, void *b, int c, int d);
void PlyrPoseFree(Object_8003DEC4 *pPlayer);
unsigned char CheatFlagsIsSet(int index);
int StoryEventsGetCurrentEvent(void);
void GearDbOpen(DbCursor *pObject);
void GearDbOpenType(DbCursor *pObject, int a);
void GearDbClose(DbCursor *pObject);
int GearDbSeekTypeId(DbCursor *pCursor, int a, int b, int *pResult);
int GearDbGetSlotType(int index);
int GameInfoGet(int index);
int PlayerDbGetTeamIndex(Object_8008044C *pObject);
void PlayerDbGetNickname(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbGetPrty(Object_8008044C *pObject);
int PlayerDbGetPlex(Object_8008044C *pObject);
int PlayerDbGetPlht(Object_8008044C *pObject);
int PlayerDbGetHairStyle(Object_8008044C *pObject);
int PlayerDbGetPjen(Object_8008044C *pObject);
void PlayerGearGetScaledBonuses(Object_8008044C *pObject, short *pValues);
void PlayerDbReadHairColors(Object_8008044C *pObject, unsigned char *p);
void fn_80081CDC(void);
void fn_80081D24(void);
int fn_80081D4C(Object_8008044C *pObject, unsigned char *p);
int fn_80081E3C(Object_8008044C *pObject);
int fn_80081FD4(Object_8008044C *pObject, int a);
int fn_80082280(Object_8008044C *pObject);
int fn_800822D4(Object_8008044C *pObject);
void TeamDbGetColors(DbCursor *pObject, void *pBuffer);
void ParticleTrailReset(ParticleTrailSet_t *pObject);
void fn_8015F6E8(const char *pName, int b, int c, int d, PlayerHeadIds_t *pIds);
void PlyrSwitchSet(int player, int key, int value);
void PlaTexCacheSetSlot(int index, int slot, int id, int palette, int d);
int PlaTexCacheFindTexture(char *pName);
void PlaTexCacheSetColors(int index, unsigned char *pColors);
void PlaTexCacheGetHairTexture(int a, int *pId, int *pPalette);
int EditMenuIsOpen(void);
void PlyrRenderInit(int a, int b, int c, int d);
void PlyrRenderShutdown(void);
void PlyrRenderInitPlayer(Object_8003DEC4 *pPlayer, PlayerObjInit_t *pInit);
void PlyrRenderDrawPlayer(Object_8003DEC4 *pPlayer);
void PlyrRenderFreePlayer(Object_8003DEC4 *pPlayer);
void PlyrTexRequestNameplate(Object_8003DEC4 *pPlayer);
int fn_801486A0(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int ObjNewType_(int a, int b, int c, void (*pA)(Object_8003DEC4 *, PlayerObjInit_t *), void (*pB)(Object_8003DEC4 *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(Object_8003DEC4 *, int));
}

static Object_8008044C _PlayerLook_sPlayerCursor;
static DbCursor _PlayerLook_sGearCursor;

extern "C" void PlayerLookRandomizeGear(int index)
{
    int a = 0;
    int b;
    int c;
    DbCursor cursor;

    GearDbOpenType(&cursor, 11);
    a = DbCursorGetRowCount(&cursor);
    GearDbClose(&cursor);
    GearDbOpenType(&cursor, 12);
    b = DbCursorGetRowCount(&cursor);
    GearDbClose(&cursor);
    GearDbOpenType(&cursor, 1);
    c = DbCursorGetRowCount(&cursor);
    GearDbClose(&cursor);
    int x = SyncRandGetRange(0, a - 1) + 1;
    int y = SyncRandGetRange(0, b);
    int z = SyncRandGetRange(0, c - 1) + 1;
    gPlayerLooks[index].mInfo.mValues[12] = x;
    gPlayerLooks[index].mInfo.mValues[13] = y;
    gPlayerLooks[index].mInfo.mValues[1] = z;
}

extern "C" void PlayerLookApplySwitchList(int player, int index)
{
    PlayerLookSwitch_t pair;
    int i;

    for (i = 0, pair = _PlayerLook_aaItemSwitches[index][0]; pair.mKey != 0xFFFF; pair = _PlayerLook_aaItemSwitches[index][++i]) {
        PlyrSwitchSet(player, pair.mKey, pair.mValue);
    }
}

extern "C" void PlayerLookApplyItemSwitches(GearRow_t *pRow, PlayerGear_t *pInfo, int player, int slot)
{
    int type = pRow->mUnknown64;

    if (type == 63) {
        return;
    }
    if ((unsigned int)type > 53) {
        return;
    }
    switch (type) {
    case 22:
        if (pInfo->mUnknown00 & 1) {
            PlayerLookApplySwitchList(player, 22);
        }
        if (pInfo->mUnknown00 & 2) {
            PlayerLookApplySwitchList(player, 23);
        }
        break;
    case 25:
        if (pInfo->mUnknown01 & 1) {
            PlayerLookApplySwitchList(player, 26);
        }
        if (pInfo->mUnknown01 & 2) {
            PlayerLookApplySwitchList(player, 27);
        }
        break;
    case 26:
        if (pInfo->mUnknown01 & 1) {
            PlayerLookApplySwitchList(player, 28);
        }
        if (pInfo->mUnknown01 & 2) {
            PlayerLookApplySwitchList(player, 29);
        }
        break;
    default:
        if (_PlayerLook_aiItemSwitchList[pRow->mUnknown64] != 255) {
            PlayerLookApplySwitchList(player, _PlayerLook_aiItemSwitchList[pRow->mUnknown64]);
        }
        break;
    }
}

extern "C" void PlayerLookSetNumberIds(int base, unsigned int number, unsigned char home, int player, int *pIds, int *pPalettes, int kind)
{
    int id;
    int numberId;

    number--;
    if (kind == 3) {
        int partial;
        unsigned int offset;

        numberId = number + 0x3BDD;
        offset = number * 200;
        partial = !home ? offset + 0x1969 : offset + 0x1905;
        id = partial + base;
        pIds[23] = numberId;
        pIds[24] = id;
        pPalettes[23] = -1;
        pPalettes[24] = -1;
        switch (number + 1) {
        case 26:
            PlyrSwitchSet(player, 22, 255);
            PlyrSwitchSet(player, 21, 2);
            break;
        case 15:
        case 25:
        case 27:
            PlyrSwitchSet(player, 22, 0);
            PlyrSwitchSet(player, 21, 0);
            break;
        case 7:
            if (home == 0) {
                PlyrSwitchSet(player, 22, 0);
                PlyrSwitchSet(player, 21, 1);
                break;
            }
        case 1:
        case 3:
        case 8:
        case 9:
        case 10:
        case 23:
        case 30:
            PlyrSwitchSet(player, 22, 255);
            PlyrSwitchSet(player, 21, 2);
            break;
        case 6:
        case 12:
        case 14:
        case 17:
        case 21:
        case 22:
        case 24:
        case 28:
        case 31:
        case 32:
            PlyrSwitchSet(player, 22, 0);
            PlyrSwitchSet(player, 21, 1);
            break;
        case 2:
        case 4:
        case 5:
        case 11:
        case 13:
        case 16:
        case 18:
        case 19:
        case 20:
        case 29:
            PlyrSwitchSet(player, 22, 0);
            PlyrSwitchSet(player, 21, 255);
            break;
        }
    } else {
        int partial;
        unsigned int offset;

        numberId = number + 0x3BDD;
        offset = number * 200;
        partial = !home ? offset + 0x69 : offset + 5;
        id = partial + base;
        pIds[23] = numberId;
        pIds[24] = id;
        pPalettes[23] = -1;
        pPalettes[24] = -1;
        switch (number + 1) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 22:
        case 23:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            PlyrSwitchSet(player, 22, 0);
            PlyrSwitchSet(player, 21, 255);
            break;
        case 8:
        case 10:
        case 21:
        case 24:
            PlyrSwitchSet(player, 22, 255);
            PlyrSwitchSet(player, 21, 255);
            break;
        }
    }
    PlyrSwitchSet(player, 23, 0);
}

extern "C" void PlayerLookSetJerseyDecal(GearRow_t *pRow, int offset, unsigned char flag, int player, int *pIds, int *pPalettes)
{
    char name[82];
    int id;

    fn_801C2D88(name, sizeof(name), "PLATEX_DECAL_%s_CHICAGO", pRow->mName);
    id = PlaTexCacheFindTexture(name);
    if (id >= 0) {
        id += offset;
        pIds[23] = id;
        pIds[24] = id;
        pPalettes[23] = -1;
        pPalettes[24] = -1;
        PlayerLookColors_t colors = _PlayerLook_aDecalColors[pRow->mUnknown64];
        if (pRow->mUnknown71) {
            if (pRow->mUnknown72) {
                PlyrSwitchSet(player, 19, colors.mUnknown3);
            } else {
                PlyrSwitchSet(player, 19, colors.mUnknown1);
            }
        }
        if (pRow->mUnknown70) {
            PlyrSwitchSet(player, 20, colors.mUnknown1);
        }
    }
}

extern "C" void PlayerLookSetHeadDecal(GearRow_t *pRow, int offset, int player, int *pIds, int *pPalettes)
{
    char name[82];
    int id;

    fn_801C2D88(name, sizeof(name), "PLATEX_DECAL_%s_CHICAGO", pRow->mName);
    id = PlaTexCacheFindTexture(name);
    if (id >= 0) {
        if (strncmp(pRow->mName, "REEBOK_T045Z", 33) == 0 || strncmp(pRow->mName, "REEBOK_BO04A381", 33) == 0) {
            pIds[3] = 3;
            pPalettes[2] = -1;
        } else {
            pIds[3] = 4;
            pPalettes[2] = -1;
        }
        id += offset;
        pIds[2] = id;
        pPalettes[2] = -1;
        PlyrSwitchSet(player, 25, 0);
        PlyrSwitchSet(player, 26, 0);
    }
}

extern "C" void PlayerLookSetBackArtId(int number, int player, int *pId, int *pPalette)
{
    *pId = number + 0x3FEE;
    *pPalette = -1;
    PlyrSwitchSet(player, 20, 1);
}

extern "C" void PlayerLookSetDecal(int kind, int key, PlayerLookColors_t colors, unsigned char number, unsigned int index,
                            unsigned char flag, unsigned char home, unsigned char single, int player, int *pId,
                            int *pPalette)
{
    unsigned char c1 = colors.mUnknown1;
    unsigned char c0 = colors.mUnknown0;
    unsigned char c2 = colors.mUnknown2;
    unsigned int id;

    if (single) {
        c1 = colors.mUnknown3;
        c0 = c1;
        c2 = c1;
    }
    switch (kind) {
    case 0:
        break;
    case 1:
        if (number > 99) {
            number = 0;
        }
        *pId = number + 0x3B10;
        *pPalette = 0xAB;
        PlyrSwitchSet(player, key, c2);
        break;
    case 2:
        if (home) {
            *pId = index + 0x3B97;
        } else {
            *pId = index + 0x3B74;
        }
        *pPalette = -1;
        PlyrSwitchSet(player, key, c0);
        break;
    case 3:
        *pId = index + 0x3BBA;
        *pPalette = 0xA9;
        PlyrSwitchSet(player, key, c1);
        break;
    case 4:
        *pId = index + 0x3BBA;
        *pPalette = 0xA9;
        PlyrSwitchSet(player, key, c0);
        break;
    case 5:
        id = index + 0x3BDD;
        *pId = id;
        if (id > 0x3C60) {
            *pId = 0x3C0A;
        }
        *pPalette = flag ? -1 : 0xAD;
        PlyrSwitchSet(player, key, c1);
        break;
    default:
        *pId = kind + 0x31FF;
        *pPalette = -1;
        PlyrSwitchSet(player, key, c1);
        break;
    }
}

extern "C" void PlayerLookSetJerseyDecals(GearRow_t *pRow, PlayerGear_t *pInfo, unsigned char number, int index,
                            unsigned char flag, unsigned char home, int player, int *pIds, int *pPalettes)
{
    if (PlaTexIsNumberItem(pRow)) {
        PlayerLookSetNumberIds(number, pRow->mUnknown78, home, player, pIds, pPalettes, pRow->mUnknown08);
    } else if (pRow->mUnknown76) {
        PlayerLookSetJerseyDecal(pRow, pInfo->mUnknown0C, home, player, pIds, pPalettes);
    } else {
        PlayerLookColors_t colors = _PlayerLook_aDecalColors[pRow->mUnknown64];
        int kind;

        kind = pRow->mUnknown71 ? pInfo->mUnknown09 : 0;
        PlayerLookSetDecal(kind, 19, colors, number, index, flag, home, pRow->mUnknown72, player, &pIds[23], &pPalettes[23]);
        if (pInfo->mValues[10] == 0 && pInfo->mUnknown08 != 0 && home != 0) {
            PlayerLookSetBackArtId(pInfo->mUnknown08, player, &pIds[24], &pPalettes[24]);
        } else {
            kind = pRow->mUnknown70 && pInfo->mValues[10] ? pInfo->mUnknown0A : 0;
            PlayerLookSetDecal(kind, 20, colors, number, index, flag, home, 0, player, &pIds[24], &pPalettes[24]);
        }
    }
}

extern "C" void PlayerLookLoadDecalColors(int index, unsigned char *pColors, unsigned char flag)
{
    DbCursor cursor;
    TeamQuery query;
    TeamColorRow_t rgb;

    query.mUnknown8 = index + 1;
    query.mUnknown4 = 5;
    TeamDbOpen(&cursor, &query, 0x54415453);
    TeamDbGetColors(&cursor, &rgb);
    TeamDbClose(&cursor);
    pColors[4] = rgb.mUnknown0;
    pColors[5] = rgb.mUnknown1;
    pColors[6] = rgb.mUnknown2;
    PlaTexApplyAwayColors(pColors, flag);
}

extern "C" void PlayerLookLoadHeadDecalColors(int index, unsigned char *pColors, unsigned char flag)
{
    DbCursor cursor;
    TeamQuery query;
    TeamColorRow_t rgb;

    query.mUnknown8 = index + 1;
    query.mUnknown4 = 5;
    TeamDbOpen(&cursor, &query, 0x54415453);
    TeamDbGetColors(&cursor, &rgb);
    TeamDbClose(&cursor);
    pColors[0] = rgb.mUnknown0;
    pColors[1] = rgb.mUnknown1;
}

extern "C" int PlayerLookMapHatKind(unsigned int type)
{
    switch (type) {
    case 37:
        return 1;
    case 38:
        return 4;
    case 39:
        return 5;
    case 40:
        return 6;
    case 41:
        return 7;
    case 42:
        return 12;
    case 43:
        return 13;
    case 44:
        return 14;
    case 50:
        return 15;
    case 51:
        return 16;
    case 63:
        return 0;
    default:
        return 0;
    }
}

extern "C" int PlayerLookItemKeepsLogo(int type)
{
    return _PlayerLook_aiListLogoKind[_PlayerLook_aiItemSwitchList[type]] == 1;
}

extern "C" int PlayerLookGetHatKind(int index)
{
    int result;

    GearDbSeekTypeId(&_PlayerLook_sGearCursor, 9, gPlayerLooks[index].mInfo.mValues[10], 0);
    if (GearDbGetGrsi(&_PlayerLook_sGearCursor) == 13) {
        result = 0;
    } else {
        GearDbSeekTypeId(&_PlayerLook_sGearCursor, 0, gPlayerLooks[index].mInfo.mValues[0], 0);
        result = PlayerLookMapHatKind(GearDbGetGrsi(&_PlayerLook_sGearCursor));
    }
    return result;
}

extern "C" int PlayerLookGetSlot1Kind(int index)
{
    GearDbSeekTypeId(&_PlayerLook_sGearCursor, 1, gPlayerLooks[index].mInfo.mValues[1], 0);
    switch (GearDbGetGrsi(&_PlayerLook_sGearCursor)) {
    case 45:
        return 1;
    case 46:
        return 2;
    case 47:
        return 3;
    case 48:
        return 4;
    case 49:
        return 5;
    case 63:
        return 0;
    default:
        return 0;
    }
}

extern "C" void PlayerLookGetAccessoryIds(int *pId, int *pPalette, int a, int b)
{
    int even = 0;

    *pId = b + 0x3AEF;
    if (b == 2 || b == 4 || b == 6 || b == 8) {
        even = 1;
    }
    if (a == 0) {
        *pPalette = 0x3563;
        return;
    }
    *pPalette = (a - 1) * 2 + 0x3AF8 + even;
}

extern "C" void PlayerLookLoad(int index, int unused, int id, unsigned char flag)
{
    DbCursor cursor;
    FaceFeatures_t block;
    int value;
    unsigned char *pColors = gPlayerLooks[index].mUnknown7A;
    PlayerLook_t *pRecord;

    PlayerDbSeekId(&_PlayerLook_sPlayerCursor, id, 0);
    value = PlayerDbGetTeamIndex(&_PlayerLook_sPlayerCursor);
    TeamDbOpen(&cursor, 0, 0x54415453);
    TeamDbSeekId(&cursor, value, 0);
    TeamDbGetColors(&cursor, &pColors[20]);
    gPlayerLooks[index].mUnknown6A = TeamDbGetLogo(&cursor);
    gPlayerLooks[index].mUnknown68 = TeamDbGetCtdl(&cursor);
    TeamDbClose(&cursor);
    PlayerDbReadGear(&_PlayerLook_sPlayerCursor, &gPlayerLooks[index].mInfo);
    if (CheatFlagsIsSet(47) && !GameModeTypeGet()) {
        PlayerLookRandomizeGear(index);
    }
    pRecord = &gPlayerLooks[index];
    PlayerDbGetNickname(&_PlayerLook_sPlayerCursor, pRecord->mName, 31);
    pRecord->mUnknown72 = fn_80081E3C(&_PlayerLook_sPlayerCursor) + 1;
    pRecord->mUnknown73 = fn_80082280(&_PlayerLook_sPlayerCursor);
    pRecord->mUnknown74 = fn_800822D4(&_PlayerLook_sPlayerCursor);
    pRecord->mUnknown6C = PlayerDbGetPlht(&_PlayerLook_sPlayerCursor);
    pRecord->mUnknown6E = PlayerDbGetHairStyle(&_PlayerLook_sPlayerCursor);
    pRecord->mUnknown77 = PlayerDbGetPjen(&_PlayerLook_sPlayerCursor);
    pRecord->mUnknown93 = flag;
    pRecord->mUnknown78 = PlayerDbGetPybt(&_PlayerLook_sPlayerCursor);
    pRecord->mUnknown76 = PlayerDbGetPlex(&_PlayerLook_sPlayerCursor);
    if (PlayerDbGetPrty(&_PlayerLook_sPlayerCursor)) {
        fn_80082138(&_PlayerLook_sPlayerCursor, &block);
        PlayerLookSetFeatures(index, &block);
        pRecord->mInfo.mUnknown03 = FaceMorphIsAllowed(&block);
    } else {
        PlayerLookSetFeatures(index, 0);
    }
    gPlayerLooks[index].mUnknown70 = PlayerLookGetHatKind(index);
    gPlayerLooks[index].mUnknown75 = PlayerLookGetSlot1Kind(index);
    PlayerDbReadHairColors(&_PlayerLook_sPlayerCursor, &pColors[18]);
    if (!fn_80081D4C(&_PlayerLook_sPlayerCursor, pColors)) {
        PlaTexRemapColors(pColors);
        PlaTexApplyAwayColors(pColors, gPlayerLooks[index].mUnknown93);
    }
}

extern "C" void PlayerLookOpen(void)
{
    PlayerCursorOpen(&_PlayerLook_sPlayerCursor, 0, FELoopIsMainFEActive() ? 0x54415453 : 0x454D4147);
    fn_80081CDC();
    GearDbOpen(&_PlayerLook_sGearCursor);
}

extern "C" void PlayerLookClose(void)
{
    GearDbClose(&_PlayerLook_sGearCursor);
    fn_80081D24();
    PlayerCursorClose(&_PlayerLook_sPlayerCursor);
}

extern "C" void PlayerLookSetName(int index, const char *pName)
{
    strnzcpy(gPlayerLooks[index].mName, pName, 31);
}

extern "C" void PlayerLookSetHeadDecalColors(int index, int value)
{
    gPlayerLooks[index].mInfo.mUnknown0D = value;
}

extern "C" void PlayerLookSetDecalColors(int index, int value)
{
    gPlayerLooks[index].mInfo.mUnknown0C = value;
}

extern "C" void PlayerLookSetLogo(int index, int value)
{
    gPlayerLooks[index].mUnknown6A = value;
}

extern "C" void PlayerLookLoadBonuses(int index, int unused, int id)
{
    Object_8008044C cursor;
    int i;

    PlayerCursorOpenDefault(&cursor, 0);
    gPlayerLookBonuses[index].mId = id;
    if (PlayerDbSeekId(&cursor, id, 0)) {
        PlayerGearGetScaledBonuses(&cursor, gPlayerLookBonuses[index].mValues);
    } else {
        for (i = 9; i >= 0; i--) {
            gPlayerLookBonuses[index].mValues[i] = 0;
        }
    }
    PlayerCursorClose(&cursor);
}

extern "C" void PlayerLookSetGear(int player, int slot, int value)
{
    Object_8003DEC4 *pPlayer = PlyrObjsGet(player);

    gPlayerLooks[pPlayer->mUnknown4971].mInfo.mValues[slot] = value;
    gPlayerLooks[pPlayer->mUnknown4971].mUnknown70 = PlayerLookGetHatKind(pPlayer->mUnknown4971);
    gPlayerLooks[pPlayer->mUnknown4971].mUnknown75 = PlayerLookGetSlot1Kind(pPlayer->mUnknown4971);
}

extern "C" void PlayerLookApply(int player)
{
    int ids[32];
    int palettes[32];
    GearRow_t row;
    PlayerLookColors_t colors;
    int id;
    int palette;
    int id2;
    int palette2;
    int clearLogo;
    Object_8003DEC4 *pPlayer;
    unsigned char key;
    unsigned char index;
    int i;
    int slot;
    PlayerLook_t *pRecord;
    unsigned char *pColors;

    pPlayer = PlyrObjsGet(player);
    clearLogo = 0;
    key = pPlayer->mUnknown4970;
    index = pPlayer->mUnknown4971;
    for (i = 0; i < 32; i++) {
        if (i != 31) {
            ids[i] = -1;
            palettes[i] = -1;
        }
    }
    ids[25] = 0x3EEC;
    ids[26] = 0x3DE1;
    ids[27] = 0x3EED;
    ids[28] = 0x3DE2;
    ids[29] = 0x3EEE;
    ids[30] = 0x3DE3;
    for (i = 0; _PlayerLook_aDefaultSwitches[i].mKey != 0xFFFF; i++) {
        PlyrSwitchSet(key, _PlayerLook_aDefaultSwitches[i].mKey, _PlayerLook_aDefaultSwitches[i].mValue);
    }
    pColors = gPlayerLooks[index].mUnknown7A;
    PlaTexRemapColors(pColors);
    PlaTexApplyAwayColors(pColors, gPlayerLooks[index].mUnknown93);
    for (slot = 0; slot <= 13; slot++) {
        GearDbSeekTypeId(&_PlayerLook_sGearCursor, GearDbGetSlotType(slot), gPlayerLooks[index].mInfo.mValues[slot], 0);
        GearDbReadRow(&_PlayerLook_sGearCursor, &row);
        PlaTexBuildPartIds(&row, &gPlayerLooks[index], ids, palettes, slot);
        PlayerLookApplyItemSwitches(&row, &gPlayerLooks[index].mInfo, key, slot);
        if (slot == 10) {
            if (row.mUnknown64 == 13) {
                gPlayerLooks[index].mUnknown95 = 1;
            } else {
                gPlayerLooks[index].mUnknown95 = 0;
            }
            PlayerLookSetJerseyDecals(&row, &gPlayerLooks[index].mInfo, gPlayerLooks[index].mUnknown77,
                        gPlayerLooks[index].mUnknown6A - 1, gPlayerLooks[index].mUnknown68,
                        gPlayerLooks[index].mUnknown93, key, ids, palettes);
            if (row.mUnknown76) {
                PlayerLookLoadDecalColors(gPlayerLooks[index].mInfo.mUnknown0C, gPlayerLooks[index].mUnknown7A,
                            gPlayerLooks[index].mUnknown93);
            }
            clearLogo = PlayerLookItemKeepsLogo(row.mUnknown64) == 0;
        } else if (slot == 0) {
            unsigned char type;

            colors.mUnknown1 = 0;
            colors.mUnknown0 = 0;
            colors.mUnknown3 = 255;
            colors.mUnknown2 = 0;
            type = gPlayerLooks[index].mInfo.mUnknown0B;
            if (row.mUnknown76) {
                PlayerLookSetHeadDecal(&row, gPlayerLooks[index].mInfo.mUnknown0D, key, ids, palettes);
                PlayerLookLoadHeadDecalColors(gPlayerLooks[index].mInfo.mUnknown0D, gPlayerLooks[index].mUnknown7A, gPlayerLooks[index].mUnknown93);
            } else {
                if (strncmp(row.mName, "SKULLCAP_BLACK_L", 16) == 0) {
                    ids[2] = 0x3216;
                    palettes[2] = -1;
                    PlyrSwitchSet(key, 25, colors.mUnknown1);
                } else if (strncmp(row.mName, "SKULLCAP_WHITE_L", 16) == 0) {
                    ids[2] = 0x3215;
                    palettes[2] = -1;
                    PlyrSwitchSet(key, 25, colors.mUnknown1);
                } else {
                    PlayerLookSetDecal(type, 25, colors, gPlayerLooks[index].mUnknown77, gPlayerLooks[index].mUnknown6A - 1,
                                gPlayerLooks[index].mUnknown68, gPlayerLooks[index].mUnknown93, 0, key, &ids[2], &palettes[2]);
                }
                PlyrSwitchSet(key, 26, 255);
            }
        }
    }
    if (clearLogo) {
        ids[10] = -1;
        palettes[10] = -1;
    }
    PlaTexBuildDefaultIds(ids, &gPlayerLooks[index]);
    for (i = 0; i <= 31; i++) {
        if (i != 31) {
            PlaTexCacheSetSlot(index, i, ids[i], palettes[i], 0);
        }
    }
    PlaTexCacheSetColors(index, gPlayerLooks[index].mUnknown7A);
    if (ids[4] == -1) {
        PlaTexCacheGetHairTexture(gPlayerLooks[index].mUnknown6E, &id, &palette);
        PlaTexCacheSetSlot(index, 4, id, palette, 0);
    }
    pRecord = &gPlayerLooks[index];
    if (pRecord->mUnknown95) {
        PlyrSwitchSet(key, 0, 255);
        PlyrSwitchSet(key, 27, 255);
        PlyrSwitchSet(key, 25, 255);
        PlyrSwitchSet(key, 26, 255);
    }
    if (pRecord->mUnknown70 != 15 && pRecord->mUnknown70 != 16 && !pRecord->mUnknown95) {
        pRecord->mUnknown94 = 1;
    } else {
        gPlayerLooks[index].mUnknown94 = 0;
    }
    PlyrSwitchSet(key, 29, 255);
    PlyrSwitchSet(key, 30, 255);
    if (gPlayerLooks[index].mInfo.mValues[12]) {
        PlyrSwitchSet(key, 29, 0);
        if (gPlayerLooks[index].mInfo.mValues[13]) {
            PlyrSwitchSet(key, 30, 0);
        }
        PlayerLookGetAccessoryIds(&id2, &palette2, gPlayerLooks[index].mInfo.mValues[13], gPlayerLooks[index].mInfo.mValues[12]);
        PlaTexCacheSetSlot(index, 7, id2, -1, 0);
        PlaTexCacheSetSlot(index, 8, palette2, -1, 0);
    }
    strnzcpy(pPlayer->mUnknown4184, gPlayerLooks[index].mName, 31);
    PlyrTexRequestNameplate(pPlayer);
}

extern "C" void PlayerLookLoadForPlayer(unsigned int mode, int index, int unused, int id)
{
    int flag = 1;

    if (FELoopIsMainFEActive() && MsgPlayerPickupIsOpen() && StoryEventsGetCurrentEvent()) {
        DbCursor cursor;

        DbCursorOpen(&cursor, 0x59414C50, 0x44494750, 0, 0, 0x54415453);
        if (PlayerDbSeekId((Object_8008044C *)&cursor, id, 0)) {
            flag = fn_80081FD4((Object_8008044C *)&cursor, 1) == 0;
        }
        DbCursorClose(&cursor);
    } else if ((FELoopIsMainFEActive() && (EditMenuIsOpen() || StoryPlayerScreenIsActive())) || !fn_801486A0()) {
        flag = 1;
    } else if (GameInfoGet(2) == 0) {
        flag = mode <= 6;
    } else {
        flag = mode > 6;
    }
    PlayerLookLoad(index, unused, id, flag);
}

extern "C" void PlayerLookGetBonuses(int unused, int id, unsigned short *pValues)
{
    unsigned int i;
    int j;

    for (i = 0; i <= 13; i++) {
        if (gPlayerLookBonuses[i].mId == id) {
            break;
        }
    }
    if (i <= 13) {
        for (j = 0; j < 10; j++) {
            pValues[j] = gPlayerLookBonuses[i].mValues[j];
        }
    } else {
        for (j = 0; j < 10; j++) {
            *pValues++ = 0;
        }
    }
}

extern "C" int PlayerLookGetHatModel(int index)
{
    int kind;
    unsigned char style = gPlayerLooks[index].mInfo.mUnknown02;
    unsigned short type = gPlayerLooks[index].mUnknown70;

    if (type != 0 && type != 16 && type != 15) {
        switch (type) {
        case 1:
            switch (style) {
            case 0:
                kind = 1;
                break;
            case 1:
                kind = 2;
                break;
            case 2:
                kind = 3;
                break;
            default:
                kind = gPlayerLooks[index].mUnknown70;
                break;
            }
            break;
        case 7:
            switch (style) {
            case 0:
                kind = 7;
                break;
            case 2:
                kind = 8;
                break;
            case 3:
                kind = 9;
                break;
            case 5:
                kind = 10;
                break;
            case 1:
                kind = 11;
                break;
            default:
                kind = gPlayerLooks[index].mUnknown70;
                break;
            }
            break;
        default:
            kind = gPlayerLooks[index].mUnknown70;
            break;
        }
        return (kind - 1) * 14 + gPlayerLooks[index].mUnknown6C * 2 + 1;
    }
    return 3;
}

extern "C" int PlayerLookGetSlot1Model(int index)
{
    PlayerLook_t *pRecord = &gPlayerLooks[index];

    if (pRecord->mUnknown75 != 0) {
        return (pRecord->mUnknown75 - 1) * 8 + pRecord->mInfo.mUnknown03 * 2 + 1;
    }
    return 1;
}

extern "C" int PlayerLookGetAccessoryModel(int index)
{
    GearRow_t row;
    unsigned int a = gPlayerLooks[index].mInfo.mValues[12];
    unsigned int b = gPlayerLooks[index].mInfo.mValues[13];
    int result;

    if (a == 0) {
        result = 0x151;
    } else {
        GearDbSeekTypeId(&_PlayerLook_sGearCursor, 9, gPlayerLooks[index].mInfo.mValues[10], 0);
        GearDbReadRow(&_PlayerLook_sGearCursor, &row);
        result = (a - 1) / 2;
        result = result * 13;
        result = result + b;
        result = result * 3 + _PlayerLook_aiListLogoKind[_PlayerLook_aiItemSwitchList[row.mUnknown64]];
        result = result * 4 + gPlayerLooks[index].mUnknown78;
        result = result * 2;
        result = result + 1;
    }
    return result;
}

extern "C" unsigned short PlayerLookGetHair(int index)
{
    return gPlayerLooks[index].mUnknown6E;
}

extern "C" void PlayerLookSetHatStyle(int index, unsigned char value)
{
    gPlayerLooks[index].mInfo.mUnknown02 = value;
}

extern "C" void PlayerLookSetHeadDecalKind(int index, unsigned char value)
{
    gPlayerLooks[index].mInfo.mUnknown0B = value;
}

extern "C" void PlayerLookSetFrontDecalKind(int index, int value)
{
    gPlayerLooks[index].mInfo.mUnknown09 = value;
}

extern "C" void PlayerLookSetBackDecalKind(int index, unsigned char value)
{
    gPlayerLooks[index].mInfo.mUnknown0A = value;
}

extern "C" void PlayerLookSetSkin(int index, int value)
{
    gPlayerLooks[index].mUnknown72 = value;
}

extern "C" void PlayerLookSetFace(int index, int value)
{
    gPlayerLooks[index].mUnknown73 = value;
}

extern "C" void PlayerLookSetBrow(int index, int value)
{
    gPlayerLooks[index].mUnknown74 = value;
}

extern "C" void PlayerLookSetHeadType(int index, int value)
{
    gPlayerLooks[index].mUnknown6C = value;
}

extern "C" void PlayerLookSetHair(int index, int value)
{
    gPlayerLooks[index].mUnknown6E = value;
}

extern "C" void PlayerLookSetBodyType(int index, int value)
{
    gPlayerLooks[index].mUnknown78 = value;
}

extern "C" unsigned char PlayerLookGetBodyType(int index)
{
    return gPlayerLooks[index].mUnknown78;
}

extern "C" void PlayerLookSetFaceFlag(int index, int value)
{
    gPlayerLooks[index].mInfo.mUnknown03 = value;
}

extern "C" void PlayerLookSetNumber(int index, int value)
{
    gPlayerLooks[index].mUnknown77 = value;
}

extern "C" unsigned short PlayerLookGetHeadType(int index)
{
    return gPlayerLooks[index].mUnknown6C;
}

extern "C" void PlayerLookSetPlex(int index, int value)
{
    gPlayerLooks[index].mUnknown76 = value;
}

extern "C" unsigned char PlayerLookGetPlex(int index)
{
    return gPlayerLooks[index].mUnknown76;
}

extern "C" void PlayerLookApplyHeadDecal(int index, int player)
{
    PlayerLookColors_t colors;
    int dummy;

    colors.mUnknown1 = 0;
    colors.mUnknown0 = 0;
    colors.mUnknown2 = 0;
    colors.mUnknown3 = 255;
    PlayerLookSetDecal(gPlayerLooks[index].mInfo.mUnknown0B, 25, colors, gPlayerLooks[index].mUnknown77,
                gPlayerLooks[index].mUnknown6A - 1, gPlayerLooks[index].mUnknown68,
                gPlayerLooks[index].mUnknown93, 0, player, &dummy, &dummy);
}

extern "C" int PlayerLookHasHat(int index)
{
    int result = 1;

    if (gPlayerLooks[index].mUnknown70 == 0) {
        result = 0;
    }
    return result;
}

extern "C" unsigned char PlayerLookShowsHair(int index)
{
    return gPlayerLooks[index].mUnknown94;
}

extern "C" unsigned char PlayerLookHidesHead(int index)
{
    return gPlayerLooks[index].mUnknown95;
}

extern "C" void PlayerLookSetHairColor(int index, unsigned int value)
{
    gPlayerLooks[index].mUnknown7A[18] = value + 0x80;
}

extern "C" void PlayerLookSetFacialHairColor(int index, unsigned int value)
{
    gPlayerLooks[index].mUnknown7A[19] = value + 0x80;
}

extern "C" void PlayerLookSetPartVariant(int index, unsigned int which, int value)
{
    switch (which) {
    case 1:
        gPlayerLooks[index].mInfo.mUnknown05 = value;
        break;
    case 0:
        gPlayerLooks[index].mInfo.mUnknown04 = value;
        break;
    case 2:
        gPlayerLooks[index].mInfo.mUnknown08 = value;
        break;
    }
}

extern "C" void PlayerLookSetSwitchFlagsA(int index, unsigned char value)
{
    gPlayerLooks[index].mInfo.mUnknown00 = value;
}

extern "C" void PlayerLookSetSwitchFlagsB(int index, unsigned char value)
{
    gPlayerLooks[index].mInfo.mUnknown01 = value;
}

extern "C" void PlayerLookGetHeadIds(int index, const char *pName, PlayerHeadIds_t *pIds)
{
    PlayerLookGetHeadType(index);
    fn_8015F6E8(pName, PlayerLookGetHair(index), PlayerLookGetHeadType(index), PlayerLookHasHat(index), pIds);
}

extern "C" void PlayerLookHideSwitch28(void)
{
    unsigned int count = PlyrObjsGetCount();
    unsigned int i;

    for (i = 0; i < count; i++) {
        PlyrSwitchSet(PlyrObjsGet(i)->mUnknown4970, 28, 255);
    }
}

extern "C" unsigned char PlayerLookGetSkin(int index)
{
    return gPlayerLooks[index].mUnknown72;
}

extern "C" unsigned char PlayerLookGetFace(int index)
{
    return gPlayerLooks[index].mUnknown73;
}

extern "C" unsigned char PlayerLookGetBrow(int index)
{
    return gPlayerLooks[index].mUnknown74;
}

extern "C" void PlayerLookSetFeatures(int index, FaceFeatures_t *pBlock)
{
    if (pBlock) {
        gPlayerLooks[index].mBlock = *pBlock;
    } else {
        memset(&gPlayerLooks[index].mBlock, 0, sizeof(FaceFeatures_t));
    }
}

extern "C" void PlayerLookGetFeatures(int index, FaceFeatures_t *pBlock)
{
    *pBlock = gPlayerLooks[index].mBlock;
}

extern "C" void PlayerObjCreate(Object_8003DEC4 *pPlayer, PlayerObjInit_t *pInit)
{
    memset(pPlayer, 0x19F0, 0);
    PlyrPoseInit(pPlayer, pInit->mUnknown04, pInit->mUnknown08, pInit->mUnknown10, pInit->mUnknown14);
    pPlayer->mUnknown4956 = pInit->mUnknown18;
    ParticleTrailReset(&pPlayer->mUnknown5188);
    PlyrRenderInitPlayer(pPlayer, pInit);
}

extern "C" void PlayerObjDestroy(Object_8003DEC4 *pPlayer)
{
    PlyrRenderFreePlayer(pPlayer);
    PlyrPoseFree(pPlayer);
}

extern "C" void PlayerObjRenderInit(int a, int b)
{
    gPlayerObjDrawReady = 1;
    PlyrRenderInit(0, 0, a, b);
}

extern "C" void PlayerObjRenderShutdown(void)
{
    gPlayerObjDrawReady = 0;
    PlyrRenderShutdown();
}

extern "C" void PlayerObjAddObjType(int owner, int type, int count)
{
    ObjNewType_(type, 0x19F0, count, PlayerObjCreate, PlayerObjDestroy);
    if (owner) {
        ObjSetListObjFunc(owner, type, 0, PlayerObjDraw);
    }
}

extern "C" int PlayerObjDraw(Object_8003DEC4 *pPlayer, int unused)
{
    PlyrNameTag_t *pItem = pPlayer->mUnknown988;

    if (pItem && pItem->mUnknown28) {
        PlyrNameTagUpdatePosition(pItem, pPlayer->mUnknown4);
    }
    PlyrRenderDrawPlayer(pPlayer);
    return 0;
}

extern "C" void PlayerObjRemoveObjType(int type)
{
    VptFlushObjectTrashSync();
    ObjDelType(type);
}

extern "C" void PlayerObjSetDrawReady(unsigned char value)
{
    gPlayerObjDrawReady = value;
}

extern "C" unsigned char PlayerObjIsDrawReady(void)
{
    return gPlayerObjDrawReady;
}
