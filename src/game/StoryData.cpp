/* Story progress: reads and writes the story-mode state kept in each user's
   save database: the flag word, the point totals, the completed-event list
   and the names of the story players, and starts a new story with a fresh
   team and default values. */
#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/DbCursor.h"
#include "game/StevTable.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8018C48C(int tag);
int StoryTeamCreate(void);
void StoryTeamCreatePlayer(int index, int a);
int TournamentOpen(int index);
int TournamentClearMatches(void);
int TournamentClearPlayers(void);
int TournamentClose(void);
void StoryPlayerSetDefaults(DbCursor *pCursor);

void StoryClearCompletedEvents(int index);
void StorySetNew(int index, int value);
void StorySetLkss(int index, int value);

static void _StoryReadFlags(int index, int *pFlags)
{
    fn_801FCE10(0, "use \x8c select 'GLFS' into \x85 from 'TADS'\n",
                fn_8022F3D4(fn_8022F358(index)), pFlags);
}

int StoryTestFlag(int index, int mask)
{
    int flags;
    int result = 0;

    _StoryReadFlags(index, &flags);
    if (flags & mask) {
        result = 1;
    }
    return result;
}

void StorySetFlag(int index, int mask, int set)
{
    int db = fn_8022F3D4(fn_8022F358(index));
    int flags;

    _StoryReadFlags(index, &flags);
    if (set) {
        flags |= mask;
    } else {
        flags &= ~mask;
    }
    fn_801FCE10(0, "use \x8c update 'TADS' set 'GLFS' = \x85\n", db, flags);
}

static int _StoryPlayerCursorIsEmpty(DbCursor *pCursor)
{
    return DbCursorGetRowCount(pCursor) == 0;
}

int StoryGetIndexedFlagMask(int n)
{
    switch (n) {
    case 0:
        return 0x20;
    case 1:
        return 0x40;
    case 2:
        return 0x80;
    }
    return 0;
}

void StoryPlayerCursorOpen(DbCursor *pCursor, int index)
{
    DbCursorOpen(pCursor, 0x59505453, 0x44494750, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void StoryPlayerCursorClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int StoryPlayerGetFirstName(DbCursor *pCursor, int row, char *pBuffer, int size)
{
    int ok;

    if (_StoryPlayerCursorIsEmpty(pCursor)) {
        *pBuffer = 0;
        ok = 0;
    } else {
        DbCursorSeek(pCursor, row);
        DbCursorGetString(pCursor, 0x414E4650, (int)pBuffer, size);
        ok = 1;
    }
    return ok;
}

int StoryPlayerGetLastName(DbCursor *pCursor, int row, char *pBuffer, int size)
{
    int ok;

    if (_StoryPlayerCursorIsEmpty(pCursor)) {
        *pBuffer = 0;
        ok = 0;
    } else {
        DbCursorSeek(pCursor, row);
        DbCursorGetString(pCursor, 0x414E4C50, (int)pBuffer, size);
        ok = 1;
    }
    return ok;
}

/* Writes the 'ANLP' text of the row, preceded by the first character of its
   'ANFP' text and ". " when that text is not empty. */
int StoryPlayerGetShortName(DbCursor *pCursor, int row, char *pName, int size)
{
    char first[12];
    char last[15];
    int ok;
    int length;

    if (_StoryPlayerCursorIsEmpty(pCursor)) {
        ok = 0;
    } else {
        ok = StoryPlayerGetFirstName(pCursor, row, first, sizeof(first));
        length = 0;
        if (ok) {
            ok = StoryPlayerGetLastName(pCursor, row, last, sizeof(last));
            if (ok) {
                if (strlen(first)) {
                    pName[0] = first[0];
                    pName[1] = '.';
                    pName[2] = ' ';
                    length = 3;
                }
                strcpy(pName + length, last);
            }
        }
    }
    return ok;
}

int StoryGetExpPoints(int index)
{
    int value = -1;

    fn_801FCE10(0, "use \x8c select 'PPXE' into \x82 from 'TADS'\n",
                fn_8022F3D4(fn_8022F358(index)), &value);
    return value;
}

void StorySetExpPoints(int index, int value)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'PPXE' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), value);
}

int StoryGetDevPoints(int index)
{
    int value = -1;

    fn_801FCE10(0, "use \x8c select 'PVED' into \x82 from 'TADS'\n",
                fn_8022F3D4(fn_8022F358(index)), &value);
    return value;
}

void StorySetDevPoints(int index, int value)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'PVED' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), value);
}

void StoryClearFlags(int index)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'GLFS' = \x85\n",
                fn_8022F3D4(fn_8022F358(index)), 0);
}

