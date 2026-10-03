#include "game/Module.h"

extern "C" {
extern char lbl_803653D4[];
extern char lbl_80306508[];
extern char lbl_802CC740[];
extern char lbl_802EBE50[];

void fn_801CCC24(void *);
void fn_801CAEC8(const char *, int);
void fn_801CCD0C(void);
}

static ModuleDependency sDependencies[] = { lbl_803653D4, lbl_80306508, 0 };
Font gFont;

ModuleDependency *Font::GetDependencies() { return sDependencies; }
ModuleDependency *Font::GetLinks() { return 0; }
const char *Font::GetName() { return "Font"; }

int Font::Init()
{
    fn_801CCC24(lbl_802CC740);
    fn_801CAEC8(lbl_802EBE50, 3);
    return 1;
}

int Font::Shutdown()
{
    fn_801CCD0C();
    return 1;
}
