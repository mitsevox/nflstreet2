/* Sets up the scores, the kicking side and the outcome state when a game starts. */

#include "game/Challenge.h"
#include "game/ScrmPlayResult.h"
#include <string.h>
#include "game/TDbCompilePerformOp.h"

extern "C" {
void GameOutcomeSet(int value);
int ChallengeIsActive(void);
void GameInfoSet(int index, int value);
void fn_800A7A0C(int a);
void ScrmSetDown(int a);
void ScrmSetOffenseTeam(int value);
void ScrmSetSnapOffense(int value);
void ScrmSetTeamScore(int which, short value);
void ScrmClearDriveBallPlaced(void);
void ScrmSetPlayResult(const ScrmPlayResult_t *p);
void ScrmClearConversion(void);
float SyncRandGetFloat(int stream);

void GameSetupInit(void)
{
    ScrmPlayResult_t info;

    ScrmClearConversion();
    if (ChallengeIsActive()) {
        ScrmSetTeamScore(0, ChalGetCurrent()->mUnknown1AC);
        ScrmSetTeamScore(1, ChalGetCurrent()->mUnknown1A8);
        TDbCompilePerformOp(0, "update 'FNIG' set 'CSAG' = \x82 and 'CSHG' = \x82\n",
                    ChalGetCurrent()->mUnknown1A8, ChalGetCurrent()->mUnknown1AC);
        ScrmClearDriveBallPlaced();
        memset(&info, 0, sizeof(info));
        ScrmSetPlayResult(&info);
        ScrmSetDown(ChalGetCurrent()->mUnknown1C1);
        if (ChalGetCurrent()->mUnknown1B8 == 0) {
            ScrmSetOffenseTeam(1);
            ScrmSetSnapOffense(1);
        } else if (ChalGetCurrent()->mUnknown1B8 == 1) {
            ScrmSetOffenseTeam(0);
            ScrmSetSnapOffense(0);
        } else if (SyncRandGetFloat(1) < 0.5f) {
            ScrmSetOffenseTeam(1);
            ScrmSetSnapOffense(1);
            GameInfoSet(2, 1);
        } else {
            ScrmSetOffenseTeam(0);
            ScrmSetSnapOffense(0);
            GameInfoSet(2, 0);
        }
        fn_800A7A0C(0);
        fn_800A7A0C(1);
        GameOutcomeSet(2);
    } else {
        ScrmSetTeamScore(0, 0);
        ScrmSetTeamScore(1, 0);
        ScrmClearDriveBallPlaced();
        TDbCompilePerformOp(0, "update 'FNIG' set 'CSAG' = \x82 and 'CSHG' = \x82\n", 0, 0);
        memset(&info, 0, sizeof(info));
        ScrmSetPlayResult(&info);
        ScrmSetDown(1);
        ScrmSetOffenseTeam(1);
        ScrmSetSnapOffense(1);
        GameInfoSet(2, 1);
        GameOutcomeSet(2);
    }
}

}
