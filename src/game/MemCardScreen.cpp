/* Memory card screen: installs the callbacks that list the save slots and
   files, and answers the screen's messages (an option, a forced slot, whether
   the card is busy). */

#include "game/fn_8007F6F8.h"
#include "game/Callees_801D57E0.h"
#include "game/Callees_8002A138.h"
#include "game/cu_8018422C.h"
#include "game/FMCAPPORT.h"

extern "C" {
int fn_8002A1B0(int, int);
void fn_8002A330(int, int, int *, int *, int);
void fn_8002A478(int *, int *);
void MemCardScreenListBegin(int, int *);
void MemCardScreenListReset();
int MemCardScreenListGetItem(int *, int *, int *, int *);
}

static unsigned char _MemCardScreen_bFlag = 0;
static int _MemCardScreen_iUnusedArg = 2;
static int _MemCardScreen_iListPos;
static int _MemCardScreen_iForcedSlot;
static MemCardListCallbacks_t _MemCardScreen_ListCallbacks = {
    MemCardScreenListBegin, MemCardScreenListReset, MemCardScreenListGetItem, 0, 0
};

extern "C" void MemCardScreenInstallList()
{
    fn_801D6714(-1);
    fn_801851A4(&_MemCardScreen_ListCallbacks);
}

extern "C" void MemCardScreenListBegin(int value, int *pCount)
{
    int a;
    int b;
    int index;

    *pCount = 9999;
    fn_8002A478(&a, &b);
    index = fn_8002A190(a, b);
    if (index == -1) {
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        index = 0;
        if (_MemCardScreen_iForcedSlot != -1) {
            index = _MemCardScreen_iForcedSlot;
        }
    } else if (_MemCardScreen_iForcedSlot != -1 && _MemCardScreen_iForcedSlot != index) {
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        index = _MemCardScreen_iForcedSlot;
    }
    fn_801D6714(index);
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6650(8);
}

extern "C" void MemCardScreenListReset()
{
    _MemCardScreen_iListPos = 0;
}

extern "C" int MemCardScreenListGetItem(int *p0, int *p4, int *p8, int *p12)
{
    unsigned char flag = 0;
    int a;
    int b;

    fn_8002A478(&a, &b);
    _MemCardScreen_iListPos = 0;
    do {
        fn_8002A330(0, _MemCardScreen_iListPos, p4, p12, 0);
        _MemCardScreen_iListPos++;
    } while (*p4 != a || *p12 != b);
    *p0 = fn_8002A190(*p4, *p12);
    *p8 = fn_8002A1B0(a, b);
    if (a == 1 || ((a == 2 || a == 3) && fn_8002A138(a, b))) {
        char text[32];
        fn_801D6B24(text, 32);
        *p8 = fn_801D6CF4(text, a, &flag);
        int found = *p8 != -1;
        if (found) {
            *p4 += 256;
        }
    }
    if (fn_8002A190(a, b) == -1) {
        *p4 += 512;
    }
    return 1;
}

extern "C" void MemCardScreenSetFlag(unsigned char value)
{
    _MemCardScreen_bFlag = value;
}

extern "C" unsigned char MemCardScreenGetFlag()
{
    return _MemCardScreen_bFlag;
}

extern "C" int MemCardScreenMsg(unsigned int id, int *p, int c, int *pResult)
{
    switch (id) {
    case 0x80000003:
        fn_8007F6F8(12, *p);
        break;
    case 0x80000004:
        MemCardScreenInstallList();
        break;
    case 0x80000002:
        _MemCardScreen_iForcedSlot = -1;
        fn_801D65B4(0);
        fn_801D654C(1);
        fn_801D6714(0);
        fn_801851D0();
        break;
    case 0x80000005:
        fn_801D6714(-1);
        fn_801D654C(0);
        fn_801851D0();
        break;
    case 0x80000006:
        _MemCardScreen_iForcedSlot = *p;
        break;
    case 0x80000007:
        _MemCardScreen_iUnusedArg = *p;
        break;
    case 0x80000008:
        *pResult = gFMCAPPORT.IsBusy();
        break;
    default:
        return 0;
    }
    return 1;
}
