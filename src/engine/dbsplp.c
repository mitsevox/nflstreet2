/* The three position tables of the game database: when the database modules start, every row
   of 'SPLP' (keyed by 'SOPP', 21 entries), 'SPRD' (keyed by 'PRDP', 17 entries) and 'GSOP'
   (keyed by 'RGPP', 10 entries) is read into a fixed table of the same shape; when they stop,
   every entry goes back to its default {31, 31, 7, 0, ...}. */

#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

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

static Record_8022A304 lbl_802FA180[21] = {
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
};

static Record_8022A304 lbl_802FA378[17] = {
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
    {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7}, {31, 15, 7},
};

static Record_8022A304 lbl_802FA510[10] = {
    {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7},
    {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7}, {31, 31, 7},
};

int fn_80229E88(void)
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

    cursor.mUnknown0 = err;
    cursor.mUnknown4 = err;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'SPLP'\n", &cursor);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a 'SOPP' into \x82 and 'PRDP' into \x82 and 'RGPP' into \x82 and 'IROP' into \x82 and 'MIPP' into \x80 and 'RIPP' into \x80 and 'AIPP' into \x80 and 'FDPP' into \x81 and 'GSPP' into \x81 and 'SPPP' into \x81\n",
                                  &cursor, &index, &a0, &a1, &a2, &b0, &b1, &b2, &h0, &h1, &h2);
        if (err == 0 && index <= 20) {
            lbl_802FA180[index].mUnknown0 = a0;
            lbl_802FA180[index].mUnknown4 = a1;
            lbl_802FA180[index].mUnknown8 = a2;
            lbl_802FA180[index].mUnknownC = b0;
            lbl_802FA180[index].mUnknownD = b1;
            lbl_802FA180[index].mUnknownE = b2;
            lbl_802FA180[index].mUnknown10 = h0;
            lbl_802FA180[index].mUnknown12 = h1;
            lbl_802FA180[index].mUnknown14 = h2;
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
                lbl_802FA378[index].mUnknown0 = a0;
                lbl_802FA378[index].mUnknown4 = a1;
                lbl_802FA378[index].mUnknown8 = a2;
                lbl_802FA378[index].mUnknownC = b0;
                lbl_802FA378[index].mUnknownD = b1;
                lbl_802FA378[index].mUnknownE = b2;
                lbl_802FA378[index].mUnknown10 = h0;
                lbl_802FA378[index].mUnknown12 = h1;
                lbl_802FA378[index].mUnknown14 = h2;
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
                lbl_802FA510[index].mUnknown0 = a0;
                lbl_802FA510[index].mUnknown4 = a1;
                lbl_802FA510[index].mUnknown8 = a2;
                lbl_802FA510[index].mUnknownC = b0;
                lbl_802FA510[index].mUnknownD = b1;
                lbl_802FA510[index].mUnknownE = b2;
                lbl_802FA510[index].mUnknown10 = h0;
                lbl_802FA510[index].mUnknown12 = h1;
                lbl_802FA510[index].mUnknown14 = h2;
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
