/* The story-mode tournament event: an eight-team knockout bracket played with drafted teams. Draws the
   bracket, sets up and starts the player's game with the story player on his team, records the result and
   plays out the other games, and answers the bracket screen's messages. */

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/EditMenu.h"
#include "game/DepthChart.h"
#include "game/StevTable.h"
#include "game/StoryTournament.h"
#include "game/StoryTeam.h"
#include "game/GameOptions.h"
#include "game/TDbCompilePerformOp.h"
#include "game/FELoop.h"

/* Teams and round of the current match, set by StoryTournamentSetupMatch. */
struct StoryTournamentMatch_t {
    int mDit1;
    int mDit2;
    int mLvlt;
};

/* Values saved by StoryTournamentSetOptions and restored by StoryTournamentRestoreOptions. */
struct StoryTournamentOptions_t {
    int mValue0;
    int mValue1;
    int mValue14;
    unsigned char mSaved;
};

/* Index returned by DbUserFindIndex, and whether StoryTournamentOpenDbs opened the 'PDFN'
   database; while it is open, queries skip their own open and close. */
struct StoryTournamentState_t {
    signed char mIndex;
    signed char mUnknown1;
    short mUnknown2;
    short mOpen;
};

struct StoryTournamentArgs_t {
    int *mpGame;
    int *mpDit2;
    int *mpDit1;
    MenuText_t *mpName2;
    MenuText_t *mpName1;
    int *mpUnknown20;
    int *mpUnknown24;
    int *mpWinner;
};

extern "C" {
int MsgMainMenuGetActivePad(void);
int MsgMainMenuAssignPads(void);
void MsgMainMenuGoTo(int a);
void MsgPlayerSelectStart(int a, int b, int c);
void MsgStadiumStartGame(int a);
void MsgTeamPickSetMode(int a, int b);
void MsgTeamPickSetSources(int a);
void InGameRewardSetAlt(unsigned char value);
int StoryEventsPlaceSpecialPlayers(StevRow_t *pRow, int *pList);
void StoryEventsSetLineup(int index, int *pList);
void GameInfoSet(int index, int value);
void TeamDbLoadSideWithCopies(int a, int *pList, int b, int c);
int FormationGetByIndex(int a, int b);
int *FormationLineupFetchUser(int a, int b);
int FormationLineupFillTeam(int a, int *pList);
int ExpLevelClose(void);
int ExpLevelOpen(void);
int TournamentSetPlayersTeam(int *pDigp, int count, int munt, int digt);
int TournamentGetTeamPlayers(int digt, int *pList);
int TournamentClearPlayers(void);
int TournamentGetLevelMatchCount(int lvlt);
int TournamentGetMatch(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw);
int TournamentSetMatchWinner(int lvlt, int dit1, int dit2, int tniw);
int TournamentClearMatches(void);
int TournamentGetMatchCount(void);
int TournamentGetTeamList(int *pList);
int TournamentGetRoundCount(int size);
int TournamentClose(void);
int TournamentOpen(int index);
void UserStatsOpen(DbCursor *pObject, int index);
void UserStatsClose(DbCursor *pObject);
int fn_80178AE0(void);
int MsgGameGetSetupState(void);
void UserProfileSelect(signed char a, int b);
void fn_8018C48C(int tag);
int StoryGetLkss(int a);
char *strncpy(char *pDest, const char *pSource, int count);
int DbUtilRandomRange(unsigned int low, unsigned int high);
int DbUserGetId(int index);
int DbUserFindIndex(int a);
int DbUserGetDb(int a);
int DbUserGetCurrent(void);
}

Object_8008044C _StoryTournament_PlayerDb;
DbCursor _StoryTournament_UserStats;
DbCursor _StoryTournament_TeamCursor;
StevRow_t _StoryTournament_EventRow;
StoryTournamentMatch_t _StoryTournament_Match;

static unsigned char _StoryTournament_bEntered = 0;
static StevRow_t *_StoryTournament_pEvent = 0;
static Object_8008044C *_StoryTournament_pPlayerDb = 0;
static DbCursor *_StoryTournament_pUserStats = 0;
static StoryTournamentState_t _StoryTournament_State = {0, -1, 0, 0};

static StoryTournamentOptions_t _StoryTournament_SavedOptions = {-1, 0, 0, 0};

