/* Partial source for several game-database modules (player, roster and team tables) not yet cut into their files. */

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
extern float lbl_803A20A4[][13];
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
extern int fn_802297D8(void *p, int tag);
extern int fn_8022D8F8(int a, int *p, int c);
int DbResetGameInfo(void);
extern int DbUserFindIdByDb(int key);
extern int DbUserGetCurrent(void);
extern void fn_80231208(void);
int DbUserGetDb(int key);
extern const int _DbUser_aDbIds[2];
extern char lbl_802B5D64[];
extern char lbl_802B56F4[];
extern char lbl_802B5744[];
extern char lbl_802B4EA0[];
extern char lbl_802B4EC4[];
extern char lbl_802B37E4[];
extern char lbl_802B3824[];
int fn_8022C0E0(struct QueryCursor cursor, int a);
extern int TDbQryGetCount(int ref, unsigned short *pCount);
extern int fn_80230D8C(int id, int a, int b);
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
extern struct QueryCursor lbl_802FA8B0;
extern unsigned short lbl_803EC060;
extern int *lbl_803EC084;
extern unsigned short lbl_803EC088;
extern int (*lbl_803EC08C)[2];
extern unsigned short lbl_803EC090;
extern int (*lbl_803EC094)[3];
extern unsigned short lbl_803EC098;
extern int lbl_802FAA50[][10][2];
int DbLoadConferenceIds(void);
int DbLoadDivisionIds(void);
int DbLoadTeamList(void);
int fn_8022E9E4(void);
void fn_8022EA4C(void);

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

extern Record_8022D874 lbl_802FA8C0[];
extern char lbl_802B48C4[];
extern char lbl_802B4A54[];
extern char lbl_802B4A9C[];
extern char lbl_802B4AE0[];
void DbBuildPendingNodeList(void *pPairs);
void DbAssignPendingNodeIds(void);
int DbLoadTeamDepthChart(int key, int mode);
int fn_8022D710(int a, int b, int c, int row, int value);
unsigned short fn_8022D6FC(int index);

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

void fn_8022CAEC(Node_8022CC6C **ppHead);

extern int fn_8022A624(Object_8022A59C *p, struct QueryCursor cursor, int a, int b);
extern int fn_802303B4(int key, unsigned short *pId);
extern int fn_80230CC8(unsigned short id);
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
extern unsigned short lbl_802FAA1C[];
typedef struct Entry_803A2390 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
} Entry_803A2390;

typedef struct Record_8022A304 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    char mUnknownF[1];
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    unsigned short mUnknown14;
    char mUnknown16[2];
} Record_8022A304;

/* Ends a column list for TDbInsertRow. */
static inline void fn_801F9718_SetEnd(TDbCol_801F9718 *pCol)
{
    pCol->mCol = -1;
    pCol->mUnk4 = -1;
    pCol->mUnk0 = 0;
}

extern Record_8022A304 lbl_802FA180[21];
extern Record_8022A304 lbl_802FA378[17];
extern Record_8022A304 lbl_802FA510[10];

typedef struct Callbacks_8022B02C {
    int (*mpUnknown0)(int a, int b, int c, int d);
    int (*mpUnknown4)(int a);
} Callbacks_8022B02C;

typedef struct Callbacks_8022C214 {
    int (*mpUnknown0)(int a);
    int (*mpUnknown4)(int a);
} Callbacks_8022C214;

extern Entry_803A2390 lbl_803A2390[];
extern char lbl_803A23E8[];
extern char lbl_803A2474[];
extern struct QueryCursor lbl_803A25E0;
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
extern int fn_802311C8(int a);
extern int (*lbl_803EC028)(int a, int b, int c, int d);
extern int (*lbl_803EC02C)(int a);
extern unsigned char lbl_803EC030;
extern int (*lbl_803EC034)(int a);
extern int (*lbl_803EC038)(int a);
extern int (*lbl_803EC048)(int a);
extern int (*lbl_803EC04C)(int a);
extern Node_8022CC6C *lbl_803EC050;
extern Node_8022CC6C *lbl_803EC054;
extern Node_8022CC6C *lbl_803EC058;
extern Record_8022D5A4 *lbl_803EC05C;
extern unsigned short lbl_803EC060;
extern int lbl_803EC064;
extern int lbl_803EC068;
extern int lbl_803EC06C;
extern int lbl_803EC070;
extern int lbl_803EC074;
extern int lbl_803EC07C;
extern int lbl_803EC080;

