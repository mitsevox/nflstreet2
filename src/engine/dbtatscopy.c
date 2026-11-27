/* Partial source: holds the 'TATS' template database and copies its tables into another database. */

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
extern char lbl_803A1C60[];
extern float lbl_803A20A4[][13];
extern char *_DbEvas_pFileName;
extern int _DbEvas_iMode;
extern int _DbEvas_iSize;
static int _DbTatsCopy_iSize = 0;
static char *_DbTatsCopy_pFileName = 0;
static int _DbTatsCopy_iMode = -1;
extern int _DbUser_iSize;
extern char *_DbUser_pFileName;
extern int _DbUser_iMode;
extern int _DbUser_iCurrent;
extern unsigned char _DbUser_iCount;
extern DbUserEntry_t _DbUser_aEntries[];
extern TDbIODevice_t tdbiofioCallback;
extern int TDbTblDestroy(int db, int tbl);

extern const unsigned char lbl_802AEF10[];
extern const int _DbUser_aDbIds[2];
extern char lbl_802B5D64[];
extern char lbl_802B56F4[];
extern char lbl_802B5744[];
extern char lbl_802B4EA0[];
extern char lbl_802B4EC4[];
extern char _DbSrpt_szDeclareTeamsByFlagQuery[];
extern char _DbSrpt_szDeclareTeamsByFlagTypeQuery[];
extern char _DbSrpt_szFetchTeamIdQuery[];
extern char _DbSrpt_szDeclareSrptQuery[];
extern char lbl_802B479C[];
extern char lbl_802B4828[];
extern int TDbExists(int db);
extern char _DbSrpt_szDeclareTeamIdsQuery[];
extern char _DbSrpt_szFetchSrptQuery[];
extern int TDbTblExists(int db, int tbl);
int DbTatsCopyTblDestroy(int db, int tbl);
extern char lbl_802B5A48[];
extern char lbl_802B5AB0[];
extern char lbl_802B5ACC[];
extern char lbl_802B5B34[];
extern char lbl_802B5B64[];
extern char lbl_802B5BDC[];

extern char lbl_802B48C4[];
extern char lbl_802B4A54[];
extern char lbl_802B4A9C[];
extern char lbl_802B4AE0[];

#include "engine/DbNiomHandlers.h"



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

/* Ends a column list for TDbInsertRow. */
static inline void fn_801F9718_SetEnd(TDbCol_801F9718 *pCol)
{
    pCol->mCol = -1;
    pCol->mUnk4 = -1;
    pCol->mUnk0 = 0;
}


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
extern int lbl_803EC020[2];
extern int *lbl_803EC010[1];
extern unsigned char lbl_803EC014[1];
extern TDbCol_801F9718 **lbl_803EC018[1];
extern unsigned char *lbl_803EC01C[1];
extern TDbCol_801F9718 *lbl_803EC024[1];
extern unsigned char lbl_803ED01C[1];
extern int (*lbl_803EC028)(int a, int b, int c, int d);
extern int (*lbl_803EC02C)(int a);

int DbUslpSetFilter1(int (*pCallback)(int a));
int DbUslpSetFilter2(int (*pCallback)(int a));































































































































































/* prototypes of the db functions in 0x80229270-0x8022F428 (dbocmt.c to dbuser.c) */
void *DbUtilAlloc(int size, int a);
void DbUtilFree(void *p);
int DbUslpSetFilter1(int (*pCallback)(int a));
int DbUslpSetFilter2(int (*pCallback)(int a));
int DbTatsCopyInit(int a, const char *pName, int b);
void DbTatsCopyShutdown(void);
int DbTatsCopyOpen(void);
int DbTatsCopyClose(void);
int DbTatsCopyTable(int a, int b);
int DbTatsCopyAllTables(int db, int a, int b);

int DbTatsCopyInit(int a, const char *pName, int b)
{
    _DbTatsCopy_pFileName = DbUtilAlloc(strlen(pName) + 1, 1);
    strcpy(_DbTatsCopy_pFileName, pName);
    _DbTatsCopy_iMode = b;
    return 0;
}

void DbTatsCopyShutdown(void)
{
    DbUtilFree(_DbTatsCopy_pFileName);
    _DbTatsCopy_iSize = 0;
    _DbTatsCopy_pFileName = 0;
    _DbTatsCopy_iMode = -1;
}

int DbTatsCopyOpen(void)
{
    int result = TDbCreate(0x54415453, _DbTatsCopy_iSize);
    if (result == 0) {
        result = TDbExtLoadFromResource(0x54415453, _DbTatsCopy_pFileName, _DbTatsCopy_iMode, 0);
    }
    return result;
}

int DbTatsCopyClose(void)
{
    return TDbDestroy(0x54415453);
}

int DbTatsCopyTable(int a, int b)
{
    return TDbCompilePerformOp(0, "use 'TATS' select into \214.\214 * from \214\n", a, b, b);
}

int DbTatsCopyTblDestroy(int db, int tbl)
{
    return TDbTblDestroy(db, tbl);
}

int DbTatsCopyAllTables(int db, int a, int b)
{
    struct QueryCursor cursor;
    int tbl;
    int *pTbl;
    int status = 0;
    int opened = 0;

    if (TDbExists(0x54415453) != 0) {
        status = DbTatsCopyOpen();
        opened = status == 0;
    }
    if (status == 0) {
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        status = TDbCompilePerformOp(0, "use \214 declare \212 cursor for select * from \214 where (\214 = \202)\n", db, &cursor, a, b, 1);
        if (status == 0) {
            pTbl = &tbl;
            do {
                status = TDbCompilePerformOp(0, "fetch from \212 'FERT' into \202\n", &cursor, pTbl);
                if (status == 0 && TDbTblExists(db, tbl) != 0) {
                    status = DbTatsCopyTable(db, tbl);
                    if (QUERY_STATUS_ACCEPTED(status) == 1) {
                        status = 0;
                    }
                }
            } while (status == 0);
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
    }
    if (opened == 1) {
        if (status == 0) {
            status = DbTatsCopyClose();
        } else {
            DbTatsCopyClose();
        }
    }
    return status;
}
