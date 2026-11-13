/* The game's records (high-score tables) kept in the saved database: opens a sorted list for each
   of the 24 record categories, fetches and formats rows with ranks for the records screens, and
   trims each category to its top ten. */

#include <stdio.h>
#include <string.h>

#include "game/fn_801FCE10.h"

struct RecordsRow_t {
    char mUnknown0[20];
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    int mUnknown52;
    int mUnknown56;
    int mUnknown60;
    int mUnknown64;
    int mUnknown68;
    int mUnknown72;
    int mUnknown76;
    int mUnknown80;
    int mUnknown84;
    unsigned int mUnknown88;
    unsigned int mUnknown92;
    int mUnknown96;
    int mUnknown100;
    int mUnknown104;
    int mUnknown108;
};

extern "C" {
int MemCardFilesNeedsSave(int type, int index);
void MemCardFilesStoreChecksum(int type, int index);
void EnvSelect(int id);
void EnvGetUIName(char *pDest, int count);
void EnvRelease(void);
void fn_801880D4(int value, char *pText, int size);

void RecordsSumColumns(int type);
void RecordsOpenCategory(int type);
void RecordsSelectCategory(int type);
void RecordsFetchRow(int row);
int RecordsFormatColumn(int column, int row, char *pText, int size);
int RecordsGetRank(int row);
void RecordsBegin(void);
void RecordsEnd(void);
int RecordsGetText(int type, int value, int column, char *pText, int size);
void RecordsPrune(void);
void RecordsSeekRow(int a, int b);
int RecordsGetValue(int a);
void RecordsSetSharedRanks(int a);
}

static int _Records_aColumnTypes[24] = {
    24, 2, 3, 4, 5, 6, 24, 9, 7, 8, 10, 11,
    12, 13, 14, 15, 17, 18, 22, 22, 22, 22, 23, 19
};

static RecordsRow_t _Records_sRow;
static QueryCursor _Records_sCursor;
static int _Records_iCategory = -1;
static int _Records_iRow;
static int _Records_iRowCount;
static unsigned char _Records_bSaveChanged;
static unsigned char _Records_bSharedRanks;
static int _Records_iRankValue;
static int _Records_iRank;

extern "C" {

void RecordsSumColumns(int type)
{
    QueryCursor cursor;
    int key;
    int a;
    int b;
    int value = 0;
    int tagA = -1;
    int tagB = -1;
    if (type == 7) {
        tagA = 0x54505348;
        tagB = 0x54525348;
    }
    if (tagA == -1) {
        return;
    }
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "use 'EVAS' declare \x8a fastcursor for select 'KPSH' into \x82 and \x8c into \x82 and \x8c into \x82 from 'RCSH'\n", &cursor, &key, tagA, &a, tagB, &b) == 0) {
        int status;
        do {
            status = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            if (type == 7) {
                value = a + b;
            }
            fn_801FCE10(0, "use 'EVAS' update 'RCSH' set 'CSSH' = \x82 where 'KPSH' = \x82\n", value, key);
        } while (status == 0);
    }
    if (cursor.mUnknown0) {
        fn_801FCFA0(&cursor);
    }
}