/* Round ('LVLT') and row of each of the 15 bracket games. */
static int _StoryTournament_aiGameLevel[15] = {1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
static int _StoryTournament_aiGameRow[15] = {0, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7};

extern "C" {
void StoryTournamentGetTeamName(int id, char *pName, int size);
int StoryTournamentFindNextRow(int team, int lvlt);
void StoryTournamentCloseDbs(void);
void StoryTournamentOpenDbs(void);
void StoryTournamentFetchSkill(void);
void StoryTournamentPurgeRosters(void);
int StoryTournamentGetGameSlot(int game, int *pLvlt, int *pRow);
int StoryTournamentGetUserTeam(void);
void StoryTournamentDrawBracket(void);
int StoryTournamentAdvanceRound(void);
int StoryTournamentIsWon(void);
void StoryTournamentFindUserGame(int *pDit1, int *pDit2, int *pLvlt);
void StoryTournamentRestoreOptions(void);
void StoryTournamentSetOptions(int value14, int value1);
int StoryTournamentLoadCpuTeam(int digt);
int StoryTournamentLoadUserTeam(int digt);

#if defined(DECOMP_COMPARE)
void StoryTournamentGetTeamName(int id, char *pName, int size)
{
    char name[18];

    if (id < 0) {
        *pName = 0;
        return;
    }
    if (TeamDbSeekId(&_StoryTournament_TeamCursor, id, 0) == 0) {
        strncpy(pName, "NFL Draft Team", size);
    } else {
        DbCursorGetString(&_StoryTournament_TeamCursor, 0x414E4454, (int)name, sizeof(name));
        name[17] = 0;
        strncpy(pName, name, size);
    }
}

/* Row of the next round's game that the team won, or 0. */
int StoryTournamentFindNextRow(int team, int lvlt)
{
    int dit1;
    int dit2;
    int tniw;
    int next;
    int count;
    int row;

    if (lvlt <= 3) {
        next = lvlt + 1;
        count = 1 << next;
        for (row = 0; row < count; row++) {
            if (TournamentGetMatch(next, row, &dit1, &dit2, &tniw)) {
                if ((dit1 == team && tniw == 1) || (dit2 == team && tniw == 2)) {
                    return row;
                }
            }
        }
    }
    return 0;
}

void StoryTournamentCloseDbs(void)
{
    TeamDbClose(&_StoryTournament_TeamCursor);
    if (_StoryTournament_State.mOpen) {
        TournamentClose();
        _StoryTournament_State.mOpen = 0;
    }
    ExpLevelClose();
    fn_8008056C(_StoryTournament_pPlayerDb);
    _StoryTournament_pPlayerDb = 0;
    StevClose();
    UserStatsClose(_StoryTournament_pUserStats);
    _StoryTournament_pUserStats = 0;
}

void StoryTournamentOpenDbs(void)
{
    _StoryTournament_State.mIndex = DbUserFindIndex(DbUserGetCurrent());
    _StoryTournament_pPlayerDb = &_StoryTournament_PlayerDb;
    PlayerCursorOpen(&_StoryTournament_PlayerDb, 0, 0x54415453);
    StevOpen();
    ExpLevelOpen();
    _StoryTournament_State.mUnknown2 = 0x7FFF;
    _StoryTournament_pUserStats = &_StoryTournament_UserStats;
    UserStatsOpen(&_StoryTournament_UserStats, _StoryTournament_State.mIndex);
    _StoryTournament_State.mOpen = TournamentOpen(_StoryTournament_State.mIndex);
    TeamDbOpen(&_StoryTournament_TeamCursor, 0, 0x54415453);
}

void StoryTournamentFetchSkill(void)
{
    _StoryTournament_State.mUnknown1 = StoryGetLkss(_StoryTournament_State.mIndex);
}

void StoryTournamentPurgeRosters(void)
{
    fn_8018C48C(0x54415453);
    fn_8018C48C(0x454D4147);
}

int StoryTournamentGetGameSlot(int game, int *pLvlt, int *pRow)
{
    if (game >= 0 && game <= 14) {
        *pLvlt = _StoryTournament_aiGameLevel[game];
        *pRow = _StoryTournament_aiGameRow[game];
        return 1;
    }
    return 0;
}

/* Winner ('TNIW') of a game the player does not take part in. */
int StoryTournamentPickWinner(int dit1, int dit2)
{
    if (dit1 == 0x31) {
        return 1;
    }
    if (dit2 == 0x31) {
        return 2;
    }
    return DbUtilRandomRange(1, 3);
}

int StoryTournamentGetUserTeam(void)
{
    int teams[8];
    int team = 0;

    if (TournamentGetTeamList(teams) == 8) {
        team = teams[0];
    }
    return team;
}

/* Draws the first round of the bracket. */
void StoryTournamentDrawBracket(void)
{
    int teams[8];
    int order[8];
    int i;
    int j;
    int tmp;
    int first;
    int second;
    int lvlt;
    int team;
    int dit1;
    int dit2;
    int half = 4;

    TournamentGetTeamList(teams);
    for (i = 0; i < 8; i++) {
        order[i] = i;
    }
    for (i = 0; i <= 7; i++) {
        do {
            j = DbUtilRandomRange(0, 8);
        } while (j == i);
        int swap = order[i];
        order[i] = order[j];
        order[j] = swap;
    }
    first = 0;
    while (first < 8 && teams[order[first]] != 0x2E) {
        first++;
    }
    second = 0;
    while (second < 8 && teams[order[second]] != 0x31) {
        second++;
    }
    if (second < half) {
        if (first < half) {
            tmp = order[second];
            order[second] = order[second + half];
            order[second + half] = tmp;
        }
    } else if (first >= half) {
        tmp = order[second];
        order[second] = order[second - half];
        order[second - half] = tmp;
    }
    lvlt = TournamentGetRoundCount(8);
    team = StoryTournamentGetUserTeam();
    for (i = 0; i < 8; i += 2) {
        dit1 = teams[order[i]];
        dit2 = teams[order[i + 1]];
        if (dit1 == team) {
            dit1 = dit2;
            dit2 = team;
        }
        TournamentSetMatchWinner(lvlt, dit1, dit2, 0);
    }
}

/* Records the current match as won by its second team and plays the rest of
   the round. Returns 1 when that match was the final. */
int StoryTournamentAdvanceRound(void)
{
    int dit1;
    int dit2;
    int tniw;
    int lvlt = _StoryTournament_Match.mLvlt;
    int done = 0;
    int count;
    int row;
    int team;
    int winner1;
    int winner2;
    int next;
    int games;

    dit1 = _StoryTournament_Match.mDit1;
    dit2 = _StoryTournament_Match.mDit2;
    TournamentSetMatchWinner(lvlt, dit1, dit2, 2);
    if (lvlt == 1) {
        TournamentSetMatchWinner(0, dit2, dit2, 2);
        done = 1;
    } else {
        row = 0;
        count = TournamentGetLevelMatchCount(lvlt);
        next = lvlt - 1;
        for (; row < count; row++) {
            if (TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw) && tniw == 0) {
                tniw = StoryTournamentPickWinner(dit1, dit2);
                TournamentSetMatchWinner(lvlt, dit1, dit2, tniw);
            }
        }
        team = StoryTournamentGetUserTeam();
        games = TournamentGetLevelMatchCount(lvlt);
        for (row = 0; row < games; row += 2) {
            TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw);
            if (tniw == 1) {
                winner1 = dit1;
            } else {
                winner1 = dit2;
            }
            TournamentGetMatch(lvlt, row + 1, &dit1, &dit2, &tniw);
            if (tniw == 1) {
                winner2 = dit1;
            } else {
                winner2 = dit2;
            }
            if (winner1 == team) {
                winner1 = winner2;
                winner2 = team;
            }
            TournamentSetMatchWinner(next, winner1, winner2, 0);
        }
    }
    return done;
}

