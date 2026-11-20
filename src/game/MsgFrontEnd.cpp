/* Message handlers of the main front-end screens, routed by module id: the main menu and its mode loads,
   the start screen, controller and profile select, team select with roster picks (and the created-team
   select for editing), stadium select, records, user stats, credits, team source options and unlocks. */

#include <string.h>

#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/Challenge.h"
#include "game/Request_802329F0.h"
#include "game/DepthChart.h"
#include "game/AutoDepth.h"
#include "game/EditMenu.h"
#include "game/DepthChartSide.h"
#include "game/SndgMusic.h"
#include "game/GameOptions.h"
#include "game/fn_80178D18.h"
#include "game/GameModeType.h"
#include <string.h>
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/TDbCompilePerformOp.h"
#include "game/SyncRandGetRange.h"

/* One signed byte per side, copied as a pair. */
struct MsgPlayerSelectProfiles_t {
    signed char mIndex[2];
};

/* One roster row of a team: the player id, the pick slot it fills (-1 when
   not picked), its position in the list and a key byte (0xFF unset). */
struct MsgTeamSelectEntry_t {
    int mId;
    int mSlot;
    int mIndex;
    int mKey;
};

/* Roster of one team, followed by one more player id. */
struct MsgTeamSelectRoster_t {
    MsgTeamSelectEntry_t mEntries[20];
    int mUnknown140;
};

/* Scroll state of one team's roster list: the top row and the cursor row. */
struct MsgTeamSelectScroll_t {
    int mTop;
    int mRow;
};

/* Pair of bytes saved by MsgTeamSelectInit from the two MsgTeamSelectProfileChanged results. */
struct MsgTeamSelectChanged_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
};

/* Two seven-entry position lists of one team, filled by DepthChartFindPlayer. */
struct MsgTeamSelectDepth_t {
    int mUnknown0[7];
    int mUnknown1C[7];
};

/* One of the twelve 0xB8-byte records of the table at _MsgStadium_pEntries, filled by MsgStadiumGetInfo. */
struct MsgStadiumEntry_t {
    char mText0[0x21];
    char mText21[0x21];
    char mText42[0x66];
    int mUnknownA8;
    int mUnknownAC;
    int mUnknownB0;
    unsigned char mUnknownB4;
    unsigned char mValid;
};

/* Block allocated by MsgUserStatsInit: thirteen column values, three more
   values (the third a signed win/loss streak) and a name. */
struct MsgUserStats_t {
    int mValues[13];
    int mUnknown34;
    int mUnknown38;
    int mStreak;
    char mName[16];
};

/* Record filled by UnlockListReadItem. */
struct UnlockItem_t {
    signed char mIndex;
    char mName[147];
    int mUnknown94;
};

/* Pointer list read by DepthChartGetSideNames (src/game/DepthChart.cpp). */
struct DepthChartText_t;

void *operator new(unsigned int size, int unknown);

extern "C" {
void ChalGameGenerateTeam(int *pId);
int ChalGameHasGeneratedOpponent(void);
int MsgTeamPickHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
void MsgTeamPickFreePool(void);
void MsgTeamPickSetMode(int a, int b);
void MsgTeamPickSetSources(int a);
void MsgTeamPickRequestTeamSave(void);
void MsgChallengeSetResumed(unsigned char value);
int CreditsFetchLine(void);
void CreditsOpen(void);
void CreditsClose(void);
void CreditsCountLines(int *pCount);
void CreditsGetLine(char *pDest, int count);
void CreditsGetLineType(int *pValue);
int ChallengeIsActive(void);
int ChallengeIsPairingGame(void);
unsigned char InGameIsDemo(void);
void DepthChartCyclePending(int group, int kind, int slot, int code, int a, int b);
void DepthChartRevertSide(int group);
void DepthChartGetSideNames(int group, int kind, DepthChartText_t **pPairs);
void DepthChartSwapPending(int group, int kind, int slot);
void DepthChartSetEntryPair(int group, int value, int index0, int index1);
int DepthChartFindPlayer(int group, int value, int *pFirst, int *pSecond);
void PlyrObjsSetTeamIds(unsigned char side, int *pList);
void CheatFlagsAddUser(int a);
void CheatFlagsClear(void);
int DepthChartScreenIsSideShown(unsigned char a);
void DepthChartScreenGetSideName(unsigned char a, int b, char *pText, int length);
void DepthChartScreenGetSpot(unsigned char a, int b, int c, int *pList0, int *pList1, char *pText, int length);
int GauntletScreenGetSelection(void);
void MemCardScreenSetFlag(unsigned char a);
void SndgSfxSetVolume(int index, int a, unsigned char volume);
void SndgMusicStop(void);
void SndgMusicPumpFrame(int a);
int DbCursorGetRow(DbCursor *pObject);
int DbCursorLast(DbCursor *pObject);
int DbCursorPrev(DbCursor *pObject);
int DbCursorGetValue(DbCursor *pObject, int key);
int PortDbSideHasPlayers(int team);
int EnvIsLocked(int index, int id);
void EnvSelect(int id);
void EnvRelease(void);
void EnvGetPictures(int *pA, int *pB);
void EnvGetUIName(char *pDest, int count);
void EnvGetEVLO(int a, int b);
void EnvGetEVDE(int a, int b);
void GameInfoInit(void);
void GameInfoShutdown(void);
unsigned char GameInfoIsInitialized(void);
void GameInfoSet(int index, int value);
int GameInfoGet(int index);
void RecordsBegin(void);
void RecordsEnd(void);
int RecordsGetText(int type, int value, int column, char *pText, int size);
void RecordsSeekRow(int a, int b);
int RecordsGetValue(int a);
void RecordsSetSharedRanks(int a);
void TeamLockOpen(DbCursor *pObject, int db);
void TeamLockClose(DbCursor *pObject);
int TeamLockIsHidden(DbCursor *pObject, int id);
int PlayerDbGetId(Object_8008044C *pObject);
void PlayerDbGetShortName(Object_8008044C *pObject, char *pBuffer, int size);
void PlayerDbGetFullName(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
int PlayerDbGetWeight(Object_8008044C *pObject);
int PlayerDbGetBoostedRating(Object_8008044C *pObject, int index);
void fn_80082558(int a, int b);
void TeamDbOpenQuery(DbCursor *pObject, TeamQuery *pQuery);
int TeamDbGetId(DbCursor *pObject);
int TeamDbSeekTmur(DbCursor *pObject, int id, int *pResult);
int TeamDbGetColor1(DbCursor *pObject);
int TeamDbGetColor2(DbCursor *pObject);
int TeamDbGetColor3(DbCursor *pObject);
int TeamDbGetTrof(DbCursor *pObject);
int TeamDbGetTrde(DbCursor *pObject);
int TeamDbGetTrov(DbCursor *pObject);
void UserStatsOpen(DbCursor *pObject, int index);
void UserStatsClose(DbCursor *pObject);
int UserStatsGet(DbCursor *pObject, unsigned int index);
unsigned int UserInfoGetPoints(int a);
int UserInfoGetTotalPoints(int a);
void UnlockStatusOpen(DbCursor *pObject, int index);
void UnlockStatusClose(DbCursor *pObject);
int UnlockStatusGet(DbCursor *pObject, int index);
void UnlockListOpen(DbCursor *pObject, int a, unsigned char b);
void UnlockListClose(DbCursor *pObject);
void UnlockListReadItem(DbCursor *pObject, UnlockItem_t *pRecord);
void fn_800A2F3C(int a);
int fn_800A3444(void);
int fn_801485D4(void);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
int GameModeTypeIsSpecial(void);
void PositionAbbrevFormat(int a, char *pText);
int fn_80178308(void);
int fn_80178320(void);
int MsgGameGetSetupState(void);
void MsgGameIgnoreValue(int a);
void MsgGameSetSetupState(int a);
void EditMenuBegin(int mode, int value);
void EditMenuEnd(void);
int EditMenuIsOpen(void);
void EditMenuCancelRequest(void);
int UserRecGetCount(void);
int UserRecGetName(int index, char *pText);
signed char UserProfileFindIndex(int a);
int UserProfileSortByRecent(signed char *pIndices, int length);
void UserProfileSelect(signed char a, unsigned char b);
int UserProfileGetSelected(unsigned char index);
void UserProfileDeselect(int a);
void UserProfileSetPadName(unsigned char index, char *pText);
int UserProfileGetPadName(unsigned char index, char *pText, int length);
unsigned char GameTextGetBootFinished(void);
void GameTextSetPadPlayer(int index, int value);
int GameTextGetPadPlayer(int a);
int GameTextFindPlayerPad(int index);
void GameTextSetSetupActive(unsigned char a);
void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor);
int StoryTeamExists(int a);
void StoryTeamLoadUserTeams(int a, int b);
void fn_8018C48C(int tag);
int CreateTeamExists(int a);
void CreateTeamLoadUserTeams(void);
int GauntletGetCurrentTeam(int a);
int GauntletSetCurrentTeam(int a, int b);
int GauntletGetTeamsLeft(int a);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int ConGetChannelInfo(int a, int b);
int PerPollSingleDevice(int a);
unsigned int PerGetNumDevices(void);
int PerGetDeviceStatus(int a);
void PerCheckConnectAll(void);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
int UIGLibraryLoadItem(void *pObject, int a, int b);
void UIGLibraryUnLoadItem(void *pObject, int a, int b);
void *UIGLibraryGetGlobal(int index);
void DbOcmtInsert(int a, int b);
void DbOcmtClear(void);
void DbOptionsSetTpom(int tag, int a);
int DbNiomIsModeActive(void);
int DbNiomEndMode(void);
void fn_8022A490(int a);
int fn_8022A508(int a, int b, int c, int d, int e);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void fn_8022DC7C(int a);
void fn_8022DCB0(int a);
void fn_8022DCE4(int a);
void fn_8022DD18(int a);
int DbUserGetId(int index);
int DbUserFindIndex(int a);
int DbUserGetCurrent(void);

extern char lbl_802EBE24[];
extern void *gUISMainInfo;

int MsgMainMenuHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
void MsgMainMenuGoTo(int mode);
void MsgPlayerSelectSortProfiles(void);
int MsgPlayerSelectScanPads(int force);
void MsgPlayerSelectUpdateOwners(void);
int MsgPlayerSelectHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
int MsgRecordsHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
void MsgTeamSelectRandomize(DbCursor *pObject, int side);
int MsgTeamSelectIsLocked(int side, int id);
int MsgTeamSelectGetCount(int side);
int MsgTeamSelectDispatch(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
int MsgTeamSelectInit(int *pCount1, int *pCount0, int *pMode, int *pFlag);
void MsgTeamSelectSetTeam(int team, int id);
void MsgTeamSelectExit(void);
void MsgTeamSelectRequestAutoPick(int team);
void MsgTeamSelectApplyPicks(int team, int *pList);
void MsgTeamSelectGetRowName(int team, int index, char *pBuffer, int size);
int MsgTeamSelectPickPlayer(int team, int *pNext, int id);
void MsgTeamSelectUnpickPlayer(int team, int *pIndex, int id);
void MsgTeamSelectUndoPick(int team, int *pIndex);
void MsgTeamSelectSaveDepth(int team);
void MsgTeamSelectSetEditMode(unsigned char value);
void MsgTeamSelectGetSlotPlayer(int team, int slot, int *pId);
int MsgStadiumPickRandom(int *pIndex, int any);
int MsgStadiumHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
void MsgStadiumStartGame(int id);
int MsgStadiumGetEnvId(unsigned int index);
int MsgStartScreenHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
int MsgUserStatsHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
int MsgCreditsHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
int MsgTeamSourcesHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);
int MsgUnlocksHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult);

extern const char *_MsgPlayerSelect_apChoiceText[];
extern int _MsgRecords_aiColumns[][5];
extern int _MsgStadium_aiEnvId[];
extern unsigned char _MsgStadium_abLocked[];
extern const char *_MsgUnlocks_apCategoryText[];

unsigned char _MsgMainMenu_bEditOpen = 0;
unsigned char _MsgMainMenu_bEntered = 0;
int _MsgMainMenu_iActivePad = 0;
unsigned char _MsgMainMenu_bSetPlayType = 0;
int _MsgMainMenu_iPlayType = 0;
int _MsgMainMenu_iBusy = 0;
int _MsgMainMenu_iResult = -1;
unsigned char _MsgPlayerSelect_bTwoSides = 1;
unsigned char _MsgPlayerSelect_uSideLimit = 4;
unsigned char _MsgPlayerSelect_uOption = 1;
unsigned char _MsgPlayerSelect_auProfile[4] = { 3, 3, 3, 3 };
unsigned char _MsgRecords_bOpen = 0;
unsigned char _MsgTeamSelect_bEditMode = 0;
int _MsgTeamSelect_iTeamSize = 7;
unsigned char _MsgTeamSelect_auOpenCount[2] = { 0, 0 };
int _MsgTeamSelect_aiTeam[2] = { -1, -1 };
int _MsgTeamSelect_aiSavedTeam[2] = { -1, -1 };
int _MsgTeamSelect_aiChallengeTeam[2] = { -1, -1 };
int *_MsgTeamSelect_apTeamIds[2] = { 0, 0 };
unsigned char _MsgTeamSelect_bPicksApplied = 0;
int _MsgTeamSelect_aiBrowseRow[2] = { -1, -1 };
int _MsgTeamSelect_iMode = -1;
unsigned char _MsgTeamSelect_abResetPicks[2] = { 1, 1 };
unsigned char _MsgTeamSelect_abNewTeam[2] = { 1, 1 };
int _MsgTeamSelect_aiProfileDb[2] = { -1, -1 };
unsigned char _MsgTeamSelect_abAutoFill[2] = { 1, 1 };
unsigned char _MsgTeamSelect_abAutoPick[2] = { 1, 1 };
int _MsgTeamSelect_aiDepthStyle[2] = { 0, 0 };
unsigned char _MsgTeamSelect_bMainFE = 1;
unsigned char _MsgTeamSelect_abProfileChanged[2] = { 0, 0 };
unsigned char _MsgTeamSelect_bDone = 1;
int _MsgTeamEditSelect_aiTeam[2] = { -1, -1 };
MsgStadiumEntry_t *_MsgStadium_pEntries = 0;
int _MsgStadium_iCurrent = -1;
unsigned char _MsgStadium_bFirst = 1;
unsigned char _MsgStadium_bCheckLocks = 1;
unsigned char _MsgStartScreen_bShown = 0;
signed char _MsgUserStats_iProfile = -1;
MsgUserStats_t *_MsgUserStats_pStats = 0;
signed char _MsgCredits_iSpaces = -1;
unsigned char _MsgCredits_iCachedType = 2;
int _MsgTeamSources_iMode = 0;
int _MsgTeamSources_iSavedOption = 0;
unsigned char _MsgTeamSources_bSource1 = 1;
unsigned char _MsgTeamSources_bSource2 = 0;
unsigned char _MsgTeamSources_bSource4 = 0;
unsigned char _MsgTeamSources_bSource8 = 0;
signed char _MsgUnlocks_iProfile = -1;
signed char _MsgUnlocks_iCategory = 0;
signed char _MsgUnlocks_iProfileCount = 0;
DbCursor *_MsgUnlocks_pList = 0;
DbCursor *_MsgUnlocks_pStatus = 0;

unsigned char _MsgPlayerSelect_abPadPresent[8];
unsigned char _MsgPlayerSelect_auPadSide[4];
unsigned char _MsgPlayerSelect_auPadRole[4];
MsgPlayerSelectProfiles_t _MsgPlayerSelect_Profiles;
int **_MsgTeamSelect_ppWindow;
int _MsgTeamSelect_aiRosterCount[2];

DbCursor _MsgTeamSelect_aTeamCursor[2];
Object_8008044C _MsgTeamSelect_aPlayerDb[2];
MsgTeamSelectRoster_t _MsgTeamSelect_aRoster[2];
MsgTeamSelectScroll_t _MsgTeamSelect_aScroll[2];
MsgTeamSelectDepth_t _MsgTeamSelect_aDepthSpots[2];

int MsgFrontEndDispatch(int module, unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (module) {
    case 1:
        return MsgMainMenuHandleMessage(id, pArgs, count, pResult);
    case 3:
        return MsgStartScreenHandleMessage(id, pArgs, count, pResult);
    case 17:
        return MsgPlayerSelectHandleMessage(id, pArgs, count, pResult);
    case 7:
        return MsgTeamSelectDispatch(id, pArgs, count, pResult);
    case 8:
        return MsgStadiumHandleMessage(id, pArgs, count, pResult);
    case 9:
        return MsgTeamPickHandleMessage(id, pArgs, count, pResult);
    case 12:
        return MsgRecordsHandleMessage(id, pArgs, count, pResult);
    case 11:
        return MsgUserStatsHandleMessage(id, pArgs, count, pResult);
    case 4:
        return MsgCreditsHandleMessage(id, pArgs, count, pResult);
    case 15:
        return MsgTeamSourcesHandleMessage(id, pArgs, count, pResult);
    case 16:
        return MsgUnlocksHandleMessage(id, pArgs, count, pResult);
    }
    return 0;
}

