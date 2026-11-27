/* The 'MTTS' table of the game database (one row per team slot: slot 'UNLS', team 'DIGT' and
   the slot's team details) and the module that keeps the per-player and per-team column sets:
   it fills and updates the 'MTTS' rows, walks them against the 'MAET' teams, reads and writes
   one column of a 'DIGP' or 'DIGT' row by its column code, and runs the game start and resume
   hooks of the module. Partial source; not yet linked. */

#include "engine/dbteams.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/TDbLoad.h"
#include "engine/cu_80229270.h"

#include "engine/DbNiomModeFuncs.h"
#include "engine/llmemory.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"
#include "engine/t3db.h"
#include "engine/t3db_cols.h"
#include "game/DbUserSetCurrent.h"

#include <string.h>

struct CardStreamTarget;
struct SaveStreamOps_t;
#include "engine/DbUserEntry.h"
extern char lbl_802B5C8C[];
extern char lbl_803A1C60[];
extern char *_DbEvas_pFileName;
extern int _DbEvas_iMode;
extern int _DbEvas_iSize;
extern int _DbUser_iSize;
extern char *_DbUser_pFileName;
extern int _DbUser_iMode;
extern int _DbUser_iCurrent;
extern unsigned char _DbUser_iCount;
extern DbUserEntry_t _DbUser_aEntries[];
extern int TDbSave(int handle, int a, int b);
extern int TDbInsertRow(int db, int tbl, TDbCol_801F9718 *pCols, void *pRes, int a);
extern int TDbLoadFromFile(int db, int file, char *pName, int mode, TDbIODevice_t *pDevice);
extern TDbIODevice_t tdbiofioCallback;
extern int TDbTblDestroy(int db, int tbl);
signed char DbUserFindIndex(int key);

extern const unsigned char lbl_802AEF10[];
extern int DbYalpLoadWeightTable(void *p, int tag);
extern int DbThcdSetLineup(int a, int *p, int c);
int DbResetGameInfo(void);
extern int DbUserFindIdByDb(int key);
extern int DbUserGetCurrent(void);
extern void DbOccpModuleShutdown(void);
int DbUserGetDb(int key);
extern const int _DbUser_aDbIds[2];
extern char lbl_802B5D64[];
extern char lbl_802B56F4[];
extern char lbl_802B5744[];
extern char lbl_802B4EA0[];
extern char lbl_802B4EC4[];
extern char _DbSrpt_szDeclareTeamsByFlagQuery[];
extern char _DbSrpt_szDeclareTeamsByFlagTypeQuery[];
int DbSrptDeleteCursorTeams(struct QueryCursor cursor, int a);
extern int TDbQryGetCount(int ref, unsigned short *pCount);
extern int DbCacheDeleteRows(int id, int a, int b);
extern char _DbSrpt_szFetchTeamIdQuery[];
extern char _DbSrpt_szDeclareSrptQuery[];
extern char lbl_802B479C[];
extern char lbl_802B4828[];
extern char lbl_802B5CB4[];
extern char lbl_802B5CF0[];
extern int TDbExists(int db);
extern char _DbSrpt_szDeclareTeamIdsQuery[];
extern char _DbSrpt_szFetchSrptQuery[];
extern int TDbTblExists(int db, int tbl);
extern int TDbTblColEnum(int db, int tbl, TDbColInfo_801F9AB8 *pCols, unsigned int *pCount);
extern int TDbTblColExists(int db, int tbl, int col);
int DbTatsCopyTblDestroy(int db, int tbl);
extern char lbl_802B5A48[];
extern char lbl_802B5AB0[];
extern char lbl_802B5ACC[];
extern char lbl_802B5B34[];
extern char lbl_802B5B64[];
extern char lbl_802B5BDC[];
int DbLoadConferenceIds(void);
int DbLoadDivisionIds(void);
int DbLoadTeamList(void);
int DbLeagueLoad(void);
void DbLeagueFree(void);

extern char lbl_802B48C4[];
extern char lbl_802B4A54[];
extern char lbl_802B4A9C[];
extern char lbl_802B4AE0[];
void DbBuildPendingNodeList(void *pPairs);
void DbAssignPendingNodeIds(void);
int DbLoadTeamDepthChart(int key, int mode);
int DbThcdSetEntry(int a, int b, int c, int row, int value);
unsigned short DbThcdGetMaxDepth(int index);

#include "engine/DbNiomHandlers.h"

typedef struct DbMttsCursor_t {
    unsigned short mUnknown0;
    int mUnknown4;
} DbMttsCursor_t;

extern int fn_8022A624(DbMttsCursor_t *p, struct QueryCursor cursor, int a, int b);
extern int DbCacheOpen(int key, unsigned short *pId);
extern int DbCacheClose(unsigned short id);
extern int DbLockAcquire(void);
extern int DbLockRelease(void);

