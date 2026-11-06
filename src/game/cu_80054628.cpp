#include "game/Class_8018FD64Inline.h"

extern "C" {
void fn_80060458(int index, int level);
void fn_8006059C(int index);
void fn_80060674(int index);
void fn_80061D64(int index);
void fn_80061DA0(int index);
unsigned int ChalGetPoints(void);
void ChalAddPoints(int value);
void ChalSetDevPointsForSlot(signed char db, int value);
void EnvSetLocked(int index, int id, int value);
void EnvUnlockBonus(int index);
void EnvLockBonus(int index);
void GearUnlockAll(signed char db);
void GearLockAll(signed char db);
void PlaybookUnlockAll(signed char db, int index);
void PlaybookResetOrder(signed char db, int index);
void TeamUnlock(int db, int id);
void TeamLock(int db, int id);
void TeamUnlockAll(int db);
void TeamLockAll(int db);
void fn_80082688(int db);
void fn_8008274C(int db);
int TutorialAllComplete(void);
void TutorialSetProfileDb(int db);
void UserInfoSetPoints(int handle, int value);
int fn_80186B38(int db);
void fn_8018E428(int index, int value);
void fn_8018F340(int a, int b);
int fn_8018F3D8(int a);
void fn_8018F41C(int a);
void fn_8018F4C4(int a);
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_8022F478(int value);
int fn_8022F4BC(void);

void CheatEffectApply(signed char db, int id)
{
    switch (id) {
    case 1:
        EnvUnlockBonus(db);
        break;
    case 2:
        fn_80082688(db);
        break;
    case 3:
        GearUnlockAll(db);
        break;
    case 4:
        TeamUnlockAll(db);
        break;
    case 5:
        PlaybookUnlockAll(db, 0);
        PlaybookUnlockAll(db, 1);
        break;
    case 9:
        TeamUnlock(db, 43);
        break;
    case 10:
        TeamUnlock(db, 40);
        break;
    case 11:
        TeamUnlock(db, 41);
        break;
    case 12:
        TeamUnlock(db, 42);
        break;
    case 13:
        TeamUnlock(db, 39);
        break;
    case 14:
        TeamUnlock(db, 36);
        break;
    case 15:
        TeamUnlock(db, 37);
        break;
    case 16:
        TeamUnlock(db, 38);
        break;
    case 19:
        TeamUnlock(db, 33);
        break;
    case 20:
        TeamUnlock(db, 44);
        break;
    case 18:
        TeamUnlock(db, 34);
        EnvSetLocked(db, 11, 0);
        break;
    case 21:
        EnvSetLocked(db, 10, 0);
        break;
    case 6:
        fn_8018E428(db, 999999);
        ChalSetDevPointsForSlot(db, 999999);
        break;
    case 7:
        UserInfoSetPoints(fn_8022F358(db), 9999999);
        break;
    case 8: {
        int saved = fn_8022F4BC();
        fn_8022F478(fn_8022F358(db));
        fn_8006059C(db);
        fn_80061D64(db);
        fn_8022F478(saved);
        break;
    }
    case 51:
        fn_80060458(db, 0);
        break;
    case 52:
        fn_80060458(db, 1);
        break;
    case 53:
        fn_80060458(db, 2);
        break;
    case 54:
        fn_80060458(db, 3);
        break;
    case 50:
        fn_8006059C(db);
        break;
    case 49: {
        unsigned int value = ChalGetPoints();
        if (value) {
            ChalAddPoints(-value);
        } else {
            ChalAddPoints(1);
        }
        break;
    }
    case 48:
        for (int i = 1; i <= 32; i++) {
            if (i != 19 && i != 22) {
                fn_8018F340(fn_80186B38(fn_8022F4BC()), i);
                fn_8018F4C4(fn_80186B38(fn_8022F4BC()));
            }
        }
        break;
    case 17:
    case 47:
        break;
    }
}

void CheatEffectRemove(signed char db, int id)
{
    switch (id) {
    case 1:
        EnvLockBonus(db);
        break;
    case 2:
        fn_8008274C(db);
        break;
    case 3:
        GearLockAll(db);
        break;
    case 4:
        TeamLockAll(db);
        break;
    case 5:
        PlaybookResetOrder(db, 0);
        PlaybookResetOrder(db, 1);
        break;
    case 9:
        TeamLock(db, 43);
        break;
    case 10:
        TeamLock(db, 40);
        break;
    case 11:
        TeamLock(db, 41);
        break;
    case 12:
        TeamLock(db, 42);
        break;
    case 13:
        TeamLock(db, 39);
        break;
    case 14:
        TeamLock(db, 36);
        break;
    case 15:
        TeamLock(db, 37);
        break;
    case 16:
        TeamLock(db, 38);
        break;
    case 18: {
        int handle = fn_8022F3D4(fn_8022F358(db));
        Class_8018FD64 cursor;
        cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
        if (cursor.Class_8018FD64::fn_8018FF9C(0x504C5555) != 0x3FF) {
            TeamLock(db, 34);
        }
        if (fn_8018F3D8(db) != -1) {
            EnvSetLocked(db, 11, 1);
        }
        break;
    }
    case 19:
        TutorialSetProfileDb(fn_8022F358(db));
        if (TutorialAllComplete() == 0) {
            TeamLock(db, 33);
        }
        TutorialSetProfileDb(-1);
        break;
    case 20:
        TeamLock(db, 44);
        break;
    case 21:
        EnvSetLocked(db, 10, 1);
        break;
    case 6:
        fn_8018E428(db, 0);
        ChalSetDevPointsForSlot(db, 0);
        break;
    case 7:
        UserInfoSetPoints(fn_8022F358(db), 0);
        break;
    case 8:
        fn_80060674(db);
    case 50:
        fn_80061DA0(db);
        break;
    case 48:
        fn_8018F41C(db);
        break;
    case 51:
    case 52:
    case 53:
    case 54:
        fn_80060674(db);
        fn_80061DA0(db);
        break;
    case 17:
    case 47:
        break;
    }
}
}
