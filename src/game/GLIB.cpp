#include "game/Module.h"
#include <dolphin/gx/GXStruct.h>

/* Parameter block passed to fn_801CE138, which copies all 44 bytes. */
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

int fn_801CE138(GlibParams_801CE138 *pParams);
int fn_801CE190(void);
int fn_801CED2C(void);
int fn_801CED34(void);
void fn_801CEE84(void *pTable, int count);
void fn_801CEC90(void *pTable, int count);
int fn_801CECCC(int index);
void fn_801CECC8(void);
}

static GlibParams_801CE138 sParams = { 640, 448, 0, 0, 0, 4, { 1 }, { 0 }, { 0 }, 0x100000, 1, 1 };
static void *sDependencies[] = { 0 };
GLIB gGLIB;

ModuleDependency *GLIB::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *GLIB::GetLinks() { return 0; }
const char *GLIB::GetName() { return "GLIB"; }

int GLIB::Init()
{
    fn_801CE138(&sParams);
    fn_801CED2C();
    fn_801CEE84(lbl_802ED510, 16);
    fn_801CEC90(lbl_802ED510, 16);
    fn_801CECCC(14);
    fn_801CECC8();
    return 1;
}

int GLIB::Shutdown()
{
    fn_801CED34();
    fn_801CE190();
    return 1;
}
