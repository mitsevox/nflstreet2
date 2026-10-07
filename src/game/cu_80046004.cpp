#include "game/PaletteColor.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"

struct Item_80045F64 {
    int mUnknown0;
    char mUnknown4[4];
};

struct Entry_80046004 {
    int mUnknown0;
    Item_80045F64 *mUnknown4;
};

struct State_80045084 {
    char mUnknown0[12];
};

struct Palettes_8004605C {
    int mCount;
    int *mUnknown4;
    ColorPalette *mUnknown8;
};

extern "C" {
extern char lbl_802EBDE8[];

void fn_80044F20(int a, Entry_80046004 *pEntry);
void fn_80045084(void *p, State_80045084 *pState);
void fn_800450A8(void *p, State_80045084 *pState);
void fn_80045F64(Item_80045F64 *pItem, State_80045084 *pState, Palettes_8004605C *pPalettes);
char *fn_801C3084(const char *pString, int c);
int fn_801C9DC8(int value);
int fn_801F02AC(void *pData, int a, int b);
int fn_801F08FC(void *pData);
int fn_801F0A8C(void *pData, char *pName);
int fn_801F0C50(void *pData, int index);
int fn_801F0D34(void *pData);
int fn_801F1520(int value);
}

static unsigned char lbl_803EA4AC = 0;
static unsigned char lbl_803EA4AD = 0;
static Entry_80046004 *lbl_803EC7B0;
static void *lbl_803EC7B4;

extern "C" {
void fn_80046004(void *pData, int index, Entry_80046004 *pEntry)
{
    fn_801F0C50(pData, index);
    fn_80044F20(fn_801EF390(pData, index, 1), pEntry);
    fn_801F010C(pData, index);
}

void fn_8004605C(void *p, Entry_80046004 *pEntry, Palettes_8004605C *pPalettes)
{
    State_80045084 state;

    fn_80045084(p, &state);
    for (int i = 0; i < pEntry->mUnknown0; i++) {
        fn_80045F64(&pEntry->mUnknown4[i], &state, pPalettes);
    }
    fn_800450A8(p, &state);
}

void fn_800460DC(void)
{
    int saved0 = fn_801F1520(4);
    int saved1 = fn_801C9DC8(4);
    lbl_803EC7B4 = fn_801EEB44(lbl_802EBDE8, 44);
    fn_801F1520(saved0);
    fn_801C9DC8(saved1);
}

void fn_8004613C(void)
{
    lbl_803EA4AC = 1;
    fn_801F02AC(lbl_803EC7B4, 1, 1);
    lbl_803EA4AD = fn_801F0D34(lbl_803EC7B4);
    lbl_803EC7B0 = (Entry_80046004 *)fn_801D2B7C(lbl_803EA4AD * sizeof(Entry_80046004), 4, 0);
    for (unsigned char i = 0; i < lbl_803EA4AD; i++) {
        fn_80046004(lbl_803EC7B4, i, &lbl_803EC7B0[i]);
    }
    fn_801F08FC(lbl_803EC7B4);
}

void fn_800461E0(void)
{
    for (unsigned char i = 0; i < lbl_803EA4AD; i++) {
        if (lbl_803EC7B0[i].mUnknown4) {
            fn_801D2BD0(lbl_803EC7B0[i].mUnknown4);
        }
    }
    fn_801D2BD0(lbl_803EC7B0);
    lbl_803EA4AC = 0;
    fn_801EEFAC(lbl_803EC7B4);
}

void fn_8004625C(void *p, int id, const unsigned char *pPaletteIndices)
{
    Palettes_8004605C palettes;
    ColorPalette colors[25];
    int indices[25];

    palettes.mCount = 25;
    palettes.mUnknown8 = colors;
    palettes.mUnknown4 = indices;
    for (int i = 0; i < 25; i++) {
        palettes.mUnknown4[i] = i;
        fn_80079FBC(pPaletteIndices[i], &palettes.mUnknown8[i]);
    }
    fn_8004605C(p, &lbl_803EC7B0[id], &palettes);
}

int fn_800462F4(char *pName)
{
    char *pSpace;

    if ((pSpace = fn_801C3084(pName, ' ')) != 0) {
        *pSpace = 0;
    }
    return fn_801F0A8C(lbl_803EC7B4, pName);
}
}