int StoryTournamentIsWon(void)
{
    int dit1;
    int dit2;
    int tniw;
    int done = 0;

    if (TournamentGetMatch(0, 0, &dit1, &dit2, &tniw)) {
        done = tniw == 2;
    }
    return done;
}

/* Finds the player's game in the earliest round that has games. */
void StoryTournamentFindUserGame(int *pDit1, int *pDit2, int *pLvlt)
{
    int tniw;
    int last = TournamentGetRoundCount(8);
    int lvlt = 1;
    int team = StoryTournamentGetUserTeam();
    int count = last + 1;
    int row;

    for (; lvlt <= last; lvlt++) {
        count = TournamentGetLevelMatchCount(lvlt);
        if (count > 0) {
            break;
        }
    }
    if (lvlt > 0 && lvlt <= last) {
        for (row = 0; row < count; row++) {
            if (TournamentGetMatch(lvlt, row, pDit1, pDit2, &tniw) && *pDit2 == team) {
                *pLvlt = lvlt;
                break;
            }
        }
    }
}

void StoryTournamentRestoreOptions(void)
{
    if (_StoryTournament_SavedOptions.mSaved) {
        GameOptionsSet(14, _StoryTournament_SavedOptions.mValue14);
        GameOptionsSet(1, _StoryTournament_SavedOptions.mValue1);
        if (_StoryTournament_SavedOptions.mValue0 > -1) {
            GameOptionsSet(0, _StoryTournament_SavedOptions.mValue0);
        }
        _StoryTournament_SavedOptions.mSaved = 0;
    }
}