void MsgMainMenuEnter(void)
{
    CheatFlagsClear();
    if (!_MsgMainMenu_bEntered) {
        _MsgMainMenu_bEntered = 1;
        if (EditMenuIsOpen()) {
            EditMenuEnd();
        }
        EditMenuCancelRequest();
        if (!FELoopWasVisited()) {
            FELoopSetVisited(1);
        }
        fn_8018C48C(0x54415453);
        fn_8018C48C(0x454D4147);
        FELoopResetIdle();
        if (GameInfoIsInitialized()) {
            GameInfoShutdown();
        }
        if (DbNiomIsModeActive()) {
            DbNiomEndMode();
        }
        if (GameTextGetBootFinished() && !UserRecGetCount() && !FELoopIsIdleTimedOut()) {
            MsgMainMenuGoTo(11);
        }
    }
}

void MsgMainMenuLeave(int mode)
{
    int save = 1;
    Request_802329F0 request;

    if (_MsgMainMenu_bEntered) {
        MsgTeamSelectSetEditMode(0);
        switch (mode) {
        case 0:
            if (_MsgMainMenu_bSetPlayType) {
                request.mMode = 1;
            } else {
                request.mMode = mode;
            }
            break;
        case 8:
            UserProfileSelect(UserProfileFindIndex(DbUserGetCurrent()), 1);
            UserProfileSelect(-1, 0);
            /* fall through */
        case 2:
        case 6:
        case 7:
        case 9:
        case 10:
        case 11:
        case 12:
            request.mMode = mode;
            _MsgMainMenu_bSetPlayType = 0;
            break;
        case 3:
        case 4:
        case 5:
        case 13:
            save = 0;
            break;
        default:
            save = 0;
            break;
        }
        if (save) {
            request.mSize = 0x96000;
            request.mpName = lbl_802EBE24;
            request.mCount = 1;
            if (DbNiomIsModeActive()) {
                SndgMusicPumpFrame(0);
                DbNiomEndMode();
            }
            switch (mode) {
            case 0:
            case 2:
            case 6:
                DbManagerInit(&request);
                GameInfoInit();
                if (_MsgMainMenu_bSetPlayType) {
                    TDbCompilePerformOp(0, "update 'FNIG' set 'YTPG' = \x82\n", _MsgMainMenu_iPlayType);
                }
                DbOptionsSetTpom(0x544E464F, 2);
                fn_8022A490(2);
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                SndgMusicPumpFrame(1);
                SndgMusicPumpFrame(0);
                DbManagerInit(&request);
                SndgMusicPumpFrame(1);
                SndgMusicPumpFrame(0);
                GameInfoInit();
                SndgMusicPumpFrame(0);
                DbOptionsSetTpom(0x544E464F, 2);
                SndgMusicPumpFrame(0);
                fn_8022A490(2);
                break;
            }
        } else if (_MsgMainMenu_bEditOpen) {
            MsgTeamSelectSetEditMode(1);
        }
        _MsgMainMenu_bEntered = 0;
    }
    _MsgMainMenu_iResult = -1;
}

int MsgMainMenuGetActivePad(void)
{
    return _MsgMainMenu_iActivePad;
}

void MsgMainMenuSetActivePad(int a)
{
    _MsgMainMenu_iActivePad = a;
}

int MsgMainMenuAssignPads(void)
{
    int current = MsgMainMenuGetActivePad();
    int count = 0;
    int first = 8;
    int found = 0;
    int assigned = GameTextGetPadPlayer(current);
    int limit;
    int i;

    PerCheckConnectAll();
    if (PerGetNumDevices() < 8) {
        limit = PerGetNumDevices();
    } else {
        limit = 8;
    }
    for (i = 0; i < limit; i++) {
        if (PerGetDeviceStatus(i)) {
            PerPollSingleDevice(i);
        }
    }
    for (i = 0; i <= 7; i++) {
        if (PerGetDeviceStatus(ConGetChannelInfo(i, 0)) == 2) {
            GameTextSetPadPlayer(i, count);
            count++;
            found = 1;
            if (first == 8) {
                first = i;
            }
        } else {
            GameTextSetPadPlayer(i, -1);
        }
    }
    int connected = PerGetDeviceStatus(ConGetChannelInfo(current, 0)) == 2;
    if (!found) {
        int value = 0;
        if (assigned != -1 && assigned <= 3) {
            value = assigned;
        }
        GameTextSetPadPlayer(current, value);
    } else if (assigned == -1 && connected) {
        found = 0;
    } else if (assigned == -1 || assigned > 3) {
        found = 0;
        MsgMainMenuSetActivePad(first);
    } else if (!connected) {
        GameTextSetPadPlayer(current, assigned);
        found = 0;
    }
    return found;
}

int MsgMainMenuHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        if (_MsgMainMenu_bEditOpen) {
            EditMenuEnd();
            FELoopResetIdle();
            _MsgMainMenu_bEditOpen = 0;
        }
        MsgMainMenuEnter();
        break;
    case 0x80000002:
        MsgMainMenuLeave(pArgs[0].i);
        break;
    case 0x80000003:
        MsgMainMenuSetActivePad(pArgs[0].i);
        break;
    case 0x80000004:
        _MsgMainMenu_bSetPlayType = 1;
        _MsgMainMenu_iPlayType = 0;
        break;
    case 0x80000006:
        _MsgMainMenu_bSetPlayType = 1;
        _MsgMainMenu_iPlayType = 1;
        break;
    case 0x80000005:
        _MsgMainMenu_bSetPlayType = 0;
        break;
    case 0x80000007:
        switch (pArgs[0].i) {
        case 900:
            _MsgMainMenu_bEditOpen = 1;
            EditMenuBegin(2, 0x3FF);
            break;
        case 750:
            _MsgMainMenu_bEditOpen = 1;
            break;
        case 751:
            _MsgMainMenu_bEditOpen = 1;
            EditMenuBegin(4, 0x3FF);
            break;
        case 752:
            _MsgMainMenu_bEditOpen = 1;
            EditMenuBegin(1, 0x3FF);
            break;
        }
        *pResult = 1;
        break;
    case 0x80000008:
        break;
    case 0x8000000A:
        MsgGameIgnoreValue(pArgs[0].i);
        break;
    case 0x8000000B:
        _MsgMainMenu_iBusy = pArgs[0].i;
        break;
    case 0x8000000C:
        SndgMusicPumpFrame(1);
        SndgMusicPumpFrame(0);
        break;
    case 0x8000000D:
        *pResult = 0;
        break;
    case 0x80000000:
        strncpy(pArgs[0].pParams->mpText, "", pArgs[0].pParams->mLength);
        break;
    case 0x8000000F:
        FELoopCheckDemoLaunch(0);
        break;
    case 0x80000010:
        *pResult = _MsgMainMenu_iResult;
        _MsgMainMenu_iResult = -1;
        break;
    case 0x80000011:
        *pResult = 1;
        switch (pArgs[0].i) {
        case 751:
            *pResult = StoryTeamExists(DbUserFindIndex(DbUserGetCurrent()));
            break;
        case 752:
            *pResult = CreateTeamExists(DbUserFindIndex(DbUserGetCurrent()));
            break;
        }
        break;
    case 0x80000009:
        *pResult = CreateTeamExists(DbUserFindIndex(DbUserGetCurrent()));
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgMainMenuGoTo(int mode)
{
    unsigned char saved = FELoopWasVisited();
    MsgMainMenuEnter();
    MsgMainMenuLeave(mode);
    FELoopSetVisited(saved);
}

int MsgMainMenuIsShown(void)
{
    unsigned short a = 0;
    unsigned short b = 0;
    int result;

    fn_80219650(gUISMainInfo, &a, &b);
    result = 0;
    if (a == 0 && b == 1 && _MsgMainMenu_bEntered) {
        result = _MsgMainMenu_iBusy == 0;
    }
    return result;
}

void MsgMainMenuSetResult(int value)
{
    _MsgMainMenu_iResult = value;
}

void MsgPlayerSelectInit(void)
{
    GameTextSetSetupActive(0);
    switch (fn_801486A0()) {
    case 0:
    case 1:
        _MsgPlayerSelect_bTwoSides = 0;
        break;
    default:
        unsigned int type = GameModeTypeGet();
        if (type == 6 || type == 8) {
            _MsgPlayerSelect_bTwoSides = 0;
        } else {
            _MsgPlayerSelect_bTwoSides = 1;
        }
        break;
    }
    switch (fn_801486A0()) {
    case 2:
    case 3:
        _MsgPlayerSelect_uSideLimit = 2;
        break;
    default:
        _MsgPlayerSelect_uSideLimit = 4;
        break;
    }
    MsgPlayerSelectSortProfiles();
    int state = MsgGameGetSetupState();
    if (state == 1) {
        MsgPlayerSelectScanPads(1);
        _MsgPlayerSelect_uOption = state;
    }
    if (ChallengeIsActive() || ChallengeIsPairingGame()) {
        _MsgPlayerSelect_uOption = GameInfoGet(2);
    }
}

void MsgPlayerSelectSortProfiles(void)
{
    MsgPlayerSelectProfiles_t previous = _MsgPlayerSelect_Profiles;

    UserProfileSortByRecent(_MsgPlayerSelect_Profiles.mIndex, 2);
    for (unsigned char i = 0; i <= 3; i++) {
        if (_MsgPlayerSelect_auProfile[i] <= 1) {
            unsigned char j;
            for (j = 0; j <= 1; j++) {
                if (previous.mIndex[_MsgPlayerSelect_auProfile[i]] == _MsgPlayerSelect_Profiles.mIndex[j]) {
                    _MsgPlayerSelect_auProfile[i] = j;
                    break;
                }
            }
            if (j == 2 || _MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]] == -1) {
                _MsgPlayerSelect_auProfile[i] = 3;
            }
        }
    }
}

int MsgPlayerSelectScanPads(int force)
{
    unsigned char changed = 0;
    int i;
    int j;
    unsigned char k;
    int start;
    unsigned int count;
    unsigned char used[2];

    PerCheckConnectAll();
    count = 0;
    for (i = 0; i <= 7; i++) {
        unsigned char present = PerGetDeviceStatus(ConGetChannelInfo(i, 0)) == 2;
        if (present && count <= 3) {
            count++;
        } else {
            present = 0;
        }
        if (!changed) {
            changed = _MsgPlayerSelect_abPadPresent[i] != present;
        }
        _MsgPlayerSelect_abPadPresent[i] = present;
    }
    for (j = 0; j <= 9; j++) {
        GameTextSetPadPlayer(j, -1);
    }
    j = 0;
    for (i = 0; i <= 7; i++) {
        if (_MsgPlayerSelect_abPadPresent[i] && j <= 3) {
            GameTextSetPadPlayer(i, j);
            j++;
        }
    }
    if (changed || force) {
        for (j = 0; j < 4; j++) {
            if (!_MsgPlayerSelect_abPadPresent[j]) {
                _MsgPlayerSelect_auProfile[j] = 3;
            }
        }
        for (k = 0; k <= 1; k++) {
            used[k] = 0;
        }
        for (j = 0; j < 4; j++) {
            if (_MsgPlayerSelect_auProfile[j] <= 1) {
                used[_MsgPlayerSelect_auProfile[j]] = 1;
            }
        }
        k = 0;
        start = GameTextGetPadPlayer(MsgMainMenuGetActivePad());
        if (start == -1) {
            start = 0;
        }
        for (i = 0; i <= 3; i++) {
            j = (i + start) % 4;
            int pad = GameTextFindPlayerPad(j);
            if (pad != -1 && _MsgPlayerSelect_abPadPresent[pad] && _MsgPlayerSelect_auProfile[j] > 2) {
                do {
                    if (k < UserRecGetCount() && _MsgPlayerSelect_Profiles.mIndex[k] != -1) {
                        _MsgPlayerSelect_auProfile[j] = k++;
                    } else {
                        _MsgPlayerSelect_auProfile[j] = 3;
                    }
                } while (used[_MsgPlayerSelect_auProfile[j]] && _MsgPlayerSelect_auProfile[j] != 3);
            }
        }
        for (j = 0; j <= 3; j++) {
            _MsgPlayerSelect_auPadSide[j] = 1;
            _MsgPlayerSelect_auPadRole[j] = 0;
            UserProfileSetPadName(j, 0);
        }
        if (force) {
            for (j = 0; j < 4; j++) {
                if (_MsgPlayerSelect_auProfile[j] == 2) {
                    _MsgPlayerSelect_auProfile[j] = 3;
                }
            }
            j = GameTextGetPadPlayer(MsgMainMenuGetActivePad());
            if (j != -1) {
                if (_MsgPlayerSelect_bTwoSides) {
                    _MsgPlayerSelect_auPadSide[j] = 0;
                } else {
                    _MsgPlayerSelect_auPadSide[j] = 2;
                }
            }
            MsgPlayerSelectUpdateOwners();
        }
    }
    return changed || force;
}

void MsgPlayerSelectGetLayout(int *pA, int *pB)
{
    if (_MsgPlayerSelect_bTwoSides) {
        *pA = 1;
    } else {
        *pA = 2;
    }
    switch (GameModeTypeGet()) {
    case 2:
        *pB = 1;
        break;
    case 9:
        if (fn_801486A0() == 2) {
            *pB = 1;
        } else {
            *pB = 0;
        }
        break;
    default:
        *pB = 0;
        break;
    }
}

int MsgPlayerSelectCanMove(int index, int dir)
{
    int result = 0;
    unsigned char count = 0;

    for (unsigned char i = 0; i <= 3; i++) {
        switch (dir) {
        case 1:
            if (_MsgPlayerSelect_auPadSide[i] == 2) {
                count++;
            }
            break;
        case 3:
            if (_MsgPlayerSelect_auPadSide[i] == 0) {
                count++;
            }
            break;
        }
    }
    int isLeft = _MsgPlayerSelect_auPadSide[index] == 0;
    int isRight = _MsgPlayerSelect_auPadSide[index] == 2;
    switch (dir) {
    case 3:
        if (!isLeft && (isRight || (_MsgPlayerSelect_bTwoSides && count < _MsgPlayerSelect_uSideLimit))) {
            result = 1;
        }
        break;
    case 1:
        if (!isRight) {
            if (!isLeft) {
                if (count < _MsgPlayerSelect_uSideLimit) {
                    result = 1;
                }
            } else {
                result = 1;
            }
        }
        break;
    }
    return result;
}

int MsgPlayerSelectMove(int index, int dir)
{
    int moved = MsgPlayerSelectCanMove(index, dir);

    if (moved) {
        switch (dir) {
        case 3:
            switch (_MsgPlayerSelect_auPadSide[index]) {
            case 1:
                _MsgPlayerSelect_auPadSide[index] = 0;
                break;
            case 2:
                _MsgPlayerSelect_auPadSide[index] = 1;
                break;
            }
            break;
        case 1:
            switch (_MsgPlayerSelect_auPadSide[index]) {
            case 1:
                _MsgPlayerSelect_auPadSide[index] = 2;
                break;
            case 0:
                _MsgPlayerSelect_auPadSide[index] = 1;
                break;
            }
            break;
        }
    }
    MsgPlayerSelectUpdateOwners();
    return moved;
}

int MsgPlayerSelectGetIcon(int index)
{
    int result = 3;

    switch (_MsgPlayerSelect_auProfile[index]) {
    case 3:
        break;
    case 4:
        if (_MsgPlayerSelect_auPadRole[index] == 1) {
            result = 2;
        }
        break;
    case 5:
        switch (_MsgPlayerSelect_auPadRole[index]) {
        case 1:
            result = 0;
            break;
        case 2:
            result = 1;
            break;
        }
        break;
    }
    return result;
}

