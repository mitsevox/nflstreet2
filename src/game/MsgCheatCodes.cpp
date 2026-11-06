/* Cheat code screen: the player picks a profile, types a code to unlock a cheat and
   turns unlocked cheats on and off; turning one on turns off the cheats it
   conflicts with. */

#include "game/MsgCheatCodes.h"
#include "game/Cheat.h"

static signed char _MsgCheatCodes_cProfile = -1;

extern "C" {
int UserRecGetCount(void);
int fn_80186DF0(signed char *pIndices, int length);
int UserRecGetName(int index, char *pText);
void fn_80186ED8(signed char index);
void CheatEffectRemove(signed char db, int id);
void CheatEffectApply(signed char db, int id);

void MsgCheatCodesCycleProfile(int control)
{
    int count = UserRecGetCount();
    if (_MsgCheatCodes_cProfile == -1 && count > 0) {
        signed char indices[2];
        unsigned char auxiliary[2];
        fn_80186DF0(indices, 2);
        for (int i = 0; i < 2; ++i) {
            if (indices[i] != -1) {
                auxiliary[i] = 1;
            }
        }
        _MsgCheatCodes_cProfile = indices[0];
    }
    if (count > 1) {
        switch (control) {
        case 3:
            --_MsgCheatCodes_cProfile;
            if (_MsgCheatCodes_cProfile < 0) {
                _MsgCheatCodes_cProfile = count - 1;
            }
            break;
        case 1:
            _MsgCheatCodes_cProfile = (_MsgCheatCodes_cProfile + 1) % count;
            break;
        case 0:
            break;
        }
    }
}

int MsgCheatCodesGetProfile(int control, char *pText, int c, int *pValue, int *pFlag)
{
    MsgCheatCodesCycleProfile(control);
    CheatSelectSlot(_MsgCheatCodes_cProfile);
    UserRecGetName(_MsgCheatCodes_cProfile, pText);
    *pValue = CheatCountUnlocked();
    int result = CheatAreAllUnlocked();
    *pFlag = result;
    return result;
}

int MsgCheatCodesGetEntry(int value, char *pText, int length, int *pResult)
{
    int count;
    return CheatGetUnlockedInfo(value, &count, pText, length, pResult);
}

int MsgCheatCodesEnterCode(const char *pCode, int unused, char *pName, int d)
{
    unsigned int value = CheatFindByCode(pCode, unused, pName);
    fn_80186ED8(_MsgCheatCodes_cProfile);
    if (value > 54) {
        return 0;
    }
    if (CheatIsUnlocked(value)) {
        return 2;
    }
    CheatUnlock(value);
    return 1;
}

void MsgCheatCodesDisableConflicts(int value)
{
    switch (value) {
    case 27:
        CheatDisable(26);
        break;
    case 26:
        CheatDisable(27);
        break;
    case 30:
        CheatDisable(44);
        CheatDisable(31);
        CheatDisable(34);
        break;
    case 31:
        CheatDisable(44);
        CheatDisable(30);
        CheatDisable(34);
        break;
    case 44:
        CheatDisable(31);
        CheatDisable(30);
        CheatDisable(34);
        break;
    case 34:
        CheatDisable(31);
        CheatDisable(30);
        CheatDisable(44);
        CheatDisable(33);
        break;
    case 33:
        CheatDisable(34);
        break;
    case 36:
        CheatDisable(37);
        break;
    case 37:
        CheatDisable(36);
        break;
    case 28:
        CheatDisable(29);
        break;
    case 29:
        CheatDisable(28);
        break;
    case 23:
        CheatDisable(24);
        break;
    case 24:
        CheatDisable(23);
        break;
    }
}

void MsgCheatCodesToggle(int value, int *pResult)
{
    int result = CheatGetUnlockedId(value);
    fn_80186ED8(_MsgCheatCodes_cProfile);
    int changed;
    if (CheatIsEnabled(result)) {
        CheatDisable(result);
        CheatEffectRemove(_MsgCheatCodes_cProfile, result);
        changed = 0;
    } else {
        CheatEnable(result);
        CheatEffectApply(_MsgCheatCodes_cProfile, result);
        MsgCheatCodesDisableConflicts(result);
        changed = 1;
    }
    *pResult = changed;
}

int MsgCheatCodesHandleMessage(unsigned int id, CheatCodesArg_t *pArgs, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pArgs[0].mpUnknown0 = UserRecGetCount();
        break;
    case 0x80000002:
        _MsgCheatCodes_cProfile = -1;
        CheatClearSlot();
        break;
    case 0x80000004:
    {
        TextRecord_t *pRecord = pArgs[1].mpRecord;
        MsgCheatCodesGetEntry(pArgs[0].mUnknown0, pRecord->mUnknown8, pRecord->mUnknown4,
                    pArgs[2].mpUnknown0);
        break;
    }
    case 0x80000003:
    {
        TextRecord_t *pRecord = pArgs[1].mpRecord;
        MsgCheatCodesGetProfile(pArgs[0].mUnknown0, pRecord->mUnknown8, pRecord->mUnknown4,
                    pArgs[2].mpUnknown0, pArgs[3].mpUnknown0);
        break;
    }
    case 0x80000006:
    {
        CheatCodesArg_t *pFirst = pArgs[0].mpWords;
        CheatCodesArg_t *pSecond = pArgs[1].mpWords;
        *pResult = MsgCheatCodesEnterCode(pFirst[2].mpCode, pFirst[1].mUnknown0,
                               pSecond[2].mpText, pSecond[1].mUnknown0);
        break;
    }
    case 0x80000005:
        MsgCheatCodesToggle(pArgs[0].mUnknown0, pArgs[1].mpUnknown0);
        break;
    default:
        return 0;
    }
    return 1;
}
}
