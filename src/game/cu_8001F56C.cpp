#include "game/Object_8007A334.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_80072AA8.h"
#include "game/fn_8007F828.h"

/* One slot of the 21-entry table that lbl_803EBA94 points to. */
struct Entry_803EBA94 {
    int mUnknown0;
    int mUnknown4;
    int mState;
};

/* 256-byte block allocated by fn_8001FD48. */
struct Table_803EBA94 {
    int mCount;
    Entry_803EBA94 mEntries[21];
};

extern "C" {
extern char lbl_802EBFCC[];

void fn_8006DF2C(int a);
void fn_8006EA04(unsigned int index, unsigned int value);
void fn_80072AD8(unsigned char a);
void fn_80072B84(int a, int b, int c);
int fn_80072E6C(void);
void fn_80072F04(void);
void fn_80073094(void);
void fn_8007B358(Object_8007A334 *pObject);
void fn_8007B3AC(Object_8007A334 *pObject);
void fn_8007B3CC(Object_8007A334 *pObject, int key, int *pResult);
int fn_8007B404(Object_8007A334 *pObject);
void fn_8007B42C(Object_8007A334 *pObject, char *pText, int length);
void fn_8007B460(Object_8007A334 *pObject, char *pText, int length);
void fn_8007B494(Object_8007A334 *pObject, char *pText, int length);
void fn_8008352C(Object_8007A334 *pObject, void *pQuery);
void fn_800835D0(Object_8007A334 *pObject);
void fn_80083644(Object_8007A334 *pObject);
int fn_80083664(Object_8007A334 *pObject);
int fn_80083684(Object_8007A334 *pObject);
void fn_800836A4(Object_8007A334 *pObject, int a, int b, int c);
int fn_800837D8(Object_8007A334 *pObject);
int fn_80083804(Object_8007A334 *pObject);
int fn_8008382C(Object_8007A334 *pObject);
void fn_80083854(Object_8007A334 *pObject);
void fn_80083934(Object_8007A334 *pObject, int a, int b, int c);
}

static void *lbl_803EBA90 = (void *)-1;
static Table_803EBA94 *lbl_803EBA94 = 0;

