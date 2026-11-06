/* The Sys module: starts and stops the memory manager, its heaps and auxiliary RAM, the system and
   real-time clock, and installs the reset-button check. */
#include "game/Module.h"
#include "game/MemPoolDesc.h"

/* Argument of fn_801D2054. */
struct MemInitParams_t {
    char mLogName[64];
    MemPoolDesc_t *mpArena;
};

/* Argument of fn_801F7824. */
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
int fn_801D2054(MemInitParams_t *pConfig);
int fn_801D20C8(void);
int fn_801D2130(MemPoolDesc_t *pArena);
int fn_801D2570(int id);
void fn_801D277C(int a);
int fn_801D3B0C(int id, int a, int base, int size, int b, int c);
int fn_80245514(int base, int size);
int fn_801F7824(SysInitParams_t *pDesc);
int fn_801F79C0(void);
void fn_801F8248(void);
int fn_801F8868(int (*pCallback)());
}

static MemInitParams_t _Sys_MemInitParams = { "memory.log" };
static void *sDependencies[] = { 0 };
Sys gSys;

extern "C" {
static int _SysCanReset()
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
    fn_801D2054(&_Sys_MemInitParams);
    fn_801D2130(MemPoolGetDesc(0x20));
    fn_801D2130(MemPoolGetDesc(0x100));
    pDb = MemPoolGetDesc(2);
    fn_80245514(pDb->mUnknownC, pDb->mUnknown10);
    fn_801D2130(MemPoolGetDesc(2));
    pDebug = MemPoolGetDesc(8);
    if (pDebug->mUnknown10 != 0) {
        fn_801D2130(pDebug);
    }
    pAuxRam = MemPoolGetDesc(0x10);
    fn_801D3B0C(0x10, 1, pAuxRam->mUnknownC, pAuxRam->mUnknown10, 0x20, 0x20);
    fn_801D277C(1);
    SysInitParams_t desc(1, 0, 1);
    fn_801F7824(&desc);
    fn_801F8248();
    fn_801F8868(_SysCanReset);
    return 1;
}

int Sys::Shutdown()
{
    fn_801F79C0();
    if (MemPoolGetDesc(8)->mUnknown10 != 0) {
        fn_801D2570(8);
    }
    fn_801D2570(2);
    fn_801D2570(0x20);
    fn_801D20C8();
    ArenaSetupShutdown();
    DSShutdown();
    return 1;
}
