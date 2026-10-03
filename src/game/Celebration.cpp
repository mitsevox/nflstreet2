#include "game/GameState.h"
#include "game/ModuleGroup_80033A5C.h"

extern "C" {
extern char lbl_80306DFC[];

void fn_8009B720(void *);
void fn_8009B7E0(void);
}

static ModuleDependency sDependencies[] = { &gGameState, &gAnimData, lbl_80306DFC, 0 };
static ModuleDependency sLinks[] = { &gAnmsCelebration, 0 };
Celebration gCelebration;

ModuleDependency *Celebration::GetDependencies() { return sDependencies; }
ModuleDependency *Celebration::GetLinks() { return sLinks; }
const char *Celebration::GetName() { return "Celebration"; }

int Celebration::Init()
{
    fn_8009B720(gAnimData.fn_80033AF8());
    return 1;
}

int Celebration::Shutdown()
{
    fn_8009B7E0();
    return 1;
}
