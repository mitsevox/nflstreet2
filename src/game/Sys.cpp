#include "game/Module.h"
#include "game/Record_802CC680.h"

/* Argument of fn_801D2054. */
struct Object_801D2054 {
    char mLogName[64];
    Record_802CC680 *mpArena;
};

/* Argument of fn_801F7824. */
struct Object_801F7824 {
    Object_801F7824(unsigned char unknown0, unsigned char unknown1, unsigned char unknown2)
        : mUnknown0(unknown0), mUnknown1(unknown1), mUnknown2(unknown2) {}
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

extern "C" {
int fn_80185274(void);
int fn_801C6584(void);
int fn_801C65E4(void);
void fn_80025E00(void);
void fn_80025E28(void);
int fn_801D2054(Object_801D2054 *pConfig);
int fn_801D20C8(void);
int fn_801D2130(Record_802CC680 *pArena);
int fn_801D2570(int id);
void fn_801D277C(int a);
int fn_801D3B0C(int id, int a, int base, int size, int b, int c);
int fn_80245514(int base, int size);
int fn_801F7824(Object_801F7824 *pDesc);
int fn_801F79C0(void);
void fn_801F8248(void);
int fn_801F8868(int (*pCallback)());
}

static Object_801D2054 sMemoryConfig = { "memory.log" };
static void *sDependencies[] = { 0 };
Sys gSys;

extern "C" {
static int fn_8019A70C()
{
    return !fn_80185274();
}
}

ModuleDependency *Sys::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Sys::GetLinks() { return 0; }
const char *Sys::GetName() { return "Sys"; }

int Sys::Init()
{
    Record_802CC680 *pDb;
    Record_802CC680 *pDebug;
    Record_802CC680 *pAuxRam;

    fn_801C6584();
    fn_80025E00();
    sMemoryConfig.mpArena = fn_80025E50(1);
    fn_801D2054(&sMemoryConfig);
    fn_801D2130(fn_80025E50(0x20));
    fn_801D2130(fn_80025E50(0x100));
    pDb = fn_80025E50(2);
    fn_80245514(pDb->mUnknownC, pDb->mUnknown10);
    fn_801D2130(fn_80025E50(2));
    pDebug = fn_80025E50(8);
    if (pDebug->mUnknown10 != 0) {
        fn_801D2130(pDebug);
    }
    pAuxRam = fn_80025E50(0x10);
    fn_801D3B0C(0x10, 1, pAuxRam->mUnknownC, pAuxRam->mUnknown10, 0x20, 0x20);
    fn_801D277C(1);
    Object_801F7824 desc(1, 0, 1);
    fn_801F7824(&desc);
    fn_801F8248();
    fn_801F8868(fn_8019A70C);
    return 1;
}

int Sys::Shutdown()
{
    fn_801F79C0();
    if (fn_80025E50(8)->mUnknown10 != 0) {
        fn_801D2570(8);
    }
    fn_801D2570(2);
    fn_801D2570(0x20);
    fn_801D20C8();
    fn_80025E28();
    fn_801C65E4();
    return 1;
}
