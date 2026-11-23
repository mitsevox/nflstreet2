/* The game database's 'OCMT' table: inserts and deletes rows, keeps their 'olsl' order
   numbers consecutive and clears the table; start/stop stubs of its module; and the
   'LRTC' table that records which user owns a controller slot. */

#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

int DbOcmtRenumber(void)
{
    struct QueryCursor cursor;
    int a;
    int b;
    int c;
    unsigned char i;
    int err = 0;

    i = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'OCMT' order by 'olsl' asc\n", &cursor);
    if (err == 0) {
        do {
            err = TDbCompilePerformOp(0, "fetch from \x8a 'UNLS' into \x82 and 'digl' into \x82 and 'olsl' into \x82\n",
                                      &cursor, &a, &b, &c);
            if (err != 0) {
                break;
            }
            if (c != i) {
                err = TDbCompilePerformOp(0, "update 'OCMT' set 'olsl' = \x83 where ('UNLS' = \x82) and ('digl' = \x82)\n",
                                          i, a, b);
            }
            i++;
        } while (err == 0);
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

int DbOcmtModuleInit(void)
{
    return 0;
}

void DbOcmtModuleShutdown(void)
{
}

int DbOcmtInsert(int a, int b)
{
    int err = TDbCompilePerformOp(0, "insert into 'OCMT' set 'UNLS' = \x82 and 'digl' = \x82 and 'olsl' = \x82\n", a, b, 255);

    if (err == 0) {
        err = DbOcmtRenumber();
    }
    return err;
}

int DbOcmtDelete(int digl)
{
    int err = TDbCompilePerformOp(0, "delete from 'OCMT' where ('digl' = \x82)\n", digl);

    if (err == 0) {
        err = DbOcmtRenumber();
    }
    return err;
}

int DbOcmtClear(void)
{
    return TDbCompilePerformOp(0, "delete from 'OCMT'\n");
}

int DbLrtcSetUser(int digl, int user)
{
    unsigned short count;
    int err = TDbCompilePerformOp(0, "select count(*) into \x81 from 'LRTC' where ('digl' = \x82)\n", &count, digl);

    if (err == 0) {
        if (count != 0) {
            err = TDbCompilePerformOp(0, "update 'LRTC' set 'DIGU' = \x82 where ('digl' = \x82)\n", user, digl);
        } else {
            err = TDbCompilePerformOp(0, "insert into 'LRTC' set 'digl' = \x82 and 'DIGU' = \x82\n", digl, user);
        }
    }
    return err;
}

int DbLrtcClearUser(int digl)
{
    return TDbCompilePerformOp(0, "update 'LRTC' set 'DIGU' = \x82 where ('digl' = \x82)\n", -1, digl);
}
