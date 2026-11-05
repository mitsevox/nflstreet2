#include "game/Challenge.h"
#include "game/fn_8007F828.h"

extern "C" {
int fn_8002B5B0(void);
void fn_8002B5B8(int value);
void fn_8002B5C0(int value);
void fn_8002B714(int value);
int fn_80025700(void);
int fn_800634E4(void);
void fn_800634F8(void);
void ChalCloseCursors(void);
int ChalGetProgress(int id, int *pA, int *pB);
void ChalSetProgress(int id, int a, int b, int c);
void ChalAddPoints(int value);
void ChalSetTournamentWon(int value);
int ChalHasMedalGoal(Challenge_t *pRecord);
int ChalHasReward(Challenge_t *pRecord, int id);

void fn_8002B5D0(int a, int b)
{
    if (fn_8002B5B0() == 2) {
        switch (fn_80025700()) {
        case 0: {
            Challenge_t *pRecord = ChalGetCurrent();

            if (a == 2) {
                a = 1;
                if (ChalHasMedalGoal(pRecord)) {
                    a = b > 2;
                }
            }
            fn_8002B5B8(a);
            if (a == 0) {
                int x;
                int y;
                int result;

                if (ChalGetProgress(pRecord->mUnknown0, &x, &y) != 2) {
                    ChalAddPoints(-pRecord->mUnknown196);
                }
                if (ChalHasMedalGoal(pRecord)) {
                    fn_8002B5C0(b);
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
            fn_8002B5B8(a);
            if (a == 0) {
                fn_800634F8();
                if (fn_800634E4()) {
                    ChalSetTournamentWon(1);
                    fn_8002B714(34);
                }
            }
            break;
        }
        ChalCloseCursors();
    }
}

}
