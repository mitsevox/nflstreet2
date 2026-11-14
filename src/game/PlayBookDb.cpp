/* Playbook database: reads formations, play sets, plays and their position
   alignments, routes and scripts from the playbook tables (MFBP, TSBP, LTES,
   PTES, GTES, LPBP, LYLP and their detail tables) into the team's playbook
   records, counts and orders their rows, picks AI plays by weight and stores
   audible choices. */
#include "engine/fn_801F8D60.h"
#include "engine/tdbext.h"
#include <stdio.h>

#include "game/PlayCandidate.h"
#include "game/DbCursor.h"
#include "game/QueryStatus.h"
#include "game/DbQueryTable.h"
#include "game/PlayBookTeam.h"
#include "game/PlayBookDb.h"
#include <string.h>
#include "game/fn_801FCE10.h"
#include "game/fn_802372EC.h"

extern "C" {
extern char lbl_802EBDF8[];

unsigned int PlayBookGetLoadFlags(void);
void PlayTrackWeightCandidates(int team, PlayCandidate_t *pList, unsigned int count);
void SortArray(int a, void *pBase, int count, int size,
                 int (*pCompare)(PlayCandidate_t *, PlayCandidate_t *),
                 void (*pSwap)(PlayCandidate_t *, PlayCandidate_t *), int b, int c);
int fn_801FA0BC(int handle, DbQueryTable *pTables, DbFilter *pFilter, void *pSort, int *pCursor,
                QueryResult *pResult);
}

#if defined(DECOMP_COMPARE)
static const char *_PlayBookDb_apPositionNames[25] = {
    "QB", "HB", "FB", "WR", "TE", "LT", "LG", "C", "RG", "RT", "LE", "RE", "DT",
    "LOLB", "MLB", "ROLB", "CB", "FS", "SS", "K", "P", "KR", "PR", "KOS", "LS"
};

static unsigned char _PlayBookDb_aAnimCodes[8] = { 0xFF, 0x55, 0x56, 0x56, 0x55, 0x5B, 0x5B, 0xFF };
static int _PlayBookDb_iState0 = 0;
static int _PlayBookDb_iState1 = 0;
static int _PlayBookDb_iState2 = 0;
static int _PlayBookDb_iState3 = 0;
#endif

