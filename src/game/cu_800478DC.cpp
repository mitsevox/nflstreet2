#include <string.h>

#include "game/Record_803078E8.h"
#include "game/Row_8007BC34.h"
#include "game/cu_800478DC.h"

extern "C" {
extern char *lbl_802CF010[4];
extern char lbl_802CF020[32][15];
extern int lbl_802CF200[32];
extern char lbl_802CF280[16][15];
extern unsigned char lbl_802CF370[18];

int fn_80047DAC(Row_8007BC34 *pRow);
int fn_8007BF14(int index);
int fn_8007C67C(Row_8007BC34 *pRow);
int fn_800462F4(char *pName);
int fn_80161048(char *pName);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *fn_801C2F88(char *pDest, const char *pSource, unsigned int count);
int fn_801C31B0(char *pText0, char *pText1);

void fn_800478DC(unsigned char *pColors)
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

unsigned char fn_80047954(unsigned char value)
{
    return 117;
}

void fn_8004795C(unsigned char *pColors, unsigned char flag)
{
    if (!flag) {
        unsigned char value = fn_80047954(pColors[5]);

        pColors[6] = pColors[5];
        pColors[5] = pColors[4];
        pColors[4] = value;
        pColors[23] = pColors[20];
    }
}

void fn_800479B0(Row_8007BC34 *pRow, Record_803078E8 *pRecord, int *pIds, int *pPalettes, int slot)
{
    char name[82];
    char number[4];
    int palette;
    int i;

    palette = fn_80047DAC(pRow);
    if (fn_8007BF14(slot) == 6) {
        if (pRow->mUnknown52[10]) {
            int id;

            fn_801C2D88(name, sizeof(name), "PLATEX_%s_%02d_%s", pRow->mName, pRecord->mUnknown72, lbl_802CF280[10]);
            i = 17;
            id = fn_80161048(name);
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
                fn_801C2F88(name, "_AWAY", sizeof(name) - 1 - strlen(name));
            }
            if (pRow->mUnknown75) {
                fn_801C2F88(name, "_", sizeof(name) - 1 - strlen(name));
                fn_801C2F88(name, lbl_802CF010[pRecord->mUnknown78], sizeof(name) - 1 - strlen(name));
            }
            if (pRow->mUnknown73) {
                fn_801C2D88(number, sizeof(number), "_%02d", pRecord->mUnknown72);
                fn_801C2F88(name, number, sizeof(name) - 1 - strlen(name));
            }
            fn_801C2F88(name, "_", sizeof(name) - 1 - strlen(name));
            fn_801C2F88(name, lbl_802CF280[part], sizeof(name) - 1 - strlen(name));
            pIds[i] = fn_80161048(name);
            pPalettes[i] = palette;
        }
    }
}

extern const char lbl_8028D6A8[] = "PLATEX_%s_HEAVY_AWAY_%s";
extern const char lbl_8028D6C0[] = "PLATEX_%s_AWAY_%s";
extern const char lbl_8028D6D4[] = "PLATEX_%s_HEAVY_%s";
extern const char lbl_8028D6E8[] = "PLATEX_%s_%s";

void fn_80047BD0(int *pIds, int part, Record_803078E8 *pRecord)
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
    }
}

int fn_80047C74(int part)
{
    return part == 9;
}

int fn_80047C84(Row_8007BC34 *pRow)
{
    return fn_8007C67C(pRow);
}

void fn_80047CA4(int *pIds, Record_803078E8 *pRecord)
{
    char name[60];
    unsigned int i;

    for (i = 0; i <= 31; i++) {
        if (pIds[i] != -1 || !strlen(lbl_802CF020[i])) {
            continue;
        }
        if (fn_80047C74(i) && !pRecord->mUnknown93) {
            fn_801C2D88(name, sizeof(name), "PLATEX_%s_AWAY_%s%02d", lbl_802CF020[i], lbl_802CF010[pRecord->mUnknown78], pRecord->mUnknown72);
        } else {
            fn_801C2D88(name, sizeof(name), "PLATEX_%s_%s%02d", lbl_802CF020[i], lbl_802CF010[pRecord->mUnknown78], pRecord->mUnknown72);
        }
        pIds[i] = fn_80161048(name);
        fn_80047BD0(pIds, i, pRecord);
    }
}

int fn_80047DAC(Row_8007BC34 *pRow)
{
    char name[47];
    int palette = -1;

    if (pRow->mUnknown68 && fn_801C31B0(pRow->mName, "NONE")) {
        fn_801C2D88(name, sizeof(name), "PLADYNCLUT_%s", pRow->mName);
        palette = fn_800462F4(name);
    }
    return palette;
}
}
