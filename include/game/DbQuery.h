#ifndef GAME_DBQUERY_H
#define GAME_DBQUERY_H

#include "game/DbCursor.h"

/* Left operand, right operand and the comparison fn_801FA428 applies. */
struct DbExpression {
    int mLeftType;
    int mUnknown4;
    union {
        unsigned long long mColumnId;
        int mLeftValue;
    };
    int mRightType;
    int mUnknown20;
    union {
        int mValue;
        unsigned long long mUnknown24;
    };
    int mOperator;

    void Set(unsigned long long column, int op, int value)
    {
        mOperator = op;
        mColumnId = column;
        mLeftType = 6;
        mRightType = 3;
        mValue = value;
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
