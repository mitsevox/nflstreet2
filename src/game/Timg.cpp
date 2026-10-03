#include "game/Module.h"

extern "C" {
extern char lbl_803065C0[];

void fn_80237780(int);
void fn_80237868(void);
}

static ModuleDependency sDependencies[] = { lbl_803065C0, 0 };
Timg gTimg;

ModuleDependency *Timg::GetDependencies() { return sDependencies; }
ModuleDependency *Timg::GetLinks() { return 0; }
const char *Timg::GetName() { return "Timg"; }

int Timg::Init()
{
    fn_80237780(1);
    return 1;
}

int Timg::Shutdown()
{
    fn_80237868();
    return 1;
}
