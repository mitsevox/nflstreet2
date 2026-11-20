/* The instant replay screen: starts and ends replay playback and reports the replay position and
   length. */
#include "game/UISTextArg.h"


struct ReplayScreenArgs_t {
    int mUnknown0;
    UISTextArg_t *mpArgs;
};

extern "C" {
extern void *gpReplay;

int ReplayHandleControl(void *p, int a, int b);
int ReplayGetLength(void *p);
int ReplayGetPosition(void *p);
void HudPost3AOn(void);
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
    ReplayHandleControl(gpReplay, 7, 0);
}

extern "C" int ReplayScreenGetPosition(void) { return ReplayGetLength(gpReplay); }

extern "C" void ReplayScreenExit(void)
{
    UISGameLockPad(_ReplayScreen_iSavedValue);
    _ReplayScreen_iSavedValue = -1;
    UISHeldObjEnable(_ReplayScreen_bSavedFlag);
    ReplayHandleControl(gpReplay, 9, 0);
    HudPost3AOn();
}

extern "C" int ReplayScreenGetLength(void) { return ReplayGetPosition(gpReplay); }

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
