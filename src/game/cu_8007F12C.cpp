#include "game/Query_8007F19C.h"
#include "game/FELoop.h"
#include "game/Object_8007A334.h"
#include "game/cu_8007F12C.h"
#include "game/fn_8007F828.h"
#include "game/fn_8017F584.h"

/* One row of the option table: the column tag and the value to store when the
   options are reset. */
struct ColumnDefault_802D6798 {
    int mColumnTag;
    int mValue;
};

extern "C" {
extern void *lbl_803EB688;

int fn_801FA428(int file, Table_8007F19C *pTables, Expression_8007F19C *pExpression,
                ColumnValue_802D6424 *pList, Result_8007F19C *pResult, int a);
void fn_8006EA04(int channel, unsigned char level);
void fn_8006EC24(void);
int fn_8013D0D0(void);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);

}

static ColumnDefault_802D6798 sColumnDefaults[23] = {
    { 0x454C534F, 0 },
    { 0x414C504F, 36 },
    { 0x544C504F, 200000 },
    { 0x4152544F, 10 },
    { 0x5658464F, 10 },
    { 0x5647494F, 10 },
    { 0x5349444F, 0 },
    { 0x4F52504F, 0 },
    { 0x5550434F, 1 },
    { 0x4249564F, 1 },
    { 0x4853434F, 1 },
    { 0x4554534F, 1 },
    { 0x4153414F, 1 },
    { 0x41434D4F, 0 },
    { 0x444D474F, 0 },
    { 0x5455544F, 0 },
    { 0x5249414F, 1 },
    { 0x4D4E534F, 1 },
    { 0x4D5A434F, 0 },
    { 0x4542474F, 1 },
    { 0x5041504F, 0 },
    { 0x5047504F, 1 },
    { 0x5447504F, 0 },
};

static Object_8007A334 sCursor;
static ColumnValue_802D6424 sRecord[24];

/* While set, fn_8007F6F8 updates only the record and skips the per-column
   store; fn_8007F394 writes the whole record back when it clears. */
static unsigned char sDeferWrites = 0;

/* Columns 1, 2, 14, 8 and 19 keep a separate value that fn_8017F584() == 6
   selects instead of the record value. */
static int sShadow1 = 36;
static int sShadow2 = 100000;
static int sShadow14 = 0;
static int sShadow8 = 1;
static int sShadow19 = 1;