void StoryTournamentSetOptions(int value14, int value1)
{
    if (!_StoryTournament_SavedOptions.mSaved) {
        _StoryTournament_SavedOptions.mSaved = 1;
        _StoryTournament_SavedOptions.mValue14 = GameOptionsGet(14);
        _StoryTournament_SavedOptions.mValue1 = GameOptionsGet(1);
        if (_StoryTournament_State.mUnknown1 > -1) {
            _StoryTournament_SavedOptions.mValue0 = GameOptionsGet(0);
        } else {
            _StoryTournament_SavedOptions.mValue0 = _StoryTournament_State.mUnknown1;
        }
    }
    GameOptionsSet(14, value14);
    GameOptionsSet(1, value1);
    if (_StoryTournament_State.mUnknown1 > -1) {
        GameOptionsSet(0, _StoryTournament_State.mUnknown1);
    }
}

void StoryTournamentPlaceDrafted(int a, int *pList, int count, Object_8008044C *pObject)
{
    int *pSlots = 0;
    int list;
    int i;
    int id;
    int slot;
    int j;
    int tmp;

    list = FormationGetByIndex(0, 1);
    if (list) {
        pSlots = FormationLineupFetchUser(list, a);
    }
    if (pSlots) {
        for (i = 0; i < count; i++) {
            id = pList[i];
            if (!PlayerDbSeekId(pObject, id, 0)) {
                continue;
            }
            slot = PlayerDbGetPbpo(pObject);
            if (pSlots[slot] == id) {
                continue;
            }
            if (slot <= 6) {
                for (j = 0; j <= 6; j++) {
                    if (pSlots[j] == id) {
                        tmp = pSlots[slot];
                        pSlots[slot] = pSlots[j];
                        pSlots[j] = tmp;
                        break;
                    }
                }
            } else {
                for (j = 7; j <= 13; j++) {
                    if (id == pSlots[j]) {
                        tmp = pSlots[slot];
                        pSlots[slot] = pSlots[j];
                        pSlots[j] = tmp;
                        break;
                    }
                }
            }
        }
        FormationLineupFillTeam(a, pSlots);
    }
}

int StoryTournamentLoadCpuTeam(int digt)
{
    int list[14];

    TournamentGetTeamPlayers(digt, list);
    StoryEventsPlaceSpecialPlayers(_StoryTournament_pEvent, list);
    list[7] = 0x7FFF;
    StoryEventsSetLineup(0, list);
    DepthChartAutoFill(0, list, 4);
    TeamDbLoadSideWithCopies(digt, list, 0, 7);
    return digt;
}

int StoryTournamentLoadUserTeam(int digt)
{
    StoryTeamIdBlock_t picks;
    int list[14];
    int digt2;
    int count;
    int i;

    digt2 = StoryTeamLoadOneToStats(_StoryTournament_State.mIndex, 1, &picks);
    if (PlayerDbSeekId(_StoryTournament_pPlayerDb, picks.mUnknown0, 0)) {
        DbCursorSetInt(_StoryTournament_pPlayerDb, 0x44494F50, picks.mUnknown0);
        DbCursorSetInt(_StoryTournament_pPlayerDb, 0x44494754, digt2);
    }
    count = TournamentGetTeamPlayers(digt, list);
    for (i = 0; i < count && list[i] != picks.mUnknown0; i++) {
    }
    list[7] = 0x7FFF;
    StoryEventsSetLineup(1, list);
    DepthChartAutoFill(1, list, 4);
    StoryTournamentPlaceDrafted(1, &picks.mUnknown0, 1, _StoryTournament_pPlayerDb);
    TeamDbLoadSideWithCopies(digt, list, 1, 7);
    return digt;
}
#endif

void StoryTournamentSetupMatch(int dit1, int dit2, int lvlt)
{
    DepthChartLoad(1);
    dit2 = StoryTournamentLoadUserTeam(dit2);
    _StoryTournament_Match.mDit1 = StoryTournamentLoadCpuTeam(dit1);
    _StoryTournament_Match.mDit2 = dit2;
    _StoryTournament_Match.mLvlt = lvlt;
    DepthChartSave();
}