extern char lbl_802B2138[];
extern char lbl_802B2178[];
extern char lbl_802B21B8[];
extern char lbl_802B21FC[];
extern char lbl_802B2268[];
extern char lbl_802B231C[];
extern char lbl_802B238C[];
extern char lbl_802B2F64[];
extern char lbl_802B3010[];
extern char lbl_802B30D0[];
extern char lbl_802B3180[];
extern char lbl_802B3524[];
extern char lbl_802B35D4[];
extern char lbl_802B35E4[];
extern char lbl_802B35F8[];
extern char lbl_802B45F0[];
extern char lbl_802B4650[];
extern char lbl_802B5080[];
extern char lbl_802B50A0[];
extern char lbl_802B50C0[];
extern char lbl_802B50E0[];
extern char lbl_802B5100[];
extern char lbl_802B5120[];
extern char lbl_802B519C[];
extern char lbl_802B51BC[];
extern int lbl_802FA600[];
typedef struct DbSrptRow_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
} DbSrptRow_t;

/* Ends a column list for TDbInsertRow. */
static inline void fn_801F9718_SetEnd(TDbCol_801F9718 *pCol)
{
    pCol->mCol = -1;
    pCol->mUnk4 = -1;
    pCol->mUnk0 = 0;
}

typedef struct Callbacks_8022B02C {
    int (*mpUnknown0)(int a, int b, int c, int d);
    int (*mpUnknown4)(int a, int b, int c, int d);
} Callbacks_8022B02C;

typedef struct DbSrptCallbacks_t {
    int (*mpUnknown0)(int a, int b, int c, int d);
    int (*mpUnknown4)(int a, int b, int c, int d);
} DbSrptCallbacks_t;

extern DbSrptRow_t _DbSrpt_aRows[];
extern int (*_DbNiom_pEndFunc)(void);
extern void *_DbNiom_pLoadFunc;
extern void *_DbNiom_pResetFunc;
extern void (*_DbNiom_pCallback)(int);
extern int _DbNiom_iCallbackArg;
extern unsigned char _DbNiom_bModeActive;
extern unsigned char _DbNiom_bEnding;
extern int (*_DbNiom_pModeEnd)(void);
extern int (*_DbNiom_pModeLoad)(void **ppData, void *p);
extern int (*_DbNiom_pModeReset)(int a, int b);
extern int (*_DbNiom_pModeResume)(void);
extern int (*_DbNiom_pModeFn16)(void);
extern int lbl_803EC020[1];
extern int TDbQryGetSingleRow(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_t *pWhere,
                       TDbCol_801F9718 *pCols);
extern int TDbQrySetFirstRow(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_t *pWhere,
                       TDbCol_801F9718 *pCols, void *pResult, int callback);
extern int TDbQryUpdateExpr(int db, TDbSQLTableRef_801FDC18 *pTables, TDbExpr_t *pWhere,
                            unsigned long long *pKeys, TDbExpr_t *pTerms, void *pRes, int cb);
/* Set index per column letter ('A'/'a' first); neutral label. */
extern unsigned char lbl_802FA614[];
extern int *lbl_803EC010[1];
extern unsigned char lbl_803EC014[1];
extern TDbCol_801F9718 **lbl_803EC018[1];
extern unsigned char *lbl_803EC01C[1];
extern TDbCol_801F9718 *lbl_803EC024[1];
extern unsigned char lbl_803ED01C[1];
extern int DbOccpModuleInit(int a);
extern int (*lbl_803EC028)(int a, int b, int c, int d);
extern int (*lbl_803EC02C)(int a, int b, int c, int d);
extern unsigned char _DbSrpt_bHasTable;
extern int (*_DbSrpt_pBeginGameFunc)(int a, int b, int c, int d);
extern int (*_DbSrpt_pResumeGameFunc)(int a, int b, int c, int d);

int DbNiomCloseCursor(void);
int fn_8022A59C(int a, DbMttsCursor_t **ppOut);
int DbMttsReadSlots(DbMttsCursor_t *p, int a, int b);
int fn_8022AC80(DbMttsCursor_t *p);
int fn_8022BF60(void);
int fn_8022BF68(void);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void *DbUslpAllocNodes(void);
void DbUslpFreeNodes(void *p);
void DbUslpClearLists(void);
void *DbUslpAllocEntries(void);
void DbUslpFreeEntries(void *p);
void DbUslpCloseSlotCursor(void);
int DbUslpFilterNone(int a);
int DbUslpSetFilter1(int (*pCallback)(int a));
int DbUslpSetFilter2(int (*pCallback)(int a));































































































































































