#include <string.h>

#include "game/Object_8007A334.h"
#include "game/Table_8007E020.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"

struct Descriptor_80086CE8 {
    unsigned int mTable;
    unsigned int mIdColumn;
    unsigned int mNameColumn;
    int mNameSize;
    unsigned int mPriceColumn;
    unsigned int mSortColumn;
    unsigned int mProfileTable;
    unsigned int mLockedColumn;
    int mLockedValue;
    unsigned int mFlagColumn36;
};

struct Sort_80086D0C {
    int mTable;
    int mColumn;
    int mMode;
    unsigned char mUnknown12[4];
};

extern "C" {
int fn_80087BA0(int index);
int fn_801F967C(int handle, int table);
void fn_801F9718(int handle, int table, ColumnValue_802D6424 *pList, int *pResult, int flags);
int fn_801F9980(int handle, int *pTable);
int fn_801F9D70(int handle, int table, Object_80023BBC *pFilter, unsigned short *pCount);
int fn_801FA0BC(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter,
                Sort_80086D0C *pSort, int *pCursor, QueryResult *pResult);
int fn_801FA148(int cursor);
int fn_801FA290(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter,
                ColumnValue_802D6424 *pColumns);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F3D4(int handle);
int fn_8022F4BC(void);
}

static int sTeamColumns[16] = {
    0x44494754, 0x44494F54, 0x50595454, 0x44524F54,
    0x45445254, 0x464F5254, 0x564F5254, 0x4C474C54,
    0x49524454, 0x31434D54, 0x32434D54, 0x33434D54,
    0x4C445443, 0x414E5354, 0x414E4C54, 0x414E4454
};
static const char *sTeamNames[3] = { "STO", "Store Team", "Store Team" };
static const int sTeamDefaults[13] = { 0, 0, 5, 0, 0, 0, 0, 132, 0, 49, 42, 126, 1 };
static const Descriptor_80086CE8 sDescriptors[5] = {
    { 0x52414547, 0x594B5047, 0x4D4E5247, 32, 0x43525047, 0x594B5047, 0x5245474C, 0x4B434C47, 1, 0x574E5247 },
    { 0x4C414344, 0x494C4344, 0x4E4C4344, 21, 0x504C4344, 0x494C4344, 0x4C43444C, 0x4C4C4344, 1, 0x574E5247 },
    { 0x4F474F4C, 0x4C474C54, 0x4D4E474C, 21, 0x50474F4C, 0x524F474C, 0x474C4B4C, 0x4B4C474C, 1, 0x574E5247 },
    { 0x52494148, 0x52414850, 0x4D4E5248, 26, 0x43525048, 0x524F5248, 0x4B434C48, 0x4B434C48, 1, 0x574E5247 },
    { 0x4F544154, 0x49544154, 0x4E544154, 21, 0x43525054, 0x524F5454, 0x4B434C54, 0x4B434C54, 1, 0x574E5247 }
};
static const signed char sDescriptorIndex[22] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 4, 4, 4
};
static unsigned char sActive = 0;

