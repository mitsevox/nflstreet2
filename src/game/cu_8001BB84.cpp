#include "game/FELoop.h"
#include "game/cu_80181330.h"
#include "game/fn_801FCE10.h"

extern "C" {
void fn_8000FCD4(int a);
void fn_801485B4(void);
void fn_801485C0(void);
void fn_801485EC(int value);
int fn_801801B4(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
}

static unsigned char lbl_803EBA48 = 0;
static int lbl_803EBA4C = 15;
static int lbl_803EBA50 = 15;

extern "C" {
void fn_8001BB84(int *pCount, int *pValue)
{
    if (lbl_803EBA48 == 0) {
        if (fn_8022EF8C(0, 0x5444474D) == 0) {
            *pCount = 6;
            fn_801FCE10(0, "select count(*) into \x82 from 'TDGM'\n", pCount);
        }
        if (lbl_803EBA50 != 15) {
            *pValue = lbl_803EBA50;
        } else {
            *pValue = 0;
        }
        lbl_803EBA4C = 15;
        lbl_803EBA48 = 1;
        fn_80027EA0();
        if (fn_801801B4() == 0) {
            fn_801485C0();
        }
        fn_801485B4();
    }
}

void fn_8001BC34(void)
{
    if (lbl_803EBA48 != 0) {
        fn_8022EFBC(0, 0x5444474D);
        if (lbl_803EBA4C >= 0 && lbl_803EBA4C <= 5) {
            fn_801485EC(lbl_803EBA4C);
            lbl_803EBA50 = lbl_803EBA4C;
        } else {
            fn_801485C0();
            lbl_803EBA50 = 15;
        }
        lbl_803EBA48 = 0;
    }
}

void fn_8001BC98(int id, char *pDest, int count)
{
    char name[32];

    if (fn_801FCE10(0, "select 'NMIU' into \x88 from 'TDGM' where 'DIGM' = \x82\n", name, id) != 0) {
        name[0] = '?';
        name[1] = 0;
    }
    fn_801C2EF0(pDest, name, count);
}

void fn_8001BD08(int id, int *pValue, char *pDest, int count)
{
    char name[208];

    if (fn_801FCE10(0, "select 'DMIU' into \x88 and 'PMIU' into \x82 from 'TDGM' where 'DIGM' = \x82\n", name,
                    pValue, id) != 0) {
        name[0] = '?';
        name[1] = 0;
    }
    fn_801C2EF0(pDest, name, count);
}

int fn_8001BD7C(int value)
{
    lbl_803EBA4C = value;
    return value;
}

int fn_8001BD88(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8001BB84(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000002:
        fn_8001BC34();
        break;
    case 0x80000003:
        fn_8001BC98(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x80000004:
        fn_8001BD08(pArgs[0].i, pArgs[1].pi, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        break;
    case 0x80000005:
        *pResult = fn_8001BD7C(pArgs[0].i);
        fn_8000FCD4(pArgs[1].i);
        break;
    default:
        return 0;
    }
    return 1;
}
}
