/* The game database's player statistics queries: the 'OCCP' update handler that fills the
   computed columns of a statistics row (passer rating, completion percentage, yards per
   attempt), one query per statistics category that copies the matching rows of a player
   statistics table into a scratch table, computes its derived columns and opens a cursor over
   it, and the NFL passer rating formula. */

#include "engine/t3db.h"
#include "engine/t3db_cols.h"
#include "game/TDbCompilePerformOp.h"

typedef int (*DbOccpQueryFunc)(const char *pWhere, int b, unsigned long long orderKey, int orderDir,
                               struct QueryCursor *pCursor);

extern int TDbTblFindUnusedId(int db, int *pTable);
extern int TDbRegisterHandler(void *pCallback, int tag);
extern int TDbUnregisterHandler(int tag);
extern int TDbQryUpdateWithHandler(int db, TDbSQLTableRef_801FDC18 *pTables, TDbExpr_t *pWhere, int tag,
                                   TDbCol_801F9718 *pCols, int id, void *pRes, int cb);
extern int TDbQryUpdateExpr(int db, TDbSQLTableRef_801FDC18 *pTables, TDbExpr_t *pWhere,
                            unsigned long long *pKeys, TDbExpr_t *pTerms, void *pRes, int cb);
extern float floorf(float x);

int DbOccpModuleInit(int db);
void DbOccpModuleShutdown(void);
void DbOccpUpdateHandler(TDbCol_801F9718 *pCols, int mode, unsigned char *pDone);
float DbOccpPasserRating(int att, int yds, int comp, int td, int ints);

int _DbOccp_iHandlerTag = 0;
int _DbOccp_iDb = -1;

/* 1 when a query status counts as success (0, 23, 21 or 20). */
static inline int _DbOccpAccepted(int err)
{
    if (err == 0 || err == 23 || err == 21 || err == 20) {
        return 1;
    }
    return 0;
}

#define DBOCCP_KEY(table, col) (((unsigned long long)(unsigned int)(table) << 32) | (unsigned int)(col))

static inline unsigned long long _DbOccpKey(unsigned int table, unsigned int col)
{
    return ((unsigned long long)table << 32) | col;
}

static inline void _DbOccpSetCol(TDbCol_801F9718 *pCol, int table, int col)
{
    pCol->mCol = col;
    pCol->mUnk4 = table;
    pCol->mUnk0 = 0;
}

static inline void _DbOccpSetColEnd(TDbCol_801F9718 *pCol)
{
    pCol->mCol = -1;
    pCol->mUnk4 = -1;
    pCol->mUnk0 = 0;
}

static inline void _DbOccpSetTable(TDbSQLTableRef_801FDC18 *pRef, unsigned int id, unsigned int join,
                                   TDbExpr_t *pExpr)
{
    pRef->mExpr = pExpr;
    pRef->mId = id;
    pRef->mJoinType = join;
}

/* integer result of a sub-expression */
static inline void _DbOccpSetTrunc(TDbExpr_t *pExpr, TDbExpr_t *pSub)
{
    pExpr->mOp = 0;
    pExpr->mLeft.mType = TDB_TYPE_EXPR_TRUNC;
    pExpr->mLeft.mValue.p = pSub;
    pExpr->mRight.mType = 16;
}

/* column op column */
static inline void _DbOccpSetColCol(TDbExpr_t *pExpr, int op, unsigned long long colA, unsigned long long colB)
{
    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_COLUMN;
    pExpr->mLeft.mValue.l = colA;
    pExpr->mRight.mType = TDB_TYPE_COLUMN;
    pExpr->mRight.mValue.l = colB;
}

/* column op integer */
static inline void _DbOccpSetColInt(TDbExpr_t *pExpr, int op, unsigned long long col, int value)
{
    int *pValue;

    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_COLUMN;
    pExpr->mLeft.mValue.l = col;
    pExpr->mRight.mType = TDB_TYPE_INT;
    /* FAKEMATCH: the integer stored through a pointer to the value field, for the target's frame-based store address; the same field is set. */
    pValue = &pExpr->mRight.mValue.i;
    *pValue = value;
}

/* sub-expression op column */
static inline void _DbOccpSetSubCol(TDbExpr_t *pExpr, int op, TDbExpr_t *pSub, unsigned long long col)
{
    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_EXPR_TRUNC;
    pExpr->mLeft.mValue.p = pSub;
    pExpr->mRight.mType = TDB_TYPE_COLUMN;
    pExpr->mRight.mValue.l = col;
}

