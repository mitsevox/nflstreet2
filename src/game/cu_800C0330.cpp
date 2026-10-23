#include "game/Block_800BFAD0.h"
#include "game/fn_800B65A0.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801FCE10.h"
#include "game/Object_80039F5C.h"

extern "C" {
void fn_800BE944(int index, int a, unsigned int msg, float value);
void fn_8003A3F4(int a, int index);
void fn_8017DDDC(int index);
void fn_8017E01C(int index);
int fn_801C6280(int a, int b, void *p);
int fn_800C8744(int team);
unsigned short fn_800C0660(unsigned short *p, int value);
void fn_800B4DE4(QueryCursor cursor, int index, void *pData);
void fn_800B4900(QueryCursor cursor, int index, short *pRatings, void *pOut);
void fn_800B4798(short *pRatings, int team, int index, float *pOut);
void fn_800A6F04(int team);

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
                fn_800BE944((unsigned char)i, fn_800B65A0(i), 133, 0.0f);
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


extern "C" void fn_800C07F0(QueryCursor cursor, unsigned char team, unsigned short *pValues)
{
    unsigned short i = 0;
    unsigned short id;

    while (fn_801FCE10(0, "fetch from \x8a 'DIGP' into \x81\n", &cursor, &id) == 0) {
        if (i <= 6) {
            unsigned short index = fn_800C0660(pValues, id);
            Object_80039F5C *p = fn_80039F5C(team, index);

            fn_800B4DE4(cursor, i, &p->mUnknown2900);
            p->mUnknown508 = p->mUnknown2904Float;
            fn_800B4900(cursor, i, p->mRatings, p->mUnknown3020);
            fn_800B4798(p->mRatings, team, (unsigned char)index, &p->mUnknown2900);
            i++;
        }
    }
    fn_800A6F04(team);
}
