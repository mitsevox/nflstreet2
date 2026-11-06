#include "game/Module.h"

extern "C" {
void TMViewportLLNew(int);
void TMViewportLLDelete(void);
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
void TMShaderStockInit(void);
void TMShaderStockShutdown(void);
void TMMaterialListInit(int);
void TMMaterialListShutdown(void);
void TMMaterialInit(int *);
void TMClusterObjInit(int, int);
void TMClusterObjShutdown(void);
}

static void *sDependencies[] = { 0 };
Render gRender;

ModuleDependency *Render::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Render::GetLinks() { return 0; }
const char *Render::GetName() { return "Render"; }

int Render::Init()
{
    int counts[9] = { 0, 4000, 600, 300 };

    TMViewportLLNew(0x4000);
    TMRenderInit();
    TMGeomInitChannelBuffer(0x23000);
    TMModelInit(16);
    TMTexLibRegistryInit(8);
    TMShaderLibRegistryInit(64, 8);
    TMShaderStockInit();
    TMMaterialListInit(0x1480);
    TMMaterialInit(counts);
    TMClusterObjInit(4000, 1);
    return 1;
}

int Render::Shutdown()
{
    TMMaterialListShutdown();
    TMShaderStockShutdown();
    TMShaderLibRegistryShutdown();
    TMTexLibRegistryShutdown();
    TMModelShutdown();
    TMGeomFreeChannelBuffer();
    TMRenderShutdown();
    TMClusterObjShutdown();
    TMViewportLLDelete();
    return 1;
}
