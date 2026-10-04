#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
void fn_800731D0(int a);
char *fn_801C2EF0(char *pDst, const char *pSrc, int size);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
}

static unsigned char sLpxeOpen = 0;

extern "C" {
int fn_80085D7C(int ppxe)
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

int fn_80085E3C(int vlxe)
{
    int value;
    int found = 0;
    int result = fn_801FCE10(0, "select 'TFCS' into \x82 from 'LPXE' where 'VLXE' = \x85\n", &value, vlxe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        found = value;
    }
    return found;
}

int fn_80085EB0(int vlxe)
{
    int value;
    int found = 0;
    int result = fn_801FCE10(0, "select 'NBVL' into \x82 from 'LPXE' where 'VLXE' = \x85\n", &value, vlxe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        found = value;
    }
    return found;
}

int fn_80085F24(int vlxe, char *pName, int size)
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

int fn_80085FB0(void)
{
    int ok = 1;

    if (sLpxeOpen) {
        ok = fn_8022EFBC(0, 0x4C505845) == 0;
        sLpxeOpen = 0;
    }
    return ok;
}

int fn_80085FFC(void)
{
    int ok = 1;
    int failed;

    if (!sLpxeOpen) {
        fn_800731D0(1);
        fn_800731D0(0);
        failed = fn_8022EF8C(0, 0x4C505845);
        fn_800731D0(1);
        fn_800731D0(0);
        if (failed) {
            sLpxeOpen = 0;
            ok = 0;
        } else {
            sLpxeOpen = ok;
        }
    }
    return ok;
}

int fn_80086080(int ppxe)
{
    int result;

    if (!sLpxeOpen) {
        result = 0;
    } else {
        result = fn_80085D7C(ppxe);
    }
    return result;
}

int fn_800860B4(int vlxe)
{
    int result;

    if (!sLpxeOpen) {
        result = 0;
    } else {
        result = fn_80085E3C(vlxe);
    }
    return result;
}

int fn_800860E8(int vlxe)
{
    int result;

    if (!sLpxeOpen) {
        result = 0;
    } else {
        result = fn_80085EB0(vlxe);
    }
    return result;
}

int fn_8008611C(int vlxe, char *pName, int size)
{
    int result;

    if (!sLpxeOpen) {
        pName[0] = 0;
        result = 0;
    } else {
        result = fn_80085F24(vlxe, pName, size);
    }
    return result;
}

int fn_80086154(void)
{
    return fn_80085FB0();
}

int fn_80086174(void)
{
    return fn_80085FFC();
}
}
