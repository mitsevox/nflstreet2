#include "game/Object_80039F5C.h"
#include "game/StyleTracker.h"
#include "game/DbCursor.h"
#include "game/Challenge.h"
#include "game/Block_800A70F4.h"
#include "game/AudmonEvent.h"

struct GamebreakerRecord_t;

extern "C" {
int GamebreakerFind(DbCursor *pCursor, int key, int *pResult);
void GamebreakerRead(DbCursor *pCursor, GamebreakerRecord_t *pOut);
void fn_800A6658(int team);
void fn_800A6CB0(int id);
void fn_800A6DA4(void);
int fn_800A6590(int value);
int fn_800A8408(int team);
void fn_800AE7F0(int index, int team, Object_80039F5C *p);
void HudSetGameBreakerMeter(int a, float t, int b, int direct);
void HudSetGameBreakerLevel(int a, int b);
void HudSetGameBreakerHalf(int a, int b);
int ChallengeIsActive(void);
int fn_80177F70(void);
int fn_80178308(void);

extern Block_800A70F4 *lbl_803EC954[2];
extern int lbl_803EC95C;
extern unsigned char lbl_803EAA50;
extern int lbl_802D7EFC[][3];
}

extern "C" void fn_800A7B5C(void)
{
    DbCursor cursor;
    int row;
    int quiet = 0;
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        if ((lbl_803EC954[team]->mUnknown6C == 0 && StyleTrackerGetMeterFraction(team) >= 0.5f) ||
            (lbl_803EC954[team]->mUnknown6C == 1 && StyleTrackerGetMeterFraction(team) >= 1.0f)) {
            Block_800A70F4 *pBlock = lbl_803EC954[team];

            if (pBlock->mUnknown6C == 0) {
                pBlock->mUnknown5C++;
            } else if (pBlock->mUnknown6C == 1) {
                pBlock->mUnknown60++;
            }
            if (fn_80177F70() != 6) {
                fn_80178308();
            }
            DbCursorOpenTable(&cursor, 'KRBG', 'DIBG');
            fn_800A6658(team);
            if (team == fn_80178308()) {
                GamebreakerFind(&cursor, 0, &row);
            } else {
                GamebreakerFind(&cursor, 1, &row);
            }
            GamebreakerRead(&cursor, (GamebreakerRecord_t *)lbl_803EC954[team]);
            DbCursorClose(&cursor);
            lbl_803EC954[team]->mUnknown10 = 10000;
            if (lbl_803EC95C == -1) {
                fn_800A6DA4();
                fn_800A6CB0(lbl_802D7EFC[lbl_803EAA50][0]);
            }
            if (StyleTrackerGetMeterFraction(team) >= 1.0f) {
                lbl_803EC954[team]->mUnknown6C = 2;
                HudSetGameBreakerLevel(team, 2);
            } else {
                lbl_803EC954[team]->mUnknown6C = 1;
                HudSetGameBreakerLevel(team, 1);
                if (StyleTrackerGetMeterFraction(team) >= 0.5f) {
                    HudSetGameBreakerHalf(team, 2);
                }
            }
            lbl_803EC954[team]->mUnknown58 = 1.0f;
            lbl_803EC954[team]->mUnknown64 = 0;
            HudSetGameBreakerMeter(team, StyleTrackerGetMeterFraction(team), 0, 0);
            fn_800AE7F0(fn_800A6590(fn_800A8408(team)), team, 0);
            if (ChallengeIsActive() != 0 &&
                ((team == 0 && ChalGetCurrent()->mUnknown1C3 != 0) ||
                 (team == 1 && ChalGetCurrent()->mUnknown1C2 != 0))) {
                quiet = 1;
            }
            if (!quiet) {
                if (lbl_803EC954[team]->mUnknown6C == 1) {
                    AudmonEventPostArgs(22, 0, team, 0, 0);
                } else if (lbl_803EC954[team]->mUnknown6C == 2) {
                    AudmonEventPostArgs(23, 0, team, 0, 0);
                }
            }
        }
    }
}

extern "C" {
int fn_80178BA4(int team);
int fn_80178BE4(int team);
int fn_800A8444(int team);
}

extern "C" unsigned char fn_800A82FC(int team)
{
    unsigned char result = 0;
    int a = fn_80178BA4(team);
    int b = fn_80178BE4(team);
    int state = lbl_803EC954[team]->mUnknown6C;

    if (state == 2) {
        if (fn_80177F70() != 6 || a != 0 || b != 0) {
            result = 1;
        }
    } else if (state == 1) {
        if (b != 0 || a != 0 ||
            (fn_800A8444(team == 0) && fn_80177F70() != 6 && StyleTrackerGetMeterFraction(team) < 0.75f)) {
            result = 1;
        }
    }
    lbl_803EC954[team]->mUnknown64 = result;
    return result;
}
