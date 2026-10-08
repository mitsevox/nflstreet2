#ifndef GAME_OBJECT_8007A334_H
#define GAME_OBJECT_8007A334_H

struct Object_8007A334;

extern "C" {
int fn_801FA228(int handle, int a, int b, void *pRecord);
}

/* Argument of fn_8007A334 and fn_8007A3C4. The constructor sets the same
   values fn_8007A3C4 stores at its end. */
struct Object_8007A334 {
    Object_8007A334() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~Object_8007A334() {}
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
struct ColumnValue_802D6424 {
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
union Union_80023BBC {
    Union_80023BBC() {}
    Union_80023BBC(long long value) : mLong(value) {}

    int mInt;
    long long mLong;
    struct Object_80023BBC *mNode;
};

/* Fifth argument of fn_8007A334; it is stored at +28 of the cursor. */
struct Object_80023BBC {
    void Set(int a, long long b, int type)
    {
        mUnknown32 = 0x10003;
        mUnknown0 = a;
        mUnknown8 = b;
        mUnknown16 = type;
    }
    void Set(int a, long long b, int type, int c)
    {
        Set(a, b, type);
        mUnknown24.mInt = c;
    }
    void SetUnknown32(int a, long long b, int type, int unknown32)
    {
        mUnknown32 = unknown32;
        mUnknown0 = a;
        mUnknown8 = b;
        mUnknown16 = type;
    }
    void Set(int a, Object_80023BBC *pLeft, Object_80023BBC *pRight)
    {
        mUnknown32 = 0x20009;
        mUnknown0 = a;
        mUnknown8.mNode = pLeft;
        mUnknown16 = 11;
        mUnknown24.mNode = pRight;
    }

    int mUnknown0;
    Union_80023BBC mUnknown8;
    int mUnknown16;
    Union_80023BBC mUnknown24;
    int mUnknown32;
};

/* Query passed to fn_80083E40; fn_80083E40 builds the same default when
   none is passed. */
struct Query_80083E40 {
    Query_80083E40() : mUnknown0(1), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
void fn_8007A308(Object_8007A334 *pObject, int a, int b);
void fn_8007A334(Object_8007A334 *pObject, int a, int b, void *c, void *d, int e);
int fn_8007A3C4(Object_8007A334 *pObject);
int fn_8007A410(Object_8007A334 *pObject);
int fn_8007A43C(Object_8007A334 *pObject);
int fn_8007A444(Object_8007A334 *pObject);
int fn_8007A4A4(Object_8007A334 *pObject);
int fn_8007A510(Object_8007A334 *pObject);
int fn_8007A588(Object_8007A334 *pObject);
int fn_8007A600(Object_8007A334 *pObject, int a);
int fn_8007A690(Object_8007A334 *pObject, ColumnValue_802D6424 *pList, int next, int *pResult);
int fn_8007A7F4(Object_8007A334 *pObject, int a, int b, int c, int *pResult);
int fn_8007A894(Object_8007A334 *pObject, int a, int b, int c, int *pResult);
int fn_8007A934(Object_8007A334 *pObject, int a);
int fn_8007A98C(void *pObject, int a);
float fn_8007A9E4(Object_8007A334 *pObject, int a);
void fn_8007AA90(Object_8007A334 *pObject, int key, int value);
void fn_8007AA3C(Object_8007A334 *pObject, int a, int b, int c);
void fn_8007ABA4(void *pObject, int a, int b);
void fn_8007ACB8(Object_8007A334 *pObject, int a, float value);
void fn_8007ADD4(void *pObject, int a, char *pText, int length);
void fn_8007EEFC(Object_8007A334 *pObject);
void fn_8007F064(Object_8007A334 *pObject);
void fn_8007F094(Object_8007A334 *pObject, char *pBuffer, int size);
int fn_8007F0C8(Object_8007A334 *pObject);
void fn_8007F0F4(Object_8007A334 *pObject, int a, int *pResult);
void fn_80083E40(Object_8007A334 *pObject, Query_80083E40 *pQuery, int tag);
void fn_80083F68(Object_8007A334 *pObject);
void fn_80083F88(Object_8007A334 *pObject, char *pBuffer, int size);
int fn_80084034(Object_8007A334 *pObject, int id, int *pResult);
int fn_80084158(Object_8007A334 *pObject);
int fn_80084438(Object_8007A334 *pObject);
}

#endif
