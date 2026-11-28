/* The store's item database: looks up the gear, decal, logo, hair and tattoo items of a store
   category with their names and prices, counts and walks the ones the user has unlocked, reads and
   clears their lock and new flags in the user's profile, and creates or deletes the store's own
   team. */
#include "game/DbCursor.h"
#include "game/DbQueryTable.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/TDbCompilePerformOp.h"

struct StoreCategory_t {
    unsigned int mTable;
    unsigned int mIdColumn;
    unsigned int mNameColumn;
    int mNameSize;
    unsigned int mPriceColumn;
    unsigned int mSortColumn;
    unsigned int mProfileTable;
    unsigned int mLockedColumn;
    int mLockedValue;
    unsigned int mNewColumn;
};

struct StoreSortKey_t {
    void Set(int table, int column, int mode)
    {
        mColumn = column;
        mTable = table;
        mMode = mode;
    }

    void SetEnd()
    {
        mTable = -1;
        mColumn = -1;
        mMode = 3;
    }

    int mTable;
    int mColumn;
    int mMode;
    unsigned char mUnknown12[4];
};

extern "C" {
int StoreGetTattooLocation(int index);
int TDbTblDestroy(int handle, int table);
void TDbInsertRow(int handle, int table, DbColumnValue *pList, int *pResult, int flags);
int TDbTblFindUnusedId(int handle, int *pTable);
int _TDbQrySelect(int handle, DbQueryTable *pTables, DbFilter *pFilter,
                void *pSort, int *pCursor, QueryResult *pResult);
int DbFindUnusedPlayerIds(int handle, int table, int *pIds, unsigned short *pCount);
int DbFindUnusedTeamIds(int handle, int table, int *pIds, unsigned short *pCount);
int DbFileTblLoad(int a, int tag);
int DbFileTblDestroy(int a, int tag);
int DbUserGetDb(int handle);
int DbUserGetCurrent(void);
}

static int _StoreDb_aTeamColumns[16] = {
    0x44494754, 0x44494F54, 0x50595454, 0x44524F54,
    0x45445254, 0x464F5254, 0x564F5254, 0x4C474C54,
    0x49524454, 0x31434D54, 0x32434D54, 0x33434D54,
    0x4C445443, 0x414E5354, 0x414E4C54, 0x414E4454
};
static const char *_StoreDb_apszTeamNames[3] = { "STO", "Store Team", "Store Team" };
static const int _StoreDb_aTeamDefaults[13] = { 0, 0, 5, 0, 0, 0, 0, 132, 0, 49, 42, 126, 1 };
static const StoreCategory_t _StoreDb_aCategories[5] = {
    { 0x52414547, 0x594B5047, 0x4D4E5247, 32, 0x43525047, 0x594B5047, 0x5245474C, 0x4B434C47, 1, 0x574E5247 },
    { 0x4C414344, 0x494C4344, 0x4E4C4344, 21, 0x504C4344, 0x494C4344, 0x4C43444C, 0x4C4C4344, 1, 0x574E5247 },
    { 0x4F474F4C, 0x4C474C54, 0x4D4E474C, 21, 0x50474F4C, 0x524F474C, 0x474C4B4C, 0x4B4C474C, 1, 0x574E5247 },
    { 0x52494148, 0x52414850, 0x4D4E5248, 26, 0x43525048, 0x524F5248, 0x4B434C48, 0x4B434C48, 1, 0x574E5247 },
    { 0x4F544154, 0x49544154, 0x4E544154, 21, 0x43525054, 0x524F5454, 0x4B434C54, 0x4B434C54, 1, 0x574E5247 }
};
static const signed char _StoreDb_aCategoryIndex[22] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 4, 4, 4
};
static unsigned char _StoreDb_bOpen = 0;

static inline unsigned long long MakeColumnKey(unsigned int table, unsigned int column)
{
    return ((unsigned long long)table << 32) | column;
}

