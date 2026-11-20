/* Story-mode events: lists the story's events with their completion flags,
   sets up the chosen event's teams and street-event settings, records the
   completed event and builds its reward text ("You have completed %s!",
   points and credits), and handles the event screen's messages. Also builds
   the stat table of the event's players and sets the story progress that
   the cheats ask for. */
#include <string.h>

#include "game/DbCursor.h"
#include "game/StoryEvents.h"
#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8008044C.h"
#include "game/DepthChart.h"
#include "game/AutoDepth.h"
#include "game/StevTable.h"
#include "game/FELoop.h"
#include "game/StoryTournament.h"
#include "game/GameOptions.h"
#include "game/TDbCompilePerformOp.h"

/* Index returned by DbUserFindIndex and values read for it by StoryEventsReadProgress. */
struct StoryEventsState_t {
    signed char mIndex;
    signed char mUnknown1;
    short mUnknown2;
    unsigned int mPpxe;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    unsigned short mUnknown1C;
    int mUnknown20;
};

/* Values returned by GameOptionsGet and restored through GameOptionsSet. */
struct StoryEventsSavedOptions_t {
    int mValue0;
    int mValue1;
    int mValue14;
    unsigned char mSaved;
};

/* Street event settings; StoryEventsStartEvent sets the timer words. */
struct MiniGameSettings_t {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

/* Destination of the text copied by StoryEventsCopyRewardText. */
struct StoryTextBuffer_t {
    char mUnknown0[4];
    int mSize;
    char *mpText;
};

struct StoryTextArgs_t {
    StoryTextBuffer_t *mpText;
};

/* Teams set up by StoryEventsSetupTeams. */
struct StoryMatch_t {
    int mAway;
    int mHome;
    int mUnknown8;
};

/* Per-event completion flags filled by StoryEventsUpdateCompletion. */
struct StoryProgress_t {
    unsigned char mDone[12];
    unsigned char mComplete;
};

extern "C" {
int MsgMainMenuGetActivePad(void);
int MsgMainMenuAssignPads(void);
void MsgPlayerSelectStart(int a, int b, int c);
void MsgStadiumStartGame(int a);
void MsgTeamPickSetMode(int a, int b);
void MsgTeamPickSetSources(int a);
void MsgTeamPickRequestTeamSave(void);
void MsgMainMenuGoTo(int a);
void SndgMusicPumpFrame(int a);
Object_80039F5C *PlyrFindByPoid(int id);
void DepthChartAutoFillEx(int group, int *list, int value, int a, int b);
unsigned char PortDbGetSidePort(int a);
void EnvSelect(int id);
void EnvRelease(void);
void EnvGetUIName(char *pDest, int count);
void PortDbSetControlledPlayer(int pad, int id);
void SndgMusicWaitForStart(int frames);
void GameInfoSet(int index, int value);
int GameInfoGet(int index);
int PlayerDbGetPrty(Object_8008044C *pObject);
int PlayerDbGetPbpo(Object_8008044C *pObject);
unsigned int PlayerDbGetRating(Object_8008044C *pObject, int index);
void PlayerDbSetRating(Object_8008044C *pObject, int index, int value);
void TeamDbSetPlayersTgti(int id);
int TeamDbCreate(int type, int logo, const char *pName);
void TeamDbCreatePlayers(int a, int *pIds, int *pCounts, int count, int *pOut, int total);
void TeamDbAutoPickPlayers(int a, int b, int *pOut, unsigned int count, int *pIn, unsigned int size);
void TeamDbLoadSideWithCopies(int a, int *pList, int b, int c);
void TeamDbLoadSide(int team, int *pList, int side, int count);
void TeamDbLoadLibraryItem(int value);
void TeamDbUnloadLibraryItem(int value);
unsigned int ExpLevelGetForPoints(int ppxe);
int ExpLevelGetScft(int vlxe);
int ExpLevelGetLvbn(int vlxe);
int ExpLevelGetName(int vlxe, char *pName, int size);
int ExpLevelClose(void);
int ExpLevelOpen(void);
void UserStatsOpen(DbCursor *pObject, int index);
void UserStatsClose(DbCursor *pObject);
void UserStatsSet(DbCursor *pObject, int index, int value);
int UserStatsGet(DbCursor *pObject, unsigned int index);
void UserInfoAddPoints(int db, int id);
void fn_801485B4(void);
int fn_801485D4(void);
void fn_801485EC(int value);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
void fn_8014F3DC(int ticks);
void EditMenuBegin(int mode, int value);
void UserProfileSelect(signed char a, int b);
void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor);
int TeamLogoGetHandle(int a);
void StoryTeamCursorOpen(DbCursor *pCursor, int index);
void StoryTeamCursorClose(DbCursor *pCursor);
int StoryTeamLoadToStats(int index, int a, int *pIds, int *pCount);
int StoryTeamGetLogo(DbCursor *pCursor);
void fn_8018C48C(int tag);
void StoryClearFlags(int index);
void StoryClearCompletedEvents(int index);
void StoryPlayerCursorOpen(DbCursor *pCursor, int index);
void StoryPlayerCursorClose(DbCursor *pCursor);
int StoryPlayerGetFirstName(DbCursor *pCursor, int row, char *pBuffer, int size);
int StoryPlayerGetLastName(DbCursor *pCursor, int row, char *pBuffer, int size);
int StoryPlayerGetShortName(DbCursor *pCursor, int row, char *pName, int size);
int StoryGetExpPoints(int index);
void StorySetExpPoints(int index, int value);
void StorySetNew(int index, int value);
int StoryGetDevPoints(int index);
void StorySetDevPoints(int index, int value);
int StoryIsEventCompleted(int index, int id);
void StoryAddCompletedEvent(int index, int id);
int StoryCountRemainingEvents(int index);
int StoryAreGroupEventsCompleted(int index, int a);
int StoryGetLkss(int index);
int StoryIsNew(int index);
void StorySetLkss(int index, int value);
int SstlGetEntryTag(unsigned int index, char *pEtnr, int size);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int MemFill(void *pDest, int size, int value, int width);
int TDbTblDestroy(int handle, int table);
int TDbTblFindUnusedId(int handle, int *pTable);
int TDbTblGetCount(int handle, int table, DbFilter *pFilter, unsigned short *pCount);
int DbUserGetId(int index);
int DbUserGetDb(int a);
int DbUserFindIndex(int a);
int DbUserGetCurrent(void);
void InGameRewardSetAlt(unsigned char value);
void StoryTournamentClearEvent(void);
void StoryTournamentBegin(void);
int MsgGameGetSetupState(void);
int fn_80178AE0(void);
}

Object_8008044C _StoryEvents_PlayerCursor;
DbCursor _StoryEvents_UserStats;
StevRow_t _StoryEvents_EventRow;
extern MiniGameSettings_t lbl_8031BDD4;

StoryMatch_t _StoryEvents_Match;
int _StoryEvents_aaLineup[2][7];
char _StoryEvents_szRewardText[200];
StoryProgress_t _StoryEvents_Progress;

unsigned char _StoryEvents_bActive = 0;
int _StoryEvents_iResumeState = 2;
int _StoryEvents_iResumeScreen = 4;
int _StoryEvents_bFirstEventDone = 0;
StevRow_t *_StoryEvents_pEvent = 0;
Object_8008044C *_StoryEvents_pPlayerCursor = 0;
DbCursor *_StoryEvents_pUserStats = 0;
float _StoryEvents_fRatingScale = 0.0f;
int _StoryEvents_iPlayerTable = -1;
int _StoryEvents_iTeamTable = -1;
int _StoryEvents_iRewardPenalty = -1;
int _StoryEvents_bStpyFull = 0;