extern "C" {

void PlayBookDbLoadPositionSteps(int tag, int index, int key, PlayBookSet_t *pObject);

void PlayBookDbLoadSetHeader(int tag, int key, int index, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject);
void PlayBookDbLoadSetRecord(int tag, int key, PlayBookSet_t *pObject);
void PlayBookDbLoadSetPositions(int tag, int key, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject);
void PlayBookDbLoadSetSlots(int tag, int key, PlayBookSet_t *pObject);
void PlayBookDbLoadPlayHeader(int tag, int key, int index, PlayBookPlay_t *pRecord);
int PlayBookDbLoadPlayRecord(int tag, int key, PlayBookPlay_t *pRecord);
void PlayBookDbLoadPlayDetails(int tag, int key, unsigned int kind, PlayBookPlay_t *pRecord);
void PlayBookDbLoadPlayHole(int tag, int key, PlayBookPlay_t *pRecord);
void PlayBookDbLoadPlayReceivers(int tag, int key, PlayBookPlay_t *pRecord);
void PlayBookDbLoadPlayCommands(int tag, int key, PlayBookPlay_t *pRecord);
void PlayBookDbResetState(void);
int PlayBookDbOpen(unsigned int id, int a, int b, int c, int d, int e);
void PlayBookDbClose(unsigned int id, int a);
void PlayBookDbLoadPlayScripts(int tag, int key, PlayBookPlay_t *pRecord, int flag);

#if defined(DECOMP_COMPARE)
/* Discarded by the GameCube linker; body from the Xbox counterpart 0x195410. */
const char *GetPositionString(int index)
{
    return _PlayBookDb_apPositionNames[index];
}

void PlayBookDbLoadSetHeader(int tag, int key, int index, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject)
{
    DbFilter filter;
    DbFilter orderFilter;
    DbFilter keyFilter;
    DbQueryTable tables[2] = { { 0x54534250 }, { -1 } };
    DbColumnValue columns[4] = {
        { 0, 0x54534250, 0x656D616E },
        { 0, 0x54534250, 0x54534250 },
        { 0, 0x54534250, 0x4C544553 },
        { 0, -1, -1 }
    };

    columns[0].mValue = (int)pObject->mUnknownC8C;
    filter.mUnknown32 = 0x20009;
    filter.mUnknown0.Set(11, &orderFilter);
    filter.mUnknown16.Set(11, &keyFilter);
    orderFilter.mUnknown32 = 0x10003;
    orderFilter.mUnknown0.Set(6, ((long long)0x54534250 << 32) | 0x5F64726F);
    {
        DbFilterOperand *pOp = &orderFilter.mUnknown16;
        pOp->Set(3, index + 1);
    }
    keyFilter.mUnknown32 = 0x10003;
    keyFilter.mUnknown0.Set(6, ((long long)0x54534250 << 32) | 0x4D464250);
    {
        DbFilterOperand *pOp = &keyFilter.mUnknown16;
        pOp->Set(3, key);
    }
    fn_801FA290(tag, tables, &filter, columns);
    pObject->mUnknown0 = columns[1].mValue;
    pObject->mUnknown4 = columns[2].mValue;
}

void PlayBookDbLoadSetRecord(int tag, int key, PlayBookSet_t *pObject)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x4C544553 }, { -1 } };
    DbColumnValue columns[7] = {
        { 0, 0x4C544553, 0x4D524F46 },
        { 0, 0x4C544553, 0x4E544F4D },
        { 0, 0x4C544553, 0x6F736F70 },
        { 0, 0x4C544553, 0x54544953 },
        { 0, 0x4C544553, 0x5F464C53 },
        { 0, 0x4C544553, 0x54544553 },
        { 0, -1, -1 }
    };

    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x4C544553 << 32) | 0x4C544553, 3, key);
    fn_801FA290(tag, tables, &filter, columns);
    pObject->mUnknown8 = columns[0].mValue;
    pObject->mUnknownC = columns[1].mValue;
    pObject->mUnknownE = columns[2].mValue;
    pObject->mUnknown14 = columns[4].mValue;
    pObject->mUnknown10 = columns[5].mValue;
    pObject->mUnknownF = 0;
}

void PlayBookDbLoadSetPositions(int tag, int key, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x50544553 }, { -1 } };
    DbColumnValue columns[12] = {
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
    unsigned int flags = PlayBookGetLoadFlags();
    int opened = 0;
    int status;

    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x50544553 << 32) | 0x4C544553, 3, key);
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
                PlayBookDbLoadPositionSteps(tag, index, pObject->mUnknown84[0][index].mUnknownC, pObject);
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

void PlayBookDbLoadPositionSteps(int tag, int index, int key, PlayBookSet_t *pObject)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x47544553 }, { -1 } };
    DbColumnValue columns[11] = {
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
    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x47544553 << 32) | 0x50544553, 3, key);
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
            pObject->mUnknown84[row][index].mUnknown9 = _PlayBookDb_aAnimCodes[columns[4].mValue];
            pObject->mUnknown84[row][index].mUnknown18.mX = *(float *)&columns[5].mValue;
            pObject->mUnknown84[row][index].mUnknown18.mY = *(float *)&columns[6].mValue;
            pObject->mUnknown84[row][index].mUnknown24 = (int)((float)((columns[7].mValue * 360) >> 8) * 46603.379f);
            pObject->mUnknown84[row][index].mUnknownA = _PlayBookDb_aAnimCodes[columns[8].mValue];
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

void PlayBookDbLoadSetSlots(int tag, int key, PlayBookSet_t *pObject)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x00464753 }, { -1 } };
    DbColumnValue columns[4] = {
        { 0, 0x00464753, 0x656D616E },
        { 0, 0x00464753, 0x5F464753 },
        { 0, 0x00464753, 0x746C6664 },
        { 0, -1, -1 }
    };
    int cursor;
    unsigned int count = 0;
    int opened = 0;
    int status;

    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x00464753 << 32) | 0x4C544553, 3, key);
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