void MsgPlayerSelectApply(void)
{
    char text[16];
    int i;

    DbOcmtClear();
    for (i = 0; i <= 3; i++) {
        int pad = GameTextFindPlayerPad(i);
        if (pad != -1) {
            if (_MsgPlayerSelect_auPadSide[i] == 2) {
                if (_MsgPlayerSelect_bTwoSides) {
                    DbOcmtInsert(0, pad);
                } else {
                    DbOcmtInsert(1, pad);
                }
            } else if (_MsgPlayerSelect_auPadSide[i] == 0) {
                DbOcmtInsert(1, pad);
            }
        }
    }
    UserProfileDeselect(0);
    if (GameModeTypeGet() != 6 && GameModeTypeGet() != 8 && GameModeTypeGet() != 7 && GameModeTypeGet() != 11) {
        UserProfileDeselect(1);
        if (fn_801486A0() != 0 && fn_801486A0() != 1) {
            for (i = 0; i <= 3; i++) {
                if (_MsgPlayerSelect_auPadRole[i] == 1 && _MsgPlayerSelect_auProfile[i] <= 1) {
                    if (_MsgPlayerSelect_auPadSide[i] == 0) {
                        UserProfileSelect(_MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]], 1);
                    } else {
                        UserProfileSelect(_MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]], 0);
                    }
                    CheatFlagsAddUser(_MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]]);
                }
            }
        } else {
            int team = 0;
            for (i = 0; i <= 3; i++) {
                switch (_MsgPlayerSelect_auPadRole[i]) {
                case 1:
                    if (_MsgPlayerSelect_auProfile[i] <= 1) {
                        UserRecGetName(_MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]], text);
                        UserProfileSetPadName(i, text);
                    } else {
                        UserProfileSetPadName(i, 0);
                    }
                    if (_MsgPlayerSelect_auProfile[i] != 3 && team <= 1) {
                        UserProfileSelect(_MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]], team);
                        team++;
                    }
                    break;
                case 2:
                    if (_MsgPlayerSelect_auProfile[i] != 2) {
                        UserProfileSetPadName(i, 0);
                    }
                    break;
                default:
                    UserProfileSetPadName(i, 0);
                    break;
                }
            }
        }
    }
    GameInfoSet(2, _MsgPlayerSelect_uOption);
    SndgSfxSetVolume(0x8F, 0x32, 0);
    if (MsgGameGetSetupState() == 1) {
        GameTextSetSetupActive(1);
    }
}

void MsgPlayerSelectUpdateOwners(void)
{
    unsigned char i;
    unsigned char j;
    unsigned char n;

    switch (fn_801486A0()) {
    case 0:
    case 1:
        for (i = 0; i <= 3; i++) {
            if (_MsgPlayerSelect_auPadSide[i] == 2) {
                if (_MsgPlayerSelect_auPadRole[i] == 0) {
                    n = 0;
                    for (j = 0; j <= 3; j++) {
                        if (_MsgPlayerSelect_auPadRole[j] == 1) {
                            n++;
                        }
                    }
                    if (n <= 1) {
                        _MsgPlayerSelect_auPadRole[i] = 1;
                        if (_MsgPlayerSelect_auProfile[i] == 2) {
                            _MsgPlayerSelect_auProfile[i] = 3;
                        }
                    } else {
                        _MsgPlayerSelect_auPadRole[i] = 2;
                        if (_MsgPlayerSelect_auProfile[i] <= 1 || _MsgPlayerSelect_auProfile[i] == 4) {
                            _MsgPlayerSelect_auProfile[i] = 3;
                        }
                    }
                }
            } else {
                _MsgPlayerSelect_auPadRole[i] = 0;
            }
        }
        break;
    default:
        for (i = 0; i <= 3; i++) {
            _MsgPlayerSelect_auPadRole[i] = 0;
            if (_MsgPlayerSelect_auPadSide[i] != 1) {
                int unique = 1;
                for (j = 0; j < i; j++) {
                    if (_MsgPlayerSelect_auPadSide[j] == _MsgPlayerSelect_auPadSide[i]) {
                        unique = 0;
                        break;
                    }
                }
                if (unique) {
                    _MsgPlayerSelect_auPadRole[i] = 1;
                }
            }
        }
        break;
    }
}

int MsgPlayerSelectGetSide(int index)
{
    int result = -1;

    switch (_MsgPlayerSelect_auPadSide[index]) {
    case 0:
        result = 1;
        break;
    case 1:
        break;
    case 2:
        if (_MsgPlayerSelect_bTwoSides) {
            result = 0;
            break;
        }
        switch (fn_801486A0()) {
        case 0:
        case 1:
            if (_MsgPlayerSelect_auPadRole[index] == 1) {
                for (unsigned char j = 0; j <= 3; j++) {
                    if (j == index) {
                        result = 1;
                        break;
                    }
                    if (_MsgPlayerSelect_auPadRole[j] == 1) {
                        result = 0;
                        break;
                    }
                }
            }
            break;
        default:
            result = 1;
            break;
        }
        break;
    }
    return result;
}

void MsgPlayerSelectSetProfile(int index, int pad)
{
    MsgPlayerSelectSortProfiles();
    if (pad >= 0 && pad < UserRecGetCount()) {
        switch (_MsgPlayerSelect_auPadRole[index]) {
        case 1:
            for (unsigned char j = 0; j <= 1; j++) {
                if (_MsgPlayerSelect_Profiles.mIndex[j] == pad) {
                    _MsgPlayerSelect_auProfile[index] = j;
                    break;
                }
            }
            break;
        case 2:
            _MsgPlayerSelect_auProfile[index] = 2;
            break;
        }
    }
}

const char *_MsgPlayerSelect_apChoiceText[] = { "None", "Load", "Create" };

void MsgPlayerSelectCycleProfile(int index, int dir, MenuArg_t arg)
{
    MenuText_t *pParams = arg.pParams;

    MsgPlayerSelectSortProfiles();
    switch (_MsgPlayerSelect_auPadRole[index]) {
    case 1: {
        switch (dir) {
        case 2:
            if (_MsgPlayerSelect_auProfile[index] == 5) {
                _MsgPlayerSelect_auProfile[index] = 0;
            } else {
                _MsgPlayerSelect_auProfile[index]++;
            }
            while (_MsgPlayerSelect_auProfile[index] <= 2 && _MsgPlayerSelect_auProfile[index] >= UserRecGetCount()) {
                _MsgPlayerSelect_auProfile[index]++;
            }
            break;
        case 0:
            if (_MsgPlayerSelect_auProfile[index] == 0) {
                _MsgPlayerSelect_auProfile[index] = 5;
            } else {
                _MsgPlayerSelect_auProfile[index]--;
            }
            while (_MsgPlayerSelect_auProfile[index] <= 2 && _MsgPlayerSelect_auProfile[index] >= UserRecGetCount()) {
                if (_MsgPlayerSelect_auProfile[index] == 0) {
                    _MsgPlayerSelect_auProfile[index] = 5;
                } else {
                    _MsgPlayerSelect_auProfile[index]--;
                }
            }
            break;
        case -1:
            break;
        default:
            _MsgPlayerSelect_auProfile[index] = 3;
            dir = -1;
            break;
        }
        int again = 1;
        while (dir != -1 && _MsgPlayerSelect_auProfile[index] <= 1 && again) {
            int j;
            for (j = 0; j <= 3; j++) {
                if (j != index && _MsgPlayerSelect_auProfile[j] == _MsgPlayerSelect_auProfile[index]) {
                    if (_MsgPlayerSelect_auPadRole[j] == 1) {
                        if (dir == 0) {
                            if (_MsgPlayerSelect_auProfile[index] == 0) {
                                _MsgPlayerSelect_auProfile[index] = 5;
                            } else {
                                _MsgPlayerSelect_auProfile[index]--;
                            }
                        } else {
                            _MsgPlayerSelect_auProfile[index]++;
                            if (_MsgPlayerSelect_auProfile[index] >= UserRecGetCount()) {
                                _MsgPlayerSelect_auProfile[index] = 3;
                            }
                        }
                        break;
                    }
                    if (_MsgPlayerSelect_auPadRole[j] == 0) {
                        _MsgPlayerSelect_auProfile[j] = 3;
                    }
                }
            }
            if (j == 4) {
                again = 0;
            }
        }
        if (_MsgPlayerSelect_auProfile[index] <= 1) {
            UserRecGetName(_MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[index]], pParams->mpText);
        } else {
            strncpy(pParams->mpText, _MsgPlayerSelect_apChoiceText[_MsgPlayerSelect_auProfile[index] - 3], pParams->mLength);
        }
        break;
    }
    case 2:
        switch (dir) {
        case 0:
            switch (_MsgPlayerSelect_auProfile[index]) {
            case 3:
                if (UserProfileGetPadName(index, 0, 0)) {
                    _MsgPlayerSelect_auProfile[index] = 2;
                } else {
                    _MsgPlayerSelect_auProfile[index] = 5;
                }
                break;
            case 2:
                _MsgPlayerSelect_auProfile[index] = 5;
                break;
            case 5:
                _MsgPlayerSelect_auProfile[index] = 3;
                break;
            default:
                _MsgPlayerSelect_auProfile[index] = 3;
                break;
            }
            break;
        case 2:
            switch (_MsgPlayerSelect_auProfile[index]) {
            case 3:
                _MsgPlayerSelect_auProfile[index] = 5;
                break;
            case 5:
                if (UserProfileGetPadName(index, 0, 0)) {
                    _MsgPlayerSelect_auProfile[index] = 2;
                } else {
                    _MsgPlayerSelect_auProfile[index] = 3;
                }
                break;
            case 2:
                _MsgPlayerSelect_auProfile[index] = 3;
                break;
            default:
                _MsgPlayerSelect_auProfile[index] = 3;
                break;
            }
            break;
        case -1:
            break;
        default:
            _MsgPlayerSelect_auProfile[index] = 3;
            break;
        }
        if (_MsgPlayerSelect_auProfile[index] == 2) {
            UserProfileGetPadName(index, pParams->mpText, pParams->mLength);
        } else {
            strncpy(pParams->mpText, _MsgPlayerSelect_apChoiceText[_MsgPlayerSelect_auProfile[index] - 3], pParams->mLength);
        }
        break;
    default:
        pParams->mpText[0] = 0;
        break;
    }
}

int MsgPlayerSelectGetPads(int *pA, int *pB, int *pC, int *pD)
{
    int result = MsgPlayerSelectScanPads(0);
    int index;

    index = GameTextFindPlayerPad(0);
    *pA = index != -1 ? _MsgPlayerSelect_abPadPresent[index] : 0;
    index = GameTextFindPlayerPad(1);
    *pB = index != -1 ? _MsgPlayerSelect_abPadPresent[index] : 0;
    index = GameTextFindPlayerPad(2);
    *pC = index != -1 ? _MsgPlayerSelect_abPadPresent[index] : 0;
    index = GameTextFindPlayerPad(3);
    *pD = index != -1 ? _MsgPlayerSelect_abPadPresent[index] : 0;
    return result;
}

void MsgPlayerSelectGetMoves(int a, int *pB, int *pC)
{
    *pB = MsgPlayerSelectCanMove(a, 3);
    *pC = MsgPlayerSelectCanMove(a, 1);
}

int MsgPlayerSelectHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgPlayerSelectInit();
        break;
    case 0x80000003:
        MsgPlayerSelectGetLayout(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000002:
        MsgPlayerSelectApply();
        break;
    case 0x80000004:
        *pResult = MsgPlayerSelectMove(pArgs[0].i, pArgs[1].i);
        break;
    case 0x8000000C:
        *pResult = MsgPlayerSelectGetSide(pArgs[0].i);
        break;
    case 0x8000000D:
        *pResult = MsgPlayerSelectGetIcon(pArgs[0].i);
        break;
    case 0x8000000A:
        UserProfileSetPadName(pArgs[0].i, pArgs[1].pParams->mpText);
        break;
    case 0x80000007:
        if (pArgs[0].i == 2) {
            _MsgPlayerSelect_uOption = 0;
        } else {
            _MsgPlayerSelect_uOption = 1;
        }
        break;
    case 0x80000010:
        if (_MsgPlayerSelect_uOption == 0) {
            *pResult = 2;
        } else {
            *pResult = 0;
        }
        break;
    case 0x8000000F:
        MsgPlayerSelectSetProfile(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000008:
        MsgPlayerSelectCycleProfile(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x80000005:
        *pArgs[0].pi = _MsgPlayerSelect_auPadSide[0];
        *pArgs[1].pi = _MsgPlayerSelect_auPadSide[1];
        *pArgs[2].pi = _MsgPlayerSelect_auPadSide[2];
        *pArgs[3].pi = _MsgPlayerSelect_auPadSide[3];
        break;
    case 0x80000009: {
        unsigned int state = GameModeTypeGet();
        if (state == 6 || state == 8) {
            *pResult = 0;
        } else if (_MsgPlayerSelect_auPadRole[pArgs[0].i]) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    }
    case 0x80000006:
        *pResult = MsgPlayerSelectGetPads(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x8000000E:
        MsgPlayerSelectGetMoves(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000011:
        GameTextSetSetupActive(pArgs[0].i);
        break;
    case 0x8000000B:
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgPlayerSelectStart(int pad0, int pad1, int keep)
{
    MsgGameSetSetupState(1);
    if (keep) {
        MsgPlayerSelectInit();
    } else {
        MsgPlayerSelectSortProfiles();
        for (int i = 0; i < 4; i++) {
            _MsgPlayerSelect_auPadSide[i] = 1;
            _MsgPlayerSelect_auPadRole[i] = 0;
            _MsgPlayerSelect_auProfile[i] = 3;
        }
        if (pad0 != -1) {
            if (GameTextGetPadPlayer(pad0) == -1 || GameTextGetPadPlayer(pad0) > 3) {
                pad0 = MsgMainMenuGetActivePad();
            }
            _MsgPlayerSelect_auPadSide[GameTextGetPadPlayer(pad0)] = 2;
            _MsgPlayerSelect_auPadRole[GameTextGetPadPlayer(pad0)] = 1;
        }
        if (pad1 != -1) {
            if (GameTextGetPadPlayer(pad1) == -1 || GameTextGetPadPlayer(pad1) > 3) {
                pad1 = MsgMainMenuGetActivePad();
            }
            _MsgPlayerSelect_auPadSide[GameTextGetPadPlayer(pad1)] = 0;
            _MsgPlayerSelect_auPadRole[GameTextGetPadPlayer(pad1)] = 1;
        }
        _MsgPlayerSelect_uOption = 1;
    }
    char name[13] = {0};
    int db = DbUserFindIndex(DbUserGetCurrent());
    if (pad0 != -1 && GameTextGetPadPlayer(pad0) != -1) {
        _MsgPlayerSelect_auPadSide[GameTextGetPadPlayer(pad0)] = 2;
        GameModeTypeIsSpecial();
        _MsgPlayerSelect_auPadRole[GameTextGetPadPlayer(pad0)] = 1;
        _MsgPlayerSelect_auProfile[GameTextGetPadPlayer(pad0)] = db;
        if (db != -1) {
            UserRecGetName(db, name);
            UserProfileSetPadName(GameTextGetPadPlayer(pad0), name);
        }
    }
    if (pad1 != -1 && GameTextGetPadPlayer(pad1) != -1) {
        if (_MsgPlayerSelect_bTwoSides) {
            _MsgPlayerSelect_auPadSide[GameTextGetPadPlayer(pad1)] = 0;
        } else {
            _MsgPlayerSelect_auPadSide[GameTextGetPadPlayer(pad1)] = 2;
        }
        _MsgPlayerSelect_auPadRole[GameTextGetPadPlayer(pad1)] = 1;
        _MsgPlayerSelect_auProfile[GameTextGetPadPlayer(pad1)] = db;
        if (db != -1) {
            UserRecGetName(db, name);
            UserProfileSetPadName(GameTextGetPadPlayer(pad1), name);
        }
    }
    MsgPlayerSelectApply();
}

void MsgPlayerSelectRemoveProfile(int removed)
{
    for (unsigned char i = 0; i <= 3; i++) {
        unsigned char selection = _MsgPlayerSelect_auProfile[i];
        if (selection > 1) {
            continue;
        }
        if (_MsgPlayerSelect_Profiles.mIndex[selection] > removed) {
            unsigned char want = _MsgPlayerSelect_Profiles.mIndex[selection] - 1;
            for (unsigned char j = 0; j <= 1; j++) {
                if (_MsgPlayerSelect_Profiles.mIndex[j] == want) {
                    _MsgPlayerSelect_auProfile[i] = j;
                    break;
                }
            }
        } else if (_MsgPlayerSelect_Profiles.mIndex[selection] == removed) {
            _MsgPlayerSelect_auProfile[i] = 3;
        }
    }
    MsgPlayerSelectSortProfiles();
}

int MsgPlayerSelectGetSideProfile(int side)
{
    int result = -1;

    for (unsigned char i = 0; i <= 3; i++) {
        if ((side == 0 && _MsgPlayerSelect_auPadSide[i] == 2) || (side == 1 && _MsgPlayerSelect_auPadSide[i] == 0)) {
            if (_MsgPlayerSelect_auPadRole[i] == 1) {
                if (_MsgPlayerSelect_auProfile[i] <= 1) {
                    result = _MsgPlayerSelect_Profiles.mIndex[_MsgPlayerSelect_auProfile[i]];
                }
                break;
            }
        }
    }
    return result;
}

int _MsgRecords_aiColumns[][5] = {
    { 1, 24, 24, 24, 24 },
    { 0, 1, 2, 24, 24 },
    { 0, 1, 3, 24, 24 },
    { 0, 1, 4, 24, 24 },
    { 0, 1, 5, 24, 24 },
    { 0, 1, 6, 24, 24 },
    { 16, 1, 5, 24, 24 },
    { 0, 1, 7, 8, 9 },
    { 0, 1, 7, 24, 24 },
    { 0, 1, 8, 24, 24 },
    { 0, 1, 10, 24, 24 },
    { 0, 1, 11, 24, 24 },
    { 0, 1, 12, 24, 24 },
    { 0, 1, 13, 24, 24 },
    { 0, 1, 14, 24, 24 },
    { 0, 1, 15, 24, 24 },
    { 0, 1, 17, 24, 24 },
    { 0, 1, 18, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 23, 24, 24 },
    { 0, 1, 19, 20, 21 },
};

void MsgRecordsGetText(int type, int value, int column, char *pOut, int size, int *pFound)
{
    char text[32] = " ";

    if (type != 6) {
        if (value > 9) {
            *pOut = 0;
            return;
        }
    } else {
        value = MsgStadiumGetEnvId(value);
    }
    if (RecordsGetText(type, value, _MsgRecords_aiColumns[type][column], text, 32)) {
        *pFound = 1;
    } else {
        *pFound = 0;
    }
    memcpy(pOut, text, size);
}

int MsgRecordsHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        RecordsBegin();
        RecordsSetSharedRanks(1);
        _MsgRecords_bOpen = 1;
        break;
    case 0x80000002:
        RecordsEnd();
        _MsgRecords_bOpen = 0;
        break;
    case 0x80000003:
        MsgRecordsGetText(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength,
                    pArgs[4].pi);
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgTeamSelectSeekStart(DbCursor *pObject, int index, int saved)
{
    int found = 0;

    if (saved) {
        found = TeamDbSeekTmur(pObject, index, 0);
        if (found) {
            _MsgTeamSelect_aiTeam[index] = TeamDbGetId(pObject);
        }
    }
    if (!found) {
        if (_MsgTeamSelect_aiTeam[index] != -1) {
            found = TeamDbSeekId(pObject, _MsgTeamSelect_aiTeam[index], 0);
        }
        if (!found) {
            if (!TeamDbSeekTmur(pObject, index, 0)) {
                DbCursorFirst(pObject);
                MsgTeamSelectRandomize(pObject, index);
            }
        }
    }
}

unsigned char MsgTeamSelectProfileChanged(unsigned char pad)
{
    int db = UserProfileGetSelected(pad);

    if (db != -1) {
        if (DbUserGetId(UserProfileGetSelected(pad)) != _MsgTeamSelect_aiProfileDb[pad]) {
            _MsgTeamSelect_aiProfileDb[pad] = DbUserGetId(UserProfileGetSelected(pad));
            return 1;
        }
    } else if (_MsgTeamSelect_aiProfileDb[pad] != -1) {
        _MsgTeamSelect_aiProfileDb[pad] = db;
        return 1;
    }
    return 0;
}

void MsgTeamSelectCursorPrev(DbCursor *pObject)
{
    if (!DbCursorPrev(pObject)) {
        DbCursorLast(pObject);
    }
}

void MsgTeamSelectCursorNext(DbCursor *pObject)
{
    if (!DbCursorNext(pObject)) {
        DbCursorFirst(pObject);
    }
}

unsigned char MsgTeamSelectCountOpen(DbCursor *pObject, int side)
{
    unsigned char count = 0;

    if (DbCursorFirst(pObject)) {
        do {
            if (!MsgTeamSelectIsLocked(side, TeamDbGetId(pObject))) {
                count++;
            }
        } while (DbCursorNext(pObject));
    }
    return count;
}

void MsgTeamSelectRandomize(DbCursor *pObject, int side)
{
    do {
        unsigned int i = 0;
        unsigned int count = DbUtilRandomRange(0, _MsgTeamSelect_auOpenCount[side]);
        while (i < count) {
            MsgTeamSelectCursorNext(pObject);
            if (!MsgTeamSelectIsLocked(side, TeamDbGetId(pObject))) {
                i++;
            }
        }
    } while (_MsgTeamSelect_ppWindow[side][1] == TeamDbGetId(pObject));
}

void MsgTeamSelectPickRandom(int side)
{
    MsgTeamSelectRandomize(&_MsgTeamSelect_aTeamCursor[side], side);
    MsgTeamSelectCursorPrev(&_MsgTeamSelect_aTeamCursor[side]);
    for (unsigned int i = 0; i <= 2; i++) {
        _MsgTeamSelect_ppWindow[side][i] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[side]);
        MsgTeamSelectCursorNext(&_MsgTeamSelect_aTeamCursor[side]);
    }
}

void MsgTeamSelectGetTeamInfo(int side, int id, char *pName, int size, int *pA, int *pB, int *pC, int *pFree)
{
    DbCursor cursor;

    TeamDbOpenQuery(&cursor, 0);
    TeamDbSeekId(&cursor, id, 0);
    if (pName) {
        TeamDbGetName(&cursor, pName, size);
    }
    *pA = TeamDbGetTrof(&cursor);
    *pB = TeamDbGetTrde(&cursor);
    *pC = TeamDbGetTrov(&cursor);
    if (pFree) {
        *pFree = !MsgTeamSelectIsLocked(side, id);
    }
    TeamDbClose(&cursor);
}

int MsgTeamSelectIsLocked(int side, int id)
{
    int result = 0;
    int db = UserProfileGetSelected(side);
    int otherDb = UserProfileGetSelected(!side);

    if (db != -1) {
        DbCursor cursor;
        TeamLockOpen(&cursor, db);
        result = TeamLockIsHidden(&cursor, id);
        TeamLockClose(&cursor);
    } else if (otherDb != -1 && !PortDbSideHasPlayers(side)) {
        DbCursor cursor;
        TeamLockOpen(&cursor, otherDb);
        result = TeamLockIsHidden(&cursor, id);
        TeamLockClose(&cursor);
    } else {
        DbCursor *pObject = &_MsgTeamSelect_aTeamCursor[side];
        int position = DbCursorGetRow(pObject);
        TeamDbSeekId(pObject, id, 0);
        result = !DbCursorGetValue(pObject, 0x53495654);
        DbCursorSeek(pObject, position);
    }
    return result;
}

void MsgTeamSelectFindIndex(int side, int *pIndex)
{
    int i;
    int count = MsgTeamSelectGetCount(side);

    for (i = 0; i < count; i++) {
        if (GameModeTypeGet() == 8 && GauntletGetCurrentTeam(UserProfileFindIndex(DbUserGetCurrent())) != 0x3FF) {
            if (side == 1) {
                if (_MsgTeamSelect_apTeamIds[1][i] == GauntletGetCurrentTeam(UserProfileFindIndex(DbUserGetCurrent()))) {
                    *pIndex = i;
                    return;
                }
            } else if (_MsgTeamSelect_apTeamIds[0][i] == GauntletScreenGetSelection()) {
                *pIndex = i;
                return;
            }
        } else if (_MsgTeamSelect_apTeamIds[side][i] == _MsgTeamSelect_ppWindow[side][1]) {
            *pIndex = i;
            return;
        }
    }
    *pIndex = i;
}

void MsgTeamSelectListIds(int side, int *pIds, int count)
{
    int i = 0;

    if (DbCursorFirst(&_MsgTeamSelect_aTeamCursor[side])) {
        do {
            pIds[i++] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[side]);
        } while (DbCursorNext(&_MsgTeamSelect_aTeamCursor[side]));
    }
    DbCursorFirst(&_MsgTeamSelect_aTeamCursor[side]);
}

int MsgTeamSelectGetCount(int side)
{
    return DbCursorGetRowCount(&_MsgTeamSelect_aTeamCursor[side]);
}

void MsgTeamSelectGetTeam(int side, int index, int *pId, char *pName, int size)
{
    DbCursor cursor;

    *pId = _MsgTeamSelect_apTeamIds[side][index];
    TeamDbOpenQuery(&cursor, 0);
    TeamDbSeekId(&cursor, *pId, 0);
    TeamDbGetName(&cursor, pName, size);
    TeamDbClose(&cursor);
}

void MsgTeamSelectBrowsePlayer(int side, int direction, int *pId, char *pName, int nameSize, int *pPosition, char *pRole,
                 int roleSize, int *pFlag, int *pStats, char *pHeight, int heightSize, char *pWeight,
                 int weightSize)
{
    int found = -1;
    int result;

    if (direction == 3) {
        _MsgTeamSelect_aiBrowseRow[side] =
            _MsgTeamSelect_aiBrowseRow[side] - 1 < -1 ? _MsgTeamSelect_aiRosterCount[side] - 1 : _MsgTeamSelect_aiBrowseRow[side] - 1;
    } else if (direction == 1) {
        int current = _MsgTeamSelect_aiBrowseRow[side] + 1;
        if (current == _MsgTeamSelect_aiRosterCount[side]) {
            _MsgTeamSelect_aiBrowseRow[side] = -1;
        } else {
            _MsgTeamSelect_aiBrowseRow[side] = current;
        }
    }
    if (_MsgTeamSelect_aiBrowseRow[side] != -1) {
        for (int i = 0; i < _MsgTeamSelect_aiRosterCount[side]; i++) {
            if (_MsgTeamSelect_aRoster[side].mEntries[i].mIndex == _MsgTeamSelect_aiBrowseRow[side]) {
                found = i;
                break;
            }
        }
        Object_8008044C *pObject = &_MsgTeamSelect_aPlayerDb[side];
        *pId = _MsgTeamSelect_aRoster[side].mEntries[found].mId;
        pPosition[0] = _MsgTeamSelect_aiBrowseRow[side] + 1;
        pPosition[1] = _MsgTeamSelect_aiRosterCount[side];
        PlayerDbSeekId(pObject, *pId, &result);
        PlayerDbGetShortName(pObject, pName, nameSize);
        PositionAbbrevFormat(PlayerDbGetPbpo(pObject), pRole);
        if (pStats) {
            pStats[0] = PlayerDbGetBoostedRating(pObject, 6);
            pStats[1] = PlayerDbGetBoostedRating(pObject, 4);
            pStats[2] = PlayerDbGetBoostedRating(pObject, 7);
            pStats[3] = PlayerDbGetBoostedRating(pObject, 0);
            pStats[4] = PlayerDbGetBoostedRating(pObject, 3);
            pStats[5] = PlayerDbGetBoostedRating(pObject, 2);
            pStats[6] = PlayerDbGetBoostedRating(pObject, 1);
            pStats[7] = PlayerDbGetBoostedRating(pObject, 5);
            pStats[8] = PlayerDbGetBoostedRating(pObject, 8);
            pStats[9] = PlayerDbGetBoostedRating(pObject, 9);
        }
        unsigned int height = PlayerDbGetHeight(pObject);
        int weight = PlayerDbGetWeight(pObject);
        fn_801C2D88(pHeight, heightSize, "%d ft %d in", height / 12, height % 12);
        fn_801C2D88(pWeight, weightSize, "%d lbs", weight);
        if (_MsgTeamSelect_aRoster[side].mEntries[found].mSlot >= 0) {
            *pFlag = 1;
        } else {
            *pFlag = 0;
        }
    } else {
        *pId = -1;
        *pFlag = 0;
        strnzcpy(pName, "Auto Pick Players", nameSize);
        strnzcpy(pRole, "", roleSize);
        pPosition[0] = -1;
        pPosition[1] = -1;
        for (int i = 0; i < 10; i++) {
            pStats[i] = 0;
        }
    }
}

void MsgTeamSelectUnloadPortraits(int side)
{
    Object_8008044C list;
    Desc_8008044C desc;

    if (_MsgTeamSelect_aiTeam[side] != -1) {
        void *pList = UIGLibraryGetGlobal(1);
        desc.mUnknown4 = 1;
        desc.mUnknown8 = _MsgTeamSelect_aiTeam[side];
        PlayerCursorOpen(&list, &desc, 0x54415453);
        if (DbCursorFirst((DbCursor *)&list)) {
            do {
                UIGLibraryUnLoadItem(pList, 10, PlayerDbGetPortraitId(&list));
            } while (DbCursorNext((DbCursor *)&list));
        }
        fn_8008056C(&list);
    }
}

void MsgTeamSelectLoadPortraits(int side)
{
    Object_8008044C list;
    Desc_8008044C desc;
    void *pList = UIGLibraryGetGlobal(1);

    desc.mUnknown4 = 1;
    desc.mUnknown8 = _MsgTeamSelect_aiTeam[side];
    PlayerCursorOpen(&list, &desc, 0x54415453);
    if (DbCursorFirst((DbCursor *)&list)) {
        do {
            UIGLibraryLoadItem(pList, 10, PlayerDbGetPortraitId(&list));
        } while (DbCursorNext((DbCursor *)&list));
    }
    fn_8008056C(&list);
}

void MsgTeamSelectGetPlayerName(int side, char *pBuffer, int size, int full)
{
    if (full) {
        PlayerDbGetShortName(&_MsgTeamSelect_aPlayerDb[side], pBuffer, size);
    } else {
        PlayerDbGetFullName(&_MsgTeamSelect_aPlayerDb[side], pBuffer, size);
    }
}

void MsgTeamSelectOpenRoster(unsigned char side)
{
    Desc_8008044C desc;
    Object_8008044C *pObject = &_MsgTeamSelect_aPlayerDb[side];

    if (pObject->mUnknown0 != 0) {
        fn_8008056C(pObject);
    }
    desc.mUnknown0 = 1;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = _MsgTeamSelect_aiTeam[side];
    PlayerCursorOpen(pObject, &desc, FELoopIsMainFEActive() ? 0x54415453 : 0x454D4147);
    _MsgTeamSelect_aiBrowseRow[side] = -1;
}

/* Row -1 stands for the row under the cursor. */
static inline int ResolveRow(int list, int row)
{
    if (row == -1) {
        row = _MsgTeamSelect_aScroll[list].mTop + _MsgTeamSelect_aScroll[list].mRow;
        if (row >= _MsgTeamSelect_aiRosterCount[list]) {
            row = row - _MsgTeamSelect_aiRosterCount[list] - 1;
        }
    }
    return row;
}

static inline int NextRow(int list, int row)
{
    int next = -1;

    if (row != _MsgTeamSelect_aiRosterCount[list] - 1) {
        next = row + 1;
    }
    return next;
}

static inline void GetRow(int team, int list, int row, int *pOut)
{
    if (row != -1) {
        DbCursorSeek((DbCursor *)&_MsgTeamSelect_aPlayerDb[list], row);
        int id = PlayerDbGetId(&_MsgTeamSelect_aPlayerDb[list]);
        int i;

        pOut[0] = id;
        pOut[1] = -1;
        for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
            if (_MsgTeamSelect_aRoster[list].mEntries[i].mId == id && _MsgTeamSelect_aRoster[list].mEntries[i].mSlot >= 0) {
                pOut[1] = _MsgTeamSelect_aRoster[list].mEntries[i].mSlot;
                break;
            }
        }
    } else {
        pOut[1] = row;
        pOut[0] = row;
    }
}

void MsgTeamSelectResetPicks(unsigned char team)
{
    if (FELoopIsMainFEActive()) {
        if (_MsgTeamSelect_abResetPicks[team]) {
            unsigned char i;

            for (i = 0; i <= 19; i++) {
                _MsgTeamSelect_aRoster[team].mEntries[i].mSlot = -1;
                _MsgTeamSelect_aRoster[team].mEntries[i].mIndex = 0x7FFF;
                _MsgTeamSelect_aRoster[team].mEntries[i].mId = 0x7FFF;
                _MsgTeamSelect_aRoster[team].mEntries[i].mKey = 0xFF;
            }
            _MsgTeamSelect_aRoster[team].mUnknown140 = 0x7FFF;
        }
        if (DbCursorFirst((DbCursor *)&_MsgTeamSelect_aPlayerDb[team])) {
            do {
                fn_80081F50(&_MsgTeamSelect_aPlayerDb[team], team, 0);
            } while (DbCursorNext((DbCursor *)&_MsgTeamSelect_aPlayerDb[team]));
        }
        _MsgTeamSelect_bMainFE = 1;
    } else {
        _MsgTeamSelect_bMainFE = 0;
    }
}

void MsgTeamSelectResetScroll(unsigned char team)
{
    _MsgTeamSelect_aScroll[team].mTop = _MsgTeamSelect_aiRosterCount[team] - 1;
    _MsgTeamSelect_aScroll[team].mRow = 1;
}

void MsgTeamSelectFillRoster(unsigned char team)
{
    int i;

    _MsgTeamSelect_aiRosterCount[team] = DbCursorGetRowCount((DbCursor *)&_MsgTeamSelect_aPlayerDb[team]);
    DbCursorFirst((DbCursor *)&_MsgTeamSelect_aPlayerDb[team]);
    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        _MsgTeamSelect_aRoster[team].mEntries[i].mId = PlayerDbGetId(&_MsgTeamSelect_aPlayerDb[team]);
        _MsgTeamSelect_aRoster[team].mEntries[i].mIndex = i;
        DbCursorNext((DbCursor *)&_MsgTeamSelect_aPlayerDb[team]);
    }
}

void MsgTeamSelectGetVisibleRows(int team, int *pRow0, int *pRow1, int *pRow2, int *pCursor)
{
    int list = 1;
    int row;

    if (team == 0) {
        list = 0;
    }
    row = _MsgTeamSelect_aScroll[list].mTop;
    GetRow(team, list, row, pRow0);
    row = NextRow(list, row);
    GetRow(team, list, row, pRow1);
    row = NextRow(list, row);
    GetRow(team, list, row, pRow2);
    *pCursor = _MsgTeamSelect_aScroll[list].mRow;
}

void MsgTeamSelectScroll(int team, int unused, int delta, int *pOut)
{
    int list = 1;
    int row;

    if (team == 0) {
        list = 0;
    }
    row = _MsgTeamSelect_aScroll[list].mTop + _MsgTeamSelect_aScroll[list].mRow;
    if (row < _MsgTeamSelect_aiRosterCount[list]) {
        row += delta;
    } else {
        row = row - _MsgTeamSelect_aiRosterCount[list] - 1 + delta;
    }
    if (row < -1) {
        row = _MsgTeamSelect_aiRosterCount[list] - 1;
    } else if (row >= _MsgTeamSelect_aiRosterCount[list]) {
        row = -1;
    }
    if (_MsgTeamSelect_aScroll[list].mRow == 0 && delta < 0) {
        _MsgTeamSelect_aScroll[list].mTop = row;
    } else if (_MsgTeamSelect_aScroll[list].mRow == 2 && delta > 0) {
        if (_MsgTeamSelect_aScroll[list].mTop == _MsgTeamSelect_aiRosterCount[list] - 1) {
            _MsgTeamSelect_aScroll[list].mTop = -1;
        } else {
            _MsgTeamSelect_aScroll[list].mTop++;
        }
    } else {
        _MsgTeamSelect_aScroll[list].mRow += delta;
    }
    GetRow(team, list, row, pOut);
}

void MsgTeamSelectGetRowInfo(int team, int row, char *pName, int nameLength, char *pRole, int roleLength,
                 int *pValues)
{
    int list = 1;

    if (team == 0) {
        list = 0;
    }
    row = ResolveRow(list, row);
    if (row != -1) {
        DbCursorSeek((DbCursor *)&_MsgTeamSelect_aPlayerDb[list], row);
        MsgTeamSelectGetPlayerName(list, pName, nameLength, 0);
        PositionAbbrevFormat(PlayerDbGetPbpo(&_MsgTeamSelect_aPlayerDb[list]), pRole);
        if (pValues) {
            int values[10];

            PlayerGetGearRatings(&_MsgTeamSelect_aPlayerDb[list], values);
            pValues[0] = values[6];
            pValues[1] = values[4];
            pValues[2] = values[7];
            pValues[3] = values[0];
            pValues[4] = values[3];
            pValues[5] = values[2];
            pValues[6] = values[1];
            pValues[7] = values[5];
            pValues[8] = values[8];
            pValues[9] = values[9];
        }
    } else {
        fn_801C2E18(pName, " ");
        fn_801C2E18(pRole, " ");
        if (pValues) {
            unsigned char i;

            for (i = 0; i <= 9; i++) {
                pValues[i] = 1;
            }
        }
    }
}

void MsgTeamSelectSwapPending(int group, int kind, int slot)
{
    DepthChartSwapPending(group, kind, slot);
}

void MsgTeamSelectGetSideNames(int group, int kind, DepthChartText_t **pPairs)
{
    DepthChartGetSideNames(group, kind, pPairs);
}

void MsgTeamSelectCyclePending(int group, int kind, int slot, int code, int a, int b)
{
    DepthChartCyclePending(group, kind, slot, code, a, b);
}

int MsgTeamSelectHasFullTeam(int team)
{
    unsigned int picked = 0;
    int result = 1;
    int i;

    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        if (_MsgTeamSelect_aRoster[team].mEntries[i].mSlot >= 0) {
            picked++;
        }
    }
    if (picked < _MsgTeamSelect_iTeamSize) {
        result = 0;
    }
    return result;
}

