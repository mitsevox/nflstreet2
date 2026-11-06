/* Front-end message routing for two groups of screens: the team screens (skill
   levels, player pick-up, profile to controller) and the options screens
   (settings, EA Trax, tutorial, unlocks, audio settings, cheat codes). Also holds
   the profile-to-controller handler and the unlock list. */

#include "game/OptionsScreenMsg.h"
#include "game/DbTableCursorInline.h"
#include "game/cu_80181330.h"
#include "game/MsgCheatCodes.h"

extern "C" {
int MsgPlayerPickupHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001ED98(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001FE10(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int MsgTutorialHandleMessage(unsigned int id, void *pArgs, int unused, int *pResult);
int MsgAudioSettingsHandleMessage(unsigned int id, OptionsScreenMsg_t *pBlock, int unused, int *pResult);
int TournBracketMsg(unsigned int id, void *pArgs, int unused, int *pResult);
int OptionsScreenMsg(unsigned int id, OptionsScreenMsg_t *pBlock, int unused, int *pResult);
int OptAudioHandleMessage(unsigned int id, void *pArgs, int unused, int *pResult);
signed char fn_80186B38(int a);
void fn_80186ED8(signed char a);
void fn_80186F30(signed char a, int b);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
}

static int _MsgUnlockList_iSelection = 0;

extern "C" {
void MsgOptionsStubSelect(int index);

int MsgProfileAssignHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    if (id == 0x80000001) {
        fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
        fn_80186F30(-1, 0);
        return 1;
    }
    return 0;
}

int MsgTeamDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 2:
        return MsgProfileAssignHandleMessage(id, pArgs, unused, pResult);
    case 0:
        return fn_8001ED98(id, pArgs, unused, pResult);
    case 1:
        return MsgPlayerPickupHandleMessage(id, pArgs, unused, pResult);
    case 4:
        return TournBracketMsg(id, pArgs, unused, pResult);
    }
    return 0;
}

int MsgUnlockListHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int MsgOptionsStubHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);

int MsgOptionsDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 0:
        return OptionsScreenMsg(id, (OptionsScreenMsg_t *)pArgs, unused, pResult);
    case 1:
        return fn_8001FE10(id, pArgs, unused, pResult);
    case 2:
        return MsgTutorialHandleMessage(id, pArgs, unused, pResult);
    case 5:
        return OptAudioHandleMessage(id, pArgs, unused, pResult);
    case 6:
        return MsgAudioSettingsHandleMessage(id, (OptionsScreenMsg_t *)pArgs, unused, pResult);
    case 7:
        return MsgCheatCodesHandleMessage(id, (CheatCodesArg_t *)pArgs, unused, pResult);
    case 4:
        return MsgUnlockListHandleMessage(id, pArgs, unused, pResult);
    case 3:
        return MsgOptionsStubHandleMessage(id, pArgs, unused, pResult);
    }
    return 0;
}

int MsgUnlockListHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000004:
        *pResult = 9;
        break;
    case 0x80000002:
    case 0x80000003:
        break;
    case 0x80000001: {
        int handle = fn_8022F3D4(fn_8022F4BC());
        DbTableCursor cursor;
        int *pA;
        int *pB;
        int base;
        unsigned int mask;
        int i;

        cursor.OpenTable(0x464E4955, 0x44494755, 0, 0, handle);
        pA = (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4);
        pB = (int *)(pArgs[2].i + (*pArgs[2].pi + 1) * 4);
        fn_80186ED8(fn_80186B38(fn_8022F4BC()));
        base = pArgs[0].i * 4;
        for (i = 0; i < 12; i++) {
            pA[i] = i + base;
            pB[i] = 0;
        }
        mask = cursor.GetColumnValue(0x504C5555);
        for (i = base; i <= 9; i++) {
            if (mask & (1 << i)) {
                pB[i - base] = 0;
            } else {
                pB[i - base] = 1;
            }
        }
        _MsgUnlockList_iSelection = 0;
        break;
    }
    case 0x80000006:
        *pArgs[1].pi = pArgs[0].i + 40;
        _MsgUnlockList_iSelection = pArgs[0].i;
        break;
    case 0x80000005: {
        if (pArgs[0].i == 1) {
            _MsgUnlockList_iSelection++;
        } else {
            _MsgUnlockList_iSelection--;
        }
        if (_MsgUnlockList_iSelection > 39) {
            _MsgUnlockList_iSelection = 0;
        }
        {
            int handle = fn_8022F3D4(fn_8022F4BC());
            DbTableCursor cursor;
            unsigned int mask;
            int index;

            cursor.OpenTable(0x464E4955, 0x44494755, 0, 0, handle);
            mask = cursor.GetColumnValue(0x504C5555);
            index = _MsgUnlockList_iSelection;
            if (index >= 0 && index <= 9 && !(mask & (1 << index))) {
                do {
                    if (pArgs[0].i == 1) {
                        index++;
                    } else {
                        index--;
                    }
                } while (index >= 0 && index <= 9 && !(mask & (1 << index)));
                _MsgUnlockList_iSelection = index;
            }
            if (_MsgUnlockList_iSelection < 0) {
                _MsgUnlockList_iSelection = 39;
            }
            *pArgs[1].pi = _MsgUnlockList_iSelection + 40;
        }
        break;
    }
    case 0x80000007:
        _MsgUnlockList_iSelection = 0;
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgOptionsStubSelect(int index)
{
}

int MsgOptionsStubHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
    case 0x80000002:
        break;
    case 0x80000003:
        MsgOptionsStubSelect(pArgs[0].i - 1);
        break;
    default:
        return 0;
    }
    return 1;
}
}
