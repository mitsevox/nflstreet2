#include "game/DbCursor.h"
#include "game/DbSortKey.h"

extern "C" {
unsigned char fn_8007AFDC(int team);
int fn_8007B324(void);
int fn_80188030(int value);
void fn_801F9718(int handle, int table, DbColumnValue *pList, int *pResult, int flags);
int fn_801F9A90(int handle, int table);
}

static DbSortKey sColumns_802D6518[2] = {
    {0x4F434D54, 0x6469676C, 0, 0},
    {-1, -1, 3, 0}
};
static DbSortKey sColumns_802D6538[2] = {
    {0x58544145, 0x58494E53, 0, 0},
    {-1, -1, 3, 0}
};

extern "C" {

void fn_8007AEE8(DbCursor *pCursor)
{
    DbCursorOpenTable(pCursor, 0x4F434D54, -1);
}

void fn_8007AF14(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int fn_8007AF34(DbCursor *pCursor)
{
    return DbCursorGetValue(pCursor, 0x6469676C);
}

int fn_8007AF5C(DbCursor *pCursor)
{
    return DbCursorGetValue(pCursor, 0x554E4C53);
}

int fn_8007AF84(int team)
{
    int result;
    if (fn_8007B324()) {
        result = fn_8007AFDC(team) != 0;
    } else {
        result = team == 0;
    }
    return result;
}

unsigned char fn_8007AFDC(int team)
{
    DbCursor cursor;
    unsigned char count = 0;
    fn_8007AEE8(&cursor);
    int valid = DbCursorFirst(&cursor);
    while (valid) {
        int value = fn_8007AF34(&cursor);
        if (fn_8007AF5C(&cursor) == team && fn_80188030(value) != -1) {
            count++;
        }
        valid = DbCursorNext(&cursor);
    }
    fn_8007AF14(&cursor);
    return count;
}

unsigned char fn_8007B090(int team)
{
    DbCursor cursor;
    unsigned char result = 255;
    DbCursorOpen(&cursor, 0x4F434D54, 0x6469676C, sColumns_802D6518, 0, 0x454D4147);
    if (DbCursorFindInt(&cursor, 0x554E4C53, team, 0, 0)) {
        result = DbCursorGetInt(&cursor, 0x6469676C);
    }
    DbCursorClose(&cursor);
    return result;
}

void fn_8007B14C(int key, int value)
{
    DbCursor cursor;
    DbCursor *pCursor = &cursor;
    DbCursorOpen(pCursor, 0x4C525443, 0x6469676C, 0, 0, 0x454D4147);
    if (!DbCursorFindValue(pCursor, 0x6469676C, key, 0, 0)) {
        DbColumnValue columns[4];
        int result[4];
        columns[0].mColumnTag = 0x6469676C;
        columns[0].mTableTag = 0x4C525443;
        columns[0].mValue = key;
        columns[1].mColumnTag = 0x44494755;
        columns[1].mTableTag = 0x4C525443;
        columns[1].mValue = 0;
        columns[2].mColumnTag = 0x44494750;
        columns[2].mTableTag = 0x4C525443;
        columns[2].mValue = value;
        columns[3].SetEnd();
        fn_801F9718(pCursor->mUnknown4, pCursor->mUnknown8, columns, result, 0);
    } else {
        DbCursorSetValue(pCursor, 0x44494750, value);
    }
    DbCursorClose(&cursor);
}

int fn_8007B270(int key)
{
    int result = -1;
    DbCursor cursor;
    DbCursorOpen(&cursor, 0x4C525443, 0x6469676C, 0, 0, 0x454D4147);
    if (DbCursorFindValue(&cursor, 0x6469676C, key, 0, 0)) {
        result = DbCursorGetValue(&cursor, 0x44494750);
    }
    DbCursorClose(&cursor);
    return result;
}

int fn_8007B324(void)
{
    return fn_801F9A90(0, 0x4F434D54) == 0;
}

void fn_8007B358(DbCursor *pCursor)
{
    DbCursorOpen(pCursor, 0x58544145, 0x58494E53, sColumns_802D6538, 0, 0x54415453);
}

void fn_8007B3AC(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

void fn_8007B3CC(DbCursor *pCursor, int key, int *pRow)
{
    DbCursorFindInt(pCursor, 0x44494E53, key, 0, pRow);
}

int fn_8007B404(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x44494E53);
}

void fn_8007B42C(DbCursor *pCursor, char *pText, int length)
{
    DbCursorGetString(pCursor, 0x52414E53, (int)pText, length);
}

void fn_8007B460(DbCursor *pCursor, char *pText, int length)
{
    DbCursorGetString(pCursor, 0x49544E53, (int)pText, length);
}

void fn_8007B494(DbCursor *pCursor, char *pText, int length)
{
    DbCursorGetString(pCursor, 0x4C414E53, (int)pText, length);
}

}