void MsgTeamSelectGetPickedIds(int team, int *pIds)
{
    int count = 0;
    int i;

    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        if (_MsgTeamSelect_aRoster[team].mEntries[i].mSlot >= 0) {
            pIds[count] = _MsgTeamSelect_aRoster[team].mEntries[i].mId;
            count++;
        }
    }
    pIds[count] = 0x7FFF;
}

MsgTeamSelectEntry_t *MsgTeamSelectFindEntry(int team, int id, int *pIndex)
{
    MsgTeamSelectEntry_t *pSlot = 0;
    int i;

    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        if (_MsgTeamSelect_aRoster[team].mEntries[i].mId == id) {
            pSlot = &_MsgTeamSelect_aRoster[team].mEntries[i];
            break;
        }
    }
    if (pIndex) {
        *pIndex = i;
    }
    return pSlot;
}

void MsgTeamSelectAutoPickOne(int team, int *pIndex)
{
    int ids[22];
    int keys[16];
    int id = 0;
    int key;
    MsgTeamSelectEntry_t *pSlot;
    unsigned int picked;
    unsigned int keyed;

    // FAKEMATCH: dead keyed = 0 ahead of the loop (the loop resets it); key = 0 then reuses its zero register
    keyed = 0;
    key = 0;
    do {
        MsgTeamSelectEntry_t *pOpen = 0;
        int count;
        int i;

        picked = 0;
        keyed = 0;
        count = 0;
        for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
            pSlot = &_MsgTeamSelect_aRoster[team].mEntries[i];
            if (pSlot->mSlot >= 0) {
                if (pSlot->mKey != 0xFF) {
                    keys[keyed] = pSlot->mKey;
                    keyed++;
                    picked++;
                    continue;
                }
                if (!pOpen) {
                    pOpen = pSlot;
                }
                picked++;
            }
            ids[count] = _MsgTeamSelect_aRoster[team].mEntries[i].mId;
            count++;
        }
        keys[keyed] = 0xFF;
        ids[count] = 0x7FFF;
        if (pOpen) {
            pOpen->mKey = AutoDepthGetBestSlot(0, keys, pOpen->mId);
        }
    } while (picked > keyed);
    if (picked < _MsgTeamSelect_iTeamSize) {
        AutoDepthSelect(0, ids, keys, &id, &key);
        pSlot = MsgTeamSelectFindEntry(team, id, pIndex);
        pSlot->mKey = key;
    }
}

void MsgTeamSelectSwapEntries(int team, int a, int b)
{
    if (a != b) {
        MsgTeamSelectEntry_t slot = _MsgTeamSelect_aRoster[team].mEntries[a];

        _MsgTeamSelect_aRoster[team].mEntries[a] = _MsgTeamSelect_aRoster[team].mEntries[b];
        _MsgTeamSelect_aRoster[team].mEntries[b] = slot;
    }
}

void MsgTeamSelectAutoPick(int team)
{
    int ids[22];
    int index;
    int count = 0;
    int open = -1;
    int picked = 0;
    int i;

    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        if (_MsgTeamSelect_aRoster[team].mEntries[i].mSlot < 0) {
            if (open == -1) {
                open = i;
            }
        } else {
            picked++;
        }
        ids[count] = _MsgTeamSelect_aRoster[team].mEntries[i].mId;
        count++;
    }
    ids[count] = 0x7FFF;
    AutoDepthBuild(_MsgTeamSelect_aiDepthStyle[team], ids, 0);
    for (i = picked; i < _MsgTeamSelect_iTeamSize; i++) {
        MsgTeamSelectAutoPickOne(team, &index);
        if (_MsgTeamSelect_aRoster[team].mEntries[index].mSlot < 0) {
            MsgTeamSelectSwapEntries(team, open, index);
            _MsgTeamSelect_aRoster[team].mEntries[open].mSlot = open;
            open++;
            while (open <= 6 && _MsgTeamSelect_aRoster[team].mEntries[open].mSlot >= 0) {
                open++;
            }
        }
    }
    AutoDepthFree(0);
    _MsgTeamSelect_aRoster[team].mUnknown140 = _MsgTeamSelect_aRoster[team].mEntries[_MsgTeamSelect_iTeamSize - 1].mId;
    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        _MsgTeamSelect_aRoster[team].mEntries[i].mKey = 0xFF;
    }
}

