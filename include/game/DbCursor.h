#ifndef GAME_DBCURSOR_H
#define GAME_DBCURSOR_H

struct DbCursor;

extern "C" {
int fn_801FA228(int handle, int a, int b, void *pRecord);
}

/* Argument of DbCursorOpen and DbCursorClose. The constructor sets the same
   values DbCursorClose stores at its end. */
struct DbCursor {
    DbCursor() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~DbCursor() {}
    int Read(void *pRecord) { return fn_801FA228(mUnknown0, 0, 0, pRecord); }

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    char mUnknown20[24];
};

/* One entry of the column list passed to fn_801FA228, which fills in mValue.
   The list ends with an entry whose mColumnTag is -1. */
struct DbColumnValue {
    void Set(int table, int column) { mColumnTag = column; mTableTag = table; }
    void Set(int table, int column, int value)
    {
        mTableTag = table;
        mColumnTag = column;
        mValue = value;
    }

    void SetEnd()
    {
        mColumnTag = -1;
        mTableTag = -1;
        mValue = 0;
    }

    int mValue;
    int mTableTag;
    int mColumnTag;
    int mUnknown12;
};

/* Eight-byte slot written either as a long long or as an int. */
union DbFilterValue {
    int mInt;
    long long mLong;
    struct DbFilter *mNode;
};

/* One operand of DbFilter: the slot and its kind. Kind 6 names a
   table and column (the table tag in the high word), 3 or 2 an integer and 11
   another DbFilter. */
struct DbFilterOperand {
    void Set(int kind, long long value)
    {
        mKind = kind;
        mValue.mLong = value;
    }
    void Set(int kind, int value)
    {
        mKind = kind;
        mValue.mInt = value;
    }
    void Set(int kind, DbFilter *pNode)
    {
        mKind = kind;
        mValue.mNode = pNode;
    }

    int mKind;
    DbFilterValue mValue;
};

/* Fifth argument of DbCursorOpen; it is stored at +28 of the cursor. Two
   operands and the operator word. */
struct DbFilter {
    /* Operator word 0x10003, the left operand (kind a, 64-bit value b) and
       the kind of the right operand. The Set overloads below take b by value
       and pass it on here. */
    void SetFilter(int a, const long long &b, int type)
    {
        mUnknown32 = 0x10003;
        mUnknown0.mKind = a;
        mUnknown0.mValue.mLong = b;
        mUnknown16.mKind = type;
    }
    void Set(int a, long long b, int type)
    {
        SetFilter(a, b, type);
    }
    void Set(int a, long long b, int type, int c)
    {
        SetFilter(a, b, type);
        mUnknown16.mValue.mInt = c;
    }
    void SetUnknown32(int a, long long b, int type, int unknown32)
    {
        mUnknown32 = unknown32;
        mUnknown0.mKind = a;
        DbFilterValue value;
        value.mLong = b;
        mUnknown0.mValue = value;
        mUnknown16.mKind = type;
    }
    void Set(int a, DbFilter *pLeft, DbFilter *pRight)
    {
        mUnknown32 = 0x20009;
        mUnknown0.mKind = a;
        mUnknown0.mValue.mNode = pLeft;
        mUnknown16.mKind = 11;
        mUnknown16.mValue.mNode = pRight;
    }
    /* Operand setters that leave mUnknown32 to the caller. */
    void SetOperands(int kind, long long column, int valueKind, int value)
    {
        mUnknown0.Set(kind, column);
        mUnknown16.Set(valueKind, value);
    }
    void SetOperands(int kind, long long column, int valueKind, long long value)
    {
        mUnknown0.Set(kind, column);
        mUnknown16.Set(valueKind, value);
    }
    void SetOperands(int kind, DbFilter *pLeft, DbFilter *pRight)
    {
        mUnknown0.Set(kind, pLeft);
        mUnknown16.Set(kind, pRight);
    }

    DbFilterOperand mUnknown0;
    DbFilterOperand mUnknown16;
    int mUnknown32;
};

/* Query passed to fn_80083E40; fn_80083E40 builds the same default when
   none is passed. */
struct TeamQuery {
    TeamQuery() : mUnknown0(1), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
void DbCursorOpenTable(DbCursor *pObject, int a, int b);
void DbCursorOpen(DbCursor *pObject, int a, int b, void *c, void *d, int e);
int DbCursorClose(DbCursor *pObject);
int DbCursorGetRowCount(DbCursor *pObject);
int DbCursorGetRow(DbCursor *pObject);
int DbCursorFirst(DbCursor *pObject);
int DbCursorLast(DbCursor *pObject);
int DbCursorNext(DbCursor *pObject);
int DbCursorPrev(DbCursor *pObject);
int DbCursorSeek(DbCursor *pObject, int a);
int DbCursorFindRow(DbCursor *pObject, DbColumnValue *pList, int next, int *pResult);
int DbCursorFindInt(DbCursor *pObject, int a, int b, int c, int *pResult);
int DbCursorFindValue(DbCursor *pObject, int a, int b, int c, int *pResult);
int DbCursorGetValue(DbCursor *pObject, int a);
int DbCursorGetInt(void *pObject, int a);
float DbCursorGetFloat(DbCursor *pObject, int a);
void DbCursorSetValue(DbCursor *pObject, int key, int value);
void DbCursorGetString(DbCursor *pObject, int a, int b, int c);
void DbCursorSetInt(void *pObject, int a, int b);
void DbCursorSetFloat(DbCursor *pObject, int a, float value);
void DbCursorSetString(void *pObject, int a, char *pText, int length);
void LogoListOpen(DbCursor *pObject);
void LogoListClose(DbCursor *pObject);
void LogoListGetName(DbCursor *pObject, char *pBuffer, int size);
int LogoListGetId(DbCursor *pObject);
void LogoListFind(DbCursor *pObject, int a, int *pResult);
void fn_80083E40(DbCursor *pObject, TeamQuery *pQuery, int tag);
void fn_80083F68(DbCursor *pObject);
void fn_80083F88(DbCursor *pObject, char *pBuffer, int size);
int fn_80084034(DbCursor *pObject, int id, int *pResult);
int fn_80084158(DbCursor *pObject);
int fn_80084438(DbCursor *pObject);
}

#endif