int DbNiomCloseCursor(void);
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022BF60(void);
int fn_8022BF68(void);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void fn_8022CADC(void);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
void fn_8022CDA0(void);
int fn_8022D14C(int a);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));































































































































































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
int fn_802299FC(void);
int fn_80229A70(void);
float fn_80229C98(int index);
float fn_80229CB0(int index);
float fn_80229CC4(int index, int item);
float fn_80229CE4(int index);
int fn_80229E78(void);
int fn_80229E80(void);
void fn_8022A304(void);
int fn_8022A428(int a);
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
int fn_8022C02C(int a, int b, int c, int d);
int fn_8022C098(int a);
int fn_8022C0E0(struct QueryCursor cursor, int a);
int fn_8022C214(Callbacks_8022C214 *pCallbacks);
void fn_8022C3C8(void);
int fn_8022C410(int a);
int fn_8022C518(int a);
int fn_8022C628(int db, int tbl, int *pIds, unsigned short *pCount);
int fn_8022C81C(int a);
int fn_8022C858(int a);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void DbUtilSetHeap(int a);
void *DbUtilAlloc(int size, int a);
void DbUtilFree(void *p);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void DbBuildPendingNodeList(void *pPairs);
void fn_8022CADC(void);
void fn_8022CAEC(Node_8022CC6C **ppHead);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
Node_8022CC6C *fn_8022CC98(Node_8022CC6C **ppHead, unsigned short key);
void fn_8022CCC4(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void fn_8022CD0C(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
int fn_8022CD40(int a, int b, int c);
void fn_8022CDA0(void);
void fn_8022CDF8(void);
int fn_8022D14C(int a);
int fn_8022D154(void);
int fn_8022D1B8(void);
int fn_8022D23C(void);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));
int fn_8022D268(int a, int b, int c, void *pPairs, int action, int mode);
int fn_8022D2F4(int a, int b, int c, void *pPairs, int mode);
int fn_8022D3AC(void);
unsigned short fn_8022D3D4(unsigned char key);
int DbOpenDepthChartCursor(int a, int b, int mode);
int fn_8022D540(void);
int DbLoadTeamDepthChart(int key, int mode);
int fn_8022D6E8(void);
void fn_8022D6F0(void);
unsigned short fn_8022D6FC(int index);
int fn_8022D710(int a, int b, int c, int row, int value);
int DbTableLookupByte(int row, int column);
int fn_8022D864(void);
int fn_8022D86C(void);
int fn_8022D874(int a, int b, int c, int key);
int fn_8022D8F8(int a, int *p, int tag);
int fn_8022DA44(int a, int *b, int c, int *d, int e);
int fn_8022DA90(int *p);
void fn_8022DB08(void);
int DbResetGameInfo(void);
int fn_8022DBF4(int value);
int fn_8022DC38(int value);
int fn_8022DC7C(int value);
int fn_8022DCB0(int value);
int fn_8022DCE4(int value);
int fn_8022DD18(int value);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
int fn_8022DDB4(int a, void *p);
int fn_8022E21C(int a, int b);
int fn_8022E558(void);
int fn_8022E560(void);
int DbLoadConferenceIds(void);
void fn_8022E694(void);
int DbLoadDivisionIds(void);
void fn_8022E7FC(void);
int DbLoadTeamList(void);
void fn_8022E96C(void);
int fn_8022E9A4(void);
void fn_8022E9C4(void);
int fn_8022E9E4(void);
void fn_8022EA4C(void);
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

int fn_802299FC(void)
{
    int result = fn_802297D8(lbl_803A1C60, 0x43524F50);
    if (result == 0) {
        result = fn_802297D8(lbl_803A20A4, 0x524F4250);
    } else {
        fn_802297D8(lbl_803A20A4, 0x524F4250);
    }
    return result;
}

