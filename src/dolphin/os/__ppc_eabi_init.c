#include <dolphin/base/PPCArch.h>

void __init_cpp(void);
void __init_user(void);
void _ExitProcess(void);

void __init_user(void) { __init_cpp(); }

void _ExitProcess(void) { PPCHalt(); }