/* prototypes of the db functions in 0x80229270-0x8022F428 (dbocmt.c to dbuser.c) */
int DbOcmtRenumber(void);
int DbOcmtModuleInit(void);
void DbOcmtModuleShutdown(void);
int DbOcmtInsert(int a, int b);
int DbOcmtClear(void);
int DbOptionsModuleInit(void);
void DbOptionsModuleShutdown(void);
int DbOptionsSetTpom(int column, int value);
int DbNiomInit(void);
void DbNiomShutdown(void);
void DbNiomSetHandlers(DbNiomHandlers_t *p);
int DbNiomIsModeActive(void);
int DbNiomBeginMode(int *p);
int DbNiomEndMode(void);
int DbNiomRunCallback(void);
int DbNiomOpenCursor(int a);
int DbNiomReadCursor(int a, int b);
int DbNiomCloseCursor(void);
int DbNiomReadOnce(int a, int b);
void DbNiomSetModeFuncs(DbNiomModeFuncs_t *pFuncs);
void DbNiomClearModeFuncs(void);
int DbNiomModeLoad(void **ppData, void *p);
int DbNiomModeReset(int a, int b);
int DbNiomModeResume(void);
int DbYalpModuleInit(void);
int DbYalpModuleShutdown(void);
float DbYalpGetLowRating(int index);
float DbYalpGetHighRating(int index);
float DbYalpGetRatingWeight(int index, int item);
float DbYalpGetWeightSum(int index);
int DbYalpBeginGame(void);
int DbYalpResumeGame(void);
void DbSplpModuleShutdown(void);
int DbMttsInsertSlot(int a);
int fn_8022A490(unsigned int count);
int fn_8022A508(int a, int b, int c, int d, int e);
int fn_8022A558(int a, int b, int c, int d);
int DbMttsInsertTeamRow(int key, int unused, int col, int value, int index);
int fn_8022AD64(int db, TDbCol_801F9718 **ppCols, unsigned char *pCount);
int fn_8022AEFC(unsigned int value);
int fn_8022AF54(int a, int b);
int DbMttsInsertPlayerRow(int key, int unused, int col, int value, int set, int index);
int fn_8022B02C(Callbacks_8022B02C *pCallbacks);
void fn_8022B200(void);
int fn_8022BF60(void);
int fn_8022BF68(void);
int DbMttsBeginGame(int a, int b, int c, int d);
int DbMttsResumeGame(int a, int b, int c, int d);
int DbSrptDeleteCursorTeams(struct QueryCursor cursor, int a);
int DbSrptModuleInit(DbSrptCallbacks_t *pCallbacks);
void DbSrptModuleShutdown(void);
int DbSrptDeleteUnflaggedTeams(int a);
int DbSrptDeleteUnflaggedTypedTeams(int a);
int DbFindUnusedTeamIds(int db, int tbl, int *pIds, unsigned short *pCount);
int DbSrptBeginGame(int a, int b, int c, int d);
int DbSrptResumeGame(int a, int b, int c, int d);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void DbUtilSetHeap(int a);
void *DbUtilAlloc(int size, int a);
void DbUtilFree(void *p);
void *DbUslpAllocNodes(void);
void DbUslpFreeNodes(void *p);
void DbBuildPendingNodeList(void *pPairs);
void DbUslpClearLists(void);
void *DbUslpAllocEntries(void);
void DbUslpFreeEntries(void *p);
int DbUslpOpenSlotCursor(int a, int b, int c);
void DbUslpCloseSlotCursor(void);
void DbUslpApplyStoredSlots(void);
int DbUslpFilterNone(int a);
int DbUslpModuleInit(void);
int DbUslpModuleShutdown(void);
int DbUslpResetFilter1(void);
int DbUslpSetFilter1(int (*pCallback)(int a));
int DbUslpSetFilter2(int (*pCallback)(int a));
int DbUslpRunStep(int a, int b, int c, void *pPairs, int action, int mode);
int DbUslpFillSlots(int a, int b, int c, void *pPairs, int mode);
int DbUslpFinish(void);
unsigned short DbUslpGetSlotPlayer(unsigned char key);
int DbOpenDepthChartCursor(int a, int b, int mode);
int DbCloseDepthChartCursor(void);
int DbLoadTeamDepthChart(int key, int mode);
int DbThcdModuleInit(void);
void DbThcdModuleShutdown(void);
unsigned short DbThcdGetMaxDepth(int index);
int DbThcdSetEntry(int a, int b, int c, int row, int value);
int DbThcdGetFallbackPosition(int row, int column);
int DbThcdBeginGame(int home, int away, int mode, int arg);
int DbThcdResumeGame(int home, int away, int homeCshg, int awayCsag);
int DbThcdSetSlotPlayer(int a, int b, int c, int key);
int DbThcdSetLineup(int a, int *p, int tag);
int DbThcdSetLineups(int a, int *b, int c, int *d, int e);
int DbFnigModuleInit(int *p);
void DbFnigModuleShutdown(void);
int DbResetGameInfo(void);
int DbFnigSetHomeTeam(int value);
int DbFnigSetAwayTeam(int value);
int DbFnigSetHomeOffPlaybook(int value);
int DbFnigSetHomeDefPlaybook(int value);
int DbFnigSetAwayOffPlaybook(int value);
int DbFnigSetAwayDefPlaybook(int value);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
int DbFnigWriteBlock(int a, void *p);
int DbFnigCopyGamePlayers(int a, int b);
int fn_8022E558(void);
int fn_8022E560(void);
int DbLoadConferenceIds(void);
void DbLeagueFreeConferences(void);
int DbLoadDivisionIds(void);
void DbLeagueFreeDivisions(void);
int DbLoadTeamList(void);
void DbLeagueFreeTeams(void);
int DbLeagueModuleInit(void);
void DbLeagueModuleShutdown(void);
int DbLeagueLoad(void);
void DbLeagueFree(void);
int DbEvasModuleInit(void);
void DbEvasModuleShutdown(void);
int DbEvasInit(int a, const char *pName, int b);
void DbEvasShutdown(void);
int DbEvasLoad(void);
int DbEvasLoadStream(struct CardStreamTarget *pTarget, struct SaveStreamOps_t *pOps);
int DbEvasSaveStream(void *pTarget, struct SaveStreamOps_t *pOps);
int DbEvasUnload(void);
int DbTatsCopyInit(int a, const char *pName, int b);
void DbTatsCopyShutdown(void);
int DbTatsCopyOpen(void);
int DbTatsCopyClose(void);
int DbTatsCopyTable(int a, int b);
int DbTatsCopyTblDestroy(int db, int tbl);
int DbTatsCopyAllTables(int db, int a, int b);
int DbFileInit(const char *pName);
void DbFileShutdown(void);
int DbFileTblLoad(int db, int file);
int DbFileTblDestroy(int db, int tbl);
int DbUserNewId(void);
int DbUserInit(int a, const char *pName, int b);
void DbUserShutdown(void);
int DbUserCreate(void);
void DbUserDelete(int key);
void DbUserReset(int key);
int DbUserGetCount(void);
int DbUserGetId(int index);
signed char DbUserFindIndex(int key);
int DbUserGetDb(int key);

