/* Cheat code screen: the player picks a profile, types a code to unlock a cheat and
   turns unlocked cheats on and off; turning one on turns off the cheats it
   conflicts with. */

#include "game/MsgCheatCodes.h"
#include "game/cu_80190208.h"

static signed char _MsgCheatCodes_cProfile = -1;

extern "C" {
int fn_801869F0(void);
int fn_80186DF0(signed char *pIndices, int length);
int fn_80186A10(int index, char *pText);
void fn_80186ED8(signed char index);
void fn_80054964(signed char db, int id);
void fn_80054628(signed char db, int id);

void MsgCheatCodesCycleProfile(int control)
{
    int count = fn_801869F0();
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
    fn_80190280(_MsgCheatCodes_cProfile);
    fn_80186A10(_MsgCheatCodes_cProfile, pText);
    *pValue = fn_80190294();
    int result = fn_80190310();
    *pFlag = result;
    return result;
}

int MsgCheatCodesGetEntry(int value, char *pText, int length, int *pResult)
{
    int count;
    return fn_801905E0(value, &count, pText, length, pResult);
}

int MsgCheatCodesEnterCode(const char *pCode, int unused, char *pName, int d)
{
    unsigned int value = fn_80190420(pCode, unused, pName);
    fn_80186ED8(_MsgCheatCodes_cProfile);
    if (value > 54) {
        return 0;
    }
    if (fn_80190768(value)) {
        return 2;
    }
    fn_80190808(value);
    return 1;
}

void MsgCheatCodesDisableConflicts(int value)
{
    switch (value) {
    case 27:
        fn_801909E4(26);
        break;
    case 26:
        fn_801909E4(27);
        break;
    case 30:
        fn_801909E4(44);
        fn_801909E4(31);
        fn_801909E4(34);
        break;
    case 31:
        fn_801909E4(44);
        fn_801909E4(30);
        fn_801909E4(34);
        break;
    case 44:
        fn_801909E4(31);
        fn_801909E4(30);
        fn_801909E4(34);
        break;
    case 34:
        fn_801909E4(31);
        fn_801909E4(30);
        fn_801909E4(44);
        fn_801909E4(33);
        break;
    case 33:
        fn_801909E4(34);
        break;
    case 36:
        fn_801909E4(37);
        break;
    case 37:
        fn_801909E4(36);
        break;
    case 28:
        fn_801909E4(29);
        break;
    case 29:
        fn_801909E4(28);
        break;
    case 23:
        fn_801909E4(24);
        break;
    case 24:
        fn_801909E4(23);
        break;
    }
}

void MsgCheatCodesToggle(int value, int *pResult)
{
    int result = fn_801904E0(value);
    fn_80186ED8(_MsgCheatCodes_cProfile);
    int changed;
    if (fn_801908A0(result)) {
        fn_801909E4(result);
        fn_80054964(_MsgCheatCodes_cProfile, result);
        changed = 0;
    } else {
        fn_8019094C(result);
        fn_80054628(_MsgCheatCodes_cProfile, result);
        MsgCheatCodesDisableConflicts(result);
        changed = 1;
    }
    *pResult = changed;
}

int MsgCheatCodesHandleMessage(unsigned int id, CheatCodesArg_t *pArgs, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pArgs[0].mpUnknown0 = fn_801869F0();
        break;
    case 0x80000002:
        _MsgCheatCodes_cProfile = -1;
        fn_80190288();
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
