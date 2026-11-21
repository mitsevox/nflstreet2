#include "game/Module.h"

struct VptInitBlock_t {
    int mUnknown0;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
};

static VptInitBlock_t _Vpt_InitBlock = {5, 6, 40, 0, 12};

extern "C" {

int VptInit(void *);
int VptShutdown(void);
}

static ModuleDependency sDependencies[] = { &gSys, &gMat, &gObj, 0 };
Vpt gVpt;

ModuleDependency *Vpt::GetDependencies() { return sDependencies; }
ModuleDependency *Vpt::GetLinks() { return 0; }
const char *Vpt::GetName() { return "Vpt"; }

int Vpt::Init()
{
    VptInit(&_Vpt_InitBlock);
    return 1;
}

int Vpt::Shutdown()
{
    VptShutdown();
    return 1;
}