int DbMttsInsertSlot(int a)
{
    // FAKEMATCH: the last variadic 0 comes from a local so its constant is loaded first.
    int zero = 0;

    return TDbCompilePerformOp(0, lbl_802B2F64, a, 1023, 1023, 31, -1, 3, 15, 7, -1, zero);
}

int fn_8022A490(unsigned int count)
{
    int err = TDbCompilePerformOp(0, lbl_802B3010);

    if (err == 0) {
        int id = 0;
        unsigned short i;

        for (i = 0; i < count; i++) {
            if ((err = DbMttsInsertSlot(id)) == 0) {
                id++;
            } else {
                break;
            }
        }
    }
    return err;
}

int fn_8022A508(int a, int b, int c, int d, int e)
{
    return TDbCompilePerformOp(0, lbl_802B30D0, b, c, d, e, a);
}

int fn_8022A558(int a, int b, int c, int d)
{
    return TDbCompilePerformOp(0, lbl_802B3180, b, c, d, a);
}

int fn_8022A59C(int a, DbMttsCursor_t **ppOut)
{
    int err = DbLockAcquire();
    DbMttsCursor_t *p = DbUtilAlloc(8, 0);

    p->mUnknown4 = a;
    p->mUnknown0 = -1;
    if (err == 0) {
        err = DbCacheOpen(0, &p->mUnknown0);
    }
    if (err == 0) {
        *ppOut = p;
    } else {
        fn_8022AC80(p);
        *ppOut = 0;
    }
    return err;
}

