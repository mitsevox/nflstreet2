/* Player texture names: builds the PLATEX_ texture names for each gear item and body part of a
   player, his team colour list and his dynamic colour table name. */
#include <string.h>

#include "game/PlayerLookRecord.h"
#include "game/GearDb.h"
#include "game/PlaTex.h"

static char *_PlaTex_apBodyTypeNames[4] = {"HEAVY", "MUSCULAR", "ATHLETIC", "ATHLETIC"};
static char _PlaTex_aaDefaultPartNames[32][15] = {
    "", "", "", "", "", "", "", "",
    "", "TORSO", "SPAD", "BICEP", "", "ELBOW", "FOREARM", "",
    "HAND", "HAND", "", "KNEE", "UPPERSHIN", "LOWERSHIN", "", "",
    "", "", "", "", "", "", "", "",
};
static int _PlaTex_aiSlotBodyParts[32] = {
    2, 1, 34, 34, 0, 34, 34, 34, 34, 3, 4, 5, 6, 7, 8, 9,
    10, 10, 11, 12, 13, 14, 15, 34, 34, 34, 34, 34, 34, 34, 34, 34,
};
static char _PlaTex_aaBodyPartNames[16][15] = {
    "HAIR", "HAT", "EYE", "TORSO", "SPAD", "BICEP", "LOWERBICEP", "ELBOW",
    "FOREARM", "WRIST", "HAND", "THIGH", "KNEE", "UPPERSHIN", "LOWERSHIN", "SHOE",
};

