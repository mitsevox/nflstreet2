#include "game/Module.h"

extern "C" {
extern char lbl_802CC750[];

int VptInit(void *);
int VptShutdown(void);
}

static ModuleDependency sDependencies[] = { &gSys, &gMat, &gObj, 0 };
Vpt gVpt;

ModuleDependency *Vpt::GetDependencies() { return sDependencies; }
ModuleDependency *Vpt::GetLinks() { return 0; }
const char *Vpt::GetName() { return "Vpt"; }

int Vpt::Init()
{
    VptInit(lbl_802CC750);
    return 1;
}

int Vpt::Shutdown()
{
    VptShutdown();
    return 1;
}
