#include "game/Object_8007A334.h"
#include "game/cu_800314E0.h"
#include "game/cu_80190208.h"
#include "game/fn_8007F828.h"
#include "game/fn_8017F584.h"
#include "game/fn_801D2B7C.h"

/* Record filled by fn_80088CE0. */
struct Record_80088CE0 {
    signed char mIndex;
    char mName[132];
    int mUnknown136;
    int mUnknown140;
    unsigned int mUnknown144;
    int mUnknown148;
};

extern "C" {
int fn_800A3444(void);
int fn_800D41F8(int side);
int fn_800D7550(int a, unsigned int b);
void fn_80083E1C(Object_8007A334 *pObject, Query_80083E40 *pQuery);
int fn_80083FE4(Object_8007A334 *pObject);
void fn_80087BE4(Object_8007A334 *pObject, int index);
void fn_80087C3C(Object_8007A334 *pObject);
int fn_80087C8C(Object_8007A334 *pObject, unsigned int index);
void fn_8008880C(int db, int id);
void fn_8008898C(Object_8007A334 *pObject, int db);
void fn_80088A1C(Object_8007A334 *pObject);
void fn_80088A3C(Object_8007A334 *pObject, int a);
int fn_80088A74(Object_8007A334 *pObject, int index);
void fn_80088AC8(Object_8007A334 *pObject, int index, int a);
void fn_80088B24(Object_8007A334 *pObject, int a, unsigned char b);
void fn_80088C8C(Object_8007A334 *pObject);
int fn_80088CAC(Object_8007A334 *pObject, int a, int key, int b);
void fn_80088CE0(Object_8007A334 *pObject, Record_80088CE0 *pRecord);
unsigned char fn_80088D84(Object_8007A334 *pObject);
int fn_801486A0(void);
int fn_801869F0(void);
int fn_80186A10(int index, char *pText);
signed char fn_80186B38(int a);
signed char fn_80186F7C(unsigned char index);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int fn_8022F358(signed char index);
int fn_8022F384(int a);
int fn_8022F4BC(void);
int fn_80190394(void);
}

Entry_80306620 *lbl_80306620[100];
unsigned int lbl_803EA3A0 = 0;
char lbl_803EC670[6];

int lbl_802CCB18[13] = {0, 2, 10, 11, 4, 4, 3, 5, 8, 9, 6, 7, 12};
int lbl_802CCB4C[6] = {17, 20, 21, 16, 15, 18};
char lbl_802CCB64[6][8] = {"GNNE-69", "GXBE-69", "GUGE-69", "GNQE-69", "GCUE-69", "G3VE-69"};
int lbl_802CCB94[6] = {22, 23, 29, 26, 27, 24};

