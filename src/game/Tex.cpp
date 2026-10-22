#include "engine/texture.h"
#include "game/Module.h"

static ModuleDependency sDependencies[] = { &gSys, &gGLIB, 0 };
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
