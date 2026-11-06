/* Gauntlet ladder screen: works out where the ladder starts from the number
   of teams left, reports each ladder team and whether it has been beaten, and
   remembers the team the player selected. */

union GauntletMsgWord_t {
    int *mpOut;
    int mValue;
};

struct GauntletMsgArgs_t {
    GauntletMsgWord_t mUnknown0;
    int *mpUnknown4;
    int *mpUnknown8;
};

extern "C" {
int fn_8022F4BC(void);
int fn_80186B38(int a);
int fn_8018F3D8(int a);
int fn_8018F288(int a, int b);
int fn_8022F384(int a);
void EnvSetLocked(int a, int b, int c);
void fn_8018F4C4(int a);

static const signed char _GauntletScreen_acTeamOrder[33] = {
    8, 23, 7, 16, 26, 19, 5, 14, 17, 32, 29, 18, 3, 1, 6, 15, 2,
    27, 31, 12, 25, 11, 28, 4, 20, 24, 30, 13, 10, 9, 21, 22, 34,
};
static int _GauntletScreen_iSelection;

void GauntletScreenEnter(int *pOut)
{
    int value;

    if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 24) {
        value = 8;
    } else if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 16) {
        value = 16;
    } else if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 8) {
        value = 24;
    } else if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 0) {
        value = 32;
    } else {
        value = 33;
    }
    *pOut = value;
    if (fn_8018F288(fn_80186B38(fn_8022F4BC()), 34) != 0) {
        EnvSetLocked(fn_8022F384(fn_8022F4BC()), 11, 0);
    }
}

void GauntletScreenGetTeam(int index, int *pOut, int *pFlag)
{
    *pOut = _GauntletScreen_acTeamOrder[index];
    if (fn_8018F288(fn_80186B38(fn_8022F4BC()), *pOut) != 0) {
        *pFlag = 1;
    } else {
        *pFlag = 0;
    }
}

int GauntletScreenGetSelection(void)
{
    return _GauntletScreen_iSelection;
}

int GauntletScreenMsg(unsigned int id, GauntletMsgArgs_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        GauntletScreenEnter(pBlock->mUnknown0.mpOut);
        _GauntletScreen_iSelection = -1;
        break;
    case 0x80000002:
        break;
    case 0x80000003:
        GauntletScreenGetTeam(pBlock->mUnknown0.mValue, pBlock->mpUnknown4, pBlock->mpUnknown8);
        break;
    case 0x80000004:
        _GauntletScreen_iSelection = pBlock->mUnknown0.mValue;
        break;
    case 0x80000005:
        if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) == -1) {
            *pResult = 1;
            fn_8018F4C4(fn_80186B38(fn_8022F4BC()));
        } else {
            *pResult = 0;
        }
        return 0;
    default:
        return 0;
    }
    return 1;
}
}