int fn_80229A70(void)
{
    return MemFill(lbl_803A1C60, 1092, 0, 4);
}

float fn_80229C98(int index)
{
    return lbl_803A20A4[index][1];
}

float fn_80229CB0(int index)
{
    return lbl_803A20A4[index][0];
}

float fn_80229CC4(int index, int item)
{
    return lbl_803A20A4[index][item + 2];
}

float fn_80229CE4(int index)
{
    return lbl_803A20A4[index][12];
}

int fn_80229E78(void)
{
    return 0;
}

int fn_80229E80(void)
{
    return 0;
}

void fn_8022A304(void)
{
    unsigned short i;

    for (i = 0; i < 21; i++) {
        lbl_802FA180[i].mUnknown0 = 31;
        lbl_802FA180[i].mUnknown4 = 31;
        lbl_802FA180[i].mUnknown8 = 7;
        lbl_802FA180[i].mUnknownC = 0;
        lbl_802FA180[i].mUnknownD = 0;
        lbl_802FA180[i].mUnknownE = 0;
        lbl_802FA180[i].mUnknown10 = 0;
        lbl_802FA180[i].mUnknown12 = 0;
        lbl_802FA180[i].mUnknown14 = 0;
    }
    for (i = 0; i < 17; i++) {
        lbl_802FA378[i].mUnknown0 = 31;
        lbl_802FA378[i].mUnknown4 = 31;
        lbl_802FA378[i].mUnknown8 = 7;
        lbl_802FA378[i].mUnknownC = 0;
        lbl_802FA378[i].mUnknownD = 0;
        lbl_802FA378[i].mUnknownE = 0;
        lbl_802FA378[i].mUnknown10 = 0;
        lbl_802FA378[i].mUnknown12 = 0;
        lbl_802FA378[i].mUnknown14 = 0;
    }
    for (i = 0; i < 10; i++) {
        lbl_802FA510[i].mUnknown0 = 31;
        lbl_802FA510[i].mUnknown4 = 31;
        lbl_802FA510[i].mUnknown8 = 7;
        lbl_802FA510[i].mUnknownC = 0;
        lbl_802FA510[i].mUnknownD = 0;
        lbl_802FA510[i].mUnknownE = 0;
        lbl_802FA510[i].mUnknown10 = 0;
        lbl_802FA510[i].mUnknown12 = 0;
        lbl_802FA510[i].mUnknown14 = 0;
    }
}

int fn_8022A428(int a)
{
    return TDbCompilePerformOp(0, lbl_802B2F64, a, 1023, 1023, 31, -1, 3, 15, 7, -1, 0);
}