static unsigned char _StoryEvents_bLocalSlotFree;
static unsigned char _StoryEvents_bEarlierDone;

StoryEventsState_t _StoryEvents_State = {-1, -1, 0, 0, 0x7FFF};
StoryEventsSavedOptions_t _StoryEvents_SavedOptions = {-1, 0, 0, 0};
int _StoryEvents_aSlotDive[16] = {12, 12, 12, 12, 5, 7, 9, 8, 6, 4, 1, 2, 0, 3, 11, 10};
int _StoryEvents_aDiveSlot[12] = {12, 10, 11, 13, 9, 4, 8, 5, 7, 6, 15, 14};
int _StoryEvents_aCreatePositions[7] = {0, 1, 2, 4, 8, 9, 13};
int _StoryEvents_aScaledRatings[10] = {0, 4, 1, 3, 2, 5, 6, 7, 8, 9};

extern "C" {
void StoryEventsBuildEventTables(int team, int id, int *pList);
int *StoryEventsGetLineup(int index);
void StoryEventsSetRewardPenalty(int value);
int StoryEventsIsNewStory(void);
float StoryEventsGetRatingScale(void);
void StoryEventsScalePlayerRatings(Object_8008044C *pObject, int id, float scale);
int StoryEventsPlaceSpecialPlayers(StevRow_t *pRow, int *pList);
void StoryEventsSetLineup(int index, int *pList);

void StoryEventsClose(void)
{
    ExpLevelClose();
    fn_8008056C(_StoryEvents_pPlayerCursor);
    _StoryEvents_pPlayerCursor = 0;
    StevClose();
    UserStatsClose(_StoryEvents_pUserStats);
    _StoryEvents_State.mIndex = -1;
    _StoryEvents_pUserStats = 0;
}

void StoryEventsOpen(void)
{
    _StoryEvents_State.mIndex = DbUserFindIndex(DbUserGetCurrent());
    _StoryEvents_pPlayerCursor = &_StoryEvents_PlayerCursor;
    PlayerCursorOpen(&_StoryEvents_PlayerCursor, 0, 0x54415453);
    StevOpen();
    ExpLevelOpen();
    _StoryEvents_State.mUnknown2 = 0x7FFF;
    _StoryEvents_pUserStats = &_StoryEvents_UserStats;
    SndgMusicPumpFrame(1);
    UserStatsOpen(_StoryEvents_pUserStats, _StoryEvents_State.mIndex);
}

void StoryEventsReadProgress(void)
{
    _StoryEvents_State.mPpxe = StoryGetExpPoints(_StoryEvents_State.mIndex);
    _StoryEvents_State.mUnknown1C = ExpLevelGetForPoints(_StoryEvents_State.mPpxe);
    _StoryEvents_State.mUnknown8 = UserStatsGet(_StoryEvents_pUserStats, 14);
    _StoryEvents_State.mUnknownC = StoryGetDevPoints(_StoryEvents_State.mIndex);
    _StoryEvents_State.mUnknown1 = StoryGetLkss(_StoryEvents_State.mIndex);
}

void StoryEventsLoadTeamLogo(int set)
{
    DbCursor cursor;
    int value;

    StoryTeamCursorOpen(&cursor, _StoryEvents_State.mIndex);
    value = StoryTeamGetLogo(&cursor);
    StoryTeamCursorClose(&cursor);
    if (set) {
        TeamDbLoadLibraryItem(value);
    } else {
        TeamDbUnloadLibraryItem(value);
    }
}

int StoryEventsGetSlotDive(int index)
{
    return _StoryEvents_aSlotDive[index];
}

int StoryEventsGetDiveSlot(int index)
{
    return _StoryEvents_aDiveSlot[index];
}

void StoryEventsSyncDatabases(void)
{
    SndgMusicPumpFrame(1);
    SndgMusicPumpFrame(0);
    fn_8018C48C(0x54415453);
    SndgMusicPumpFrame(1);
    fn_8018C48C(0x454D4147);
    SndgMusicPumpFrame(0);
}

int StoryEventsUpdateCompletion(void)
{
    StevRow_t row;
    int complete = 1;
    int i;

    for (i = 0; i <= 11; i++) {
        SndgMusicPumpFrame(1);
        int done = StoryAreGroupEventsCompleted(_StoryEvents_State.mIndex, i);
        _StoryEvents_Progress.mDone[i] = done;
        if (complete && !done) {
            int count = StevCountDiveRows(i);
            for (int j = 0; j < count; j++) {
                if (StevGetRow(i, j, &row) && !StoryIsEventCompleted(_StoryEvents_State.mIndex, row.mNets) &&
                    row.mItes != 4) {
                    complete = 0;
                    break;
                }
            }
        }
    }
    _StoryEvents_Progress.mComplete = complete;
    return complete;
}

unsigned char StoryEventsIsAllComplete(void)
{
    return _StoryEvents_Progress.mComplete;
}

int StoryEventsIsFinalEvent(void)
{
    return StoryCountRemainingEvents(_StoryEvents_State.mIndex) == 2;
}

void StoryEventsAwardExpPoints(int *pTotal)
{
    StevRow_t *pRow = _StoryEvents_pEvent;
    int ppxe = _StoryEvents_State.mPpxe + pRow->mPewr;
    unsigned short limit = _StoryEvents_State.mUnknown1C;
    _StoryEvents_State.mUnknown10 = pRow->mPewr;
    unsigned int level = ExpLevelGetForPoints(ppxe);
    StorySetExpPoints(_StoryEvents_State.mIndex, ppxe);
    if (level > limit) {
        *pTotal += ExpLevelGetLvbn(level);
    }
}

void StoryEventsRestoreOptions(void)
{
    if (_StoryEvents_SavedOptions.mSaved) {
        GameOptionsSet(14, _StoryEvents_SavedOptions.mValue14);
        GameOptionsSet(1, _StoryEvents_SavedOptions.mValue1);
        if (_StoryEvents_SavedOptions.mValue0 > -1) {
            GameOptionsSet(0, _StoryEvents_SavedOptions.mValue0);
        }
        _StoryEvents_SavedOptions.mSaved = 0;
    }
}

void StoryEventsOverrideOptions(int value14, int value1)
{
    if (!_StoryEvents_SavedOptions.mSaved) {
        _StoryEvents_SavedOptions.mSaved = 1;
        _StoryEvents_SavedOptions.mValue14 = GameOptionsGet(14);
        _StoryEvents_SavedOptions.mValue1 = GameOptionsGet(1);
        if (_StoryEvents_State.mUnknown1 > -1) {
            _StoryEvents_SavedOptions.mValue0 = GameOptionsGet(0);
        } else {
            _StoryEvents_SavedOptions.mValue0 = _StoryEvents_State.mUnknown1;
        }
    }
    GameOptionsSet(14, value14);
    GameOptionsSet(1, value1);
    if (_StoryEvents_State.mUnknown1 > -1) {
        GameOptionsSet(0, _StoryEvents_State.mUnknown1);
    }
}

float StoryEventsUpdateRatingScale(void)
{
    return _StoryEvents_fRatingScale = ExpLevelGetScft(_StoryEvents_State.mUnknown1C) * 0.001f;
}

void StoryEventsScalePlayers(int id, int *pList, int skip, unsigned int count, float scale)
{
    for (unsigned int i = 0; i < count; i++) {
        int value = pList[i];
        if (value != skip) {
            StoryEventsScalePlayerRatings(&_StoryEvents_PlayerCursor, value, scale);
        }
    }
}

int StoryEventsSetupFinalTeam(void)
{
    int ids[10];
    int list[14];
    QueryResult result;
    int digp = 0;
    // FAKEMATCH: dead initializer; count is set from the query result before its use
    unsigned int count = 0;
    unsigned int i;

    MemFill(list, sizeof(list), 0x7FFF, 4);
    QueryCursor cursor = {0, 0, -1, 0};
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    TDbCompilePerformOp(&result,
                "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x82 from 'YALP' where 'DIGT' = \x85 "
                "order by 'DIGP' desc\n",
                &cursor, &digp, 0x21);
    count = result.mUnknown0;
    for (i = 0; i < count; i++) {
        TDbCompilePerformOp(0, "fetch from \x8a\n", &cursor);
        ids[i] = digp;
    }
    if (cursor.mUnknown0) {
        TDbSQLDestroyCursor(&cursor);
    }
    TeamDbAutoPickPlayers(0x21, 0, list, 7, ids, 10);
    StoryEventsPlaceSpecialPlayers(_StoryEvents_pEvent, list);
    list[7] = 0x7FFF;
    StoryEventsSetLineup(0, list);
    DepthChartAutoFill(0, list, 4);
    TeamDbLoadSide(0x21, list, 0, 7);
    TeamDbSetPlayersTgti(0x21);
    return 0x21;
}

int StoryEventsCreateAwayTeam(int *pTeam, int *pCopy)
{
    int ids[21];
    int list[14];
    unsigned int count;
    int full;
    int team;
    int etnr;

    full = count = 0;
    if (_StoryEvents_pEvent->mItes == 1 && fn_801485D4()) {
        switch (fn_801486A0()) {
        case 1:
            full = 1;
        case 0:
        case 3:
            count = 3;
            break;
        case 4:
            count = 4;
            break;
        case 5:
        default:
            count = 7;
            break;
        }
    }
    char name[33] = {0};
    etnr = -1;
    if (_StoryEvents_pEvent->mItes == 2) {
        etnr = SstlGetEntryTag(_StoryEvents_pEvent->mNets, name, sizeof(name));
    }
    *pTeam = TeamDbCreate(6, etnr, name);
    team = TeamDbCreate(6, etnr, name);
    if (full) {
        int counts[7] = {0};
        counts[0] = 7;
        TeamDbCreatePlayers(*pTeam, _StoryEvents_aCreatePositions, counts, 7, ids, 21);
    } else {
        int counts[7] = {1, 1, 1, 1, 1, 1, 1};
        TeamDbCreatePlayers(*pTeam, _StoryEvents_aCreatePositions, counts, 7, ids, 21);
    }
    TeamDbAutoPickPlayers(0, 0, list, 7, ids, 21);
    StoryEventsPlaceSpecialPlayers(_StoryEvents_pEvent, list);
    StoryEventsScalePlayers(team, list, _StoryEvents_State.mUnknown2, 7, StoryEventsUpdateRatingScale());
    list[7] = 0x7FFF;
    StoryEventsSetLineup(0, list);
    DepthChartAutoFill(0, list, 4);
    TeamDbLoadSideWithCopies(team, list, 0, 7);
    TeamDbSetPlayersTgti(team);
    if (pCopy && count) {
        for (unsigned int i = 0; i < count; i++) {
            pCopy[i] = list[i];
        }
    }
    return team;
}

void StoryEventsCopyIds(int *pDest, int *pSource, int count)
{
    memcpy(pDest, pSource, count * 4);
}

void StoryEventsTeamSetupStub(int group, int *pIds, int count, Object_8008044C *pObject, int a)
{
}

int StoryEventsCreateHomeTeam(int *pTeam, int *pCopy, int *pCount)
{
    int ids[8];
    int ids2[22];
    int list[14];
    int count;
    int first = 0;
    int second = 0;
    int team;
    int i;

    if ((_StoryEvents_pEvent->mItes == 1 || _StoryEvents_pEvent->mItes == 2) && fn_801485D4()) {
        switch (fn_801486A0()) {
        case 1:
            second = 1;
            break;
        case 0:
            first = 1;
            break;
        case 2:
            break;
        }
    }
    team = StoryTeamLoadToStats(_StoryEvents_State.mIndex, 1, ids, &count);
    *pTeam = TeamDbCreate(6, -1, 0);
    if (count > 0) {
        for (i = 0; i < count; i++) {
            if (PlayerDbSeekId(_StoryEvents_pPlayerCursor, ids[i], 0)) {
                DbCursorSetInt(_StoryEvents_pPlayerCursor, 0x44494F50, ids[i]);
                DbCursorSetInt(_StoryEvents_pPlayerCursor, 0x44494754, *pTeam);
            }
        }
        int counts[7] = {1, 1, 1, 1, 1, 1, 1};
        TeamDbCreatePlayers(*pTeam, _StoryEvents_aCreatePositions, counts, 7, ids2, 21);
        TeamDbAutoPickPlayers(0, 0, list, 7, ids2, 21);
        _StoryEvents_State.mUnknown2 = ids[0];
        switch (fn_801486A0()) {
        case 0:
        case 1:
            StoryEventsScalePlayers(team, list, _StoryEvents_State.mUnknown2, 7, StoryEventsUpdateRatingScale());
            StoryEventsCopyIds(list, ids, 1);
            break;
        case 2:
        default:
            StoryEventsScalePlayers(team, list, _StoryEvents_State.mUnknown2, 7, 1.0f);
            StoryEventsCopyIds(list, ids, count);
            break;
        }
        list[7] = 0x7FFF;
        StoryEventsSetLineup(1, list);
        PlayerDbSeekId(_StoryEvents_pPlayerCursor, _StoryEvents_State.mUnknown2, 0);
        DepthChartAutoFillEx(1, list, 4, (unsigned char)count, PlayerDbGetPbpo(_StoryEvents_pPlayerCursor));
        StoryEventsTeamSetupStub(1, ids, count, _StoryEvents_pPlayerCursor, 0);
        TeamDbLoadSideWithCopies(team, list, 1, 7);
        TeamDbSetPlayersTgti(team);
        if (pCopy && pCount) {
            unsigned int copied = 0;
            if (first) {
                copied = 2;
            } else if (second) {
                copied = 3;
            }
            for (unsigned int k = 0; k < copied; k++) {
                pCopy[k] = list[k + 1];
            }
            *pCount = copied;
        }
        if (first || second) {
            PortDbSetControlledPlayer(PortDbGetSidePort(1), _StoryEvents_State.mUnknown2);
        }
    }
    return team;
}

void StoryEventsSetupTeams(void)
{
    int list[14];
    int count;
    int home;
    int away;
    int awayTeam;
    int homeTeam;

    DepthChartLoad(1);
    count = 0;
    MemFill(list, sizeof(list), 0x7FFF, 4);
    home = StoryEventsCreateHomeTeam(&homeTeam, list, &count);
    if (StoryEventsIsFinalEvent()) {
        away = StoryEventsSetupFinalTeam();
        awayTeam = away;
    } else {
        away = StoryEventsCreateAwayTeam(&awayTeam, &list[count]);
    }
    if (_StoryEvents_pEvent->mItes == 1 && fn_801486A0() != 15) {
        StoryEventsBuildEventTables(away, awayTeam, list);
    }
    _StoryEvents_Match.mAway = away;
    _StoryEvents_Match.mHome = home;
    _StoryEvents_Match.mUnknown8 = 0;
    DepthChartSave();
}

void StoryEventsSetupMatch(void)
{
    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }
    StoryEventsSetupTeams();
    AutoDepthSetRateCallback(0);
    AutoDepthSetSelectCallback(0);
    MsgStadiumStartGame(_StoryEvents_pEvent->mDive);
    TDbCompilePerformOp(0, "use 'EMAG' update 'YALP' set 'ITGT' = \x82 where 'DIOP' = \x82\n", 0x21, 0x1FF);
}

