#include "game/Module.h"
#include "game/SndgPathfinder.h"

/* Argument of SndInit. */
struct SndInitDesc_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    unsigned short mUnknown16;
    unsigned short mUnknown18;
    unsigned short mUnknown20;
    unsigned short mUnknown22;
    unsigned short mUnknown24;
    char mUnknown26[6];
    void *mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
};

extern "C" {
void fn_801F76E8(void);
void fn_801F7710(void);
unsigned long fn_8023CEE0(void);
void SndSetOutputMode(int a, int b);
void SndSetAllocHeap(int a);
int SndInit(SndInitDesc_t *pDesc);
int SndShutdown(void);
void fn_80071790(void);
}

static void *sDependencies[] = { 0 };
Snd gSnd;

ModuleDependency *Snd::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Snd::GetLinks() { return 0; }
const char *Snd::GetName() { return "Snd"; }

int Snd::Init()
{
    SndInitDesc_t desc;

    fn_801F76E8();
    desc.mUnknown0 = 0x90301;
    desc.mUnknown4 = 0x12400;
    desc.mUnknown8 = 0xC00000;
    desc.mUnknown12 = 0x400000;
    desc.mUnknown16 = 24;
    desc.mUnknown18 = 6;
    desc.mUnknown20 = 1;
    desc.mUnknown22 = 5;
    desc.mUnknown24 = 12;
    desc.mUnknown32 = gSndgAramRegions;
    desc.mUnknown36 = 0;
    desc.mUnknown40 = 0;
    desc.mUnknown44 = 0;
    desc.mUnknown48 = 32;
    desc.mUnknown52 = 0;
    desc.mUnknown53 = 1;
    desc.mUnknown54 = 1;
    if (fn_8023CEE0()) {
        SndSetOutputMode(3, 0);
    }
    SndSetAllocHeap(256);
    SndInit(&desc);
    fn_80071790();
    return 1;
}

int Snd::Shutdown()
{
    SndShutdown();
    fn_801F7710();
    return 1;
}