/* An array argument points at a header of p[0] + 1 words; its data follows the header. */
int MsgTeamSelectHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        _MsgTeamSelect_iMode = pArgs[4].i;
        *pResult = MsgTeamSelectInit(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x80000002:
        MsgTeamSelectExit();
        break;
    case 0x80000003:
        MsgTeamSelectGetTeamInfo(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pi,
                    pArgs[4].pi, pArgs[5].pi, pArgs[6].pi);
        break;
    case 0x80000019:
        MsgTeamSelectGetTeam(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength);
        break;
    case 0x80000018:
        MsgTeamSelectFindIndex(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x80000005:
        MsgTeamSelectPickRandom(pArgs[0].i);
        break;
    case 0x80000006:
        if (GameModeTypeGet() == 8 && pArgs[0].i == 0) {
            MsgTeamSelectSetTeam(0, GauntletScreenGetSelection());
            break;
        }
        if (GameModeTypeGet() == 8 && MsgGameGetSetupState() == 1) {
            if (GauntletGetCurrentTeam(UserProfileFindIndex(DbUserGetCurrent())) == 0x3FF) {
                GauntletSetCurrentTeam(UserProfileFindIndex(DbUserGetCurrent()), pArgs[1].i);
            } else {
                pArgs[1].i = GauntletGetCurrentTeam(UserProfileFindIndex(DbUserGetCurrent()));
            }
        }
        if (GameModeTypeGet() == 6 && ChallengeIsActive()) {
            DbCursor query;
            int team;

            TeamDbOpen(&query, 0, 0x54415453);
            TeamDbSeekTmur(&query, 1, 0);
            team = TeamDbGetId(&query);
            TeamDbClose(&query);
            if (pArgs[0].i == 1 && pArgs[1].i != team) {
                MsgTeamSelectSetTeam(1, team);
                pArgs[0].i = 0;
            }
        }
        MsgTeamSelectSetTeam(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000016:
        *pResult = GauntletScreenGetSelection();
        break;
    case 0x80000017:
        *pResult = GauntletGetCurrentTeam(UserProfileFindIndex(DbUserGetCurrent()));
        break;
    case 0x8000000F:
        if (count == 5) {
            int *pRow0 = pArgs[1].pi;
            int *pRow1 = pArgs[2].pi;
            int *pRow2 = pArgs[3].pi;
            int row0 = pRow0[0] + 1;
            int row1 = pRow1[0] + 1;
            int row2 = pRow2[0] + 1;

            MsgTeamSelectGetVisibleRows(pArgs[0].i, pRow0 + row0, pRow1 + row1, pRow2 + row2, pArgs[4].pi);
        }
        break;
    case 0x80000010:
        if (count == 4) {
            int *pRow = pArgs[3].pi;
            int row = pRow[0] + 1;

            MsgTeamSelectScroll(pArgs[0].i, pArgs[1].i, pArgs[2].i, pRow + row);
        } else {
            MsgTeamSelectBrowsePlayer(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength,
                        (int *)(pArgs[4].i + (*pArgs[4].pi + 1) * 4), pArgs[5].pParams->mpText,
                        pArgs[5].pParams->mLength, pArgs[6].pi, (int *)(pArgs[7].i + (*pArgs[7].pi + 1) * 4),
                        pArgs[8].pParams->mpText, pArgs[8].pParams->mLength, pArgs[9].pParams->mpText,
                        pArgs[9].pParams->mLength);
        }
        break;
    case 0x80000011:
    {
        int *pValues = pArgs[5].pi;
        int values = pValues[0] + 1;

        MsgTeamSelectGetRowInfo(pArgs[0].i, -1, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pParams->mpText,
                    pArgs[3].pParams->mLength, pValues + values);
        break;
    }
    case 0x80000014:
        MsgTeamSelectGetRowName(pArgs[0].i, -1, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x8000000C:
        MsgTeamSelectSwapPending(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0x8000000A:
    {
        int *pPairs = pArgs[2].pi;
        int pairs = pPairs[0] + 1;

        MsgTeamSelectGetSideNames(pArgs[0].i, pArgs[1].i, (DepthChartText_t **)(pPairs + pairs));
        break;
    }
    case 0x8000000B:
        MsgTeamSelectSaveDepth(pArgs[0].i);
        break;
    case 0x8000000E:
        MsgTeamSelectCyclePending(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, (int)pArgs[4].pParams->mpText,
                    pArgs[4].pParams->mLength);
        break;
    case 0x80000008:
        *pResult = MsgTeamSelectPickPlayer(pArgs[0].i, pArgs[1].pi, pArgs[2].i);
        break;
    case 0x80000009:
        MsgTeamSelectUnpickPlayer(pArgs[0].i, pArgs[1].pi, pArgs[2].i);
        break;
    case 0x8000000D:
        MsgTeamSelectUndoPick(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x80000012:
    {
        int *pList = pArgs[1].pi;
        int list = pList[0] + 1;

        MsgTeamSelectApplyPicks(pArgs[0].i, pList + list);
        _MsgTeamSelect_bPicksApplied = 1;
        break;
    }
    case 0x80000007:
        MsgTeamSelectRequestAutoPick(pArgs[0].i);
        break;
    case 0x80000013:
        GameModeTypeGet();
        break;
    case 0xD:
        if (pArgs[0].i == -1) {
            *pResult = 1;
            break;
        }
        return 0;
    case 0x8000001A:
        MsgTeamSelectGetSlotPlayer(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x147:
        *pResult = DepthChartScreenIsSideShown(pArgs[0].i);
        break;
    case 0x149:
        DepthChartScreenGetSideName(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        *pArgs[3].pi = fn_80178D70(pArgs[0].i ? fn_80178308() : fn_80178320());
        break;
    case 0x14A: {
        int *pList = pArgs[1].pi;
        int list = pList[0] + 1;

        pList += list;
        DepthChartScreenGetSpot(pArgs[0].i, pArgs[4].i, pArgs[3].i, pList, pList + 1, pArgs[2].pParams->mpText,
                    pArgs[2].pParams->mLength);
        break;
    }
    case 0xE:
    case 0x80000015:
        break;
    default:
        return 0;
    }
    return 1;
}

int MsgTeamEditSelectInit(int *pCount, int *pA, int *pB, int *pC)
{
    *pC = 0;
    if (DbNiomIsModeActive()) {
        DbNiomEndMode();
    }
    *pB = 0;
    if (EditMenuIsOpen()) {
        EditMenuEnd();
    }
    TeamQuery query;
    query.mUnknown0 = 1;
    query.mUnknown4 = 3;
    TeamDbOpen(&_MsgTeamSelect_aTeamCursor[1], &query, 0x54415453);
    *pA = 0;
    *pCount = DbCursorGetRowCount(&_MsgTeamSelect_aTeamCursor[1]);
    return 0;
}

void MsgTeamEditSelectExit(void)
{
    DbCursor *pQuery = &_MsgTeamSelect_aTeamCursor[1];

    if (pQuery->mUnknown0) {
        TeamDbClose(pQuery);
    }
    if (MsgGameGetSetupState() == 1) {
        EditMenuBegin(5, _MsgTeamEditSelect_aiTeam[1]);
    } else {
        _MsgTeamEditSelect_aiTeam[1] = 0x3FF;
    }
}

void MsgTeamEditSelectGetTeamInfo(int mode, int id, char *pName, int nameLength, int *pA, int *pB, int *pC, int *pMode)
{
    if (mode == 1) {
        DbCursor query;

        TeamDbOpen(&query, 0, 0x54415453);
        TeamDbSeekId(&query, id, 0);
        if (pName) {
            TeamDbGetName(&query, pName, nameLength);
        }
        *pA = TeamDbGetTrof(&query);
        *pB = TeamDbGetTrde(&query);
        *pC = TeamDbGetTrov(&query);
        if (pMode) {
            *pMode = mode;
        }
        TeamDbClose(&query);
    }
}

void MsgTeamEditSelectGetTeam(int mode, int row, int *pId, char *pName, int nameLength)
{
    DbCursor query;

    if (mode == 1) {
        int current = DbCursorGetRow(&_MsgTeamSelect_aTeamCursor[1]);

        DbCursorSeek(&_MsgTeamSelect_aTeamCursor[1], row);
        *pId = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[1]);
        TeamDbGetName(&_MsgTeamSelect_aTeamCursor[1], pName, nameLength);
        if (current != -1) {
            DbCursorSeek(&_MsgTeamSelect_aTeamCursor[1], current);
        }
    }
}

void MsgTeamEditSelectSeekCurrent(int mode, int *pResult)
{
    int found = 0;

    if (mode == 1) {
        found = TeamDbSeekId(&_MsgTeamSelect_aTeamCursor[1], _MsgTeamEditSelect_aiTeam[1], pResult);
    }
    if (!found) {
        *pResult = found;
    }
}

void MsgTeamEditSelectSetCurrent(int index, int value)
{
    _MsgTeamEditSelect_aiTeam[index] = value;
}

int MsgTeamEditSelectHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pResult = MsgTeamEditSelectInit(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x80000002:
        MsgTeamEditSelectExit();
        break;
    case 0x80000003:
        MsgTeamEditSelectGetTeamInfo(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pi,
                    pArgs[4].pi, pArgs[5].pi, pArgs[6].pi);
        break;
    case 0x80000019:
        MsgTeamEditSelectGetTeam(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength);
        break;
    case 0x80000018:
        MsgTeamEditSelectSeekCurrent(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x80000006:
        MsgTeamEditSelectSetCurrent(pArgs[0].i, pArgs[1].i);
        break;
    case 0xF: {
        int *pList = pArgs[0].pi;
        int offset = pList[0] + 1;
        int i;

        pList += offset;

        for (i = 3; i >= 0; i--) {
            pList[i] = 1;
        }
        break;
    }
    case 0xA:
        *pArgs[0].pi = 0;
        break;
    case 0x111:
        *pResult = -1;
        break;
    case 0x80000004:
    case 0x80000005:
        break;
    default:
        return 0;
    }
    return 1;
}


void MsgTeamSelectFillSlots(int team)
{
    int count = 0;
    int i;

    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        MsgTeamSelectEntry_t *pPlayer = &_MsgTeamSelect_aRoster[team].mEntries[i];
        if (pPlayer->mSlot >= 0) {
            count++;
        }
    }
    for (i = 0; i < _MsgTeamSelect_aiRosterCount[team] && count <= 6; i++) {
        MsgTeamSelectEntry_t *pPlayer = &_MsgTeamSelect_aRoster[team].mEntries[i];
        if (pPlayer->mSlot < 0) {
            pPlayer->mSlot = count;
            count++;
        }
    }
}
void MsgTeamSelectTrimSlots(int team)
{
    for (int i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        MsgTeamSelectEntry_t *pPlayer = &_MsgTeamSelect_aRoster[team].mEntries[i];
        if (pPlayer->mSlot >= _MsgTeamSelect_iTeamSize) {
            pPlayer->mSlot = -1;
        }
    }
}

int MsgTeamSelectDispatch(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    int result;

    if (_MsgTeamSelect_bEditMode == 0) {
        result = MsgTeamSelectHandleMessage(id, pArgs, count, pResult);
    } else {
        result = MsgTeamEditSelectHandleMessage(id, pArgs, count, pResult);
    }
    return result;
}

void MsgTeamSelectQuickSetup(int id0, int id1)
{
    int saved1 = _MsgTeamSelect_aiTeam[1];
    int saved0 = _MsgTeamSelect_aiTeam[0];

    MsgGameSetSetupState(1);
    MsgTeamSelectInit(0, 0, 0, 0);

    if (id0 == -2) {
        MsgTeamSelectPickRandom(0);
        _MsgTeamSelect_aiTeam[0] = _MsgTeamSelect_ppWindow[0][1];
    } else if (id0 == -1) {
        _MsgTeamSelect_aiTeam[0] = 31;
    } else if (id0 == -3) {
        TeamDbSeekTmur(&_MsgTeamSelect_aTeamCursor[0], 0, 0);
        _MsgTeamSelect_aiTeam[0] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[0]);
    } else {
        _MsgTeamSelect_aiTeam[0] = id0;
    }

    if (id1 == -2) {
        do {
            MsgTeamSelectPickRandom(1);
            _MsgTeamSelect_aiTeam[1] = _MsgTeamSelect_ppWindow[1][1];
        } while (_MsgTeamSelect_aiTeam[0] == _MsgTeamSelect_aiTeam[1]);
    } else if (id1 == -1) {
        _MsgTeamSelect_aiTeam[1] = 20;
    } else if (id1 == -3) {
        TeamDbSeekTmur(&_MsgTeamSelect_aTeamCursor[1], 1, 0);
        _MsgTeamSelect_aiTeam[1] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[1]);
    } else {
        _MsgTeamSelect_aiTeam[1] = id1;
    }

    MsgTeamSelectSetTeam(0, _MsgTeamSelect_aiTeam[0]);
    MsgTeamSelectSetTeam(1, _MsgTeamSelect_aiTeam[1]);
    MsgTeamSelectRequestAutoPick(0);
    MsgTeamSelectRequestAutoPick(1);
    MsgTeamSelectApplyPicks(0, 0);
    MsgTeamSelectApplyPicks(1, 0);
    MsgTeamSelectExit();

    _MsgTeamSelect_aiTeam[1] = saved1;
    _MsgTeamSelect_aiTeam[0] = saved0;
}

void MsgTeamSelectSetChallengeTeam(int team, int id)
{
    _MsgTeamSelect_aiChallengeTeam[team] = id;
}

void MsgTeamSelectNull(void)
{
}

int MsgTeamSelectInit(int *pCount1, int *pCount0, int *pMode, int *pFlag)
{
    TeamQuery query;
    MsgTeamSelectChanged_t pair = { 0, 0 };
    unsigned char color[3];
    int mode;
    unsigned int i;
    unsigned int j;

    mode = fn_801486A0();
    if (GameModeTypeGet() == 6) {
        _MsgTeamSelect_aiSavedTeam[0] = _MsgTeamSelect_aiTeam[0];
        _MsgTeamSelect_aiSavedTeam[1] = _MsgTeamSelect_aiTeam[1];
        _MsgTeamSelect_aiTeam[0] = _MsgTeamSelect_aiChallengeTeam[0];
        _MsgTeamSelect_aiTeam[1] = _MsgTeamSelect_aiChallengeTeam[1];
    }
    if (pFlag) {
        *pFlag = 1;
    }
    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }

    switch (mode) {
    case 3:
        _MsgTeamSelect_iTeamSize = 3;
        break;
    case 4:
        _MsgTeamSelect_iTeamSize = 4;
        break;
    case 5:
        _MsgTeamSelect_iTeamSize = 7;
        break;
    default:
        _MsgTeamSelect_iTeamSize = 7;
        break;
    }
    if (pMode) {
        *pMode = _MsgTeamSelect_iTeamSize;
    }

    _MsgTeamSelect_bDone = 0;
    _MsgTeamSelect_aiBrowseRow[0] = -1;
    _MsgTeamSelect_aiBrowseRow[1] = -1;
    pair.mUnknown0 = MsgTeamSelectProfileChanged(0);
    pair.mUnknown1 = MsgTeamSelectProfileChanged(1);
    _MsgTeamSelect_abProfileChanged[0] = pair.mUnknown0;
    _MsgTeamSelect_abProfileChanged[1] = pair.mUnknown1;

    if (MsgGameGetSetupState() == 1) {
        if (GameModeTypeGet() == 6) {
            if (!ChalGameHasGeneratedOpponent() || _MsgTeamSelect_iMode != 0x6B) {
                CreateTeamLoadUserTeams();
            }
        } else {
            CreateTeamLoadUserTeams();
        }
    }

    query.mUnknown0 = 1;
    query.mUnknown4 = 0;
    if (GameModeTypeGet() == 3) {
        query.mUnknown4 = 3;
    } else if (GameModeTypeGet() == 6) {
        if (_MsgTeamSelect_iMode == 0x6B) {
            if (_MsgTeamSelect_aiTeam[0] == 63) {
                int id;
                ChalGameGenerateTeam(&id);
                _MsgTeamSelect_aiTeam[0] = id;
            }
            query.mUnknown4 = 0;
        } else {
            query.mUnknown4 = 3;
        }
    } else if (PortDbSideHasPlayers(0) == 0 && UserProfileGetSelected(1) != -1) {
        query.mUnknown4 = 1;
        query.mUnknown8 = 1;
    } else {
        query.mUnknown4 = 1;
        query.mUnknown8 = 0;
    }
    TeamDbOpenQuery(&_MsgTeamSelect_aTeamCursor[0], &query);
    if (MsgGameGetSetupState() == 1) {
        _MsgTeamSelect_auOpenCount[0] = MsgTeamSelectCountOpen(&_MsgTeamSelect_aTeamCursor[0], 0);
    }

    query.mUnknown4 = 0;
    query.mUnknown0 = 1;
    if (GameModeTypeGet() == 3) {
        query.mUnknown4 = 3;
    } else if (GameModeTypeGet() == 6) {
        if (_MsgTeamSelect_iMode == 0x6B) {
            query.mUnknown4 = 1;
            query.mUnknown8 = 1;
        } else {
            query.mUnknown4 = 3;
        }
    } else {
        int ai = PortDbSideHasPlayers(1);
        if (ai == 0 && UserProfileGetSelected(0) != -1) {
            query.mUnknown4 = 1;
            query.mUnknown8 = ai;
        } else {
            query.mUnknown4 = 1;
            query.mUnknown8 = 1;
        }
    }
    TeamDbOpenQuery(&_MsgTeamSelect_aTeamCursor[1], &query);
    if (MsgGameGetSetupState() == 1) {
        _MsgTeamSelect_auOpenCount[1] = MsgTeamSelectCountOpen(&_MsgTeamSelect_aTeamCursor[1], 1);
    }

    if (TeamDbSeekTmur(&_MsgTeamSelect_aTeamCursor[0], 0, 0)) {
        color[0] = TeamDbGetColor1(&_MsgTeamSelect_aTeamCursor[0]);
        color[1] = TeamDbGetColor2(&_MsgTeamSelect_aTeamCursor[0]);
        color[2] = TeamDbGetColor3(&_MsgTeamSelect_aTeamCursor[0]);
        TeamLogoRequestTint(0, 4, TeamDbGetLogo(&_MsgTeamSelect_aTeamCursor[0]), 172, color);
    }
    if (TeamDbSeekTmur(&_MsgTeamSelect_aTeamCursor[1], 1, 0)) {
        color[0] = TeamDbGetColor1(&_MsgTeamSelect_aTeamCursor[1]);
        color[1] = TeamDbGetColor2(&_MsgTeamSelect_aTeamCursor[1]);
        color[2] = TeamDbGetColor3(&_MsgTeamSelect_aTeamCursor[1]);
        TeamLogoRequestTint(1, 4, TeamDbGetLogo(&_MsgTeamSelect_aTeamCursor[1]), 172, color);
    }

    _MsgTeamSelect_ppWindow = (int **)fn_801D2B7C(8, 0, 0);
    for (i = 0; i < 2; i++) {
        _MsgTeamSelect_ppWindow[i] = (int *)fn_801D2B7C(12, 0, 0);
    }

    if (GameModeTypeGet() == 6) {
        if (_MsgTeamSelect_iMode == 0x6B) {
            TeamDbSeekId(&_MsgTeamSelect_aTeamCursor[0], _MsgTeamSelect_aiTeam[0], 0);
        } else {
            DbCursorFirst(&_MsgTeamSelect_aTeamCursor[0]);
        }
    } else {
        MsgTeamSelectSeekStart(&_MsgTeamSelect_aTeamCursor[0], 0, pair.mUnknown0);
    }
    for (i = 0; i < 1; i++) {
        MsgTeamSelectCursorPrev(&_MsgTeamSelect_aTeamCursor[0]);
    }
    for (j = 0; j < 3; j++) {
        _MsgTeamSelect_ppWindow[0][j] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[0]);
        MsgTeamSelectCursorNext(&_MsgTeamSelect_aTeamCursor[0]);
    }

    if (GameModeTypeGet() == 6) {
        if (_MsgTeamSelect_iMode == 0x6B) {
            TeamDbSeekId(&_MsgTeamSelect_aTeamCursor[1], _MsgTeamSelect_aiTeam[1], 0);
        } else if (_MsgTeamSelect_aiTeam[0] != 0) {
            _MsgTeamSelect_aiTeam[1] = _MsgTeamSelect_aiTeam[0];
            TeamDbSeekId(&_MsgTeamSelect_aTeamCursor[1], _MsgTeamSelect_aiTeam[0], 0);
        } else {
            DbCursorFirst(&_MsgTeamSelect_aTeamCursor[1]);
            _MsgTeamSelect_aiTeam[1] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[1]);
        }
    } else {
        MsgTeamSelectSeekStart(&_MsgTeamSelect_aTeamCursor[1], 1, pair.mUnknown1);
    }
    for (i = 0; i < 1; i++) {
        MsgTeamSelectCursorPrev(&_MsgTeamSelect_aTeamCursor[1]);
    }
    for (j = 0; j < 3; j++) {
        _MsgTeamSelect_ppWindow[1][j] = TeamDbGetId(&_MsgTeamSelect_aTeamCursor[1]);
        MsgTeamSelectCursorNext(&_MsgTeamSelect_aTeamCursor[1]);
    }

    void *pList = UIGLibraryGetGlobal(1);
    UIGLibraryLoadItem(pList, 10, 1);
    UIGLibraryLoadItem(pList, 10, 1);
    DepthChartLoad(MsgGameGetSetupState() == 1);
    _MsgTeamSelect_abResetPicks[0] = _MsgTeamSelect_abResetPicks[1] = MsgGameGetSetupState() == 1;
    if (MsgGameGetSetupState() == 1) {
        _MsgTeamSelect_abAutoFill[0] = 1;
        _MsgTeamSelect_abAutoFill[1] = 1;
        _MsgTeamSelect_abAutoPick[0] = 1;
        _MsgTeamSelect_abAutoPick[1] = 1;
        _MsgTeamSelect_abNewTeam[0] = 1;
        _MsgTeamSelect_abNewTeam[1] = 1;
    }

    if (pCount0 && pCount1) {
        *pCount0 = MsgTeamSelectGetCount(0);
        *pCount1 = MsgTeamSelectGetCount(1);
        _MsgTeamSelect_apTeamIds[0] = (int *)fn_801D2B7C(*pCount0 * 4, 0, 0);
        _MsgTeamSelect_apTeamIds[1] = (int *)fn_801D2B7C(*pCount1 * 4, 0, 0);
        MsgTeamSelectListIds(0, _MsgTeamSelect_apTeamIds[0], *pCount0);
        MsgTeamSelectListIds(1, _MsgTeamSelect_apTeamIds[1], *pCount1);
    }
    return 0;
}

void MsgTeamSelectSetTeam(int team, int id)
{
    MsgTeamSelectUnloadPortraits(team);
    _MsgTeamSelect_aiTeam[team] = id;
    MsgTeamSelectLoadPortraits(team);
    MsgTeamSelectOpenRoster(team);
    if (FELoopIsMainFEActive()) {
        if (_MsgTeamSelect_abResetPicks[team]) {
            int index = UserProfileGetSelected(team);
            if (index == -1) {
                index = UserProfileGetSelected(team == 0);
            }
            fn_80082558(id, index);
            MsgTeamSelectResetPicks(team);
            MsgTeamSelectFillRoster(team);
            MsgTeamSelectResetScroll(team);
            _MsgTeamSelect_aiDepthStyle[team] = SyncRandGetRange(0, 5);
            _MsgTeamSelect_abAutoPick[team] = 1;
            _MsgTeamSelect_abNewTeam[team] = 0;
            _MsgTeamSelect_abAutoFill[team] = 1;
        }
        _MsgTeamSelect_abResetPicks[team] = 1;
    }
}

