#include <stdio.h>

#include "game/Candidate_8016B364.h"
#include "game/Object_8007A334.h"
#include "game/QueryStatus.h"
#include "game/Team_80167A8C.h"
#include "game/fn_800670B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801FCE10.h"

/* The 40-byte condition node passed to fn_801FA0BC and fn_801FA290: two
   operands (an 8-byte value tagged with its kind) and a word combining the
   operator. Kind 6 names a table and column, 3 an integer and 11 another
   node; fn_801FA290 reads the same bytes as Object_80023BBC. */
struct Condition_800659AC;

union Value_800659AC {
    int mInt;
    unsigned long long mColumn;
    Condition_800659AC *mpNode;
};

struct Operand_800659AC {
    void Set(int kind, unsigned long long column)
    {
        mKind = kind;
        mValue.mColumn = column;
    }
    void Set(int kind, int value)
    {
        mKind = kind;
        mValue.mInt = value;
    }
    void Set(int kind, Condition_800659AC *pNode)
    {
        mKind = kind;
        mValue.mpNode = pNode;
    }

    int mKind;
    Value_800659AC mValue;
};

struct Condition_800659AC {
    void Set(int kind, unsigned long long column, int valueKind, int value)
    {
        mLeft.Set(kind, column);
        mRight.Set(valueKind, value);
    }
    void Set(int kind, unsigned long long column, int valueKind, unsigned long long value)
    {
        mLeft.Set(kind, column);
        mRight.Set(valueKind, value);
    }
    void Set(int kind, Condition_800659AC *pLeft, Condition_800659AC *pRight)
    {
        mLeft.Set(kind, pLeft);
        mRight.Set(kind, pRight);
    }

    Operand_800659AC mLeft;
    Operand_800659AC mRight;
    int mOperator;
};

/* One entry of the table list of fn_801FA0BC and fn_801FA290, as
   Table_800659AC but filtered by a Condition_800659AC. */
struct Table_800659AC {
    void Set(int tag, int type, Condition_800659AC *pFilter)
    {
        mpFilter = pFilter;
        mTag = tag;
        mType = type;
    }

    int mTag;
    int mType;
    Condition_800659AC *mpFilter;
};

extern "C" {
extern char lbl_802EBDF8[];

unsigned int fn_801688D4(void);
void fn_8016B364(int team, Candidate_8016B364 *pList, unsigned int count);
void fn_801F51DC(int a, void *pBase, int count, int size,
                 int (*pCompare)(Candidate_8016B364 *, Candidate_8016B364 *),
                 void (*pSwap)(Candidate_8016B364 *, Candidate_8016B364 *), int b, int c);
int fn_801F8D60(int tag, int a);
int fn_801F8EEC(int tag);
int fn_801F9D70(int handle, int table, Condition_800659AC *pFilter, unsigned short *pCount);
int fn_801FA0BC(int handle, Table_800659AC *pTables, Condition_800659AC *pFilter, void *pSort, int *pCursor,
                QueryResult *pResult);
int fn_801FA148(int cursor);
int fn_801FA290(int handle, Table_800659AC *pTables, Condition_800659AC *pFilter, ColumnValue_802D6424 *pColumns);
int fn_8020D2D0(int tag, char *pName, int a, int b);
unsigned int fn_802372EC(unsigned int, unsigned int);
}

static const char *lbl_802D5034[25] = {
    "QB", "HB", "FB", "WR", "TE", "LT", "LG", "C", "RG", "RT", "LE", "RE", "DT",
    "LOLB", "MLB", "ROLB", "CB", "FS", "SS", "K", "P", "KR", "PR", "KOS", "LS"
};

static unsigned char lbl_803EA658[8] = { 0xFF, 0x55, 0x56, 0x56, 0x55, 0x5B, 0x5B, 0xFF };
static int lbl_803EA660 = 0;
static int lbl_803EA664 = 0;
static int lbl_803EA668 = 0;
static int lbl_803EA66C = 0;