/* Opens a cursor over the 'MTTS' team-slot rows in slot order and reads them through p. */
int DbMttsReadSlots(DbMttsCursor_t *p, int a, int b)
{
    struct QueryCursor cursor;
    int err = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, lbl_802B3524, &cursor);
    if (err == 0) {
        err = fn_8022A624(p, cursor, a, b);
    }
    if (QUERY_STATUS_ACCEPTED(err) == 1) {
        if (cursor.mUnknown0 != 0) {
            err = TDbSQLDestroyCursor(&cursor);
        } else {
            err = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return err;
}

int fn_8022AC80(DbMttsCursor_t *p)
{
    int err = 0;

    if (p->mUnknown0 != 0xFFFF) {
        err = DbCacheClose(p->mUnknown0);
    }
    if (err == 0) {
        err = DbLockRelease();
    } else {
        DbLockRelease();
    }
    DbUtilFree(p);
    return err;
}

/* Adds a team row: 'DIGT' set to key and column col set to value. */
int DbMttsInsertTeamRow(int key, int unused, int col, int value, int index)
{
    TDbCol_801F9718 aCols[4];
    int table;

    table = lbl_803EC020[index];
    aCols[0].mUnk0 = key;
    aCols[0].mUnk4 = table;
    aCols[0].mCol = 0x44494754;
    aCols[1].mCol = col;
    aCols[1].mUnk4 = table;
    aCols[1].mUnk0 = value;
    fn_801F9718_SetEnd(&aCols[2]);
    return TDbInsertRow(0, table, aCols, 0, 0);
}

int fn_8022AD64(int db, TDbCol_801F9718 **ppCols, unsigned char *pCount)
{
    TDbColInfo_801F9AB8 aInfo[254];
    unsigned int count;
    int status;
    int hasP;
    int hasT;
    unsigned char n;
    unsigned char i;

    n = 1;
    hasP = TDbTblColExists(0, db, 0x44494750) == 0;
    hasT = TDbTblColExists(0, db, 0x44494754) == 0;
    count = 254;
    status = TDbTblColEnum(0, db, aInfo, &count);
    if (!hasP && !hasT) {
        n = 0;
    }
    if (status == 0) {
        *ppCols = DbUtilAlloc((count + 1) * 16, 1);
        (*ppCols)[0].mCol = -1;
        for (i = 0; i < count; i++) {
            if (aInfo[i].mCol == 0x44494750 || aInfo[i].mCol == 0x44494754) {
                (*ppCols)[0].mUnk4 = db;
                (*ppCols)[0].mCol = aInfo[i].mCol;
            } else {
                (*ppCols)[n].mUnk4 = db;
                (*ppCols)[n].mCol = aInfo[i].mCol;
                n++;
            }
        }
        fn_801F9718_SetEnd(&(*ppCols)[n]);
    }
    if (status == 0) {
        *pCount = n;
    } else {
        *pCount = 0;
    }
    return status;
}

int fn_8022AEFC(unsigned int value)
{
    int c = value >> 24;
    int result = 255;
    if ((lbl_802AEF10 + 1)[c] & 2) {
        result = 0;
    } else if ((lbl_802AEF10 + 1)[c] & 1) {
        result = 3;
    } else if (c == '0') {
        result = 2;
    } else if (c == '1') {
        result = 1;
    }
    return result;
}

int fn_8022AF54(int a, int b)
{
    return 0;
}

/* Adds a player row: 'DIGP' set to key and column col set to value; retries once on status 19. */
int DbMttsInsertPlayerRow(int key, int unused, int col, int value, int set, int index)
{
    TDbCol_801F9718 aCols[4];
    int table;
    int err = 0;

    table = lbl_803EC010[set][index];
    aCols[0].mUnk0 = key;
    aCols[0].mUnk4 = table;
    aCols[0].mCol = 0x44494750;
    aCols[1].mCol = col;
    aCols[1].mUnk4 = table;
    aCols[1].mUnk0 = value;
    fn_801F9718_SetEnd(&aCols[2]);
    err = TDbInsertRow(0, table, aCols, 0, 0);
    if (err == 19) {
        err = fn_8022AF54(set, index);
        if (err == 0) {
            err = TDbInsertRow(0, table, aCols, 0, 0);
        }
    }
    return err;
}

int fn_8022B02C(Callbacks_8022B02C *pCallbacks)
{
    int status = 0;
    int table;
    unsigned char i;
    unsigned char j;
    unsigned char count;

    for (i = 0; i < 1; i++) {
        count = lbl_803EC014[i];
        for (j = 0; j < count; j++) {
            lbl_803EC018[i][j] = 0;
        }
    }
    for (i = 0; i < 1; i++) {
        lbl_803EC024[i] = 0;
    }
    for (i = 0; i < 1; i++) {
        count = lbl_803EC014[i];
        for (j = 0; j < count; j++) {
            table = lbl_803EC010[i][j];
            {
                TDbCol_801F9718 **ppCols = &lbl_803EC018[i][j];
                unsigned char *pCount = &lbl_803EC01C[i][j];

                if (TDbTblExists(0, table) == 0) {
                    status = fn_8022AD64(table, ppCols, pCount);
                } else {
                    *ppCols = 0;
                    *pCount = 0;
                }
            }
            if (status != 0) {
                break;
            }
        }
        if (status != 0) {
            break;
        }
    }
    if (status == 0) {
        for (i = 0; i < 1; i++) {
            unsigned char *pCount = &lbl_803ED01C[i];

            table = lbl_803EC020[i];
            if (TDbTblExists(0, table) == 0) {
                status = fn_8022AD64(table, &lbl_803EC024[i], pCount);
            } else {
                *pCount = 0;
            }
            if (status != 0) {
                break;
            }
        }
    }
    if (status == 0) {
        if (pCallbacks != 0) {
            lbl_803EC028 = pCallbacks->mpUnknown0;
            lbl_803EC02C = pCallbacks->mpUnknown4;
        }
        status = DbOccpModuleInit(0);
    }
    return status;
}

void fn_8022B200(void)
{
    unsigned char i;
    unsigned char j;
    unsigned char count;

    DbOccpModuleShutdown();
    for (i = 0; i < 1; i++) {
        count = lbl_803EC014[i];
        for (j = 0; j < count; j++) {
            if (lbl_803EC018[i][j] != 0) {
                DbUtilFree(lbl_803EC018[i][j]);
                lbl_803EC018[i][j] = 0;
            }
        }
    }
    for (i = 0; i < 1; i++) {
        if (lbl_803EC024[i] != 0) {
            DbUtilFree(lbl_803EC024[i]);
            lbl_803EC024[i] = 0;
        }
    }
    lbl_803EC028 = 0;
    lbl_803EC02C = 0;
}

/* The 64-bit column key of col in table (table word high, column id low). */
static inline unsigned long long _DbColKey(unsigned int table, unsigned int col)
{
    return ((unsigned long long)table << 32) | col;
}

/* One table reference of a query's table list (as dboccp.c's _DbOccpSetTable). */
static inline void _DbMttsSetTable(TDbSQLTableRef_801FDC18 *pRef, unsigned int id, unsigned int join,
                                   TDbExpr_t *pExpr)
{
    pRef->mExpr = pExpr;
    pRef->mId = id;
    pRef->mJoinType = join;
}

/* One column of a column list: its value, table and column code. */
static inline void _DbMttsSetCol(TDbCol_801F9718 *pCol, int value, int table, int col)
{
    pCol->mUnk4 = table;
    pCol->mCol = col;
    pCol->mUnk0 = value;
}

/* column op unsigned value */
static inline void _DbMttsSetColUInt(TDbExpr_t *pExpr, int op, unsigned int table, unsigned int col, int value)
{
    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_COLUMN;
    pExpr->mLeft.mValue.l = _DbColKey(table, col);
    pExpr->mRight.mType = TDB_TYPE_UINT;
    pExpr->mRight.mValue.i = value;
}

/* column op integer */
static inline void _DbMttsSetColInt(TDbExpr_t *pExpr, int op, unsigned long long col, int value)
{
    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_COLUMN;
    pExpr->mLeft.mValue.l = col;
    pExpr->mRight.mType = TDB_TYPE_INT;
    /* FAKEMATCH: the integer stored through a pointer to the value field, for the target's frame-based store address in DbMttsAddTeamRushStat; the same field is set. */
    {
        int *pValue = &pExpr->mRight.mValue.i;
        *pValue = value;
    }
}

/* sub-expression op sub-expression */
static inline void _DbMttsSetSubSub(TDbExpr_t *pExpr, int op, TDbExpr_t *pLeft, TDbExpr_t *pRight)
{
    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_EXPR_UINT;
    pExpr->mLeft.mValue.p = pLeft;
    pExpr->mRight.mType = TDB_TYPE_EXPR_UINT;
    pExpr->mRight.mValue.p = pRight;
}

/* Writes value into column col of the 'DIGP' row key of the set selected by the column's
   third letter; when no row matched (23) the row is added through DbMttsInsertPlayerRow. Returns 131
   for a column letter without a set. */
int DbMttsSetPlayerColumn(int key, unsigned int col, int value)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    TDbCol_801F9718 aCols[2];
    TDbExpr_t expr;
    unsigned int c;
    int index;
    int table;
    int err;

    c = (col >> 8) & 0xFF;
    if (c > 96) {
        index = lbl_802FA614[c - 97];
    } else {
        index = lbl_802FA614[c - 65];
    }
    if (index >= 0) {
        table = lbl_803EC010[0][index];
        _DbMttsSetCol(&aCols[0], value, table, col);
        fn_801F9718_SetEnd(&aCols[1]);
        _DbMttsSetColUInt(&expr, 0x10003, table, 0x44494750, key);
        _DbMttsSetTable(&aTables[0], table, 2, &expr);
        _DbMttsSetTable(&aTables[1], -1, 2, 0);
        err = TDbQrySetFirstRow(0, aTables, 0, aCols, 0, 0);
        if (err == 23) {
            err = DbMttsInsertPlayerRow(key, -1, col, value, 0, index);
        }
    } else {
        err = 131;
    }
    return err;
}