int fn_8022A490(unsigned int count)
{
    int err = TDbCompilePerformOp(0, lbl_802B3010);

    if (err == 0) {
        int id = 0;
        unsigned short i;

        for (i = 0; i < count; i++) {
            if ((err = fn_8022A428(id)) == 0) {
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

int fn_8022A59C(int a, Object_8022A59C **ppOut)
{
    int err = DbLockAcquire();
    Object_8022A59C *p = DbUtilAlloc(8, 0);

    p->mUnknown4 = a;
    p->mUnknown0 = -1;
    if (err == 0) {
        err = fn_802303B4(0, &p->mUnknown0);
    }
    if (err == 0) {
        *ppOut = p;
    } else {
        fn_8022AC80(p);
        *ppOut = 0;
    }
    return err;
}

int fn_8022AB6C(Object_8022A59C *p, int a, int b)
{
    struct QueryCursor cursor;
    int err;

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

int fn_8022AC80(Object_8022A59C *p)
{
    int err = 0;

    if (p->mUnknown0 != 0xFFFF) {
        err = fn_80230CC8(p->mUnknown0);
    }
    if (err == 0) {
        err = DbLockRelease();
    } else {
        DbLockRelease();
    }
    DbUtilFree(p);
    return err;
}

int fn_8022ACEC(int key, int unused, int col, int value, int index)
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

int fn_8022AF5C(int key, int unused, int col, int value, int set, int index)
{
    TDbCol_801F9718 aCols[4];
    int table;
    int err;

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
            if (TDbTblExists(0, table) == 0) {
                status = fn_8022AD64(table, &lbl_803EC018[i][j], &lbl_803EC01C[i][j]);
            } else {
                lbl_803EC018[i][j] = 0;
                lbl_803EC01C[i][j] = 0;
            }
            if (status != 0) {
                break;
            }
        }
        if (status != 0) {
            break;
        }
    }
    for (i = 0; i < 1 && status == 0; i++) {
        table = lbl_803EC020[i];
        if (TDbTblExists(0, table) == 0) {
            status = fn_8022AD64(table, &lbl_803EC024[i], &lbl_803ED01C[i]);
        } else {
            lbl_803ED01C[i] = 0;
        }
    }
    if (status == 0) {
        if (pCallbacks != 0) {
            lbl_803EC028 = pCallbacks->mpUnknown0;
            lbl_803EC02C = pCallbacks->mpUnknown4;
        }
        status = fn_802311C8(0);
    }
    return status;
}

void fn_8022B200(void)
{
    unsigned char i;
    unsigned char j;
    unsigned char count;

    fn_80231208();
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

/* Writes value into column col of the 'DIGP' row key of the set selected by the column's
   third letter; when no row matched (23) the row is added through 0x8022AF5C. Returns 131
   for a column letter without a set. */
int fn_8022B2CC(int key, unsigned int col, int value)
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
    if (index < 0) {
        return 131;
    }
    table = lbl_803EC010[0][index];
    aCols[0].mUnk0 = value;
    aCols[0].mUnk4 = table;
    aCols[0].mCol = col;
    fn_801F9718_SetEnd(&aCols[1]);
    expr.mLeft.mType = 6;
    expr.mLeft.mValue.l = _DbColKey(table, 0x44494750);
    expr.mRight.mType = 3;
    expr.mRight.mValue.i = key;
    expr.mOp = 0x10003;
    aTables[0].mId = table;
    aTables[0].mJoinType = 2;
    aTables[0].mExpr = &expr;
    aTables[1].mId = -1;
    aTables[1].mJoinType = 2;
    aTables[1].mExpr = 0;
    err = TDbQrySetFirstRow(0, aTables, 0, aCols, 0, 0);
    if (err == 23) {
        err = fn_8022AF5C(key, -1, col, value, 0, index);
    }
    return err;
}

/* Reads column col of the 'DIGP' row key of the set selected by the column's third letter
   into *pOut; returns 131 for a letter without a set, 132 when no row matched. */
int fn_8022B414(int key, unsigned int col, int *pOut)
{
    TDbSQLTableRef_801FDC18 aTables[2];
    TDbCol_801F9718 aCols[2];
    TDbExpr_t expr;
    unsigned int c;
    int index;
    int table;
    int err;
    int ok;

    *pOut = 0;
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
        expr.mLeft.mType = 6;
        expr.mLeft.mValue.l = _DbColKey(table, 0x44494750);
        expr.mRight.mType = 3;
        expr.mRight.mValue.i = key;
        expr.mOp = 0x10003;
        aTables[0].mId = table;
        aTables[0].mJoinType = 2;
        aTables[0].mExpr = &expr;
        aTables[1].mId = -1;
        aTables[1].mJoinType = 2;
        aTables[1].mExpr = 0;
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

/* Reads column col of the row of the first table whose 'DIGT' column equals value; returns
   0 with the value in *pOut, 132 when the query ended without a row, or the query error. */
int fn_8022B7A4(int value, int col, int *pOut)
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
    expr.mLeft.mType = 6;
    expr.mLeft.mValue.l = _DbColKey(table, 0x44494754);
    expr.mRight.mType = 3;
    expr.mRight.mValue.i = value;
    expr.mOp = 0x10003;
    aTables[0].mId = table;
    aTables[0].mJoinType = 2;
    aTables[0].mExpr = &expr;
    aTables[1].mId = -1;
    aTables[1].mJoinType = 2;
    aTables[1].mExpr = 0;
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

int fn_8022C02C(int a, int b, int c, int d)
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

int fn_8022C098(int a)
{
    int err = 0;

    if (lbl_803EC02C != 0) {
        err = lbl_803EC02C(a);
    }
    if (err == 0) {
        err = fn_8022BF60();
    }
    return err;
}

int fn_8022C0E0(struct QueryCursor cursor, int a)
{
    unsigned short total;
    int *pIds;
    int id;
    int status;
    unsigned short count;
    unsigned short i;

    pIds = 0;
    status = TDbQryGetCount(cursor.mUnknown0, &total);
    if (status == 0) {
        pIds = DbUtilAlloc(total * 4, 0);
    }
    count = 0;
    if (status == 0) {
        while (status == 0) {
            status = TDbCompilePerformOp(0, lbl_802B3610, &cursor, &id);
            if (status == 0) {
                pIds[count] = id;
                count++;
            }
        }
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = 0;
        }
        if (status == 0) {
            for (i = 0; i < count; i++) {
                status = fn_80230D8C(pIds[i], 0, a);
                if (status != 0) {
                    break;
                }
            }
        }
    }
    if (pIds != 0) {
        DbUtilFree(pIds);
    }
    return status;
}

int fn_8022C214(Callbacks_8022C214 *pCallbacks)
{
    struct QueryCursor cursor;
    int status = 0;
    int index;
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, lbl_802B3698, &cursor);
    while (status == 0) {
        status = TDbCompilePerformOp(0, lbl_802B36C4, &cursor, &index, &a, &b, &c, &d);
        if (status == 0) {
            lbl_803A2390[index].mUnknown0 = a;
            lbl_803A2390[index].mUnknown2 = b;
            lbl_803A2390[index].mUnknown4 = c;
            lbl_803A2390[index].mUnknown6 = d;
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
    if (status == 0) {
        status = DbTatsCopyTblDestroy(0, 0x53525054);
    } else {
        DbTatsCopyTblDestroy(0, 0x53525054);
    }
    lbl_803EC030 = 0;
    if (status == 0) {
        lbl_803EC030 = TDbTblExists(0, 0x53525054) == 0;
        if (pCallbacks != 0) {
            lbl_803EC034 = pCallbacks->mpUnknown0;
            lbl_803EC038 = pCallbacks->mpUnknown4;
        }
    }
    return status;
}

void fn_8022C3C8(void)
{
    MemFill((char *)lbl_803A2390, 88, 0, 4);
    lbl_803EC030 = 0;
    lbl_803EC034 = 0;
    lbl_803EC038 = 0;
}

int fn_8022C410(int a)
{
    struct QueryCursor cursor;
    int status = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, lbl_802B37E4, &cursor, 0);
    if (status == 0) {
        status = fn_8022C0E0(cursor, a);
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
    return status;
}

int fn_8022C518(int a)
{
    struct QueryCursor cursor;
    int status = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, lbl_802B3824, &cursor, 0, 5, 1);
    if (status == 0) {
        status = fn_8022C0E0(cursor, a);
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
    return status;
}

int fn_8022C628(int db, int tbl, int *pIds, unsigned short *pCount)
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
    status = TDbCompilePerformOp(0, lbl_802B3888, db, &cursor, tbl);
    prev = -1;
    next = -1;
    last = 1023;
    count = 0;
    while (status == 0 && count < *pCount) {
        status = TDbCompilePerformOp(0, lbl_802B3610, &cursor, &id);
        if (status == 0) {
            if (id > prev + 1) {
                next = prev + 1;
                while (status == 0 && next < id && count < *pCount && next <= 1008) {
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
        if (last == 1023) {
            next = 0;
        }
        while (count < *pCount && next <= 1008) {
            pIds[count] = next;
            count++;
            next++;
        }
    }
    *pCount = count;
    return status;
}

int fn_8022C81C(int a)
{
    if (lbl_803EC034 != 0) {
        return lbl_803EC034(a);
    }
    return 0;
}

int fn_8022C858(int a)
{
    if (lbl_803EC038 != 0) {
        return lbl_803EC038(a);
    }
    return 0;
}
