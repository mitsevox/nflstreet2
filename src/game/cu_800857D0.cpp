#include "game/fn_801FCE10.h"
#include "game/fn_8003B6BC.h"

struct Result_8008593C {
    short mUnknown0;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknown12[4];
};

extern "C" {
int fn_80168ED0(int a);
void fn_800850E8(void);
void fn_80085118(void);
int fn_80085148(int *pFirst, int *pSecond);
int fn_800853A0(int formation, int team, int *pKeys, int *pValues);
int fn_800855C8(int a);
int fn_80085620(int index, int a);
int *fn_80085744(int formation, int team);
int fn_8022D8F8(int a, int *pValues, int tag);
int fn_80085BE4(int team);

int fn_800857D0(int formation, int team)
{
    return fn_801FCE10(0, "use 'EMAG' delete from 'ULMF' where ( 'NMRF' = \x85 and 'DIGT' = \x82 )\n", formation, team) == 0;
}

int fn_80085810(int formation, int team, int *pValues)
{
    fn_800857D0(formation, team);
    return fn_801FCE10(0, "use 'EMAG' insert into 'ULMF' set 'NMRF' = \x85 and 'DIGT' = \x82 and 'ZBQF' = \x85 and 'ZBRF' = \x85 and 'FRWF' = \x85 and 'BRWF' = \x85 and 'LLOF' = \x85 and 'CLOF' = \x85 and 'RLOF' = \x85 and 'LLDF' = \x85 and 'RLDF' = \x85 and 'FBLF' = \x85 and 'BBLF' = \x85 and 'LBDF' = \x85 and 'CBDF' = \x85 and 'RBDF' = \x85\n", formation, team,
                      pValues[0], pValues[1], pValues[2], pValues[3],
                      pValues[4], pValues[5], pValues[6], pValues[7],
                      pValues[8], pValues[9], pValues[10], pValues[11],
                      pValues[12], pValues[13]) == 0;
}

int fn_800858C8(int formation, int team, int first, int second)
{
    int result = 0;
    int *pValues = fn_80085744(formation, team);
    if (pValues) {
        int value = pValues[first];
        pValues[first] = pValues[second];
        pValues[second] = value;
        result = fn_80085810(formation, team, pValues);
    }
    return result;
}

extern const char lbl_802942A4[] = "use 'EMAG' select 'ZBQF' into \x85 and 'ZBRF' into \x85 and 'FRWF' into \x85 and 'BRWF' into \x85 and 'LLOF' into \x85 and 'CLOF' into \x85 and 'RLOF' into \x85 and 'LLDF' into \x85 and 'RLDF' into \x85 and 'FBLF' into \x85 and 'BBLF' into \x85 and 'LBDF' into \x85 and 'CBDF' into \x85 and 'RBDF' into \x85 from 'ULMF' where 'DIGT' = \x82 and 'NMRF' = \x85\n";

#if defined(DECOMP_COMPARE)
/* Continue fetching after a failed swap, without attempting further swaps. */
int fn_8008593C(int a, int team, int first, int second)
{
    Result_8008593C result;
    QueryCursor cursor;
    int formation;
    int mode = fn_80168ED0(a);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'OFLP' into \x85 from 'ILMF' where 'FOSI' = \x83 and 'DIBP' = \x85 order by 'OFLP' asc\n", &cursor, &formation, a, mode);
    int success = 1;
    int status = 0;
    for (int index = 0; status == 0; index++) {
        cursor.mUnknown4 = index;
        status = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        if (status == 0) {
            success = success && fn_800858C8(formation, team, first, second);
        }
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    return success;
}

int fn_80085A34(int formation, int team)
{
    int *pValues = fn_80085744(formation, team);
    if (pValues) fn_8022D8F8(team, pValues, 0x41474344);
    return 1;
}

void fn_80085A7C(void)
{
    fn_80085118();
    fn_800850E8();
}

void fn_80085AA0(int firstTeam, Record_8003B6BC *pFirst, int secondTeam,
                Record_8003B6BC *pSecond)
{
    Record_8003B6BC first;
    Record_8003B6BC second;
    for (int i = 0; i < 14; i++) {
        first.mUnknown[i] = pFirst->mUnknown[i];
        second.mUnknown[i] = pSecond->mUnknown[i];
    }
    if (fn_80085148(first.mUnknown, second.mUnknown)) {
        fn_800850E8();
        fn_80085BE4(firstTeam);
        fn_80085BE4(secondTeam);
        fn_80085118();
        int count = fn_800855C8(1);
        for (int i = 0; i < count; i++) {
            int formation = fn_80085620(i, 1);
            fn_800853A0(formation, firstTeam, pFirst->mUnknown, first.mUnknown);
            fn_800853A0(formation, secondTeam, pSecond->mUnknown, second.mUnknown);
        }
        count = fn_800855C8(0);
        for (int i = 0; i < count; i++) {
            int formation = fn_80085620(i, 0);
            fn_800853A0(formation, firstTeam, pFirst->mUnknown, first.mUnknown);
            fn_800853A0(formation, secondTeam, pSecond->mUnknown, second.mUnknown);
        }
    }
    fn_800850E8();
}

int fn_80085BE4(int team)
{
    fn_801FCE10(0, "use 'EMAG' delete from 'BLMF' where ( 'DIGT' = \x85 )\n", team);
    return fn_801FCE10(0, "use 'EMAG' insert into 'BLMF' * select * from 'ULMF' where ( 'DIGT' = \x85 )\n", team);
}

int fn_80085C3C(int team)
{
    fn_801FCE10(0, "use 'EMAG' delete from 'ULMF' where ( 'DIGT' = \x85 )\n", team);
    return fn_801FCE10(0, "use 'EMAG' insert into 'ULMF' * select * from 'BLMF' where ( 'DIGT' = \x85 )\n", team);
}

int fn_80085C94(int team, int *pValues)
{
    fn_801FCE10(0, "use 'EMAG' delete from 'ULMF' where ( 'DIGT' = \x85 )\n", team);
    int count = fn_800855C8(0);
    for (int i = 0; i < count; i++) {
        fn_80085810(fn_80085620(i, 0), team, pValues);
    }
    count = fn_800855C8(1);
    for (int i = 0; i < count; i++) {
        fn_80085810(fn_80085620(i, 1), team, pValues);
    }
    return 1;
}

int fn_80085D54(void)
{
    fn_80085118();
    fn_800850E8();
    return 1;
}
#endif
}
