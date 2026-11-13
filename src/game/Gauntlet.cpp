/* Gauntlet mode progress for a profile slot: the current opponent, which of
   the 32 teams are beaten, how many are left, and the run's win/loss and
   game statistics. Also reads rows of the static 'TK' tables. */
#include "game/DbCursor.h"
#include "game/fn_801FCE10.h"

#include "game/StyleAwardRule.h"

extern "C" {
int SstlFetchEntry(unsigned int index, int *pLglt, char *pEtnr, int size);
int fn_8022F358(int index);
int fn_8022F3D4(int a);

int SstlGetEntryTag(unsigned int index, char *pEtnr, int size);
int GauntletGetCurrentTeam(int a);
int GauntletIsTeamBeaten(int a, int b);
int GauntletSetCurrentTeam(int a, int b);
void GauntletMarkTeamBeaten(int a, int b);
void GauntletClearTeamBeaten(int a, int b);
int GauntletGetTeamsLeft(int a);
void GauntletReset(int a);
void GauntletResetTeamsLeft(int a);
void GauntletAdvance(int a);
void GauntletStatsOpen(DbCursor *pObject, int a);
void GauntletStatsClose(DbCursor *pObject);
int GauntletStatsGet(DbCursor *pObject, int index);
void GauntletStatsAdd(DbCursor *pObject, int index, int delta);
void GauntletStatsReset(int a);
void TkTableOpen(DbCursor *pObject, int type);
void TkTableClose(DbCursor *pObject);
int TkTableFindId(DbCursor *pObject, int id);
void TkTableReadRow(DbCursor *pObject, StyleAwardRule_t *pRecord);

int SstlGetEntryTag(unsigned int index, char *pEtnr, int size)
{
    int lglt = -1;

    SstlFetchEntry(index, &lglt, pEtnr, size);
    return lglt;
}

int GauntletGetCurrentTeam(int a)
{
    int digt;
    int lttg = GauntletGetTeamsLeft(a);

    fn_801FCE10(0, "use \x8c select 'DIGT' into \x85 from 'MTTG' where 'LTTG' = \x82\n",
                fn_8022F3D4(fn_8022F358(a)), &digt, lttg);
    return digt;
}

int GauntletIsTeamBeaten(int a, int b)
{
    int fdtg;

    if (fn_801FCE10(0, "use \x8c select 'FDTG' into \x82 from 'NUAG' where 'DIGT' = \x85\n",
                    fn_8022F3D4(fn_8022F358(a)), &fdtg, b) == 0 && fdtg == 1) {
        return 1;
    }
    return 0;
}

int GauntletSetCurrentTeam(int a, int b)
{
    return fn_801FCE10(0, "use \x8c update 'MTTG' set 'DIGT' = \x85\n", fn_8022F3D4(fn_8022F358(a)), b);
}

void GauntletMarkTeamBeaten(int a, int b)
{
    fn_801FCE10(0, "use \x8c update 'NUAG' set 'FDTG' = 1 where 'DIGT' = \x85\n", fn_8022F3D4(fn_8022F358(a)), b);
}

void GauntletClearTeamBeaten(int a, int b)
{
    fn_801FCE10(0, "use \x8c update 'NUAG' set 'FDTG' = 0 where 'DIGT' = \x85\n", fn_8022F3D4(fn_8022F358(a)), b);
}

int GauntletGetTeamsLeft(int a)
{
    int lttg;

    fn_801FCE10(0, "use \x8c select 'LTTG' into \x82 from 'MTTG'\n", fn_8022F3D4(fn_8022F358(a)), &lttg);
    return lttg;
}

void GauntletReset(int a)
{
    int i;

    for (i = 1; i <= 32; i++) {
        GauntletClearTeamBeaten(a, i);
    }
    GauntletResetTeamsLeft(a);
    GauntletClearTeamBeaten(a, 34);
    GauntletSetCurrentTeam(a, 1023);
    GauntletStatsReset(a);
}

void GauntletResetTeamsLeft(int a)
{
    fn_801FCE10(0, "use \x8c update 'MTTG' set 'LTTG' = 32\n", fn_8022F3D4(fn_8022F358(a)));
}

void GauntletAdvance(int a)
{
    int lttg = GauntletGetTeamsLeft(a) - 1;
    int digt = GauntletGetCurrentTeam(a);

    fn_801FCE10(0, "use \x8c update 'MTTG' set 'LTTG' = \x82 where 'DIGT' = \x85\n",
                fn_8022F3D4(fn_8022F358(a)), lttg, digt);
}

void GauntletStatsOpen(DbCursor *pObject, int a)
{
    DbCursorOpen(pObject, 0x41545347, 0x4E575347, 0, 0, fn_8022F3D4(fn_8022F358(a)));
}

void GauntletStatsClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int GauntletStatsGet(DbCursor *pObject, int index)
{
    switch (index) {
    case 0:
        return DbCursorGetInt(pObject, 0x4E575347);
    case 1:
        return DbCursorGetInt(pObject, 0x534C5347);
    case 14:
        return DbCursorGetValue(pObject, 0x54535347);
    case 13:
        return DbCursorGetInt(pObject, 0x46505347);
    case 2:
        return DbCursorGetInt(pObject, 0x50545347);
    case 3:
        return DbCursorGetInt(pObject, 0x54525347);
    case 4:
        return DbCursorGetInt(pObject, 0x54505347);
    case 5:
        return DbCursorGetInt(pObject, 0x54445347);
    case 6:
        return DbCursorGetInt(pObject, 0x53445347);
    case 7:
        return DbCursorGetInt(pObject, 0x41535347);
    case 8:
        return DbCursorGetInt(pObject, 0x49445347);
    case 9:
        return DbCursorGetInt(pObject, 0x46465347);
    case 11:
        return DbCursorGetInt(pObject, 0x42475347);
    case 12:
        return DbCursorGetInt(pObject, 0x32475347);
    case 10:
        return DbCursorGetInt(pObject, 0x44465347);
    }
    return -1;
}

void GauntletStatsAdd(DbCursor *pObject, int index, int delta)
{
    switch (index) {
    case 0:
        if (delta) {
            DbCursorSetInt(pObject, 0x4E575347, DbCursorGetInt(pObject, 0x4E575347) + 1);
            if (DbCursorGetValue(pObject, 0x54535347) < 0) {
                DbCursorSetValue(pObject, 0x54535347, 1);
            } else {
                DbCursorSetValue(pObject, 0x54535347, DbCursorGetValue(pObject, 0x54535347) + 1);
            }
        } else {
            DbCursorSetInt(pObject, 0x534C5347, DbCursorGetInt(pObject, 0x534C5347) + 1);
            if (DbCursorGetValue(pObject, 0x54535347) > 0) {
                DbCursorSetValue(pObject, 0x54535347, -1);
            } else {
                DbCursorSetValue(pObject, 0x54535347, DbCursorGetValue(pObject, 0x54535347) - 1);
            }
        }
        break;
    case 13:
        DbCursorSetInt(pObject, 0x46505347, DbCursorGetInt(pObject, 0x46505347) + delta);
        break;
    case 2:
        DbCursorSetInt(pObject, 0x50545347, DbCursorGetInt(pObject, 0x50545347) + delta);
        break;
    case 3:
        DbCursorSetInt(pObject, 0x54525347, DbCursorGetInt(pObject, 0x54525347) + delta);
        break;
    case 4:
        DbCursorSetInt(pObject, 0x54505347, DbCursorGetInt(pObject, 0x54505347) + delta);
        break;
    case 5:
        DbCursorSetInt(pObject, 0x54445347, DbCursorGetInt(pObject, 0x54445347) + delta);
        break;
    case 6:
        DbCursorSetInt(pObject, 0x53445347, DbCursorGetInt(pObject, 0x53445347) + delta);
        break;
    case 7:
        DbCursorSetInt(pObject, 0x41535347, DbCursorGetInt(pObject, 0x41535347) + delta);
        break;
    case 8:
        DbCursorSetInt(pObject, 0x49445347, DbCursorGetInt(pObject, 0x49445347) + delta);
        break;
    case 9:
        DbCursorSetInt(pObject, 0x46465347, DbCursorGetInt(pObject, 0x46465347) + delta);
        break;
    case 11:
        DbCursorSetInt(pObject, 0x42475347, DbCursorGetInt(pObject, 0x42475347) + delta);
        break;
    case 12:
        DbCursorSetInt(pObject, 0x32475347, DbCursorGetInt(pObject, 0x32475347) + delta);
        break;
    case 10:
        DbCursorSetInt(pObject, 0x44465347, DbCursorGetInt(pObject, 0x44465347) + delta);
        break;
    }
}

void GauntletStatsReset(int a)
{
    DbCursor object;

    GauntletStatsOpen(&object, a);
    DbCursorSetInt(&object, 0x4E575347, 0);
    DbCursorSetValue(&object, 0x54535347, 0);
    DbCursorSetInt(&object, 0x534C5347, 0);
    DbCursorSetValue(&object, 0x54535347, 0);
    DbCursorSetInt(&object, 0x46505347, 0);
    DbCursorSetInt(&object, 0x50545347, 0);
    DbCursorSetInt(&object, 0x54525347, 0);
    DbCursorSetInt(&object, 0x54505347, 0);
    DbCursorSetInt(&object, 0x54445347, 0);
    DbCursorSetInt(&object, 0x53445347, 0);
    DbCursorSetInt(&object, 0x41535347, 0);
    DbCursorSetInt(&object, 0x49445347, 0);
    DbCursorSetInt(&object, 0x46465347, 0);
    DbCursorSetInt(&object, 0x42475347, 0);
    DbCursorSetInt(&object, 0x32475347, 0);
    DbCursorSetInt(&object, 0x44465347, 0);
    GauntletStatsClose(&object);
}

void TkTableOpen(DbCursor *pObject, int type)
{
    switch (type) {
    case 0:
        DbCursorOpen(pObject, 0x54504B54, 0x44494B54, 0, 0, 0x54415453);
        break;
    case 1:
        DbCursorOpen(pObject, 0x43435054, 0x44494B54, 0, 0, 0x54415453);
        break;
    }
}

void TkTableClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int TkTableFindId(DbCursor *pObject, int id)
{
    return DbCursorFindInt(pObject, 0x44494B54, id, 0, 0);
}

void TkTableReadRow(DbCursor *pObject, StyleAwardRule_t *pRecord)
{
    pRecord->mEnabled = 1;
    pRecord->mApply = DbCursorGetInt(pObject, 0x50554B54);
    pRecord->mAllowZero = DbCursorGetInt(pObject, 0x565A4B54);
    pRecord->mPoints = DbCursorGetInt(pObject, 0x54504B54);
    pRecord->unk_0x8 = DbCursorGetInt(pObject, 0x42474B54);
    pRecord->mMeterSteal = DbCursorGetInt(pObject, 0x47534B54);
    pRecord->mScoreDelta = DbCursorGetValue(pObject, 0x43534B54);
    pRecord->mTableIndex = DbCursorGetInt(pObject, 0x54534B54);
    pRecord->mOpponentDistance = DbCursorGetFloat(pObject, 0x49444B54);
    pRecord->mOpponentAngle = DbCursorGetInt(pObject, 0x4E414B54);
    pRecord->mComboWeight = DbCursorGetInt(pObject, 0x4F434B54);
    pRecord->mAllowBehindLine = DbCursorGetInt(pObject, 0x4C424B54);
    pRecord->mCategory = DbCursorGetInt(pObject, 0x59544B54);
    pRecord->mComboLabel = DbCursorGetInt(pObject, 0x4E534B54);
    pRecord->mMessage = DbCursorGetInt(pObject, 0x4E4C4B54);
}
}
