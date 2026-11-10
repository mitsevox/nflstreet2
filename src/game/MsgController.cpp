/* Controller selection screen: answers the screen's messages that open and close it
   (with its sounds), print a controller's port number, and say whether a controller is
   the current one or is plugged in. */
#include "game/MsgController.h"
#include "game/PauseMenu.h"
#include "game/AudmonEvent.h"
#include "game/FELoop.h"
#include "game/InGame.h"

struct CtrlSelText_t {
    int mUnknown0;
    int mUnknown4;
    char *mpText;
};

union CtrlSelArgWord_t {
    int mValue;
    CtrlSelText_t *mpText;
};

struct CtrlSelArgs_t {
    int mUnknown0;
    CtrlSelArgWord_t mUnknown4;
};

extern "C" {
int fn_8006C854(int index, Vector_80039F5C *pPos);
int MsgGameFindActivePort(void);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int ConGetChannelInfo(int a, int b);
int fn_801E195C(int a);
}

static unsigned char _CtrlSel_bAltSounds = 0;
static unsigned char _CtrlSel_bEndRequest = 0;
static unsigned char _CtrlSel_bOpen = 0;

extern "C" {

void CtrlSelClose(int a, unsigned char b)
{
    _CtrlSel_bOpen = 0;
    if (_CtrlSel_bAltSounds == 0 && InGameIsStopped() == 0) {
        AudmonEventPost(0x72, 0);
    } else {
        fn_8006C854(0x78, 0);
    }
    if (_CtrlSel_bEndRequest) {
        PauseRequestClose();
    }
}

void CtrlSelIdle(int a)
{
}

void CtrlSelFormatNumber(int index, char *pText)
{
    fn_801C2E18(pText, "%d", index + 1);
}

void CtrlSelFormatPort(int a, char *pText)
{
    CtrlSelFormatNumber(ConGetChannelInfo(a, 0), pText);
}

int CtrlSelIsCurrent(int a)
{
    return a == PauseGetValue();
}

int CtrlSelAlwaysFalse(int a)
{
    return 0;
}

int CtrlSelIsConnected(int a)
{
    return fn_801E195C(ConGetChannelInfo(a, 0)) == 2;
}

unsigned char CtrlSelIsOpen(void)
{
    return _CtrlSel_bOpen;
}

int CtrlSelHandleMessage(unsigned int id, CtrlSelArgs_t *pParams, int c, int *pResult)
{
    switch (id) {
    case 0x8000000A:
        _CtrlSel_bEndRequest = pParams->mUnknown0;
        _CtrlSel_bOpen = 1;
        if (_CtrlSel_bEndRequest == 0) {
            if (FELoopIsMainFEActive() != 0 || PauseIsAudioPaused() != 0) {
                _CtrlSel_bAltSounds = 1;
                fn_8006C854(0x77, 0);
            } else {
                _CtrlSel_bAltSounds = 0;
                AudmonEventPost(0x71, 0);
            }
        } else {
            _CtrlSel_bAltSounds = 0;
        }
        break;
    case 0x80000001:
        CtrlSelFormatPort(pParams->mUnknown0, pParams->mUnknown4.mpText->mpText);
        break;
    case 0x80000003:
        CtrlSelClose(pParams->mUnknown0, pParams->mUnknown4.mValue);
        break;
    case 0x8000000B:
        CtrlSelIdle(pParams->mUnknown0);
        break;
    case 0x80000002:
        *pResult = CtrlSelIsCurrent(pParams->mUnknown0);
        break;
    case 0x80000004:
        *pResult = MsgGameFindActivePort();
        break;
    case 0x80000005:
        *pResult = CtrlSelAlwaysFalse(pParams->mUnknown0);
        break;
    case 0x80000006:
        *pResult = CtrlSelIsConnected(pParams->mUnknown0);
        break;
    case 0x80000007:
        *pResult = 0;
        break;
    default:
        return 0;
    }
    return 1;
}

}
