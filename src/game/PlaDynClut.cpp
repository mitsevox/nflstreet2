/* Player dynamic colour tables: loads pladyncl.dat and recolours jersey and gear textures with a
   team's colours. */
#include "game/DynClut_80044F20.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"

extern "C" {
extern char lbl_802EBDE8[];

char *fn_801C3084(const char *pString, int c);
int fn_801C9DC8(int value);
int fn_801F02AC(void *pData, int a, int b);
int fn_801F08FC(void *pData);
int fn_801F0A8C(void *pData, char *pName);
int fn_801F0C50(void *pData, int index);
int fn_801F0D34(void *pData);
int fn_801F1520(int value);
}

static unsigned char _PlaDynClut_bLoaded = 0;
static unsigned char _PlaDynClut_uCount = 0;
static PlaDynClutEntry_t *_PlaDynClut_pEntries;
static void *_PlaDynClut_pFile;

extern "C" {
void PlaDynClutLoadEntry(void *pData, int index, PlaDynClutEntry_t *pEntry)
{
    fn_801F0C50(pData, index);
    fn_80044F20((void *)fn_801EF390(pData, index, 1), pEntry);
    fn_801F010C(pData, index);
}

void PlaDynClutApply(void *p, PlaDynClutEntry_t *pEntry, PlaDynClutPalettes_t *pPalettes)
{
    State_80045084 state;

    fn_80045084(p, &state);
    for (int i = 0; i < pEntry->mCount; i++) {
        fn_80045F64(&pEntry->mpEntries[i], &state, pPalettes);
    }
    fn_800450A8(p, &state);
}

void PlaDynClutOpen(void)
{
    int saved0 = fn_801F1520(4);
    int saved1 = fn_801C9DC8(4);
    _PlaDynClut_pFile = fn_801EEB44(lbl_802EBDE8, 44);
    fn_801F1520(saved0);
    fn_801C9DC8(saved1);
}

void PlaDynClutLoad(void)
{
    _PlaDynClut_bLoaded = 1;
    fn_801F02AC(_PlaDynClut_pFile, 1, 1);
    _PlaDynClut_uCount = fn_801F0D34(_PlaDynClut_pFile);
    _PlaDynClut_pEntries = (PlaDynClutEntry_t *)fn_801D2B7C(_PlaDynClut_uCount * sizeof(PlaDynClutEntry_t), 4, 0);
    for (unsigned char i = 0; i < _PlaDynClut_uCount; i++) {
        PlaDynClutLoadEntry(_PlaDynClut_pFile, i, &_PlaDynClut_pEntries[i]);
    }
    fn_801F08FC(_PlaDynClut_pFile);
}

void PlaDynClutUnload(void)
{
    for (unsigned char i = 0; i < _PlaDynClut_uCount; i++) {
        if (_PlaDynClut_pEntries[i].mpEntries) {
            fn_801D2BD0(_PlaDynClut_pEntries[i].mpEntries);
        }
    }
    fn_801D2BD0(_PlaDynClut_pEntries);
    _PlaDynClut_bLoaded = 0;
    fn_801EEFAC(_PlaDynClut_pFile);
}

void PlaDynClutApplyColors(void *p, int id, const unsigned char *pPaletteIndices)
{
    PlaDynClutPalettes_t palettes;
    ColorPalette colors[25];
    int indices[25];

    palettes.mCount = 25;
    palettes.mpPalettes = colors;
    palettes.mpColorNums = indices;
    for (int i = 0; i < 25; i++) {
        palettes.mpColorNums[i] = i;
        DbColPalGetPalette(pPaletteIndices[i], &palettes.mpPalettes[i]);
    }
    PlaDynClutApply(p, &_PlaDynClut_pEntries[id], &palettes);
}

int PlaDynClutFind(char *pName)
{
    char *pSpace;

    if ((pSpace = fn_801C3084(pName, ' ')) != 0) {
        *pSpace = 0;
    }
    return fn_801F0A8C(_PlaDynClut_pFile, pName);
}
}