/* float sub-expression op float */
typedef union DbOccpFloatBits {
    float f;
    unsigned int u;
} DbOccpFloatBits;

static inline void _DbOccpSetSubFloat(TDbExpr_t *pExpr, int op, TDbExpr_t *pSub, float value)
{
    DbOccpFloatBits v;

    v.f = value;
    /* FAKEMATCH: value stored first, an order found by a permutation search for the float queries' schedule; the same five fields are set. */
    pExpr->mRight.mValue.u = v.u;
    pExpr->mLeft.mType = TDB_TYPE_EXPR_FLOAT;
    pExpr->mLeft.mValue.p = pSub;
    pExpr->mRight.mType = TDB_TYPE_FLOAT;
    pExpr->mOp = op;
}

int DbOccpModuleInit(int db)
{
    _DbOccp_iDb = db;
    _DbOccp_iHandlerTag = 0x4F434350;
    return TDbRegisterHandler(DbOccpUpdateHandler, 0x4F434350);
}

void DbOccpModuleShutdown(void)
{
    _DbOccp_iDb = -1;
    TDbUnregisterHandler(_DbOccp_iHandlerTag);
    _DbOccp_iHandlerTag = 0;
}

void DbOccpUpdateHandler(TDbCol_801F9718 *pCols, int mode, unsigned char *pDone)
{
    if (pCols == 0) {
        if (pDone != 0) {
            *pDone = 0;
        }
        return;
    }
    pCols[5].mUnk0 = DbOccpPasserRating(pCols[0].mUnk0, pCols[1].mUnk0, pCols[2].mUnk0, pCols[3].mUnk0, pCols[4].mUnk0) * 10.0f;
    if (mode == 2) {
        pCols[6].mUnk0 = pCols[2].mUnk0 * 100 / pCols[0].mUnk0;
        pCols[7].mUnk0 = (float)pCols[1].mUnk0 / (float)pCols[0].mUnk0 * 10.0f;
    }
    *pDone = 1;
}

/* Discarded: the handler of the second statistics table, never registered. */
static void _DbOccpUpdateTeamHandler(TDbCol_801F9718 *pCols, int mode, unsigned char *pDone)
{
    int att;
    int plays;

    if (pCols == 0) {
        if (pDone != 0) {
            *pDone = 0;
        }
        return;
    }
    if (mode == 0) {
        plays = pCols[1].mUnk0;
        att = pCols[0].mUnk0;
        pCols[20].mUnk0 = att + plays;
        pCols[21].mUnk0 = pCols[3].mUnk0 ? (int)((float)pCols[2].mUnk0 / pCols[3].mUnk0 * 10.0f) : 0;
        pCols[22].mUnk0 = pCols[5].mUnk0 ? (int)((float)pCols[4].mUnk0 / pCols[5].mUnk0 * 10.0f) : 0;
        pCols[23].mUnk0 = att ? pCols[6].mUnk0 * 100 / att : 0;
        pCols[24].mUnk0 = pCols[6].mUnk0 ? (int)((float)pCols[7].mUnk0 / pCols[6].mUnk0 * 10.0f) : 0;
        pCols[25].mUnk0 = plays ? (int)((float)pCols[8].mUnk0 / plays * 10.0f) : 0;
        pCols[26].mUnk0 = pCols[11].mUnk0
                              ? (int)((float)(pCols[10].mUnk0 + pCols[9].mUnk0) / pCols[11].mUnk0 * 100.0f)
                              : 0;
        pCols[27].mUnk0 = pCols[13].mUnk0 ? pCols[12].mUnk0 * 100 / pCols[13].mUnk0 : 0;
        pCols[28].mUnk0 = pCols[15].mUnk0 ? pCols[114].mUnk0 * 100 / pCols[15].mUnk0 : 0;
        pCols[29].mUnk0 = pCols[17].mUnk0 ? pCols[16].mUnk0 * 100 / pCols[17].mUnk0 : 0;
        pCols[30].mUnk0 = pCols[18].mUnk0 - pCols[19].mUnk0;
    }
    *pDone = 1;
}

