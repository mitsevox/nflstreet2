/* Player texture names: builds the PLATEX_ texture names for each gear item and body part of a
   player, his team colour list and his dynamic colour table name. */
#include <string.h>

#include "game/PlayerLookRecord.h"
#include "game/Row_8007BC34.h"
#include "game/PlaTex.h"

extern "C" {
extern char *lbl_802CF010[4];
extern char lbl_802CF020[32][15];
extern int lbl_802CF200[32];
extern char lbl_802CF280[16][15];
extern unsigned char lbl_802CF370[18];

int PlaTexFindDynClut(Row_8007BC34 *pRow);
int fn_8007BF14(int index);
int fn_8007C67C(Row_8007BC34 *pRow);
int PlaDynClutFind(char *pName);
int PlaTexCacheFindTexture(char *pName);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);

void PlaTexRemapColors(unsigned char *pColors)
{
    int i;

    for (i = 0; i < 18; i++) {
        if (lbl_802CF370[i] >= 20 && lbl_802CF370[i] <= 22) {
            pColors[i] = pColors[lbl_802CF370[i]];
        } else if (lbl_802CF370[i] == 240) {
            pColors[i] = 117;
        } else if (lbl_802CF370[i] == 241) {
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

void PlaTexBuildPartIds(Row_8007BC34 *pRow, PlayerLook_t *pRecord, int *pIds, int *pPalettes, int slot)
{
    char name[82];
    char number[4];
    int palette;
    int i;

    palette = PlaTexFindDynClut(pRow);
    if (fn_8007BF14(slot) == 6) {
        if (pRow->mUnknown52[10]) {
            int id;

            fn_801C2D88(name, sizeof(name), "PLATEX_%s_%02d_%s", pRow->mName, pRecord->mUnknown72, lbl_802CF280[10]);
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
            int part = lbl_802CF200[i];

            if (part == 34 || !pRow->mUnknown52[part]) {
                continue;
            }
            fn_801C2D88(name, sizeof(name), "PLATEX_%s", pRow->mName);
            if (pRow->mUnknown74 && !pRecord->mUnknown93) {
                strncat(name, "_AWAY", sizeof(name) - 1 - strlen(name));
            }
            if (pRow->mUnknown75) {
                strncat(name, "_", sizeof(name) - 1 - strlen(name));
                strncat(name, lbl_802CF010[pRecord->mUnknown78], sizeof(name) - 1 - strlen(name));
            }
            if (pRow->mUnknown73) {
                fn_801C2D88(number, sizeof(number), "_%02d", pRecord->mUnknown72);
                strncat(name, number, sizeof(name) - 1 - strlen(name));
            }
            strncat(name, "_", sizeof(name) - 1 - strlen(name));
            strncat(name, lbl_802CF280[part], sizeof(name) - 1 - strlen(name));
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
    case 16: /* HAND parts (lbl_802CF020) take no extra ids */
    case 17:
        break;
    }
}

int PlaTexIsAwayPart(int part)
{
    return part == 9;
}

int PlaTexIsNumberItem(Row_8007BC34 *pRow)
{
    return fn_8007C67C(pRow);
}

void PlaTexBuildDefaultIds(int *pIds, PlayerLook_t *pRecord)
{
    char name[60];
    unsigned int i;

    for (i = 0; i <= 31; i++) {
        if (pIds[i] != -1 || !strlen(lbl_802CF020[i])) {
            continue;
        }
        if (PlaTexIsAwayPart(i) && !pRecord->mUnknown93) {
            fn_801C2D88(name, sizeof(name), "PLATEX_%s_AWAY_%s%02d", lbl_802CF020[i], lbl_802CF010[pRecord->mUnknown78], pRecord->mUnknown72);
        } else {
            fn_801C2D88(name, sizeof(name), "PLATEX_%s_%s%02d", lbl_802CF020[i], lbl_802CF010[pRecord->mUnknown78], pRecord->mUnknown72);
        }
        pIds[i] = PlaTexCacheFindTexture(name);
        PlaTexSetArmArtIds(pIds, i, pRecord);
    }
}

int PlaTexFindDynClut(Row_8007BC34 *pRow)
{
    char name[47];
    int palette = -1;

    if (pRow->mUnknown68 && stricmp(pRow->mName, "NONE")) {
        fn_801C2D88(name, sizeof(name), "PLADYNCLUT_%s", pRow->mName);
        palette = PlaDynClutFind(name);
    }
    return palette;
}
}
