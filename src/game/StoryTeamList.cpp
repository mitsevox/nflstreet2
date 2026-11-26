/* Rebuilds the story team list after the player saves a team. */

#include "game/fn_801D2B7C.h"
#include "game/TDbCompilePerformOp.h"

extern "C" {
int DbFileTblLoad(int a, int tag);
int DbFileTblDestroy(int a, int tag);
int DbUserGetDb(int a);
int DbUserGetCurrent(void);
int SyncRandGetIntRange(int stream, int low, int high);

void SstlRebuildForTeam(int teamId)
{
    QueryCursor cursor;
    char name[40];
    int count = 0;
    int value = 9;
    int lglt;
    int i;

    DbFileTblLoad(0, 0x43544E52);
    TDbCompilePerformOp(0, "select count(*) into \x82 from 'CTNR'\n", &count);
    int *pOrder = (int *)fn_801D2B7C(count * 4, 0, 0);
    int *pRow = pOrder;
    for (i = 0; i < count; ++i, ++pRow) {
        *pRow = i;
    }
    for (int i = 0; i < count * 8; i++) {
        int a = SyncRandGetIntRange(1, 0, count - 1);
        int b = SyncRandGetIntRange(1, 0, count - 1);
        int temp = pOrder[a];
        pOrder[a] = pOrder[b];
        pOrder[b] = temp;
    }

    int handle = DbUserGetDb(DbUserGetCurrent());
    TDbCompilePerformOp(0, "use \x8c select 'LGLT' into \x82 from 'METS' where 'DIGT' = \x82\n", handle, &value, teamId);
    int last = count - 1;
    for (i = 0; i < count && last >= 0; i++) {
        if (pOrder[i] == value) {
            int temp = pOrder[last];
            pOrder[last] = pOrder[i];
            pOrder[i] = temp;
            last--;
        }
    }

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'CTNR'\n", &cursor);
    TDbCompilePerformOp(0, "use \x8c delete from 'LTSS'\n", handle);
    for (int i = 0; i < count; i++) {
        cursor.mUnknown4 = pOrder[i];
        TDbCompilePerformOp(0, "fetch from \x8a 'LGLT' into \x82 and 'ETNR' into \x88\n", &cursor, &lglt, name);
        TDbCompilePerformOp(0, "use \x8c insert into 'LTSS' set 'LGLT' = \x82 and 'ETNR' = \x88\n", handle, lglt, name);
    }
    if (cursor.mUnknown0) TDbSQLDestroyCursor(&cursor);
    fn_801D2BD0(pOrder);
    DbFileTblDestroy(0, 0x43544E52);
}
}