extern "C" {

void fn_80086C10(int team)
{
    QueryResult result;
    unsigned short count = 1;
    int player;
    int sourcePlayer;
    int table;
    fn_80229AA4(0x54415453, 0x59414C50, &player, &count);
    fn_801FCE10(0, "use 'TATS' select 'DIGP' into \x85 from 'PRTS'\n", &sourcePlayer);
    fn_801F9980(0x54415453, &table);
    fn_801FCE10(&result, "use 'TATS' select into \x8c * from 'PRTS' where ('DIGP' = \x85)\n", table, sourcePlayer);
    fn_801FCE10(&result, "use 'TATS' update \x8c set 'DIGT' = \x85 and 'DIGP' = \x85\n", table, team, player);
    fn_801FCE10(&result, "use 'TATS' insert into 'YALP' * select * from \x8c\n", table);
    fn_801F967C(0x54415453, table);
}

const Descriptor_80086CE8 *fn_80086CE8(int index)
{
    return &sDescriptors[sDescriptorIndex[index]];
}

int fn_80086D0C(int index, int id, int byRow, int *pId, int *pPrice,
                char *pName, int nameSize)
{
    Table_8007E020 tables[2];
    Object_80023BBC priceFilter;
    Object_80023BBC both;
    Object_80023BBC categoryFilter;
    ColumnValue_802D6424 columns[4];
    Sort_80086D0C sort[2];
    QueryResult queryResult;
    int cursor;
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int result = 0;
    char *pBuffer = 0;
    Object_80023BBC *pFilter = &priceFilter;
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
        priceFilter.SetUnknown32(6, ((unsigned long long)pDescriptor->mTable << 32) | pDescriptor->mPriceColumn, 2, 0x10004);
        priceFilter.mUnknown24.mInt = 0;
        if (pDescriptor->mTable == 0x52414547) {
            pFilter = &both;
            both.Set(11, &priceFilter, &categoryFilter);
            categoryFilter.Set(6, ((unsigned long long)pDescriptor->mTable << 32) | 0x49525453, 3, index);
        } else if (pDescriptor->mTable == 0x4F544154) {
            int category = fn_80087BA0(index);
            pFilter = &both;
            both.Set(11, &priceFilter, &categoryFilter);
            categoryFilter.Set(6, ((unsigned long long)pDescriptor->mTable << 32) | 0x4C544154, 3, category);
        }
    } else {
        priceFilter.Set(6, ((unsigned long long)pDescriptor->mTable << 32) | pDescriptor->mIdColumn, 3, id);
    }
    tables[0].Set(pDescriptor->mTable, 2, pFilter);
    tables[1].Set(-1);
    if (byRow) {
        sort[0].mTable = pDescriptor->mTable;
        sort[0].mColumn = pDescriptor->mSortColumn;
        sort[0].mMode = 0;
        sort[1].mTable = -1;
        sort[1].mColumn = -1;
        sort[1].mMode = 3;
        if (fn_801FA0BC(0x54415453, tables, 0, sort, &cursor, &queryResult) == 0) {
            if (fn_801FA228(cursor, 1, id, columns) == 0) {
                result = 1;
            }
        }
        fn_801FA148(cursor);
    } else {
        if (fn_801FA290(0x54415453, tables, 0, columns) == 0) {
            result = 1;
        }
    }
    if (result) {
        column = 0;
        if (pName) {
            strncpy(pName, pBuffer, nameSize);
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

int fn_80087128(int index)
{
    Object_80023BBC priceFilter;
    Object_80023BBC both;
    Object_80023BBC categoryFilter;
    unsigned short count;
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int result = 0;
    Object_80023BBC *pFilter = &priceFilter;
    priceFilter.SetUnknown32(6, ((unsigned long long)pDescriptor->mTable << 32) | pDescriptor->mPriceColumn, 2, 0x10004);
    priceFilter.mUnknown24.mInt = 0;
    if (pDescriptor->mTable == 0x52414547) {
        pFilter = &both;
        both.Set(11, &priceFilter, &categoryFilter);
        categoryFilter.Set(6, ((unsigned long long)pDescriptor->mTable << 32) | 0x49525453, 3, index);
    } else if (pDescriptor->mTable == 0x4F544154) {
        int category = fn_80087BA0(index);
        pFilter = &both;
        both.Set(11, &priceFilter, &categoryFilter);
        categoryFilter.Set(6, ((unsigned long long)pDescriptor->mTable << 32) | 0x4C544154, 3, category);
    }
    if (fn_801F9D70(0x54415453, pDescriptor->mTable, pFilter, &count) == 0) {
        result = count;
    }
    return result;
}

int fn_800872E8(int index)
{
    int result;
    if (!sActive) result = 0;
    else result = fn_80087128(index);
    return result;
}

int fn_8008731C(int index, int id, int *pId, int *pPrice, char *pName, int nameSize)
{
    int result;
    if (!sActive) result = 0;
    else result = fn_80086D0C(index, id, 1, pId, pPrice, pName, nameSize);
    return result;
}

int fn_8008736C(int index, int id)
{
    int count;
    int result = 1;
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int db = fn_8022F3D4(fn_8022F4BC());
    int category = fn_80087BA0(index);
    int status;
    if (category != 3) {
        status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85 and \x8c = \x82\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mLockedColumn, pDescriptor->mLockedValue, 0x4C544154, category);
    } else {
        status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mLockedColumn, pDescriptor->mLockedValue);
    }
    if (status == 0) {
        if (count == 0) result = 0;
    }
    return result;
}

int fn_80087460(int index, int id)
{
    int count;
    int result = 1;
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int db = fn_8022F3D4(fn_8022F4BC());
    int category = fn_80087BA0(index);
    int status;
    if (category != 3) {
        status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85 and \x8c = \x82\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mFlagColumn36, 1, 0x4C544154, category);
    } else {
        status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from \x8c where \x8c = \x85 and \x8c = \x85\n", db, &count,
                pDescriptor->mProfileTable, pDescriptor->mIdColumn, id, pDescriptor->mFlagColumn36, 1);
    }
    if (status == 0) {
        if (count == 0) result = 0;
    }
    return result;
}