extern "C" {

void StoreTeamAddPlayer(int team)
{
    QueryResult result;
    unsigned short count = 1;
    int player;
    int sourcePlayer;
    int table;
    DbFindUnusedPlayerIds(0x54415453, 0x59414C50, &player, &count);
    TDbCompilePerformOp(0, "use 'TATS' select 'DIGP' into \x85 from 'PRTS'\n", &sourcePlayer);
    TDbTblFindUnusedId(0x54415453, &table);
    TDbCompilePerformOp(&result, "use 'TATS' select into \x8c * from 'PRTS' where ('DIGP' = \x85)\n", table, sourcePlayer);
    TDbCompilePerformOp(&result, "use 'TATS' update \x8c set 'DIGT' = \x85 and 'DIGP' = \x85\n", table, team, player);
    TDbCompilePerformOp(&result, "use 'TATS' insert into 'YALP' * select * from \x8c\n", table);
    TDbTblDestroy(0x54415453, table);
}

const StoreCategory_t *StoreGetCategory(int index)
{
    return &_StoreDb_aCategories[_StoreDb_aCategoryIndex[index]];
}

int StoreGetItem(int index, int id, int byRow, int *pId, int *pPrice,
                char *pName, int nameSize)
{
    DbQueryTable tables[2];
    DbFilter priceFilter;
    DbFilter both;
    DbFilter categoryFilter;
    DbColumnValue columns[4];
    StoreSortKey_t sort[2];
    QueryResult queryResult;
    int cursor;
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int result = 0;
    char *pBuffer = 0;
    DbFilter *pFilter = &priceFilter;
    int column = 0;

    if (pName) {
        *pName = 0;
        pBuffer = (char *)fn_801D2B7C(pDescriptor->mNameSize, 0, 0);
        columns[column++].Set(pDescriptor->mTable, pDescriptor->mNameColumn, (int)pBuffer);
    }
    if (pId) {
        *pId = -1;
        columns[column++].Set(pDescriptor->mTable, pDescriptor->mIdColumn, 0);
    }
    if (pPrice) {
        *pPrice = -1;
        columns[column++].Set(pDescriptor->mTable, pDescriptor->mPriceColumn, 0);
    }
    columns[column].SetEnd();
    if (byRow) {
        priceFilter.SetUnknown32(6, MakeColumnKey(pDescriptor->mTable, pDescriptor->mPriceColumn), 2, 0x10004);
        priceFilter.mUnknown16.mValue.mInt = 0;
        if (pDescriptor->mTable == 0x52414547) {
            pFilter = &both;
            both.Set(11, &priceFilter, &categoryFilter);
            categoryFilter.Set(6, MakeColumnKey(pDescriptor->mTable, 0x49525453), 3, index);
        } else if (pDescriptor->mTable == 0x4F544154) {
            int category = StoreGetTattooLocation(index);
            pFilter = &both;
            both.Set(11, &priceFilter, &categoryFilter);
            categoryFilter.Set(6, MakeColumnKey(pDescriptor->mTable, 0x4C544154), 3, category);
        }
    } else {
        priceFilter.Set(6, MakeColumnKey(pDescriptor->mTable, pDescriptor->mIdColumn), 3, id);
    }
    tables[0].Set(pDescriptor->mTable, 2, pFilter);
    tables[1].Set(-1);
    if (byRow) {
        sort[0].Set(pDescriptor->mTable, pDescriptor->mSortColumn, 0);
        sort[1].SetEnd();
        if (_TDbQrySelect(0x54415453, tables, 0, sort, &cursor, &queryResult) == 0) {
            if (TDbQryRetrieve(cursor, 1, id, columns) == 0) {
                result = 1;
            }
        }
        TDbQryDestroy(cursor);
    } else {
        if (TDbQryGetSingleRow(0x54415453, tables, 0, columns) == 0) {
            result = 1;
        }
    }
    if (result) {
        column = 0;
        if (pName) {
            strnzcpy(pName, pBuffer, nameSize);
            column++;
        }
        if (pId) {
            *pId = columns[column++].mValue;
        }
        if (pPrice) {
            *pPrice = columns[column].mValue;
        }
    }
    if (pBuffer) {
        fn_801D2BD0(pBuffer);
    }
    return result;
}

static int _StoreGetStringById(int id, char *pName, int nameSize)
{
    char name[36];
    int result = 0;
    if (TDbCompilePerformOp(0, "select 'IUNS' into \x88 from 'MNTS' where 'IRTS' = \x85\n", name, id) == 0) {
        strncpy(pName, name, nameSize);
        result = 1;
    }
    return result;
}

int StoreCountItems(int index)
{
    DbFilter priceFilter;
    DbFilter both;
    DbFilter categoryFilter;
    unsigned short count;
    // FAKEMATCH: the price filter is set up through an alias taken before the call; it only steers the base register
    DbFilter *pPrice = &priceFilter;
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int result = 0;
    pPrice->SetOperands(6, MakeColumnKey(pDescriptor->mTable, pDescriptor->mPriceColumn), 2, 0);
    pPrice->mUnknown32 = 0x10004;
    DbFilter *pFilter = pPrice;
    if (pDescriptor->mTable == 0x52414547) {
        pFilter = &both;
        both.Set(11, &priceFilter, &categoryFilter);
        categoryFilter.Set(6, MakeColumnKey(pDescriptor->mTable, 0x49525453), 3, index);
    } else if (pDescriptor->mTable == 0x4F544154) {
        int category = StoreGetTattooLocation(index);
        pFilter = &both;
        both.Set(11, &priceFilter, &categoryFilter);
        categoryFilter.Set(6, MakeColumnKey(pDescriptor->mTable, 0x4C544154), 3, category);
    }
    if (TDbTblGetCount(0x54415453, pDescriptor->mTable, pFilter, &count) == 0) {
        result = count;
    }
    return result;
}

int StoreGetItemCount(int index)
{
    int result;
    if (!_StoreDb_bOpen) result = 0;
    else result = StoreCountItems(index);
    return result;
}

int StoreGetItemByRow(int index, int id, int *pId, int *pPrice, char *pName, int nameSize)
{
    int result;
    if (!_StoreDb_bOpen) result = 0;
    else result = StoreGetItem(index, id, 1, pId, pPrice, pName, nameSize);
    return result;
}

int StoreIsItemLocked(int index, int id)
{
    int count;
    int result = 1;
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int db = DbUserGetDb(DbUserGetCurrent());
    int category = StoreGetTattooLocation(index);
    int status;
    if (category != 3) {
        status = TDbCompilePerformOp(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85 and \x8c = \x82\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mLockedColumn, pDescriptor->mLockedValue, 0x4C544154, category);
        // FAKEMATCH: id is not used after the query; its dead increment on a failed query keeps the
        // status test, likely left by a stripped error check (flow deletes the increment after cse)
        if (status != 0) id++;
    } else {
        status = TDbCompilePerformOp(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mLockedColumn, pDescriptor->mLockedValue);
        // FAKEMATCH: id is not used after the query; its dead increment on a failed query keeps the
        // status test, likely left by a stripped error check (flow deletes the increment after cse)
        if (status != 0) id++;
    }
    if (status == 0) {
        if (count == 0) result = 0;
    }
    return result;
}

int StoreIsItemNew(int index, int id)
{
    int count;
    int result = 1;
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int db = DbUserGetDb(DbUserGetCurrent());
    int category = StoreGetTattooLocation(index);
    int status;
    if (category != 3) {
        status = TDbCompilePerformOp(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85 and \x8c = \x82\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mNewColumn, 1, 0x4C544154, category);
        // FAKEMATCH: id is not used after the query; its dead increment on a failed query keeps the
        // status test, likely left by a stripped error check (flow deletes the increment after cse)
        if (status != 0) id++;
    } else {
        status = TDbCompilePerformOp(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mNewColumn, 1);
        // FAKEMATCH: id is not used after the query; its dead increment on a failed query keeps the
        // status test, likely left by a stripped error check (flow deletes the increment after cse)
        if (status != 0) id++;
    }
    if (status == 0) {
        if (count == 0) result = 0;
    }
    return result;
}

void StoreClearItemNew(int index, int id)
{
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int db = DbUserGetDb(DbUserGetCurrent());
    int category = StoreGetTattooLocation(index);
    if (category != 3) {
        // FAKEMATCH: id is not used after the query; its dead increment on a failed query keeps the
        // status test, likely left by a stripped error check (flow deletes the increment after cse)
        if (TDbCompilePerformOp(0, "use \x8c update \x8c set \x8c = 0 where \x8c = \x85 and \x8c = \x82\n", db,
                pDescriptor->mProfileTable, pDescriptor->mNewColumn, pDescriptor->mIdColumn, id, 0x4C544154, category) != 0) id++;
    } else {
        TDbCompilePerformOp(0, "use \x8c update \x8c set \x8c = 0 where \x8c = \x85\n", db,
                pDescriptor->mProfileTable, pDescriptor->mNewColumn, pDescriptor->mIdColumn, id);
    }
}

void StoreUnlockItem(int index, int id)
{
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int db = DbUserGetDb(DbUserGetCurrent());
    int category = StoreGetTattooLocation(index);
    if (category != 3) {
        // FAKEMATCH: id is not used after the query; its dead increment on a failed query keeps the
        // status test, likely left by a stripped error check (flow deletes the increment after cse)
        if (TDbCompilePerformOp(0, "use \x8c update \x8c set \x8c = 0 and \x8c = 1 where \x8c = \x85 and \x8c = \x82\n", db,
                pDescriptor->mProfileTable, pDescriptor->mLockedColumn, pDescriptor->mNewColumn, pDescriptor->mIdColumn, id, 0x4C544154, category) != 0) id++;
    } else {
        TDbCompilePerformOp(0, "use \x8c update \x8c set \x8c = 0 and \x8c = 1 where \x8c = \x85\n", db,
                pDescriptor->mProfileTable, pDescriptor->mLockedColumn, pDescriptor->mNewColumn, pDescriptor->mIdColumn, id);
    }
}

int StoreClose(void)
{
    if (_StoreDb_bOpen) {
        DbFileTblDestroy(0, 0x4D4E5453);
        _StoreDb_bOpen = 0;
    }
    return 1;
}

int StoreOpen(void)
{
    int result = 1;
    if (DbFileTblLoad(0, 0x4D4E5453) == 0) {
        _StoreDb_bOpen = 1;
    } else {
        _StoreDb_bOpen = 0;
        result = 0;
    }
    return result;
}

int StoreTeamCreate(void)
{
    DbColumnValue columns[17];
    unsigned short count = 1;
    int team;
    DbFindUnusedTeamIds(0x54415453, 0x4D414554, &team, &count);
    for (int i = 0; i < 13; i++) {
        columns[i].Set(0x4D414554, _StoreDb_aTeamColumns[i]);
        columns[i].mValue = _StoreDb_aTeamDefaults[i];
    }
    for (int i = 0; i < 3; i++) {
        const char *pName = _StoreDb_apszTeamNames[i];
        columns[i + 13].Set(0x4D414554, _StoreDb_aTeamColumns[i + 13], (int)pName);
    }
    columns[0].mValue = team;
    columns[16].SetEnd();
    TDbInsertRow(0x54415453, 0x4D414554, columns, 0, 0);
    StoreTeamAddPlayer(team);
    return team;
}

void StoreTeamDelete(int team)
{
    TDbCompilePerformOp(0, "use 'TATS' delete from 'YALP' where 'DIGT' = \x82\n", team);
    TDbCompilePerformOp(0, "use 'TATS' delete from 'MAET' where 'DIGT' = \x85\n", team);
}

int StoreGetRowItemId(int index, DbCursor *pCursor, int row)
{
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int id = -1;
    if (DbCursorSeek(pCursor, row)) {
        id = DbCursorGetInt(pCursor, pDescriptor->mIdColumn);
    }
    return id;
}

int StoreFindUnlockedRow(int index, DbCursor *pCursor, int ordinal, int *pRow)
{
    int result = 0;
    int row = 0;
    int available = 0;
    for (; DbCursorSeek(pCursor, row); row++) {
        int id = StoreGetRowItemId(index, pCursor, row);
        if (!StoreIsItemLocked(index, id)) {
            if (available == ordinal) {
                if (pRow) {
                    *pRow = row;
                }
                result = 1;
                break;
            }
            available++;
        }
    }
    return result;
}

int StoreIsRowItemNew(int index, DbCursor *pCursor)
{
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int id = DbCursorGetInt(pCursor, pDescriptor->mIdColumn);
    return StoreIsItemNew(index, id);
}

void StoreClearRowItemNew(int index, DbCursor *pCursor)
{
    const StoreCategory_t *pDescriptor = StoreGetCategory(index);
    int id = DbCursorGetInt(pCursor, pDescriptor->mIdColumn);
    StoreClearItemNew(index, id);
}

int StoreGetUnlockedOrdinal(int index, DbCursor *pCursor, int id, int *pOrdinal)
{
    int result = 0;
    int ordinal = 0;
    int row;
    for (; StoreFindUnlockedRow(index, pCursor, ordinal, &row); ordinal++) {
        if (StoreGetRowItemId(index, pCursor, row) == id) {
            *pOrdinal = ordinal;
            result = 1;
            break;
        }
    }
    return result;
}

int StoreCountUnlocked(int index, DbCursor *pCursor)
{
    int count = 0;
    int row;
    while (StoreFindUnlockedRow(index, pCursor, count, &row)) {
        count++;
    }
    return count;
}

int StoreTattooLocationToKind(int type)
{
    int index = 31;
    switch (type) {
    case 0:
        index = 20;
        break;
    case 1:
        index = 21;
        break;
    case 2:
        index = 19;
        break;
    }
    return index;
}

int StoreGetTattooLocation(int index)
{
    int type = 3;
    switch (index) {
    case 20:
        type = 0;
        break;
    case 21:
        type = 1;
        break;
    case 19:
        type = 2;
        break;
    }
    return type;
}

}
