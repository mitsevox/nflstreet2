#include "game/FELoop.h"
#include "game/Module.h"

extern "C" {
void fn_80194D20(void);
void fn_80194D70(void);
void fn_80194DB8(void);
}

static void *sDependencies[] = { 0 };
Rumble gRumble;

ModuleDependency *Rumble::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Rumble::GetLinks() { return 0; }
const char *Rumble::GetName() { return "Rumble"; }

int Rumble::Init()
{
    if (fn_80027DF0()) {
        fn_80194D70();
    } else {
        fn_80194D20();
    }
    return 1;
}

int Rumble::Shutdown()
{
    fn_80194DB8();
    return 1;
}