void StoryEventsStartEvent(void)
{
    int b = MsgMainMenuAssignPads();

    MsgPlayerSelectStart(-1, MsgMainMenuGetActivePad(), b);
    UserProfileSelect(_StoryEvents_State.mIndex, 1);
    GameInfoSet(2, 1);
    StoryEventsOverrideOptions(0, _StoryEvents_pEvent->mPes[1] >= 0 ? _StoryEvents_pEvent->mPes[1] : 2);
    SndgMusicWaitForStart(90);
    int ites = _StoryEvents_pEvent->mItes;
    switch (ites) {
    case 0:
        MsgTeamPickSetMode(0, 0);
        MsgTeamPickSetSources(4);
        _StoryEvents_Match.mAway = 0;
        _StoryEvents_Match.mHome = 1;
        _StoryEvents_Match.mUnknown8 = 0;
        break;
    case 1: {
        StoryEventsSetRewardPenalty(0);
        int type = _StoryEvents_pEvent->mPes[0];
        fn_801485B4();
        switch (type) {
        case 4:
            fn_801485EC(4);
            break;
        case 3:
            fn_801485EC(3);
            break;
        case 0:
            fn_801485EC(0);
            fn_8014F3DC(_StoryEvents_pEvent->mPes[3] * 60);
            break;
        case 5:
            fn_801485EC(5);
            break;
        case 1: {
            fn_801485EC(1);
            // FAKEMATCH: reused local; value holds mPes[2], then mPes[1], then mPes[3]
            int value = _StoryEvents_pEvent->mPes[2];
            lbl_8031BDD4.mUnknown40 = value == 1;
            value = _StoryEvents_pEvent->mPes[1];
            if (value < 0) {
                value = _StoryEvents_pEvent->mPes[3];
                if (value < 0) {
                    lbl_8031BDD4.mUnknown32 = 1;
                    lbl_8031BDD4.mUnknown36 = 0;
                } else {
                    lbl_8031BDD4.mUnknown32 = 0;
                    // FAKEMATCH: the product goes back into value; it sets the target's register choice
                    value *= 60;
                    lbl_8031BDD4.mUnknown36 = value;
                }
            } else {
                lbl_8031BDD4.mUnknown32 = value;
                lbl_8031BDD4.mUnknown36 = 0;
            }
            break;
        }
        case 2: {
            int enable = 1;
            fn_801485EC(2);
            // FAKEMATCH: reused local; the outer switch's type holds mPes[2], then mPes[3]
            type = _StoryEvents_pEvent->mPes[2];
            if (type == 2) {
                enable = 0;
            }
            fn_80148A58()->vfn_07(0, enable);
            type = _StoryEvents_pEvent->mPes[3];
            fn_80148A58()->vfn_07(1, type);
            break;
        }
        }
        StoryEventsSetupMatch();
        break;
    }
    case 2:
        if (_StoryEvents_pEvent->mPes[0] == 4) {
            fn_801485B4();
            fn_801485EC(4);
        }
        StoryEventsSetupMatch();
        break;
    case 3:
        StoryEventsSetupMatch();
        break;
    case 4:
        break;
    }
}

