/* The Sys module: starts and stops the memory manager, its heaps and auxiliary RAM, the system and
   real-time clock, and installs the reset-button check. */
#include "game/Module.h"
#include "game/MemPoolDesc.h"
#include "engine/MemExtern.h"
#include "engine/system.h"
#include <dolphin/__vm.h>

/* Argument of MemInit. */
struct MemInitParams_t {
    char mLogName[64];
    MemPoolDesc_t *mpArena;
};

/* Argument of SysInit. */
struct SysInitParams_t {
    SysInitParams_t(unsigned char unknown0, unsigned char unknown1, unsigned char unknown2)
        : mUnknown0(unknown0), mUnknown1(unknown1), mUnknown2(unknown2) {}
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

extern "C" {
int MemCardUIIsResetLocked(void);
int DSInit(void);
int DSShutdown(void);
void ArenaSetupInit(void);
void ArenaSetupShutdown(void);
int MemInit(MemInitParams_t *pConfig);
int MemShutdown(void);
int fn_801D2130(MemPoolDesc_t *pArena);
int fn_801D2570(int id);
void MemSetDefaultHeap(int a);
int SysInit(SysInitParams_t *pDesc);
int SysShutdown(void);
}

static MemInitParams_t _Sys_MemInitParams = { "memory.log" };
static void *sDependencies[] = { 0 };
Sys gSys;

extern "C" {
static int _SysCanReset(int resetRequested)
{
    return !MemCardUIIsResetLocked();
}
}

ModuleDependency *Sys::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Sys::GetLinks() { return 0; }
const char *Sys::GetName() { return "Sys"; }

int Sys::Init()
{
    MemPoolDesc_t *pDb;
    MemPoolDesc_t *pDebug;
    MemPoolDesc_t *pAuxRam;

    DSInit();
    ArenaSetupInit();
    _Sys_MemInitParams.mpArena = MemPoolGetDesc(1);
    MemInit(&_Sys_MemInitParams);
    fn_801D2130(MemPoolGetDesc(0x20));
    fn_801D2130(MemPoolGetDesc(0x100));
    pDb = MemPoolGetDesc(2);
    VMAlloc(pDb->mUnknownC, pDb->mUnknown10);
    fn_801D2130(MemPoolGetDesc(2));
    pDebug = MemPoolGetDesc(8);
    if (pDebug->mUnknown10 != 0) {
        fn_801D2130(pDebug);
    }
    pAuxRam = MemPoolGetDesc(0x10);
    MemInitExternHeap(0x10, 1, (char *)pAuxRam->mUnknownC, pAuxRam->mUnknown10, 0x20, 0x20);
    MemSetDefaultHeap(1);
    SysInitParams_t desc(1, 0, 1);
    SysInit(&desc);
    SysInitRealTimeClock();
    SysSetResetCallback(_SysCanReset);
    return 1;
}

int Sys::Shutdown()
{
    SysShutdown();
    if (MemPoolGetDesc(8)->mUnknown10 != 0) {
        fn_801D2570(8);
    }
    fn_801D2570(2);
    fn_801D2570(0x20);
    MemShutdown();
    ArenaSetupShutdown();
    DSShutdown();
    return 1;
}