extern "C" {

void fn_80066000(int tag, int index, int key, Object_8006719C *pObject);

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x195410. */
const char *GetPositionString(int index)
{
    return lbl_802D5034[index];
}

void fn_800659AC(int tag, int handle, int index, Team_80167A8C *pTeam, Object_8006719C *pObject)
{
    Condition_800659AC filter;
    Condition_800659AC orderFilter;
    Condition_800659AC handleFilter;
    Table_800659AC tables[2] = { { 0x54534250 }, { -1 } };
    ColumnValue_802D6424 columns[4] = {
        { 0, 0x54534250, 0x656D616E },
        { 0, 0x54534250, 0x54534250 },
        { 0, 0x54534250, 0x4C544553 },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x20009;
    filter.Set(11, &orderFilter, &handleFilter);
    orderFilter.mOperator = 0x10003;
    orderFilter.Set(6, ((unsigned long long)0x54534250 << 32) | 0x5F64726F, 3, index + 1);
    handleFilter.mOperator = 0x10003;
    handleFilter.Set(6, ((unsigned long long)0x54534250 << 32) | 0x4D464250, 3, handle);
    columns[0].mValue = (int)pObject->mUnknownC8C;
    fn_801FA290(tag, tables, &filter, columns);
    pObject->mUnknown0 = columns[1].mValue;
    pObject->mUnknown4 = columns[2].mValue;
}

void fn_80065B50(int tag, int handle, Object_8006719C *pObject)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x4C544553 }, { -1 } };
    ColumnValue_802D6424 columns[7] = {
        { 0, 0x4C544553, 0x4D524F46 },
        { 0, 0x4C544553, 0x4E544F4D },
        { 0, 0x4C544553, 0x6F736F70 },
        { 0, 0x4C544553, 0x54544953 },
        { 0, 0x4C544553, 0x5F464C53 },
        { 0, 0x4C544553, 0x54544553 },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x4C544553 << 32) | 0x4C544553, 3, handle);
    fn_801FA290(tag, tables, &filter, columns);
    pObject->mUnknown8 = columns[0].mValue;
    pObject->mUnknownC = columns[1].mValue;
    pObject->mUnknownE = columns[2].mValue;
    pObject->mUnknown14 = columns[4].mValue;
    pObject->mUnknown10 = columns[5].mValue;
    pObject->mUnknownF = 0;
}

void fn_80065CAC(int tag, int handle, Team_80167A8C *pTeam, Object_8006719C *pObject)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x50544553 }, { -1 } };
    ColumnValue_802D6424 columns[12] = {
        { 0, 0x54534250, 0x50544553 },
        { 0, 0x54534250, 0x736F5044 },
        { 0, 0x54534250, 0x736F5045 },
        { 0, 0x54534250, 0x5F544753 },
        { 0, 0x54534250, 0x6F626174 },
        { 0, 0x54534250, 0x6F736F70 },
        { 0, 0x54534250, 0x78747261 },
        { 0, 0x54534250, 0x79747261 },
        { 0, 0x54534250, 0x73616C66 },
        { 0, 0x54534250, 0x78746D66 },
        { 0, 0x54534250, 0x79746D66 },
        { 0, -1, -1 }
    };
    int cursor;
    unsigned int flags = fn_801688D4();
    int opened = 0;
    int status;

    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x50544553 << 32) | 0x4C544553, 3, handle);
    status = fn_801FA0BC(tag, tables, &filter, 0, &cursor, 0);
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        opened = 1;
    }
    if (status == 0) {
        status = fn_801FA228(cursor, 1, 0, columns);
        while (status == 0) {
            unsigned char index = columns[5].mValue;
            if (index <= 6) {
                if (flags & 1) {
                    int row;
                    for (row = 0; row < 11; row++) {
                        pObject->mUnknown84[row][index].mUnknownC = columns[0].mValue;
                        pObject->mUnknown84[row][index].mUnknown2 = (unsigned char)columns[1].mValue;
                        pObject->mUnknown84[row][index].mUnknown0 = (unsigned char)columns[2].mValue;
                        pObject->mUnknown84[row][index].mUnknown4 = (unsigned char)columns[3].mValue;
                        pObject->mUnknown84[row][index].mUnknown8 = columns[4].mValue;
                        pObject->mUnknown84[row][index].mUnknownB = columns[8].mValue;
                    }
                } else {
                    pObject->mUnknown84[0][index].mUnknownC = columns[0].mValue;
                    pObject->mUnknown84[0][index].mUnknown2 = (unsigned char)columns[1].mValue;
                    pObject->mUnknown84[0][index].mUnknown0 = (unsigned char)columns[2].mValue;
                    pObject->mUnknown84[0][index].mUnknown4 = (unsigned char)columns[3].mValue;
                    pObject->mUnknown84[0][index].mUnknown8 = columns[4].mValue;
                    pObject->mUnknown84[0][index].mUnknownB = columns[8].mValue;
                }
                if (!(flags & 4)) {
                    pTeam->mUnknown693C[index].mX = (unsigned int)columns[6].mValue;
                    pTeam->mUnknown693C[index].mY = (unsigned int)columns[7].mValue;
                } else {
                    pTeam->mUnknown693C[index].mX = (unsigned int)columns[9].mValue;
                    pTeam->mUnknown693C[index].mY = (unsigned int)columns[10].mValue;
                }
                fn_80066000(tag, index, pObject->mUnknown84[0][index].mUnknownC, pObject);
            }
            status = fn_801FA228(cursor, 0, 1, columns);
        }
    }
    if (opened == 1) {
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = fn_801FA148(cursor);
        } else {
            fn_801FA148(cursor);
        }
    }
}