int StoryEventsGetEventScreen(void)
{
    int value = 100;

    switch (_StoryEvents_pEvent->mItes) {
    case 0:
        value = 109;
        break;
    case 1:
        value = 700;
        break;
    case 2:
        switch (_StoryEvents_pEvent->mPes[0]) {
        case 4:
            value = 700;
            break;
        case 7:
            value = 122;
            break;
        }
        break;
    case 3:
        value = 122;
        break;
    case 4:
        break;
    }
    return value;
}

void StoryEventsStoreLkss(void)
{
    int value = GameOptionsGet(0);

    StorySetLkss(_StoryEvents_State.mIndex, value);
    _StoryEvents_State.mUnknown1 = value;
}

void StoryEventsCompleteEvent(void)
{
    if (_StoryEvents_State.mUnknown1 < 0) {
        StoryEventsStoreLkss();
    }
    StoryAddCompletedEvent(_StoryEvents_State.mIndex, _StoryEvents_pEvent->mNets);
    int total = 0;
    // FAKEMATCH: dead initializer; base is set again before its use
    int base = 0;
    StoryEventsAwardExpPoints(&total);
    total += _StoryEvents_pEvent->mPdwr;
    if (_StoryEvents_pEvent->mItes == 1) {
        switch (_StoryEvents_pEvent->mPes[0]) {
        case 0:
            if (_StoryEvents_iRewardPenalty > 5) {
                _StoryEvents_iRewardPenalty = 0;
            }
            total = total * (5 - _StoryEvents_iRewardPenalty) / 5;
            break;
        case 1:
            if (_StoryEvents_iRewardPenalty > 3) {
                _StoryEvents_iRewardPenalty = 0;
            }
            total = total * (3 - _StoryEvents_iRewardPenalty) / 3;
            break;
        }
    }
    _StoryEvents_State.mUnknown14 = total;
    total += _StoryEvents_State.mUnknownC;
    StorySetDevPoints(_StoryEvents_State.mIndex, total);
    base = _StoryEvents_State.mUnknown8;
    int credits = _StoryEvents_pEvent->mCswr;
    _StoryEvents_State.mUnknown18 = credits;
    UserStatsSet(_StoryEvents_pUserStats, 14, base + credits);
    UserInfoAddPoints(DbUserGetId(_StoryEvents_State.mIndex), _StoryEvents_pEvent->mCswr);
    _StoryEvents_Progress.mDone[_StoryEvents_pEvent->mDive] = StoryAreGroupEventsCompleted(_StoryEvents_State.mIndex, _StoryEvents_pEvent->mDive);
    StoryEventsReadProgress();
}

int StoryEventsGetEventInfo(int dive, int droe, int *pLevel, int *pDone, int *pLocked, int count, char *pName, int size)
{
    StevRow_t row;
    StevRow_t first;
    int ites = 5;

    *pLevel = 0;
    *pLocked = 0;
    *pDone = 0;
    if (pName) {
        *pName = 0;
    }
    if (StevGetRow(dive, droe, &row)) {
        ites = row.mItes;
        if (pName) {
            strncpy(pName, row.mIuve, size);
        }
        *pLevel = ExpLevelGetForPoints(row.mQrxe);
        if (StoryIsEventCompleted(_StoryEvents_State.mIndex, row.mNets)) {
            *pDone = 1;
        } else if (row.mItes == 4) {
            StevGetRow(0, 0, &first);
            *pLocked = !StoryIsEventCompleted(_StoryEvents_State.mIndex, first.mNets);
        } else if (_StoryEvents_State.mPpxe < row.mQrxe) {
            *pLocked = 1;
        }
        if (count > 2) {
            if (droe == 0) {
                _StoryEvents_bLocalSlotFree = 1;
                _StoryEvents_bEarlierDone = 1;
            }
            if (row.mItes != 2) {
                if (*pDone == 0) {
                    _StoryEvents_bEarlierDone = 0;
                }
            } else if (_StoryEvents_bEarlierDone) {
                if (*pDone == 0) {
                    if (_StoryEvents_bLocalSlotFree) {
                        *pLocked = 0;
                        _StoryEvents_bLocalSlotFree = 0;
                    } else {
                        *pLocked = 1;
                    }
                }
            } else {
                *pLocked = 1;
            }
        }
    }
    return ites;
}

