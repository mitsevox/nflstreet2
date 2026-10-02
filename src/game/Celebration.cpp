#include "game/Module.h"

extern "C" {
extern char lbl_803065C0[];
extern char lbl_80306D28[];
extern char lbl_80306DFC[];
extern AnmsCelebration lbl_8030BE78;

void fn_80033AF8(void *);
void fn_8009B720(void);
void fn_8009B7E0(void);
}

static ModuleDependency sDependencies[] = { lbl_803065C0, lbl_80306D28, lbl_80306DFC, 0 };
static ModuleLink sLink(&lbl_8030BE78);
Celebration gCelebration;

void *Celebration::GetDependencies() { return sDependencies; }
void *Celebration::GetLink() { return &sLink; }
const char *Celebration::GetName() { return "Celebration"; }

int Celebration::Init()
{
    fn_80033AF8(lbl_80306D28);
    fn_8009B720();
    return 1;
}

int Celebration::Shutdown()
{
    fn_8009B7E0();
    return 1;
}
