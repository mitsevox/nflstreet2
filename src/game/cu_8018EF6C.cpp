#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
int fn_80237390(int stream, int low, int high);

/* Rebuilds 'LTSS' from 'CTNR' in a shuffled order, with the rows of the
   team's own league moved to the end. */
void fn_8018EF6C(int team)
{
    QueryCursor cursor;
    char name[40];
    int count = 0;
    int league = 9;
    int lglt;

    fn_8022EF8C(0, 0x43544E52);
    fn_801FCE10(0, "select count(*) into \x82 from 'CTNR'\n", &count);
    int *pOrder = (int *)fn_801D2B7C(count * 4, 0, 0);
    for (int i = 0; i < count; i++) pOrder[i] = i;
    for (int i = 0; i < count * 8; i++) {
        int a = fn_80237390(1, 0, count - 1);
        int b = fn_80237390(1, 0, count - 1);
        int temp = pOrder[a];
        pOrder[a] = pOrder[b];
        pOrder[b] = temp;
    }

    int handle = fn_8022F3D4(fn_8022F4BC());
    fn_801FCE10(0, "use \x8c select 'LGLT' into \x82 from 'METS' where 'DIGT' = \x82\n", handle, &league, team);
    int last = count - 1;
    for (int i = 0; i < count && last >= 0; i++) {
        if (pOrder[i] == league) {
            int temp = pOrder[last];
            pOrder[last] = pOrder[i];
            pOrder[i] = temp;
            last--;
        }
    }

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(0, "declare \x8a cursor for select * from 'CTNR'\n", &cursor);
    fn_801FCE10(0, "use \x8c delete from 'LTSS'\n", handle);
    for (int i = 0; i < count; i++) {
        cursor.mUnknown4 = pOrder[i];
        fn_801FCE10(0, "fetch from \x8a 'LGLT' into \x82 and 'ETNR' into \x88\n", &cursor, &lglt, name);
        fn_801FCE10(0, "use \x8c insert into 'LTSS' set 'LGLT' = \x82 and 'ETNR' = \x88\n", handle, lglt, name);
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    fn_801D2BD0(pOrder);
    fn_8022EFBC(0, 0x43544E52);
}
}
