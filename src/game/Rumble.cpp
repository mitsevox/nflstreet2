#include "game/FELoop.h"
#include "game/Module.h"

extern "C" {
void RumbleInit(void);
void RumbleInitAllPorts(void);
void RumbleShutdown(void);
}

static void *sDependencies[] = { 0 };
Rumble gRumble;

ModuleDependency *Rumble::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Rumble::GetLinks() { return 0; }
const char *Rumble::GetName() { return "Rumble"; }

int Rumble::Init()
{
    if (fn_80027DF0()) {
        RumbleInitAllPorts();
    } else {
        RumbleInit();
    }
    return 1;
}

int Rumble::Shutdown()
{
    RumbleShutdown();
    return 1;
}
