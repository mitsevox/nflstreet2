#include <dolphin/base/PPCArch.h>

typedef void (*voidfunctionptr)(void);

extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

static void __init_cpp(void);
void __init_user(void);
void abort(void);
void exit(int status);
void _ExitProcess(void);

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
