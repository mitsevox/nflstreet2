#include "game/Module.h"

extern "C" {
void fn_80215B6C(int);
void fn_80215B70(void);
void TMRenderInit(void);
void TMRenderShutdown(void);
void TMGeomInitChannelBuffer(int);
void TMGeomFreeChannelBuffer(void);
void TMModelInit(int);
void TMModelShutdown(void);
void TMTexLibRegistryInit(int);
void TMTexLibRegistryShutdown(void);
void TMShaderLibRegistryInit(int, int);
void TMShaderLibRegistryShutdown(void);
void fn_80213160(void);
void fn_802131D8(void);
void TMMaterialListInit(int);
void TMMaterialListShutdown(void);
void TMMaterialInit(int *);
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
    TMRenderInit();
    TMGeomInitChannelBuffer(0x23000);
    TMModelInit(16);
    TMTexLibRegistryInit(8);
    TMShaderLibRegistryInit(64, 8);
    fn_80213160();
    TMMaterialListInit(0x1480);
    TMMaterialInit(counts);
    fn_80213444(4000, 1);
    return 1;
}

int Render::Shutdown()
{
    TMMaterialListShutdown();
    fn_802131D8();
    TMShaderLibRegistryShutdown();
    TMTexLibRegistryShutdown();
    TMModelShutdown();
    TMGeomFreeChannelBuffer();
    TMRenderShutdown();
    fn_802134AC();
    fn_80215B70();
    return 1;
}
