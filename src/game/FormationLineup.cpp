/* Formation lineups: which player fills each of the fourteen positions of a formation for
   a team, the screen position and label of each lineup slot, and the formations of a
   playbook. */

#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int PlayCallGetPlaybookId(int a);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int FormationLineupStoreUser(int formation, int team, int *pValues);
}

static int _FormationLineup_aSlots[14];
static unsigned char _FormationLineup_bValid = 0;

extern "C" {

/* Query outputs replace the IDs in each list; any failure makes the result zero. */
int FormationLineupMapPlayerIds(int *pFirst, int *pSecond)
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
int *FormationLineupFetch(int formation, int team, int table)
{
    QueryCursor cursor;
    int *pResult = 0;
    _FormationLineup_bValid = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = fn_801FCE10(0, "use 'EMAG' declare \x8a cursor for select * from \x8c where ( 'NMRF' = \x85 and 'DIGT' = \x82 )\n", &cursor, table, formation, team);
    if (status == 0) {
        status = fn_801FCE10(0, "fetch from \x8a 'ZBQF' into \x85 and 'ZBRF' into \x85 and 'FRWF' into \x85 and 'BRWF' into \x85 and 'LLOF' into \x85 and 'CLOF' into \x85 and 'RLOF' into \x85 and 'LLDF' into \x85 and 'RLDF' into \x85 and 'FBLF' into \x85 and 'BBLF' into \x85 and 'LBDF' into \x85 and 'CBDF' into \x85 and 'RBDF' into \x85\n", &cursor,
                            &_FormationLineup_aSlots[0], &_FormationLineup_aSlots[1], &_FormationLineup_aSlots[2], &_FormationLineup_aSlots[3],
                            &_FormationLineup_aSlots[4], &_FormationLineup_aSlots[5], &_FormationLineup_aSlots[6], &_FormationLineup_aSlots[7],
                            &_FormationLineup_aSlots[8], &_FormationLineup_aSlots[9], &_FormationLineup_aSlots[10], &_FormationLineup_aSlots[11],
                            &_FormationLineup_aSlots[12], &_FormationLineup_aSlots[13]);
        if (status == 0) {
            _FormationLineup_bValid = 1;
            pResult = _FormationLineup_aSlots;
        }
        if (QUERY_STATUS_ACCEPTED(status) == true) {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        } else {
            if (cursor.mUnknown0) fn_801FCFA0(&cursor);
        }
    }
    return pResult;
}

static int _FormationLineupLookup(int value, int *pKeys, int *pValues)
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
int FormationLineupRemapBase(int formation, int team, int *pKeys, int *pValues)
{
    int result = 0;
    int *pRecord = FormationLineupFetch(formation, team, 0x424C4D46);
    if (pRecord) {
        for (int i = 0; i < 14; i++) {
            pRecord[i] = _FormationLineupLookup(pRecord[i], pKeys, pValues);
        }
        result = FormationLineupStoreUser(formation, team, pRecord);
    }
    return result;
}

int FormationSlotGetInfo(int a, int b, float *pX, float *pY, int *pValue,
                char *pLabel, int labelSize)
{
    QueryCursor cursor;
    char label[8];
    int x = 0;
    int y = 0;
    int result = 0;
    int mode = PlayCallGetPlaybookId(a);
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

int FormationCountForPlaybook(int a)
{
    int count = 0;
    int mode = PlayCallGetPlaybookId(a);
    fn_801FCE10(0, "use 'TATS' select count(*) into \x85 from 'ILMF' where ( 'DIBP' = \x85 and 'FOSI' = \x83 )\n", &count, mode, a);
    return count;
}

extern const char gFormationLineupFormationQuery[] = "use 'TATS' declare \x8a cursor for select * from 'ILMF' where ( 'OFLP' = \x85 and 'DIBP' = \x85 and 'FOSI' = \x83 )\n";
extern const char gFormationLineupFetchUifnQuery[] = "fetch from \x8a 'NFIU' into \x88\n";

/* Keep fetching through the requested index, but reject any intervening failure. */
int FormationGetByIndex(int index, int a)
{
    QueryCursor cursor;
    int value = 0;
    int mode = PlayCallGetPlaybookId(a);
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

int *FormationLineupFetchUser(int formation, int team)
{
    return FormationLineupFetch(formation, team, 0x554C4D46);
}

int FormationLineupFindSlot(int value, int firstHalf)
{
    int result = 255;
    if (_FormationLineup_bValid) {
        int start = firstHalf ? 0 : 7;
        int end = firstHalf ? 6 : 13;
        for (int i = start; i <= end; i++) {
            if (_FormationLineup_aSlots[i] == value) {
                result = i;
                break;
            }
        }
    }
    return result;
}
}
