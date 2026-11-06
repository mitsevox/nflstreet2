/* 32-team knockout bracket: seeds the teams, builds the games round by round,
   simulates the scores of the other teams' games, records the player's result
   and answers the bracket screen's queries. */

#include "game/DbCursor.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802372EC.h"

struct BracketNameArg_t {
    Params_80005284 *mUnknown0;
};

struct BracketGame_t {
    short mUnknown0[2];
    short mUnknown4[2];
};

extern "C" {
int fn_80183360(void);
void ChalGetTournamentScore(int, short *, short *);
float fn_80237260(int stream);
void ChalSetTournamentScore(int, int, int);
void ChalSaveTournamentTeams(int *, int);
void ChalLoadTournamentTeams(int *, int);
void fn_801834DC();
void fn_80183368(int, int);
DbCursor *fn_80182DBC(void);
int fn_800841AC(DbCursor *pObject);
int fn_800841D8(DbCursor *pObject);
int fn_80084204(DbCursor *pObject);
void fn_80188CBC(int, int, int, int, char *);
int ChalGetTournamentSlot();
void ChalSetTournamentSlot(int);
int MsgGameGetSetupState();
int MsgGameGetSetupArg();
void ChalCloseCursors();
void fn_8000FCD4(int a);
void fn_8000473C(int, int);
int ChalGetTournamentWon();
int fn_801787DC(int a);
}

static BracketGame_t *_TournBracket_pGames = 0;
static int _TournBracket_iUserSeed = -1;
static int _TournBracket_iCurGame = -1;
static int _TournBracket_iUserSide = 0;
static int _TournBracket_aiSeedTeams[33] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31,
    34,
};

extern "C" BracketGame_t *TournBracketGetGame(int index)
{
    return &_TournBracket_pGames[index];
}

extern "C" int TournBracketIsPlayed(int index)
{
    BracketGame_t *p = TournBracketGetGame(index);
    return p->mUnknown4[1] != 0 || p->mUnknown4[0] != 0;
}

extern "C" int TournBracketGetTeam(int index)
{
    int result;
    if (index == _TournBracket_iUserSeed) {
        result = fn_80183360();
    } else {
        result = _TournBracket_aiSeedTeams[index];
    }
    return result;
}

extern "C" int TournBracketGetWinner(int index)
{
    int result = -1;
    if (TournBracketIsPlayed(index)) {
        BracketGame_t *p = TournBracketGetGame(index);
        if (p->mUnknown4[1] > p->mUnknown4[0]) {
            result = p->mUnknown0[1];
        } else {
            result = p->mUnknown0[0];
        }
    }
    return result;
}

extern "C" int TournBracketGetRound(int index)
{
    int count = 16;
    int result = 1;
    if (index == 31) {
        result = -1;
    } else {
        while (index >= count) {
            index -= count;
            count /= 2;
            result++;
        }
    }
    return result;
}

extern "C" int TournBracketFindUserGame(int *pSide)
{
    int i;
    *pSide = 2;
    for (i = 0; i <= 31; i++) {
        int played = TournBracketIsPlayed(i);
        if (!played) {
            BracketGame_t *p = TournBracketGetGame(i);
            if (p->mUnknown0[1] == _TournBracket_iUserSeed) {
                *pSide = 1;
                break;
            }
            if (p->mUnknown0[0] == _TournBracket_iUserSeed) {
                *pSide = 0;
                break;
            }
        }
    }
    return i;
}

extern "C" void TournBracketBuild()
{
    int i;
    for (i = 0; i <= 31; i++) {
        BracketGame_t *p = TournBracketGetGame(i);
        if (i <= 15) {
            p->mUnknown0[1] = i * 2;
            p->mUnknown0[0] = i * 2 + 1;
        } else if (i == 31) {
            p->mUnknown0[0] = 32;
            p->mUnknown0[1] = TournBracketGetWinner(30);
        } else {
            int j;
            int base = i * 2 - 32;
            for (j = 0; j <= 1; j++) {
                int k = !j;
                p->mUnknown0[k] = TournBracketGetWinner(base + j);
            }
        }
        ChalGetTournamentScore(i, &p->mUnknown4[1], &p->mUnknown4[0]);
    }
}

