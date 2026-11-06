/* The instant replay screen: starts and ends replay playback and reports the replay position and
   length. */
#include "game/ArgsPrefix_8017F6A8.h"


struct ReplayScreenArgs_t {
    int mUnknown0;
    ArgsPrefix_8017F6A8 *mpArgs;
};

extern "C" {
extern void *lbl_803EA368;

int fn_8002CA74(void *p, int a, int b);
int fn_8002D0D0(void *p);
int fn_8002D0FC(void *p);
void fn_8017DBCC(void);
void UISGameLockPad(int value);
int UISGameUnlockPad(void);
unsigned char UISHeldObjEnable(unsigned char value);
}

static unsigned char _ReplayScreen_bSavedFlag = 0;
static int _ReplayScreen_iSavedValue = -1;

extern "C" void ReplayScreenEnter(void)
{
    _ReplayScreen_iSavedValue = UISGameUnlockPad();
    _ReplayScreen_bSavedFlag = UISHeldObjEnable(0);
    fn_8002CA74(lbl_803EA368, 7, 0);
}

extern "C" int ReplayScreenGetPosition(void) { return fn_8002D0D0(lbl_803EA368); }

extern "C" void ReplayScreenExit(void)
{
    UISGameLockPad(_ReplayScreen_iSavedValue);
    _ReplayScreen_iSavedValue = -1;
    UISHeldObjEnable(_ReplayScreen_bSavedFlag);
    fn_8002CA74(lbl_803EA368, 9, 0);
    fn_8017DBCC();
}

extern "C" int ReplayScreenGetLength(void) { return fn_8002D0FC(lbl_803EA368); }

extern "C" void ReplayScreenNotify(int a, int b, int c) {}

extern "C" int ReplayScreenHandleMessage(unsigned int id, ReplayScreenArgs_t *pBlock, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        ReplayScreenEnter();
        break;
    case 0x80000002:
        *pResult = ReplayScreenGetPosition();
        break;
    case 0x80000003:
        ReplayScreenExit();
        break;
    case 0x80000004:
        *pResult = ReplayScreenGetLength();
        break;
    case 0x80000005:
        ReplayScreenNotify(pBlock->mUnknown0, pBlock->mpArgs->mUnknown8, pBlock->mpArgs->mUnknown4);
        break;
    default:
        return 0;
    }
    return 1;
}
