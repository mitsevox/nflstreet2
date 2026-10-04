#include "game/Module.h"
#include "game/Object_8007A334.h"
#include "game/PaletteColor.h"

static void *sDependencies[] = { 0 };
static ColumnValue_802D6424 sRecord[14] = {
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
static ColorPalette sPalettes[140];

ModuleDependency *DbColPal::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *DbColPal::GetLinks() { return 0; }
const char *DbColPal::GetName() { return "DbColPal"; }

int DbColPal::Init()
{
    Object_8007A334 cursor;
    int args[8] = { 0x52485043, 0x494C5043, 0, 0, -1, -1, 3, 0 };
    unsigned char index;

    fn_8007A334(&cursor, 0x4C415043, 0x494C5043, 0, 0, 0x54415453);
    if (fn_8007A444(&cursor)) {
        do {
            cursor.Read(sRecord);
            index = sRecord[0].mValue;
            sPalettes[index].mColors[0].r = sRecord[1].mValue;
            sPalettes[index].mColors[0].g = sRecord[2].mValue;
            sPalettes[index].mColors[0].b = sRecord[3].mValue;
            sPalettes[index].mColors[1].r = sRecord[4].mValue;
            sPalettes[index].mColors[1].g = sRecord[5].mValue;
            sPalettes[index].mColors[1].b = sRecord[6].mValue;
            sPalettes[index].mColors[2].r = sRecord[7].mValue;
            sPalettes[index].mColors[2].g = sRecord[8].mValue;
            sPalettes[index].mColors[2].b = sRecord[9].mValue;
            sPalettes[index].mColors[3].r = sRecord[10].mValue;
            sPalettes[index].mColors[3].g = sRecord[11].mValue;
            sPalettes[index].mColors[3].b = sRecord[12].mValue;
        } while (fn_8007A510(&cursor));
    }
    fn_8007A3C4(&cursor);

    fn_8007A334(&cursor, 0x52485043, 0x494C5043, args, 0, 0x54415453);
    if (fn_8007A444(&cursor)) {
        do {
            cursor.Read(sRecord);
            index = sRecord[0].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[0].r = sRecord[1].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[0].g = sRecord[2].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[0].b = sRecord[3].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[1].r = sRecord[4].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[1].g = sRecord[5].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[1].b = sRecord[6].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[2].r = sRecord[7].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[2].g = sRecord[8].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[2].b = sRecord[9].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[3].r = sRecord[10].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[3].g = sRecord[11].mValue;
            sPalettes[(unsigned char)(index + 128)].mColors[3].b = sRecord[12].mValue;
        } while (fn_8007A510(&cursor));
    }
    fn_8007A3C4(&cursor);
    return 1;
}

int DbColPal::Shutdown() { return 1; }

extern "C" {
void fn_80079FBC(int index, ColorPalette *pPalette)
{
    pPalette->mColors[0].r = sPalettes[index].mColors[0].r;
    pPalette->mColors[0].g = sPalettes[index].mColors[0].g;
    pPalette->mColors[0].b = sPalettes[index].mColors[0].b;
    pPalette->mColors[1].r = sPalettes[index].mColors[1].r;
    pPalette->mColors[1].g = sPalettes[index].mColors[1].g;
    pPalette->mColors[1].b = sPalettes[index].mColors[1].b;
    pPalette->mColors[2].r = sPalettes[index].mColors[2].r;
    pPalette->mColors[2].g = sPalettes[index].mColors[2].g;
    pPalette->mColors[2].b = sPalettes[index].mColors[2].b;
    pPalette->mColors[3].r = sPalettes[index].mColors[3].r;
    pPalette->mColors[3].g = sPalettes[index].mColors[3].g;
    pPalette->mColors[3].b = sPalettes[index].mColors[3].b;
}

void fn_8007A068(unsigned char index, PaletteColor *pColor)
{
    pColor->r = sPalettes[index].mColors[0].r;
    pColor->g = sPalettes[index].mColors[0].g;
    pColor->b = sPalettes[index].mColors[0].b;
}

void fn_8007A098(int a, int b, int c)
{
    Object_8007A334 cursor;

    fn_8007A334(&cursor, 0x52485043, 0x494C5043, 0, 0, 0x54415453);
    fn_8007A7F4(&cursor, 0x494C5043, a, 0, 0);
    fn_8007AA3C(&cursor, 0x44435043, b, c);
    fn_8007A3C4(&cursor);
}
}