void PlayBookDbLoadPlayHeader(int tag, int key, int index, PlayBookPlay_t *pRecord)
{
    DbFilter filter;
    DbFilter keyFilter;
    DbFilter orderFilter;
    DbQueryTable tables[2] = { { 0x4C504250 }, { -1 } };
    DbColumnValue columns[4] = {
        { 0, 0x4C504250, 0x4C594C50 },
        { 0, 0x4C504250, 0x4C504250 },
        { 0, 0x4C504250, 0x5F64726F },
        { 0, -1, -1 }
    };

    filter.mUnknown32 = 0x20009;
    filter.mUnknown0.Set(11, &keyFilter);
    filter.mUnknown16.Set(11, &orderFilter);
    keyFilter.mUnknown32 = 0x10003;
    keyFilter.mUnknown0.Set(6, ((long long)0x4C504250 << 32) | 0x54534250);
    {
        DbFilterOperand *pOp = &keyFilter.mUnknown16;
        pOp->Set(3, key);
    }
    orderFilter.mUnknown32 = 0x10003;
    orderFilter.mUnknown0.Set(6, ((long long)0x4C504250 << 32) | 0x5F64726F);
    {
        DbFilterOperand *pOp = &orderFilter.mUnknown16;
        pOp->Set(3, index + 1);
    }
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknown0 = columns[0].mValue;
    pRecord->mUnknown4 = columns[1].mValue;
    pRecord->mUnknown8 = columns[2].mValue;
}

int PlayBookDbLoadPlayRecord(int tag, int key, PlayBookPlay_t *pRecord)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x4C594C50 }, { -1 } };
    DbColumnValue columns[9] = {
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
    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x4C594C50 << 32) | 0x4C594C50, 3, key);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknownD = columns[1].mValue;
    pRecord->mUnknownC = columns[2].mValue;
    pRecord->mUnknown10 = columns[3].mValue;
    pRecord->mUnknown18 = columns[5].mValue;
    pRecord->mUnknown14 = columns[6].mValue;
    return columns[7].mValue;
}

void PlayBookDbLoadPlayDetails(int tag, int key, unsigned int kind, PlayBookPlay_t *pRecord)
{
    memset(pRecord->mUnknown1C, 0, sizeof(pRecord->mUnknown1C));
    switch (kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        PlayBookDbLoadPlayReceivers(tag, key, pRecord);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        PlayBookDbLoadPlayHole(tag, key, pRecord);
        break;
    case 21:
        break;
    }
    PlayBookDbLoadPlayCommands(tag, key, pRecord);
}

void PlayBookDbLoadPlayHole(int tag, int key, PlayBookPlay_t *pRecord)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x44524C50 }, { -1 } };
    DbColumnValue columns[2] = {
        { 0, 0x44524C50, 0x656C6F68 },
        { 0, -1, -1 }
    };

    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x44524C50 << 32) | 0x4C594C50, 3, key);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknown1C[0][0] = columns[0].mValue;
}

void PlayBookDbLoadPlayReceivers(int tag, int key, PlayBookPlay_t *pRecord)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x44504C50 }, { -1 } };
    DbColumnValue columns[7] = {
        { 0, 0x44504C50, 0x31766372 },
        { 0, 0x44504C50, 0x31726570 },
        { 0, 0x44504C50, 0x32766372 },
        { 0, 0x44504C50, 0x32726570 },
        { 0, 0x44504C50, 0x33766372 },
        { 0, 0x44504C50, 0x33726570 },
        { 0, -1, -1 }
    };

    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x44504C50 << 32) | 0x4C594C50, 3, key);
    fn_801FA290(tag, tables, &filter, columns);
    pRecord->mUnknown1C[0][0] = columns[0].mValue;
    pRecord->mUnknown1C[0][1] = columns[1].mValue;
    pRecord->mUnknown1C[1][0] = columns[2].mValue;
    pRecord->mUnknown1C[1][1] = columns[3].mValue;
    pRecord->mUnknown1C[2][0] = columns[4].mValue;
    pRecord->mUnknown1C[2][1] = columns[5].mValue;
}