extern "C" {
extern unsigned char gPlayerLookColorRemap[18];

int PlaTexFindDynClut(GearRow_t *pRow);
int GearDbGetSlotType(int index);
int GearDbIsNumberItem(GearRow_t *pRow);
int PlaDynClutFind(char *pName);
int PlaTexCacheFindTexture(char *pName);
int snprintf(char *pBuffer, int size, const char *pFormat, ...);

void PlaTexRemapColors(unsigned char *pColors)
{
    int i;

    for (i = 0; i < 18; i++) {
        if (gPlayerLookColorRemap[i] >= 20 && gPlayerLookColorRemap[i] <= 22) {
            pColors[i] = pColors[gPlayerLookColorRemap[i]];
        } else if (gPlayerLookColorRemap[i] == 240) {
            pColors[i] = 117;
        } else if (gPlayerLookColorRemap[i] == 241) {
            pColors[i] = 127;
        }
    }
    pColors[23] = 117;
    pColors[24] = pColors[21];
}

unsigned char PlaTexGetAwayColor(unsigned char value)
{
    return 117;
}

void PlaTexApplyAwayColors(unsigned char *pColors, unsigned char flag)
{
    if (!flag) {
        unsigned char value = PlaTexGetAwayColor(pColors[5]);

        pColors[6] = pColors[5];
        pColors[5] = pColors[4];
        pColors[4] = value;
        pColors[23] = pColors[20];
    }
}

void PlaTexBuildPartIds(GearRow_t *pRow, PlayerLook_t *pRecord, int *pIds, int *pPalettes, int slot)
{
    char name[82];
    char number[4];
    int palette;
    int i;

    palette = PlaTexFindDynClut(pRow);
    if (GearDbGetSlotType(slot) == 6) {
        if (pRow->mUnknown52[10]) {
            int id;

            snprintf(name, sizeof(name), "PLATEX_%s_%02d_%s", pRow->mName, pRecord->mUnknown72, _PlaTex_aaBodyPartNames[10]);
            i = 17;
            id = PlaTexCacheFindTexture(name);
            if (slot == 6) {
                i = 16;
            }
            pIds[i] = id;
            pPalettes[i] = palette;
        }
    } else {
        for (i = 0; i < 32; i++) {
            int part = _PlaTex_aiSlotBodyParts[i];

            if (part == 34 || !pRow->mUnknown52[part]) {
                continue;
            }
            snprintf(name, sizeof(name), "PLATEX_%s", pRow->mName);
            if (pRow->mUnknown74 && !pRecord->mUnknown93) {
                strncat(name, "_AWAY", sizeof(name) - 1 - strlen(name));
            }
            if (pRow->mUnknown75) {
                strncat(name, "_", sizeof(name) - 1 - strlen(name));
                strncat(name, _PlaTex_apBodyTypeNames[pRecord->mUnknown78], sizeof(name) - 1 - strlen(name));
            }
            if (pRow->mUnknown73) {
                snprintf(number, sizeof(number), "_%02d", pRecord->mUnknown72);
                strncat(name, number, sizeof(name) - 1 - strlen(name));
            }
            strncat(name, "_", sizeof(name) - 1 - strlen(name));
            strncat(name, _PlaTex_aaBodyPartNames[part], sizeof(name) - 1 - strlen(name));
            pIds[i] = PlaTexCacheFindTexture(name);
            pPalettes[i] = palette;
        }
    }
}

extern const char _PlaTex_szHeavyAwayFormat[] = "PLATEX_%s_HEAVY_AWAY_%s";
extern const char _PlaTex_szAwayFormat[] = "PLATEX_%s_AWAY_%s";
extern const char _PlaTex_szHeavyFormat[] = "PLATEX_%s_HEAVY_%s";
extern const char _PlaTex_szFormat[] = "PLATEX_%s_%s";

void PlaTexSetArmArtIds(int *pIds, int part, PlayerLook_t *pRecord)
{
    switch (part) {
    case 11:
        pIds[26] = pRecord->mInfo.mUnknown04 * 3 + 15841;
        pIds[25] = pRecord->mInfo.mUnknown05 * 3 + 16108;
        break;
    case 14:
        pIds[28] = pRecord->mInfo.mUnknown04 * 3 + 15842;
        pIds[27] = pRecord->mInfo.mUnknown05 * 3 + 16109;
        break;
    case 13:
        pIds[30] = pRecord->mInfo.mUnknown04 * 3 + 15843;
        pIds[29] = pRecord->mInfo.mUnknown05 * 3 + 16110;
        break;
    case 16: /* HAND parts (_PlaTex_aaDefaultPartNames) take no extra ids */
    case 17:
        break;
    }
}

int PlaTexIsAwayPart(int part)
{
    return part == 9;
}

int PlaTexIsNumberItem(GearRow_t *pRow)
{
    return GearDbIsNumberItem(pRow);
}

void PlaTexBuildDefaultIds(int *pIds, PlayerLook_t *pRecord)
{
    char name[60];
    unsigned int i;

    for (i = 0; i <= 31; i++) {
        if (pIds[i] != -1 || !strlen(_PlaTex_aaDefaultPartNames[i])) {
            continue;
        }
        if (PlaTexIsAwayPart(i) && !pRecord->mUnknown93) {
            snprintf(name, sizeof(name), "PLATEX_%s_AWAY_%s%02d", _PlaTex_aaDefaultPartNames[i], _PlaTex_apBodyTypeNames[pRecord->mUnknown78], pRecord->mUnknown72);
        } else {
            snprintf(name, sizeof(name), "PLATEX_%s_%s%02d", _PlaTex_aaDefaultPartNames[i], _PlaTex_apBodyTypeNames[pRecord->mUnknown78], pRecord->mUnknown72);
        }
        pIds[i] = PlaTexCacheFindTexture(name);
        PlaTexSetArmArtIds(pIds, i, pRecord);
    }
}

int PlaTexFindDynClut(GearRow_t *pRow)
{
    char name[47];
    int palette = -1;

    if (pRow->mUnknown68 && stricmp(pRow->mName, "NONE")) {
        snprintf(name, sizeof(name), "PLADYNCLUT_%s", pRow->mName);
        palette = PlaDynClutFind(name);
    }
    return palette;
}
}
