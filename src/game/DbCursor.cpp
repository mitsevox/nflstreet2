/* The DbCursor helpers every game-database wrapper uses: close a cursor, count rows, move to the
   first, last, next or previous row, seek a row, find a row by column values, and read a column of
   the current row. */

#include "game/DbCursor.h"
#include "game/fn_801D2B7C.h"

extern "C" {
int DbCursorGetValue(DbCursor *pCursor, int column);
int fn_801FA148(int cursor);
int fn_801FA1C0(int cursor, unsigned short *pCount);

int DbCursorClose(DbCursor *pCursor)
{
    int status = fn_801FA148(pCursor->mUnknown0);
    pCursor->mUnknown0 = 0;
    pCursor->mUnknown4 = 0;
    pCursor->mUnknown8 = -1;
    pCursor->mUnknown12 = -1;
    pCursor->mUnknown16 = -1;
    return status;
}

int DbCursorGetRowCount(DbCursor *pCursor)
{
    unsigned short count;
    fn_801FA1C0(pCursor->mUnknown0, &count);
    return count;
}

int DbCursorGetRow(DbCursor *pCursor)
{
    return pCursor->mUnknown16;
}

int DbCursorFirst(DbCursor *pCursor)
{
    pCursor->mUnknown16 = -1;
    int result = 0;
    int status = fn_801FA228(pCursor->mUnknown0, 1, 0, 0);
    if (status != 20 && status != 21) {
        pCursor->mUnknown16 = 0;
        result = 1;
    }
    return result;
}

int DbCursorLast(DbCursor *pCursor)
{
    pCursor->mUnknown16 = -1;
    int result = 0;
    int status = fn_801FA228(pCursor->mUnknown0, 2, 0, 0);
    if (status != 20 && status != 21) {
        pCursor->mUnknown16 = DbCursorGetRowCount(pCursor) - 1;
        result = 1;
    }
    return result;
}

int DbCursorNext(DbCursor *pCursor)
{
    int result = 0;
    if (pCursor->mUnknown16 != -1) {
        int status = fn_801FA228(pCursor->mUnknown0, 0, 1, 0);
        if (status != 20 && status != 21) {
            pCursor->mUnknown16++;
            result = 1;
        } else {
            pCursor->mUnknown16 = -1;
        }
    }
    return result;
}

int DbCursorPrev(DbCursor *pCursor)
{
    int result = 0;
    if (pCursor->mUnknown16 != -1) {
        int status = fn_801FA228(pCursor->mUnknown0, 0, -1, 0);
        if (status != 20 && status != 21) {
            pCursor->mUnknown16--;
            result = 1;
        } else {
            pCursor->mUnknown16 = -1;
        }
    }
    return result;
}

int DbCursorSeek(DbCursor *pCursor, int row)
{
    int result = 0;
    int status;
    if (row < 0) {
        pCursor->mUnknown16 = DbCursorGetRowCount(pCursor) + row;
        status = fn_801FA228(pCursor->mUnknown0, 2, row + 1, 0);
    } else {
        pCursor->mUnknown16 = row;
        status = fn_801FA228(pCursor->mUnknown0, 1, row, 0);
    }
    if (status != 20 && status != 21) {
        result = 1;
    } else {
        pCursor->mUnknown16 = -1;
    }
    return result;
}

int DbCursorFindRow(DbCursor *pCursor, DbColumnValue *pColumns,
                int next, int *pRow)
{
    int found = 0;
    unsigned int count = 0;
    int valid;
    if (!next) {
        valid = DbCursorFirst(pCursor);
    } else {
        valid = DbCursorNext(pCursor);
    }
    if (valid) {
        for (DbColumnValue *p = pColumns; p->mColumnTag != -1; p++) {
            count++;
        }
        int *pValues = (int *)fn_801D2B7C(count * sizeof(int), 0, 0);
        unsigned int i;
        for (i = 0; i < count; i++) {
            pValues[i] = pColumns[i].mValue;
        }
        while (valid) {
            fn_801FA228(pCursor->mUnknown0, 0, 0, pColumns);
            found = 1;
            for (i = 0; i < count; i++) {
                if (pValues[i] != pColumns[i].mValue) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                break;
            }
            valid = DbCursorNext(pCursor);
        }
        fn_801D2BD0(pValues);
    }
    if (pRow) {
        *pRow = pCursor->mUnknown16;
    }
    return found;
}

int DbCursorFindInt(DbCursor *pCursor, int column, int value, int next, int *pRow)
{
    int valid;
    if (!next) {
        valid = DbCursorFirst(pCursor);
    } else {
        valid = DbCursorNext(pCursor);
    }
    while (valid && DbCursorGetInt(pCursor, column) != value) {
        valid = DbCursorNext(pCursor);
    }
    if (pRow) {
        *pRow = pCursor->mUnknown16;
    }
    return valid;
}

int DbCursorFindValue(DbCursor *pCursor, int column, int value, int next, int *pRow)
{
    int valid;
    if (!next) {
        valid = DbCursorFirst(pCursor);
    } else {
        valid = DbCursorNext(pCursor);
    }
    while (valid && DbCursorGetValue(pCursor, column) != value) {
        valid = DbCursorNext(pCursor);
    }
    if (pRow) {
        *pRow = pCursor->mUnknown16;
    }
    return valid;
}

int DbCursorGetValue(DbCursor *pCursor, int column)
{
    DbColumnValue columns[2];
    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = 0;
    columns[1].SetEnd();
    fn_801FA228(pCursor->mUnknown0, 0, 0, columns);
    return columns[0].mValue;
}

int DbCursorGetInt(void *pObject, int column)
{
    DbCursor *pCursor = (DbCursor *)pObject;
    DbColumnValue columns[2];
    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = 0;
    columns[1].SetEnd();
    fn_801FA228(pCursor->mUnknown0, 0, 0, columns);
    return columns[0].mValue;
}

}
