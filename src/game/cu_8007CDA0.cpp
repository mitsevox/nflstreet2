#include <stdio.h>
#include <string.h>

#include "game/fn_801FCE10.h"

struct Record_8030BA00 {
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
int fn_80029D74(int type, int index);
void fn_80029CE0(int type, int index);
void fn_8007B684(int id);
void fn_8007B8A4(char *pDest, int count);
void fn_8007B6D4(void);
void fn_801880D4(int value, char *pText, int size);

void fn_8007CDA0(int type);
void fn_8007CEA4(int type);
void fn_8007D26C(int type);
void fn_8007D298(int row);
int fn_8007D2E8(int column, int row, char *pText, int size);
int fn_8007D448(int row);
void fn_8007D4E8(void);
void fn_8007D52C(void);
int fn_8007D5A0(int type, int value, int column, char *pText, int size);
void fn_8007D654(void);
void fn_8007DB74(int a, int b);
int fn_8007DBB4(int a);
void fn_8007DDC0(int a);
}

static int sColumnTypes[24] = {
    24, 2, 3, 4, 5, 6, 24, 9, 7, 8, 10, 11,
    12, 13, 14, 15, 17, 18, 22, 22, 22, 22, 23, 19
};

static Record_8030BA00 sRecord;
static QueryCursor sCursor;
static int lbl_803EA7A8 = -1;
static int lbl_803EC854;
static int lbl_803EC858;
static unsigned char lbl_803EC85C;
static unsigned char lbl_803EC85D;
static int lbl_803EC860;
static int lbl_803EC864;

extern "C" {

void fn_8007CDA0(int type)
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

void fn_8007CEA4(int type)
{
    QueryResult result;
    int tag = -1;
    if (lbl_803EA7A8 != -1) {
        if (sCursor.mUnknown0) {
            fn_801FCFA0(&sCursor);
        }
        lbl_803EA7A8 = -1;
    }
    sCursor.mUnknown0 = 0;
    sCursor.mUnknown4 = 0;
    sCursor.mUnknown8 = -1;
    sCursor.mUnknown12 = 0;
    if (type == 6) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'DFSH'.'KTFH' into \x82 and 'DFSH'.'KUFH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'DFSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'DFSH'.'KUFH' order by 'DFSH'.'DIVE' asc\n",
                    &sCursor, &sRecord.mUnknown32, &sRecord.mUnknown108, sRecord.mUnknown0);
    } else if (type == 4) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KTSH'.'TPTH' into \x82 and 'KTSH'.'KUTH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'KTSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'KTSH'.'KUTH' order by 'KTSH'.'TPTH' desc and 'RCSH'.'KUSH' asc\n",
                    &sCursor, &sRecord.mUnknown32, &sRecord.mUnknown108, sRecord.mUnknown0);
    } else if (type == 2) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'SWSH'.'SWWH' into \x82 and 'SWSH'.'KUWH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'SWSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'SWSH'.'KUWH' order by 'SWSH'.'SWWH' desc and 'RCSH'.'KUSH' asc\n",
                    &sCursor, &sRecord.mUnknown24, &sRecord.mUnknown108, sRecord.mUnknown0);
    } else if (type == 0) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'HCSH'.'KUCH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'HCSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'HCSH'.'KUCH' order by 'KPCH' desc\n",
                    &sCursor, &sRecord.mUnknown108, sRecord.mUnknown0);
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
                    &sCursor, &sRecord.mUnknown96, &sRecord.mUnknown108, sRecord.mUnknown0, count);
    } else if (type == 22) {
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'BJSH'.'SJSH' into \x82 and 'BJSH'.'UBJH' into \x82 and 'RCSH'.'KUSH' into \x88 from 'BJSH' inner join 'RCSH' on 'RCSH'.'KPSH' = 'BJSH'.'UBJH' order by 'BJSH'.'SJSH' desc\n",
                    &sCursor, &sRecord.mUnknown100, &sRecord.mUnknown108, sRecord.mUnknown0);
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
            fn_8007CDA0(7);
            tag = 0x43535348;
            break;
        default:
            tag = -1;
            break;
        }
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'KUSH' into \x88 and 'WGSH' into \x82 and 'PTSH' into \x82 and 'TPSH' into \x82 and 'TRSH' into \x82 and 'TDSH' into \x82 and 'TSSH' into \x82 and 'CISH' into \x82 and 'RFSH' into \x82 and 'GTSH' into \x82 and '2TSH' into \x82 and 'TTSH' into \x82 and 'KSSH' into \x82 and 'WQSH' into \x82 and 'WOSH' into \x82 and 'LOSH' into \x82 and 'SOSH' into \x82 and 'AOSH' into \x82 and 'CSSH' into \x82 from 'RCSH' order by \x8c desc and 'KUSH' asc\n",
                    &sCursor, sRecord.mUnknown0, &sRecord.mUnknown20, &sRecord.mUnknown28,
                    &sRecord.mUnknown40, &sRecord.mUnknown44, &sRecord.mUnknown48, &sRecord.mUnknown52,
                    &sRecord.mUnknown56, &sRecord.mUnknown60, &sRecord.mUnknown64, &sRecord.mUnknown68,
                    &sRecord.mUnknown36, &sRecord.mUnknown72, &sRecord.mUnknown76, &sRecord.mUnknown80,
                    &sRecord.mUnknown84, &sRecord.mUnknown88, &sRecord.mUnknown92, &sRecord.mUnknown104, tag);
    }
    lbl_803EA7A8 = type;
    lbl_803EC858 = result.mUnknown0;
    lbl_803EC854 = -1;
}

