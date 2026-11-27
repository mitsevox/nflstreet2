/* The player-rating module of the game database ('YALP' players): when the database modules
   start it loads the two weight tables 'CROP' and 'ROBP' (per row two bounds, ten rating
   weights and their sum), turns a player's ten ratings into one overall rating with them, and
   lists unused player ids. Partial source; not yet linked. */

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
typedef struct Record_802297D8 {
    float mUnknown0;
    float mUnknown4;
    float aUnknown8[10];
    float mUnknown30;
} Record_802297D8;

extern Record_802297D8 lbl_803A20A4[];
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
extern char lbl_802B37E4[];
extern char lbl_802B3824[];
int DbSrptDeleteCursorTeams(struct QueryCursor cursor, int a);
extern int TDbQryGetCount(int ref, unsigned short *pCount);
extern int DbCacheDeleteRows(int id, int a, int b);
extern char lbl_802B3610[];
extern char lbl_802B3698[];
extern char lbl_802B479C[];
extern char lbl_802B4828[];
extern char lbl_802B5CB4[];
extern char lbl_802B5CF0[];
extern int TDbExists(int db);
extern char lbl_802B3888[];
extern char lbl_802B36C4[];
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

typedef struct Record_8022D5A4 {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
} Record_8022D5A4;

typedef struct Record_8022D874 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
} Record_8022D874;

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

typedef struct Object_8022A59C {
    unsigned short mUnknown0;
    int mUnknown4;
} Object_8022A59C;

typedef struct Node_8022CC6C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    short mUnknown6;
    unsigned short mUnknown8;
    char mUnknown10[2];
    struct Node_8022CC6C *mpUnknown12;
    struct Node_8022CC6C *mpUnknown16;
} Node_8022CC6C;

void DbUslpSortOpen(Node_8022CC6C **ppHead);

extern int fn_8022A624(Object_8022A59C *p, struct QueryCursor cursor, int a, int b);
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
extern Object_8022A59C *_DbNiom_pCursor;
extern int (*_DbNiom_pModeEnd)(void);
extern int (*_DbNiom_pModeLoad)(void **ppData, void *p);
extern int (*_DbNiom_pModeReset)(int a, int b);
extern int (*_DbNiom_pModeResume)(void);
extern int (*_DbNiom_pModeFn16)(void);
extern int lbl_803EC020[2];
extern int TDbQryGetSingleRow(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_t *pWhere,
                       TDbCol_801F9718 *pCols);
