#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_80168ED0(int a);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int fn_80085810(int formation, int team, int *pValues);
}

static int sRecord[14];
static unsigned char sRecordValid = 0;

extern "C" {

/* Query outputs replace the IDs in each list; any failure makes the result zero. */
int fn_80085148(int *pFirst, int *pSecond)
{
    int result = 1;
    for (unsigned int i = 0; i < 14; i++) {
        if (fn_801FCE10(0, "select 'DIGP' into \x85 from 'YALP' where 'DIOP' = \x85 and 'DIGT' = \x82\n", &pFirst[i], pFirst[i], 0) != 0) {
            result = 0;
        }
    }
    for (unsigned int i = 0; i < 14; i++) {
        if (fn_801FCE10(0, "select 'DIGP' into \x85 from 'YALP' where 'DIOP' = \x85 and 'DIGT' = \x82\n", &pSecond[i], pSecond[i], 1) != 0) {
            result = 0;
        }
    }
    return result;
}

/* The shared record is available only after a successful fetch. */
int *fn_80085208(int formation, int team, int table)
{
    QueryCursor cursor;
    int *pResult = 0;
    sRecordValid = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = fn_801FCE10(0, "use 'EMAG' declare \x8a cursor for select * from \x8c where ( 'NMRF' = \x85 and 'DIGT' = \x82 )\n", &cursor, table, formation, team);
    if (status == 0) {
        status = fn_801FCE10(0, "fetch from \x8a 'ZBQF' into \x85 and 'ZBRF' into \x85 and 'FRWF' into \x85 and 'BRWF' into \x85 and 'LLOF' into \x85 and 'CLOF' into \x85 and 'RLOF' into \x85 and 'LLDF' into \x85 and 'RLDF' into \x85 and 'FBLF' into \x85 and 'BBLF' into \x85 and 'LBDF' into \x85 and 'CBDF' into \x85 and 'RBDF' into \x85\n", &cursor,
                            &sRecord[0], &sRecord[1], &sRecord[2], &sRecord[3],
                            &sRecord[4], &sRecord[5], &sRecord[6], &sRecord[7],
                            &sRecord[8], &sRecord[9], &sRecord[10], &sRecord[11],
                            &sRecord[12], &sRecord[13]);
        if (status == 0) {
            sRecordValid = 1;
            pResult = sRecord;
        }
        if (QUERY_STATUS_ACCEPTED(status) == true) {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        } else {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        }
    }
    return pResult;
}

static int fn_8008535C(int value, int *pKeys, int *pValues)
{
    int result = 0;
    for (int i = 0; i < 14; i++) {
        if (pKeys[i] == value) {
            result = pValues[i];
            break;
        }
    }
    return result;
}

/* Replace each cached value with the first matching key's mapped value. */
int fn_800853A0(int formation, int team, int *pKeys, int *pValues)
{
    int result = 0;
    int *pRecord = fn_80085208(formation, team, 0x424C4D46);
    if (pRecord) {
        for (int i = 0; i < 14; i++) {
            pRecord[i] = fn_8008535C(pRecord[i], pKeys, pValues);
        }
        result = fn_80085810(formation, team, pRecord);
    }
    return result;
}

int fn_80085428(int a, int b, float *pX, float *pY, int *pValue,
                char *pLabel, int labelSize)
{
    QueryCursor cursor;
    char label[8];
    int x = 0;
    int y = 0;
    int result = 0;
    int mode = fn_80168ED0(a);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = fn_801FCE10(0, "use 'TATS' declare \x8a cursor for select * from 'IIUF' where ( 'OIFP' = \x83 and 'DIBP' = \x85 and 'NTLS' = \x82 )\n", &cursor, a, mode, b);
    if (status == 0) {
        status = fn_801FCE10(0, "fetch from \x8a 'LBLP' into \x88 and 'XSOP' into \x82 and 'YSOP' into \x82 and 'EPDB' into \x85\n", &cursor, label, &x, &y, pValue);
        *pX = x;
        *pY = y;
        if (status == 0) {
            result = 1;
            strncpy(pLabel, label, labelSize);
        }
        if (QUERY_STATUS_ACCEPTED(status) == true) {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        } else {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        }
    } else {
        *pX = 0.0f;
        *pY = 0.0f;
        *pValue = 0;
        fn_801C2E18(pLabel, "??");
    }
    return result;
}

int fn_800855C8(int a)
{
    int count = 0;
    int mode = fn_80168ED0(a);
    fn_801FCE10(0, "use 'TATS' select count(*) into \x85 from 'ILMF' where ( 'DIBP' = \x85 and 'FOSI' = \x83 )\n", &count, mode, a);
    return count;
}

extern const char lbl_80294050[] = "use 'TATS' declare \x8a cursor for select * from 'ILMF' where ( 'OFLP' = \x85 and 'DIBP' = \x85 and 'FOSI' = \x83 )\n";
extern const char lbl_802940BC[] = "fetch from \x8a 'NFIU' into \x88\n";

/* Keep fetching through the requested index, but reject any intervening failure. */
int fn_80085620(int index, int a)
{
    QueryCursor cursor;
    int value = 0;
    int mode = fn_80168ED0(a);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = fn_801FCE10(0, "use 'TATS' declare \x8a cursor for select * from 'ILMF' where ( 'DIBP' = \x85 and 'FOSI' = \x83 )\n", &cursor, mode, a);
    if (status == 0) {
        int valid = 1;
        for (int i = 0; i <= index; i++) {
            status = fn_801FCE10(0, "fetch from \x8a 'OFLP' into \x85\n", &cursor, &value);
            if (status != 0) valid = 0;
        }
        if (QUERY_STATUS_ACCEPTED(status) == true) {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        } else {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        }
        if (!valid) value = 0;
    }
    return value;
}

int *fn_80085744(int formation, int team)
{
    return fn_80085208(formation, team, 0x554C4D46);
}

int fn_8008576C(int value, int firstHalf)
{
    int result = 255;
    if (sRecordValid) {
        int start = firstHalf ? 0 : 7;
        int end = firstHalf ? 6 : 13;
        for (int i = start; i <= end; i++) {
            if (sRecord[i] == value) {
                result = i;
                break;
            }
        }
    }
    return result;
}
}
