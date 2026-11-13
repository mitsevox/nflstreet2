/* Loads the team colour palettes (four RGB colours each) from the CPAL and CPHR database tables at
   startup and hands out a palette, its primary colour or its name by palette index. */

#include "game/Module.h"
#include "game/DbCursor.h"
#include "game/PaletteColor.h"

static void *sDependencies[] = { 0 };
static DbColumnValue _DbColPal_aRecord[14] = {
    { 0, 0x4C415043, 0x494C5043, 0 },
    { 0, 0x4C415043, 0x44525043, 0 },
    { 0, 0x4C415043, 0x52475043, 0 },
    { 0, 0x4C415043, 0x55425043, 0 },
    { 0, 0x4C415043, 0x44525343, 0 },
    { 0, 0x4C415043, 0x52475343, 0 },
    { 0, 0x4C415043, 0x55425343, 0 },
    { 0, 0x4C415043, 0x44524D43, 0 },
    { 0, 0x4C415043, 0x52474D43, 0 },
    { 0, 0x4C415043, 0x4C424D43, 0 },
    { 0, 0x4C415043, 0x44524843, 0 },
    { 0, 0x4C415043, 0x52474843, 0 },
    { 0, 0x4C415043, 0x4C424843, 0 },
    { 0, -1, -1, 0 },
};
DbColPal gDbColPal;
static ColorPalette _DbColPal_aPalettes[140];

ModuleDependency *DbColPal::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *DbColPal::GetLinks() { return 0; }
const char *DbColPal::GetName() { return "DbColPal"; }

int DbColPal::Init()
{
    DbCursor cursor;
    int args[8] = { 0x52485043, 0x494C5043, 0, 0, -1, -1, 3, 0 };
    unsigned char index;

    DbCursorOpen(&cursor, 0x4C415043, 0x494C5043, 0, 0, 0x54415453);
    if (DbCursorFirst(&cursor)) {
        do {
            cursor.Read(_DbColPal_aRecord);
            index = _DbColPal_aRecord[0].mValue;
            _DbColPal_aPalettes[index].mColors[0].r = _DbColPal_aRecord[1].mValue;
            _DbColPal_aPalettes[index].mColors[0].g = _DbColPal_aRecord[2].mValue;
            _DbColPal_aPalettes[index].mColors[0].b = _DbColPal_aRecord[3].mValue;
            _DbColPal_aPalettes[index].mColors[1].r = _DbColPal_aRecord[4].mValue;
            _DbColPal_aPalettes[index].mColors[1].g = _DbColPal_aRecord[5].mValue;
            _DbColPal_aPalettes[index].mColors[1].b = _DbColPal_aRecord[6].mValue;
            _DbColPal_aPalettes[index].mColors[2].r = _DbColPal_aRecord[7].mValue;
            _DbColPal_aPalettes[index].mColors[2].g = _DbColPal_aRecord[8].mValue;
            _DbColPal_aPalettes[index].mColors[2].b = _DbColPal_aRecord[9].mValue;
            _DbColPal_aPalettes[index].mColors[3].r = _DbColPal_aRecord[10].mValue;
            _DbColPal_aPalettes[index].mColors[3].g = _DbColPal_aRecord[11].mValue;
            _DbColPal_aPalettes[index].mColors[3].b = _DbColPal_aRecord[12].mValue;
        } while (DbCursorNext(&cursor));
    }
    DbCursorClose(&cursor);

    DbCursorOpen(&cursor, 0x52485043, 0x494C5043, args, 0, 0x54415453);
    if (DbCursorFirst(&cursor)) {
        do {
            cursor.Read(_DbColPal_aRecord);
            index = _DbColPal_aRecord[0].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[0].r = _DbColPal_aRecord[1].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[0].g = _DbColPal_aRecord[2].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[0].b = _DbColPal_aRecord[3].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[1].r = _DbColPal_aRecord[4].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[1].g = _DbColPal_aRecord[5].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[1].b = _DbColPal_aRecord[6].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[2].r = _DbColPal_aRecord[7].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[2].g = _DbColPal_aRecord[8].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[2].b = _DbColPal_aRecord[9].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[3].r = _DbColPal_aRecord[10].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[3].g = _DbColPal_aRecord[11].mValue;
            _DbColPal_aPalettes[(unsigned char)(index + 128)].mColors[3].b = _DbColPal_aRecord[12].mValue;
        } while (DbCursorNext(&cursor));
    }
    DbCursorClose(&cursor);
    return 1;
}

int DbColPal::Shutdown() { return 1; }

extern "C" {
void DbColPalGetPalette(int index, ColorPalette *pPalette)
{
    pPalette->mColors[0].r = _DbColPal_aPalettes[index].mColors[0].r;
    pPalette->mColors[0].g = _DbColPal_aPalettes[index].mColors[0].g;
    pPalette->mColors[0].b = _DbColPal_aPalettes[index].mColors[0].b;
    pPalette->mColors[1].r = _DbColPal_aPalettes[index].mColors[1].r;
    pPalette->mColors[1].g = _DbColPal_aPalettes[index].mColors[1].g;
    pPalette->mColors[1].b = _DbColPal_aPalettes[index].mColors[1].b;
    pPalette->mColors[2].r = _DbColPal_aPalettes[index].mColors[2].r;
    pPalette->mColors[2].g = _DbColPal_aPalettes[index].mColors[2].g;
    pPalette->mColors[2].b = _DbColPal_aPalettes[index].mColors[2].b;
    pPalette->mColors[3].r = _DbColPal_aPalettes[index].mColors[3].r;
    pPalette->mColors[3].g = _DbColPal_aPalettes[index].mColors[3].g;
    pPalette->mColors[3].b = _DbColPal_aPalettes[index].mColors[3].b;
}

void DbColPalGetPrimaryColor(unsigned char index, PaletteColor *pColor)
{
    pColor->r = _DbColPal_aPalettes[index].mColors[0].r;
    pColor->g = _DbColPal_aPalettes[index].mColors[0].g;
    pColor->b = _DbColPal_aPalettes[index].mColors[0].b;
}

void DbColPalGetPaletteName(int index, char *pBuffer, int size)
{
    DbCursor cursor;

    DbCursorOpen(&cursor, 0x52485043, 0x494C5043, 0, 0, 0x54415453);
    DbCursorFindInt(&cursor, 0x494C5043, index, 0, 0);
    DbCursorGetString(&cursor, 0x44435043, (int)pBuffer, size);
    DbCursorClose(&cursor);
}
}
