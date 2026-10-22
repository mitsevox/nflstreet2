#include "game/Block_800BFAD0.h"
#include "game/fn_800B65A0.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801FCE10.h"

extern "C" {
void fn_800BE944(unsigned char index, int team, int kind, float value);
void fn_8003A3F4(int a, int index);
void fn_8017DDDC(int index);
void fn_8017E01C(int index);
int fn_801C6280(int a, int b, void *p);
int fn_800C8744(int team);

extern char lbl_802ECD44[];
}

extern "C" void fn_800C0330(void *p)
{
    if (fn_800AD9B4() == 2) {
        int i;

        for (i = 0; i <= 1; i++) {
            switch (lbl_803EABA8->mSlots[i].mUnknown0) {
            case 0:
                break;
            case 4:
                fn_800BE944(i, fn_800B65A0(i), 133, 0.0f);
                fn_800BEC1C(fn_800B65A0(i), (unsigned char)i);
                fn_8003A3F4(0, i);
                break;
            case 1:
                lbl_803EABA8->mSlots[i].mUnknown0 = 0;
                fn_8017DDDC((unsigned char)i);
                break;
            case 3:
                lbl_803EABA8->mSlots[i].mUnknown0 = 0;
                fn_8017E01C((unsigned char)i);
                break;
            }
        }
        fn_801C6280(-1, 3, lbl_802ECD44);
    }
}

extern "C" QueryCursor fn_800C0698(unsigned char index, unsigned short *pValues)
{
    int id = fn_800C8744(index);
    QueryCursor cursor;
    QueryResult result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result,
                "declare \x8a cursor for select * from 'AGLP' where ('DIGT' = \x85) and "
                "(('DIGP' = \x84) or ('DIGP' = \x84) or ('DIGP' = \x84) or ('DIGP' = \x84) or "
                "('DIGP' = \x84) or ('DIGP' = \x84) or ('DIGP' = \x84))\n",
                &cursor, id, pValues[0], pValues[1], pValues[2], pValues[3],
                pValues[4], pValues[5], pValues[6]);
    return cursor;
}