void fn_80066000(int tag, int index, int key, Object_8006719C *pObject)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x47544553 }, { -1 } };
    ColumnValue_802D6424 columns[11] = {
        { 0, 0x47544553, 0x5F464753 },
        { 0, 0x47544553, 0x5F5F5F78 },
        { 0, 0x47544553, 0x5F5F5F79 },
        { 0, 0x47544553, 0x5F726964 },
        { 0, 0x47544553, 0x5F6D6E61 },
        { 0, 0x47544553, 0x5F5F7866 },
        { 0, 0x47544553, 0x5F5F7966 },
        { 0, 0x47544553, 0x72696466 },
        { 0, 0x47544553, 0x6D6E6166 },
        { 0, 0x47544553, 0x5F5F4653 },
        { 0, -1, -1 }
    };
    int cursor;
    int opened;
    int status;
    int row;

    for (row = 10; row >= 0; row--) {
        pObject->mUnknown84[row][index].mUnknown6 = 0x7FFF;
    }
    opened = 0;
    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x47544553 << 32) | 0x50544553, 3, key);
    status = fn_801FA0BC(tag, tables, &filter, 0, &cursor, 0);
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        opened = 1;
    }
    if (status == 0) {
        status = fn_801FA228(cursor, 1, 0, columns);
        row = 0;
        while (status == 0) {
            pObject->mUnknown84[row][index].mUnknown6 = columns[0].mValue;
            pObject->mUnknown84[row][index].mUnknown10.mX = *(float *)&columns[1].mValue;
            pObject->mUnknown84[row][index].mUnknown10.mY = *(float *)&columns[2].mValue;
            pObject->mUnknown84[row][index].mUnknown20 = (int)((float)((columns[3].mValue * 360) >> 8) * 46603.379f);
            pObject->mUnknown84[row][index].mUnknown9 = lbl_803EA658[columns[4].mValue];
            pObject->mUnknown84[row][index].mUnknown18.mX = *(float *)&columns[5].mValue;
            pObject->mUnknown84[row][index].mUnknown18.mY = *(float *)&columns[6].mValue;
            pObject->mUnknown84[row][index].mUnknown24 = (int)((float)((columns[7].mValue * 360) >> 8) * 46603.379f);
            pObject->mUnknown84[row][index].mUnknownA = lbl_803EA658[columns[8].mValue];
            pObject->mUnknown84[row][index].mUnknownE = columns[9].mValue;
            row++;
            status = fn_801FA228(cursor, 0, 1, columns);
        }
    }
    if (opened == 1) {
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = fn_801FA148(cursor);
        } else {
            fn_801FA148(cursor);
        }
    }
}

void fn_80066318(int tag, int handle, Object_8006719C *pObject)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x00464753 }, { -1 } };
    ColumnValue_802D6424 columns[4] = {
        { 0, 0x00464753, 0x656D616E },
        { 0, 0x00464753, 0x5F464753 },
        { 0, 0x00464753, 0x746C6664 },
        { 0, -1, -1 }
    };
    int cursor;
    unsigned int count = 0;
    int opened = 0;
    int status;

    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x00464753 << 32) | 0x4C544553, 3, handle);
    columns[0].mValue = (int)pObject->mUnknown1C[0].mUnknown0;
    status = fn_801FA0BC(tag, tables, &filter, 0, &cursor, 0);
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        opened = 1;
    }
    if (status == 0) {
        status = fn_801FA228(cursor, 1, 0, columns);
        while (status == 0) {
            pObject->mUnknown1C[count].mUnknown6 = columns[1].mValue;
            pObject->mUnknown1C[count].mUnknown5 = columns[2].mValue;
            count++;
            columns[0].mValue = (int)pObject->mUnknown1C[count].mUnknown0;
            status = fn_801FA228(cursor, 0, 1, columns);
        }
    }
    if (opened == 1) {
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = fn_801FA148(cursor);
        } else {
            fn_801FA148(cursor);
        }
    }
    pObject->mUnknown18 = count;
}

