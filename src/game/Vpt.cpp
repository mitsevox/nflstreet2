#include "game/Module.h"

extern "C" {
extern char lbl_803653D4[];
extern char lbl_802CC750[];

int fn_802280B0(void *);
int fn_80228194(void);
}

static ModuleDependency sDependencies[] = { lbl_803653D4, &gMat, &gObj, 0 };
Vpt gVpt;

ModuleDependency *Vpt::GetDependencies() { return sDependencies; }
ModuleDependency *Vpt::GetLinks() { return 0; }
const char *Vpt::GetName() { return "Vpt"; }

int Vpt::Init()
{
    fn_802280B0(lbl_802CC750);
    return 1;
}

int Vpt::Shutdown()
{
    fn_80228194();
    return 1;
}
