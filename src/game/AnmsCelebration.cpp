#include "game/Module.h"

extern "C" {
extern char lbl_803065C0[];
extern char lbl_80306D28[];

void fn_800925F0(void);
void *fn_80033AF8(void *);
void fn_80093684(void *);
void fn_800937CC(void);
void fn_800926A8(void);
}

static ModuleDependency sDependencies[] = { lbl_803065C0, lbl_80306D28, 0 };
static ModuleDependency sLinks[] = { &gCelebration, 0 };
AnmsCelebration gAnmsCelebration;

ModuleDependency *AnmsCelebration::GetDependencies() { return sDependencies; }
ModuleDependency *AnmsCelebration::GetLinks() { return sLinks; }
const char *AnmsCelebration::GetName() { return "AnmsCelebration"; }

int AnmsCelebration::Init()
{
    fn_800925F0();
    fn_80093684(fn_80033AF8(lbl_80306D28));
    return 1;
}

int AnmsCelebration::Shutdown()
{
    fn_800937CC();
    fn_800926A8();
    return 1;
}
