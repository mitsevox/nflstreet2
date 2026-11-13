#ifndef GAME_DBQUERY_H
#define GAME_DBQUERY_H

#include "game/DbCursor.h"

/* Condition fn_801FA428 applies: the same 40-byte DbFilter node that
   DbCursorOpen takes (left operand +0, right operand +0x10, operator word
   +0x20). This setter stores a table/column pair compared with an integer
   under a caller-given operator word. */
struct DbExpression : DbFilter {
    void Set(int a, long long b, int type, int c)
    {
        SetFilter(a, b, type);
        mUnknown16.mValue.mInt = c;
    }
    void Set(unsigned long long column, int op, int value)
    {
        mUnknown32 = op;
        mUnknown0.mValue.mLong = column;
        mUnknown0.mKind = 6;
        mUnknown16.mKind = 3;
        mUnknown16.mValue.mInt = value;
    }
};

/* One entry of the table list fn_801FA428 walks; the list ends with mTag -1. */
struct DbTableRef {
    void Set(int tag, int type = 2, DbExpression *filter = 0)
    {
        mFilter = filter;
        mTag = tag;
        mUnknown4 = type;
    }

    int mTag;
    int mUnknown4;
    DbExpression *mFilter;
};

/* Output of fn_801FA428, which reports a row count in the halfword at +0 and a
   status word at +4. The functions here reserve it and read neither. */
struct DbQueryResult {
    unsigned short mCount;
    int mStatus;
    char mUnknown8[8];
};

extern "C" int fn_801FA428(int, DbTableRef *, DbExpression *, DbColumnValue *, DbQueryResult *, int);

#endif