void RecordsOpenCategory(int type)
{
    QueryResult result;
    int tag = -1;
    if (_Records_iCategory != -1) {
        if (_Records_sCursor.mUnknown0) {
            fn_801FCFA0(&_Records_sCursor);
        }
        _Records_iCategory = -1;
    }
    _Records_sCursor.mUnknown0 = 0;
    _Records_sCursor.mUnknown4 = 0;
    _Records_sCursor.mUnknown8 = -1;
    _Records_sCursor.mUnknown12 = 0;
    if (type == 6) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'DFSH'.'KTFH' into \x82 and 'DFSH'.'KUFH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'DFSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'DFSH'.'KUFH' order by 'DFSH'.'DIVE' asc\n",
                    &_Records_sCursor, &_Records_sRow.mUnknown32, &_Records_sRow.mUnknown108, _Records_sRow.mUnknown0);
    } else if (type == 4) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KTSH'.'TPTH' into \x82 and 'KTSH'.'KUTH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'KTSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'KTSH'.'KUTH' order by 'KTSH'.'TPTH' desc and 'RCSH'.'KUSH' asc\n",
                    &_Records_sCursor, &_Records_sRow.mUnknown32, &_Records_sRow.mUnknown108, _Records_sRow.mUnknown0);
    } else if (type == 2) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'SWSH'.'SWWH' into \x82 and 'SWSH'.'KUWH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'SWSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'SWSH'.'KUWH' order by 'SWSH'.'SWWH' desc and 'RCSH'.'KUSH' asc\n",
                    &_Records_sCursor, &_Records_sRow.mUnknown24, &_Records_sRow.mUnknown108, _Records_sRow.mUnknown0);
    } else if (type == 0) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'HCSH'.'KUCH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'HCSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'HCSH'.'KUCH' order by 'KPCH' desc\n",
                    &_Records_sCursor, &_Records_sRow.mUnknown108, _Records_sRow.mUnknown0);
    } else if (type >= 18 && type <= 21) {
        int count = 5;
        switch (type) {
        case 18:
            count = 3;
            break;
        case 19:
            break;
        case 20:
            count = 8;
            break;
        case 21:
            count = 10;
            break;
        }
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'CCSH'.'SRCH' into \x82 and 'CCSH'.'UCCH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'CCSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'CCSH'.'UCCH' where 'CCSH'.'TRCH' = \x83 order by 'CCSH'.'SRCH' desc\n",
                    &_Records_sCursor, &_Records_sRow.mUnknown96, &_Records_sRow.mUnknown108, _Records_sRow.mUnknown0, count);
    } else if (type == 22) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'BJSH'.'SJSH' into \x82 and 'BJSH'.'UBJH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'BJSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'BJSH'.'UBJH' order by 'BJSH'.'SJSH' desc\n",
                    &_Records_sCursor, &_Records_sRow.mUnknown100, &_Records_sRow.mUnknown108, _Records_sRow.mUnknown0);
    } else {
        switch (type) {
        case 1:
            tag = 0x57475348;
            break;
        case 3:
            tag = 0x50545348;
            break;
        case 5:
            tag = 0x54545348;
            break;
        case 8:
            tag = 0x54505348;
            break;
        case 9:
            tag = 0x54525348;
            break;
        case 10:
            tag = 0x54445348;
            break;
        case 11:
            tag = 0x54535348;
            break;
        case 12:
            tag = 0x43495348;
            break;
        case 13:
            tag = 0x52465348;
            break;
        case 14:
            tag = 0x47545348;
            break;
        case 15:
            tag = 0x32545348;
            break;
        case 16:
            tag = 0x4B535348;
            break;
        case 17:
            tag = 0x57515348;
            break;
        case 23:
            tag = 0x574F5348;
            break;
        case 7:
            RecordsSumColumns(7);
            tag = 0x43535348;
            break;
        default:
            tag = -1;
            break;
        }
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KUSH' into \x88 and 'WGSH' into \x82 and 'PTSH' into \x82 and 'TPSH' into \x82 and 'TRSH' into \x82 and 'TDSH' into \x82 and 'TSSH' into \x82 and 'CISH' into \x82 and 'RFSH' into \x82 and 'GTSH' into \x82 and '2TSH' into \x82 and 'TTSH' into \x82 and 'KSSH' into \x82 and 'WQSH' into \x82 and 'WOSH' into \x82 and 'LOSH' into \x82 and 'SOSH' into \x82 and 'AOSH' into \x82 and 'CSSH' into \x82 from 'RCSH' order by \x8c desc and 'KUSH' asc\n",
                    &_Records_sCursor, _Records_sRow.mUnknown0, &_Records_sRow.mUnknown20, &_Records_sRow.mUnknown28,
                    &_Records_sRow.mUnknown40, &_Records_sRow.mUnknown44, &_Records_sRow.mUnknown48, &_Records_sRow.mUnknown52,
                    &_Records_sRow.mUnknown56, &_Records_sRow.mUnknown60, &_Records_sRow.mUnknown64, &_Records_sRow.mUnknown68,
                    &_Records_sRow.mUnknown36, &_Records_sRow.mUnknown72, &_Records_sRow.mUnknown76, &_Records_sRow.mUnknown80,
                    &_Records_sRow.mUnknown84, &_Records_sRow.mUnknown88, &_Records_sRow.mUnknown92, &_Records_sRow.mUnknown104, tag);
    }
    _Records_iCategory = type;
    _Records_iRowCount = result.mUnknown0;
    _Records_iRow = -1;
}