void fn_8008754C(int index, int id)
{
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int db = fn_8022F3D4(fn_8022F4BC());
    int category = fn_80087BA0(index);
    if (category != 3) {
        fn_801FCE10(0, "use \x8c update \x8c set \x8c = 0 where \x8c = \x85 and \x8c = \x82\n", db,
                pDescriptor->mProfileTable, pDescriptor->mFlagColumn36, pDescriptor->mIdColumn, id, 0x4C544154, category);
    } else {
        fn_801FCE10(0, "use \x8c update \x8c set \x8c = 0 where \x8c = \x85\n", db,
                pDescriptor->mProfileTable, pDescriptor->mFlagColumn36, pDescriptor->mIdColumn, id);
    }
}

void fn_80087600(int index, int id)
{
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int db = fn_8022F3D4(fn_8022F4BC());
    int category = fn_80087BA0(index);
    if (category != 3) {
        fn_801FCE10(0, "use \x8c update \x8c set \x8c = 0 and \x8c = 1 where \x8c = \x85 and \x8c = \x82\n", db,
                pDescriptor->mProfileTable, pDescriptor->mLockedColumn, pDescriptor->mFlagColumn36, pDescriptor->mIdColumn, id, 0x4C544154, category);
    } else {
        fn_801FCE10(0, "use \x8c update \x8c set \x8c = 0 and \x8c = 1 where \x8c = \x85\n", db,
                pDescriptor->mProfileTable, pDescriptor->mLockedColumn, pDescriptor->mFlagColumn36, pDescriptor->mIdColumn, id);
    }
}

int fn_800876C0(void)
{
    if (sActive) {
        fn_8022EFBC(0, 0x4D4E5453);
        sActive = 0;
    }
    return 1;
}

int fn_80087704(void)
{
    int result = 1;
    if (fn_8022EF8C(0, 0x4D4E5453) == 0) {
        sActive = 1;
    } else {
        sActive = 0;
        result = 0;
    }
    return result;
}

int fn_8008775C(void)
{
    ColumnValue_802D6424 columns[17];
    unsigned short count = 1;
    int team;
    fn_8022C628(0x54415453, 0x4D414554, &team, &count);
    for (int i = 0; i < 13; i++) {
        columns[i].Set(0x4D414554, sTeamColumns[i], sTeamDefaults[i]);
    }
    for (int i = 0; i < 3; i++) {
        columns[i + 13].Set(0x4D414554, sTeamColumns[i + 13], (int)sTeamNames[i]);
    }
    columns[0].mValue = team;
    columns[16].SetEnd();
    fn_801F9718(0x54415453, 0x4D414554, columns, 0, 0);
    fn_80086C10(team);
    return team;
}

void fn_80087880(int team)
{
    fn_801FCE10(0, "use 'TATS' delete from 'YALP' where 'DIGT' = \x82\n", team);
    fn_801FCE10(0, "use 'TATS' delete from 'MAET' where 'DIGT' = \x85\n", team);
}

int fn_800878D8(int index, Object_8007A334 *pCursor, int row)
{
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int id = -1;
    if (fn_8007A600(pCursor, row)) {
        id = fn_8007A98C(pCursor, pDescriptor->mIdColumn);
    }
    return id;
}

int fn_80087938(int index, Object_8007A334 *pCursor, int ordinal, int *pRow)
{
    int result = 0;
    int row = 0;
    int available = 0;
    for (; fn_8007A600(pCursor, row); row++) {
        int id = fn_800878D8(index, pCursor, row);
        if (!fn_8008736C(index, id)) {
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

int fn_800879E8(int index, Object_8007A334 *pCursor)
{
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int id = fn_8007A98C(pCursor, pDescriptor->mIdColumn);
    return fn_80087460(index, id);
}

void fn_80087A30(int index, Object_8007A334 *pCursor)
{
    const Descriptor_80086CE8 *pDescriptor = fn_80086CE8(index);
    int id = fn_8007A98C(pCursor, pDescriptor->mIdColumn);
    fn_8008754C(index, id);
}

int fn_80087A78(int index, Object_8007A334 *pCursor, int id, int *pOrdinal)
{
    int result = 0;
    int ordinal = 0;
    int row;
    for (; fn_80087938(index, pCursor, ordinal, &row); ordinal++) {
        if (fn_800878D8(index, pCursor, row) == id) {
            *pOrdinal = ordinal;
            result = 1;
            break;
        }
    }
    return result;
}

int fn_80087B00(int index, Object_8007A334 *pCursor)
{
    int count = 0;
    int row;
    while (fn_80087938(index, pCursor, count, &row)) {
        count++;
    }
    return count;
}

int fn_80087B5C(int type)
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

int fn_80087BA0(int index)
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