/* Reads column col of the 'DIGP' row key of the set selected by the column's third letter
   into *pOut; returns 131 for a letter without a set, 132 when no row matched. */
int DbMttsGetPlayerColumn(int key, unsigned int col, int *pOut)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    TDbCol_801F9718 aCols[2];
    TDbExpr_t expr;
    unsigned int c;
    int index;
    int table;
    int err;
    int ok;

    err = 0;
    *pOut = err;
    c = (col >> 8) & 0xFF;
    if (c > 96) {
        index = lbl_802FA614[c - 97];
    } else {
        index = lbl_802FA614[c - 65];
    }
    if (index >= 0) {
        table = lbl_803EC010[0][index];
        aCols[0].mUnk0 = 0;
        aCols[0].mUnk4 = table;
        aCols[0].mCol = col;
        fn_801F9718_SetEnd(&aCols[1]);
        _DbMttsSetColUInt(&expr, 0x10003, table, 0x44494750, key);
        _DbMttsSetTable(&aTables[0], table, 2, &expr);
        _DbMttsSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryGetSingleRow(0, aTables, 0, aCols);
        ok = 0;
        if (err == 0 || err == 23 || err == 21 || err == 20) {
            ok = 1;
        }
        if (ok == 1) {
            if (err == 0) {
                *pOut = aCols[0].mUnk0;
            } else {
                err = 132;
            }
        }
    } else {
        err = 131;
    }
    return err;
}

/* Sets column col of the 'DIGP' row key of the set selected by the column's third letter, by
   the column's kind (0x8022AEFC): kind 2 stores value, kinds 0 and 3 update the column with the
   expression ops 0x4000D and 0x40013 of value; when no row matched (23) the row is added through
   DbMttsInsertPlayerRow. Returns 130 for another kind, 131 for a letter without a set. */
int DbMttsUpdatePlayerColumn(int key, unsigned int col, int value)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    unsigned long long aKeys[2];
    TDbCol_801F9718 aCols[2];
    TDbExpr_t expr;
    TDbExpr_t term;
    unsigned int c;
    signed char index;
    int table;
    int err;

    c = (col >> 8) & 0xFF;
    if (c > 96) {
        index = lbl_802FA614[c - 97];
    } else {
        index = lbl_802FA614[c - 65];
    }
    if (index >= 0) {
        table = lbl_803EC010[0][index];
        _DbMttsSetColUInt(&expr, 0x10003, table, 0x44494750, key);
        _DbMttsSetTable(&aTables[0], table, 2, &expr);
        _DbMttsSetTable(&aTables[1], -1, 2, 0);
        switch (fn_8022AEFC(col)) {
        case 0:
            aKeys[0] = _DbColKey(table, col);
            aKeys[1] = -1;
            _DbMttsSetColInt(&term, 0x4000D, _DbColKey(table, col), value);
            err = TDbQryUpdateExpr(0, aTables, 0, aKeys, &term, 0, 0);
            break;
        case 2:
            _DbMttsSetCol(&aCols[0], value, table, col);
            fn_801F9718_SetEnd(&aCols[1]);
            err = TDbQrySetFirstRow(0, aTables, 0, aCols, 0, 0);
            break;
        case 3:
            aKeys[0] = _DbColKey(table, col);
            aKeys[1] = -1;
            _DbMttsSetColInt(&term, 0x40013, _DbColKey(table, col), value);
            err = TDbQryUpdateExpr(0, aTables, 0, aKeys, &term, 0, 0);
            break;
        default:
            err = 130;
            break;
        }
        if (err == 23) {
            err = DbMttsInsertPlayerRow(key, -1, col, value, 0, (unsigned char)index);
        }
    } else {
        err = 131;
    }
    return err;
}

