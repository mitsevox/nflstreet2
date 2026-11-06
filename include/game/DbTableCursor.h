#ifndef GAME_DB_TABLE_CURSOR_H
#define GAME_DB_TABLE_CURSOR_H

#include "game/DbCursor.h"

/* Data-less polymorphic base of DbTableCursor, without a destructor of its
   own. It declares entries 1-17 of the vtable 0x802AB4F8, the slots before
   the destructor. */
class DbTableCursorBase {
public:
    virtual int GetRowCount() = 0;
    virtual int GetRowIndex() = 0;
    virtual int MoveFirst() = 0;
    virtual int MoveLast() = 0;
    virtual int MoveNext() = 0;
    virtual int MovePrev() = 0;
    virtual int MoveToRow(int a) = 0;
    virtual int FindColumnValue(int a, int b, int c, int *pResult) = 0;
    virtual int FindColumnInt(int a, int b, int c, int *pResult) = 0;
    virtual int GetColumnInt(int column) = 0;
    virtual int GetColumnValue(int column) = 0;
    virtual float GetColumnFloat(int column) = 0;
    virtual void GetColumnString(int a, int b, int c) = 0;
    virtual void SetColumnInt(int column, int value) = 0;
    virtual void SetColumnValue(int column, int value) = 0;
    virtual void SetColumnFloat(int column, float value) = 0;
    virtual void SetColumnString(int column, char *pText, int length) = 0;
};

/* Cursor object with vtable 0x802AB4F8: the vtable pointer at +0 and an
   DbCursor at +4 (48 bytes). Each virtual member passes &mObject and
   its arguments to one DbCursor function (vtable entry 1 0x8018FE34 to
   entry 17 0x80190074, then the destructor 0x8018FD94 and 0x8018FE10).
   The constructor 0x8018FD64 is declared out of line here; see
   game/Class_8018FD64Inline.h for the files that expand it inline. */
class DbTableCursor : public DbTableCursorBase {
public:
    DbTableCursor();
    void OpenTable(int a, int b, void *c, void *d, int e);

    virtual int GetRowCount();
    virtual int GetRowIndex();
    virtual int MoveFirst();
    virtual int MoveLast();
    virtual int MoveNext();
    virtual int MovePrev();
    virtual int MoveToRow(int a);
    virtual int FindColumnValue(int a, int b, int c, int *pResult);
    virtual int FindColumnInt(int a, int b, int c, int *pResult);
    virtual int GetColumnInt(int column);
    virtual int GetColumnValue(int column);
    virtual float GetColumnFloat(int column);
    virtual void GetColumnString(int a, int b, int c);
    virtual void SetColumnInt(int column, int value);
    virtual void SetColumnValue(int column, int value);
    virtual void SetColumnFloat(int column, float value);
    virtual void SetColumnString(int column, char *pText, int length);
    virtual ~DbTableCursor();
    virtual void CloseTable();

private:
    DbCursor mObject;
};

#endif