extern int TDbQrySetFirstRow(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_t *pWhere,
                       TDbCol_801F9718 *pCols, void *pResult, int callback);
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
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022BF60(void);
int fn_8022BF68(void);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void *DbUslpAllocNodes(void);
void DbUslpFreeNodes(void *p);
void DbUslpClearLists(void);
Node_8022CC6C *DbUslpFindSlot(Node_8022CC6C **ppHead, unsigned char key);
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
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022ACEC(int key, int unused, int col, int value, int index);
int fn_8022AD64(int db, TDbCol_801F9718 **ppCols, unsigned char *pCount);
int fn_8022AEFC(unsigned int value);
int fn_8022AF54(int a, int b);
int fn_8022AF5C(int key, int unused, int col, int value, int set, int index);
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
void DbUslpSortOpen(Node_8022CC6C **ppHead);
Node_8022CC6C *DbUslpFindSlot(Node_8022CC6C **ppHead, unsigned char key);
Node_8022CC6C *DbUslpFindPlayer(Node_8022CC6C **ppHead, unsigned short key);
void DbUslpListRemove(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void DbUslpListPush(Node_8022CC6C **ppHead, Node_8022CC6C *p);
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

extern char lbl_802B2430[];
extern char lbl_802B2458[];

int DbYalpLoadWeightTable(void *pTable, int tag)
{
    struct QueryCursor cursor;
    float aVals[10];
    int index;
    unsigned int a;
    unsigned int b;
    Record_802297D8 *pRow;
    int err = 0;
    unsigned char i;

    cursor.mUnknown0 = err;
    cursor.mUnknown4 = err;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, lbl_802B2430, &cursor, tag);
    while (err == 0) {
        err = TDbCompilePerformOp(0, lbl_802B2458, &cursor, &aVals[0], &aVals[1], &aVals[2], &aVals[3],
                                  &aVals[4], &aVals[5], &aVals[6], &aVals[7], &aVals[8], &aVals[9],
                                  &index, &a, &b);
        if (err == 0) {
            pRow = &((Record_802297D8 *)pTable)[index];
            pRow->mUnknown0 = a;
            pRow->mUnknown4 = b;
            pRow->mUnknown30 = 0.0f;
            for (i = 0; i < 10; i++) {
                pRow->aUnknown8[i] = aVals[i];
                pRow->mUnknown30 += aVals[i];
            }
        }
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
    if (err == 0) {
        err = DbTatsCopyTblDestroy(0, tag);
    } else {
        DbTatsCopyTblDestroy(0, tag);
    }
    return err;
}

int DbYalpModuleInit(void)
{
    int result = DbYalpLoadWeightTable(lbl_803A1C60, 0x43524F50);
    if (result == 0) {
        result = DbYalpLoadWeightTable(lbl_803A20A4, 0x524F4250);
    } else {
        DbYalpLoadWeightTable(lbl_803A20A4, 0x524F4250);
    }
    return result;
}

int DbYalpModuleShutdown(void)
{
    return MemFill(lbl_803A1C60, 1092, 0, 4);
}

extern char lbl_802B255C[];
extern char lbl_802B259C[];

int DbFindUnusedPlayerIds(int db, int tbl, int *pIds, unsigned short *pCount)
{
    struct QueryCursor cursor;
    int status = 0;
    int id;
    int prev;
    int next;
    int last;
    unsigned short count;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, lbl_802B255C, db, &cursor, tbl);
    prev = -1;
    next = -1;
    last = 0x7FFF;
    count = 0;
    while (status == 0 && count < *pCount) {
        status = TDbCompilePerformOp(0, lbl_802B259C, &cursor, &id);
        if (status == 0) {
            if (id > prev + 1) {
                next = prev + 1;
                while (status == 0 && next < id && count < *pCount && next <= 0x7F14) {
                    pIds[count] = next;
                    count++;
                    next++;
                }
            }
            last = (next > id) ? next : id;
            prev = id;
        }
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    if (status == 0 && count < *pCount) {
        next = last + 1;
        if (last == 0x7FFF) {
            next = 0;
        }
        while (count < *pCount && next <= 0x7F14) {
            pIds[count] = next;
            count++;
            next++;
        }
    }
    *pCount = count;
    return status;
}

float DbYalpGetLowRating(int index)
{
    return lbl_803A20A4[index].mUnknown4;
}

float DbYalpGetHighRating(int index)
{
    return lbl_803A20A4[index].mUnknown0;
}

float DbYalpGetRatingWeight(int index, int item)
{
    return lbl_803A20A4[index].aUnknown8[item];
}

float DbYalpGetWeightSum(int index)
{
    return lbl_803A20A4[index].mUnknown30;
}

unsigned int DbYalpGetOverallRating(int index, int *pRatings, int clamp)
{
    float sum = 0.0f;
    float weight;
    float total;
    float low;
    float high;
    int i;

    for (i = 0; i < 10; i++) {
        weight = DbYalpGetRatingWeight(index, i);
        if (weight <= 0.0f) {
            continue;
        }
        sum += pRatings[i] * weight;
    }
    total = DbYalpGetWeightSum(index);
    low = DbYalpGetLowRating(index);
    high = DbYalpGetHighRating(index);
    sum -= low * total;
    sum /= (high - low) * total * (1.0f / 99.0f);
    sum += 0.5f;
    if (!(sum >= 0.0f)) {
        sum = 0.0f;
    }
    if (clamp == 1) {
        if (sum < 12.0f) {
            sum = 12.0f;
        } else if (!(sum <= 100.0f)) {
            sum = 100.0f;
        }
    }
    return sum;
}

int DbYalpBeginGame(void)
{
    return 0;
}

int DbYalpResumeGame(void)
{
    return 0;
}