extern "C" void TournBracketSimScore(int index, short *score)
{
    int count = 0;
    int side = 1;
    score[0] = 0;
    score[1] = 0;
    while (score[0] <= 35 && score[1] <= 35 && count <= 99) {
        if (fn_80237260(1) < 0.3f) {
            score[side] += 6;
            if (score[side] <= 35) {
                if (fn_80237260(1) < 0.75f) {
                    score[side] += 2;
                } else if (fn_80237260(1) < 0.5f) {
                    score[side] += 1;
                }
            }
        } else if (fn_80237260(1) < 0.05f) {
            score[side] += 2;
        }
        side ^= 1;
        count++;
    }
    if (count > 99) {
        char winner = fn_802372EC(1, 2);
        score[winner] = 36;
    }
}

extern "C" void TournBracketSimRound()
{
    short score[2];
    int round = TournBracketGetRound(_TournBracket_iCurGame);
    int i;
    for (i = 0; i <= 30; i++) {
        if (TournBracketGetRound(i) == round && !TournBracketIsPlayed(i)) {
            BracketGame_t *p = TournBracketGetGame(i);
            TournBracketSimScore(i, score);
            p->mUnknown4[0] = score[0];
            p->mUnknown4[1] = score[1];
            ChalSetTournamentScore(i, score[1], score[0]);
        }
    }
}

extern "C" void TournBracketCreate()
{
    _TournBracket_pGames = (BracketGame_t *)fn_801D2B7C(256, 0, 0);
    fn_801C1F94(_TournBracket_pGames, 0, 256);
    TournBracketBuild();
}

extern "C" void TournBracketDestroy()
{
    fn_801D2BD0(_TournBracket_pGames);
    _TournBracket_pGames = 0;
}

extern "C" void TournBracketShuffleSeeds()
{
    int i;
    for (i = 0; i <= 2; i++) {
        int j;
        for (j = 0; j < 32; j++) {
            int k = fn_802372EC(1, 32);
            int value = _TournBracket_aiSeedTeams[j];
            _TournBracket_aiSeedTeams[j] = _TournBracket_aiSeedTeams[k];
            _TournBracket_aiSeedTeams[k] = value;
        }
    }
}

extern "C" void TournBracketSaveSeeds()
{
    ChalSaveTournamentTeams(_TournBracket_aiSeedTeams, 32);
}

extern "C" void TournBracketLoadSeeds()
{
    ChalLoadTournamentTeams(_TournBracket_aiSeedTeams, 32);
}

extern "C" void TournBracketEnter(int *pIndex)
{
    int i;
    fn_801834DC();
    fn_80183368(1, 1023);
    if (fn_80084438(fn_80182DBC()) == 0) {
        char values[3];
        values[0] = fn_800841AC(fn_80182DBC());
        values[1] = fn_800841D8(fn_80182DBC());
        values[2] = fn_80084204(fn_80182DBC());
        fn_80188CBC(0, 4, fn_80084158(fn_80182DBC()), 172, values);
    }
    _TournBracket_iUserSeed = ChalGetTournamentSlot();
    if (_TournBracket_iUserSeed == -1) {
        _TournBracket_iUserSeed = fn_802372EC(1, 32);
        ChalSetTournamentSlot(_TournBracket_iUserSeed);
        TournBracketShuffleSeeds();
        TournBracketSaveSeeds();
    } else {
        TournBracketLoadSeeds();
    }
    TournBracketCreate();
    i = 31;
    do {
        BracketGame_t *p = TournBracketGetGame(i);
        if (p != 0 && (p->mUnknown0[0] == _TournBracket_iUserSeed || p->mUnknown0[1] == _TournBracket_iUserSeed)) {
            *pIndex = i;
            break;
        }
    } while (--i >= 0);
}