int StoryEventsFindOpenDive(int all)
{
    int found = 12;
    int dive;

    for (dive = 0; dive <= 11; dive++) {
        int count = all ? StevCountDiveRows(dive) : 1;
        for (int droe = 0; droe < count; droe++) {
            int level;
            int done;
            int locked;
            int ites = StoryEventsGetEventInfo(dive, droe, &level, &done, &locked, count, 0, 0);
            if (ites == 4 || ites == 5) {
                continue;
            }
            if (!done && !locked) {
                found = dive;
                break;
            }
        }
        if (found != 12) {
            break;
        }
    }
    return found;
}

int StoryEventsIsDiveDone(int dive)
{
    int done = 0;

    if (_StoryEvents_Progress.mDone[dive]) {
        done = 1;
    }
    return done;
}

int StoryEventsIsDiveFinished(int dive)
{
    int complete = 1;
    int count = StevCountDiveRows(dive);

    for (int droe = 0; droe < count; droe++) {
        int level;
        int done;
        int locked;
        StoryEventsGetEventInfo(dive, droe, &level, &done, &locked, count, 0, 0);
        if (!done && !locked) {
            complete = 0;
            break;
        }
    }
    return complete;
}

void StoryEventsBuildRewardText(void)
{
    char hero[40];
    // FAKEMATCH: local that only aliases the global buffer _StoryEvents_szRewardText
    char *pText = _StoryEvents_szRewardText;
    const char *pName;
    int completed;
    int length;

    pText[0] = 0;
    pName = "Story task";
    completed = 0;
    switch (_StoryEvents_pEvent->mItes) {
    case 0:
        pName = "a Pickup Game";
        break;
    case 1:
        switch (_StoryEvents_pEvent->mPes[0]) {
        case 4:
            pName = "a 4 on 4 Street Event";
            break;
        case 3:
            pName = "a 2 Minute Challenge Street Event";
            break;
        case 0:
            pName = "a Crush the Carrier Street Event";
            break;
        case 5:
            pName = "a Quick Strike Street Event";
            break;
        case 1:
            pName = "a \nJump Ball Battle Street Event";
            break;
        case 2:
            pName = "an Open Field Showdown Street Event";
            break;
        }
        break;
    case 2:
        pName = "a Local Game";
        break;
    case 3:
        pName = "an Exhibition Game";
        break;
    }
    switch (_StoryEvents_State.mUnknown20) {
    case 1:
    case 2:
        fn_801C2E18(pText, "You have completed %s!", pName);
        completed = 1;
        break;
    // FAKEMATCH: empty case for a result value nothing stores; it sets the target's range-test order
    case 3:
        break;
    }
    length = strlen(pText);
    if (completed && (_StoryEvents_State.mUnknown14 || _StoryEvents_State.mUnknown18)) {
        fn_801C2E18(pText + length, "\nYou are rewarded");
        length = strlen(pText);
        if (_StoryEvents_State.mUnknown14) {
            fn_801C2E18(pText + length, "\n%d Dev Points", _StoryEvents_State.mUnknown14);
            length = strlen(pText);
        }
        if (_StoryEvents_State.mUnknown18) {
            fn_801C2E18(pText + length, "\n%d Credits", _StoryEvents_State.mUnknown18);
            length = strlen(pText);
        }
    }
    if (StoryEventsIsDiveDone(_StoryEvents_pEvent->mDive)) {
        int dive = StoryEventsFindOpenDive(0);
        if (dive != 12) {
            EnvSelect(dive);
            EnvGetUIName(hero, 33);
            EnvRelease();
            length = strlen(pText);
        }
    }
}

void StoryEventsEnterScreen(int *pState, int *pScreen)
{
    StevRow_t first;
    unsigned short count;
    int played;
    int dive;

    if (StoryTournamentGetEvent()) {
        StoryTournamentClearEvent();
    }
    if (_StoryEvents_bActive) {
        return;
    }
    StoryEventsSyncDatabases();
    StoryEventsOpen();
    StoryEventsLoadTeamLogo(1);
    if (StoryEventsIsNewStory()) {
        StorySetNew(_StoryEvents_State.mIndex, 0);
    }
    played = 0;
    _StoryEvents_bStpyFull = 0;
    if (_StoryEvents_pEvent) {
        played = _StoryEvents_Match.mUnknown8 == 1;
    }
    StoryEventsRestoreOptions();
    StoryEventsReadProgress();
    if (StoryEventsUpdateCompletion()) {
        *pState = 3;
        *pScreen = StoryEventsGetDiveSlot(0);
    } else {
        dive = StoryEventsFindOpenDive(1);
        if (dive == 12) {
            *pState = 1;
            *pScreen = StoryEventsGetDiveSlot(0);
        } else {
            *pState = _StoryEvents_iResumeState;
            if (_StoryEvents_iResumeScreen == -1) {
                *pScreen = StoryEventsGetDiveSlot(dive);
            } else {
                *pScreen = _StoryEvents_iResumeScreen;
            }
        }
        if (played) {
            StoryEventsCompleteEvent();
            StevGetRow(0, 0, &first);
            if (_StoryEvents_pEvent->mNets == first.mNets) {
                _StoryEvents_bFirstEventDone = 1;
            }
            if (_StoryEvents_pEvent->mItes == 0 || _StoryEvents_pEvent->mItes == 1) {
                _StoryEvents_State.mUnknown20 = 2;
                count = 0;
                TDbTblGetCount(DbUserGetDb(DbUserGetId(_StoryEvents_State.mIndex)), 0x59505453, 0, &count);
                if (count == 4) {
                    _StoryEvents_bStpyFull = 1;
                }
            } else {
                _StoryEvents_State.mUnknown20 = 1;
            }
            dive = StoryEventsFindOpenDive(1);
            if (dive != _StoryEvents_pEvent->mDive && StoryEventsIsDiveDone(_StoryEvents_pEvent->mDive)) {
                // FAKEMATCH: the *pState = 2 store is repeated in both arms instead of once before the test
                if (dive == 12) {
                    *pState = 2;
                    *pScreen = StoryEventsGetDiveSlot(0);
                } else {
                    *pState = 2;
                    *pScreen = StoryEventsGetDiveSlot(dive);
                }
            } else {
                *pState = 3;
                // FAKEMATCH: goto shares the screen store below; it sets the target's register choice
                goto current;
            }
        } else if (_StoryEvents_pEvent) {
            *pState = 3;
        current:
            *pScreen = StoryEventsGetDiveSlot(_StoryEvents_pEvent->mDive);
        }
    }
    if (StoryEventsUpdateCompletion() && played) {
        _StoryEvents_State.mUnknown20 = 0;
    }
    if (_StoryEvents_State.mUnknown20) {
        StoryEventsBuildRewardText();
    }
    _StoryEvents_pEvent = 0;
    _StoryEvents_bActive = 1;
    _StoryEvents_fRatingScale = StoryEventsGetRatingScale();
    FELoopResetIdle();
}

