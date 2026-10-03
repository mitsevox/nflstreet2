#include "game/Module.h"

extern "C" {
void fn_80215B6C(int);
void fn_80215B70(void);
void fn_802102E8(void);
void fn_8021032C(void);
void fn_8020EFC8(int);
void fn_8020F00C(void);
void fn_8020F5F0(int);
void fn_8020F76C(void);
void fn_80211F94(int);
void fn_80211FC8(void);
void fn_8021189C(int, int);
void fn_802118F0(void);
void fn_80213160(void);
void fn_802131D8(void);
void fn_8020FFE4(int);
void fn_80210020(void);
void fn_8020FC1C(int *);
void fn_80213444(int, int);
void fn_802134AC(void);
}

static void *sDependencies[] = { 0 };
Render gRender;

ModuleDependency *Render::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Render::GetLinks() { return 0; }
const char *Render::GetName() { return "Render"; }

int Render::Init()
{
    int counts[9] = { 0, 4000, 600, 300 };

    fn_80215B6C(0x4000);
    fn_802102E8();
    fn_8020EFC8(0x23000);
    fn_8020F5F0(16);
    fn_80211F94(8);
    fn_8021189C(64, 8);
    fn_80213160();
    fn_8020FFE4(0x1480);
    fn_8020FC1C(counts);
    fn_80213444(4000, 1);
    return 1;
}

int Render::Shutdown()
{
    fn_80210020();
    fn_802131D8();
    fn_802118F0();
    fn_80211FC8();
    fn_8020F76C();
    fn_8020F00C();
    fn_8021032C();
    fn_802134AC();
    fn_80215B70();
    return 1;
}