/* Reads column col of the row of the first table whose 'DIGT' column equals value; returns
   0 with the value in *pOut, 132 when the query ended without a row, or the query error. */
int DbMttsGetTeamColumn(int value, int col, int *pOut)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    TDbCol_801F9718 aCols[2];
    TDbExpr_t expr;
    int table;
    int err;
    int ok;

    err = 0;
    *pOut = err;
    table = lbl_803EC020[0];
    aCols[0].mUnk0 = err;
    aCols[0].mUnk4 = table;
    aCols[0].mCol = col;
    fn_801F9718_SetEnd(&aCols[1]);
    _DbMttsSetColUInt(&expr, 0x10003, table, 0x44494754, value);
    _DbMttsSetTable(&aTables[0], table, 2, &expr);
    _DbMttsSetTable(&aTables[1], -1, 2, 0);
    err = TDbQryGetSingleRow(0, aTables, 0, aCols);
    ok = 0;
    if (err == 0 || err == 23 || err == 21 || err == 20) {
        ok = 1;
    }
    if (ok == 1) {
        if (err == 0) {
            *pOut = aCols[0].mUnk0;
        } else {
            err = 132;
        }
    }
    return err;
}

/* Sets column col of the row of the first team table whose 'DIGT' column equals key, by the
   column's kind as DbMttsUpdatePlayerColumn does; when no row matched (23) the row is added through
   DbMttsInsertTeamRow. Returns 130 for a kind without an update. */
int DbMttsUpdateTeamColumn(int key, unsigned int col, int value)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    unsigned long long aKeys[2];
    TDbCol_801F9718 aCols[2];
    TDbExpr_t expr;
    TDbExpr_t term;
    int table;
    int err = 0;

    table = lbl_803EC020[0];
    _DbMttsSetColUInt(&expr, 0x10003, table, 0x44494754, key);
    _DbMttsSetTable(&aTables[0], table, 2, &expr);
    _DbMttsSetTable(&aTables[1], -1, 2, 0);
    switch (fn_8022AEFC(col)) {
    case 0:
        aKeys[0] = _DbColKey(table, col);
        aKeys[1] = -1;
        _DbMttsSetColInt(&term, 0x4000D, _DbColKey(table, col), value);
        err = TDbQryUpdateExpr(0, aTables, 0, aKeys, &term, 0, 0);
        break;
    case 2:
        _DbMttsSetCol(&aCols[0], value, table, col);
        fn_801F9718_SetEnd(&aCols[1]);
        err = TDbQrySetFirstRow(0, aTables, 0, aCols, 0, 0);
        break;
    case 3:
        aKeys[0] = _DbColKey(table, col);
        aKeys[1] = -1;
        _DbMttsSetColInt(&term, 0x40013, _DbColKey(table, col), value);
        err = TDbQryUpdateExpr(0, aTables, 0, aKeys, &term, 0, 0);
        break;
    default:
        err = 130;
        break;
    }
    if (err == 23) {
        err = DbMttsInsertTeamRow(key, -1, col, value, 0);
    }
    return err;
}

/* The score-margin class of a game result: 0 below -9, 1 from -9 to 8, 2 above 8. */
static inline int _DbMarginClass(int margin)
{
    return margin < -9 ? 0 : (margin <= 8 ? 1 : 2);
}

/* Adds one pass play to the 'RPST' row of team key and the class of margin: 'apst' counts
   the plays, 'cpst' and 'post' add a and b; when no row matched (23) the row is inserted with
   these values. */
