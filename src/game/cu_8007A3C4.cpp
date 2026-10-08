#include "game/Object_8007A334.h"
#include "game/fn_801D2B7C.h"

extern "C" {
int fn_8007A934(Object_8007A334 *pCursor, int column);
int fn_801FA148(int cursor);
int fn_801FA1C0(int cursor, unsigned short *pCount);

int fn_8007A3C4(Object_8007A334 *pCursor)
{
    int status = fn_801FA148(pCursor->mUnknown0);
    pCursor->mUnknown0 = 0;
    pCursor->mUnknown4 = 0;
    pCursor->mUnknown8 = -1;
    pCursor->mUnknown12 = -1;
    pCursor->mUnknown16 = -1;
    return status;
}

int fn_8007A410(Object_8007A334 *pCursor)
{
    unsigned short count;
    fn_801FA1C0(pCursor->mUnknown0, &count);
    return count;
}

int fn_8007A43C(Object_8007A334 *pCursor)
{
    return pCursor->mUnknown16;
}

int fn_8007A444(Object_8007A334 *pCursor)
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

int fn_8007A4A4(Object_8007A334 *pCursor)
{
    pCursor->mUnknown16 = -1;
    int result = 0;
    int status = fn_801FA228(pCursor->mUnknown0, 2, 0, 0);
    if (status != 20 && status != 21) {
        pCursor->mUnknown16 = fn_8007A410(pCursor) - 1;
        result = 1;
    }
    return result;
}

int fn_8007A510(Object_8007A334 *pCursor)
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

int fn_8007A588(Object_8007A334 *pCursor)
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

int fn_8007A600(Object_8007A334 *pCursor, int row)
{
    int result = 0;
    int status;
    if (row < 0) {
        pCursor->mUnknown16 = fn_8007A410(pCursor) + row;
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

int fn_8007A690(Object_8007A334 *pCursor, ColumnValue_802D6424 *pColumns,
                int next, int *pRow)
{
    int found = 0;
    unsigned int count = 0;
    int valid;
    if (!next) {
        valid = fn_8007A444(pCursor);
    } else {
        valid = fn_8007A510(pCursor);
    }
    if (valid) {
        for (ColumnValue_802D6424 *p = pColumns; p->mColumnTag != -1; p++) {
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
            valid = fn_8007A510(pCursor);
        }
        fn_801D2BD0(pValues);
    }
    if (pRow) {
        *pRow = pCursor->mUnknown16;
    }
    return found;
}

int fn_8007A7F4(Object_8007A334 *pCursor, int column, int value, int next, int *pRow)
{
    int valid;
    if (!next) {
        valid = fn_8007A444(pCursor);
    } else {
        valid = fn_8007A510(pCursor);
    }
    while (valid && fn_8007A98C(pCursor, column) != value) {
        valid = fn_8007A510(pCursor);
    }
    if (pRow) {
        *pRow = pCursor->mUnknown16;
    }
    return valid;
}

int fn_8007A894(Object_8007A334 *pCursor, int column, int value, int next, int *pRow)
{
    int valid;
    if (!next) {
        valid = fn_8007A444(pCursor);
    } else {
        valid = fn_8007A510(pCursor);
    }
    while (valid && fn_8007A934(pCursor, column) != value) {
        valid = fn_8007A510(pCursor);
    }
    if (pRow) {
        *pRow = pCursor->mUnknown16;
    }
    return valid;
}

int fn_8007A934(Object_8007A334 *pCursor, int column)
{
    ColumnValue_802D6424 columns[2];
    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = 0;
    columns[1].SetEnd();
    fn_801FA228(pCursor->mUnknown0, 0, 0, columns);
    return columns[0].mValue;
}

int fn_8007A98C(void *pObject, int column)
{
    Object_8007A334 *pCursor = (Object_8007A334 *)pObject;
    ColumnValue_802D6424 columns[2];
    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = 0;
    columns[1].SetEnd();
    fn_801FA228(pCursor->mUnknown0, 0, 0, columns);
    return columns[0].mValue;
}

}
