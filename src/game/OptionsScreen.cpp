/* Options screen: maps menu items to game options, reads and writes them, and
   reacts to changes (a rumble test pulse, sound modes, and option 6 when the
   screen closes). */

#include "game/cu_8007F12C.h"
#include "game/OptionsScreenMsg.h"
#include "game/OptionsScreen.h"
#include "game/FELoop.h"
#include "game/fn_8007F828.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_8017F584.h"
#include "engine/viewporttypes.h"

extern "C" {
extern void *lbl_803EB688;

int ConGetChannelInfo(int a, int b);
int fn_801E195C(int a);
void RumbleStart(int a, int b, int c);
int fn_800B6644(int a);
void fn_80185F4C(int a, int b);
Viewport_t *fn_8018A854(void);
void fn_8018A7F8(Viewport_t *pObject, int mode);

static int _OptionsScreen_iSavedOption6 = 3;
static int _OptionsScreen_iStoredArg = -1;
static int _OptionsScreen_aiOptionIds[21] = {
    24, 0, 8, 6, 10, 9, 11, 12, 3, 4, 5, 24, 14, 15, 16, 17, 1, 2, 1, 18, 19,
};

void OptionsScreenEnter(void)
{
    FELoopIsMainFEActive();
    _OptionsScreen_iSavedOption6 = fn_8007F828(6);
}

void OptionsScreenExit(void)
{
    int value;

    if (_OptionsScreen_iSavedOption6 != fn_8007F828(6)) {
        if (fn_8007F828(6) == 0) {
            value = 0;
        } else {
            value = 1;
        }
        fn_8021D7B8(lbl_803EB688, 0x8000000F, 1, &value);
        if (fn_8007F828(6) == 1) {
            fn_8018A7F8(fn_8018A854(), 0);
        } else {
            fn_8018A7F8(fn_8018A854(), fn_8007F828(6));
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
        if (flag != 0 && fn_8007F828(9) != 0) {
            if (FELoopIsMainFEActive() != 0) {
                for (i = 0; i < 8; i++) {
                    if (fn_801E195C(ConGetChannelInfo(i, 0)) == 2) {
                        RumbleStart(i, 127, 20);
                    }
                }
            } else {
                for (i = 0; i < 10; i++) {
                    if (fn_801E195C(ConGetChannelInfo(i, 0)) == 2 && fn_800B6644(i) != 255) {
                        RumbleStart(i, 127, 20);
                    }
                }
            }
        }
        break;
    case 8:
    case 9:
    case 10:
        fn_80185F4C(id, flag);
        break;
    }
}

void OptionsScreenSetOption(int index, int value, int notify)
{
    int flag = 0;

    if (_OptionsScreen_aiOptionIds[index] == 24) {
        return;
    }
    if (fn_8017F584() == 8 && _OptionsScreen_aiOptionIds[index] == 8) {
        return;
    }
    if (fn_8007F828(_OptionsScreen_aiOptionIds[index]) == 0 && value != 0) {
        flag = 1;
    }
    fn_8007F6F8(_OptionsScreen_aiOptionIds[index], value);
    if (notify == 1) {
        OptionsScreenOnChange(index, flag);
    }
}

int OptionsScreenGetOption(unsigned int index)
{
    int result = 0;
    int id = OptionsScreenGetOptionId(index);

    if (id != 24) {
        result = fn_8007F828(id);
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
        fn_8007F548();
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
