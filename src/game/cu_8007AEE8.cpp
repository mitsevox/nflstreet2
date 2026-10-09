#include "game/Object_8007A334.h"
#include "game/Key_8007A334.h"

extern "C" {
unsigned char fn_8007AFDC(int team);
int fn_8007B324(void);
int fn_80188030(int value);
void fn_801F9718(int handle, int table, ColumnValue_802D6424 *pList, int *pResult, int flags);
int fn_801F9A90(int handle, int table);
}

static Key_8007A334 sColumns_802D6518[2] = {
    {0x4F434D54, 0x6469676C, 0, 0},
    {-1, -1, 3, 0}
};
static Key_8007A334 sColumns_802D6538[2] = {
    {0x58544145, 0x58494E53, 0, 0},
    {-1, -1, 3, 0}
};

extern "C" {

void fn_8007AEE8(Object_8007A334 *pCursor)
{
    fn_8007A308(pCursor, 0x4F434D54, -1);
}

void fn_8007AF14(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int fn_8007AF34(Object_8007A334 *pCursor)
{
    return fn_8007A934(pCursor, 0x6469676C);
}

int fn_8007AF5C(Object_8007A334 *pCursor)
{
    return fn_8007A934(pCursor, 0x554E4C53);
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
    Object_8007A334 cursor;
    unsigned char count = 0;
    fn_8007AEE8(&cursor);
    int valid = fn_8007A444(&cursor);
    while (valid) {
        int value = fn_8007AF34(&cursor);
        if (fn_8007AF5C(&cursor) == team && fn_80188030(value) != -1) {
            count++;
        }
        valid = fn_8007A510(&cursor);
    }
    fn_8007AF14(&cursor);
    return count;
}

unsigned char fn_8007B090(int team)
{
    Object_8007A334 cursor;
    unsigned char result = 255;
    fn_8007A334(&cursor, 0x4F434D54, 0x6469676C, sColumns_802D6518, 0, 0x454D4147);
    if (fn_8007A7F4(&cursor, 0x554E4C53, team, 0, 0)) {
        result = fn_8007A98C(&cursor, 0x6469676C);
    }
    fn_8007A3C4(&cursor);
    return result;
}

void fn_8007B14C(int key, int value)
{
    Object_8007A334 cursor;
    Object_8007A334 *pCursor = &cursor;
    fn_8007A334(pCursor, 0x4C525443, 0x6469676C, 0, 0, 0x454D4147);
    if (!fn_8007A894(pCursor, 0x6469676C, key, 0, 0)) {
        ColumnValue_802D6424 columns[4];
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
        fn_8007AA90(pCursor, 0x44494750, value);
    }
    fn_8007A3C4(&cursor);
}

int fn_8007B270(int key)
{
    int result = -1;
    Object_8007A334 cursor;
    fn_8007A334(&cursor, 0x4C525443, 0x6469676C, 0, 0, 0x454D4147);
    if (fn_8007A894(&cursor, 0x6469676C, key, 0, 0)) {
        result = fn_8007A934(&cursor, 0x44494750);
    }
    fn_8007A3C4(&cursor);
    return result;
}

int fn_8007B324(void)
{
    return fn_801F9A90(0, 0x4F434D54) == 0;
}

void fn_8007B358(Object_8007A334 *pCursor)
{
    fn_8007A334(pCursor, 0x58544145, 0x58494E53, sColumns_802D6538, 0, 0x54415453);
}

void fn_8007B3AC(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

void fn_8007B3CC(Object_8007A334 *pCursor, int key, int *pRow)
{
    fn_8007A7F4(pCursor, 0x44494E53, key, 0, pRow);
}

int fn_8007B404(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x44494E53);
}

void fn_8007B42C(Object_8007A334 *pCursor, char *pText, int length)
{
    fn_8007AA3C(pCursor, 0x52414E53, (int)pText, length);
}

void fn_8007B460(Object_8007A334 *pCursor, char *pText, int length)
{
    fn_8007AA3C(pCursor, 0x49544E53, (int)pText, length);
}

void fn_8007B494(Object_8007A334 *pCursor, char *pText, int length)
{
    fn_8007AA3C(pCursor, 0x4C414E53, (int)pText, length);
}

}
