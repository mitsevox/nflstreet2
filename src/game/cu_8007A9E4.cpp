#include "game/DbCursor.h"
#include "game/Query_8007F19C.h"

extern "C" {

float fn_8007A9E4(DbCursor *pCursor, int column)
{
    DbColumnValue columns[2];
    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = 0;
    columns[1].SetEnd();
    pCursor->Read(columns);
    return *(float *)&columns[0].mValue;
}

void fn_8007AA3C(DbCursor *pCursor, int column, int buffer, int length)
{
    DbColumnValue columns[2];
    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = buffer;
    columns[1].SetEnd();
    pCursor->Read(columns);
}

void fn_8007AA90(DbCursor *pCursor, int column, int value)
{
    DbColumnValue columns[2];
    DbColumnValue *pList = columns;
    Expression_8007F19C expression;
    Result_8007F19C result;
    Table_8007F19C tables[2];
    DbColumnValue key[2];

    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = value;
    columns[1].SetEnd();
    key[0].Set(-1, pCursor->mUnknown12, 0);
    key[1].SetEnd();
    pCursor->Read(key);
    unsigned int table = pCursor->mUnknown8;
    unsigned int keyColumn = pCursor->mUnknown12;
    expression.Set(((unsigned long long)table << 32) | keyColumn,
                   0x00010003, key[0].mValue);
    tables[0].Set(pCursor->mUnknown8);
    tables[1].Set(-1);
    fn_801FA428(pCursor->mUnknown4, tables, &expression, pList, &result, 0);
}

void fn_8007ABA4(void *pObject, int column, int value)
{
    DbCursor *pCursor = (DbCursor *)pObject;
    DbColumnValue columns[2];
    DbColumnValue *pList = columns;
    Expression_8007F19C expression;
    Result_8007F19C result;
    Table_8007F19C tables[2];
    DbColumnValue key[2];

    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = value;
    columns[1].SetEnd();
    key[0].Set(-1, pCursor->mUnknown12, 0);
    key[1].SetEnd();
    pCursor->Read(key);
    unsigned int table = pCursor->mUnknown8;
    unsigned int keyColumn = pCursor->mUnknown12;
    expression.Set(((unsigned long long)table << 32) | keyColumn,
                   0x00010003, key[0].mValue);
    tables[0].Set(pCursor->mUnknown8);
    tables[1].Set(-1);
    fn_801FA428(pCursor->mUnknown4, tables, &expression, pList, &result, 0);
}

void fn_8007ACB8(DbCursor *pCursor, int column, float value)
{
    DbColumnValue columns[2];
    DbColumnValue *pList = columns;
    Expression_8007F19C expression;
    Result_8007F19C result;
    Table_8007F19C tables[2];
    DbColumnValue key[2];

    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = *(int *)&value;
    columns[1].SetEnd();
    key[0].Set(-1, pCursor->mUnknown12, 0);
    key[1].SetEnd();
    pCursor->Read(key);
    unsigned int table = pCursor->mUnknown8;
    unsigned int keyColumn = pCursor->mUnknown12;
    expression.Set(((unsigned long long)table << 32) | keyColumn,
                   0x00010003, key[0].mValue);
    tables[0].Set(pCursor->mUnknown8);
    tables[1].Set(-1);
    fn_801FA428(pCursor->mUnknown4, tables, &expression, pList, &result, 0);
}

void fn_8007ADD4(void *pObject, int column, char *pText, int length)
{
    DbCursor *pCursor = (DbCursor *)pObject;
    DbColumnValue columns[2];
    DbColumnValue *pList = columns;
    Expression_8007F19C expression;
    Result_8007F19C result;
    Table_8007F19C tables[2];
    DbColumnValue key[2];

    columns[0].mColumnTag = column;
    columns[0].mTableTag = -1;
    columns[0].mValue = (int)pText;
    columns[1].SetEnd();
    key[0].Set(-1, pCursor->mUnknown12, 0);
    key[1].SetEnd();
    pCursor->Read(key);
    unsigned int table = pCursor->mUnknown8;
    unsigned int keyColumn = pCursor->mUnknown12;
    expression.Set(((unsigned long long)table << 32) | keyColumn,
                   0x00010003, key[0].mValue);
    tables[0].Set(pCursor->mUnknown8);
    tables[1].Set(-1);
    fn_801FA428(pCursor->mUnknown4, tables, &expression, pList, &result, 0);
}

}