void StoryEventsLeaveScreen(int state, int screen)
{
    if (_StoryEvents_bActive) {
        StoryEventsLoadTeamLogo(0);
        if (MsgGameGetSetupState() == 0) {
            StoryEventsSyncDatabases();
        } else if (MsgGameGetSetupState() == 1 && _StoryEvents_pEvent) {
            FELoopSetResume(1);
            StoryEventsStartEvent();
        }
        StoryEventsClose();
        _StoryEvents_State.mUnknown20 = 0;
        _StoryEvents_bActive = 0;
    }
    if (MsgGameGetSetupState() == 0) {
        _StoryEvents_iResumeState = 2;
        _StoryEvents_iResumeScreen = 4;
    } else {
        _StoryEvents_iResumeState = state;
        _StoryEvents_iResumeScreen = screen;
    }
    InGameRewardSetAlt(0);
}

void StoryEventsGetDiveEventCount(int dive, int *pCount)
{
    *pCount = StevCountDiveRows(dive);
    if (dive == 0 && !StoryEventsIsAllComplete()) {
        (*pCount)--;
    }
}

int StoryEventsSelectEvent(int dive, int droe)
{
    int value = 100;

    if (StevGetRow(dive, droe, &_StoryEvents_EventRow)) {
        _StoryEvents_pEvent = &_StoryEvents_EventRow;
        value = StoryEventsGetEventScreen();
    }
    return value;
}

void StoryEventsStartFirstEvent(void)
{
    StevRow_t row;
    int dive;

    MsgMainMenuGoTo(7);
    StoryEventsOpen();
    StoryEventsReadProgress();
    for (dive = 0;; dive++) {
        if (dive <= 11) {
            StevGetRow(dive, 0, &row);
            if (row.mQrxe != 0) {
                continue;
            }
        } else {
            dive = 5;
        }
        break;
    }
    StoryEventsSelectEvent(dive, 0);
    FELoopSetResume(1);
    StoryEventsStartEvent();
    StoryEventsClose();
}

void StoryEventsHandleAction(int id)
{
    switch (id) {
    case 0:
        break;
    case 113:
        EditMenuBegin(4, 0x3FF);
        break;
    case 900:
        EditMenuBegin(2, 0x3FF);
        break;
    case 603:
        StoryTournamentBegin();
    case 109:
        MsgTeamPickRequestTeamSave();
        break;
    }
}

int StoryEventsShowReward(int screen)
{
    int shown = 0;

    if (_StoryEvents_State.mUnknown20 && screen == 5) {
        shown = 1;
        InGameRewardSetAlt(1);
    }
    return shown;
}

int StoryEventsGetTeamLogo(int *pResult)
{
    int value = 0;

    *pResult = TeamLogoGetHandle(-1);
    DbCursor cursor;
    StoryTeamCursorOpen(&cursor, _StoryEvents_State.mIndex);
    if (DbCursorGetRowCount(&cursor) > 0) {
        value = StoryTeamGetLogo(&cursor);
        if (DbCursorGetInt(&cursor, 0x4C445443) == 0) {
            unsigned char color[3];
            color[0] = DbCursorGetInt(&cursor, 0x31434D54);
            color[1] = DbCursorGetInt(&cursor, 0x32434D54);
            color[2] = DbCursorGetInt(&cursor, 0x33434D54);
            TeamLogoRequestTint(0, 4, value, 0xAC, color);
            *pResult = TeamLogoGetHandle(0);
        }
    }
    StoryTeamCursorClose(&cursor);
    return value;
}

/* Compiled-out assert of the release build. */
#define STORY_ASSERT(e) do { } while (0)

void StoryEventsGetHeroName(char *pName, int size)
{
    unsigned int last = size - 1;
    *pName = 0;
    DbCursor cursor;
    char buffer[64];
    unsigned int length;

    StoryPlayerCursorOpen(&cursor, _StoryEvents_State.mIndex);
    buffer[0] = 0;
    if (!StoryPlayerGetLastName(&cursor, 0, buffer, sizeof(buffer))) {
        *pName = 0;
    }
    // FAKEMATCH: compiled-out bounds assert; its empty do-while keeps the zero store of the branch on the call result
    STORY_ASSERT(last < sizeof(buffer));
    buffer[last] = 0;
    length = strlen(buffer);
    buffer[0] = 0;
    if (!StoryPlayerGetFirstName(&cursor, 0, buffer, sizeof(buffer))) {
        *pName = 0;
    } else {
        buffer[last] = 0;
        unsigned int first = strlen(buffer);
        length += first;
        length++;
        if (length < last - 1) {
            buffer[first] = ' ';
            first++;
            StoryPlayerGetLastName(&cursor, 0, buffer + first, sizeof(buffer) - first);
            buffer[length] = 0;
        }
    }
    if (*pName == 0) {
        StoryPlayerGetShortName(&cursor, 0, pName, last);
        if (*pName == 0) {
            strncpy(pName, "your hero", last);
            goto done;
        }
    }
    strncpy(pName, buffer, last);
done:
    pName[last] = 0;
    StoryPlayerCursorClose(&cursor);
}

void StoryEventsGetTeamName(char *pName, int size)
{
    *pName = 0;
    int last = size - 1;
    DbCursor cursor;

    StoryTeamCursorOpen(&cursor, _StoryEvents_State.mIndex);
    if (DbCursorGetRowCount(&cursor) > 0) {
        DbCursorSeek(&cursor, 0);
        DbCursorGetString(&cursor, 0x414E4454, (int)pName, last);
    }
    StoryTeamCursorClose(&cursor);
}

void StoryEventsPlaceInSlot(int *pList, int id, int slot)
{
    if (slot > 6) {
        return;
    }
    int previous = pList[slot];
    pList[slot] = id;
    for (int i = 0; i < 7; i++) {
        if (i != slot && pList[i] == id) {
            pList[i] = previous;
        }
    }
}

float StoryEventsGetRatingScale(void)
{
    float scale;

    if (_StoryEvents_bActive) {
        scale = ExpLevelGetScft(_StoryEvents_State.mUnknown1C) * 0.001f;
        _StoryEvents_fRatingScale = scale;
    } else {
        scale = _StoryEvents_fRatingScale;
    }
    return scale;
}

void StoryEventsScalePlayerRatings(Object_8008044C *pObject, int id, float scale)
{
    int found = PlayerDbSeekId(pObject, id, 0);
    int type = PlayerDbGetPrty(pObject);

    if ((type == 1 || type == 2) && found) {
        for (int i = 0; i < 10; i++) {
            unsigned int value = PlayerDbGetRating(pObject, _StoryEvents_aScaledRatings[i]);
            value -= (int)(value * scale);
            if (value > 100) {
                value = 100;
            }
            value = value < 5 ? 5 : value;
            PlayerDbSetRating(pObject, _StoryEvents_aScaledRatings[i], value);
        }
    }
}

void StoryEventsCopyRewardText(StoryTextArgs_t *pArgs)
{
    StoryTextBuffer_t *pDest = pArgs->mpText;
    char *pText = pDest->mpText;
    int size = pDest->mSize;

    *pText = 0;
    strncpy(pText, _StoryEvents_szRewardText, size);
}

void StoryEventsClearResult(void)
{
    _StoryEvents_State.mUnknown20 = 0;
}

void StoryEventsGetHomeTeam(int *pHome)
{
    *pHome = _StoryEvents_Match.mHome;
}

int StoryEventsIsNewStory(void)
{
    return StoryIsNew(DbUserFindIndex(DbUserGetCurrent()));
}