int DbMttsAddTeamPassStat(int key, int a, int margin, int b)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    TDbExpr_t expr;
    TDbExpr_t keyExpr;
    TDbExpr_t classExpr;
    TDbExpr_t aTerms[3];
    unsigned long long aKeys[4];
    TDbCol_801F9718 aCols[6];
    int cls;
    int err;

    cls = _DbMarginClass(margin);
    _DbMttsSetSubSub(&expr, 0x20009, &keyExpr, &classExpr);
    _DbMttsSetColUInt(&keyExpr, 0x10003, 0x52505354, 0x44494754, key);
    _DbMttsSetColUInt(&classExpr, 0x10003, 0x52505354, 0x63647374, cls);
    _DbMttsSetTable(&aTables[0], 0x52505354, 2, &expr);
    _DbMttsSetTable(&aTables[1], -1, 2, 0);
    aKeys[0] = _DbColKey(0x52505354, 0x61707374);
    aKeys[1] = _DbColKey(0x52505354, 0x63707374);
    aKeys[2] = _DbColKey(0x52505354, 0x706F7374);
    aKeys[3] = -1;
    _DbMttsSetColInt(&aTerms[0], 0x4000D, _DbColKey(0x52505354, 0x61707374), 1);
    _DbMttsSetColInt(&aTerms[1], 0x4000D, _DbColKey(0x52505354, 0x63707374), a);
    _DbMttsSetColInt(&aTerms[2], 0x4000D, _DbColKey(0x52505354, 0x706F7374), b);
    err = TDbQryUpdateExpr(0, aTables, 0, aKeys, aTerms, 0, 0);
    if (err == 23) {
        aCols[0].mCol = 0x44494754;
        aCols[0].mUnk0 = key;
        aCols[0].mUnk4 = 0x52505354;
        aCols[1].mCol = 0x63647374;
        aCols[1].mUnk0 = cls;
        aCols[1].mUnk4 = 0x52505354;
        aCols[2].mCol = 0x61707374;
        aCols[2].mUnk0 = 1;
        aCols[2].mUnk4 = 0x52505354;
        aCols[3].mCol = 0x63707374;
        aCols[3].mUnk0 = a;
        aCols[3].mUnk4 = 0x52505354;
        aCols[4].mUnk4 = 0x52505354;
        aCols[4].mCol = 0x706F7374;
        aCols[4].mUnk0 = b;
        fn_801F9718_SetEnd(&aCols[5]);
        err = TDbInsertRow(0, 0x52505354, aCols, 0, 0);
    }
    return err;
}

/* Adds one rushing play to the 'DRST' row of team key and the class of margin: 'arst' counts
   the plays and 'rost' adds a; when no row matched (23) the row is inserted with these values. */
int DbMttsAddTeamRushStat(int key, int margin, int a)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    TDbExpr_t aTerms[2];
    TDbExpr_t expr;
    TDbExpr_t keyExpr;
    TDbExpr_t classExpr;
    unsigned long long aKeys[3];
    TDbCol_801F9718 aCols[5];
    int cls;
    int err;

    cls = _DbMarginClass(margin);
    _DbMttsSetSubSub(&expr, 0x20009, &keyExpr, &classExpr);
    _DbMttsSetColUInt(&keyExpr, 0x10003, 0x44525354, 0x44494754, key);
    _DbMttsSetColUInt(&classExpr, 0x10003, 0x44525354, 0x63647374, cls);
    _DbMttsSetTable(&aTables[0], 0x44525354, 2, &expr);
    _DbMttsSetTable(&aTables[1], -1, 2, 0);
    aKeys[2] = -1;
    aKeys[0] = _DbColKey(0x44525354, 0x61727374);
    aKeys[1] = _DbColKey(0x44525354, 0x726F7374);
    _DbMttsSetColInt(&aTerms[0], 0x4000D, _DbColKey(0x44525354, 0x61727374), 1);
    _DbMttsSetColInt(&aTerms[1], 0x4000D, _DbColKey(0x44525354, 0x726F7374), a);
    err = TDbQryUpdateExpr(0, aTables, 0, aKeys, aTerms, 0, 0);
    if (err == 23) {
        aCols[0].mCol = 0x44494754;
        aCols[0].mUnk0 = key;
        aCols[0].mUnk4 = 0x44525354;
        aCols[1].mCol = 0x63647374;
        aCols[1].mUnk0 = cls;
        aCols[1].mUnk4 = 0x44525354;
        aCols[2].mCol = 0x61727374;
        aCols[2].mUnk0 = 1;
        aCols[2].mUnk4 = 0x44525354;
        aCols[3].mUnk4 = 0x44525354;
        aCols[3].mCol = 0x726F7374;
        aCols[3].mUnk0 = a;
        fn_801F9718_SetEnd(&aCols[4]);
        err = TDbInsertRow(0, 0x44525354, aCols, 0, 0);
    }
    return err;
}

int fn_8022BF60(void)
{
    return 0;
}

int fn_8022BF68(void)
{
    int err = 0;
    unsigned char i;

    for (i = 0; i <= 4; i++) {
        err = TDbCompilePerformOp(0, lbl_802B35D4, lbl_802FA600[i]);
        if (err != 0) {
            break;
        }
    }
    if (err == 0) {
        err = TDbCompilePerformOp(0, lbl_802B35D4, lbl_803EC020[0]);
    }
    if (err == 0) {
        err = TDbCompilePerformOp(0, lbl_802B35E4);
    }
    if (err == 0) {
        err = TDbCompilePerformOp(0, lbl_802B35F8);
    }
    return err;
}

int DbMttsBeginGame(int a, int b, int c, int d)
{
    int err = 0;

    if (c == 0) {
        err = fn_8022BF68();
    }
    if (err == 0 && lbl_803EC028 != 0) {
        err = lbl_803EC028(a, b, c, d);
    }
    return err;
}

int DbMttsResumeGame(int a, int b, int c, int d)
{
    int err = 0;

    if (lbl_803EC02C != 0) {
        err = lbl_803EC02C(a, b, c, d);
    }
    if (err == 0) {
        err = fn_8022BF60();
    }
    return err;
}
