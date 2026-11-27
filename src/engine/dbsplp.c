/* The three position tables of the game database: when the database modules start, every row
   of 'SPLP' (keyed by 'SOPP', 21 entries), 'SPRD' (keyed by 'PRDP', 17 entries) and 'GSOP'
   (keyed by 'RGPP', 10 entries) is read into a fixed table of the same shape; when they stop,
   every entry is reset to {31, 31, 7, 0, ...}. */

#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

typedef struct DbSplpEntry_t {
    int mUnknown0;
    int mUnknown4;
    int mIrop;
    unsigned char mMipp;
    unsigned char mRipp;
    unsigned char mAipp;
    char mUnknownF[1];
    unsigned short mFdpp;
    unsigned short mGspp;
    unsigned short mSppp;
    char mUnknown16[2];
} DbSplpEntry_t;

static DbSplpEntry_t _DbSplp_aSplp[21] = {
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
};

static DbSplpEntry_t _DbSplp_aSprd[17] = {
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
};

static DbSplpEntry_t _DbSplp_aGsop[10] = {
    {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7},
    {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7},
};

int DbSplpModuleInit(void)
{
    struct QueryCursor cursor;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned short h0;
    unsigned short h1;
    unsigned short h2;
    unsigned int index;
    int a0;
    int a1;
    int a2;
    int err = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'SPLP'\n", &cursor);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a 'SOPP' into \x82 and 'PRDP' into \x82 and 'RGPP' into \x82 and 'IROP' into \x82 and 'MIPP' into \x80 and 'RIPP' into \x80 and 'AIPP' into \x80 and 'FDPP' into \x81 and 'GSPP' into \x81 and 'SPPP' into \x81\n",
                                  &cursor, &index, &a0, &a1, &a2, &b0, &b1, &b2, &h0, &h1, &h2);
        if (err == 0 && index <= 20) {
            _DbSplp_aSplp[index].mUnknown0 = a0;
            _DbSplp_aSplp[index].mUnknown4 = a1;
            _DbSplp_aSplp[index].mIrop = a2;
            _DbSplp_aSplp[index].mMipp = b0;
            _DbSplp_aSplp[index].mRipp = b1;
            _DbSplp_aSplp[index].mAipp = b2;
            _DbSplp_aSplp[index].mFdpp = h0;
            _DbSplp_aSplp[index].mGspp = h1;
            _DbSplp_aSplp[index].mSppp = h2;
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
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (err == 0) {
        err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'SPRD'\n", &cursor);
        while (err == 0) {
            err = TDbCompilePerformOp(0, "fetch from \x8a 'PRDP' into \x82 and 'SOPP' into \x82 and 'RGPP' into \x82 and 'IROP' into \x82 and 'MIPP' into \x80 and 'RIPP' into \x80 and 'AIPP' into \x80 and 'FDPP' into \x81 and 'GSPP' into \x81 and 'SPPP' into \x81\n",
                                      &cursor, &index, &a0, &a1, &a2, &b0, &b1, &b2, &h0, &h1, &h2);
            if (err == 0 && index <= 16) {
                _DbSplp_aSprd[index].mUnknown0 = a0;
                _DbSplp_aSprd[index].mUnknown4 = a1;
                _DbSplp_aSprd[index].mIrop = a2;
                _DbSplp_aSprd[index].mMipp = b0;
                _DbSplp_aSprd[index].mRipp = b1;
                _DbSplp_aSprd[index].mAipp = b2;
                _DbSplp_aSprd[index].mFdpp = h0;
                _DbSplp_aSprd[index].mGspp = h1;
                _DbSplp_aSprd[index].mSppp = h2;
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
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (err == 0) {
        err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'GSOP'\n", &cursor);
        while (err == 0) {
            err = TDbCompilePerformOp(0, "fetch from \x8a 'RGPP' into \x82 and 'SOPP' into \x82 and 'PRDP' into \x82 and 'IROP' into \x82 and 'MIPP' into \x80 and 'RIPP' into \x80 and 'AIPP' into \x80 and 'FDPP' into \x81 and 'GSPP' into \x81 and 'SPPP' into \x81\n",
                                      &cursor, &index, &a0, &a1, &a2, &b0, &b1, &b2, &h0, &h1, &h2);
            if (err == 0 && index <= 9) {
                _DbSplp_aGsop[index].mUnknown0 = a0;
                _DbSplp_aGsop[index].mUnknown4 = a1;
                _DbSplp_aGsop[index].mIrop = a2;
                _DbSplp_aGsop[index].mMipp = b0;
                _DbSplp_aGsop[index].mRipp = b1;
                _DbSplp_aGsop[index].mAipp = b2;
                _DbSplp_aGsop[index].mFdpp = h0;
                _DbSplp_aGsop[index].mGspp = h1;
                _DbSplp_aGsop[index].mSppp = h2;
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
    return err;
}

void DbSplpModuleShutdown(void)
{
    unsigned short i;

    for (i = 0; i < 21; i++) {
        _DbSplp_aSplp[i].mUnknown0 = 31;
        _DbSplp_aSplp[i].mUnknown4 = 31;
        _DbSplp_aSplp[i].mIrop = 7;
        _DbSplp_aSplp[i].mMipp = 0;
        _DbSplp_aSplp[i].mRipp = 0;
        _DbSplp_aSplp[i].mAipp = 0;
        _DbSplp_aSplp[i].mFdpp = 0;
        _DbSplp_aSplp[i].mGspp = 0;
        _DbSplp_aSplp[i].mSppp = 0;
    }
    for (i = 0; i < 17; i++) {
        _DbSplp_aSprd[i].mUnknown0 = 31;
        _DbSplp_aSprd[i].mUnknown4 = 31;
        _DbSplp_aSprd[i].mIrop = 7;
        _DbSplp_aSprd[i].mMipp = 0;
        _DbSplp_aSprd[i].mRipp = 0;
        _DbSplp_aSprd[i].mAipp = 0;
        _DbSplp_aSprd[i].mFdpp = 0;
        _DbSplp_aSprd[i].mGspp = 0;
        _DbSplp_aSprd[i].mSppp = 0;
    }
    for (i = 0; i < 10; i++) {
        _DbSplp_aGsop[i].mUnknown0 = 31;
        _DbSplp_aGsop[i].mUnknown4 = 31;
        _DbSplp_aGsop[i].mIrop = 7;
        _DbSplp_aGsop[i].mMipp = 0;
        _DbSplp_aGsop[i].mRipp = 0;
        _DbSplp_aGsop[i].mAipp = 0;
        _DbSplp_aGsop[i].mFdpp = 0;
        _DbSplp_aGsop[i].mGspp = 0;
        _DbSplp_aGsop[i].mSppp = 0;
    }
}