extern "C" {
int fn_800314E0(Object_8007A334 *pCursor, Object_8007A334 *pOther, int key, Entry_80306620 *pEntry, int db)
{
    Record_80088CE0 record;

    if (fn_80088CAC(pCursor, 0, key, 0) == 0) {
        return 0;
    }
    if (fn_80088A74(pOther, fn_80088D84(pCursor)) != 0) {
        return 0;
    }
    fn_80088A3C(pOther, 1);
    fn_80088CE0(pCursor, &record);
    fn_8008880C(db, record.mUnknown148);
    fn_801C2E18(pEntry->mName, record.mName);
    fn_80186A10(fn_80186B38(db), pEntry->mText);
    pEntry->mUnknown164 = record.mUnknown148;
    return 1;
}

void fn_8003159C(Object_8007A334 *pCursor, Object_8007A334 *pOther, signed char pad)
{
    Record_80088CE0 record;
    Object_8007A334 object;
    Entry_80306620 *pEntry;
    unsigned int count;

    if (fn_8007A444(pCursor)) {
        fn_80087BE4(&object, pad);
        do {
            if (fn_80088A74(pOther, fn_80088D84(pCursor)) == 0) {
                fn_80088CE0(pCursor, &record);
                if (record.mUnknown140 == 4) {
                    count = fn_80087C8C(&object, 4) + fn_80087C8C(&object, 3) + fn_80087C8C(&object, 5);
                } else {
                    count = fn_80087C8C(&object, lbl_802CCB18[record.mUnknown140]);
                }
                if (count >= record.mUnknown144) {
                    fn_80088A3C(pOther, 1);
                    fn_8008880C(fn_8022F358(pad), record.mUnknown148);
                    pEntry = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
                    lbl_80306620[lbl_803EA3A0] = pEntry;
                    fn_801C2E18(pEntry->mName, record.mName);
                    fn_80186A10(pad, pEntry->mText);
                    pEntry->mUnknown164 = record.mUnknown148;
                    lbl_803EA3A0++;
                }
            }
        } while (fn_8007A510(pCursor));
        fn_80087C3C(&object);
    }
}

void fn_80031724(Object_8007A334 *pCursor, Object_8007A334 *pOther, int db)
{
    Entry_80306620 entry;
    int mode;
    int index;
    int key;

    mode = fn_8017F584();
    switch (mode) {
    case 0:
        key = 13;
        break;
    case 2:
        key = 14;
        break;
    case 9:
        index = fn_801486A0();
        key = lbl_802CCB4C[index];
        break;
    default:
        return;
    }
    if (fn_800314E0(pCursor, pOther, key, &entry, db)) {
        lbl_80306620[lbl_803EA3A0] = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
        fn_801C2E18(lbl_80306620[lbl_803EA3A0]->mName, entry.mName);
        fn_801C2E18(lbl_80306620[lbl_803EA3A0]->mText, entry.mText);
        lbl_80306620[lbl_803EA3A0]->mUnknown164 = entry.mUnknown164;
        lbl_803EA3A0++;
    }
}

void fn_80031828(Object_8007A334 *pCursor, Object_8007A334 *pOther, int db)
{
    Record_80088CE0 record;
    Entry_80306620 *pEntry;
    unsigned int value;

    value = fn_8007F828(1);
    if (fn_80088CAC(pCursor, 0, 37, 0)) {
        do {
            if (fn_80088A74(pOther, fn_80088D84(pCursor)) == 0) {
                fn_80088CE0(pCursor, &record);
                if (value >= record.mUnknown144) {
                    fn_80088A3C(pOther, 1);
                    fn_8008880C(db, record.mUnknown148);
                    pEntry = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
                    lbl_80306620[lbl_803EA3A0] = pEntry;
                    fn_801C2E18(pEntry->mName, record.mName);
                    fn_80186A10(fn_8022F384(db), pEntry->mText);
                    pEntry->mUnknown164 = record.mUnknown148;
                    lbl_803EA3A0++;
                }
            }
        } while (fn_80088CAC(pCursor, 1, 37, 0) == 1);
    }
}

void fn_80031940(Object_8007A334 *pCursor, Object_8007A334 *pOther, int db, int key, int value)
{
    Record_80088CE0 record;
    Entry_80306620 *pEntry;

    if (fn_80088CAC(pCursor, 0, key, 0)) {
        do {
            fn_80088CE0(pCursor, &record);
            if (record.mUnknown144 == value) {
                if (fn_80088A74(pOther, fn_80088D84(pCursor)) == 0) {
                    fn_80088A3C(pOther, 1);
                    fn_8008880C(db, record.mUnknown148);
                    pEntry = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
                    lbl_80306620[lbl_803EA3A0] = pEntry;
                    fn_801C2E18(pEntry->mName, record.mName);
                    fn_80186A10(fn_8022F384(db), pEntry->mText);
                    pEntry->mUnknown164 = record.mUnknown148;
                    lbl_803EA3A0++;
                }
                return;
            }
        } while (fn_80088CAC(pCursor, 1, key, 0) == 1);
    }
}

void fn_80031A54(void)
{
    Object_8007A334 other;
    Object_8007A334 cursor;
    Object_8007A334 query;
    unsigned char i;
    signed char pad;
    int db;

    for (i = 0; i < 2; i++) {
        pad = fn_80186F7C(i);
        if (pad == -1) {
            continue;
        }
        db = fn_8022F358(pad);
        fn_8008898C(&other, db);
        fn_80088B24(&cursor, 1, 0);
        fn_8003159C(&cursor, &other, pad);
        fn_80088C8C(&cursor);
        fn_80088B24(&cursor, 0, 0);
        fn_80031724(&cursor, &other, db);
        if (fn_8017F584() == 0) {
            fn_80083E1C(&query, 0);
            if (fn_8007F828(14) == 0) {
                fn_80031828(&cursor, &other, db);
            }
            fn_80084034(&query, i, 0);
            fn_80031940(&cursor, &other, db, 34, fn_80083FE4(&query));
            fn_80084034(&query, (i + 1) % 2, 0);
            fn_80031940(&cursor, &other, db, 35, fn_80083FE4(&query));
            fn_80031940(&cursor, &other, db, 36, fn_800A3444());
            fn_80083F68(&query);
        }
        fn_80088C8C(&cursor);
        fn_80088A1C(&other);
    }
}

void fn_80031C28(void)
{
    Record_80088CE0 record;
    Object_8007A334 other;
    Object_8007A334 cursor;
    Entry_80306620 *pEntry;
    int i;
    int j;
    int db;
    int index;

    fn_80088B24(&cursor, 0, 0);
    for (i = 0; i <= 5; i++) {
        if (lbl_803EC670[i] == 1 && fn_80088CAC(&cursor, 0, lbl_802CCB94[i], 0) == 1) {
            for (j = 0; j < fn_801869F0(); j++) {
                db = fn_8022F358(j);
                index = fn_80088D84(&cursor);
                fn_8008898C(&other, db);
                if (fn_80088A74(&other, index) == 0) {
                    fn_80088CE0(&cursor, &record);
                    fn_80088A3C(&other, 1);
                    fn_8008880C(db, record.mUnknown148);
                    pEntry = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
                    lbl_80306620[lbl_803EA3A0] = pEntry;
                    fn_801C2E18(pEntry->mName, record.mName);
                    fn_80186A10(fn_8022F384(db), pEntry->mText);
                    pEntry->mUnknown164 = record.mUnknown148;
                    lbl_803EA3A0++;
                }
                fn_80088A1C(&other);
            }
        }
    }
    fn_80088C8C(&cursor);
}

void fn_80031DC8(void)
{
    Record_80088CE0 record;
    Object_8007A334 other;
    Object_8007A334 cursor;
    Entry_80306620 *pEntry;
    int db;

    db = fn_8022F4BC();
    fn_8008898C(&other, db);
    fn_80088B24(&cursor, 0, 0);
    if (fn_80088CAC(&cursor, 0, 39, 0)) {
        fn_80088CE0(&cursor, &record);
        fn_80088AC8(&other, record.mIndex, 1);
        fn_8008880C(db, record.mUnknown148);
        pEntry = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
        lbl_80306620[lbl_803EA3A0] = pEntry;
        fn_801C2E18(pEntry->mName, record.mName);
        fn_80186A10(fn_8022F384(db), pEntry->mText);
        pEntry->mUnknown164 = record.mUnknown148;
        lbl_803EA3A0++;
        fn_80088A1C(&other);
        fn_80088C8C(&cursor);
        fn_80031C28();
    }
}

void fn_80031EFC(void)
{
    Object_8007A334 cursor;
    Object_8007A334 other;
    Entry_80306620 entry;
    unsigned char i;
    int db;

    fn_80088B24(&cursor, 0, 0);
    for (i = 0; i < fn_801869F0(); i++) {
        db = fn_8022F358(i);
        fn_8008898C(&other, db);
        if (fn_800314E0(&cursor, &other, 38, &entry, db)) {
            lbl_80306620[lbl_803EA3A0] = (Entry_80306620 *)fn_801D2B7C(168, 0, 0);
            fn_801C2E18(lbl_80306620[lbl_803EA3A0]->mName, entry.mName);
            fn_801C2E18(lbl_80306620[lbl_803EA3A0]->mText, entry.mText);
            lbl_80306620[lbl_803EA3A0]->mUnknown164 = entry.mUnknown164;
            lbl_803EA3A0++;
        }
        fn_80088A1C(&other);
    }
    fn_80088C8C(&cursor);
}

unsigned int fn_8003203C(void)
{
    return lbl_803EA3A0;
}

void fn_80032044(int index, Entry_80306620 *pEntry)
{
    if (index <= 100) {
        fn_801C2E18(pEntry->mName, lbl_80306620[index]->mName);
        fn_801C2E18(pEntry->mText, lbl_80306620[index]->mText);
        pEntry->mUnknown164 = lbl_80306620[index]->mUnknown164;
    }
}

void fn_800320B0(void)
{
    unsigned int i;

    for (i = 0; i < lbl_803EA3A0; i++) {
        fn_801D2BD0(lbl_80306620[i]);
    }
    lbl_803EA3A0 = 0;
}

int fn_80032110(Entry_80306620 *pEntry)
{
    int result = 0;
    Object_8007A334 cursor;
    Object_8007A334 other;
    int db;
    int mode;
    int key;

    db = fn_8022F4BC();

    fn_80088B24(&cursor, 0, 0);
    fn_8008898C(&other, db);
    mode = fn_8017F584();
    switch (mode) {
    case 6:
        key = 30;
        break;
    case 7:
    case 12:
        key = 31;
        break;
    case 8:
        key = 32;
        break;
    case 11:
        key = 33;
        break;
    default:
        key = -1;
        break;
    }
    result = fn_800314E0(&cursor, &other, key, pEntry, db);
    fn_80088C8C(&cursor);
    fn_80088A1C(&other);
    return result;
}

void fn_80032220(void)
{
    int i;

    for (i = 0; i < 6; i++) {
        lbl_803EC670[i] = 0;
    }
}

void fn_80032240(int index)
{
    lbl_803EC670[index] = 1;
}

void fn_80032250(int index, char *pDest)
{
    fn_801C2E18(pDest, lbl_802CCB64[index]);
}

int fn_80032288(int side)
{
    unsigned char flag;

    flag = 0;
    if (fn_8017F584() == 0) {
        if (fn_80186F7C(0) != -1) {
            fn_80190280(fn_80186F7C(0));
            flag |= fn_80190394() == 0;
            fn_80190288();
        }
        if (fn_80186F7C(1) != -1) {
            fn_80190280(fn_80186F7C(1));
            flag |= fn_80190394() == 0;
            fn_80190288();
        }
    }
    if (flag) {
        return 0;
    }
    return fn_800D7550(side, fn_800D41F8(side));
}
}
