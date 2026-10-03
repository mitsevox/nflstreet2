#include "game/GameState.h"

extern "C" {
extern char lbl_80306D28[];
extern char lbl_80306DFC[];

void *fn_80033AF8(void *);
void fn_8009B720(void *);
void fn_8009B7E0(void);
}

static ModuleDependency sDependencies[] = { &gGameState, lbl_80306D28, lbl_80306DFC, 0 };
static ModuleDependency sLinks[] = { &gAnmsCelebration, 0 };
Celebration gCelebration;

ModuleDependency *Celebration::GetDependencies() { return sDependencies; }
ModuleDependency *Celebration::GetLinks() { return sLinks; }
const char *Celebration::GetName() { return "Celebration"; }

int Celebration::Init()
{
    fn_8009B720(fn_80033AF8(lbl_80306D28));
    return 1;
}

int Celebration::Shutdown()
{
    fn_8009B7E0();
    return 1;
}