void fn_8007D26C(int type)
{
    if (lbl_803EA7A8 != type) {
        fn_8007CEA4(type);
    }
}

void fn_8007D298(int row)
{
    QueryResult result;
    sCursor.mUnknown4 = row;
    fn_801FCE10(&result, "fetch from \x8a\n", &sCursor);
    lbl_803EC854 = row;
}

int fn_8007D2E8(int column, int row, char *pText, int size)
{
    int value = fn_8007DBB4(column);
    switch (column) {
    case 0:
        sprintf(pText, "%d", fn_8007D448(row));
        break;
    case 1: {
        sprintf(pText, sRecord.mUnknown0);
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
        fn_8007B684(row);
        fn_8007B8A4(pText, size);
        fn_8007B6D4();
        break;
    case 24:
    default:
        sprintf(pText, " ");
        break;
    }
    return 0;
}

int fn_8007D448(int row)
{
    int result = row + 1;
    if (lbl_803EC85D != 0) {
        if (sColumnTypes[lbl_803EA7A8] != 24) {
            if (row == 0) {
                lbl_803EC860 = fn_8007DBB4(sColumnTypes[lbl_803EA7A8]);
                lbl_803EC864 = 1;
            } else if (fn_8007DBB4(sColumnTypes[lbl_803EA7A8]) != lbl_803EC860) {
                lbl_803EC860 = fn_8007DBB4(sColumnTypes[lbl_803EA7A8]);
                lbl_803EC864 = result;
            }
            result = lbl_803EC864;
        }
    }
    return result;
}

void fn_8007D4E8(void)
{
    lbl_803EC85C = fn_80029D74(1, 0);
    lbl_803EC85D = 0;
    lbl_803EC860 = 0;
    lbl_803EC864 = 1;
}

void fn_8007D52C(void)
{
    if (lbl_803EA7A8 != -1) {
        if (sCursor.mUnknown0) {
            fn_801FCFA0(&sCursor);
        }
        lbl_803EA7A8 = -1;
    }
    if (lbl_803EC85C == 0 && fn_80029D74(1, 0) != 0) {
        fn_80029CE0(1, 0);
    }
}

int fn_8007D5A0(int type, int value, int column, char *pText, int size)
{
    char text[32] = " ";
    int result = 0;
    fn_8007D26C(type);
    if (lbl_803EC854 != value) {
        fn_8007D298(value);
    }
    if (value < lbl_803EC858) {
        result = fn_8007D2E8(column, value, text, 32);
    }
    memcpy(pText, text, size);
    return result;
}

void fn_8007D654(void)
{
    QueryResult result;
    QueryCursor cursor;
    int count;
    int key;
    unsigned char flag = 0;
    int type;

    fn_8007D4E8();
    fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'UFSH' = 0\n");
    for (type = 0; type <= 23; type++) {
        int status = 0;
        fn_8007CEA4(type);
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
                fn_8007D298(count);
                status = fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'UFSH' = 1 where 'KPSH' = \x82\n", sRecord.mUnknown108);
            }
            break;
        default:
            for (count = 0, status = 0; status == 0 && count <= 9; count++) {
                fn_8007D298(count);
                status = fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'UFSH' = 1 where 'KUSH' = \x88\n", sRecord.mUnknown0);
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
        lbl_803EC85C = 1;
    }
    fn_8007D52C();
}

void fn_8007DB74(int a, int b)
{
    fn_8007D26C(a);
    if (lbl_803EC854 != b) {
        fn_8007D298(b);
    }
}

int fn_8007DBB4(int a)
{
    int value = 0;
    switch (a) {
    case 1:
        break;
    case 2:
        value = sRecord.mUnknown20;
        break;
    case 3:
        value = sRecord.mUnknown24;
        break;
    case 4:
        value = sRecord.mUnknown28;
        break;
    case 5:
        value = sRecord.mUnknown32;
        break;
    case 6:
        value = sRecord.mUnknown36;
        break;
    case 7:
        value = sRecord.mUnknown40;
        break;
    case 8:
        value = sRecord.mUnknown44;
        break;
    case 9:
        value = sRecord.mUnknown104;
        break;
    case 10:
        value = sRecord.mUnknown48;
        break;
    case 11:
        value = sRecord.mUnknown52;
        break;
    case 12:
        value = sRecord.mUnknown56;
        break;
    case 13:
        value = sRecord.mUnknown60;
        break;
    case 14:
        value = sRecord.mUnknown64;
        break;
    case 15:
        value = sRecord.mUnknown68;
        break;
    case 16:
        break;
    case 17:
        value = sRecord.mUnknown72;
        break;
    case 18:
        value = sRecord.mUnknown76;
        break;
    case 19:
        value = sRecord.mUnknown80;
        break;
    case 20:
        value = sRecord.mUnknown84;
        break;
    case 21:
        if (sRecord.mUnknown92 != 0) {
            value = sRecord.mUnknown88 * 100 / sRecord.mUnknown92;
        }
        break;
    case 22:
        value = sRecord.mUnknown96;
        break;
    case 23:
        value = sRecord.mUnknown100;
        break;
    case 24:
        break;
    }
    return value;
}

void fn_8007DDC0(int a)
{
    lbl_803EC85D = a;
}

}
