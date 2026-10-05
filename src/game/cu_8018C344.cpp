#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_8022F3D4(int handle);
int fn_801F9980(int handle, int *pTable);
int fn_801F967C(int handle, int table);
int fn_801F9014(int handle);
void fn_8008A9BC(void);
int fn_80086ACC(int *pList);

void fn_8018C344(int database, int firstTable, int secondTable,
                int *pFirstCopy, int *pSecondCopy)
{
    int source = fn_8022F3D4(database);
    fn_801F9980(0x54415453, pFirstCopy);
    fn_801FCE10(0, "use \x8c select into \x8c.\x8c * from \x8c\n", source, 0x54415453, *pFirstCopy, firstTable);
    fn_801F9980(0x54415453, pSecondCopy);
    fn_801FCE10(0, "use \x8c select into \x8c.\x8c * from \x8c\n", source, 0x54415453, *pSecondCopy, secondTable);
}

void fn_8018C3EC(int firstTable, int secondTable)
{
    fn_801F967C(0x54415453, firstTable);
    fn_801F967C(0x54415453, secondTable);
}

void fn_8018C438(int handle, int team)
{
    if (fn_801F9014(handle) == 0) {
        fn_801FCE10(0, "use \x8c delete from 'YALP' where 'DIGT' = \x82\n", handle, team);
    }
}

void fn_8018C48C(int handle)
{
    QueryCursor cursor;
    int teams[8];
    int team;
    if (fn_801F9014(handle) == 0) {
        fn_8008A9BC();
        int status = fn_801FCE10(0, "use \x8c declare \x8a cursor for select 'DIGT' from 'MAET' where 'PYTT' = \x82 or 'PYTT' = \x82\n", handle, &cursor, 6, 5);
        while (status == 0) {
            status = fn_801FCE10(0, "fetch from \x8a 'DIGT' into \x85\n", &cursor, &team);
            if (status != 0) {
                break;
            }
            status = fn_801FCE10(0, "use \x8c delete from 'YALP' where 'DIGT' = \x82\n", handle, team);
        }
        if (QUERY_STATUS_ACCEPTED(status) == true) {
            if (cursor.mUnknown0) {
                status = fn_801FCFA0(&cursor);
            } else {
                status = 0;
            }
        } else {
            if (cursor.mUnknown0) {
                fn_801FCFA0(&cursor);
            }
        }
        if (status == 0) {
            status = fn_801FCE10(0, "use \x8c delete from 'MAET' where 'PYTT' = \x82 or 'PYTT' = \x82\n", handle, 6, 5);
            if (QUERY_STATUS_ACCEPTED(status) == true) {
                status = 0;
            }
            if (status == 0) {
                status = fn_801FCE10(0, "use \x8c delete from 'YALP' where 'YTRP' = \x82 or 'YTRP' = \x82\n", handle, 1, 2);
                if (QUERY_STATUS_ACCEPTED(status) == true) {
                    status = 0;
                }
            }
        }
        int count = fn_80086ACC(teams);
        for (int i = 0; i < count; i++) {
            fn_8018C438(0x54415453, teams[i]);
        }
    }
}
}