void StoryTournamentStartMatch(void)
{
    int dit1;
    int dit2;
    int lvlt;
    int saved = MsgMainMenuAssignPads();

    StoryTournamentSetOptions(0, 0x24);
    if (TournamentGetLevelMatchCount(1) == 0) {
        _StoryTournament_pEvent->mCsos = -1;
    }
    StoryTournamentFindUserGame(&dit1, &dit2, &lvlt);
    StoryTournamentSetupMatch(dit1, dit2, lvlt);
    if (_StoryTournament_pEvent->mDive) {
        _StoryTournament_pEvent->mDive = 0;
    }
    MsgPlayerSelectStart(-1, MsgMainMenuGetActivePad(), saved);
    UserProfileSelect(_StoryTournament_State.mIndex, 1);
    GameInfoSet(2, 1);
    MsgStadiumStartGame(_StoryTournament_pEvent->mDive);
}

int StoryTournamentHasMatches(void)
{
    return TournamentGetMatchCount() > 0;
}

int StoryTournamentFetchEvent(void)
{
    int result = 100;

    if (StevGetRow(0, StevCountDiveRows(0) - 1, &_StoryTournament_EventRow)) {
        result = 123;
        _StoryTournament_pEvent = &_StoryTournament_EventRow;
    }
    return result;
}

void StoryTournamentRunEvent(void)
{
    switch (_StoryTournament_pEvent->mItes) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    case 4:
        StoryTournamentHasMatches();
        StoryTournamentStartMatch();
        break;
    }
}

void StoryTournamentGetGame(int game, int *pDit1, int *pUnknown5, int *pDit2, int *pUnknown7, int *pWinner)
{
    int lvlt;
    int row;
    int dit1 = -1;
    int dit2 = -1;
    int tniw;
    int found;

    *pUnknown5 = -1;
    *pUnknown7 = -1;
    *pWinner = -1;
    *pDit1 = -1;
    *pDit2 = -1;
    if (StoryTournamentGetGameSlot(game, &lvlt, &row)) {
        found = TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw);
        if (found) {
            *pDit1 = dit1;
            *pDit2 = dit2;
            switch ((unsigned int)tniw) {
            case 0:
                break;
            case 1:
                *pWinner = 0;
                break;
            case 2:
                *pWinner = 1;
                break;
            }
        }
        if (found && lvlt < _StoryTournament_aiGameLevel[14]) {
            if (StoryTournamentFindNextRow(dit1, lvlt) < StoryTournamentFindNextRow(dit2, lvlt)) {
                *pDit2 = dit1;
                *pDit1 = dit2;
            }
        }
    }
}

/* Starts the tournament on first use and returns the player's open game. */
void StoryTournamentEnterScreen(int *pGame)
{
    int lvlt;
    int row;
    int dit1;
    int dit2;
    int tniw;
    int game;

    *pGame = 0;
    if (!_StoryTournament_bEntered) {
        MsgMainMenuGoTo(10);
        StoryTournamentPurgeRosters();
        StoryTournamentOpenDbs();
        StoryTournamentRestoreOptions();
        StoryTournamentFetchSkill();
        if (!StoryTournamentHasMatches()) {
            StoryTournamentDrawBracket();
        }
        _StoryTournament_pEvent = 0;
        _StoryTournament_bEntered = 1;
        FELoopResetIdle();
    }
    for (game = 0; game <= 14; game++) {
        if (StoryTournamentGetGameSlot(game, &lvlt, &row) && TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw) && tniw == 0 &&
            (dit1 == 0x2E || dit2 == 0x2E)) {
            *pGame = game;
        }
    }
}

void StoryTournamentExitScreen(void)
{
    if (_StoryTournament_bEntered) {
        if (!StoryTournamentIsWon()) {
            if (MsgGameGetSetupState() == 0) {
                StoryTournamentPurgeRosters();
                _StoryTournament_pEvent = 0;
            } else if (MsgGameGetSetupState() == 1) {
                FELoopSetResume(1);
                StoryTournamentFetchEvent();
                StoryTournamentRunEvent();
            }
        }
        StoryTournamentCloseDbs();
        _StoryTournament_bEntered = 0;
    }
    InGameRewardSetAlt(0);
}

int StoryTournamentRecordResult(void)
{
    int done = 0;

    if (_StoryTournament_pEvent) {
        StoryTournamentOpenDbs();
        if (!StoryTournamentIsWon()) {
            StoryTournamentAdvanceRound();
        }
        if (StoryTournamentIsWon()) {
            done = 1;
        }
        StoryTournamentCloseDbs();
    }
    return done;
}

