#include "game/Module.h"

extern "C" {

int ObjInit(int);
int ObjShutdown(void);
}

static ModuleDependency sDependencies[] = { &gSys, 0 };
Obj gObj;

ModuleDependency *Obj::GetDependencies() { return sDependencies; }
ModuleDependency *Obj::GetLinks() { return 0; }
const char *Obj::GetName() { return "Obj"; }

int Obj::Init()
{
    ObjInit(0x21);
    return 1;
}

int Obj::Shutdown()
{
    ObjShutdown();
    return 1;
}