static inline void _DbOccpSetSubFloatP(TDbExpr_t *pExpr, int op, TDbExpr_t *pSub, float value)
{
    DbOccpFloatBits v;
    unsigned int *pValue;

    v.f = value;
    pExpr->mOp = op;
    pExpr->mLeft.mType = TDB_TYPE_EXPR_FLOAT;
    pExpr->mLeft.mValue.p = pSub;
    pExpr->mRight.mType = TDB_TYPE_FLOAT;
    /* FAKEMATCH: the float bits stored through a pointer to the value field, for the target's frame-based store address; the same field is set. */
    pValue = &pExpr->mRight.mValue.u;
    *pValue = v.u;
}

int DbOccpQueryPassing(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    TDbCol_801F9718 aCols[11];
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'FOGP'.'mcag' and 'FOGP'.'taag' and "
                              "'FOGP'.'ayag' and 'FOGP'.'dtag' and 'FOGP'.'niag' and 'FOGP'.'asag' and 'FOGP'.'Nlag' and "
                              "'OCCP'.'ppcp' and 'OCCP'.'ypcp' and 'OCCP'.'tpcp' and 'OCCP'.'rpcp' from 'FOGP' inner join "
                              "'YALP' on 'YALP'.'DIGP' = 'FOGP'.'DIGP' left outer join 'OCCP' on 'OCCP'.'DIGP' = "
                              "'YALP'.'DIGP' where 'FOGP'.'taag' != 0 and \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        _DbOccpSetCol(&aCols[0], table, 0x74616167);
        _DbOccpSetCol(&aCols[1], table, 0x61796167);
        _DbOccpSetCol(&aCols[2], table, 0x6D636167);
        _DbOccpSetCol(&aCols[3], table, 0x64746167);
        _DbOccpSetCol(&aCols[4], table, 0x6E696167);
        _DbOccpSetCol(&aCols[5], table, 0x72706370);
        _DbOccpSetCol(&aCols[6], table, 0x70706370);
        _DbOccpSetCol(&aCols[7], table, 0x74706370);
        _DbOccpSetCol(&aCols[8], table, 0x79706370);
        _DbOccpSetColEnd(&aCols[9]);
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateWithHandler(0, aTables, 0, _DbOccp_iHandlerTag, aCols, 2, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

int DbOccpQueryRushing(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    unsigned long long aKeys[3];
    TDbExpr_t aTerms[2];
    TDbExpr_t scale;
    TDbExpr_t ratio;
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'FOGP'.'ayug' and 'FOGP'.'taug' and "
                              "'FOGP'.'dtug' and 'FOGP'.'ufug' and 'FOGP'.'Nlug' and 'FOGP'.'tbug' and 'FOGP'.'y2ug' and "
                              "'FOGP'.'hyug' and 'OCCP'.'cscp' and 'OCCP'.'gscp' from 'FOGP' inner join 'YALP' on "
                              "'YALP'.'DIGP' = 'FOGP'.'DIGP' left outer join 'OCCP' on 'OCCP'.'DIGP' = 'YALP'.'DIGP' "
                              "where 'FOGP'.'taug' != 0 and \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        aKeys[0] = DBOCCP_KEY(table, 0x63736370);
        _DbOccpSetTrunc(&aTerms[0], &scale);
        _DbOccpSetSubFloatP(&scale, 0x40010, &ratio, 10.0f);
        _DbOccpSetColCol(&ratio, 0x100018, _DbOccpKey(table, 0x61797567), _DbOccpKey(table, 0x74617567));
        aKeys[1] = -1;
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateExpr(_DbOccp_iDb, aTables, 0, aKeys, aTerms, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

int DbOccpQueryReceiving(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    unsigned long long aKeys[4];
    TDbExpr_t aTerms[3];
    TDbExpr_t scale0;
    TDbExpr_t ratio0;
    TDbExpr_t scale1;
    TDbExpr_t ratio1;
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'FOGP'.'aycg' and 'FOGP'.'accg' and "
                              "'FOGP'.'cycg' and 'FOGP'.'dtcg' and 'FOGP'.'rdcg' and 'FOGP'.'Lrcg' and 'OCCP'.'crcp' and "
                              "'OCCP'.'grcp' and 'OCCP'.'arcp' from 'FOGP' inner join 'YALP' on 'YALP'.'DIGP' = "
                              "'FOGP'.'DIGP' left outer join 'OCCP' on 'OCCP'.'DIGP' = 'YALP'.'DIGP' where "
                              "('FOGP'.'accg' > 0 or 'FOGP'.'rdcg' > 0) and \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        aKeys[0] = DBOCCP_KEY(table, 0x61726370);
        _DbOccpSetTrunc(&aTerms[0], &scale0);
        _DbOccpSetSubFloat(&scale0, 0x40010, &ratio0, 10.0f);
        _DbOccpSetColCol(&ratio0, 0x100018, _DbOccpKey(table, 0x61796367), _DbOccpKey(table, 0x61636367));
        aKeys[1] = DBOCCP_KEY(table, 0x63726370);
        _DbOccpSetTrunc(&aTerms[1], &scale1);
        _DbOccpSetSubFloat(&scale1, 0x40010, &ratio1, 10.0f);
        _DbOccpSetColCol(&ratio1, 0x100018, _DbOccpKey(table, 0x63796367), _DbOccpKey(table, 0x61636367));
        aKeys[2] = -1;
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateExpr(_DbOccp_iDb, aTables, 0, aKeys, aTerms, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

int DbOccpQueryNone(void)
{
    return 3;
}

int DbOccpQueryBlocking(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "declare \x8a cursor for select into \x8c 'LOGP'.'DIGP' and 'YALP'.'DIGT' and 'LOGP'.'apog' "
                              "and 'LOGP'.'asog' from 'LOGP' inner join 'YALP' on 'YALP'.'DIGP' = 'LOGP'.'DIGP' where "
                              "\x8f order by \x8c.\x8c \x8e\n",
                              pCursor, table, pWhere, (int)(orderKey >> 32), (int)orderKey, orderDir);
    if (_DbOccpAccepted(err)) {
        /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
    }
    return err;
}

int DbOccpQueryDefense(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    unsigned long long aKeys[3];
    TDbExpr_t aTerms[2];
    TDbExpr_t scale;
    TDbExpr_t ratio;
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'EDGP'.'yisg' and 'EDGP'.'nisg' and "
                              "'EDGP'.'tisg' and 'EDGP'.'tflg' and 'EDGP'.'atdg' and 'EDGP'.'ltdg' and 'EDGP'.'kslg' and "
                              "'EDGP'.'fflg' and 'EDGP'.'rflg' and 'EDGP'.'yflg' and 'EDGP'.'lblg' and 'EDGP'.'aslg' and "
                              "'EDGP'.'Rlsg' and 'EDGP'.'dpdg' and 'DCCP'.'aicp' and 'DCCP'.'tdcp' from 'EDGP' inner join "
                              "'YALP' on 'YALP'.'DIGP' = 'EDGP'.'DIGP' left outer join 'DCCP' on 'DCCP'.'DIGP' = "
                              "'YALP'.'DIGP' where \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        aKeys[0] = DBOCCP_KEY(table, 0x61696370);
        _DbOccpSetTrunc(&aTerms[0], &scale);
        _DbOccpSetSubFloatP(&scale, 0x40010, &ratio, 10.0f);
        _DbOccpSetColCol(&ratio, 0x100018, _DbOccpKey(table, 0x79697367), _DbOccpKey(table, 0x6E697367));
        aKeys[1] = DBOCCP_KEY(table, 0x74646370);
        _DbOccpSetColCol(&aTerms[1], 0x4000D, _DbOccpKey(table, 0x74697367), _DbOccpKey(table, 0x74666C67));
        aKeys[2] = -1;
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateExpr(_DbOccp_iDb, aTables, 0, aKeys, aTerms, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

/* Kicking statistics: copies the kickers' stats into a scratch table, adds field goal and extra point percentages, and opens a sorted cursor on it. */
int DbOccpQueryKicking(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    unsigned long long aKeys[3];
    TDbExpr_t aTerms[2];
    TDbExpr_t made0;
    TDbExpr_t made1;
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'IKGP'.'Lfkg' and 'IKGP'.'mfkg' and "
                              "'IKGP'.'afkg' and 'IKGP'.'mekg' and 'IKGP'.'aekg' and 'IKGP'.'bfkg' and 'IKGP'.'bekg' and "
                              "'IKGP'.'btkg' and 'IKGP'.COL_PLYRSTAT_KICKFGMADE29ORLESS and 'IKGP'.'cmkg' and "
                              "'IKGP'.'dmkg' and 'IKGP'.'emkg' and 'IKGP'.COL_PLYRSTAT_KICKFGATTEMPTS29ORLESS and "
                              "'IKGP'.'cakg' and 'IKGP'.'dakg' and 'IKGP'.'eakg' and 'IKGP'.'knkg' and 'KCCP'.'pfcp' and "
                              "'KCCP'.'pxcp' from 'IKGP' inner join 'YALP' on 'YALP'.'DIGP' = 'IKGP'.'DIGP' left outer "
                              "join 'KCCP' on 'KCCP'.'DIGP' = 'YALP'.'DIGP' where ('IKGP'.'aekg' != 0 or 'IKGP'.'afkg' "
                              "!= 0 or 'IKGP'.'knkg' != 0) and \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        aKeys[0] = DBOCCP_KEY(table, 0x70666370);
        _DbOccpSetSubCol(&aTerms[0], 0x4000F, &made0, _DbOccpKey(table, 0x61666B67));
        _DbOccpSetColInt(&made0, 0x40010, _DbOccpKey(table, 0x6D666B67), 100);
        aKeys[1] = DBOCCP_KEY(table, 0x70786370);
        _DbOccpSetSubCol(&aTerms[1], 0x4000F, &made1, _DbOccpKey(table, 0x61656B67));
        _DbOccpSetColInt(&made1, 0x40010, _DbOccpKey(table, 0x6D656B67), 100);
        aKeys[2] = -1;
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateExpr(_DbOccp_iDb, aTables, 0, aKeys, aTerms, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

int DbOccpQueryPunting(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    unsigned long long aKeys[3];
    TDbExpr_t aTerms[2];
    TDbExpr_t scale0;
    TDbExpr_t ratio0;
    TDbExpr_t scale1;
    TDbExpr_t ratio1;
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'IKGP'.'aypg' and 'IKGP'.'tapg' and "
                              "'IKGP'.'ynpg' and 'IKGP'.'tppg' and 'IKGP'.'lbpg' and 'IKGP'.'Nlpg' and 'IKGP'.'btpg' and "
                              "'KCCP'.'aucp' and 'KCCP'.'nucp' from 'IKGP' inner join 'YALP' on 'YALP'.'DIGP' = "
                              "'IKGP'.'DIGP' left outer join 'KCCP' on 'KCCP'.'DIGP' = 'YALP'.'DIGP' where "
                              "'IKGP'.'tapg' != 0 and \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        aKeys[0] = DBOCCP_KEY(table, 0x61756370);
        _DbOccpSetTrunc(&aTerms[0], &scale0);
        _DbOccpSetSubFloat(&scale0, 0x40010, &ratio0, 10.0f);
        _DbOccpSetColCol(&ratio0, 0x100018, _DbOccpKey(table, 0x61797067), _DbOccpKey(table, 0x74617067));
        aKeys[1] = DBOCCP_KEY(table, 0x6E756370);
        _DbOccpSetTrunc(&aTerms[1], &scale1);
        _DbOccpSetSubFloat(&scale1, 0x40010, &ratio1, 10.0f);
        _DbOccpSetColCol(&ratio1, 0x100018, _DbOccpKey(table, 0x796E7067), _DbOccpKey(table, 0x74617067));
        aKeys[2] = -1;
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateExpr(_DbOccp_iDb, aTables, 0, aKeys, aTerms, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

int DbOccpQueryReturns(const char *pWhere, int b, unsigned long long orderKey, int orderDir, struct QueryCursor *pCursor)
{
    unsigned long long aKeys[3];
    TDbExpr_t aTerms[2];
    TDbExpr_t scale0;
    TDbExpr_t ratio0;
    TDbExpr_t scale1;
    TDbExpr_t ratio1;
    TDbSQLTableRef_801FDC18 aTables[2];
    int table;
    int err;

    TDbTblFindUnusedId(_DbOccp_iDb, &table);
    err = TDbCompilePerformOp(0,
                              "select into \x8c 'YALP'.'DIGP' and 'YALP'.'DIGT' and 'PKGP'.'ykrg' and 'PKGP'.'akrg' and "
                              "'PKGP'.'yprg' and 'PKGP'.'aprg' and 'PKGP'.'tkrg' and 'PKGP'.'tprg' and 'PKGP'.'Lprg' and "
                              "'PKGP'.'Lkrg' and 'RCCP'.'akcp' and 'RCCP'.'apcp' from 'PKGP' inner join 'YALP' on "
                              "'YALP'.'DIGP' = 'PKGP'.'DIGP' left outer join 'RCCP' on 'RCCP'.'DIGP' = 'YALP'.'DIGP' "
                              "where \x8f\n",
                              table, pWhere);
    if (_DbOccpAccepted(err)) {
        aKeys[0] = DBOCCP_KEY(table, 0x616B6370);
        _DbOccpSetTrunc(&aTerms[0], &scale0);
        _DbOccpSetSubFloat(&scale0, 0x40010, &ratio0, 10.0f);
        _DbOccpSetColCol(&ratio0, 0x100018, _DbOccpKey(table, 0x796B7267), _DbOccpKey(table, 0x616B7267));
        aKeys[1] = DBOCCP_KEY(table, 0x61706370);
        _DbOccpSetTrunc(&aTerms[1], &scale1);
        _DbOccpSetSubFloat(&scale1, 0x40010, &ratio1, 10.0f);
        _DbOccpSetColCol(&ratio1, 0x100018, _DbOccpKey(table, 0x79707267), _DbOccpKey(table, 0x61707267));
        aKeys[2] = -1;
        _DbOccpSetTable(&aTables[0], table, 2, 0);
        _DbOccpSetTable(&aTables[1], -1, 2, 0);
        err = TDbQryUpdateExpr(_DbOccp_iDb, aTables, 0, aKeys, aTerms, 0, 0);
        if (_DbOccpAccepted(err)) {
            err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by \x8c.\x8c \x8e\n",
                                      pCursor, table, (int)(orderKey >> 32), (int)orderKey, orderDir);
            if (_DbOccpAccepted(err)) {
                /* FAKEMATCH: empty accepted test after the last query, only for the target's trailing mr. r3,r3 (a plain return drops it) */
            }
        }
    }
    return err;
}

/* Discarded: recomputes the stored passer rating of every row of a statistics table. */
static int _DbOccpUpdatePasserRatings(int tbl, int colAtt, int colYds, int colComp, int colTd, int colInts)
{
    struct QueryCursor cursor;
    int id;
    int att;
    int yds;
    int comp;
    int td;
    int ints;
    float rating;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c\n", &cursor, tbl);
    if (_DbOccpAccepted(err)) {
        err = TDbCompilePerformOp(0,
                                  "fetch from \x8a 'DIGP' into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into "
                                  "\x82 and \x8c into \x82 and \x8c into \x82\n",
                                  &cursor, &id, colAtt, &att, colYds, &yds, colComp, &comp, colTd, &td, colInts, &ints);
        while (err == 0) {
            rating = 0.0f;
            if (att != 0) {
                rating = DbOccpPasserRating(att, yds, comp, td, ints) * 10.0f;
            }
            err = TDbCompilePerformOp(0, "update \x8c set 'rpcp' = \x82 where 'DIGP' = \x82\n", tbl, (int)rating,
                                      id);
            if (err != 0) {
                break;
            }
            err = TDbCompilePerformOp(0,
                                      "fetch from \x8a 'DIGP' into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c "
                                      "into \x82 and \x8c into \x82 and \x8c into \x82\n",
                                      &cursor, &id, colAtt, &att, colYds, &yds, colComp, &comp, colTd, &td, colInts,
                                      &ints);
        }
        if (cursor.mUnknown0 != 0) {
            TDbSQLDestroyCursor(&cursor);
        }
    }
    return err;
}

float DbOccpPasserRating(int att, int yds, int comp, int td, int ints)
{
    float rating = 0.0f;
    float a;
    float b;
    float c;
    float d;

    if (att != 0) {
        rating = (float)comp / (float)att * 5.0f - 1.5f;
        rating = rating < 0.0f ? 0.0f : (rating > 2.375f ? 2.375f : rating);
        b = ((float)yds / (float)att - 3.0f) * 0.25f;
        rating += b < 0.0f ? 0.0f : (b > 2.375f ? 2.375f : b);
        c = (float)td / (float)att * 19.958f;
        rating += c < 0.0f ? 0.0f : (c > 2.375f ? 2.375f : c);
        d = 2.375f - (float)ints / (float)att * 25.0f;
        rating += d < 0.0f ? 0.0f : d;
        rating = floorf((rating * 16.666668f + 0.05) * 10.0) * 0.1f + 0.005;
    }
    return rating;
}

DbOccpQueryFunc gDbOccpQueries[9] = {
    DbOccpQueryPassing, DbOccpQueryRushing, DbOccpQueryReceiving, (DbOccpQueryFunc)DbOccpQueryNone, DbOccpQueryBlocking,
    DbOccpQueryDefense, DbOccpQueryKicking, DbOccpQueryPunting, DbOccpQueryReturns,
};
