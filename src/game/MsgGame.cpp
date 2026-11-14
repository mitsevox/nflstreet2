/* Game-wide front-end message handler: the first handler the message dispatcher tries, it answers the generic message ids that no screen handler took (game setup values, Street Event sides, controllers, profiles, player status and portrait, user text buffers, demo and memory card flags). */
#include "game/ResLoad.h"
#include "game/fn_8022F478.h"
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/cu_80181330.h"
#include "game/GameInfo.h"
#include "game/MsgGame.h"
#include "game/GameOptions.h"
#include "game/GameModeType.h"
#include <string.h>
#include "game/UISGameMsg.h"
#include "game/fn_800B65A0.h"

/* Filled per slot by the mini-game slot query; the constructor leaves
   mUnknown8 unset. */
struct MiniGameSlotInfo_t {
    MiniGameSlotInfo_t() : mUnknown0(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

/* One argument or result slot of the message handler MsgGameHandleMessage. */
union MsgGameArg_t {
    int i;
    float f;
    int *pi;
    float *pf;
    Params_80005284 *pParams;
};

extern "C" {
int fn_8022F4BC(void);
int fn_80186B38(int a);
int GauntletSetCurrentTeam(int a, int b);
int fn_8001194C(int a);
int UserRecGetCount(void);
int fn_80186D64(int a);
void fn_80186F9C(int a, char *pText, int c);
int fn_801486A0(void);
void fn_80152940(Class_80148A58 *pObject, int index, MiniGameSlotInfo_t *pInfo);
int fn_80178AE0(void);
void PerCheckConnectAll(void);
void PortDbOpenSides(DbCursor *pObject);
void PortDbCloseSides(DbCursor *pObject);
int PortDbGetPort(DbCursor *pObject);
int PortDbGetSide(DbCursor *pObject);
int ConGetChannelInfo(int a, int b);
int PerGetDeviceStatus(int a);
int fn_800B81A4(void);
float fn_80237260(int stream);
int GameTextGetPadPlayer(int a);
int GameTextFindPlayerPad(int a);
void FEPlyrSetPlayer(int index, int a, int b);
int GameTextGetMemCardNames(char *pText0, int length0, char *pText1, int length1, char *pText2, int length2, char *pText3, int length3);
int fn_801D6850(void);
void GameTextGetEnteredName(char *pText, int length);
void fn_801410F4(int a);
void fn_80186A44(signed char a);
int fn_8022F358(int index);
void fn_80186F30(signed char a, int b);
void fn_80186F8C(int a);
unsigned char MemCardScreenGetFlag(void);
int UserStringGet(char *pDest, int count);
void UserStringSet(const char *pSource, int count);
int TextEntryGetCharSet(int a, char *pText, int length);
int ChallengeIsActive(void);
int ChallengeIsPairingGame(void);
int GameModeTypeIsSpecial(void);
void fn_80083E1C(DbCursor *pObject, int a);
int fn_8008400C(DbCursor *pObject);
int fn_80084360(DbCursor *pObject);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
void fn_80010150(int a);
int fn_8000FCDC(void);
void fn_80011600(int a, int b, int c);
void UISGameSetInputFlag(unsigned char value);
int PauseGetValue(void);
int fn_8022F384(int a);
void *fn_8021EA44(int index);
void *fn_8021E984(void *p, int a);
void fn_8000FCD4(int a);
int fn_8000FCCC(void);
unsigned char GameTextGetBootFinished(void);
void GameTextSetBootFinished(unsigned char a);
void TutorialGetHudPosition(float *pX, float *pY, float *pZ);
int fn_8005902C(void);
int PortDbHasSides(void);
int TeamLogoGetHandle(int a);
int fn_8022E558(void);
int fn_8022E560(void);
}

static int _MsgGame_iSetupState = 0;
static int _MsgGame_iSetupId = -1;
static int _MsgGame_iSetupArg = -1;
static int _MsgGame_iPendingChoice = -1;
static int _MsgGame_bFEStarted = 0;
static unsigned char _MsgGame_bOverride = 0;
static unsigned char _MsgGame_bMemCardActive = 0;

extern "C" {
int MsgGameMsg1Result(void)
{
    return 2;
}

int MsgGameMsg136Result(void)
{
    return 0;
}

int MsgGameMsg7Result(void)
{
    return 0;
}

float MsgGameRandRange(float min, float max)
{
    return min + (max - min) * fn_80237260(1);
}

void MsgGameSetSetup(int a, int b, int c)
{
    _MsgGame_iSetupState = a;
    _MsgGame_iSetupId = b;
    _MsgGame_iSetupArg = c;
    if (a == 0 && b == 0x69 && GameModeTypeGet() == 8) {
        GauntletSetCurrentTeam(fn_80186B38(fn_8022F4BC()), 0x3FF);
    }
}

int MsgGameCheckSetting6(void)
{
    int value = GameOptionsGet(6);

    return value == 1 || value == 2;
}

int MsgGameGetProfileValue(int a, int *pResult)
{
    int value = -1;

    if (a != -1) {
        value = fn_8001194C(a == 0);
    }
    *pResult = UserRecGetCount();
    bool found = false;
    if (*pResult == 2) {
        *pResult = fn_80186D64(value);
        found = true;
    }
    return found;
}

void MsgGameSetPendingChoice(int a)
{
    _MsgGame_iPendingChoice = a;
}

int MsgGameSetProfileText(int a, char *pText)
{
    int state;

    if (a == -1) {
        a = 1;
    }
    state = UserRecGetCount();
    fn_80186F9C(state, pText, a);
    return state;
}

int MsgGameStreetEventHasOpenSlot(void)
{
    int result = 0;

    if (FELoopIsMainFEActive() == 0) {
        MiniGameSlotInfo_t info;

        switch (fn_801486A0()) {
        case 0:
            result = 1;
            break;
        case 1:
            for (unsigned int i = 0; i <= 3; i++) {
                fn_80152940(fn_80148A58(), i, &info);
                if (info.mUnknown20 == 0xFF) {
                    result = 1;
                    break;
                }
            }
            break;
        default: {
            unsigned char first = fn_800B65A0(0) != 0xFF;
            unsigned char second = fn_800B65A0(1) != 0xFF;

            result = first ^ second;
            break;
        }
        }
    }
    return result;
}

int MsgGameStreetEventCheckSide(void)
{
    if (fn_801486A0() != 15) {
        return fn_80148A58()->vfn_13();
    }
    return fn_800B65A0(fn_80178AE0()) != 0xFF;
}

int MsgGameFindActivePort(void)
{
    int result = -1;

    if (FELoopIsMainFEActive() != 0) {
        DbCursor cursor;
        int searching = 1;

        PerCheckConnectAll();
        PortDbOpenSides(&cursor);
        for (int found = DbCursorFirst(&cursor); found && searching; found = DbCursorNext(&cursor)) {
            result = PortDbGetPort(&cursor);
            PortDbGetSide(&cursor);
            searching = PerGetDeviceStatus(ConGetChannelInfo(result, 0)) == 2;
        }
        PortDbCloseSides(&cursor);
        if (searching) {
            result = -1;
        }
    } else {
        int value = fn_800B81A4();

        if (value != 0xFF) {
            result = value;
        }
    }
    return result;
}

int MsgGameGetSetupState(void)
{
    return _MsgGame_iSetupState;
}

int MsgGameGetSetupArg(void)
{
    return _MsgGame_iSetupArg;
}

void MsgGameIgnoreValue(int a)
{
}

void MsgGameSetSetupState(int a)
{
    _MsgGame_iSetupState = a;
}

int MsgGameTakePendingChoice(void)
{
    int value = _MsgGame_iPendingChoice;

    _MsgGame_iPendingChoice = -1;
    return value;
}

unsigned char MsgGameGetFEStarted(void)
{
    return _MsgGame_bFEStarted;
}

void MsgGameSetFEStarted(int a)
{
    _MsgGame_bFEStarted = a;
}

void MsgGameSetMemCardActive(unsigned char a)
{
    _MsgGame_bMemCardActive = a;
}

void MsgGameFillPortStates(int *pValues);
void MsgGameGetPlayerStatus(int id, int *pStatus, int *pTeam);
int MsgGameGetPlayerPortrait(int id);

int MsgGameHandleMessage(unsigned int id, MsgGameArg_t *pArgs, int unused, MsgGameArg_t *pResult)
{
    switch (id) {
    case 1:
        pResult->i = MsgGameMsg1Result();
        break;
    case 0x136:
        pResult->i = MsgGameMsg136Result();
        break;
    case 7:
        pResult->i = MsgGameMsg7Result();
        break;
    case 8:
        MsgGameGetPlayerStatus(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 9:
        pResult->f = MsgGameRandRange(pArgs[0].f, pArgs[1].f);
        break;
    case 0xA:
        *pArgs[0].pi = GameTextGetPadPlayer(*pArgs[0].pi);
        break;
    case 0x139:
        pResult->i = GameTextFindPlayerPad(pArgs[0].i);
        break;
    case 0xB:
        MsgGameSetSetup(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0xC:
        pResult->i = MsgGameCheckSetting6();
        break;
    case 0xF: {
        int index = pArgs[0].pi[0] + 1;

        MsgGameFillPortStates(&pArgs[0].pi[index]);
        break;
    }

    case 0xD:
        pResult->i = MsgGameGetPlayerPortrait(pArgs[0].i);
        break;
    case 0xE:
        FEPlyrSetPlayer(pArgs[1].i, pArgs[0].i, 0);
        break;
    case 0x5E:
        MsgGameSetMemCardActive(pArgs[0].i);
        break;
    case 0x5F:
        pResult->i = _MsgGame_bMemCardActive;
        break;
    case 0x114:
        pResult->i = GameTextGetMemCardNames(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength,
                                 pArgs[1].pParams->mpText, pArgs[1].pParams->mLength,
                                 pArgs[2].pParams->mpText, pArgs[2].pParams->mLength,
                                 pArgs[3].pParams->mpText, pArgs[3].pParams->mLength);
        break;
    case 0xDB:
        pResult->i = fn_801D6850();
        break;
    case 6:
        GameTextGetEnteredName(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength);
        break;
    case 0x10:
        fn_801410F4(2);
        break;
    case 0x13:
        pResult->i = UserRecGetCount();
        break;
    case 0x1F0:
        fn_80186A44(pArgs[0].i);
        break;
    case 0x1EF:
        if (pArgs[0].i == -1) {
            fn_8022F478(fn_8022F358((signed char)pArgs[1].i));
        } else {
            fn_80186F30(pArgs[1].i, pArgs[0].i != 0);
        }
        break;
    case 0x14:
        fn_80186D64(fn_8001194C(pArgs[0].i == 0));
        break;
    case 0x23:
        pResult->i = MsgGameGetProfileValue(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x24:
        pResult->i = MsgGameSetProfileText(pArgs[0].i, pArgs[1].pParams->mpText);
        break;
    case 0x25:
        fn_80186F8C(pArgs[0].i != 0);
        break;
    case 0x21: {
        int value = GameOptionsGet(12);

        if (value == 1 && FELoopIsMainFEActive() != 0) {
            pResult->i = value;
        } else {
            pResult->i = 0;
        }
        break;
    }
    case 0x26:
        if (_MsgGame_bOverride != 0 || InGameIsDemo() != 0 || (_MsgGame_bFEStarted != 0 && MemCardScreenGetFlag() != 0)) {
            pResult->i = 1;
        } else {
            pResult->i = 0;
        }
        break;
    case 0x3A:
    case 0x3C:
        pResult->i = UserStringGet(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength);
        break;
    case 0x3B:
        UserStringSet(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength);
        break;
    case 0x3D:
        pResult->i = TextEntryGetCharSet(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x109:
        pResult->i = strcmp(pArgs[0].pParams->mpText, pArgs[1].pParams->mpText);
        break;
    case 0x12A:
        pResult->i = stricmp(pArgs[0].pParams->mpText, pArgs[1].pParams->mpText);
        break;
    case 0x104:
        pResult->i = ChallengeIsActive();
        break;
    case 0x105:
        pResult->i = ChallengeIsPairingGame();
        break;
    case 0xE0:
        pResult->i = GameModeTypeIsSpecial();
        break;
    case 0xED: {
        DbCursor cursor;
        char name[32];

        fn_80083E1C(&cursor, 0);
        if (fn_80084034(&cursor, pArgs[0].i, 0)) {
            fn_80083F88(&cursor, name, sizeof(name));
            strnzcpy(pArgs[1].pParams->mpText, name, pArgs[1].pParams->mLength);
        } else {
            strnzcpy(pArgs[1].pParams->mpText, "", pArgs[1].pParams->mLength);
        }
        fn_80083F68(&cursor);
        break;
    }
    case 0x103:
        fn_80010150(pArgs[0].i);
        break;
    case 0xFF: {
        int value = fn_8000FCDC();

        fn_80011600(pArgs[0].i, pArgs[1].i, value);
        break;
    }

    case 0x113:
        UISGameSetInputFlag(pArgs[0].i == 1);
        break;
    case 0x107:
        if (PauseGetValue() == -1) {
            pResult->i = -1;
        } else {
            pResult->i = PauseGetValue();
        }
        break;
    case 0x122:
        pResult->i = MsgGameGetFEStarted();
        break;
    case 0x11F:
        MsgGameSetFEStarted(pArgs[0].i == 1);
        break;
    case 0x108:
        pResult->i = fn_8022F384(fn_8022F4BC());
        break;
    case 0x111:
        pResult->i = MsgGameFindActivePort();
        break;
    case 0x13A:
        pResult->i = PerGetDeviceStatus(ConGetChannelInfo(pArgs[0].i, 0)) == 2;
        break;
    case 0x19C:
        pResult->i = 0xFF;
        break;
    case 0xF5:
        InGameSetDemo();
        FELoopConfigureEntry(0, -1, -1, -2, -2, -2);
        break;
    case 0x134:
        pResult->i = GameOptionsGet(20) != 0;
        break;
    case 0x144: {
        void *pObject = fn_8021EA44(1);
        int high = pArgs[1].i >> 16;
        int low = pArgs[1].i & 0xFFFF;

        pResult->i = ResIsLoaded(fn_8021E984(pObject, high), low);

        break;
    }

    case 0x189:
        fn_8000FCD4(pArgs[0].i);
        break;
    case 0x172:
        pResult->i = GameModeTypeGet();
        break;
    case 0x17C:
        pResult->i = fn_8000FCCC();
        break;
    case 0x91: {
        int result = 0;

        if (GameTextGetBootFinished()) {
            result = UserRecGetCount() == 0;
        }
        pResult->i = result;
        GameTextSetBootFinished(0);
        break;
    }
    case 0x181: {
        float position[3];

        TutorialGetHudPosition(&position[0], &position[1], &position[2]);
        *pArgs[0].pf = position[0];
        *pArgs[1].pf = position[1];
        *pArgs[2].pf = position[2];
        break;
    }

    case 0x186:
        MsgGameSetPendingChoice(pArgs[0].i);
        break;
    case 0x38:
        pResult->i = 1;
        break;
    case 0x190:
        pResult->i = MsgGameStreetEventHasOpenSlot();
        break;
    case 0x191:
        pResult->i = MsgGameStreetEventCheckSide();
        break;
    case 0xCB:
        pResult->i = 0;
        break;
    case 0x195:
        pResult->i = 0;
        break;
    case 0x196:
        pResult->i = 0;
        break;
    case 0x19D:
        pResult->i = fn_8005902C();
        break;
    case 5:
    case 0xBB:
    case 0xBC:
    case 0x102:
    case 0x106:
    case 0x11E:
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgGameFillPortStates(int *pValues)
{
    DbCursor cursor;

    if (PortDbHasSides()) {
        for (int i = 3; i >= 0; i--) {
            pValues[i] = -1;
        }
        PortDbOpenSides(&cursor);
        if (DbCursorFirst(&cursor)) {
            do {
                int key = PortDbGetPort(&cursor);
                int value = PortDbGetSide(&cursor);
                int index = GameTextGetPadPlayer(key);

                if (index != -1) {
                    pValues[index] = value == 0 ? 0 : value == 1 ? 1 : -1;

                }
            } while (DbCursorNext(&cursor));
        }
        PortDbCloseSides(&cursor);
    }
}

void MsgGameGetPlayerStatus(int id, int *pStatus, int *pTeam)
{
    DbCursor cursor;
    int team = 2;
    int mode;
    int result;

    *pStatus = 0;
    *pTeam = TeamLogoGetHandle(-1);
    mode = GameModeTypeGet();
    result = FELoopIsMainFEActive();
    if (mode == 7) {
        if (result) {
            DbCursorOpen(&cursor, 0x4D414554, 0x44494754, 0, 0, 0x54415453);
        } else {
            fn_80083E1C(&cursor, 0);
        }
        if (fn_80084034(&cursor, id, 0)) {
            *pStatus = fn_80084158(&cursor);
            if (*pStatus == 0) {
                if (id == GameInfoGet(1)) {
                    *pStatus = 0x85;
                } else {
                    *pStatus = 0x86;
                }
            } else if (!fn_80084438(&cursor)) {
                if (result) {
                    team = fn_80084360(&cursor);
                    if (team != 0 && team != 1) {
                        team = 2;
                    }
                } else if (fn_8022E558() == id) {
                    team = 0;
                } else if (fn_8022E560() == id) {
                    team = 1;
                }
                switch (team) {
                case 0:
                    *pTeam = TeamLogoGetHandle(0);
                    break;
                case 1:
                    *pTeam = TeamLogoGetHandle(1);
                    break;
                }
            }
        }
        fn_80083F68(&cursor);
    } else if (mode == 2 || mode == 4 || mode == 13) {
        if (id == GameInfoGet(1)) {
            *pStatus = 0x85;
        } else {
            *pStatus = 0x86;
        }
    } else if (mode == 11) {
        if (id == GameInfoGet(1)) {
            fn_80083E1C(&cursor, 0);
            if (fn_80084034(&cursor, id, 0)) {
                *pStatus = fn_80084158(&cursor);
            } else {
                *pStatus = 0x85;
            }
            fn_80083F68(&cursor);
        } else {
            *pStatus = 0x86;
        }
    } else if (id == 10001) {
        *pStatus = 0x8E;
    } else {
        if (result) {
            fn_80083E40(&cursor, 0, 0x54415453);
        } else {
            fn_80083E1C(&cursor, 0);
        }
        if (fn_80084034(&cursor, id, 0)) {
            if (!result) {
                if (fn_8008400C(&cursor) != 5) {
                    team = 2;
                } else if (fn_8022E558() == id) {
                    team = 0;
                } else {
                    team = 1;
                }
            } else {
                team = fn_80084360(&cursor);
                if (team != 0 && team != 1) {
                    team = 2;
                }
            }

            if (!fn_80084438(&cursor)) {
                switch (team) {
                case 0:
                    *pTeam = TeamLogoGetHandle(0);
                    break;
                case 1:
                    *pTeam = TeamLogoGetHandle(1);
                    break;
                }
            }
            *pStatus = fn_80084158(&cursor);
        }
        fn_80083F68(&cursor);
    }
}

int MsgGameGetPlayerPortrait(int id)
{
    Object_8008044C cursor;
    int result = 0;

    if (FELoopIsMainFEActive()) {
        fn_8008044C(&cursor, 0, 0x54415453);
    } else {
        fn_8008040C(&cursor, 0);
    }
    if (PlayerDbSeekId(&cursor, id, 0)) {
        result = PlayerDbGetPortraitId(&cursor);
    }
    fn_8008056C(&cursor);
    return result;
}
}