extern "C" {

static void fn_8007F3D8(void);

static inline int WriteRecord(Object_8007A334 *pCursor,
                              ColumnValue_802D6424 *pList)
{
    Expression_8007F19C expression;
    Result_8007F19C result;
    Table_8007F19C tables[2];
    ColumnValue_802D6424 key[2];

    key[0].Set(-1, pCursor->mUnknown12, 0);
    key[1].SetEnd();
    pCursor->Read(key);
    unsigned int table = pCursor->mUnknown8;
    unsigned int column = pCursor->mUnknown12;

    expression.Set(((unsigned long long)table << 32) | column,
                   0x00010003, key[0].mValue);
    tables[0].Set(table);
    tables[1].Set(-1);
    return fn_801FA428(pCursor->mUnknown4, tables, &expression, pList, &result, 0);
}

static void fn_8007F12C(void)
{
    fn_8007A334(&sCursor, 0x5354504F, 0x554E554F, 0, 0, 0x45564153);
}

static int fn_8007F174(void)
{
    return fn_8007A3C4(&sCursor);
}

/* Writes the whole record back to the row the cursor's key column selects. */
static int fn_8007F19C(void)
{
    return WriteRecord(&sCursor, sRecord);
}

/* Fills the record with the defaults and replaces them with the stored row. */
static int fn_8007F298(void)
{
    ColumnValue_802D6424 *pEnd;
    int i;

    for (i = 0; i < 23; i++) {
        sRecord[i].mTableTag = 0x5354504F;
        sRecord[i].mColumnTag = sColumnDefaults[i].mColumnTag;
        sRecord[i].mValue = sColumnDefaults[i].mValue;
    }
    pEnd = &sRecord[23];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;
    return sCursor.Read(sRecord);
}

void fn_8007F328(int reset)
{
    sDeferWrites = 0;
    fn_8007F12C();
    if (reset != 0) {
        fn_8007F3D8();
    } else {
        fn_8007F298();
    }
    fn_8006EC24();
}

int fn_8007F374(void)
{
    return fn_8007F174();
}

void fn_8007F394(int defer)
{
    if (sDeferWrites != 0 && defer == 0) {
        fn_8007F19C();
    }
    sDeferWrites = defer;
}

/* Resets every option to its default and stores the result. */
static void fn_8007F3D8(void)
{
    ColumnValue_802D6424 *pEnd;
    int mode;
    int i;

    for (i = 0; i < 23; i++) {
        sRecord[i].mTableTag = 0x5354504F;
        sRecord[i].mColumnTag = sColumnDefaults[i].mColumnTag;
        sRecord[i].mValue = sColumnDefaults[i].mValue;
    }
    pEnd = &sRecord[23];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;

    WriteRecord(&sCursor, sRecord);

    mode = fn_8013D0D0();
    if (mode == 1 || mode == 2) {
        fn_8007F6F8(6, mode);
    }
}

/* Resets the marked options to their defaults and stores the result. */
int fn_8007F548(void)
{
    unsigned char reset[23] = {
        1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    };
    ColumnValue_802D6424 *pEnd;
    int i;

    for (i = 0; i < 23; i++) {
        sRecord[i].mTableTag = 0x5354504F;
        sRecord[i].mColumnTag = sColumnDefaults[i].mColumnTag;
        if (reset[i] != 0) {
            sRecord[i].mValue = sColumnDefaults[i].mValue;
        }
    }
    pEnd = &sRecord[23];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;

    return WriteRecord(&sCursor, sRecord);
}

void fn_8007F6F8(int id, int value)
{
    if (fn_8017F584() == 6) {
        switch (id) {
        case 1:
            sShadow1 = value;
            return;
        case 2:
            sShadow2 = value;
            return;
        case 14:
            sShadow14 = value;
            return;
        case 8:
            sShadow8 = value;
            return;
        case 19:
            sShadow19 = value;
            return;
        }
    }
    if (sDeferWrites == 0) {
        fn_8007AA90(&sCursor, sColumnDefaults[id].mColumnTag, value);
    }
    sRecord[id].mValue = value;
    if (id >= 3 && id <= 5) {
        switch (id) {
        case 3:
            fn_8006EA04(3, value * 10);
            break;
        case 4:
            fn_8006EA04(1, value * 10);
            break;
        case 5:
            fn_8006EA04(2, value * 10);
            break;
        }
    }
}

int fn_8007F828(int id)
{
    int allowed = 1;
    int result = 0;
    int override = 0;

    if ((unsigned int)id <= 22) {
        if (fn_8017F584() == 8) {
            override = 1;
            if (fn_80027DF0() != 0 && lbl_803EB688 != 0) {
                unsigned short state;
                unsigned short other;

                fn_80219650(lbl_803EB688, &state, &other);
                if (state == 5 || state == 0) {
                    allowed = 0;
                }
            }
        }
        if (fn_8017F584() == 6) {
            switch (id) {
            case 1:
                return sShadow1;
            case 2:
                return sShadow2;
            case 14:
                return sShadow14;
            case 8:
                return sShadow8;
            case 19:
                return sShadow19;
            }
        } else if (override != 0 && allowed != 0) {
            switch (id) {
            case 1:
                return 36;
            case 14:
                return 0;
            case 8:
                return 1;
            case 19:
                return 1;
            }
        }
        result = sRecord[id].mValue;
    }
    return result;
}

void fn_8007F97C(void)
{
    sShadow1 = sRecord[1].mValue;
    sShadow2 = sRecord[2].mValue;
    sShadow14 = sRecord[14].mValue;
    sShadow8 = sRecord[8].mValue;
    sShadow19 = sRecord[19].mValue;
}
}