void RecordsSelectCategory(int type)
{
    if (_Records_iCategory != type) {
        RecordsOpenCategory(type);
    }
}

void RecordsFetchRow(int row)
{
    QueryResult result;
    _Records_sCursor.mUnknown4 = row;
    fn_801FCE10(&result, "fetch from \x8a\n", &_Records_sCursor);
    _Records_iRow = row;
}

int RecordsFormatColumn(int column, int row, char *pText, int size)
{
    int value = RecordsGetValue(column);
    switch (column) {
    case 0:
        sprintf(pText, "%d", RecordsGetRank(row));
        break;
    case 1: {
        sprintf(pText, _Records_sRow.mUnknown0);
        int i = strlen(pText) - 1;
        while (pText[i] == ' ' && i > 0) {
            pText[i] = 0;
            i--;
        }
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 17:
    case 18:
    case 19:
    case 20:
    case 22:
    case 23:
        fn_801880D4(value, pText, size);
        break;
    case 21:
        sprintf(pText, "%d%%", value);
        break;
    case 16:
        EnvSelect(row);
        EnvGetUIName(pText, size);
        EnvRelease();
        break;
    case 24:
    default:
        sprintf(pText, " ");
        break;
    }
    return 0;
}

int RecordsGetRank(int row)
{
    int result = row + 1;
    if (_Records_bSharedRanks != 0) {
        if (_Records_aColumnTypes[_Records_iCategory] != 24) {
            if (row == 0) {
                _Records_iRankValue = RecordsGetValue(_Records_aColumnTypes[_Records_iCategory]);
                _Records_iRank = 1;
            } else if (RecordsGetValue(_Records_aColumnTypes[_Records_iCategory]) != _Records_iRankValue) {
                _Records_iRankValue = RecordsGetValue(_Records_aColumnTypes[_Records_iCategory]);
                _Records_iRank = result;
            }
            result = _Records_iRank;
        }
    }
    return result;
}

void RecordsBegin(void)
{
    _Records_bSaveChanged = MemCardFilesNeedsSave(1, 0);
    _Records_bSharedRanks = 0;
    _Records_iRankValue = 0;
    _Records_iRank = 1;
}

void RecordsEnd(void)
{
    if (_Records_iCategory != -1) {
        if (_Records_sCursor.mUnknown0) {
            fn_801FCFA0(&_Records_sCursor);
        }
        _Records_iCategory = -1;
    }
    if (_Records_bSaveChanged == 0 && MemCardFilesNeedsSave(1, 0) != 0) {
        MemCardFilesStoreChecksum(1, 0);
    }
}

int RecordsGetText(int type, int value, int column, char *pText, int size)
{
    char text[32] = " ";
    int result = 0;
    RecordsSelectCategory(type);
    if (_Records_iRow != value) {
        RecordsFetchRow(value);
    }
    if (value < _Records_iRowCount) {
        result = RecordsFormatColumn(column, value, text, 32);
    }
    memcpy(pText, text, size);
    return result;
}

void RecordsPrune(void)
{
    QueryResult result;
    QueryCursor cursor;
    int count;
    int key;
    unsigned char flag = 0;
    int type;

    RecordsBegin();
    fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'UFSH' = 0\n");
    for (type = 0; type <= 23; type++) {
        int status = 0;
        RecordsOpenCategory(type);
        switch (type) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 18:
        case 19:
        case 20:
        case 21:
            for (count = 0, status = 0; status == 0 && count <= 9; count++) {
                RecordsFetchRow(count);
                status = fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'UFSH' = 1 where 'KPSH' = \x82\n", _Records_sRow.mUnknown108);
            }
            break;
        default:
            for (count = 0, status = 0; status == 0 && count <= 9; count++) {
                RecordsFetchRow(count);
                status = fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'UFSH' = 1 where 'KUSH' = \x88\n", _Records_sRow.mUnknown0);
            }
            break;
        }
    }
    fn_801FCE10(&result, "use 'EVAS' delete from 'RCSH' where 'UFSH' = 0\n");
    flag |= result.mUnknown0 != 0;

    fn_801FCE10(&result, "use 'EVAS' select count(*) into \x82 from 'BGSH'\n", &count);
    if (count > 10) {
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KPGH' into \x82 from 'BGSH' order by 'TPGH' asc\n", &cursor, &key);
        while (count > 10) {
            cursor.mUnknown4 = 0;
            fn_801FCE10(&result, "fetch from \x8a\n", &cursor);
            fn_801FCE10(&result, "use 'EVAS' delete from 'BGSH' where 'KPGH' = \x82\n", key);
            flag |= result.mUnknown0 != 0;
            count--;
        }
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
    }

    fn_801FCE10(&result, "use 'EVAS' select count(*) into \x82 from 'TGSH'\n", &count);
    if (count > 10) {
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KPGH' into \x82 from 'TGSH' order by 'TPGH' asc\n", &cursor, &key);
        while (count > 10) {
            cursor.mUnknown4 = 0;
            fn_801FCE10(&result, "fetch from \x8a\n", &cursor);
            fn_801FCE10(&result, "use 'EVAS' delete from 'TGSH' where 'KPGH' = \x82\n", key);
            flag |= result.mUnknown0 != 0;
            count--;
        }
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
    }

    fn_801FCE10(&result, "use 'EVAS' select count(*) into \x82 from 'SWSH'\n", &count);
    if (count > 10) {
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KPWH' into \x82 from 'SWSH' order by 'SWWH' asc\n", &cursor, &key);
        while (count > 10) {
            cursor.mUnknown4 = 0;
            fn_801FCE10(&result, "fetch from \x8a\n", &cursor);
            fn_801FCE10(&result, "use 'EVAS' delete from 'SWSH' where 'KPWH' = \x82\n", key);
            flag |= result.mUnknown0 != 0;
            count--;
        }
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
    }

    fn_801FCE10(&result, "use 'EVAS' select count(*) into \x82 from 'KTSH'\n", &count);
    if (count > 10) {
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KPTH' into \x82 from 'KTSH' order by 'TPTH' asc\n", &cursor, &key);
        while (count > 10) {
            cursor.mUnknown4 = 0;
            fn_801FCE10(&result, "fetch from \x8a\n", &cursor);
            fn_801FCE10(&result, "use 'EVAS' delete from 'KTSH' where 'KPTH' = \x82\n", key);
            flag |= result.mUnknown0 != 0;
            count--;
        }
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
    }

    if (flag) {
        _Records_bSaveChanged = 1;
    }
    RecordsEnd();
}

