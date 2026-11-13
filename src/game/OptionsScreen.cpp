/* Options screen: maps menu items to game options, reads and writes them, and
   reacts to changes (a rumble test pulse, sound modes, and option 6 when the
   screen closes). */

#include "game/GameOptions.h"
#include "game/OptionsScreenMsg.h"
#include "game/OptionsScreen.h"
#include "game/FELoop.h"
#include "game/fn_8021D7B8.h"
#include "game/GameModeType.h"
#include "engine/viewporttypes.h"

extern "C" {
extern void *gUISMainInfo;

int ConGetChannelInfo(int a, int b);
int PerGetDeviceStatus(int a);
void RumbleStart(int a, int b, int c);
int fn_800B6644(int a);
void OptAudioOnOptionChanged(int a, int b);
Viewport_t *UISGameGetMainViewport(void);
void UISGameSetAspect(Viewport_t *pObject, int mode);

static int _OptionsScreen_iSavedOption6 = 3;
static int _OptionsScreen_iStoredArg = -1;
static int _OptionsScreen_aiOptionIds[21] = {
    24, 0, 8, 6, 10, 9, 11, 12, 3, 4, 5, 24, 14, 15, 16, 17, 1, 2, 1, 18, 19,
};

void OptionsScreenEnter(void)
{
    FELoopIsMainFEActive();
    _OptionsScreen_iSavedOption6 = GameOptionsGet(6);
}

void OptionsScreenExit(void)
{
    int value;

    if (_OptionsScreen_iSavedOption6 != GameOptionsGet(6)) {
        if (GameOptionsGet(6) == 0) {
            value = 0;
        } else {
            value = 1;
        }
        fn_8021D7B8(gUISMainInfo, 0x8000000F, 1, &value);
        if (GameOptionsGet(6) == 1) {
            UISGameSetAspect(UISGameGetMainViewport(), 0);
        } else {
            UISGameSetAspect(UISGameGetMainViewport(), GameOptionsGet(6));
        }
    }
}

void OptionsScreenStoreArg(int value)
{
    _OptionsScreen_iStoredArg = value;
}

void OptionsScreenOnChange(int id, int flag)
{
    unsigned int i;

    switch (id) {
    case 5:
        if (flag != 0 && GameOptionsGet(9) != 0) {
            if (FELoopIsMainFEActive() != 0) {
                for (i = 0; i < 8; i++) {
                    if (PerGetDeviceStatus(ConGetChannelInfo(i, 0)) == 2) {
                        RumbleStart(i, 127, 20);
                    }
                }
            } else {
                for (i = 0; i < 10; i++) {
                    if (PerGetDeviceStatus(ConGetChannelInfo(i, 0)) == 2 && fn_800B6644(i) != 255) {
                        RumbleStart(i, 127, 20);
                    }
                }
            }
        }
        break;
    case 8:
    case 9:
    case 10:
        OptAudioOnOptionChanged(id, flag);
        break;
    }
}

void OptionsScreenSetOption(int index, int value, int notify)
{
    int flag = 0;

    if (_OptionsScreen_aiOptionIds[index] == 24) {
        return;
    }
    if (GameModeTypeGet() == 8 && _OptionsScreen_aiOptionIds[index] == 8) {
        return;
    }
    if (GameOptionsGet(_OptionsScreen_aiOptionIds[index]) == 0 && value != 0) {
        flag = 1;
    }
    GameOptionsSet(_OptionsScreen_aiOptionIds[index], value);
    if (notify == 1) {
        OptionsScreenOnChange(index, flag);
    }
}

int OptionsScreenGetOption(unsigned int index)
{
    int result = 0;
    int id = OptionsScreenGetOptionId(index);

    if (id != 24) {
        result = GameOptionsGet(id);
    }
    return result;
}

int OptionsScreenMsg(unsigned int id, OptionsScreenMsg_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000005:
        OptionsScreenStoreArg(pBlock->mUnknown0);
        break;
    case 0x80000004:
        OptionsScreenSetOption(pBlock->mUnknown0, pBlock->mUnknown4, pBlock->mUnknown8);
        break;
    case 0x80000003:
        *pResult = OptionsScreenGetOption(pBlock->mUnknown0);
        break;
    case 0x80000007:
        GameOptionsResetMarked();
        OptionsScreenSetOption(5, 1, 0);
        break;
    case 0x80000001:
        OptionsScreenEnter();
        break;
    case 0x80000002:
        OptionsScreenExit();
        break;
    case 0x80000006:
        break;
    default:
        return 0;
    }
    return 1;
}

int OptionsScreenGetOptionId(unsigned int index)
{
    int id = 24;

    if (index <= 20) {
        id = _OptionsScreen_aiOptionIds[index];
    }
    return id;
}
}
