/* Street Event setup: the screen that sets up the chosen Street Event before play.
   It builds the option rows for the event (game type, timer or rounds, play-to,
   player count), lets the player switch the player-pool groups on and off (NFL
   players, legends, created and randomized players) and hands the choices to the
   game when the screen closes. */

#include "game/Class_80148A58.h"
#include "game/DbCursor.h"
#include "game/cu_80181330.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"

struct StreetEventPoolToggle_t {
    int mValue;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    int mUnknown8;
};

struct StreetEventOption_t {
    char **mppItems;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mCount;
    unsigned char mSelection;
    char mName[13];
    char mDescription[71];
};

struct StreetEventSetup_t {
    StreetEventPoolToggle_t mToggles[4];
    StreetEventOption_t mOptions[3];
    unsigned char mUnknown324;
    unsigned char mUnknown325;
};

struct MiniGameSettings_t {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
void MsgTeamPickSetMode(int a, int b);
void MsgTeamPickSetSources(int a);
void MsgTeamPickRequestTeamSave(void);
void PortDbOpenSides(DbCursor *pObject);
void PortDbCloseSides(DbCursor *pObject);
unsigned char PortDbCountSidePlayers(int a);
int fn_80082414(int index);
int fn_801486A0(void);
void fn_8014F3DC(int ticks);
int MsgGameGetSetupState(void);
void StoryTeamLoadUserTeams(int a, int b);
void fn_8018C48C(int handle);
void fn_8018D7E0(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
char *fn_801C3084(const char *pString, int c);

extern MiniGameSettings_t lbl_8031BDD4;
extern int lbl_802A11F4[];
extern char *lbl_803EB2E8;

void MsgStreetEventSetupFreeOptions(StreetEventSetup_t *pState);
void MsgStreetEventSetupSetOption(StreetEventOption_t *pOption, const char *pName, const char *pItems, const char *pDescription,
                 unsigned char flag);
}

static StreetEventSetup_t *_MsgStreetEventSetup_pState = 0;
static int _MsgStreetEventSetup_iMinPool = 14;

extern "C" {
void MsgStreetEventSetupCountPool(void)
{
    _MsgStreetEventSetup_pState->mToggles[0].mUnknown8 = fn_80082414(0);
    _MsgStreetEventSetup_pState->mToggles[1].mUnknown8 = fn_80082414(1);
    _MsgStreetEventSetup_pState->mToggles[2].mUnknown8 = fn_80082414(3);
    _MsgStreetEventSetup_pState->mToggles[3].mUnknown8 = fn_80082414(2);
}

void MsgStreetEventSetupBuildOptions(StreetEventSetup_t *pState)
{
    int count;

    MsgStreetEventSetupSetOption(&pState->mOptions[0], 0, 0, 0, 0);
    MsgStreetEventSetupSetOption(&pState->mOptions[1], 0, 0, 0, 0);
    MsgStreetEventSetupSetOption(&pState->mOptions[2], 0, 0, 0, 0);
    count = 3;
    switch (fn_801486A0()) {
    case 1:
        MsgStreetEventSetupSetOption(&pState->mOptions[0], "Game Type", "Single Round|^Elimination",
                    "Play a single round or multiple rounds with Elimination.", 0);
        MsgStreetEventSetupSetOption(&pState->mOptions[1], "Play To", lbl_803EB2E8,
                    "Select the length of the Street Event, or play to score.", 0);
        _MsgStreetEventSetup_iMinPool = 7;
        break;
    case 0:
        MsgStreetEventSetupSetOption(&pState->mOptions[0], "Timer", "3 Minutes|^5 Minutes|8 Minutes|10 Minutes",
                    "Select the Length of the Street Event.", 0);
        count = 2;
        _MsgStreetEventSetup_iMinPool = 6;
        break;
    case 2:
        MsgStreetEventSetupSetOption(&pState->mOptions[0], "Game Type",
                    (pState->mUnknown324 <= 1 && pState->mUnknown325 <= 1) ? "2 on 2|^1 on 1" : "2 on 2",
                    "Select the Game Type for the Street Event.", 0);
        MsgStreetEventSetupSetOption(&pState->mOptions[1], "Rounds", "5 Rounds|^10 Rounds|15 Rounds|20 Rounds",
                    "Select the Number of Rounds for the Street Event.", 0);
        _MsgStreetEventSetup_iMinPool = 2;
        break;
    case 3:
    case 4:
        break;
    }
    MsgStreetEventSetupSetOption(&pState->mOptions[count - 1], "Player Count", "^40 Random|All Players",
                "Choose the number of players to put in the pool.", 0);
}

void MsgStreetEventSetupFreeOptions(StreetEventSetup_t *pState)
{
    unsigned char i;
    unsigned char j;

    for (i = 0; i <= 2; i++) {
        if (pState->mOptions[i].mCount != 0) {
            for (j = 0; j < pState->mOptions[i].mCount; j++) {
                fn_801D2BD0(pState->mOptions[i].mppItems[j]);
            }
            fn_801D2BD0(pState->mOptions[i].mppItems);
        }
    }
}

void MsgStreetEventSetupInitPool(StreetEventSetup_t *pState)
{
    pState->mToggles[0].mValue = 1;
    pState->mToggles[1].mValue = 2;
    pState->mToggles[2].mValue = 8;
    pState->mToggles[3].mValue = 4;
    pState->mToggles[0].mUnknown5 = 1;
    pState->mToggles[1].mUnknown5 = 1;
    pState->mToggles[2].mUnknown5 = 1;
    pState->mToggles[3].mUnknown5 = 0;
    pState->mToggles[0].mUnknown4 = 1;
    pState->mToggles[1].mUnknown4 = 0;
    pState->mToggles[2].mUnknown4 = 0;
    pState->mToggles[3].mUnknown4 = 0;
    if (_MsgStreetEventSetup_pState->mToggles[0].mUnknown8 != 0) {
        _MsgStreetEventSetup_pState->mToggles[0].mUnknown6 = 0;
    } else {
        _MsgStreetEventSetup_pState->mToggles[0].mUnknown6 = 1;
        _MsgStreetEventSetup_pState->mToggles[0].mUnknown4 = 0;
    }
    if (_MsgStreetEventSetup_pState->mToggles[1].mUnknown8 != 0) {
        _MsgStreetEventSetup_pState->mToggles[1].mUnknown6 = 0;
    } else {
        _MsgStreetEventSetup_pState->mToggles[1].mUnknown6 = 1;
        _MsgStreetEventSetup_pState->mToggles[1].mUnknown4 = 0;
    }
    if (_MsgStreetEventSetup_pState->mToggles[2].mUnknown8 != 0) {
        _MsgStreetEventSetup_pState->mToggles[2].mUnknown6 = 0;
    } else {
        _MsgStreetEventSetup_pState->mToggles[2].mUnknown6 = 1;
        _MsgStreetEventSetup_pState->mToggles[2].mUnknown4 = 0;
    }
}

void MsgStreetEventSetupApplyOptions(StreetEventSetup_t *pState)
{
    switch (fn_801486A0()) {
    case 1:
    {
        unsigned char index;

        switch (pState->mOptions[0].mSelection) {
        case 0:
            lbl_8031BDD4.mUnknown40 = 0;
            break;
        case 1:
            lbl_8031BDD4.mUnknown40 = 1;
            break;
        }
        index = pState->mOptions[1].mSelection;
        if (index <= 14) {
            lbl_8031BDD4.mUnknown32 = lbl_802A11F4[index];
            lbl_8031BDD4.mUnknown36 = 0;
        } else {
            lbl_8031BDD4.mUnknown36 = lbl_802A11F4[index];
            lbl_8031BDD4.mUnknown32 = 0;
        }
        break;
    }
    case 0:
    {
        int minutes = 0;

        switch (pState->mOptions[0].mSelection) {
        case 0:
            minutes = 3;
            break;
        case 1:
            minutes = 5;
            break;
        case 2:
            minutes = 8;
            break;
        case 3:
            minutes = 10;
            break;
        }
        fn_8014F3DC(minutes * 60);
        break;
    }
    case 2:
    {
        int rounds = 5;
        int type = pState->mOptions[0].mSelection;

        switch (pState->mOptions[1].mSelection) {
        case 0:
            break;
        case 1:
            rounds = 10;
            break;
        case 2:
            rounds = 15;
            break;
        case 3:
            rounds = 20;
            break;
        }
        fn_80148A58()->vfn_07(0, type);
        fn_80148A58()->vfn_07(1, rounds);
        break;
    }
    case 3:
    case 4:
        break;
    }
    MsgStreetEventSetupFreeOptions(pState);
}

void MsgStreetEventSetupInit(void)
{
    _MsgStreetEventSetup_pState = (StreetEventSetup_t *)fn_801D2B7C(sizeof(StreetEventSetup_t), 0, 0);
    fn_801C1F94(_MsgStreetEventSetup_pState, 0, sizeof(StreetEventSetup_t));
    fn_8018D7E0();
    StoryTeamLoadUserTeams(0, 1);
    {
        DbCursor object;

        PortDbOpenSides(&object);
        _MsgStreetEventSetup_pState->mUnknown324 = PortDbCountSidePlayers(0);
        _MsgStreetEventSetup_pState->mUnknown325 = PortDbCountSidePlayers(1);
        PortDbCloseSides(&object);
    }
    _MsgStreetEventSetup_iMinPool = 14;
    MsgStreetEventSetupCountPool();
    MsgStreetEventSetupInitPool(_MsgStreetEventSetup_pState);
    MsgStreetEventSetupBuildOptions(_MsgStreetEventSetup_pState);
}

void MsgStreetEventSetupShutdown(void)
{
    int mask = 0;
    int count = 3;
    int mode;
    int i;

    for (i = 0; i < 4; i++) {
        if (_MsgStreetEventSetup_pState->mToggles[i].mUnknown4 != 0) {
            mask |= _MsgStreetEventSetup_pState->mToggles[i].mValue;
        }
    }
    if (fn_801486A0() == 0) {
        count = 2;
    }
    mode = 0;
    if (_MsgStreetEventSetup_pState->mOptions[count - 1].mSelection != 0) {
        mode = _MsgStreetEventSetup_pState->mOptions[count - 1].mSelection == 1 ? 2 : 0;
    }
    MsgTeamPickSetSources(mask);
    MsgTeamPickSetMode(mode, _MsgStreetEventSetup_iMinPool);
    MsgTeamPickRequestTeamSave();
    MsgStreetEventSetupApplyOptions(_MsgStreetEventSetup_pState);
    if (MsgGameGetSetupState() == 0) {
        fn_8018C48C(0x54415453);
    }
    fn_801D2BD0(_MsgStreetEventSetup_pState);
    _MsgStreetEventSetup_pState = 0;
}

void MsgStreetEventSetupGetRow(int index, int *pEnabled, MenuArg_t text, int *pState)
{
    int selectable = 1;

    if (index >= 1 && index <= 3) {
        *pEnabled = _MsgStreetEventSetup_pState->mOptions[index - 1].mUnknown5;
        if (_MsgStreetEventSetup_pState->mOptions[index - 1].mUnknown5 != 0) {
            fn_801C2EF0(text.pParams->mpText, _MsgStreetEventSetup_pState->mOptions[index - 1].mName, text.pParams->mLength);
        }
        selectable = _MsgStreetEventSetup_pState->mOptions[index - 1].mCount > 1;
    } else if (index >= 4 && index <= 7) {
        *pEnabled = _MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown5;
        if (_MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown5 != 0) {
            const char *pName = index == 4   ? "NFL Players"
                                : index == 5 ? "NFL Legends"
                                : index == 6 ? "Created"
                                : index == 7 ? "Randomized"
                                             : "Unknown";

            fn_801C2EF0(text.pParams->mpText, pName, text.pParams->mLength);
        }
    }
    *pState = 0;
    if (!selectable || (index >= 4 && index <= 7 && _MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown6 != 0)) {
        *pState = 2;
    }
}

int MsgStreetEventSetupChangeRow(int index, int direction, MenuArg_t text)
{
    int changed = 0;
    Params_80005284 *pText = text.pParams;

    if (index >= 1 && index <= 3 ? _MsgStreetEventSetup_pState->mOptions[index - 1].mUnknown5 != 0
                                 : index >= 4 && index <= 7 && _MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown5 != 0) {
        switch (direction) {
        case 0:
            break;
        case 3:
            if (index >= 1 && index <= 3) {
                if (_MsgStreetEventSetup_pState->mOptions[index - 1].mSelection == 0) {
                    _MsgStreetEventSetup_pState->mOptions[index - 1].mSelection = _MsgStreetEventSetup_pState->mOptions[index - 1].mCount - 1;
                } else {
                    _MsgStreetEventSetup_pState->mOptions[index - 1].mSelection--;
                }
            } else if (index >= 4 && index <= 7) {
                _MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown4 = !_MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown4;
            }
            break;
        case 1:
            if (index >= 1 && index <= 3) {
                if (_MsgStreetEventSetup_pState->mOptions[index - 1].mSelection == _MsgStreetEventSetup_pState->mOptions[index - 1].mCount - 1) {
                    _MsgStreetEventSetup_pState->mOptions[index - 1].mSelection = 0;
                } else {
                    _MsgStreetEventSetup_pState->mOptions[index - 1].mSelection++;
                }
            } else if (index >= 4 && index <= 7) {
                _MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown4 = !_MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown4;
            }
            break;
        }
        if (index >= 1 && index <= 3) {
            if (_MsgStreetEventSetup_pState->mOptions[index - 1].mUnknown4 != 0) {
                MsgStreetEventSetupFreeOptions(_MsgStreetEventSetup_pState);
                changed = 1;
                MsgStreetEventSetupBuildOptions(_MsgStreetEventSetup_pState);
            }
            fn_801C2EF0(pText->mpText, _MsgStreetEventSetup_pState->mOptions[index - 1].mppItems[_MsgStreetEventSetup_pState->mOptions[index - 1].mSelection],
                        pText->mLength);
            if (fn_801486A0() == 2 && index == 1) {
                switch (_MsgStreetEventSetup_pState->mOptions[0].mSelection) {
                case 0:
                    _MsgStreetEventSetup_iMinPool = 4;
                    break;
                case 1:
                    _MsgStreetEventSetup_iMinPool = 2;
                    break;
                }
            }
        } else if (index >= 4 && index <= 7) {
            const char *pValue = _MsgStreetEventSetup_pState->mToggles[index - 4].mUnknown4 ? "On" : "Off";

            fn_801C2EF0(pText->mpText, pValue, pText->mLength);
        }
    }
    return changed;
}

void MsgStreetEventSetupGetHelp(int index, MenuArg_t text)
{
    if (index >= 1 && index <= 3) {
        fn_801C2EF0(text.pParams->mpText, _MsgStreetEventSetup_pState->mOptions[index - 1].mDescription, text.pParams->mLength);
    } else if (index >= 4 && index <= 7) {
        const char *pDescription = index == 4   ? "Allow/Disallow NFL Players in the Selection Pool."
                                   : index == 5 ? "Allow/Disallow NFL Legends in the Selection Pool."
                                   : index == 6 ? "Allow/Disallow Created Players in the Selection Pool."
                                   : index == 7 ? "Allow/Disallow Randomly Generated Characters in the Selection Pool."
                                                : "";

        fn_801C2EF0(text.pParams->mpText, pDescription, text.pParams->mLength);
    }
}

void MsgStreetEventSetupSetOption(StreetEventOption_t *pOption, const char *pName, const char *pItems, const char *pDescription,
                 unsigned char flag)
{
    if (pName != 0) {
        fn_801C2EF0(pOption->mName, pName, 12);
    } else {
        pOption->mName[0] = 0;
    }
    if (pName != 0) {
        fn_801C2EF0(pOption->mDescription, pDescription, 70);
    } else {
        pOption->mDescription[0] = 0;
    }
    pOption->mCount = 0;
    if (pItems != 0 && *pItems != 0) {
        const char *p;
        unsigned char i;

        pOption->mSelection = 0;
        pOption->mCount = 1;
        for (p = pItems; *p != 0; p++) {
            if (*p == '|') {
                pOption->mCount++;
            }
        }
        pOption->mppItems = (char **)fn_801D2B7C(pOption->mCount * 4, 0, 0);
        p = pItems;
        for (i = 0; i < pOption->mCount; i++) {
            char *pBar;

            pOption->mppItems[i] = (char *)fn_801D2B7C(14, 0, 0);
            if (*p == '^') {
                pOption->mSelection = i;
                p++;
            }
            fn_801C2EF0(pOption->mppItems[i], p, 13);
            pBar = fn_801C3084(pOption->mppItems[i], '|');
            if (pBar != 0) {
                *pBar = 0;
            }
            p = fn_801C3084(p + 1, '|') + 1;
        }
    } else {
        pOption->mUnknown5 = 0;
        pOption->mSelection = 0;
    }
    pOption->mUnknown5 = pOption->mCount != 0;
    pOption->mUnknown4 = flag;
}

int MsgStreetEventSetupHasEnoughPlayers(void)
{
    unsigned int total;
    int count = 3;

    if (fn_801486A0() == 0) {
        count = 2;
    }
    total = 0;
    if (_MsgStreetEventSetup_pState->mToggles[0].mUnknown4 != 0) {
        total = _MsgStreetEventSetup_pState->mToggles[0].mUnknown8;
    }
    if (_MsgStreetEventSetup_pState->mToggles[1].mUnknown4 != 0) {
        total += _MsgStreetEventSetup_pState->mToggles[1].mUnknown8;
    }
    if (_MsgStreetEventSetup_pState->mToggles[2].mUnknown4 != 0) {
        total += _MsgStreetEventSetup_pState->mToggles[2].mUnknown8;
    }
    if (_MsgStreetEventSetup_pState->mToggles[3].mUnknown4 != 0) {
        total += _MsgStreetEventSetup_pState->mToggles[3].mUnknown8;
    }
    switch (_MsgStreetEventSetup_pState->mOptions[count - 1].mSelection) {
    case 1:
        total = total >= _MsgStreetEventSetup_iMinPool;
        break;
    case 0:
    default:
        total = total >= 40;
        break;
    }
    return total;
}

int MsgStreetEventSetupHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgStreetEventSetupInit();
        break;
    case 0x80000002:
        MsgStreetEventSetupShutdown();
        break;
    case 0x80000003:
        MsgStreetEventSetupGetRow(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3].pi);
        break;
    case 0x80000004:
        *pResult = MsgStreetEventSetupChangeRow(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x80000005:
        MsgStreetEventSetupGetHelp(pArgs[0].i, pArgs[1]);
        break;
    case 0x80000006:
        *pResult = MsgStreetEventSetupHasEnoughPlayers();
        break;
    default:
        return 0;
    }
    return 1;
}
}