void PlayBookDbLoadPlayCommands(int tag, int key, PlayBookPlay_t *pRecord)
{
    DbFilter filter;
    DbQueryTable tables[2] = { { 0x4D434C50 }, { -1 } };
    DbColumnValue columns[16] = {
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

    filter.mUnknown32 = 0x10003;
    filter.SetOperands(6, ((long long)0x4D434C50 << 32) | 0x4C594C50, 3, key);
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

void PlayBookDbResetState(void)
{
    _PlayBookDb_iState0 = 0;
    _PlayBookDb_iState1 = 0;
    _PlayBookDb_iState2 = 0;
    _PlayBookDb_iState3 = 0;
}

int PlayBookDbOpen(unsigned int id, int a, int b, int c, int d, int e)
{
    int result = fn_801F8D60(id, 0x80000);

    if (result == 0) {
        result = TDbExtLoadFromResource(id, lbl_802EBDF8, a, 0);
    }
    return result;
}

void PlayBookDbClose(unsigned int id, int a)
{
    fn_801F8EEC(id);
}

void PlayBookDbLoadPlayScripts(int tag, int key, PlayBookPlay_t *pRecord, int flag)
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
        if (flag) {
            fn_801FCE10(0, "use \x8c select 'LTES' into \x85 from 'LYLP' where 'LYLP' = \x85\n", tag, &set, key);
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
                        &list, key, i);
            if (flag) {
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

#endif

unsigned short PlayBookDbCountFormations(int tag, int kind)
{
    DbFilter filter;
    unsigned short count;

    filter.mUnknown32 = 0x10003;
    filter.mUnknown0.mKind = 6;
    filter.mUnknown0.mValue.mLong = ((long long)0x4D464250 << 32) | 0x50595446;
    filter.mUnknown16.mKind = 3;
    filter.mUnknown16.mValue.mInt = kind;
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

int PlayBookDbLoadFormation(int tag, int a, int b, PlayBookFormation_t *pObject)
{
    memset(pObject, 0, sizeof(*pObject));
    return fn_801FCE10(0,
                       "use \x8c select 'MFBP' into \x85 and 'eman' into \x88 from 'MFBP' where 'PYTF' = \x82 and "
                       "'_dro' = \x82\n",
                       tag, pObject, pObject->mUnknownCB0, a, b + 1);
}

unsigned short PlayBookDbCountSets(int tag, int key)
{
    DbFilter filter;
    unsigned short count;

    filter.mUnknown32 = 0x10003;
    filter.mUnknown0.mKind = 6;
    filter.mUnknown0.mValue.mLong = ((long long)0x54534250 << 32) | 0x4D464250;
    filter.mUnknown16.mKind = 3;
    filter.mUnknown16.mValue.mInt = key;
    if (fn_801F9D70(tag, 0x54534250, &filter, &count) != 0) {
        count = 0;
    }
    return count;
}

void PlayBookDbLoadSetByOrder(int tag, int key, int index, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject)
{
    memset(pObject, 0, sizeof(*pObject));
    PlayBookDbLoadSetHeader(tag, key, index, pTeam, pObject);
    if (pObject->mUnknown4) {
        PlayBookDbLoadSetRecord(tag, pObject->mUnknown4, pObject);
        PlayBookGetLoadFlags();
        PlayBookDbLoadSetPositions(tag, pObject->mUnknown4, pTeam, pObject);
        PlayBookDbLoadSetSlots(tag, pObject->mUnknown4, pObject);
    }
}

void PlayBookDbLoadSet(int tag, int key, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject)
{
    memset(pObject, 0, sizeof(*pObject));
    pObject->mUnknown4 = key;
    PlayBookDbLoadSetRecord(tag, key, pObject);
    PlayBookGetLoadFlags();
    PlayBookDbLoadSetPositions(tag, key, pTeam, pObject);
    PlayBookDbLoadSetSlots(tag, key, pObject);
}

unsigned short PlayBookDbCountPlays(int tag, int key)
{
    DbFilter filter;
    unsigned short count;

    filter.mUnknown32 = 0x10003;
    filter.mUnknown0.mKind = 6;
    filter.mUnknown0.mValue.mLong = ((long long)0x4C504250 << 32) | 0x54534250;
    filter.mUnknown16.mKind = 3;
    filter.mUnknown16.mValue.mInt = key;
    if (fn_801F9D70(tag, 0x4C504250, &filter, &count) != 0) {
        count = 0;
    }
    return count;
}

int PlayBookDbLoadPlay(int tag, int key, int index, PlayBookPlay_t *pRecord)
{
    int flag = 0;
    int result;
    unsigned int flags;

    memset(pRecord, 0, sizeof(*pRecord));
    PlayBookDbLoadPlayHeader(tag, key, index, pRecord);
    result = PlayBookDbLoadPlayRecord(tag, pRecord->mUnknown0, pRecord);
    flags = PlayBookGetLoadFlags();
    PlayBookDbLoadPlayDetails(tag, pRecord->mUnknown0, pRecord->mUnknown14, pRecord);
    if (flags & 2) {
        if (flags & 8) {
            flag = 1;
        }
        PlayBookDbLoadPlayScripts(tag, pRecord->mUnknown0, pRecord, flag);
    }
    return result;
}

int PlayBookDbGetPlayOrder(int tag, int a, int b)
{
    int value = 1;

    fn_801FCE10(0, "use \x8c select '_dro' into \x85 from 'LPBP' where 'LPBP' = \x82 and 'TSBP' = \x82\n", tag, &value,
                b, a);
    return value - 1;
}

int PlayBookDbGetSetOrder(int tag, int a, int b)
{
    int value = 1;

    fn_801FCE10(0, "use \x8c select '_dro' into \x85 from 'TSBP' where 'MFBP' = \x82 and 'TSBP' = \x82\n", tag, &value,
                a, b);
    return value - 1;
}

int PlayBookDbGetFormationOrder(int tag, int a, int b)
{
    int value = 1;

    fn_801FCE10(0, "use \x8c select '_dro' into \x85 from 'MFBP' where 'MFBP' = \x82 and 'PYTF' = \x82\n", tag, &value,
                b, a);
    return value - 1;
}

void PlayBookDbGetPlayPath(int tag, int a, int *pResult)
{
    int b;
    int c;
    int d;

    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'LPBP' where 'LPBP' = \x85\n", tag, &b, a);
    pResult[2] = PlayBookDbGetPlayOrder(tag, b, a);
    fn_801FCE10(0, "use \x8c select 'MFBP' into \x85 from 'TSBP' where 'TSBP' = \x85\n", tag, &c, b);
    pResult[1] = PlayBookDbGetSetOrder(tag, c, b);
    fn_801FCE10(0, "use \x8c select 'PYTF' into \x85 from 'MFBP' where 'MFBP' = \x85\n", tag, &d, c);
    pResult[3] = d;
    pResult[0] = PlayBookDbGetFormationOrder(tag, d, c);
}

/* Discarded by the GameCube linker; bodies from the Xbox counterparts 0x196E70 and 0x196EB0. */
void SelectUABPRecord(int tag, int index, int kind, int *pResult)
{
    int value = 0;

    fn_801FCE10(0, "use \x8c select 'LPBP' into \x85 from 'UABP' where 'UABP' = \x85 and 'PYTF' = \x85\n", tag, &value,
                index + 1, kind);
    PlayBookDbGetPlayPath(tag, value, pResult);
}

int CountUABPRows(int tag, int kind)
{
    int count = 0;

    fn_801FCE10(0, "use \x8c select count('LPBP') into \x85 from 'UABP' where 'PYTF' = \x85\n", tag, &count, kind);
    return count;
}

void PlayBookDbSetAudiblePlay(int tag, int a, int b)
{
    if (b != 0xFFFF) {
        int result[4];

        PlayBookDbGetPlayPath(tag, b, result);
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

void LoadTSBPObject(int tag, int key, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject)
{
    unsigned int flags;
    int formation;
    int order;

    memset(pObject, 0, sizeof(*pObject));
    flags = PlayBookGetLoadFlags();
    fn_801FCE10(0, "use \x8c select 'MFBP' into \x85 and '_dro' into \x85 from 'TSBP' where 'TSBP' = \x85\n", tag,
                &formation, &order, key);
    PlayBookDbLoadSetHeader(tag, formation, order - 1, pTeam, pObject);
    if (pObject->mUnknown4) {
        PlayBookDbLoadSetRecord(tag, pObject->mUnknown4, pObject);
        if (flags & 1) {
            PlayBookDbLoadSetPositions(tag, pObject->mUnknown4, pTeam, pObject);
        }
        PlayBookDbLoadSetSlots(tag, pObject->mUnknown4, pObject);
    }
}

int SelectLTESName(int tag, char *pName, int set)
{
    return fn_801FCE10(0, "use \x8c select 'eman' into \x88 from 'LTES' where 'LTES' = \x85\n", tag, pName, set);
}

int _PlayBookDbComparePickWeight(PlayCandidate_t *pA, PlayCandidate_t *pB)
{
    if (pA->mUnknown4 < pB->mUnknown4) {
        return -1;
    }
    return 0;
}

void _PlayBookDbSwapPicks(PlayCandidate_t *pA, PlayCandidate_t *pB)
{
    PlayCandidate_t temp = *pA;

    *pA = *pB;
    *pB = temp;
}

int PlayBookDbPickAIPlay(int team, int tag, int kind)
{
    PlayCandidate_t list[225];
    DbFilter kindFilter;
    DbFilter joinFilter;
    DbFilter lylpFilter;
    DbQueryTable tables[5];
    DbColumnValue columns[5] = {
        { 0, 0x4C504250, 0x4C504250 },
        { 0, 0x4C594C50, 0x54594C50 },
        { 0, 0x49414250, 0x74637270 },
        { 0, 0x4C594C50, 0x5F464C50 },
        { 0, -1, -1 }
    };
    int cursor;
    unsigned short count;
    int opened;
    int status;
    unsigned short i;
    unsigned int total;
    unsigned int pick;

    kindFilter.Set(6, ((long long)0x49414250 << 32) | 0x52474941, 3, kind);
    joinFilter.Set(6, ((long long)0x49414250 << 32) | 0x4C504250, 6);
    joinFilter.mUnknown16.mValue.mLong = ((long long)0x4C504250 << 32) | 0x4C504250;
    lylpFilter.Set(6, ((long long)0x4C504250 << 32) | 0x4C594C50, 6);
    lylpFilter.mUnknown16.mValue.mLong = ((long long)0x4C594C50 << 32) | 0x4C594C50;
    tables[0].Set(0x49414250, 0, &kindFilter);
    tables[1].Set(0x4C504250, 0, &joinFilter);
    tables[2].Set(0x4C594C50, 0, &lylpFilter);
    tables[3].Set(-1, 0, 0);
    count = 0;
    opened = 0;
    memset(list, 0, sizeof(list));
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
    if (status != 0) {
        return status;
    }
    SortArray(0, list, count, sizeof(PlayCandidate_t), _PlayBookDbComparePickWeight, _PlayBookDbSwapPicks, 0, 0);
    PlayTrackWeightCandidates(team, list, count);
    total = 0;
    for (i = 0; i < count; i++) {
        total += list[i].mUnknown4;
    }
    pick = fn_802372EC(0, total);
    total = 0;
    for (i = 0; i < count; i++) {
        total += list[i].mUnknown4;
        if (total >= pick) {
            break;
        }
    }
    return list[i].mUnknown0;
}

void PlayBookDbPickAIPlayPath(int team, int tag, int kind, int *pResult)
{
    PlayBookDbGetPlayPath(tag, PlayBookDbPickAIPlay(team, tag, kind), pResult);
}

int PlayBookDbHasAIPlay(int tag, int a, int b)
{
    DbFilter filter;
    DbFilter kindFilter;
    DbFilter lpbpFilter;
    DbQueryTable tables[2] = { { 0x49414250 }, { -1 } };
    DbColumnValue columns[2] = {
        { 0, 0x49414250, 0x4C504250 },
        { 0, -1, -1 }
    };

    filter.mUnknown32 = 0x20009;
    filter.mUnknown0.Set(11, &kindFilter);
    filter.mUnknown16.Set(11, &lpbpFilter);
    kindFilter.mUnknown32 = 0x10003;
    kindFilter.mUnknown0.Set(6, ((long long)0x49414250 << 32) | 0x52474941);
    {
        DbFilterOperand *pOp = &kindFilter.mUnknown16;
        pOp->Set(3, a);
    }
    lpbpFilter.mUnknown32 = 0x10003;
    lpbpFilter.mUnknown0.Set(6, ((long long)0x49414250 << 32) | 0x4C504250);
    {
        DbFilterOperand *pOp = &lpbpFilter.mUnknown16;
        pOp->Set(3, b);
    }
    return fn_801FA290(tag, tables, &filter, columns) != 0x17;
}

}
