/* Game side of the UIStudio debug window: forwards its line and help-line requests to installed print callbacks and closes the window. */
#include "game/UISTextArg.h"


struct DebugWindowMsg_t {
    int mUnknown0;
    UISTextArg_t *mpArgs;
    int mUnknown8;
};

extern "C" {
extern void *gUISMainInfo;

void fn_8021956C(void *p, int a, int b, int c);
}

static void (*_DebugWindow_pPrintLineFn)(int, int, int) = 0;
static void (*_DebugWindow_pPrintHelpLineFn)(int, int, int, int) = 0;
static unsigned char _DebugWindow_bOpen = 0;

extern "C" void DebugWindowPrintLine(int a, int b, int c)
{
    if (_DebugWindow_pPrintLineFn != 0) {
        _DebugWindow_pPrintLineFn(a, b, c);
    }
}

extern "C" void DebugWindowPrintHelpLine(int a, int b, int c, int d)
{
    if (_DebugWindow_pPrintHelpLineFn != 0) {
        _DebugWindow_pPrintHelpLineFn(a, b, c, d);
    }
}

extern "C" void DebugWindowOnOpen(void) {}

extern "C" unsigned char DebugWindowIsOpen(void);

extern "C" void DebugWindowClose(void)
{
    if (DebugWindowIsOpen()) {
        fn_8021956C(gUISMainInfo, 2, 3, 1);
        _DebugWindow_pPrintLineFn = 0;
        _DebugWindow_pPrintHelpLineFn = 0;
        _DebugWindow_bOpen = 0;
    }
}

extern "C" unsigned char DebugWindowIsOpen(void) { return _DebugWindow_bOpen; }

extern "C" int DebugWindowHandleMsg(unsigned int id, DebugWindowMsg_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        DebugWindowOnOpen();
        break;
    case 0x80000002:
        DebugWindowPrintLine(pBlock->mUnknown0, pBlock->mpArgs->mUnknown8, pBlock->mpArgs->mUnknown4);
        break;
    case 0x80000003:
        DebugWindowPrintHelpLine(pBlock->mUnknown0, pBlock->mpArgs->mUnknown8, pBlock->mpArgs->mUnknown4, pBlock->mUnknown8);
        break;
    default:
        return 0;
    }
    return 1;
}