extern "C" {

void fn_8001F56C(void)
{
    Object_8007A334 cursor;
    Object_8007A334 table;
    unsigned char i;

    for (i = 0; i <= 20; i++) {
        lbl_803EBA94->mEntries[i].mUnknown0 = -1;
        lbl_803EBA94->mEntries[i].mUnknown4 = -1;
        lbl_803EBA94->mEntries[i].mState = 3;
    }
    fn_8008352C(&cursor, 0);
    i = 0;
    fn_800835D0(&cursor);
    fn_8007B358(&table);
    lbl_803EBA94->mCount = 40;
    if (fn_80083664(&cursor)) {
        do {
            lbl_803EBA94->mEntries[i].mState = 0;
            if (fn_800837D8(&cursor) == 0) {
                fn_80083804(&cursor);
                fn_8008382C(&cursor);
                lbl_803EBA94->mEntries[i].mUnknown0 = 1;
                lbl_803EBA94->mEntries[i].mUnknown4 = 0;
            } else {
                lbl_803EBA94->mEntries[i].mUnknown0 = 0;
                fn_8007B3CC(&table, fn_8008382C(&cursor), &lbl_803EBA94->mEntries[i].mUnknown4);
            }
            i++;
            lbl_803EBA94->mCount--;
        } while (fn_80083684(&cursor));
    }
    fn_8007B3AC(&table);
    fn_80083644(&cursor);
}

void fn_8001F704(void)
{
    Object_8007A334 cursor;
    Object_8007A334 table;
    int changed = 0;
    unsigned char i;

    fn_8008352C(&cursor, 0);
    fn_8007B358(&table);
    for (i = 0; i <= 20; i++) {
        int state = lbl_803EBA94->mEntries[i].mState;

        if (state == 1 || state == 2) {
            int found;
            int value;

            if (lbl_803EBA94->mEntries[i].mUnknown0 == 0) {
                found = 1;
                fn_8007A600(&table, lbl_803EBA94->mEntries[i].mUnknown4);
                value = fn_8007B404(&table);
            } else {
                found = 0;
                value = 0;
            }
            if (lbl_803EBA94->mEntries[i].mState == 1) {
                fn_800836A4(&cursor, found, 0, value);
                fn_80083854(&cursor);
            } else {
                fn_80083934(&cursor, found, 0, value);
            }
            changed = 1;
        }
    }
    fn_8007B3AC(&table);
    fn_80083644(&cursor);
    if (changed) {
        fn_80072AA8();
    }
}

void fn_8001F850(int mode, int *pResult, Params_80005284 *pText)
{
    int count = 0;

    if (mode == 0) {
        Object_8007A334 table;

        fn_8007B358(&table);
        count = fn_8007A410(&table);
        *pResult = count;
        fn_8007B3AC(&table);
        fn_801C3284(pText->mpText, "EA TRAX", pText->mLength);
    } else if (mode - 1 < 0) {
        *pResult = count;
    } else {
        *pResult = count;
        fn_801C3284(pText->mpText, " ", pText->mLength);
    }
}

int fn_8001F900(void)
{
    return lbl_803EBA94->mCount;
}

int fn_8001F90C(int mode, int key, Params_80005284 **ppTexts)
{
    int result = 0;
    unsigned char i;

    if (mode == 0) {
        Object_8007A334 table;

        fn_8007B358(&table);
        if (fn_8007A600(&table, key)) {
            fn_8007B460(&table, ppTexts[0]->mpText, ppTexts[0]->mLength);
            fn_8007B42C(&table, ppTexts[1]->mpText, ppTexts[1]->mLength);
            fn_8007B494(&table, ppTexts[2]->mpText, ppTexts[2]->mLength);
            fn_8007B404(&table);
            for (i = 0; i <= 20; i++) {
                if (lbl_803EBA94->mEntries[i].mUnknown0 == mode && lbl_803EBA94->mEntries[i].mUnknown4 == key) {
                    int state = lbl_803EBA94->mEntries[i].mState;

                    if (state == 0 || state == 2) {
                        result = 1;
                    }
                    break;
                }
            }
        }
        fn_8007B3AC(&table);
    } else if (mode - 1 < 0) {
        for (i = 0; i <= 20; i++) {
            if (lbl_803EBA94->mEntries[i].mUnknown0 == mode && lbl_803EBA94->mEntries[i].mUnknown4 == key) {
                int state = lbl_803EBA94->mEntries[i].mState;

                if (state == 0 || state == 2) {
                    result = 1;
                }
                break;
            }
        }
    }
    return result;
}

void fn_8001FA90(int mode, int key, Params_80005284 *pText1, Params_80005284 *pText2, Params_80005284 *pText3)
{
    if (mode == 0) {
        Object_8007A334 table;

        fn_8007B358(&table);
        if (fn_8007A600(&table, key)) {
            fn_8007B42C(&table, pText1->mpText, pText1->mLength);
            fn_8007B460(&table, pText2->mpText, pText2->mLength);
            fn_8007B494(&table, pText3->mpText, pText3->mLength);
        }
        fn_8007B3AC(&table);
    }
}

void fn_8001FB3C(int mode, int key)
{
    if (mode == 0) {
        Object_8007A334 table;
        int value;

        fn_8007B358(&table);
        fn_8007A600(&table, key);
        value = fn_8007B404(&table);
        fn_8007B3AC(&table);
        fn_8006DF2C(0x11000001);
        fn_80072B84(1, 0, value);
    } else if (mode - 1 < 0) {
        fn_80072B84(0, 0, 0);
    }
}

void fn_8001FBE8(void)
{
    fn_80073094();
}

int fn_8001FC08(int a, int b)
{
    Table_803EBA94 *pTable = lbl_803EBA94;
    int result = 0;
    int free = 21;
    unsigned char i;

    for (i = 0; i <= 20; i++) {
        if (pTable->mEntries[i].mUnknown0 == a && pTable->mEntries[i].mUnknown4 == b) {
            int state = pTable->mEntries[i].mState;

            if (state == 0) {
                pTable->mEntries[i].mState = 1;
                result = 1;
            } else if (state == 1) {
                pTable->mEntries[i].mState = 0;
                result = 1;
                pTable->mCount--;
                break;
            } else if (state == 2) {
                pTable->mEntries[i].mUnknown0 = -1;
                result = 1;
                pTable->mEntries[i].mUnknown4 = -1;
                pTable->mEntries[i].mState = 3;
            } else {
                continue;
            }
            pTable->mCount++;
            break;
        } else if (pTable->mEntries[i].mUnknown0 == -1 && pTable->mEntries[i].mUnknown4 == -1 && free == 21) {
            free = i;
        }
    }
    if (result == 0 && free != 21) {
        result = 1;
        lbl_803EBA94->mEntries[free].mState = 2;
        lbl_803EBA94->mEntries[free].mUnknown0 = a;
        lbl_803EBA94->mEntries[free].mUnknown4 = b;
        lbl_803EBA94->mCount--;
    }
    return result;
}

void fn_8001FD48(void)
{
    lbl_803EBA90 = fn_801EEB44(lbl_802EBFCC, 44);
    fn_8006EA04(2, 100);
    if (fn_80072E6C()) {
        fn_80072F04();
    }
    fn_80073094();
    fn_80072AD8(1);
    lbl_803EBA94 = (Table_803EBA94 *)fn_801D2B7C(256, 0, 0);
    fn_8001F56C();
}

void fn_8001FDB8(void)
{
    fn_8006EA04(2, (unsigned char)(fn_8007F828(5) * 10));
    fn_80072AD8(0);
    fn_801EEFAC(lbl_803EBA90);
    fn_801D2BD0(lbl_803EBA94);
    lbl_803EBA94 = 0;
    fn_80072F90();
}

int fn_8001FE10(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pResult = 0;
        break;
    case 0x80000002:
        fn_8001F850(pArgs[0].i, pArgs[1].pi, pArgs[2].pParams);
        break;
    case 0x80000003:
        *pResult = fn_8001F900();
        break;
    case 0x80000004:
        *pResult = fn_8001F90C(pArgs[0].i, pArgs[1].i,
                               (Params_80005284 **)(pArgs[2].i + (*pArgs[2].pi + 1) * 4));
        break;
    case 0x80000005:
        fn_8001FA90(pArgs[0].i, pArgs[1].i, pArgs[2].pParams, pArgs[3].pParams, pArgs[4].pParams);
        break;
    case 0x80000006:
        fn_8001FB3C(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000007:
        fn_8001FBE8();
        break;
    case 0x80000008:
        *pResult = fn_8001FC08(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000009:
        fn_8001FD48();
        break;
    case 0x8000000A:
        fn_8001FDB8();
        break;
    case 0x8000000B:
        fn_8001F704();
        fn_8001F56C();
        break;
    default:
        return 0;
    }
    return 1;
}

}