void MsgTeamSelectExit(void)
{
    DepthChartSide_t records[2];
    int ids[2][7];
    int value0 = 0;
    int value1 = 0;
    int id0 = 0;
    int id1 = 0;

    _MsgTeamSelect_bDone = 1;
    MsgTeamSelectUnloadPortraits(0);
    MsgTeamSelectUnloadPortraits(1);
    void *pList = UIGLibraryGetGlobal(1);
    UIGLibraryUnLoadItem(pList, 10, 1);
    UIGLibraryUnLoadItem(pList, 10, 1);

    if (MsgGameGetSetupState() == 1) {
        id0 = _MsgTeamSelect_aiTeam[0];
        TeamDbSeekId(&_MsgTeamSelect_aTeamCursor[0], id0, 0);
        value0 = DbCursorGetInt(&_MsgTeamSelect_aTeamCursor[0], 0x49524454);
        id1 = _MsgTeamSelect_aiTeam[1];
        TeamDbSeekId(&_MsgTeamSelect_aTeamCursor[1], id1, 0);
        value1 = DbCursorGetInt(&_MsgTeamSelect_aTeamCursor[1], 0x49524454);
    }
    if (_MsgTeamSelect_aTeamCursor[0].mUnknown0) {
        TeamDbClose(&_MsgTeamSelect_aTeamCursor[0]);
    }
    DbCursor *pCursor = &_MsgTeamSelect_aTeamCursor[1];
    if (pCursor->mUnknown0) {
        TeamDbClose(pCursor);
    }
    if (MsgGameGetSetupState() == 1) {
        GameInfoSet(0, id0);
        GameInfoSet(1, id1);
        fn_8022A508(0, id0, id0, 0, value0);
        fn_8022A508(1, id1, id1, 0, value1);
        fn_8022DC7C(0);
        fn_8022DCB0(0);
        fn_8022DCE4(0);
        fn_8022DD18(0);
    }

    for (unsigned int i = 0; i < 2; i++) {
        fn_801D2BD0(_MsgTeamSelect_ppWindow[i]);
    }
    fn_801D2BD0(_MsgTeamSelect_ppWindow);
    if (_MsgTeamSelect_apTeamIds[0]) {
        fn_801D2BD0(_MsgTeamSelect_apTeamIds[0]);
        fn_801D2BD0(_MsgTeamSelect_apTeamIds[1]);
        _MsgTeamSelect_apTeamIds[0] = 0;
        _MsgTeamSelect_apTeamIds[1] = 0;
    }

    if (MsgGameGetSetupState() == 1 && ((GameModeTypeGet() == 8 && _MsgTeamSelect_bPicksApplied) || GameModeTypeGet() != 8) &&
        ((GameModeTypeGet() == 6 && _MsgTeamSelect_bPicksApplied) || GameModeTypeGet() != 6)) {
        DepthChartGetSide(0, &records[0]);
        DepthChartGetSide(1, &records[1]);
        for (unsigned char i = 0; i <= 6; i++) {
            PlayerDbSeekId(&_MsgTeamSelect_aPlayerDb[0], records[0].mUnknown[i], 0);
            fn_80081F50(&_MsgTeamSelect_aPlayerDb[0], 0, 1);
            ids[0][i] = _MsgTeamSelect_aRoster[0].mEntries[i].mId;
            PlayerDbSeekId(&_MsgTeamSelect_aPlayerDb[1], records[1].mUnknown[i], 0);
            fn_80081F50(&_MsgTeamSelect_aPlayerDb[1], 1, 1);
            ids[1][i] = _MsgTeamSelect_aRoster[1].mEntries[i].mId;
        }
        PlyrObjsSetTeamIds(0, ids[0]);
        PlyrObjsSetTeamIds(1, ids[1]);
    }

    if (_MsgTeamSelect_aPlayerDb[0].mUnknown0) {
        fn_8008056C(&_MsgTeamSelect_aPlayerDb[0]);
    }
    Object_8008044C *pPlayer = &_MsgTeamSelect_aPlayerDb[1];
    if (pPlayer->mUnknown0) {
        fn_8008056C(pPlayer);
    }
    DepthChartSave();

    if (MsgGameGetSetupState() == 1) {
        if (GameModeTypeGet() == 6 && _MsgTeamSelect_bPicksApplied) {
            if (ChallengeIsActive()) {
                MsgStadiumStartGame(ChalGetCurrent()->mUnknown1BC);
            } else {
                MsgStadiumStartGame(fn_800A3444());
            }
            MsgChallengeSetResumed(1);
        }
        FELoopSetResume(1);
    }
    if (MsgGameGetSetupState() == 0) {
        GameTextSetSetupActive(0);
        if (GameModeTypeGet() == 6) {
            if (!ChalGameHasGeneratedOpponent() || _MsgTeamSelect_iMode != 0x6B) {
                fn_8018C48C(0x454D4147);
                fn_8018C48C(0x54415453);
            }
        } else {
            fn_8018C48C(0x454D4147);
            fn_8018C48C(0x54415453);
        }
    }

    AutoDepthSetRateCallback(0);
    AutoDepthSetSelectCallback(0);
    if (GameModeTypeGet() == 6) {
        if (ChalGameHasGeneratedOpponent() && MsgGameGetSetupState() == 1 && _MsgTeamSelect_iMode != 0x6B) {
            _MsgTeamSelect_aiChallengeTeam[0] = _MsgTeamSelect_aiTeam[0];
        }
        _MsgTeamSelect_aiTeam[0] = _MsgTeamSelect_aiSavedTeam[0];
        _MsgTeamSelect_aiTeam[1] = _MsgTeamSelect_aiSavedTeam[1];
    }
    _MsgTeamSelect_bPicksApplied = 0;
}

void MsgTeamSelectRequestAutoPick(int team)
{
    int side = team ? 1 : 0;

    _MsgTeamSelect_abAutoFill[side] = 1;
    _MsgTeamSelect_abAutoPick[side] = 1;
}

void MsgTeamSelectApplyPicks(int team, int *pList)
{
    int list[8];
    int side = team ? 1 : 0;

    if (_MsgTeamSelect_abAutoFill[side]) {
        if (_MsgTeamSelect_abAutoPick[side]) {
            MsgTeamSelectAutoPick(side);
            _MsgTeamSelect_abAutoPick[side] = 0;
        }
        MsgTeamSelectFillSlots(team);
        MsgTeamSelectGetPickedIds(team, list);
        DepthChartAutoFill(team, list, _MsgTeamSelect_aiDepthStyle[side]);
    }
    DepthChartRevertSide(team);

    if (pList) {
        unsigned char count = 0;
        for (unsigned char i = 0; count <= 6 && i < 20; i++) {
            if (_MsgTeamSelect_aRoster[team].mEntries[i].mSlot >= 0) {
                pList[count] = _MsgTeamSelect_aRoster[team].mEntries[i].mId;
                count++;
            }
        }
    }
}

void MsgTeamSelectGetRowName(int team, int index, char *pBuffer, int size)
{
    int side = team ? 1 : 0;

    index = ResolveRow(side, index);
    if (index != -1) {
        DbCursorSeek((DbCursor *)&_MsgTeamSelect_aPlayerDb[side], index);
        MsgTeamSelectGetPlayerName(side, pBuffer, size, 1);
    } else {
        strnzcpy(pBuffer, " ", size + 1);
    }
}

int MsgTeamSelectPickPlayer(int team, int *pNext, int id)
{
    int result = 0;

    if (id != -1) {
        int side;
        int slot;
        int i;

        result = 1;
        side = team ? 1 : 0;
        for (slot = 0; slot < _MsgTeamSelect_aiRosterCount[team]; slot++) {
            if (_MsgTeamSelect_aRoster[side].mEntries[slot].mSlot < 0) {
                break;
            }
        }
        for (i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
            if (_MsgTeamSelect_aRoster[side].mEntries[i].mId == id) {
                _MsgTeamSelect_aRoster[side].mEntries[i].mSlot = slot;
                break;
            }
        }
        if (!_MsgTeamSelect_abAutoFill[side]) {
            DepthChartSetEntryPair(team, id, _MsgTeamSelect_aDepthSpots[side].mUnknown1C[slot], _MsgTeamSelect_aDepthSpots[side].mUnknown0[slot]);
        }
        if (i != slot) {
            MsgTeamSelectSwapEntries(team, i, slot);
        }
        for (slot++; slot < _MsgTeamSelect_aiRosterCount[team]; slot++) {
            if (_MsgTeamSelect_aRoster[side].mEntries[slot].mSlot < 0) {
                break;
            }
        }
        *pNext = slot;
        if (MsgTeamSelectHasFullTeam(side)) {
            _MsgTeamSelect_aRoster[side].mUnknown140 = id;
        }
        _MsgTeamSelect_abAutoPick[side] = 0;
    }
    return result;
}

void MsgTeamSelectUnpickPlayer(int team, int *pIndex, int id)
{
    int side = team ? 1 : 0;

    for (*pIndex = 0; *pIndex < _MsgTeamSelect_aiRosterCount[team]; (*pIndex)++) {
        if (_MsgTeamSelect_aRoster[side].mEntries[*pIndex].mId == id) {
            _MsgTeamSelect_aRoster[side].mEntries[*pIndex].mSlot = -1;
            break;
        }
    }
    _MsgTeamSelect_aRoster[side].mUnknown140 = 0x7FFF;
}

void MsgTeamSelectUndoPick(int team, int *pIndex)
{
    int side = team ? 1 : 0;

    MsgTeamSelectTrimSlots(team);
    for (int i = 0; i < _MsgTeamSelect_aiRosterCount[side]; i++) {
        if (_MsgTeamSelect_aRoster[side].mEntries[i].mId == _MsgTeamSelect_aRoster[side].mUnknown140) {
            _MsgTeamSelect_aiBrowseRow[side] = _MsgTeamSelect_aRoster[side].mEntries[i].mIndex;
            break;
        }
    }
    PlayerDbSeekId(&_MsgTeamSelect_aPlayerDb[side], _MsgTeamSelect_aRoster[side].mUnknown140, &_MsgTeamSelect_aScroll[side].mTop);
    if (_MsgTeamSelect_aScroll[side].mTop == 0) {
        _MsgTeamSelect_aScroll[side].mTop = -1;
    } else {
        _MsgTeamSelect_aScroll[side].mTop--;
    }
    _MsgTeamSelect_aScroll[side].mRow = 1;
    for (*pIndex = 0; *pIndex < _MsgTeamSelect_aiRosterCount[side]; (*pIndex)++) {
        if (_MsgTeamSelect_aRoster[side].mEntries[*pIndex].mId == _MsgTeamSelect_aRoster[side].mUnknown140) {
            _MsgTeamSelect_aRoster[side].mEntries[*pIndex].mSlot = -1;
            break;
        }
    }
    _MsgTeamSelect_aRoster[side].mUnknown140 = 0x7FFF;
    _MsgTeamSelect_abAutoFill[team] = 1;
}

void MsgTeamSelectSaveDepth(int team)
{
    _MsgTeamSelect_abAutoFill[team] = 0;
    for (int i = 0; i < 7; i++) {
        DepthChartFindPlayer(team, _MsgTeamSelect_aRoster[team].mEntries[i].mId, &_MsgTeamSelect_aDepthSpots[team].mUnknown1C[i],
                    &_MsgTeamSelect_aDepthSpots[team].mUnknown0[i]);
    }
}

void MsgTeamSelectSetEditMode(unsigned char value)
{
    _MsgTeamSelect_bEditMode = value;
}

void MsgTeamSelectGetSlotPlayer(int team, int slot, int *pId)
{
    *pId = -1;
    for (int i = 0; i < _MsgTeamSelect_aiRosterCount[team]; i++) {
        if (_MsgTeamSelect_aRoster[team].mEntries[i].mSlot == slot) {
            *pId = _MsgTeamSelect_aRoster[team].mEntries[i].mId;
            break;
        }
    }
}

int _MsgStadium_aiEnvId[] = { 9, 2, 0, 1, 5, 3, 4, 6, 7, 8, 10, 11 };
unsigned char _MsgStadium_abLocked[12] = { 0 };

void MsgStadiumGetInfo(int index, char *pName, int nameSize, char *pTeam, int teamSize, int *pValue, char *pText,
                 int textSize, int *pA, int *pB, int *pFlag)
{
    if (!_MsgStadium_pEntries[index].mValid) {
        EnvSelect(_MsgStadium_aiEnvId[index]);
        EnvGetUIName(pName, nameSize);
        EnvGetEVLO((int)pTeam, teamSize);
        EnvGetEVDE((int)pText, textSize);
        EnvGetPictures(&_MsgStadium_pEntries[index].mUnknownAC, &_MsgStadium_pEntries[index].mUnknownB0);
        EnvRelease();
        RecordsBegin();
        RecordsSeekRow(6, _MsgStadium_aiEnvId[index]);
        _MsgStadium_pEntries[index].mUnknownA8 = RecordsGetValue(5);
        RecordsEnd();
        if (_MsgStadium_bCheckLocks) {
            int index0 = UserProfileGetSelected(0);
            int index1 = UserProfileGetSelected(1);
            *pFlag = 1;
            DbUserGetCurrent();
            if (index0 != -1) {
                *pFlag = EnvIsLocked(index0, _MsgStadium_aiEnvId[index]);
            }
            if (index1 != -1 && *pFlag == 1) {
                *pFlag = EnvIsLocked(index1, _MsgStadium_aiEnvId[index]);
            }
            if (index0 == -1 && index1 == -1) {
                if (_MsgStadium_aiEnvId[index] == 10 || _MsgStadium_aiEnvId[index] == 11) {
                    *pFlag = 1;
                } else {
                    *pFlag = 0;
                }
            }
            if (GameModeTypeGet() == 8) {
                int value = GauntletGetTeamsLeft(UserProfileGetSelected(1));
                if (value == 0 && _MsgStadium_aiEnvId[index] == 11) {
                    *pFlag = value;
                }
            }
        } else {
            *pFlag = _MsgStadium_abLocked[index];
        }
        strnzcpy(_MsgStadium_pEntries[index].mText0, pName, sizeof(_MsgStadium_pEntries[index].mText0));
        strnzcpy(_MsgStadium_pEntries[index].mText21, pTeam, sizeof(_MsgStadium_pEntries[index].mText21));
        *pValue = _MsgStadium_pEntries[index].mUnknownA8;
        strnzcpy(_MsgStadium_pEntries[index].mText42, pText, sizeof(_MsgStadium_pEntries[index].mText42));
        _MsgStadium_pEntries[index].mUnknownB4 = *pFlag;
        *pA = _MsgStadium_pEntries[index].mUnknownAC;
        *pB = _MsgStadium_pEntries[index].mUnknownB0;
        _MsgStadium_pEntries[index].mValid = 1;
    } else {
        strnzcpy(pName, _MsgStadium_pEntries[index].mText0, nameSize + 1);
        strnzcpy(pTeam, _MsgStadium_pEntries[index].mText21, teamSize + 1);
        *pValue = _MsgStadium_pEntries[index].mUnknownA8;
        strnzcpy(pText, _MsgStadium_pEntries[index].mText42, textSize + 1);
        *pFlag = _MsgStadium_pEntries[index].mUnknownB4;
        *pA = _MsgStadium_pEntries[index].mUnknownAC;
        *pB = _MsgStadium_pEntries[index].mUnknownB0;
    }
    _MsgStadium_iCurrent = index;
}

void MsgStadiumInit(int *pCount, int *pCurrent, int *pResult)
{
    int current = _MsgStadium_iCurrent;
    int flag;
    _MsgStadium_pEntries = (MsgStadiumEntry_t *)fn_801D2B7C(12 * sizeof(MsgStadiumEntry_t), 0, 0);
    memset(_MsgStadium_pEntries, 0, 12 * sizeof(MsgStadiumEntry_t));
    for (unsigned char i = 0; i <= 11; i++) {
        MsgStadiumEntry_t *pEntry = &_MsgStadium_pEntries[i];
        MsgStadiumGetInfo(i, pEntry->mText0, 32, pEntry->mText21, 32, &pEntry->mUnknownA8, pEntry->mText42,
                    101, &pEntry->mUnknownAC, &pEntry->mUnknownB0, &flag);
    }
    if (_MsgStadium_bFirst) {
        _MsgStadium_bFirst = 0;
        MsgStadiumPickRandom(&_MsgStadium_iCurrent, 0);
    } else {
        if (_MsgStadium_pEntries[current].mUnknownB4) {
            MsgStadiumPickRandom(&current, 0);
        }
        _MsgStadium_iCurrent = current;
    }
    *pCount = 12;
    *pCurrent = _MsgStadium_iCurrent;
    if (GameModeTypeGet() == 8 && GauntletGetTeamsLeft(UserProfileGetSelected(1)) == 0) {
        *pCurrent = 11;
        _MsgStadium_iCurrent = 11;
    }
    switch (fn_801486A0()) {
    case 0:
    case 1:
    case 2:
        *pResult = 1;
        break;
    default:
        *pResult = 0;
        break;
    }
}

void MsgStadiumExit(int id, int unused)
{
    if (MsgGameGetSetupState() == 1) {
        fn_800A2F3C(id);
        FELoopStartGame();
    } else if (fn_801486A0() != 15) {
        MsgTeamPickFreePool();
    }
    fn_801D2BD0(_MsgStadium_pEntries);
}

int MsgStadiumPickRandom(int *pIndex, int any)
{
    int index;
    do {
        index = SyncRandGetRange(0, 12);
    } while ((!any && _MsgStadium_pEntries[index].mUnknownB4) || index == _MsgStadium_iCurrent);
    int id = _MsgStadium_aiEnvId[index];
    *pIndex = index;
    return id;
}

void MsgStadiumSetCurrent(int index)
{
    _MsgStadium_iCurrent = index;
}

int MsgStadiumHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgStadiumInit(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000002:
        MsgStadiumExit(_MsgStadium_aiEnvId[_MsgStadium_iCurrent], pArgs[0].i);
        break;
    case 0x80000003:
        MsgStadiumGetInfo(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength,
                    pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pi,
                    pArgs[4].pParams->mpText, pArgs[4].pParams->mLength, pArgs[5].pi,
                    pArgs[6].pi, pArgs[7].pi);
        break;
    case 0x80000004:
        MsgStadiumPickRandom(pArgs[0].pi, 0);
        break;
    case 0x80000005:
        MsgStadiumSetCurrent(pArgs[0].i);
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgStadiumStartGame(int id)
{
    int count;
    int current;
    int flag;
    MsgGameSetSetupState(1);
    MsgStadiumInit(&count, &current, &flag);
    int saved = _MsgStadium_iCurrent;
    if (id == -1) {
        _MsgStadium_iCurrent = 0;
    } else if (id == -2) {
        MsgStadiumPickRandom(&_MsgStadium_iCurrent, 1);
    } else {
        for (_MsgStadium_iCurrent = 0; _MsgStadium_iCurrent <= 11; _MsgStadium_iCurrent++) {
            if (_MsgStadium_aiEnvId[_MsgStadium_iCurrent] == id) {
                break;
            }
        }
    }
    if (_MsgStadium_iCurrent > 11) {
        if (id > 11) {
            id = _MsgStadium_aiEnvId[0];
        }
        MsgStadiumExit(id, 0);
    } else {
        MsgStadiumExit(_MsgStadium_aiEnvId[_MsgStadium_iCurrent], 0);
    }
    _MsgStadium_iCurrent = saved;
}

int MsgStadiumGetEnvId(unsigned int index)
{
    int id = 12;
    if (index <= 11) {
        id = _MsgStadium_aiEnvId[index];
    }
    return id;
}

void MsgStartScreenEnter(MenuArg_t *pArgs, int count, int *pResult)
{
    _MsgStartScreen_bShown = 1;
    FELoopSetVisited(0);
    SndgMusicStop();
    MemCardScreenSetFlag(0);
}

void MsgStartScreenExit(MenuArg_t *pArgs, int count, int *pResult)
{
    _MsgStartScreen_bShown = 0;
    if (!InGameIsDemo()) {
        SndgMusicReshuffle();
        SndgMusicContinue();
    }
}

int MsgStartScreenHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgStartScreenEnter(pArgs, count, pResult);
        break;
    case 0x80000002:
        MsgStartScreenExit(pArgs, count, pResult);
        break;
    default:
        return 0;
    }
    return 1;
}

int MsgStartScreenIsShown(void)
{
    unsigned short a = 0;
    unsigned short b = 0;
    fn_80219650(gUISMainInfo, &a, &b);
    return a == 0 && b == 3 && _MsgStartScreen_bShown;
}

int MsgUserStatsCycle(int control)
{
    int index = _MsgUserStats_iProfile;
    if (index != -1) {
        switch (control) {
        case -1:
            if (index == 0) {
                _MsgUserStats_iProfile = UserRecGetCount() - 1;
            } else {
                _MsgUserStats_iProfile--;
            }
            break;
        case 0:
            break;
        case 1:
            if (index == UserRecGetCount() - 1) {
                _MsgUserStats_iProfile = 0;
            } else {
                _MsgUserStats_iProfile++;
            }
            break;
        }
    }
    return index;
}

void MsgUserStatsLoad(void)
{
    DbCursor query;
    if (_MsgUserStats_iProfile != -1) {
        UserStatsOpen(&query, _MsgUserStats_iProfile);
        _MsgUserStats_pStats->mValues[0] = UserStatsGet(&query, 10);
        _MsgUserStats_pStats->mValues[1] = UserStatsGet(&query, 11);
        _MsgUserStats_pStats->mValues[4] = UserStatsGet(&query, 3);
        _MsgUserStats_pStats->mValues[3] = UserStatsGet(&query, 4);
        _MsgUserStats_pStats->mValues[5] = UserStatsGet(&query, 5);
        _MsgUserStats_pStats->mValues[2] = _MsgUserStats_pStats->mValues[3] + _MsgUserStats_pStats->mValues[4] + _MsgUserStats_pStats->mValues[5];
        _MsgUserStats_pStats->mValues[6] = UserStatsGet(&query, 8);
        _MsgUserStats_pStats->mValues[7] = UserStatsGet(&query, 9);
        _MsgUserStats_pStats->mValues[8] = UserStatsGet(&query, 6);
        _MsgUserStats_pStats->mValues[9] = UserStatsGet(&query, 7);
        _MsgUserStats_pStats->mValues[10] = UserStatsGet(&query, 12);
        _MsgUserStats_pStats->mValues[11] = UserStatsGet(&query, 13);
        _MsgUserStats_pStats->mValues[12] = UserInfoGetTotalPoints(DbUserGetId(_MsgUserStats_iProfile));
        _MsgUserStats_pStats->mUnknown34 = UserStatsGet(&query, 0);
        _MsgUserStats_pStats->mUnknown38 = UserStatsGet(&query, 1);
        _MsgUserStats_pStats->mStreak = UserStatsGet(&query, 2);
        UserStatsClose(&query);
        UserRecGetName(_MsgUserStats_iProfile, _MsgUserStats_pStats->mName);
    } else {
        for (unsigned char i = 0; i <= 12; i++) {
            _MsgUserStats_pStats->mValues[i] = 0;
        }
        _MsgUserStats_pStats->mUnknown34 = 0;
        _MsgUserStats_pStats->mUnknown38 = 0;
        _MsgUserStats_pStats->mStreak = 0;
        strnzcpy(_MsgUserStats_pStats->mName, "None", 14);
    }
}

void MsgUserStatsInit(int *pCount)
{
    signed char indices[4];
    _MsgUserStats_pStats = (MsgUserStats_t *)fn_801D2B7C(sizeof(MsgUserStats_t), 0, 0);
    *pCount = UserRecGetCount();
    UserProfileSortByRecent(indices, 4);
    if (*pCount > 0) {
        _MsgUserStats_iProfile = indices[0];
    } else {
        _MsgUserStats_iProfile = -1;
    }
    MsgUserStatsLoad();
}

void MsgUserStatsExit(void)
{
    fn_801D2BD0(_MsgUserStats_pStats);
    _MsgUserStats_pStats = 0;
    _MsgUserStats_iProfile = -1;
}

void MsgUserStatsGet(int control, MenuText_t *pName, int *pUnknown34, int *pUnknown38,
                 MenuText_t *pStreak, int *pValues, int *pClear)
{
    if (MsgUserStatsCycle(control) != _MsgUserStats_iProfile) {
        MsgUserStatsLoad();
    }
    strnzcpy(pName->mpText, _MsgUserStats_pStats->mName, pName->mLength);
    *pUnknown34 = _MsgUserStats_pStats->mUnknown34;
    *pUnknown38 = _MsgUserStats_pStats->mUnknown38;
    int streak = _MsgUserStats_pStats->mStreak;
    if (streak >= 0) {
        if (streak == 1) {
            strnzcpy(pStreak->mpText, "1 Win", pStreak->mLength);
        } else {
            fn_801C2E18(pStreak->mpText, "%d Wins", streak);
        }
    } else if (streak == -1) {
        strnzcpy(pStreak->mpText, "1 Loss", pStreak->mLength);
    } else {
        fn_801C2E18(pStreak->mpText, "%d Losses", -streak);
    }
    unsigned char i;
    for (i = 0; i <= 12; i++) {
        pValues[i] = _MsgUserStats_pStats->mValues[i];
    }
    for (i = 0; i <= 15; i++) {
        pClear[i] = 0;
    }
}

int MsgUserStatsHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgUserStatsInit(pArgs[0].pi);
        break;
    case 0x80000002:
        MsgUserStatsExit();
        break;
    case 0x80000003:
    {
        int *pValues = pArgs[5].pi;
        int *pClear = pArgs[6].pi;
        int valuesOffset = pValues[0] + 1;
        int clearOffset = pClear[0] + 1;
        MsgUserStatsGet(pArgs[0].i, pArgs[1].pParams, pArgs[2].pi, pArgs[3].pi,
                    pArgs[4].pParams, pValues + valuesOffset, pClear + clearOffset);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

/* Remaps the Windows-1252 trademark, registered and copyright signs to 0xB0-0xB2
   and replaces curly quotes with plain ones. */
void MsgCreditsFormatText(char *pText)
{
    signed char length = strlen(pText);
    for (signed char i = 0; i < length; i++) {
        switch (pText[i]) {
        case '\x99':
            pText[i] = '\xb0';
            break;
        case '\xae':
            pText[i] = '\xb1';
            break;
        case '\xa9':
            pText[i] = '\xb2';
            break;
        case '\x93':
        case '\x94':
            pText[i] = '"';
            break;
        case '\x91':
        case '\x92':
            pText[i] = '\'';
            break;
        }
    }
}

void MsgCreditsInit(void)
{
    CreditsOpen();
    _MsgCredits_iSpaces = -1;
    _MsgCredits_iCachedType = 2;
}

void MsgCreditsShutdown(void)
{
    CreditsClose();
}

void MsgCreditsGetNextLine(int *pCount, int *pValue, MenuText_t *pRecord)
{
    int ok = 1;
    if (_MsgCredits_iSpaces < 0) {
        ok = CreditsFetchLine();
    }
    if (ok) {
        CreditsGetLineType(pValue);
        if (_MsgCredits_iSpaces == -1 && *pValue == 2 && _MsgCredits_iCachedType != 2) {
            _MsgCredits_iSpaces = 2;
        } else if (_MsgCredits_iSpaces == -1 && *pValue == 1 && _MsgCredits_iCachedType != 1) {
            _MsgCredits_iSpaces = 1;
        }
        if (_MsgCredits_iSpaces > 0) {
            _MsgCredits_iSpaces--;
            strcpy(pRecord->mpText, " ");
            *pValue = 0;
            (*pCount)--;
        } else {
            CreditsGetLine(pRecord->mpText, pRecord->mLength);
            _MsgCredits_iSpaces = -1;
            _MsgCredits_iCachedType = *pValue;
        }
    } else {
        strcpy(pRecord->mpText, " ");
        *pValue = 0;
    }
    MsgCreditsFormatText(pRecord->mpText);
}

int MsgCreditsHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgCreditsInit();
        CreditsCountLines(pArgs[0].pi);
        break;
    case 0x80000002:
        MsgCreditsShutdown();
        break;
    case 0x80000003:
        MsgCreditsGetNextLine(pArgs[0].pi, pArgs[1].pi, pArgs[2].pParams);
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgTeamSourcesEnter(void)
{
    _MsgTeamSources_iSavedOption = GameOptionsGet(1);
    CreateTeamLoadUserTeams();
    StoryTeamLoadUserTeams(0, 1);
}

void MsgTeamSourcesExit(void)
{
    GameOptionsSet(1, _MsgTeamSources_iSavedOption);
    MsgTeamPickSetSources(_MsgTeamSources_bSource1 + _MsgTeamSources_bSource2 * 2 + _MsgTeamSources_bSource4 * 4 + _MsgTeamSources_bSource8 * 8);
    if (MsgGameGetSetupState() == 1) {
        MsgTeamPickSetMode(_MsgTeamSources_iMode, 14);
        MsgTeamPickRequestTeamSave();
    }
}

int MsgTeamSourcesGet(int key)
{
    switch (key) {
    case 1:
        return _MsgTeamSources_iMode;
    case 2:
        return _MsgTeamSources_bSource1;
    case 3:
        return _MsgTeamSources_bSource2;
    case 4:
        return _MsgTeamSources_bSource4;
    case 5:
        return _MsgTeamSources_bSource8;
    case 6:
        return _MsgTeamSources_iSavedOption;
    }
    return 0;
}

void MsgTeamSourcesSet(int key, int value)
{
    switch (key) {
    case 1:
        _MsgTeamSources_iMode = value;
        break;
    case 2:
        _MsgTeamSources_bSource1 = value;
        break;
    case 3:
        _MsgTeamSources_bSource2 = value;
        break;
    case 4:
        _MsgTeamSources_bSource4 = value;
        break;
    case 5:
        _MsgTeamSources_bSource8 = value;
        break;
    case 6:
        _MsgTeamSources_iSavedOption = value;
        break;
    }
}

int MsgTeamSourcesHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000007:
        MsgTeamSourcesEnter();
        break;
    case 0x80000008:
        MsgTeamSourcesExit();
        break;
    case 0x80000001:
        *pResult = MsgTeamSourcesGet(pArgs[0].i);
        break;
    case 0x80000002:
        MsgTeamSourcesSet(pArgs[0].i, pArgs[1].i);
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgUnlocksInit(int *pCount)
{
    _MsgUnlocks_iProfileCount = UserRecGetCount();
    *pCount = _MsgUnlocks_iProfileCount;
    _MsgUnlocks_pList = new (0) DbCursor;
    if (_MsgUnlocks_iProfileCount > 0) {
        signed char indices[2];
        unsigned char auxiliary[2];
        UserProfileSortByRecent(indices, 2);
        for (int i = 0; i < 2; ++i) {
            if (indices[i] != -1) {
                auxiliary[i] = 1;
            }
        }
        _MsgUnlocks_iProfile = indices[0];
        _MsgUnlocks_pStatus = new (0) DbCursor;
    } else {
        _MsgUnlocks_iProfile = -1;
    }
}

void MsgUnlocksExit(void)
{
    if (_MsgUnlocks_pList) {
        UnlockListClose(_MsgUnlocks_pList);
        delete _MsgUnlocks_pList;
        _MsgUnlocks_pList = 0;
    }
    if (_MsgUnlocks_pStatus) {
        UnlockStatusClose(_MsgUnlocks_pStatus);
        delete _MsgUnlocks_pStatus;
        _MsgUnlocks_pStatus = 0;
    }
}

void MsgUnlocksCycleUser(int control, char *pText, int *pResult)
{
    if (_MsgUnlocks_iProfile == -1) {
        fn_801C2E18(pText, "None");
        *pResult = 0;
        return;
    }
    if (control != -1 && _MsgUnlocks_iProfileCount > 1) {
        if (control == 3) {
            if (_MsgUnlocks_iProfile - 1 >= 0) {
                _MsgUnlocks_iProfile--;
            } else {
                _MsgUnlocks_iProfile = _MsgUnlocks_iProfileCount - 1;
            }
        } else if (control == 1) {
            _MsgUnlocks_iProfile = (_MsgUnlocks_iProfile + 1) % _MsgUnlocks_iProfileCount;
        }
    }
    if (_MsgUnlocks_pStatus->mUnknown0) {
        UnlockStatusClose(_MsgUnlocks_pStatus);
    }
    UnlockStatusOpen(_MsgUnlocks_pStatus, _MsgUnlocks_iProfile);
    UserRecGetName(_MsgUnlocks_iProfile, pText);
    *pResult = UserInfoGetPoints(DbUserGetId(_MsgUnlocks_iProfile));
}

void MsgUnlocksGetItem(int index, char *pText, int *pUnknown94, int *pFlag)
{
    UnlockItem_t record;
    DbCursorSeek(_MsgUnlocks_pList, index);
    UnlockListReadItem(_MsgUnlocks_pList, &record);
    fn_801C2E18(pText, record.mName);
    char *pDot = strchr(pText, '.');
    if (pDot) {
        pDot[1] = 0;
    }
    *pUnknown94 = record.mUnknown94;
    if (_MsgUnlocks_iProfile != -1 && UnlockStatusGet(_MsgUnlocks_pStatus, record.mIndex) != 0) {
        *pFlag = 1;
    } else {
        *pFlag = 0;
    }
}

const char *_MsgUnlocks_apCategoryText[] = { "User Stats", "Game Modes", "Save Files", "Miscellaneous" };

void MsgUnlocksCycleCategory(int control, char *pText, int size, int *pResult)
{
    switch (control) {
    case -1:
        break;
    case 1:
        _MsgUnlocks_iCategory = (_MsgUnlocks_iCategory + 1) % 4;
        break;
    case 3:
        if (--_MsgUnlocks_iCategory < 0) {
            _MsgUnlocks_iCategory = 3;
        }
        break;
    }
    if (_MsgUnlocks_pList->mUnknown0) {
        UnlockListClose(_MsgUnlocks_pList);
    }
    UnlockListOpen(_MsgUnlocks_pList, 1, _MsgUnlocks_iCategory);
    strnzcpy(pText, _MsgUnlocks_apCategoryText[_MsgUnlocks_iCategory], size);
    *pResult = DbCursorGetRowCount(_MsgUnlocks_pList);
}

int MsgUnlocksHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgUnlocksInit(pArgs[0].pi);
        break;
    case 0x80000002:
        MsgUnlocksExit();
        break;
    case 0x80000003:
        MsgUnlocksCycleUser(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[2].pi);
        break;
    case 0x80000004:
        MsgUnlocksGetItem(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[2].pi,
                    pArgs[3].pi);
        break;
    case 0x80000005:
        MsgUnlocksCycleCategory(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength,
                    pArgs[2].pi);
        break;
    default:
        return 0;
    }
    return 1;
}
}