int StoryEventsHandleMessage(unsigned int id, int *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        StoryEventsEnterScreen((int *)pArgs[0], (int *)pArgs[1]);
        break;
    case 0x80000002:
        StoryEventsLeaveScreen(pArgs[0], pArgs[1]);
        break;
    case 0x80000003: {
        int *pCount = (int *)pArgs[1];
        int dive = StoryEventsGetSlotDive(pArgs[0]);
        if (dive == 12) {
            *pCount = 0;
        } else {
            StoryEventsGetDiveEventCount(dive, pCount);
        }
        break;
    }
    case 0x80000004: {
        int dive = StoryEventsGetSlotDive(pArgs[0]);
        int droe = pArgs[1];
        int *pLevel = (int *)pArgs[2];
        int *pDone = (int *)pArgs[4];
        int *pLocked = (int *)pArgs[5];
        if (dive == 12) {
            *pLevel = 0;
            *pDone = 1;
            *pLocked = 1;
        } else {
            int count = StevCountDiveRows(dive);
            StoryTextBuffer_t *pText = (StoryTextBuffer_t *)pArgs[3];
            StoryEventsGetEventInfo(dive, droe, pLevel, pDone, pLocked, count, pText->mpText, pText->mSize);
        }
        break;
    }
    case 0x80000005: {
        int dive = StoryEventsGetSlotDive(pArgs[0]);
        if (dive == 12) {
            *pResult = 1;
        } else {
            *pResult = StoryEventsIsDiveDone(dive);
        }
        break;
    }
    case 0x80000006: {
        int dive = StoryEventsGetSlotDive(pArgs[0]);
        if (dive == 12) {
            *pResult = 100;
        } else {
            *pResult = StoryEventsSelectEvent(dive, pArgs[1]);
        }
        break;
    }
    case 0x8000000C:
        *pResult = _StoryEvents_bStpyFull;
        break;
    case 0x182: {
        int found = ExpLevelGetName(_StoryEvents_State.mUnknown1C, ((StoryTextBuffer_t *)pArgs[0])->mpText,
                                    ((StoryTextBuffer_t *)pArgs[0])->mSize);
        *pResult = _StoryEvents_State.mUnknown1C;
        if (!found) {
            strncpy(((StoryTextBuffer_t *)pArgs[0])->mpText, "", ((StoryTextBuffer_t *)pArgs[0])->mSize);
        }
        break;
    }
    case 0x80000007:
        StoryEventsHandleAction(pArgs[0]);
        break;
    case 0x11A:
        StoryEventsHandleAction(113);
        break;
    case 0x80000008:
        *pResult = StoryEventsShowReward(pArgs[0]);
        break;
    case 0x80000009:
        if (StoryEventsIsFinalEvent()) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x8000000A:
        if (_StoryEvents_bFirstEventDone) {
            *pResult = 1;
            _StoryEvents_bFirstEventDone = 0;
        } else {
            *pResult = 0;
        }
        break;
    case 0x17B:
    {
        int *pLogo = (int *)pArgs[0];
        *pResult = *pLogo = StoryEventsGetTeamLogo((int *)pArgs[1]);
        break;
    }
    case 0x16E: {
        StoryTextBuffer_t *pText = (StoryTextBuffer_t *)pArgs[0];
        StoryEventsGetHeroName(pText->mpText, pText->mSize);
        break;
    }
    case 0x146: {
        StoryTextBuffer_t *pText = (StoryTextBuffer_t *)pArgs[0];
        StoryEventsGetTeamName(pText->mpText, pText->mSize);
        break;
    }
    case 0x8000000B: {
        int dive = StoryEventsGetSlotDive(pArgs[0]);
        if (dive == 12) {
            *pResult = 1;
        } else {
            *pResult = StoryEventsIsDiveFinished(dive);
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}

StevRow_t *StoryEventsGetCurrentEvent(void)
{
    return _StoryEvents_pEvent;
}

int StoryEventsRecordGameResult(void)
{
    int active;

    if (!_StoryEvents_pEvent) {
        active = 0;
    } else {
        int result = fn_80178AE0();
        active = 1;
        switch (result) {
        case 0:
            _StoryEvents_Match.mUnknown8 = 2;
            break;
        case 1:
            _StoryEvents_Match.mUnknown8 = 1;
            break;
        default:
            _StoryEvents_Match.mUnknown8 = 3;
            break;
        }
    }
    return active;
}

void StoryEventsBuildPickupTables(int *pFirst, int *pSecond)
{
    int ids[13];
    int itgt[13];
    int count;
    int i;
    unsigned char secondSide;
    unsigned char firstSide;

    int n = 0;
    for (i = 1; i <= 6; i++) {
        ids[n++] = pSecond[i];
    }
    for (i = 0; i < 7; i++) {
        ids[n++] = pFirst[i];
    }
    {
        Object_8008044C object;
        int found = 0;
        PlayerCursorOpen(&object, 0, 0x54415453);
        for (i = 0; i <= 12; i++) {
            if (PlayerDbSeekId(&object, ids[i], 0)) {
                itgt[found++] = DbCursorGetInt(&object, 0x49544754);
            }
        }
        fn_8008056C(&object);
    }
    if (_StoryEvents_iPlayerTable != -1) {
        TDbTblDestroy(0x54415453, _StoryEvents_iPlayerTable);
        _StoryEvents_iPlayerTable = -1;
    }
    TDbTblFindUnusedId(0x54415453, &_StoryEvents_iPlayerTable);
    TDbCompilePerformOp(0, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable,
                ids[0], ids[1], ids[2], ids[3], ids[4], ids[5], ids[6], ids[7], ids[8], ids[9], ids[10], ids[11], ids[12]);
    TDbCompilePerformOp(0, "use 'TATS' select count(*) into \x82 from \x8c\n", &count, _StoryEvents_iPlayerTable);
    {
        DbCursor cursor;
        if (GameInfoGet(2) == 0) {
            secondSide = 1;
            firstSide = 0;
        } else {
            secondSide = 0;
            firstSide = 1;
        }
        DbCursorOpen(&cursor, _StoryEvents_iPlayerTable, 0x44494750, 0, 0, 0x54415453);
        for (i = 1; i <= 6; i++) {
            if (PlayerDbSeekId((Object_8008044C *)&cursor, pSecond[i], 0)) {
                fn_80081F50((Object_8008044C *)&cursor, secondSide, 1);
            }
        }
        for (i = 0; i <= 6; i++) {
            if (PlayerDbSeekId((Object_8008044C *)&cursor, pFirst[i], 0)) {
                fn_80081F50((Object_8008044C *)&cursor, firstSide, 1);
            }
        }
        DbCursorClose(&cursor);
    }
    if (_StoryEvents_iTeamTable != -1) {
        TDbTblDestroy(0x54415453, _StoryEvents_iTeamTable);
        _StoryEvents_iTeamTable = -1;
    }
    TDbTblFindUnusedId(0x54415453, &_StoryEvents_iTeamTable);
    TDbCompilePerformOp(0, "use 'TATS' select into 'TATS'.\x8c * from 'MAET' where ('DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85)\n", _StoryEvents_iTeamTable,
                itgt[0], itgt[1], itgt[2], itgt[3], itgt[4], itgt[5], itgt[6], itgt[7], itgt[8], itgt[9], itgt[10], itgt[11],
                itgt[12]);
    TDbCompilePerformOp(0, "use 'TATS' select count(*) into \x82 from \x8c\n", &count, _StoryEvents_iTeamTable);
}

void StoryEventsBuildEventTables(int team, int id, int *pList)
{
    QueryResult result;

    if (_StoryEvents_iPlayerTable != -1) {
        TDbTblDestroy(0x54415453, _StoryEvents_iPlayerTable);
        _StoryEvents_iPlayerTable = -1;
    }
    TDbTblFindUnusedId(0x54415453, &_StoryEvents_iPlayerTable);
    switch (fn_801486A0()) {
    case 1:
        TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0], pList[1], pList[2],
                    pList[3], pList[4], pList[5]);
        break;
    case 0:
        TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0], pList[1], pList[2],
                    pList[3], pList[4]);
        break;
    case 3:
        TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0], pList[1], pList[2]);
        break;
    case 2:
        if (_StoryEvents_pEvent->mPes[2] == 2) {
            TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0], pList[1]);
        } else {
            TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0]);
        }
        break;
    case 4:
        TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0], pList[1], pList[2],
                    pList[3]);
        break;
    case 5:
    default:
        TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", _StoryEvents_iPlayerTable, pList[0], pList[1], pList[2],
                    pList[3], pList[4], pList[5], pList[6]);
        break;
    }
    if (_StoryEvents_iTeamTable != -1) {
        TDbTblDestroy(0x54415453, _StoryEvents_iTeamTable);
        _StoryEvents_iTeamTable = -1;
    }
    TDbTblFindUnusedId(0x54415453, &_StoryEvents_iTeamTable);
    TDbCompilePerformOp(&result, "use 'TATS' select into 'TATS'.\x8c * from 'MAET' where 'DIGT' = \x85 or 'DIGT' = \x85\n",
                _StoryEvents_iTeamTable, team, id);
}

