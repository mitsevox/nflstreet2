/* Database cursor class over the game's database tables: opens a
   table of a database, moves between its rows and reads or updates single
   columns of the current row. Also holds the members of the cursor subclass
   that reads the 'FCHR' table. */
#include "game/DbTableCursor.h"
#include "game/FchrCursor.h"

DbTableCursor::DbTableCursor() {}

DbTableCursor::~DbTableCursor()
{
    if (mObject.mUnknown0 != 0) {
        CloseTable();
    }
}

void DbTableCursor::OpenTable(int a, int b, void *c, void *d, int e)
{
    DbCursorOpen(&mObject, a, b, c, d, e);
}

void DbTableCursor::CloseTable()
{
    DbCursorClose(&mObject);
}

int DbTableCursor::GetRowCount()
{
    return DbCursorGetRowCount(&mObject);
}

int DbTableCursor::GetRowIndex()
{
    return DbCursorGetRow(&mObject);
}

int DbTableCursor::MoveFirst()
{
    return DbCursorFirst(&mObject);
}

int DbTableCursor::MoveLast()
{
    return DbCursorLast(&mObject);
}

int DbTableCursor::MoveNext()
{
    return DbCursorNext(&mObject);
}

int DbTableCursor::MovePrev()
{
    return DbCursorPrev(&mObject);
}

int DbTableCursor::MoveToRow(int a)
{
    return DbCursorSeek(&mObject, a);
}

int DbTableCursor::FindColumnInt(int a, int b, int c, int *pResult)
{
    return DbCursorFindInt(&mObject, a, b, c, pResult);
}

int DbTableCursor::FindColumnValue(int a, int b, int c, int *pResult)
{
    return DbCursorFindValue(&mObject, a, b, c, pResult);
}

int DbTableCursor::GetColumnValue(int column)
{
    return DbCursorGetValue(&mObject, column);
}

int DbTableCursor::GetColumnInt(int column)
{
    return DbCursorGetInt(&mObject, column);
}

float DbTableCursor::GetColumnFloat(int column)
{
    return fn_8007A9E4(&mObject, column);
}

void DbTableCursor::GetColumnString(int a, int b, int c)
{
    fn_8007AA3C(&mObject, a, b, c);
}

void DbTableCursor::SetColumnValue(int column, int value)
{
    fn_8007AA90(&mObject, column, value);
}

void DbTableCursor::SetColumnInt(int column, int value)
{
    fn_8007ABA4(&mObject, column, value);
}

void DbTableCursor::SetColumnFloat(int column, float value)
{
    fn_8007ACB8(&mObject, column, value);
}

void DbTableCursor::SetColumnString(int column, char *pText, int length)
{
    fn_8007ADD4(&mObject, column, pText, length);
}

void FchrCursor::OpenFchrTable()
{
    OpenTable(0x52484346, -1, 0, 0, 0x54415453);
}

int FchrCursor::FindFchrRow(int id, int *pResult)
{
    return FindColumnValue(0x48464650, id, 0, pResult);
}

int FchrCursor::GetFchrPffh()
{
    return GetColumnValue(0x48464650);
}

void FchrCursor::GetFchrFhdcText(char *pBuffer, int size)
{
    GetColumnString(0x43444846, (int)pBuffer, size);
}

int FchrCursor::GetFchrFhstCode()
{
    switch (GetColumnValue(0x54534846)) {
    case 0:
        return 106;
    case 1:
        return 107;
    default:
        return 105;
    }
}
