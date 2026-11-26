/* Stat generator module support: creates the clock-seeded random-number
   stream the StatGen module uses while it runs and deletes it when the
   module shuts down, and holds the record of the game the stat generator
   simulates. Of the simulation itself the game keeps no code: the team
   set-up and score-saving functions below are linked out, and only their
   database query strings remain after the code. */
#include "game/StatGen.h"
#include "game/TDbCompilePerformOp.h"
#include "engine/rand.h"

/* One team of the simulated game: its id, the ten team ratings read from
   the team table, and the per-game counters the simulation clears. */
typedef struct StatGenTeam_t {
    int mId;
    int mRatings[10];
    int unk_0x2C;
    int unk_0x30;
    int unk_0x34;
    int unk_0x38;
    int unk_0x3C;
    int mScore;
    int unk_0x44;
    int unk_0x48;
    int unk_0x4C;
    int unk_0x50;
    int unk_0x54;
    int unk_0x58;
    unsigned char unk_0x5C[0x13B0 - 0x5C];
} StatGenTeam_t;

/* The simulated game: both teams, then the game state, among it the
   overtime flag the final score is saved with. */
typedef struct StatGenGame_t {
    StatGenTeam_t mTeams[2];
    unsigned char unk_0x2760[0x277C - 0x2760];
    unsigned char mOvertime;
    unsigned char unk_0x277D[0x27D4 - 0x277D];
} StatGenGame_t;

void StatGenTeamLoadRoster(StatGenTeam_t *pTeam, int id);
int StatGenGetWeek(void);
int StatGenGetFirstPlayoffWeek(void);

static void *_StatGen_pRandomStream = 0;

static StatGenGame_t _StatGen_sGame;

void StatGenTeamInit(StatGenTeam_t *pTeam, int id, unsigned char flag)
{
    pTeam->mId = id;
    StatGenTeamLoadRoster(pTeam, id);
    TDbCompilePerformOp(0, "select 'FORT' into \x82 and 'EDRT' into \x82 and 'BDRT' into \x82 and 'LDRT' into \x82 and 'BLRT' into \x82 and 'BQRT' into \x82 and 'BRRT' into \x82 and 'RRWT' into \x82 and 'LORT' into \x82 and 'TSRT' into \x82 from 'MAET' where 'DIGT' = \x82\n",
                        &pTeam->mRatings[0], &pTeam->mRatings[1], &pTeam->mRatings[2], &pTeam->mRatings[3],
                        &pTeam->mRatings[4], &pTeam->mRatings[5], &pTeam->mRatings[6], &pTeam->mRatings[7],
                        &pTeam->mRatings[8], &pTeam->mRatings[9], id);
    pTeam->unk_0x2C = 0x100;
    pTeam->unk_0x30 = 0;
    pTeam->unk_0x34 = 0x100;
    pTeam->unk_0x38 = 0;
    if (StatGenGetWeek() < StatGenGetFirstPlayoffWeek() + 3 && flag == 1) {
        if (StatGenGetWeek() < StatGenGetFirstPlayoffWeek()) {
            pTeam->mRatings[0] /= 2;
            pTeam->mRatings[1] /= 2;
        } else {
            pTeam->mRatings[0] = 0;
            pTeam->mRatings[1] = 0;
        }
    }
    pTeam->unk_0x3C = 0;
    pTeam->mScore = 0;
    pTeam->unk_0x4C = 0;
    pTeam->unk_0x48 = 0;
    pTeam->unk_0x50 = 0;
    pTeam->unk_0x44 = 0;
    pTeam->unk_0x54 = 0;
    pTeam->unk_0x58 = 0;
}

void StatGenSaveQuarterScores(int quarter, unsigned char home, unsigned char away)
{
    int game = 0;

    TDbCompilePerformOp(0, "select 'MNGS' into \x82 from 'FNIG'\n", &game);
    TDbCompilePerformOp(0, "insert into TBL_WEEK_QTRSCORES set 'CSHG' = \x80 and 'CSAG' = \x80 and 'RTQG' = \x82 and 'MNGS' = \x82\n",
                        home, away, quarter, game);
}

void StatGenSaveFinalScore(StatGenGame_t *pGame)
{
    TDbCompilePerformOp(0, "update 'FNIG' set 'CSHG' = \x82 and 'CSAG' = \x82 and 'RTQG' = \x82 and 'TOFG' = \x83\n",
                        pGame->mTeams[0].mScore, pGame->mTeams[1].mScore, 6, pGame->mOvertime);
}

int StatGenGetWeek(void)
{
    int week;

    if (TDbCompilePerformOp(0, "select COL_SEAS_WEEKNUM into \x82 from TBL_SEASON_INFO\n", &week) != 0) {
        return 0;
    }
    return week;
}

int StatGenGetFirstPlayoffWeek(void)
{
    int week;

    if (TDbCompilePerformOp(0, "select COL_SEAS_FIRSTPLAYOFFWEEKNUM into \x82 from TBL_SEASON_INFO\n", &week) != 0) {
        return 0;
    }
    return week;
}

void StatGenCreateRandomStream(void)
{
    _StatGen_pRandomStream = MathNewRandomStream(0, MathGetRandomSeed());
}

int StatGenDestroyRandomStream(void)
{
    int result = MathDelRandomStream(_StatGen_pRandomStream);
    _StatGen_pRandomStream = 0;
    return result;
}
