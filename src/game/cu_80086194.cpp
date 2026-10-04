#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F358(int index);
int fn_8022F3D4(int a);
}

static unsigned char sPdfnOpen = 0;
static int sHandle = -1;

extern "C" {
int fn_80086194(int ptfd, int *pList, int max)
{
    QueryCursor cursor;
    int value;
    int count = -1;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "declare \x8a fastcursor for select 'DIGP' into \x85 from 'PDFN' where 'PTFD' = \x85\n",
                    &cursor, &value, ptfd) == 0) {
        result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        count = 0;
        while (cursor.mUnknown0 != 0 && QUERY_STATUS_ACCEPTED(result) == true && result != 0x15) {
            pList[count++] = value;
            if (count >= max) {
                break;
            }
            result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return count;
}

int fn_800862AC(void)
{
    int count;
    int total = -1;
    int result = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LTFN'\n", sHandle, &count);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        total = count;
    }
    return total;
}

int fn_80086320(int lvlt)
{
    int count;
    int total = -1;
    int result = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LTFN' where 'LVLT' = \x82\n", sHandle,
                             &count, lvlt);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        total = count;
    }
    return total;
}

int fn_80086398(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw)
{
    QueryCursor cursor;
    int found = 0;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0,
                    "use \x8c declare \x8a fastcursor for select '1DIT' into \x85 and '2DIT' into \x85 and 'TNIW' "
                    "into \x85 from 'LTFN' where 'LVLT' = \x82\n",
                    sHandle, &cursor, pDit1, pDit2, pTniw, lvlt) == 0) {
        cursor.mUnknown4 = row;
        if (cursor.mUnknown0 != 0) {
            result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            if (QUERY_STATUS_ACCEPTED(result) == true && result != 0x15) {
                found = 1;
            }
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return found;
}

int fn_8008648C(int lvlt, int dit1, int dit2, int tniw)
{
    int success = 0;
    int result = fn_801FCE10(0,
                             "use \x8c update 'LTFN' set 'TNIW' = \x85 where 'LVLT' = \x82 and '1DIT' = \x85 and "
                             "'2DIT' = \x85\n",
                             sHandle, tniw, lvlt, dit1, dit2);

    if (result == 0x17) {
        success = fn_801FCE10(0,
                              "use \x8c insert into 'LTFN' set '1DIT' = \x85 and '2DIT' = \x85 and 'LVLT' = \x82 and "
                              "'TNIW' = \x85\n",
                              sHandle, dit1, dit2, lvlt, tniw) == 0;
    } else if (result == 0) {
        success = 1;
    }
    return success;
}

int DeleteLtfnRow(int lvlt, int dit1, int dit2)
{
    return fn_801FCE10(0,
                       "use \x8c delete from 'LTFN' where 'LVLT' = \x82 and '1DIT' = \x85 and '2DIT' = \x85\n",
                       sHandle, lvlt, dit1, dit2) != 0x17;
}

int fn_80086534(void)
{
    fn_801FCE10(0, "use \x8c delete from 'LTFN'\n", sHandle);
    return 1;
}

int fn_8008656C(int digp, int munt, int digt)
{
    int success = 0;
    int result = fn_801FCE10(0, "use \x8c update 'PTFN' set 'MUNT' = \x85 and 'DIGT' = \x85 where 'DIGP' = \x85\n",
                             sHandle, munt, digt, digp);

    if (result == 0x17) {
        success = fn_801FCE10(0, "use \x8c insert into 'PTFN' set 'DIGP' = \x85 and 'MUNT' = \x85 and 'DIGT' = \x85\n",
                              sHandle, digp, munt, digt) == 0;
    } else if (result == 0) {
        success = 1;
    }
    return success;
}

int SelectPtfnRow(int digp, int *pMunt, int *pDigt)
{
    int result = fn_801FCE10(0,
                             "use \x8c select 'MUNT' into \x85 and 'DIGT' into \x85 from 'PTFN' where 'DIGP' = \x85\n",
                             sHandle, pMunt, pDigt, digp);

    return QUERY_STATUS_ACCEPTED(result) && result != 0x17;
}

int fn_8008660C(int digt, int *pList)
{
    QueryCursor cursor;
    int value;
    int count = -1;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x85 from 'PTFN' where 'DIGT' = \x85\n",
                    sHandle, &cursor, &value, digt) == 0) {
        result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        count = 0;
        while (cursor.mUnknown0 != 0 && QUERY_STATUS_ACCEPTED(result) == true && result != 0x15) {
            pList[count++] = value;
            result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return count;
}

int ListPtfnByMunt(int munt, int *pList)
{
    QueryCursor cursor;
    int value;
    int count = -1;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x85 from 'PTFN' where 'MUNT' = \x85\n",
                    sHandle, &cursor, &value, munt) == 0) {
        result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        count = 0;
        while (cursor.mUnknown0 != 0 && QUERY_STATUS_ACCEPTED(result) == true && result != 0x15) {
            pList[count++] = value;
            result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return count;
}

int fn_8008671C(void)
{
    fn_801FCE10(0, "use \x8c delete from 'PTFN'\n", sHandle);
    return 1;
}

int fn_80086754(int *pList)
{
    QueryCursor cursor;
    int value;
    int count = -1;
    int result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0,
                    "use 'TATS' declare \x8a fastcursor for select 'DIGT' into \x85 from 'MAET' where 'PYTT' = \x85 "
                    "order by 'DROT'\n",
                    &cursor, &value, 2) == 0) {
        result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        count = 0;
        while (cursor.mUnknown0 != 0 && QUERY_STATUS_ACCEPTED(result) == true && result != 0x15) {
            pList[count++] = value;
            if (count >= 8) {
                break;
            }
            result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return count;
}

int fn_80086868(int *pList, int max)
{
    int result;

    if (!sPdfnOpen) {
        result = -1;
    } else {
        result = fn_80086194(1, pList, max);
    }
    return result;
}

int fn_800868A8(int *pList, int max)
{
    int result;

    if (!sPdfnOpen) {
        result = -1;
    } else {
        result = fn_80086194(0, pList, max);
    }
    return result;
}

int fn_800868E8(int *pDigp, int count, int munt, int digt)
{
    int result = 0;
    int i;

    if (sHandle != -1) {
        for (i = 0; i < count; i++) {
            result = fn_8008656C(pDigp[i], munt, digt);
            if (!result) {
                break;
            }
        }
    }
    return result;
}

int fn_80086960(int digt, int *pList)
{
    int result;

    if (sHandle == -1) {
        result = -1;
    } else {
        result = fn_8008660C(digt, pList);
    }
    return result;
}

int fn_80086994(void)
{
    int result;

    if (sHandle == -1) {
        result = 0;
    } else {
        result = fn_8008671C();
    }
    return result;
}

int fn_800869C8(int lvlt)
{
    int result;

    if (sHandle == -1) {
        result = -1;
    } else {
        result = fn_80086320(lvlt);
    }
    return result;
}

int fn_800869FC(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw)
{
    int result;

    if (sHandle == -1) {
        result = 0;
    } else {
        result = fn_80086398(lvlt, row, pDit1, pDit2, pTniw);
    }
    return result;
}

int fn_80086A30(int lvlt, int dit1, int dit2, int tniw)
{
    int result;

    if (sHandle == -1) {
        result = 0;
    } else {
        result = fn_8008648C(lvlt, dit1, dit2, tniw);
    }
    return result;
}

int fn_80086A64(void)
{
    int result;

    if (sHandle == -1) {
        result = 0;
    } else {
        result = fn_80086534();
    }
    return result;
}

int fn_80086A98(void)
{
    int result;

    if (sHandle == -1) {
        result = -1;
    } else {
        result = fn_800862AC();
    }
    return result;
}

int fn_80086ACC(int *pList)
{
    return fn_80086754(pList);
}

int fn_80086AEC(int size)
{
    int shift;

    if (size <= 2) {
        shift = 1;
    } else if (size <= 4) {
        shift = 2;
    } else if (size <= 8) {
        shift = 3;
    } else if (size <= 16) {
        shift = 4;
    } else if (size <= 32) {
        shift = 5;
    } else if (size <= 64) {
        shift = 6;
    } else {
        shift = -1;
    }
    return shift;
}

int fn_80086B50(void)
{
    int result;

    if (!sPdfnOpen) {
        return 1;
    }
    result = fn_8022EFBC(0, 0x5044464E);
    sHandle = -1;
    sPdfnOpen = 0;
    return result == 0;
}

int fn_80086BA4(int index)
{
    int ok = 1;

    sHandle = fn_8022F3D4(fn_8022F358(index));
    if (sHandle == -1) {
        ok = 0;
    }
    if (fn_8022EF8C(0, 0x5044464E) == 0) {
        sPdfnOpen = 1;
    } else {
        sPdfnOpen = 0;
        ok = 0;
    }
    return ok;
}
}
