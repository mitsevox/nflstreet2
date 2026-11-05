#include "game/Module.h"
#include <dolphin/gx/GXStruct.h>

/* Parameter block passed to GlibInit, which copies all 44 bytes. */
struct GlibParams_801CE138 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24[2];
    GXColor mUnknown26;
    unsigned char mUnknown30[2];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
extern char lbl_802ED510[];

int GlibInit(GlibParams_801CE138 *pParams);
int GlibShutdown(void);
int GlibRenderInit(void);
int GlibRenderShutdown(void);
void GlibBinAllocList(void *pTable, int count);
void GlibRenderSetBinList(void *pTable, int count);
int GlibRenderGetBin(int index);
void GlibRenderSetDefaultBin(void);
}

static GlibParams_801CE138 sParams = { 640, 448, 0, 0, 0, 4, { 1 }, { 0 }, { 0 }, 0x100000, 1, 1 };
static void *sDependencies[] = { 0 };
GLIB gGLIB;

ModuleDependency *GLIB::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *GLIB::GetLinks() { return 0; }
const char *GLIB::GetName() { return "GLIB"; }

int GLIB::Init()
{
    GlibInit(&sParams);
    GlibRenderInit();
    GlibBinAllocList(lbl_802ED510, 16);
    GlibRenderSetBinList(lbl_802ED510, 16);
    GlibRenderGetBin(14);
    GlibRenderSetDefaultBin();
    return 1;
}

int GLIB::Shutdown()
{
    GlibRenderShutdown();
    GlibShutdown();
    return 1;
}