int StoryTournamentScreenMessage(unsigned int id, StoryTournamentArgs_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        StoryTournamentEnterScreen(pBlock->mpGame);
        break;
    case 0x80000002:
        StoryTournamentExitScreen();
        break;
    case 0x80000003: {
        int *pDit2 = pBlock->mpDit2;
        int *pDit1 = pBlock->mpDit1;

        StoryTournamentGetGame((int)pBlock->mpGame, pDit1, pBlock->mpUnknown24, pDit2, pBlock->mpUnknown20, pBlock->mpWinner);
        StoryTournamentGetTeamName(*pDit1, pBlock->mpName1->mpText, pBlock->mpName1->mLength);
        StoryTournamentGetTeamName(*pDit2, pBlock->mpName2->mpText, pBlock->mpName2->mLength);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

StevRow_t *StoryTournamentGetEvent(void)
{
    return _StoryTournament_pEvent;
}

void StoryTournamentClearEvent(void)
{
    _StoryTournament_pEvent = 0;
}

void StoryTournamentBegin(void)
{
    int saved = MsgMainMenuAssignPads();

    StoryTournamentFetchEvent();
    MsgPlayerSelectStart(-1, MsgMainMenuGetActivePad(), saved);
    UserProfileSelect(_StoryTournament_State.mIndex, 1);
    if (_StoryTournament_State.mOpen == 0) {
        _StoryTournament_State.mIndex = DbUserFindIndex(DbUserGetCurrent());
        TournamentOpen(_StoryTournament_State.mIndex);
    }
    TournamentClearMatches();
    TournamentClearPlayers();
    if (_StoryTournament_State.mOpen == 0) {
        TournamentClose();
    }
    MsgTeamPickSetMode(2, 0);
    MsgTeamPickSetSources(1);
}

void StoryTournamentSetTeamPlayers(int team, int *pDigp)
{
    int teams[8];
    int munt = 0;
    int i;

    StoryTournamentOpenDbs();
    TournamentGetTeamList(teams);
    for (munt = 0; munt <= 7 && teams[munt] != team; munt++) {
    }
    if (team == StoryTournamentGetUserTeam()) {
        for (i = 0; i <= 6 && pDigp[i] != 0; i++) {
        }
    }
    TournamentSetPlayersTeam(pDigp, 7, munt, team);
    StoryTournamentCloseDbs();
}

int StoryTournamentIsActive(void)
{
    int result;

    if (_StoryTournament_State.mOpen == 0) {
        TournamentOpen(_StoryTournament_State.mIndex = DbUserFindIndex(DbUserGetCurrent()));
    }
    result = StoryTournamentHasMatches();
    if (_StoryTournament_State.mOpen == 0) {
        TournamentClose();
    }
    return result;
}

int StoryTournamentIsComplete(void)
{
    int result;

    if (_StoryTournament_State.mOpen == 0) {
        TournamentOpen(_StoryTournament_State.mIndex = DbUserFindIndex(DbUserGetCurrent()));
    }
    result = StoryTournamentIsWon();
    if (_StoryTournament_State.mOpen == 0) {
        TournamentClose();
    }
    return result;
}

int StoryTournamentOnGameEnd(void)
{
    int result;

    if (_StoryTournament_pEvent == 0) {
        result = 0;
    } else {
        int state = fn_80178AE0();
        result = 1;
        if (state == 1) {
            StoryTournamentRecordResult();
        }
    }
    return result;
}

void StoryTournamentForceWin(int index)
{
    TDbCompilePerformOp(0,
                "use \x8c insert into 'LTFN' set 'TNIW' = 2 and 'LVLT' = 0 and '1DIT' = 1 and '2DIT' = 2\n",
                DbUserGetDb(DbUserGetId(index)));
}

void StoryTournamentClearWin(int index)
{
    TDbCompilePerformOp(0, "use \x8c delete from 'LTFN' where ('TNIW' = 2)\n", DbUserGetDb(DbUserGetId(index)));
}

void StoryTournamentDropEvent(void)
{
    _StoryTournament_pEvent = 0;
}

int StoryTournamentCountRows(void)
{
    int count = 0;

    TDbCompilePerformOp(0, "use \x8c select count(*) into \x85 from 'LTFN'\n", DbUserGetDb(DbUserGetCurrent()), &count);
    return count;
}
}
