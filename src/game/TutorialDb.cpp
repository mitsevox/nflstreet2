/* Tutorial lessons: the plays, side and field offset of each lesson step, lesson
   descriptions, and the per-profile step counters and completion flags of the five
   lessons. */

#include <string.h>

#include "game/PlayBookDb.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F3D4(int a);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int fn_801C302C(const char *s1, const char *s2, int n);
int TutorialIsComplete(int id);
void TutorialMarkComplete(int id);
}

/* _Tutorial_bPlaysOpen and _Tutorial_bInfoOpen: open flags of the 'LPUT' and 'FNIT' tables.
   _Tutorial_bAllComplete: set by TutorialMarkComplete when TutorialAllComplete succeeds after the
   'RUUT' update, read and cleared by TutorialTakeAllCompleteFlag. _Tutorial_iProfileDb: database index set by TutorialSetProfileDb (-1 when
   unset). */
static unsigned char _Tutorial_bPlaysOpen = 0;
static unsigned char _Tutorial_bInfoOpen = 0;
static unsigned char _Tutorial_bAllComplete = 0;
static int _Tutorial_iProfileDb = -1;

extern "C" {

unsigned char TutorialDbOpenPlays(void)
{
    unsigned char result = 1;

    if (!_Tutorial_bPlaysOpen) {
        if (fn_8022EF8C(0, 0x4C505554)) {
            _Tutorial_bPlaysOpen = 0;
            result = 0;
        } else {
            _Tutorial_bPlaysOpen = 1;
        }
    }
    return result;
}

unsigned char TutorialDbOpenInfo(void)
{
    unsigned char result = 1;

    if (!_Tutorial_bInfoOpen) {
        if (fn_8022EF8C(0, 0x464E4954)) {
            _Tutorial_bInfoOpen = 0;
            result = 0;
        } else {
            _Tutorial_bInfoOpen = 1;
        }
    }
    return result;
}

unsigned char TutorialDbCloseInfo(void)
{
    unsigned char result = 1;

    if (_Tutorial_bInfoOpen) {
        result = fn_8022EFBC(0, 0x464E4954) == 0;
        _Tutorial_bInfoOpen = 0;
    }
    return result;
}

unsigned char TutorialDbClosePlays(void)
{
    unsigned char result = 1;

    if (_Tutorial_bPlaysOpen) {
        result = fn_8022EFBC(0, 0x4C505554) == 0;
        _Tutorial_bPlaysOpen = 0;
    }
    return result;
}

int TutorialGetStepCount(int id)
{
    int value = 0;

    if (_Tutorial_iProfileDb != -1) {
        fn_801FCE10(0, "use \x8c select 'GCUT' into \x82 from 'RUUT' where 'NCUT' = \x82\n",
                    fn_8022F3D4(_Tutorial_iProfileDb), &value, id);
    }
    return value;
}

void TutorialSetStepCount(unsigned int id, unsigned int count)
{
    unsigned int limit = 0;
    int update = 1;
    unsigned char set = TutorialIsComplete(id);
    unsigned int value = count;

    switch (id) {
    case 0:
        limit = 7;
        break;
    case 2:
        limit = 8;
        break;
    case 3:
        limit = 6;
        break;
    case 1:
    case 4:
        limit = 9;
        break;
    }

    if (set) {
        update = 0;
    } else if (count >= limit) {
        value = 0;
        TutorialMarkComplete(id);
    }

    if (update) {
        fn_801FCE10(0, "use \x8c update 'RUUT' set 'GCUT' = \x82 where 'NCUT' = \x82\n",
                    fn_8022F3D4(_Tutorial_iProfileDb), value, id);
    }
}

int TutorialAllComplete(void)
{
    int count = TutorialIsComplete(0);

    count += TutorialIsComplete(1);
    count += TutorialIsComplete(2);
    count += TutorialIsComplete(3);
    count += TutorialIsComplete(4);
    return count == 5;
}

int TutorialIsComplete(int id)
{
    int value = 0;

    if (_Tutorial_iProfileDb != -1) {
        int db = fn_8022F3D4(_Tutorial_iProfileDb);
        if (db != -1) {
            fn_801FCE10(0, "use \x8c select 'MCUT' into \x82 from 'RUUT' where 'NCUT' = \x82\n", db, &value, id);
        }
    }
    return value;
}

void TutorialMarkComplete(int id)
{
    int db = fn_8022F3D4(_Tutorial_iProfileDb);

    if (db != -1) {
        int value = 0;
        fn_801FCE10(0, "use \x8c select 'MCUT' into \x85 from 'RUUT' where 'NCUT' = \x85\n", db, &value, id);
        if (value == 0) {
            fn_801FCE10(0, "use \x8c update 'RUUT' set 'MCUT' = \x82 where 'NCUT' = \x82\n", db, 1, id);
            if (TutorialAllComplete()) {
                _Tutorial_bAllComplete = 1;
            }
        }
    }
}

void TutorialGetDescription(int id, char *pDest, int count)
{
    char buffer[80];

    fn_801FCE10(0, "select 'CSDT' into \x88 from 'FNIT' where 'DIDT' = \x82\n", buffer, id);
    strncpy(pDest, buffer, count);
}

unsigned int TutorialGetPlayIndex(int a, int b, int flag)
{
    PlayBookFormation_t table;
    char key[3];
    PlayBookPlay_t record;
    int id;
    int handle;
    int tag;
    int kind;
    unsigned int count;
    unsigned int i;

    fn_801FCE10(0, "select 'CUUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &id, a, b);
    if (flag) {
        tag = 0x31544250;
        kind = 1;
    } else {
        tag = 0x31444250;
        kind = 11;
    }
    PlayBookDbLoadFormation(tag, kind, 0, &table);
    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n", tag,
                &handle, 1, table.mUnknown0);
    count = PlayBookDbCountPlays(tag, handle);
    fn_801C2E18(key, "%02d", id);
    for (i = 0; i < count; i++) {
        PlayBookDbLoadPlay(tag, handle, i, &record);
        if (fn_801C302C(record.mUnknown1F0, key, 2) == 0) {
            break;
        }
    }
    return i;
}

unsigned int TutorialGetOtherPlayIndex(int a, int b, int flag)
{
    PlayBookFormation_t table;
    char key[3];
    PlayBookPlay_t record;
    int id;
    int handle;
    int tag;
    int kind;
    unsigned int count;
    unsigned int i;

    fn_801FCE10(0, "select 'PUUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &id, a, b);
    if (flag) {
        tag = 0x31444250;
        kind = 11;
    } else {
        tag = 0x31544250;
        kind = 1;
    }
    PlayBookDbLoadFormation(tag, kind, 0, &table);
    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n", tag,
                &handle, 1, table.mUnknown0);
    count = PlayBookDbCountPlays(tag, handle);
    fn_801C2E18(key, "%02d", id);
    for (i = 0; i < count; i++) {
        PlayBookDbLoadPlay(tag, handle, i, &record);
        if (fn_801C302C(record.mUnknown1F0, key, 2) == 0) {
            break;
        }
    }
    return i;
}

int TutorialGetStepSide(int a, int b)
{
    int value;

    fn_801FCE10(0, "select 'OPUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &value, a, b);
    return value;
}

float TutorialGetStepOffset(int a, int b)
{
    float value;

    fn_801FCE10(0, "select 'PSUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &value, a, b);
    return value;
}

unsigned char TutorialTakeAllCompleteFlag(void)
{
    unsigned char result = _Tutorial_bAllComplete;

    _Tutorial_bAllComplete = 0;
    return result;
}

void TutorialSetProfileDb(int db)
{
    _Tutorial_iProfileDb = db;
}

int TutorialGetProfileDb(void)
{
    return _Tutorial_iProfileDb;
}
}
