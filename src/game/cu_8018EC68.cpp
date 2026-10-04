#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

#include "game/cu_8018EC68.h"

#include <string.h>

extern "C" {
void fn_800731D0(int a);
char *fn_801C310C(char *pText, const char *pPattern);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
}

static unsigned char sVetsOpen = 0;

extern "C" {
#if defined(DECOMP_COMPARE)
int fn_8018EA3C(void)
{
    int count;
    int total = 0;
    int result = fn_801FCE10(0, "select count(*) into \x85 from 'VETS'\n", &count);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        total = count;
    }
    return total;
}

int fn_8018EAAC(int dive)
{
    int count;
    int total = 0;
    int result = fn_801FCE10(0, "select count(*) into \x85 from 'VETS' where 'DIVE' = \x85\n", &count, dive);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        total = count;
    }
    return total;
}

int fn_8018EB20(unsigned int index, int *pLglt, char *pEtnr, int size)
{
    QueryCursor cursor;
    int count;
    int lglt;
    int found = 0;
    int handle = fn_8022F3D4(fn_8022F4BC());
    char etnr[33] = {0};

    fn_801FCE10(0, "use \x8c select count(*) into \x82 from 'LTSS'\n", handle, &count);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(0, "use \x8c declare \x8a cursor for select * from 'LTSS'\n", handle, &cursor);
    if (count > 0) {
        cursor.mUnknown4 = index % count;
    } else {
        cursor.mUnknown4 = index;
    }
    fn_801FCE10(0, "use \x8c fetch from \x8a 'LGLT' into \x82 and 'ETNR' into \x88\n", handle, &cursor, &lglt, etnr);
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    if (strlen(etnr)) {
        if (pLglt) {
            *pLglt = lglt;
        }
        if (pEtnr) {
            strncpy(pEtnr, etnr, size);
        }
        found = 1;
    }
    return found;
}
#else
int fn_8018EA3C(void);
int fn_8018EAAC(int dive);
int fn_8018EB20(unsigned int index, int *pLglt, char *pEtnr, int size);
#endif

int fn_8018EC68(int nets, VetsRow_8018EC68 *pRow)
{
    unsigned char dive;
    unsigned char ites;
    char *pTag;
    int found = 0;
    int result = fn_801FCE10(0,
                             "select 'DIVE' into \x83 and 'ITES' into \x83 and 'DROE' into \x83 and '0PES' into "
                             "\x82 and '1PES' into \x82 and '2PES' into \x82 and '3PES' into \x82 and 'CSIS' into "
                             "\x80 and 'CSOS' into \x80 and 'QRXE' into \x84 and 'PEWR' into \x84 and 'PDWR' into "
                             "\x84 and 'CSWR' into \x84 and 'IUVE' into \x88 from 'VETS' where 'NETS' = \x85\n",
                             &dive, &ites, &pRow->mDroe, &pRow->mPes[0], &pRow->mPes[1], &pRow->mPes[2],
                             &pRow->mPes[3], &pRow->mCsis, &pRow->mCsos, &pRow->mQrxe, &pRow->mPewr,
                             &pRow->mPdwr, &pRow->mCswr, pRow->mIuve, nets);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        pTag = fn_801C310C(pRow->mIuve, "<T>");
        if (pTag) {
            fn_8018EB20(nets, 0, pTag, sizeof(pRow->mIuve) - 1 - (pTag - pRow->mIuve));
        }
        pRow->mDive = dive;
        pRow->mItes = ites;
        pRow->mNets = nets;
        found = 1;
    }
    return found;
}

int SelectTopVetsNets(void)
{
    QueryCursor cursor;
    int value;
    int found = 0;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "declare \x8a fastcursor for select 'NETS' into \x85 from 'VETS' order by 'NETS' desc\n",
                    &cursor, &value) == 0) {
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

int fn_8018ED78(int dive, int droe)
{
    unsigned char nets;
    int found = 0;
    int result = fn_801FCE10(0, "select 'NETS' into \x83 from 'VETS' where 'DIVE' = \x83 and 'DROE' = \x85\n", &nets,
                             (unsigned char)dive, droe);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        found = nets;
    }
    return found;
}

int fn_8018EDF0(int dive, int droe, VetsRow_8018EC68 *pRow)
{
    int found = 0;
    int nets;

    if (sVetsOpen) {
        nets = fn_8018ED78(dive, droe);
        if (nets) {
            found = fn_8018EC68(nets, pRow);
        }
    }
    return found;
}

int fn_8018EE44(int dive)
{
    int result;

    if (!sVetsOpen) {
        result = 0;
    } else {
        result = fn_8018EAAC(dive);
    }
    return result;
}

int fn_8018EE78(void)
{
    int result;

    if (!sVetsOpen) {
        result = 0;
    } else {
        result = fn_8018EA3C();
    }
    return result;
}

int fn_8018EEAC(void)
{
    if (sVetsOpen) {
        fn_8022EFBC(0, 0x56455453);
        sVetsOpen = 0;
    }
    return 1;
}

int fn_8018EEF0(void)
{
    int ok = 1;
    int failed;

    fn_800731D0(1);
    fn_800731D0(0);
    failed = fn_8022EF8C(0, 0x56455453);
    fn_800731D0(1);
    fn_800731D0(0);
    if (failed == 0) {
        sVetsOpen = ok;
    } else {
        sVetsOpen = 0;
        ok = 0;
    }
    return ok;
}
}
