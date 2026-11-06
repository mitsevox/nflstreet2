/* Experience levels: opens the level table and answers which level a points total reaches,
   the points a level needs, and a level's name and other values. */

#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
void fn_800731D0(int a);
char *fn_801C2EF0(char *pDst, const char *pSrc, int size);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
}

static unsigned char _ExpLevel_bOpen = 0;

extern "C" {
int ExpLevelQueryForPoints(int ppxe)
{
    QueryCursor cursor;
    int value;
    int found = 0;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0,
                    "declare \x8a fastcursor for select 'VLXE' into \x85 from 'LPXE' where 'PPXE' <= \x82 "
                    "order by 'PPXE' desc\n",
                    &cursor, &value, ppxe) == 0) {
        result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
            found = value;
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return found;
}

int SelectLpxePpxe(int vlxe)
{
    int value;
    int found = -1;
    int result = fn_801FCE10(0, "select 'PPXE' into \x82 from 'LPXE' where 'VLXE' = \x85\n", &value, vlxe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        found = value;
    }
    return found;
}

int ExpLevelQueryScft(int vlxe)
{
    int value;
    int found = 0;
    int result = fn_801FCE10(0, "select 'TFCS' into \x82 from 'LPXE' where 'VLXE' = \x85\n", &value, vlxe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        found = value;
    }
    return found;
}

int ExpLevelQueryLvbn(int vlxe)
{
    int value;
    int found = 0;
    int result = fn_801FCE10(0, "select 'NBVL' into \x82 from 'LPXE' where 'VLXE' = \x85\n", &value, vlxe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        found = value;
    }
    return found;
}

int ExpLevelQueryName(int vlxe, char *pName, int size)
{
    char name[33];
    int found = 0;
    int result = fn_801FCE10(0, "select 'NLXE' into \x88 from 'LPXE' where 'VLXE' = \x85\n", name, vlxe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        fn_801C2EF0(pName, name, size);
        found = 1;
    }
    return found;
}

int ExpLevelCloseTable(void)
{
    int ok = 1;

    if (_ExpLevel_bOpen) {
        ok = fn_8022EFBC(0, 0x4C505845) == 0;
        _ExpLevel_bOpen = 0;
    }
    return ok;
}

int ExpLevelOpenTable(void)
{
    int ok = 1;
    int failed;

    if (!_ExpLevel_bOpen) {
        fn_800731D0(1);
        fn_800731D0(0);
        failed = fn_8022EF8C(0, 0x4C505845);
        fn_800731D0(1);
        fn_800731D0(0);
        if (failed) {
            _ExpLevel_bOpen = 0;
            ok = 0;
        } else {
            _ExpLevel_bOpen = ok;
        }
    }
    return ok;
}

int ExpLevelGetForPoints(int ppxe)
{
    int result;

    if (!_ExpLevel_bOpen) {
        result = 0;
    } else {
        result = ExpLevelQueryForPoints(ppxe);
    }
    return result;
}

int ExpLevelGetScft(int vlxe)
{
    int result;

    if (!_ExpLevel_bOpen) {
        result = 0;
    } else {
        result = ExpLevelQueryScft(vlxe);
    }
    return result;
}

int ExpLevelGetLvbn(int vlxe)
{
    int result;

    if (!_ExpLevel_bOpen) {
        result = 0;
    } else {
        result = ExpLevelQueryLvbn(vlxe);
    }
    return result;
}

int ExpLevelGetName(int vlxe, char *pName, int size)
{
    int result;

    if (!_ExpLevel_bOpen) {
        pName[0] = 0;
        result = 0;
    } else {
        result = ExpLevelQueryName(vlxe, pName, size);
    }
    return result;
}

int ExpLevelClose(void)
{
    return ExpLevelCloseTable();
}

int ExpLevelOpen(void)
{
    return ExpLevelOpenTable();
}
}