void StoryEventsFreeTables(void)
{
    if (_StoryEvents_iPlayerTable != -1) {
        TDbTblDestroy(0x54415453, _StoryEvents_iPlayerTable);
        _StoryEvents_iPlayerTable = -1;
    }
    if (_StoryEvents_iTeamTable != -1) {
        TDbTblDestroy(0x54415453, _StoryEvents_iTeamTable);
        _StoryEvents_iTeamTable = -1;
    }
}

int StoryEventsGetPlayerTable(void)
{
    return _StoryEvents_iPlayerTable;
}

int StoryEventsGetTeamTable(void)
{
    return _StoryEvents_iTeamTable;
}

int StoryEventsIsWonPickupEvent(void)
{
    StevRow_t *pRow = _StoryEvents_pEvent;

    if (pRow && (pRow->mItes == 0 || (pRow->mItes == 1 && pRow->mQrxe != 0)) && _StoryEvents_Match.mUnknown8 == 1) {
        return 1;
    }
    return 0;
}

void StoryEventsCallTeamSetupStub(int group, int *pIds, int count, Object_8008044C *pObject)
{
    StoryEventsTeamSetupStub(group, pIds, count, pObject, 0);
}

int StoryEventsPlaceSpecialPlayers(StevRow_t *pRow, int *pList)
{
    int set = 0;
    int type = pRow->mCsis;

    if (type == -1) {
        type = pRow->mCsos;
    }
    if (type != -1) {
        switch (type) {
        case 0:
        case 1:
            StoryEventsPlaceInSlot(pList, 0x1FF, 1);
            set = 1;
            break;
        case 2:
        case 3:
            StoryEventsPlaceInSlot(pList, 0x1FF, 0);
            StoryEventsPlaceInSlot(pList, 0x1FB, 1);
            set = 2;
            break;
        case 4:
            StoryEventsPlaceInSlot(pList, 0x1F8, 1);
            set = 1;
            break;
        }
    }
    return set;
}

void StoryEventsSetLineup(int index, int *pList)
{
    for (int i = 0; i < 7; i++) {
        _StoryEvents_aaLineup[index][i] = pList[i];
    }
}

int *StoryEventsGetLineup(int index)
{
    return _StoryEvents_aaLineup[index];
}

void StoryEventsCheatSetLevel(int index, int level)
{
    int ppxe[4] = {16, 39, 63, 72};
    StevRow_t row;
    unsigned int mask = 0;
    StevRow_t *pSaved;
    int dive;

    switch (level) {
    case 3:
        mask = 8;
    case 2:
        mask |= 0x16;
    case 1:
        mask |= 0x340;
    case 0:
        mask |= 0xA0;
        StorySetExpPoints(index, ppxe[level]);
        break;
    }
    StevOpen();
    pSaved = _StoryEvents_pEvent;
    for (dive = 0; dive <= 11; dive++) {
        if (mask & (1 << dive)) {
            _StoryEvents_pEvent = &row;
            int count = StevCountDiveRows(dive);
            for (int droe = 0; droe < count; droe++) {
                StevGetRow(dive, droe, &row);
                if (!StoryIsEventCompleted(index, row.mNets)) {
                    StoryAddCompletedEvent(index, row.mNets);
                }
            }
        }
    }
    StorySetNew(index, 0);
    StevClose();
    _StoryEvents_pEvent = pSaved;
}

void StoryEventsCheatCompleteAll(int index)
{
    StevRow_t row;
    StevRow_t *pSaved;
    int dive;

    StevOpen();
    pSaved = _StoryEvents_pEvent;
    for (dive = 0; dive <= 11; dive++) {
        _StoryEvents_pEvent = &row;
        int count = StevCountDiveRows(dive);
        for (int droe = 0; droe < count; droe++) {
            if (dive == 0 && droe == count - 1) {
                continue;
            }
            StevGetRow(dive, droe, &row);
            if (!StoryIsEventCompleted(index, row.mNets)) {
                StoryAddCompletedEvent(index, row.mNets);
            }
        }
    }
    StorySetNew(index, 0);
    StevClose();
    _StoryEvents_pEvent = pSaved;
}

void StoryEventsReset(int index)
{
    StoryClearCompletedEvents(index);
    StorySetExpPoints(index, 0);
    StoryClearFlags(index);
    StorySetNew(index, 1);
    StorySetLkss(index, -1);
}

Object_80039F5C *StoryEventsFindLineupPlayer(int type, int position)
{
    Object_80039F5C *pResult = 0;
    Object_80039F5C *pObject = 0;
    int *pList = 0;
    int id = 0;

    switch (type) {
    case 0:
    case 1:
    case 2:
        pList = StoryEventsGetLineup(0);
        switch (position) {
        case 0:
            id = pList[1];
            break;
        case 3:
            id = pList[0];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        pList = StoryEventsGetLineup(0);
        switch (position) {
        case 0:
            id = pList[1];
            break;
        case 2:
            id = pList[0];
            break;
        case 4:
            id = pList[2];
            break;
        case 5:
            id = pList[3];
            break;
        case 6:
            id = pList[4];
            break;
        case 7:
        case 8:
            id = pList[5];
            break;
        case 3:
        case 9:
            id = pList[6];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 8:
        pList = StoryEventsGetLineup(0);
        switch (position) {
        case 0:
            id = pList[0];
            break;
        case 2:
            id = pList[1];
            break;
        case 3:
            id = pList[2];
            break;
        case 4:
            id = pList[3];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 9:
    case 10:
    case 11:
        pList = StoryEventsGetLineup(0);
        switch (position) {
        case 0:
            id = pList[0];
            break;
        case 1:
            id = pList[1];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 12:
        if (position == 1) {
            pList = StoryEventsGetLineup(0);
            id = pList[1];
        }
        break;
    }
    if (pList) {
        pObject = PlyrFindByPoid(id);
    }
    if (pObject) {
        pResult = pObject;
    }
    return pResult;
}

void StoryEventsSetRewardPenalty(int value)
{
    _StoryEvents_iRewardPenalty = value;
}
}
