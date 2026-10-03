#include "game/Module.h"
#include "game/Record_802CC680.h"

extern "C" {
extern char lbl_80365384[];

int fn_801EE970(int);
void fn_801F2BAC(int);
void fn_801F23B8(int, int);
void fn_801F2790(int);
void fn_801F2694(int);
void fn_801F2BF0(void);
int fn_801EEA60(void);
}

static ModuleDependency sDependencies[] = { &gSys, lbl_80365384, 0 };
Res gRes;

ModuleDependency *Res::GetDependencies() { return sDependencies; }
ModuleDependency *Res::GetLinks() { return 0; }
const char *Res::GetName() { return "Res"; }

int Res::Init()
{
    fn_801EE970(0x40);
    fn_801F2BAC(1);
    if (fn_80025E50(8)->mUnknown10 != 0) {
        fn_801F23B8(8, 0x100000);
        fn_801F2790(0);
        fn_801F2694(1);
    }
    return 1;
}

int Res::Shutdown()
{
    fn_801F2BF0();
    fn_801EEA60();
    return 1;
}