extern "C" void TournBracketPlayNext(int value)
{
    int team = -1;
    int active = 0;
    if (MsgGameGetSetupState() == 1) {
        active = MsgGameGetSetupArg() == 1;
    }
    if (active) {
        char opponent;
        _TournBracket_iCurGame = TournBracketFindUserGame(&_TournBracket_iUserSide);
        opponent = TournBracketGetGame(_TournBracket_iCurGame)->mUnknown0[!_TournBracket_iUserSide];
        team = TournBracketGetTeam(opponent);
    }
    TournBracketDestroy();
    ChalCloseCursors();
    fn_801834DC();
    if (active) {
        fn_8000FCD4(value);
        fn_8000473C(team, 11);
    }
}

extern "C" void TournBracketGetGameInfo(int index, int *pIdA, int *pIdB, BracketNameArg_t nameA, BracketNameArg_t nameB,
                            int *pScoreA, int *pScoreB, int *pResult)
{
    int *ids[2];
    BracketNameArg_t names[2];
    BracketGame_t *p;
    int i;
    char name[24];

    names[0] = nameB;
    ids[0] = pIdB;
    ids[1] = pIdA;
    names[1] = nameA;
    p = TournBracketGetGame(index);
    for (i = 0; i < 2; i++) {
        int team = p->mUnknown0[i];
        if (team == -1) {
            *ids[i] = team;
            fn_801C3284(names[i].mUnknown0->mpText, "TBD", names[i].mUnknown0->mLength);
        } else {
            *ids[i] = TournBracketGetTeam(team);
            DbCursor object;
            fn_80083E40(&object, 0, 0x54415453);
            fn_80084034(&object, *ids[i], 0);
            fn_80083F88(&object, name, 18);
            fn_801C3284(names[i].mUnknown0->mpText, name, names[i].mUnknown0->mLength);
            fn_80083F68(&object);
        }
    }
    *pScoreA = p->mUnknown4[1];
    *pScoreB = p->mUnknown4[0];
    if (!TournBracketIsPlayed(index)) {
        *pResult = -1;
    } else if (*pScoreA > *pScoreB) {
        *pResult = 1;
    } else {
        *pResult = 0;
    }
}

extern "C" void TournBracketGetState(int *p)
{
    *p = ChalGetTournamentWon();
}

extern "C" int TournBracketIsFinal()
{
    return _TournBracket_iCurGame == 31;
}

extern "C" void TournBracketRecordResult()
{
    short score[2];
    if (_TournBracket_iUserSide == 1) {
        score[1] = fn_801787DC(1);
        score[0] = fn_801787DC(0);
    } else {
        score[0] = fn_801787DC(1);
        score[1] = fn_801787DC(0);
    }
    ChalSetTournamentScore(_TournBracket_iCurGame, score[1], score[0]);
    TournBracketCreate();
    TournBracketSimRound();
    TournBracketDestroy();
}

union BracketMsgWord_t {
    int mValue;
    int *mpValue;
};

struct BracketMsgArgs_t {
    BracketMsgWord_t mUnknown0;
    int *mpUnknown4;
    int *mpUnknown8;
    BracketNameArg_t mUnknown12;
    BracketNameArg_t mUnknown16;
    int *mpUnknown20;
    int *mpUnknown24;
    int *mpUnknown28;
};

extern "C" int TournBracketMsg(unsigned int id, BracketMsgArgs_t *p)
{
    switch (id) {
    case 0x80000002:
        TournBracketEnter(p->mUnknown0.mpValue);
        break;
    case 0x80000003:
        TournBracketPlayNext(p->mUnknown0.mValue);
        break;
    case 0x80000001:
        TournBracketGetGameInfo(p->mUnknown0.mValue, p->mpUnknown4, p->mpUnknown8, p->mUnknown12, p->mUnknown16,
                    p->mpUnknown20, p->mpUnknown24, p->mpUnknown28);
        break;
    case 0x80000004:
        TournBracketGetState(p->mUnknown0.mpValue);
        break;
    default:
        return 0;
    }
    return 1;
}
