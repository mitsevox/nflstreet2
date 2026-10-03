#include "game/Module.h"

extern "C" {
extern char lbl_803653D4[];
extern char lbl_803653A4[];

int fn_8020DE8C(int, int, int);
int fn_8020DF44(void);
}

static ModuleDependency sDependencies[] = { lbl_803653D4, lbl_803653A4, 0 };
Tex gTex;

ModuleDependency *Tex::GetDependencies() { return sDependencies; }
ModuleDependency *Tex::GetLinks() { return 0; }
const char *Tex::GetName() { return "Tex"; }

int Tex::Init()
{
    fn_8020DE8C(1, 1, 1);
    return 1;
}

int Tex::Shutdown()
{
    fn_8020DF44();
    return 1;
}
