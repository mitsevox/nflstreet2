/* Records the result of a finished challenge or pairing game. */

#include "game/Object_800785C0.h"
#include "game/fn_8007F828.h"

extern "C" {
int GameOutcomeGet(void);
void GameOutcomeSet(int value);
void ChallengeBonusSet(int value);
void TeamFilterSet(int value);
int ChallengeGetMode(void);
int fn_800634E4(void);
void fn_800634F8(void);
void fn_80077F24(void);
int fn_80078620(int id, int *pA, int *pB);
void fn_80078738(int id, int a, int b, int c);
void fn_80078844(int value);
void fn_8007897C(int value);
int fn_8007984C(Object_800785C0 *pRecord);
int fn_80079864(Object_800785C0 *pRecord, int id);

void ChallengeRecordResult(int a, int b)
{
    if (GameOutcomeGet() == 2) {
        switch (ChallengeGetMode()) {
        case 0: {
            Object_800785C0 *pRecord = fn_800785C0();

            if (a == 2) {
                a = 1;
                if (fn_8007984C(pRecord)) {
                    a = b > 2;
                }
            }
            GameOutcomeSet(a);
            if (a == 0) {
                int x;
                int y;
                int result;

                if (fn_80078620(pRecord->mUnknown0, &x, &y) != 2) {
                    fn_80078844(-pRecord->mUnknown196);
                }
                if (fn_8007984C(pRecord)) {
                    ChallengeBonusSet(b);
                }
                result = 2;
                if (fn_80079864(pRecord, 4)) {
                    result = 3;
                }
                fn_80078738(pRecord->mUnknown0, result, b, fn_8007F828(0));
            }
            break;
        }
        case 1:
            GameOutcomeSet(a);
            if (a == 0) {
                fn_800634F8();
                if (fn_800634E4()) {
                    fn_8007897C(1);
                    TeamFilterSet(34);
                }
            }
            break;
        }
        fn_80077F24();
    }
}

}