/* Deletes the 'YPTS' rows whose 'DIGP' is greater than 0, clears this file's 'TADS'
   and 'CETS' state and rewrites the defaults of the 'DIGP' 0 row. */
static void ResetYptsTadsCetsTables(void)
{
    DbCursor cursor;
    int index = fn_8022F384(fn_8022F4BC());

    fn_801FCE10(0, "use \x8c delete from 'YPTS' where 'DIGP' > 0\n", fn_8022F3D4(fn_8022F4BC()));
    StoryClearCompletedEvents(index);
    StorySetDevPoints(index, 250);
    StorySetExpPoints(index, 0);
    StoryClearFlags(index);
    StorySetNew(index, 1);
    StorySetLkss(index, -1);
    StoryPlayerCursorOpen(&cursor, index);
    if (DbCursorFindInt(&cursor, 0x44494750, 0, 0, 0)) {
        StoryPlayerSetDefaults(&cursor);
    }
    StoryPlayerCursorClose(&cursor);
    TournamentOpen(index);
    TournamentClearMatches();
    TournamentClearPlayers();
    TournamentClose();
}

int StoryStartNew(void)
{
    int index = fn_8022F384(fn_8022F4BC());
    int result;

    fn_8018C48C(0x54415453);
    result = StoryTeamCreate();
    StoryTeamCreatePlayer(index, result);
    StoryClearCompletedEvents(index);
    StorySetDevPoints(index, 250);
    StorySetExpPoints(index, 0);
    StoryClearFlags(index);
    StorySetNew(index, 1);
    StorySetLkss(index, -1);
    TournamentOpen(index);
    TournamentClearMatches();
    TournamentClearPlayers();
    TournamentClose();
    return result;
}

void StoryClearCompletedEvents(int index)
{
    fn_801FCE10(0, "use \x8c delete from 'CETS'\n", fn_8022F3D4(fn_8022F358(index)));
}

int StoryCountCompletedEvents(int index)
{
    int count;
    int result = -1;

    if (fn_801FCE10(0, "use \x8c select count(*) into \x82 from 'CETS'\n",
                    fn_8022F3D4(fn_8022F358(index)), &count) == 0) {
        result = count;
    }
    return result;
}

#if defined(DECOMP_COMPARE)
int StoryIsEventCompleted(int index, int id)
{
    int value;
    int found = 0;

    if (fn_801FCE10(0, "use \x8c select 'NETS' into \x82 from 'CETS' where 'NETS' = \x82\n",
                    fn_8022F3D4(fn_8022F358(index)), &value, id) == 0) {
        found = 1;
    }
    return found;
}

void StoryAddCompletedEvent(int index, int id)
{
    fn_801FCE10(0, "use \x8c insert into 'CETS' set 'NETS' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), id);
}

int StoryCountRemainingEvents(int index)
{
    return StevCountRows() - StoryCountCompletedEvents(index);
}

int StoryAreGroupEventsCompleted(int index, int a)
{
    StevRow_t row;
    int result = 1;
    unsigned int count = StevCountDiveRows(a);

    if (count) {
        unsigned int i;

        for (i = 0; i < count; i++) {
            if (StevGetRow(a, i, &row) && !StoryIsEventCompleted(index, row.mNets)) {
                result = 0;
                break;
            }
        }
    } else if (a == 11) {
        result = 0;
    }
    return result;
}

int StoryIsNew(int index)
{
    return !StoryTestFlag(index, 1);
}

void StorySetNew(int index, int value)
{
    StorySetFlag(index, 1, !value);
}

int StoryGetLkss(int index)
{
    int value;
    int result = -1;

    if (fn_801FCE10(0, "use \x8c select 'LKSS' into \x82 from 'TADS'\n",
                    fn_8022F3D4(fn_8022F358(index)), &value) == 0) {
        result = value;
    }
    return result;
}

void StorySetLkss(int index, int value)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'LKSS' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), value);
}

int StoryTestIndexedFlag(int index, int n)
{
    return StoryTestFlag(index, StoryGetIndexedFlagMask(n));
}

void StorySetIndexedFlag(int index, int n, int set)
{
    StorySetFlag(index, StoryGetIndexedFlagMask(n), set);
}

int StoryGetFlag100(int index)
{
    return !StoryTestFlag(index, 0x100);
}

void StorySetFlag100(int index, int value)
{
    StorySetFlag(index, 0x100, !value);
}

int StoryGetFlag200(int index)
{
    return !StoryTestFlag(index, 0x200);
}

void StorySetFlag200(int index, int value)
{
    StorySetFlag(index, 0x200, !value);
}
#endif
}
