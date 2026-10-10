#include "game/Object_8007A334.h"
#include "game/Table_8007E020.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_801FA0BC(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter, void *pSort, int *pCursor,
                QueryResult *pResult);
int fn_801FA148(int cursor);

void fn_8007A24C(int handle)
{
    Table_8007E020 tables[2];
    QueryResult result;
    ColumnValue_802D6424 columns[2];
    int cursor = 0;

    tables[0].Set(0x52455653);
    tables[1].Set(-1);
    fn_801FA0BC(handle, tables, 0, 0, &cursor, &result);
    columns[0].Set(0x52455653, 0x52455653);
    columns[0].mValue = 0;
    columns[1].Set(-1, -1);
    columns[1].mValue = 0;
    fn_801FA228(cursor, 1, 0, columns);
    if (columns[0].mValue != 0xB2A) {
        *(char *)0 = 0;
    }
    fn_801FA148(cursor);
}

void fn_8007A308(Object_8007A334 *pObject, int a, int b)
{
    fn_8007A334(pObject, a, b, 0, 0, 0);
}

void fn_8007A334(Object_8007A334 *pObject, int a, int b, void *c, void *d, int e)
{
    Table_8007E020 *tables = (Table_8007E020 *)pObject->mUnknown20;
    QueryResult result;

    pObject->mUnknown4 = e;
    pObject->mUnknown12 = b;
    pObject->mUnknown8 = a;
    tables[0].Set(a, 2, (Object_80023BBC *)d);
    tables[1].Set(-1);
    fn_801FA0BC(pObject->mUnknown4, tables, 0, c, &pObject->mUnknown0, &result);
    if (result.mUnknown0 != 0) {
        pObject->mUnknown16 = 0;
    } else {
        pObject->mUnknown16 = -1;
    }
}
}
