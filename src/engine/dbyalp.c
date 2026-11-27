/* The player-rating module of the game database ('YALP' players): when the database modules
   start it loads the two weight tables 'CROP' and 'ROBP' (per row two bounds, ten rating
   weights and their sum), turns a player's ten ratings into one overall rating with them, and
   lists unused player ids. */

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

typedef struct DbYalpWeightRow_t {
    float mHigh;
    float mLow;
    float aWeights[10];
    float mWeightSum;
} DbYalpWeightRow_t;

extern DbYalpWeightRow_t lbl_803A1C60[];
extern DbYalpWeightRow_t lbl_803A20A4[];

int DbTatsCopyTblDestroy(int db, int tbl);

int DbYalpModuleInit(void);
int DbYalpModuleShutdown(void);
float DbYalpGetLowRating(int index);
float DbYalpGetHighRating(int index);
float DbYalpGetRatingWeight(int index, int item);
float DbYalpGetWeightSum(int index);
int DbYalpBeginGame(void);
int DbYalpResumeGame(void);

/* Reads every row of the weight table tag into the row array pTable (bounds, ten weights and their sum), then drops the table from the database. */
int DbYalpLoadWeightTable(void *pTable, int tag)
{
    struct QueryCursor cursor;
    float aVals[10];
    int index;
    unsigned int a;
    unsigned int b;
    int err = 0;
    unsigned char i;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c\n", &cursor, tag);
    while (err == 0) {
        err = TDbCompilePerformOp(0,
                                  "fetch from \x8a 'WGAP' into \x86 and 'WESP' into \x86 and 'WWAP' into \x86 and "
                                  "'WACP' into \x86 and 'WTBP' into \x86 and 'WCTP' into \x86 and 'WSPP' into \x86 and "
                                  "'WLBP' into \x86 and 'WVCP' into \x86 and 'WTDP' into \x86 and 'SOPP' into \x82 and "
                                  "'HDRP' into \x82 and 'LDRP' into \x82\n",
                                  &cursor, &aVals[0], &aVals[1], &aVals[2], &aVals[3],
                                  &aVals[4], &aVals[5], &aVals[6], &aVals[7], &aVals[8], &aVals[9],
                                  &index, &a, &b);
        if (err == 0) {
            ((DbYalpWeightRow_t *)pTable)[index].mHigh = a;
            ((DbYalpWeightRow_t *)pTable)[index].mLow = b;
            ((DbYalpWeightRow_t *)pTable)[index].mWeightSum = 0.0f;
            for (i = 0; i < 10; i++) {
                ((DbYalpWeightRow_t *)pTable)[index].aWeights[i] = aVals[i];
                ((DbYalpWeightRow_t *)pTable)[index].mWeightSum += aVals[i];
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
    return MemFill((char *)lbl_803A1C60, 1092, 0, 4);
}

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
    status = TDbCompilePerformOp(0, "use \x8c declare \x8a cursor for select * from \x8c order by 'DIGP' asc\n", db,
                                 &cursor, tbl);
    prev = -1;
    next = -1;
    last = 0x7FFF;
    count = 0;
    while (status == 0 && count < *pCount) {
        status = TDbCompilePerformOp(0, "fetch from \x8a 'DIGP' into \x82\n", &cursor, &id);
        if (status == 0) {
            if (id > prev + 1) {
                next = prev + 1;
                while (status == 0 && next < id) {
                    if (count < *pCount && next <= 0x7F14) {
                        pIds[count] = next;
                        count++;
                        next++;
                    } else {
                        break;
                    }
                }
            }
            if (next > id) {
                last = next;
            } else {
                last = id;
            }
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
        if (last == 0x7FFF) {
            next = 0;
        } else {
            next = last + 1;
        }
        while (count < *pCount) {
            if (next <= 0x7F14) {
                pIds[count] = next;
                count++;
                next++;
            } else {
                break;
            }
        }
    }
    *pCount = count;
    return status;
}

// FAKEMATCH: discarded file-static stand-ins; their literals are the unreferenced
// 0x802B25B8-0x802B2727 queries of the target .rodata
static int _DbYalpInsertPlayer(int id, int origId, int team)
{
    return TDbCompilePerformOp(0, "insert into 'YALP' set 'DIGP' = \x82 and 'DIOP' = \x82 and 'DIGT' = \x82 and\n",
                               id, origId, team);
}

static int _DbYalpDeletePlayer(int id)
{
    return TDbCompilePerformOp(0, "delete from 'YALP' where ('DIGP' = \x82)\n", id);
}

static int _DbYalpSetValue(int col, int value, int id)
{
    return TDbCompilePerformOp(0, "update 'YALP' set \x8c = \x82 where ('DIGP' = \x82)\n", col, value, id);
}

static int _DbYalpSetText(int col, const char *pText, int id)
{
    return TDbCompilePerformOp(0, "update 'YALP' set \x8c = \x88 where ('DIGP' = \x82)\n", col, pText, id);
}

static int _DbYalpMovePlayers(int first, int last, int newFirst, int team)
{
    struct QueryCursor cursor;
    int id;
    int status;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0,
                                 "declare \x8a cursor for select * from 'YALP' where ('DIGP' >= \x82) and "
                                 "('DIGP' <= \x82) order by 'DIGP' asc\n",
                                 &cursor, first, last);
    while (status == 0) {
        status = TDbCompilePerformOp(0, "fetch from \x8a 'DIGP' into \x82\n", &cursor, &id);
        if (status == 0) {
            status = TDbCompilePerformOp(0, "update 'YALP' set 'DIGP' = \x82 and 'DIGT' = \x82 where ('DIGP' = \x82)\n",
                                         id - first + newFirst, team, id);
        }
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return status;
}

// FAKEMATCH: discarded file-static stand-in; its literal pool is the unreferenced
// 0x802B2728-0x802B274F block, laid out like the pool of DbYalpGetOverallRating
static unsigned int _DbYalpGetOverallRatingFrom(DbYalpWeightRow_t *pRow, int *pRatings, int clamp)
{
    float sum = 0.0f;
    float weight;
    int i;

    for (i = 0; i < 10; i++) {
        weight = pRow->aWeights[i];
        if (weight <= 0.0f) {
            continue;
        }
        sum += pRatings[i] * weight;
    }
    sum -= pRow->mLow * pRow->mWeightSum;
    sum /= (pRow->mHigh - pRow->mLow) * pRow->mWeightSum * (1.0f / 99.0f);
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

float DbYalpGetLowRating(int index)
{
    return lbl_803A20A4[index].mLow;
}

float DbYalpGetHighRating(int index)
{
    return lbl_803A20A4[index].mHigh;
}

float DbYalpGetRatingWeight(int index, int item)
{
    return lbl_803A20A4[index].aWeights[item];
}

float DbYalpGetWeightSum(int index)
{
    return lbl_803A20A4[index].mWeightSum;
}

/* Turns a player's ten ratings into one overall rating (0-99 scale) with weight row index; clamp 1 keeps it within 12-100. */
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

// FAKEMATCH: discarded file-static stand-ins; their literals are the unreferenced
// 0x802B2778-0x802B2C9D queries of the target .rodata
static int _DbYalpOpenPlayer(struct QueryCursor *pCursor, int id)
{
    return TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'YALP' where ('DIGP' = \x82)\n", pCursor, id);
}

static int _DbYalpSetTableOverall(int tbl, int overall, int id)
{
    return TDbCompilePerformOp(0, "update \x8c set \x8c.'RVOP' = \x82 where (\x8c.'DIGP' = \x82)\n", tbl, tbl, overall,
                               tbl, id);
}

static int _DbYalpFetchTableRatings(struct QueryCursor *pCursor, int tbl, int *p)
{
    return TDbCompilePerformOp(0,
                               "fetch from \x8a \x8c.'DIGP' into \x82 and \x8c.'SOPP' into \x82 and \x8c.'IGAP' into \x82 and "
                               "\x8c.'DPSP' into \x82 and \x8c.'MUJP' into \x82 and \x8c.'HTCP' into \x82 and \x8c.'KTBP' into "
                               "\x82 and \x8c.'KATP' into \x82 and \x8c.'SSPP' into \x82 and \x8c.'KLBP' into \x82 and "
                               "\x8c.'VOCP' into \x82 and \x8c.'TFDP' into \x82\n",
                               pCursor, tbl, &p[0], tbl, &p[1], tbl, &p[2], tbl, &p[3], tbl, &p[4], tbl, &p[5], tbl,
                               &p[6], tbl, &p[7], tbl, &p[8], tbl, &p[9], tbl, &p[10], tbl, &p[11]);
}

static int _DbYalpFetchRatings(struct QueryCursor *pCursor, int *p)
{
    return TDbCompilePerformOp(0,
                               "fetch from \x8a 'DIGP' into \x82 and 'SOPP' into \x82 and 'IGAP' into \x82 and 'DPSP' into "
                               "\x82 and 'MUJP' into \x82 and 'HTCP' into \x82 and 'KTBP' into \x82 and 'KATP' into \x82 "
                               "and 'SSPP' into \x82 and 'KLBP' into \x82 and 'VOCP' into \x82 and 'TFDP' into \x82\n",
                               pCursor, &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6], &p[7], &p[8], &p[9], &p[10],
                               &p[11]);
}

static int _DbYalpSetRatings(int tbl, int *p, int id)
{
    return TDbCompilePerformOp(0,
                               "update \x8c set 'RVOP' = \x82 and 'IGAP' = \x82 and 'DPSP' = \x82 and 'MUJP' = \x82 and "
                               "'HTCP' = \x82 and 'KTBP' = \x82 and 'KATP' = \x82 and 'SSPP' = \x82 and 'KLBP' = \x82 and "
                               "'VOCP' = \x82 and 'TFDP' = \x82 where ('DIGP' = \x82)\n",
                               tbl, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], id);
}

static int _DbYalpGetTableRatings(int db, int tbl, int *p, int id)
{
    return TDbCompilePerformOp(0,
                               "use \x8c select 'SOPP' into \x82 and 'IGAP' into \x82 and 'DPSP' into \x82 and 'MUJP' into "
                               "\x82 and 'HTCP' into \x82 and 'KTBP' into \x82 and 'KATP' into \x82 and 'SSPP' into \x82 "
                               "and 'KLBP' into \x82 and 'VOCP' into \x82 and 'TFDP' into \x82 from \x8c where ('DIGP' = "
                               "\x82)\n",
                               db, &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6], &p[7], &p[8], &p[9], &p[10], tbl, id);
}

static int _DbYalpGetPlayerInfo(int tbl, int *p, int id)
{
    return TDbCompilePerformOp(0,
                               "select 'SOPP' into \x82 and 'EGAP' into \x82 and COL_PLYR_YEARSPRO into \x82 and 'RVOP' "
                               "into \x82 and 'IGAP' into \x82 and 'DPSP' into \x82 and 'MUJP' into \x82 and 'HTCP' into "
                               "\x82 and 'KTBP' into \x82 and 'KATP' into \x82 and 'SSPP' into \x82 and 'KLBP' into \x82 "
                               "and 'VOCP' into \x82 and 'TFDP' into \x82 from \x8c where ('DIGP' = \x82)\n",
                               &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6], &p[7], &p[8], &p[9], &p[10], &p[11],
                               &p[12], &p[13], tbl, id);
}

int DbYalpBeginGame(void)
{
    return 0;
}

int DbYalpResumeGame(void)
{
    return 0;
}