void RecordsSeekRow(int a, int b)
{
    RecordsSelectCategory(a);
    if (_Records_iRow != b) {
        RecordsFetchRow(b);
    }
}

int RecordsGetValue(int a)
{
    int value = 0;
    switch (a) {
    case 1:
        break;
    case 2:
        value = _Records_sRow.mUnknown20;
        break;
    case 3:
        value = _Records_sRow.mUnknown24;
        break;
    case 4:
        value = _Records_sRow.mUnknown28;
        break;
    case 5:
        value = _Records_sRow.mUnknown32;
        break;
    case 6:
        value = _Records_sRow.mUnknown36;
        break;
    case 7:
        value = _Records_sRow.mUnknown40;
        break;
    case 8:
        value = _Records_sRow.mUnknown44;
        break;
    case 9:
        value = _Records_sRow.mUnknown104;
        break;
    case 10:
        value = _Records_sRow.mUnknown48;
        break;
    case 11:
        value = _Records_sRow.mUnknown52;
        break;
    case 12:
        value = _Records_sRow.mUnknown56;
        break;
    case 13:
        value = _Records_sRow.mUnknown60;
        break;
    case 14:
        value = _Records_sRow.mUnknown64;
        break;
    case 15:
        value = _Records_sRow.mUnknown68;
        break;
    case 16:
        break;
    case 17:
        value = _Records_sRow.mUnknown72;
        break;
    case 18:
        value = _Records_sRow.mUnknown76;
        break;
    case 19:
        value = _Records_sRow.mUnknown80;
        break;
    case 20:
        value = _Records_sRow.mUnknown84;
        break;
    case 21:
        if (_Records_sRow.mUnknown92 != 0) {
            value = _Records_sRow.mUnknown88 * 100 / _Records_sRow.mUnknown92;
        }
        break;
    case 22:
        value = _Records_sRow.mUnknown96;
        break;
    case 23:
        value = _Records_sRow.mUnknown100;
        break;
    case 24:
        break;
    }
    return value;
}

void RecordsSetSharedRanks(int a)
{
    _Records_bSharedRanks = a;
}

}
