#include "game/Module.h"

extern "C" {
extern char lbl_803653D4[];

int fn_801DCE74(int);
int fn_801DCEC8(void);
}

static ModuleDependency sDependencies[] = { lbl_803653D4, 0 };
Obj gObj;

ModuleDependency *Obj::GetDependencies() { return sDependencies; }
ModuleDependency *Obj::GetLinks() { return 0; }
const char *Obj::GetName() { return "Obj"; }

int Obj::Init()
{
    fn_801DCE74(0x21);
    return 1;
}

int Obj::Shutdown()
{
    fn_801DCEC8();
    return 1;
}