void fn_80066560(int tag, int handle, int index, Record_80067338 *pRecord)
{
    Condition_800659AC filter;
    Condition_800659AC handleFilter;
    Condition_800659AC orderFilter;
    Table_800659AC tables[2] = { { 0x4C504250 }, { -1 } };
    ColumnValue_802D6424 columns[4] = {
        { 0, 0x4C504250, 0x4C594C50 },
        { 0, 0x4C504250, 0x4C504250 },
        { 0, 0x4C504250, 0x5F64726F },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x20009;
    filter.Set(11, &handleFilter, &orderFilter);
    handleFilter.mOperator = 0x10003;
    handleFilter.Set(6, ((unsigned long long)0x4C504250 << 32) | 0x54534250, 3, handle);
    orderFilter.mOperator = 0x10003;
    orderFilter.Set(6, ((unsigned long long)0x4C504250 << 32) | 0x5F64726F, 3, index + 1);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknown0 = columns[0].mValue;
    pRecord->mUnknown4 = columns[1].mValue;
    pRecord->mUnknown8 = columns[2].mValue;
}

int fn_80066704(int tag, int handle, Record_80067338 *pRecord)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x4C594C50 }, { -1 } };
    ColumnValue_802D6424 columns[9] = {
        { 0, 0x4C594C50, 0x656D616E },
        { 0, 0x4C594C50, 0x6E746F6D },
        { 0, 0x4C594C50, 0x736F7076 },
        { 0, 0x4C594C50, 0x54544953 },
        { 0, 0x4C594C50, 0x6B736972 },
        { 0, 0x4C594C50, 0x5F464C50 },
        { 0, 0x4C594C50, 0x54594C50 },
        { 0, 0x4C594C50, 0x4C544553 },
        { 0, -1, -1 }
    };

    columns[0].mValue = (int)pRecord->mUnknown1F0;
    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x4C594C50 << 32) | 0x4C594C50, 3, handle);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknownD = columns[1].mValue;
    pRecord->mUnknownC = columns[2].mValue;
    pRecord->mUnknown10 = columns[3].mValue;
    pRecord->mUnknown18 = columns[5].mValue;
    pRecord->mUnknown14 = columns[6].mValue;
    return columns[7].mValue;
}

void fn_800668E4(int tag, int handle, Record_80067338 *pRecord);
void fn_80066A0C(int tag, int handle, Record_80067338 *pRecord);
void fn_80066B6C(int tag, int handle, Record_80067338 *pRecord);

void fn_80066844(int tag, int handle, unsigned int kind, Record_80067338 *pRecord)
{
    fn_801C1F94(pRecord->mUnknown1C, 0, sizeof(pRecord->mUnknown1C));
    switch (kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        fn_80066A0C(tag, handle, pRecord);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        fn_800668E4(tag, handle, pRecord);
        break;
    case 21:
        kind = 0;
        break;
    }
    fn_80066B6C(tag, handle, pRecord);
}

void fn_800668E4(int tag, int handle, Record_80067338 *pRecord)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x44524C50 }, { -1 } };
    ColumnValue_802D6424 columns[2] = {
        { 0, 0x44524C50, 0x656C6F68 },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x44524C50 << 32) | 0x4C594C50, 3, handle);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknown1C[0][0] = columns[0].mValue;
}

void fn_80066A0C(int tag, int handle, Record_80067338 *pRecord)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x44504C50 }, { -1 } };
    ColumnValue_802D6424 columns[7] = {
        { 0, 0x44504C50, 0x31766372 },
        { 0, 0x44504C50, 0x31726570 },
        { 0, 0x44504C50, 0x32766372 },
        { 0, 0x44504C50, 0x32726570 },
        { 0, 0x44504C50, 0x33766372 },
        { 0, 0x44504C50, 0x33726570 },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x44504C50 << 32) | 0x4C594C50, 3, handle);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknown1C[0][0] = columns[0].mValue;
    pRecord->mUnknown1C[0][1] = columns[1].mValue;
    pRecord->mUnknown1C[1][0] = columns[2].mValue;
    pRecord->mUnknown1C[1][1] = columns[3].mValue;
    pRecord->mUnknown1C[2][0] = columns[4].mValue;
    pRecord->mUnknown1C[2][1] = columns[5].mValue;
}

