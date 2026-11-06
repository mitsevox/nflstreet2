/* Records the result of a finished challenge or pairing game. */

#include "game/Challenge.h"
#include "game/fn_8007F828.h"

extern "C" {
int GameOutcomeGet(void);
void GameOutcomeSet(int value);
void ChallengeBonusSet(int value);
void TeamFilterSet(int value);
int ChallengeGetMode(void);
int TournBracketIsFinal(void);
void TournBracketRecordResult(void);
void ChalCloseCursors(void);
int ChalGetProgress(int id, int *pA, int *pB);
void ChalSetProgress(int id, int a, int b, int c);
void ChalAddPoints(int value);
void ChalSetTournamentWon(int value);
int ChalHasMedalGoal(Challenge_t *pRecord);
int ChalHasReward(Challenge_t *pRecord, int id);

void ChallengeRecordResult(int a, int b)
{
    if (GameOutcomeGet() == 2) {
        switch (ChallengeGetMode()) {
        case 0: {
            Challenge_t *pRecord = ChalGetCurrent();

            if (a == 2) {
                a = 1;
                if (ChalHasMedalGoal(pRecord)) {
                    a = b > 2;
                }
            }
            GameOutcomeSet(a);
            if (a == 0) {
                int x;
                int y;
                int result;

                if (ChalGetProgress(pRecord->mUnknown0, &x, &y) != 2) {
                    ChalAddPoints(-pRecord->mUnknown196);
                }
                if (ChalHasMedalGoal(pRecord)) {
                    ChallengeBonusSet(b);
                }
                result = 2;
                if (ChalHasReward(pRecord, 4)) {
                    result = 3;
                }
                ChalSetProgress(pRecord->mUnknown0, result, b, fn_8007F828(0));
            }
            break;
        }
        case 1:
            GameOutcomeSet(a);
            if (a == 0) {
                TournBracketRecordResult();
                if (TournBracketIsFinal()) {
                    ChalSetTournamentWon(1);
                    TeamFilterSet(34);
                }
            }
            break;
        }
        ChalCloseCursors();
    }
}

}
