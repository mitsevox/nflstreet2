#include <dolphin/base/PPCArch.h>

typedef void (*voidfunctionptr)(void);

extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

static void __init_cpp(void);
void __init_user(void);
void abort(void);
void exit(int status);
void _ExitProcess(void);

void __init_hardware(void);
void __OSPSInit(void);
void __OSFPRInit(void);
void __OSCacheInit(void);

__declspec(section ".init") asm void __init_hardware(void)
{
    nofralloc
    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0
    mflr r31
    bl __OSPSInit
    bl __OSFPRInit
    bl __OSCacheInit
    mtlr r31
    blr
}

void __init_user(void) { __init_cpp(); }

#pragma peephole off
static void __init_cpp(void) {
    voidfunctionptr* constructor;

    for (constructor = _ctors; *constructor; constructor++) {
        (*constructor)();
    }
}

static void __fini_cpp(void) {
    voidfunctionptr* destructor;

    for (destructor = _dtors; *destructor; destructor++) {
        (*destructor)();
    }
}

void abort(void) { _ExitProcess(); }

void exit(int status) {
    __fini_cpp();
    _ExitProcess();
}
#pragma peephole reset

void _ExitProcess(void) { PPCHalt(); }