void fn_80066B6C(int tag, int handle, Record_80067338 *pRecord)
{
    Condition_800659AC filter;
    Table_800659AC tables[2] = { { 0x4D434C50 }, { -1 } };
    ColumnValue_802D6424 columns[16] = {
        { 0, 0x4D434C50, 0x31796C70 },
        { 0, 0x4D434C50, 0x32796C70 },
        { 0, 0x4D434C50, 0x33796C70 },
        { 0, 0x4D434C50, 0x34796C70 },
        { 0, 0x4D434C50, 0x35796C70 },
        { 0, 0x4D434C50, 0x31726570 },
        { 0, 0x4D434C50, 0x32726570 },
        { 0, 0x4D434C50, 0x33726570 },
        { 0, 0x4D434C50, 0x34726570 },
        { 0, 0x4D434C50, 0x35726570 },
        { 0, 0x4D434C50, 0x31726964 },
        { 0, 0x4D434C50, 0x32726964 },
        { 0, 0x4D434C50, 0x33726964 },
        { 0, 0x4D434C50, 0x34726964 },
        { 0, 0x4D434C50, 0x35726964 },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x10003;
    filter.Set(6, ((unsigned long long)0x4D434C50 << 32) | 0x4C594C50, 3, handle);
    if (fn_801FA290(tag, tables, &filter, columns) == 0) {
        pRecord->mUnknown28[0][0] = columns[0].mValue;
        pRecord->mUnknown28[1][0] = columns[1].mValue;
        pRecord->mUnknown28[2][0] = columns[2].mValue;
        pRecord->mUnknown28[3][0] = columns[3].mValue;
        pRecord->mUnknown28[4][0] = columns[4].mValue;
        pRecord->mUnknown28[0][1] = columns[5].mValue;
        pRecord->mUnknown28[1][1] = columns[6].mValue;
        pRecord->mUnknown28[2][1] = columns[7].mValue;
        pRecord->mUnknown28[3][1] = columns[8].mValue;
        pRecord->mUnknown28[4][1] = columns[9].mValue;
        pRecord->mUnknown28[0][2] = columns[10].mValue;
        pRecord->mUnknown28[1][2] = columns[11].mValue;
        pRecord->mUnknown28[2][2] = columns[12].mValue;
        pRecord->mUnknown28[3][2] = columns[13].mValue;
        pRecord->mUnknown28[4][2] = columns[14].mValue;
    } else {
        pRecord->mUnknown28[0][0] = 0;
        pRecord->mUnknown28[1][0] = 0;
        pRecord->mUnknown28[2][0] = 0;
        pRecord->mUnknown28[3][0] = 0;
        pRecord->mUnknown28[4][0] = 0;
        pRecord->mUnknown28[0][1] = 0;
        pRecord->mUnknown28[1][1] = 0;
        pRecord->mUnknown28[2][1] = 0;
        pRecord->mUnknown28[3][1] = 0;
        pRecord->mUnknown28[4][1] = 0;
        pRecord->mUnknown28[0][2] = 0;
        pRecord->mUnknown28[1][2] = 0;
        pRecord->mUnknown28[2][2] = 0;
        pRecord->mUnknown28[3][2] = 0;
        pRecord->mUnknown28[4][2] = 0;
    }
}

void fn_80066D5C(void)
{
    lbl_803EA660 = 0;
    lbl_803EA664 = 0;
    lbl_803EA668 = 0;
    lbl_803EA66C = 0;
}

int fn_80066D74(unsigned int id, int a, int b, int c, int d, int e)
{
    int result = fn_801F8D60(id, 0x80000);

    if (result == 0) {
        result = fn_8020D2D0(id, lbl_802EBDF8, a, 0);
    }
    return result;
}

void fn_80066DC8(unsigned int id, int a)
{
    fn_801F8EEC(id);
}

void fn_80066DE8(int tag, int handle, Record_80067338 *pRecord, int full)
{
    unsigned char values[3];
    QueryCursor cursor;
    unsigned char code;
    int set = 0;
    unsigned int type = 0;
    int list;
    unsigned int i;

    for (i = 0; i < 7; i++) {
        int ok;

        cursor.mUnknown0 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown4 = 0;
        cursor.mUnknown12 = 0;
        ok = 1;
        if (full) {
            fn_801FCE10(0, "use \x8c select 'LTES' into \x85 from 'LYLP' where 'LYLP' = \x85\n", tag, &set, handle);
            fn_801FCE10(0, "use \x8c select 'soPE' into \x85 from 'PTES' where 'LTES' = \x85 and 'osop' = \x85\n", tag,
                        &type, set, i);
            switch (type) {
            case 1:
            case 2:
            case 4:
                break;
            default:
                ok = 0;
                break;
            }
        }
        if (ok) {
            int status;
            unsigned int count;
            unsigned int tries;

            fn_801FCE10(0, "use \x8c select 'LASP' into \x85 from 'SYLP' where 'LYLP' = \x85 and 'osop' = \x85\n", tag,
                        &list, handle, i);
            if (full) {
                status = fn_801FCE10(0,
                                     "use \x8c declare \x8a fastcursor for select 'edoc' into \x83 and '1lav' into \x83 "
                                     "and '2lav' into \x83 and '3lav' into \x83 from 'LASP' where 'LASP' = \x85 and "
                                     "'pets' < \x85 order by 'pets' asc\n",
                                     tag, &cursor, &code, &values[0], &values[1], &values[2], list, 3);
            } else {
                status = fn_801FCE10(0,
                                     "use \x8c declare \x8a fastcursor for select 'edoc' into \x83 and '1lav' into \x83 "
                                     "and '2lav' into \x83 and '3lav' into \x83 from 'LASP' where 'LASP' = \x85 order by "
                                     "'pets' asc\n",
                                     tag, &cursor, &code, &values[0], &values[1], &values[2], list);
            }
            count = 0;
            tries = 0;
            if (status == 0) {
                do {
                    status = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
                    if (status == 0) {
                        if (code == 0xFF) {
                            break;
                        }
                        pRecord->mUnknown38[i][count][0] = code;
                        pRecord->mUnknown38[i][count][1] = values[0];
                        pRecord->mUnknown38[i][count][2] = values[1];
                        pRecord->mUnknown38[i][count][3] = values[2];
                        count++;
                    }
                    tries++;
                    if (tries > 9) {
                        break;
                    }
                } while (status == 0);
            }
            pRecord->mUnknown38[i][count - 1][0] |= 0x80;
            if (cursor.mUnknown0) {
                fn_801FCFA0(&cursor);
            }
        }
    }
}

unsigned short fn_80067038(int tag, int kind)
{
    Condition_800659AC filter;
    unsigned short count;

    filter.mOperator = 0x10003;
    filter.mLeft.mKind = 6;
    filter.mLeft.mValue.mColumn = ((unsigned long long)0x4D464250 << 32) | 0x50595446;
    filter.mRight.mKind = 3;
    filter.mRight.mValue.mInt = kind;
    if (fn_801F9D70(tag, 0x4D464250, &filter, &count) != 0) {
        count = 0;
    }
    return count;
}

/* Discarded by the GameCube linker; bodies from the Xbox counterparts 0x196A60, 0x196A80 and 0x196AB0. */
int CountRows(int tag, unsigned int *pCount, int table)
{
    *pCount = 0;
    return fn_801FCE10(0, "use \x8c select count(*) into \x85 from \x8c\n", tag, pCount, table);
}

int SelectColumnByKey(int tag, int column, int table, int keyColumn, int key)
{
    int value = 0;

    fn_801FCE10(0, "use \x8c select \x8c into \x85 from \x8c where \x8c = \x85\n", tag, column, &value, table, keyColumn,
                key);
    return value;
}

int UpdateColumnByKey(int tag, int table, int column, int value, int keyColumn, int key)
{
    return fn_801FCE10(0, "use \x8c update \x8c set \x8c = \x85 where \x8c = \x85\n", tag, table, column, value,
                       keyColumn, key);
}

int fn_800670B4(int tag, int a, int b, Object_800670B4 *pObject)
{
    fn_801C1F94(pObject, 0, sizeof(*pObject));
    return fn_801FCE10(0,
                       "use \x8c select 'MFBP' into \x85 and 'eman' into \x88 from 'MFBP' where 'PYTF' = \x82 and "
                       "'_dro' = \x82\n",
                       tag, pObject, pObject->mUnknownCB0, a, b + 1);
}

unsigned short fn_80067120(int tag, int handle)
{
    Condition_800659AC filter;
    unsigned short count;

    filter.mOperator = 0x10003;
    filter.mLeft.mKind = 6;
    filter.mLeft.mValue.mColumn = ((unsigned long long)0x54534250 << 32) | 0x4D464250;
    filter.mRight.mKind = 3;
    filter.mRight.mValue.mInt = handle;
    if (fn_801F9D70(tag, 0x54534250, &filter, &count) != 0) {
        count = 0;
    }
    return count;
}

void fn_8006719C(int tag, int handle, int index, Team_80167A8C *pTeam, Object_8006719C *pObject)
{
    fn_801C1F94(pObject, 0, sizeof(*pObject));
    fn_800659AC(tag, handle, index, pTeam, pObject);
    if (pObject->mUnknown4) {
        fn_80065B50(tag, pObject->mUnknown4, pObject);
        fn_801688D4();
        fn_80065CAC(tag, pObject->mUnknown4, pTeam, pObject);
        fn_80066318(tag, pObject->mUnknown4, pObject);
    }
}

void fn_8006723C(int tag, int handle, Team_80167A8C *pTeam, Object_8006719C *pObject)
{
    fn_801C1F94(pObject, 0, sizeof(*pObject));
    pObject->mUnknown4 = handle;
    fn_80065B50(tag, handle, pObject);
    fn_801688D4();
    fn_80065CAC(tag, handle, pTeam, pObject);
    fn_80066318(tag, handle, pObject);
}

unsigned short fn_800672BC(int tag, int handle)
{
    Condition_800659AC filter;
    unsigned short count;

    filter.mOperator = 0x10003;
    filter.mLeft.mKind = 6;
    filter.mLeft.mValue.mColumn = ((unsigned long long)0x4C504250 << 32) | 0x54534250;
    filter.mRight.mKind = 3;
    filter.mRight.mValue.mInt = handle;
    if (fn_801F9D70(tag, 0x4C504250, &filter, &count) != 0) {
        count = 0;
    }
    return count;
}

int fn_80067338(int tag, int handle, int index, Record_80067338 *pRecord)
{
    int full = 0;
    int result;
    unsigned int flags;

    fn_801C1F94(pRecord, 0, sizeof(*pRecord));
    fn_80066560(tag, handle, index, pRecord);
    result = fn_80066704(tag, pRecord->mUnknown0, pRecord);
    flags = fn_801688D4();
    fn_80066844(tag, pRecord->mUnknown0, pRecord->mUnknown14, pRecord);
    if (flags & 2) {
        if (flags & 8) {
            full = 1;
        }
        fn_80066DE8(tag, pRecord->mUnknown0, pRecord, full);
    }
    return result;
}

int fn_800673F0(int tag, int a, int b)
{
    int value = 1;

    fn_801FCE10(0, "use \x8c select '_dro' into \x85 from 'LPBP' where 'LPBP' = \x82 and 'TSBP' = \x82\n", tag, &value,
                b, a);
    return value - 1;
}

int fn_80067440(int tag, int a, int b)
{
    int value = 1;

    fn_801FCE10(0, "use \x8c select '_dro' into \x85 from 'TSBP' where 'MFBP' = \x82 and 'TSBP' = \x82\n", tag, &value,
                a, b);
    return value - 1;
}

int fn_80067490(int tag, int a, int b)
{
    int value = 1;

    fn_801FCE10(0, "use \x8c select '_dro' into \x85 from 'MFBP' where 'MFBP' = \x82 and 'PYTF' = \x82\n", tag, &value,
                b, a);
    return value - 1;
}

void fn_800674E0(int tag, int a, int *pResult)
{
    int b;
    int c;
    int d;

    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'LPBP' where 'LPBP' = \x85\n", tag, &b, a);
    pResult[2] = fn_800673F0(tag, b, a);
    fn_801FCE10(0, "use \x8c select 'MFBP' into \x85 from 'TSBP' where 'TSBP' = \x85\n", tag, &c, b);
    pResult[1] = fn_80067440(tag, c, b);
    fn_801FCE10(0, "use \x8c select 'PYTF' into \x85 from 'MFBP' where 'MFBP' = \x85\n", tag, &d, c);
    pResult[3] = d;
    pResult[0] = fn_80067490(tag, d, c);
}

/* Discarded by the GameCube linker; bodies from the Xbox counterparts 0x196E70 and 0x196EB0. */
void SelectUABPRecord(int tag, int index, int kind, int *pResult)
{
    int value = 0;

    fn_801FCE10(0, "use \x8c select 'LPBP' into \x85 from 'UABP' where 'UABP' = \x85 and 'PYTF' = \x85\n", tag, &value,
                index + 1, kind);
    fn_800674E0(tag, value, pResult);
}

int CountUABPRows(int tag, int kind)
{
    int count = 0;

    fn_801FCE10(0, "use \x8c select count('LPBP') into \x85 from 'UABP' where 'PYTF' = \x85\n", tag, &count, kind);
    return count;
}

void fn_800675B4(int tag, int a, int b)
{
    if (b != 0xFFFF) {
        int result[4];

        fn_800674E0(tag, b, result);
        fn_801FCE10(0, "use \x8c update 'UABP' set 'LPBP' = \x82 where 'UABP' = \x85 and 'PYTF' = \x82\n", tag, b, a + 1,
                    result[3]);
    }
}

/* Discarded by the GameCube linker; bodies from the Xbox counterparts 0x196F20, 0x196F70, 0x197020 and
   0x1970B0. */
int SelectLTESAndTSBPByOrder(int tag, int *pResult, int index, int key)
{
    return fn_801FCE10(0,
                       "use \x8c select 'LTES' into \x85 and 'TSBP' into \x85 from 'TSBP' where '_dro' = \x82 and "
                       "'MFBP' = \x85\n",
                       tag, &pResult[1], &pResult[0], index + 1, key);
}

void SelectTSBPPoints(int tag, int key, Point_8017886C *pPoints)
{
    char x[8];
    char y[8];
    unsigned int xValue;
    unsigned int yValue;
    int i;

    for (i = 0; i < 7; i++) {
        int status;

        sprintf(x, "ax%d_", i);
        sprintf(y, "ay%d_", i);
        status = fn_801FCE10(0, "use \x8c select \x8c into \x85 and \x8c into \x85 from 'TSBP' where 'TSBP' = \x85\n", tag,
                             *(int *)x, &xValue, *(int *)y, &yValue, key);
        if (status != 0) {
            break;
        }
        pPoints[i].mX = xValue;
        pPoints[i].mY = yValue;
    }
}

void LoadTSBPObject(int tag, int handle, Team_80167A8C *pTeam, Object_8006719C *pObject)
{
    unsigned int flags;
    int formation;
    int order;

    fn_801C1F94(pObject, 0, sizeof(*pObject));
    flags = fn_801688D4();
    fn_801FCE10(0, "use \x8c select 'MFBP' into \x85 and '_dro' into \x85 from 'TSBP' where 'TSBP' = \x85\n", tag,
                &formation, &order, handle);
    fn_800659AC(tag, formation, order - 1, pTeam, pObject);
    if (pObject->mUnknown4) {
        fn_80065B50(tag, pObject->mUnknown4, pObject);
        if (flags & 1) {
            fn_80065CAC(tag, pObject->mUnknown4, pTeam, pObject);
        }
        fn_80066318(tag, pObject->mUnknown4, pObject);
    }
}

int SelectLTESName(int tag, char *pName, int set)
{
    return fn_801FCE10(0, "use \x8c select 'eman' into \x88 from 'LTES' where 'LTES' = \x85\n", tag, pName, set);
}

int fn_80067624(Candidate_8016B364 *pA, Candidate_8016B364 *pB)
{
    if (pA->mUnknown4 < pB->mUnknown4) {
        return -1;
    }
    return 0;
}

void fn_80067640(Candidate_8016B364 *pA, Candidate_8016B364 *pB)
{
    Candidate_8016B364 temp = *pA;

    *pA = *pB;
    *pB = temp;
}

int fn_80067690(int team, int tag, int kind)
{
    Candidate_8016B364 list[225];
    Condition_800659AC kindFilter;
    Condition_800659AC joinFilter;
    Condition_800659AC playerFilter;
    Table_800659AC tables[4];
    ColumnValue_802D6424 columns[5] = {
        { 0, 0x4C504250, 0x4C504250 },
        { 0, 0x4C594C50, 0x54594C50 },
        { 0, 0x49414250, 0x74637270 },
        { 0, 0x4C594C50, 0x5F464C50 },
        { 0, -1, -1 }
    };
    int cursor;
    unsigned short count = 0;
    int opened = 0;
    int status;

    kindFilter.mOperator = 0x10003;
    kindFilter.Set(6, ((unsigned long long)0x49414250 << 32) | 0x52474941, 3, kind);
    joinFilter.mOperator = 0x10003;
    joinFilter.Set(6, ((unsigned long long)0x49414250 << 32) | 0x4C504250, 6,
                   ((unsigned long long)0x4C504250 << 32) | 0x4C504250);
    playerFilter.mOperator = 0x10003;
    playerFilter.Set(6, ((unsigned long long)0x4C504250 << 32) | 0x4C594C50, 6,
                     ((unsigned long long)0x4C594C50 << 32) | 0x4C594C50);
    tables[0].Set(0x49414250, 0, &kindFilter);
    tables[1].Set(0x4C504250, 0, &joinFilter);
    tables[2].Set(0x4C594C50, 0, &playerFilter);
    tables[3].Set(-1, 0, 0);
    fn_801C1F94(list, 0, sizeof(list));
    status = fn_801FA0BC(tag, tables, 0, 0, &cursor, 0);
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        opened = 1;
    }
    if (status == 0) {
        status = fn_801FA228(cursor, 1, 0, columns);
        while (status == 0) {
            list[count].mUnknown0 = columns[0].mValue;
            list[count].mUnknown8 = columns[1].mValue;
            list[count].mUnknown4 = columns[2].mValue;
            list[count].mUnknown6 = columns[3].mValue;
            count++;
            status = fn_801FA228(cursor, 0, 1, columns);
        }
    }
    if (opened == 1) {
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = fn_801FA148(cursor);
        } else {
            fn_801FA148(cursor);
        }
    }
    if (status == 0) {
        unsigned short i;
        unsigned int total;
        unsigned int pick;
        unsigned int sum;

        fn_801F51DC(0, list, count, sizeof(Candidate_8016B364), fn_80067624, fn_80067640, 0, 0);
        fn_8016B364(team, list, count);
        total = 0;
        for (i = 0; i < count; i++) {
            total += list[i].mUnknown4;
        }
        pick = fn_802372EC(0, total);
        sum = 0;
        for (i = 0; i < count; i++) {
            sum += list[i].mUnknown4;
            if (sum >= pick) {
                break;
            }
        }
        return list[i].mUnknown0;
    }
    return status;
}

void fn_80067A4C(int team, int tag, int kind, int *pResult)
{
    fn_800674E0(tag, fn_80067690(team, tag, kind), pResult);
}

int fn_80067A8C(int tag, int a, int b)
{
    Condition_800659AC filter;
    Condition_800659AC kindFilter;
    Condition_800659AC playerFilter;
    Table_800659AC tables[2] = { { 0x49414250 }, { -1 } };
    ColumnValue_802D6424 columns[2] = {
        { 0, 0x49414250, 0x4C504250 },
        { 0, -1, -1 }
    };

    filter.mOperator = 0x20009;
    filter.Set(11, &kindFilter, &playerFilter);
    kindFilter.mOperator = 0x10003;
    kindFilter.Set(6, ((unsigned long long)0x49414250 << 32) | 0x52474941, 3, a);
    playerFilter.mOperator = 0x10003;
    playerFilter.Set(6, ((unsigned long long)0x49414250 << 32) | 0x4C504250, 3, b);
    return fn_801FA290(tag, tables, &filter, columns) != 0x17;
}

}
