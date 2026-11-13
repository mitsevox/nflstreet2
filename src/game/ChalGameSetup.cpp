// Challenge and tournament game set-up. Starting a challenge loads it, picks the
// opponent team (remembered per challenge and user) and copies the challenge's
// game options; starting a tournament game puts the bracket opponent against the
// user's team. Some challenges play against a generated team: it is created in
// the stat database, its player ratings are scaled down, and it is copied with
// its players into the game database.
#include "game/Challenge.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/GameOptions.h"
#include "game/fn_801FCE10.h"

static int _ChalGame_aiGeneratedPositions[7] = {0, 1, 2, 4, 8, 9, 13};
static int _ChalGame_iCachedChallenge = -1;
static int _ChalGame_iCachedTeam = -1;
static int _ChalGame_iCachedUser = -1;
static unsigned char _ChalGame_bGeneratedOpponent = 0;

extern "C" {
int fn_801F9980(int handle, int *pTable);
int fn_801F967C(int handle, int table);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int PlayerDbGetRating(Object_8008044C *pObject, int index);
void PlayerDbSetRating(Object_8008044C *pObject, int index, int value);
int fn_8008454C(int type, int logo, const char *pName);
void fn_80084808(int a, int *pIds, int *pCounts, int count, int *pOut, int total);
void fn_80083DE4(int id);
void ChallengeSetMode(int mode);
void GameOutcomeSet(int value);
int fn_8022F4BC(void);
signed char fn_80186B38(int db);
void fn_80186F30(signed char index, unsigned char pad);
void TeamFilterSet(int value);
void MsgChallengeSetFlowState(int value);
void ChalLoadCurrent(unsigned char id, int level);
void fn_80083E1C(DbCursor *pObject, TeamQuery *pQuery);
int ChalHasReward(Challenge_t *pRecord, int id);
int fn_80084388(void);
void fn_8018D7E0(void);
int fn_8008406C(DbCursor *pObject, int id, int *pResult);
int fn_80083FBC(DbCursor *pObject);
void fn_8001441C(int team, int id);
void GameInfoSet(int index, int value);
float fn_80237260(int stream);
void fn_800A2F3C(int value);

int ChalGameCopyTeam(int sourceTeam)
{
    QueryResult result;
    int ids[10];
    unsigned short teamCount = 1;
    unsigned short count;
    int team;
    int table = -1;
    QueryCursor cursor = {0, 0, -1, 0};
    int player;

    fn_8022C628(0x454D4147, 0x4D414554, &team, &teamCount);
    fn_801F9980(0x454D4147, &table);
    fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from 'MAET' where ('DIGT' = \x82)\n", 0x54415453, 0x454D4147, table, sourceTeam);
    fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", 0x454D4147, table, team, sourceTeam);
    fn_801FCE10(&result, "use \x8c insert into 'MAET' * select * from \x8c\n", 0x454D4147, table);
    fn_801F967C(0x454D4147, table);
    fn_801FCE10(&result, "use \x8c update 'MAET' set 'RUMT' = \x85 and 'OLFT' = 0 and 'SIVT' = 1 and 'DIGD' = \x82 where ('DIGT' = \x85)\n", 0x454D4147, 3, 8, team);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int code = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c where ('DIGT' = \x85) order by 'DIGP'\n", 0x54415453, &cursor, &player, 0x59414C50, sourceTeam);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        count = result.mUnknown0;
        fn_80229AA4(0x454D4147, 0x59414C50, ids, &count);
        for (unsigned int i = 0; i < count; i++) {
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801F9980(0x454D4147, &table);
            status = fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where ('DIGP' = \x82)\n", 0x54415453, 0x454D4147, table, 0x59414C50, player);
            status = fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIGP' = \x85 and 'DIOP' = \x85 where ('DIGP' = \x82)\n", 0x454D4147, table, sourceTeam, ids[i], player, player);
            status = fn_801FCE10(&result, "use \x8c insert into 'YALP' * select * from \x8c\n", 0x454D4147, table);
            status = fn_801FCE10(&result, "use \x8c update 'YALP' set 'ITGT' = \x85 where 'DIGP' = \x82\n", 0x454D4147, sourceTeam, ids[i]);
            fn_801F967C(0x454D4147, table);
        }
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    return team;
}

void ChalGameScaleTeamRatings(int team)
{
    Object_8008044C cursor;
    Desc_8008044C desc;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = team;
    fn_8008044C(&cursor, &desc, 0x54415453);
    if (DbCursorFirst((DbCursor *)&cursor)) {
        do {
            for (int i = 0; i < 10; i++) {
                unsigned int value = PlayerDbGetRating(&cursor, i);
                value = (unsigned int)((float)value * 0.13f) * 5;
                value = value == 0 ? 1 : (value > 100 ? 100 : value);
                PlayerDbSetRating(&cursor, i, value);
            }
        } while (DbCursorNext((DbCursor *)&cursor));
    }
    fn_8008056C(&cursor);
}

int ChalGameGenerateTeam(int *pTeam)
{
    int players[10];
    int team = fn_8008454C(6, -1, 0);
    int counts[7] = {1, 1, 1, 1, 1, 1, 1};
    fn_80084808(team, _ChalGame_aiGeneratedPositions, counts, 7, players, 10);
    ChalGameScaleTeamRatings(team);
    fn_80083DE4(team);
    int gameTeam = ChalGameCopyTeam(team);
    if (pTeam) *pTeam = gameTeam;
    return team;
}

void ChalGameStart(unsigned char id)
{
    DbCursor cursor;
    _ChalGame_bGeneratedOpponent = 0;
    ChallengeSetMode(0);
    GameOutcomeSet(2);
    fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
    fn_80186F30(-1, 0);
    TeamFilterSet(1023);
    MsgChallengeSetFlowState(5);
    ChalLoadCurrent(id, GameOptionsGet(0));
    Challenge_t *pRecord = ChalGetCurrent();
    GameOptionsCopyShadow();
    fn_80083E1C(&cursor, 0);
    int team;
    if (ChalHasReward(pRecord, 4)) {
        _ChalGame_bGeneratedOpponent = 1;
        team = 0;
    } else if (pRecord->mUnknown198) {
        team = pRecord->mUnknown198;
    } else if (_ChalGame_iCachedChallenge == pRecord->mUnknown0 && _ChalGame_iCachedTeam != -1 && _ChalGame_iCachedUser == fn_8022F4BC()) {
        team = _ChalGame_iCachedTeam;
    } else {
        team = fn_80084388();
        _ChalGame_iCachedChallenge = pRecord->mUnknown0;
        _ChalGame_iCachedTeam = team;
        _ChalGame_iCachedUser = fn_8022F4BC();
    }
    fn_8018D7E0();
    fn_8008406C(&cursor, 1, 0);
    int otherTeam = fn_80083FBC(&cursor);
    fn_80083F68(&cursor);
    fn_8001441C(0, team);
    fn_8001441C(1, otherTeam);
    switch (pRecord->mUnknown1B8) {
    case 0:
        GameInfoSet(2, 1);
        break;
    case 1:
        GameInfoSet(2, 0);
        break;
    default:
        if (!(fn_80237260(1) >= 0.5f)) GameInfoSet(2, 1);
        else GameInfoSet(2, 0);
        break;
    }
    fn_800A2F3C(pRecord->mUnknown1BC);
    if (pRecord->mUnknown19C == 0) {
        GameOptionsSet(14, 0);
        GameOptionsSet(1, pRecord->mUnknown1A0);
    } else {
        GameOptionsSet(14, 1);
        GameOptionsSet(2, pRecord->mUnknown1A0);
    }
    GameOptionsSet(8, pRecord->mUnknown1A7);
    GameOptionsSet(19, 1);
}

void ChalGameStartTournament(int team, int value)
{
    DbCursor cursor;
    _ChalGame_bGeneratedOpponent = 0;
    GameOptionsCopyShadow();
    ChallengeSetMode(1);
    GameOutcomeSet(2);
    TeamFilterSet(1023);
    MsgChallengeSetFlowState(6);
    fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
    fn_80186F30(-1, 0);
    fn_8018D7E0();
    fn_80083E1C(&cursor, 0);
    fn_8008406C(&cursor, 1, 0);
    int otherTeam = fn_80083FBC(&cursor);
    fn_80083F68(&cursor);
    fn_8001441C(0, team);
    fn_8001441C(1, otherTeam);
    GameInfoSet(2, 1);
    fn_800A2F3C(value);
    GameOptionsSet(14, 0);
    GameOptionsSet(1, 36);
    GameOptionsSet(8, 1);
    GameOptionsSet(19, 1);
}

}

extern "C" int ChalGameHasGeneratedOpponent(void)
{
    return _ChalGame_bGeneratedOpponent;
}
