/* Tournament data in a profile database: the draft pool, which players were drafted to
   which tournament team, the bracket matches of each round with their winners, and the
   number of rounds for a bracket size. */

#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F358(int index);
int fn_8022F3D4(int a);
}

static unsigned char _Tournament_bDraftPoolOpen = 0;
static int _Tournament_iDbHandle = -1;

extern "C" {
int TournamentDbQueryDraftPool(int ptfd, int *pList, int max)
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

int TournamentDbQueryMatchCount(void)
{
    int count;
    int total = -1;
    int result = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LTFN'\n", _Tournament_iDbHandle, &count);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        total = count;
    }
    return total;
}

int TournamentDbQueryLevelMatchCount(int lvlt)
{
    int count;
    int total = -1;
    int result = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LTFN' where 'LVLT' = \x82\n", _Tournament_iDbHandle,
                             &count, lvlt);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        total = count;
    }
    return total;
}

int TournamentDbQueryMatch(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw)
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
                    _Tournament_iDbHandle, &cursor, pDit1, pDit2, pTniw, lvlt) == 0) {
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

int TournamentDbWriteMatchWinner(int lvlt, int dit1, int dit2, int tniw)
{
    int success = 0;
    int result = fn_801FCE10(0,
                             "use \x8c update 'LTFN' set 'TNIW' = \x85 where 'LVLT' = \x82 and '1DIT' = \x85 and "
                             "'2DIT' = \x85\n",
                             _Tournament_iDbHandle, tniw, lvlt, dit1, dit2);

    if (result == 0x17) {
        success = fn_801FCE10(0,
                              "use \x8c insert into 'LTFN' set '1DIT' = \x85 and '2DIT' = \x85 and 'LVLT' = \x82 and "
                              "'TNIW' = \x85\n",
                              _Tournament_iDbHandle, dit1, dit2, lvlt, tniw) == 0;
    } else if (result == 0) {
        success = 1;
    }
    return success;
}

int DeleteLtfnRow(int lvlt, int dit1, int dit2)
{
    return fn_801FCE10(0,
                       "use \x8c delete from 'LTFN' where 'LVLT' = \x82 and '1DIT' = \x85 and '2DIT' = \x85\n",
                       _Tournament_iDbHandle, lvlt, dit1, dit2) != 0x17;
}

int TournamentDbDeleteAllMatches(void)
{
    fn_801FCE10(0, "use \x8c delete from 'LTFN'\n", _Tournament_iDbHandle);
    return 1;
}

int TournamentDbWritePlayerTeam(int digp, int munt, int digt)
{
    int success = 0;
    int result = fn_801FCE10(0, "use \x8c update 'PTFN' set 'MUNT' = \x85 and 'DIGT' = \x85 where 'DIGP' = \x85\n",
                             _Tournament_iDbHandle, munt, digt, digp);

    if (result == 0x17) {
        success = fn_801FCE10(0, "use \x8c insert into 'PTFN' set 'DIGP' = \x85 and 'MUNT' = \x85 and 'DIGT' = \x85\n",
                              _Tournament_iDbHandle, digp, munt, digt) == 0;
    } else if (result == 0) {
        success = 1;
    }
    return success;
}

int SelectPtfnRow(int digp, int *pMunt, int *pDigt)
{
    int result = fn_801FCE10(0,
                             "use \x8c select 'MUNT' into \x85 and 'DIGT' into \x85 from 'PTFN' where 'DIGP' = \x85\n",
                             _Tournament_iDbHandle, pMunt, pDigt, digp);

    return QUERY_STATUS_ACCEPTED(result) && result != 0x17;
}

int TournamentDbQueryTeamPlayers(int digt, int *pList)
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
                    _Tournament_iDbHandle, &cursor, &value, digt) == 0) {
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
                    _Tournament_iDbHandle, &cursor, &value, munt) == 0) {
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

int TournamentDbDeleteAllPlayers(void)
{
    fn_801FCE10(0, "use \x8c delete from 'PTFN'\n", _Tournament_iDbHandle);
    return 1;
}

int TournamentDbQueryTeamList(int *pList)
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

int TournamentGetDraftPool1(int *pList, int max)
{
    int result;

    if (!_Tournament_bDraftPoolOpen) {
        result = -1;
    } else {
        result = TournamentDbQueryDraftPool(1, pList, max);
    }
    return result;
}

int TournamentGetDraftPool0(int *pList, int max)
{
    int result;

    if (!_Tournament_bDraftPoolOpen) {
        result = -1;
    } else {
        result = TournamentDbQueryDraftPool(0, pList, max);
    }
    return result;
}

int TournamentSetPlayersTeam(int *pDigp, int count, int munt, int digt)
{
    int result = 0;
    int i;

    if (_Tournament_iDbHandle != -1) {
        for (i = 0; i < count; i++) {
            result = TournamentDbWritePlayerTeam(pDigp[i], munt, digt);
            if (!result) {
                break;
            }
        }
    }
    return result;
}

int TournamentGetTeamPlayers(int digt, int *pList)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = -1;
    } else {
        result = TournamentDbQueryTeamPlayers(digt, pList);
    }
    return result;
}

int TournamentClearPlayers(void)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = 0;
    } else {
        result = TournamentDbDeleteAllPlayers();
    }
    return result;
}

int TournamentGetLevelMatchCount(int lvlt)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = -1;
    } else {
        result = TournamentDbQueryLevelMatchCount(lvlt);
    }
    return result;
}

int TournamentGetMatch(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = 0;
    } else {
        result = TournamentDbQueryMatch(lvlt, row, pDit1, pDit2, pTniw);
    }
    return result;
}

int TournamentSetMatchWinner(int lvlt, int dit1, int dit2, int tniw)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = 0;
    } else {
        result = TournamentDbWriteMatchWinner(lvlt, dit1, dit2, tniw);
    }
    return result;
}

int TournamentClearMatches(void)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = 0;
    } else {
        result = TournamentDbDeleteAllMatches();
    }
    return result;
}

int TournamentGetMatchCount(void)
{
    int result;

    if (_Tournament_iDbHandle == -1) {
        result = -1;
    } else {
        result = TournamentDbQueryMatchCount();
    }
    return result;
}

int TournamentGetTeamList(int *pList)
{
    return TournamentDbQueryTeamList(pList);
}

int TournamentGetRoundCount(int size)
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

int TournamentClose(void)
{
    int result;

    if (!_Tournament_bDraftPoolOpen) {
        return 1;
    }
    result = fn_8022EFBC(0, 0x5044464E);
    _Tournament_iDbHandle = -1;
    _Tournament_bDraftPoolOpen = 0;
    return result == 0;
}

int TournamentOpen(int index)
{
    int ok = 1;

    _Tournament_iDbHandle = fn_8022F3D4(fn_8022F358(index));
    if (_Tournament_iDbHandle == -1) {
        ok = 0;
    }
    if (fn_8022EF8C(0, 0x5044464E) == 0) {
        _Tournament_bDraftPoolOpen = 1;
    } else {
        _Tournament_bDraftPoolOpen = 0;
        ok = 0;
    }
    return ok;
}
}
