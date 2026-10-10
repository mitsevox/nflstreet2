#include "game/fn_801FCE10.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8017F584.h"
#include "game/fn_8022F478.h"
#include "game/cu_80190208.h"
#include "game/Object_8007A334.h"
#include "game/fn_8007F828.h"

extern "C" unsigned char lbl_803EA588;

struct Record_80055584 {
    int type;
    int column;
    int value[2];
    unsigned char exceeded;
    unsigned char unknown11[3];
    int side;

    void SetValue(int player, int incoming)
    {
        lbl_803EA588 = 1;
        value[player] = incoming;
        if (side == 2 || incoming > value[side])
            side = player;
    }
};

extern "C" {
extern Record_80055584 lbl_802D4B14[];
extern unsigned char lbl_803EC7EC[2];
int fn_80186F7C(unsigned char index);
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_800D41F8(int side);
int fn_8017F60C(void);
int fn_80190394(void);
void fn_80186BAC(void);
void fn_80186CE8(unsigned char *flags);
int fn_80186A10(int index, char *text);
void fn_8007D4E8(void);
void fn_8007D52C(void);
void fn_8007DB74(int type, int row);
int fn_8007DBB4(int column);
int fn_8007D5A0(int type, int row, int column, char *text, int size);
int fn_800A3444(void);
int fn_801C31B0(char *first, char *second);
int fn_801485D4(void);
int fn_8022B7A4(int handle, int tag, void *pValue);
int fn_80187C6C(void);
int fn_80187C8C(void);
int fn_801788D8(int *pValue);
int fn_80178EE0(unsigned char side);
unsigned int fn_801787DC(unsigned char side);
int fn_800A7E40(unsigned char side);
int fn_800A7E54(unsigned char side);
int fn_80032288(int side);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8018F52C(Object_8007A334 *pObject, int a);
void fn_8018F584(Object_8007A334 *pObject);
void fn_8018F6C0(Object_8007A334 *pObject, int index, int delta);
int fn_80178AE0(void);
unsigned int fn_8009D990(int index);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
void fn_800652A8(void);
}

extern "C" void fn_80055584(void)
{
    for (int i = 0; i <= 20; ++i) {
        fn_801C1F94(lbl_802D4B14[i].value, 0, 8);
        lbl_802D4B14[i].side = 2;
        lbl_802D4B14[i].exceeded = 0;
    }
    for (int side = 0; side <= 1; ++side) {
        if (fn_80186F7C((unsigned char)side) != -1) {
            int handle = fn_8022F358(fn_80186F7C((unsigned char)side));
            fn_8022F478(handle);
            int values[18];
            int result = fn_801FCE10(0,
                "use \x8c select 'wnSU' into \x82 and 'swSU' into \x82 and 'FPRP' into \x82 and 'tpSU' into \x82 and 'trSU' into \x82 and 'TDTU' into \x82 and 'FSSU' into \x82 and 'idSU' into \x82 and 'rfSU' into \x82 and 'BGSU' into \x82 and 'TBGU' into \x82 and 'TPTU' into \x82 and 'sdSU' into \x82 and 'WSQU' into \x82 and 'WOSU' into \x82 and 'LOSU' into \x82 and 'SOSU' into \x82 and 'AOSU' into \x82 from 'TSPU'\n",
                fn_8022F3D4(handle),
                &values[0], &values[1], &values[2], &values[3], &values[4], &values[5],
                &values[6], &values[7], &values[8], &values[9], &values[10], &values[11],
                &values[12], &values[13], &values[14], &values[15], &values[16], &values[17]);
            int score = fn_800D41F8(side);
            if (result == 0) {
                lbl_802D4B14[0].SetValue(side, values[0]);
                lbl_802D4B14[1].SetValue(side, values[1]);
                lbl_802D4B14[2].SetValue(side, values[2]);
                lbl_802D4B14[3].SetValue(side, score);
                lbl_802D4B14[4].SetValue(side, score);
                lbl_802D4B14[5].SetValue(side, values[11]);
                lbl_802D4B14[6].SetValue(side, values[3] + values[4]);
                lbl_802D4B14[7].SetValue(side, values[3]);
                lbl_802D4B14[8].SetValue(side, values[4]);
                lbl_802D4B14[9].SetValue(side, values[5]);
                lbl_802D4B14[10].SetValue(side, values[6]);
                lbl_802D4B14[11].SetValue(side, values[7]);
                lbl_802D4B14[12].SetValue(side, values[8]);
                lbl_802D4B14[13].SetValue(side, values[9]);
                lbl_802D4B14[14].SetValue(side, values[10]);
                lbl_802D4B14[15].SetValue(side, values[12]);
                lbl_802D4B14[16].SetValue(side, values[13]);
                lbl_802D4B14[17].SetValue(side, values[14]);
                lbl_802D4B14[18].SetValue(side, values[15]);
                lbl_802D4B14[19].SetValue(side, values[16]);
                lbl_802D4B14[20].SetValue(side, values[17]);
            }
        }
    }
}

extern "C" void fn_80055B2C(unsigned char *anyExceeded)
{
    int update = 0;
    if (!fn_8017F60C() && fn_8017F584() != 11)
        update = 1;
    *anyExceeded = 0;
    unsigned char unavailable = 0;
    if (!fn_8017F584()) {
        if (fn_80186F7C(0) != -1) {
            fn_80190280(fn_80186F7C(0));
            unavailable = fn_80190394() == 0;
            fn_80190288();
        }
        if (fn_80186F7C(1) != -1) {
            fn_80190280(fn_80186F7C(1));
            unavailable |= fn_80190394() == 0;
            fn_80190288();
        }
    }
    if (!unavailable) {
        if (update)
            fn_80186BAC();
        fn_801C1F94(lbl_803EC7EC, 0, 2);
        if (update) {
            if (fn_80186F7C(0) != -1 || fn_80186F7C(1) != -1) {
                char names[2][32];
                for (int side = 0; side <= 1; ++side) {
                    if (fn_80186F7C((unsigned char)side) != -1)
                        fn_80186A10(fn_80186F7C((unsigned char)side), names[side]);
                    else
                        names[side][0] = 0;
                }
                fn_80055584();
                fn_8007D4E8();
                for (int i = 0; i <= 20; ++i) {
                    int row = 0;
                    if (lbl_802D4B14[i].type == 6)
                        row = fn_800A3444();
                    fn_8007DB74(lbl_802D4B14[i].type, row);
                    int current = fn_8007DBB4(lbl_802D4B14[i].column);
                    char holder[32];
                    fn_8007D5A0(lbl_802D4B14[i].type, row, 1, holder, 32);
                    if (lbl_802D4B14[i].type == 6) {
                        lbl_802D4B14[i].exceeded = lbl_802D4B14[i].value[lbl_802D4B14[i].side] > current;
                        lbl_803EC7EC[lbl_802D4B14[i].side] |= lbl_802D4B14[i].exceeded;
                    } else {
                        fn_8007DB74(lbl_802D4B14[i].type, row + 1);
                        int other = fn_8007DBB4(lbl_802D4B14[i].column);
                        if (lbl_802D4B14[i].type == 4) {
                            lbl_802D4B14[i].exceeded = lbl_802D4B14[i].value[lbl_802D4B14[i].side] > current;
                        } else {
                            int exceeded = 0;
                            if (lbl_802D4B14[i].value[lbl_802D4B14[i].side] > current) {
                                if (fn_801C31B0(holder, names[lbl_802D4B14[i].side]) || current != other)
                                    exceeded = 1;
                            }
                            lbl_802D4B14[i].exceeded = exceeded;
                        }
                    }
                    if (lbl_802D4B14[i].exceeded && i <= 15 && !fn_801485D4())
                        *anyExceeded = 1;
                    if (lbl_802D4B14[i].type != 6) {
                        fn_8007DB74(lbl_802D4B14[i].type, 9);
                        int threshold = fn_8007DBB4(lbl_802D4B14[i].column);
                        for (int side = 0; side <= 1; ++side) {
                            if (lbl_802D4B14[i].value[side] > threshold)
                                lbl_803EC7EC[side] = 1;
                        }
                    }
                }
                fn_8007D52C();
            }
            fn_80186CE8(lbl_803EC7EC);
        }
    }
}

extern "C" void fn_80055E8C(int *values, int *exceeded)
{
    fn_8007D4E8();
    for (int i = 0; i < 16; i++) {
        int row;
        if (lbl_802D4B14[i].type == 6)
            row = fn_800A3444();
        else
            row = 0;
        fn_8007DB74(lbl_802D4B14[i].type, row);
        values[i] = fn_8007DBB4(lbl_802D4B14[i].column);
        exceeded[i] = lbl_802D4B14[i].exceeded;
    }
    fn_8007D52C();
}

/* Whole minutes and remaining seconds of a time in seconds. */
#define MINUTES_OF(seconds) ((seconds) / 3600 * 60 + ((seconds) / 60 - (seconds) / 3600 * 60))
#define SECONDS_OF(seconds) ((seconds) - MINUTES_OF(seconds) * 60)

/* Text buffer argument of message 0x80000001. */
struct Text_80056444 {
    int mUnknown0;
    int mSize;
    char *mpBuffer;
};

/* Arguments of fn_80056444. The handlers receive each array from the
   element after the one its first word indexes. */
struct Args_80056444 {
    int *mpArray0;
    int *mpArray1;
    int *mpArray2;
    int *mpMode;
    Text_80056444 *mpText;
};

static inline int *ArgData(int *pArray)
{
    int index = pArray[0] + 1;

    return &pArray[index];
}

extern "C" int fn_80055F24(int handle, int tag)
{
    int value;

    fn_8022B7A4(handle, tag, &value);
    return value;
}

extern "C" void fn_80055F4C(int *pHandles, int *pStats1, int *pStats0, int *pMode, char *pBuffer, int size)
{
    int *pStats[2];
    int value;

    pHandles[1] = fn_80187C6C();
    pHandles[0] = fn_80187C8C();
    for (unsigned char i = 1; i <= 14; i++) {
        pStats0[i] = 9999;
        pStats1[i] = 9999;
    }
    pStats[0] = pStats0;
    pStats[1] = pStats1;
    for (unsigned int side = 0; side <= 1; side++) {
        int index;

        if (side != 0) {
            index = side == 1 ? 1 : -1;
        } else {
            index = 0;
        }
        switch (fn_801788D8(&value)) {
        case 2:
            pStats[side][0] = fn_80178EE0(side);
            break;
        case 1:
            pStats[side][0] = -1;
            break;
        case 0:
        default:
            pStats[side][0] = fn_801787DC(side);
            break;
        }
        int a = fn_80055F24(pHandles[index], 0x74727374);
        int b = fn_80055F24(pHandles[index], 0x74507374);
        int c = fn_80055F24(pHandles[index], 0x64647374);
        pStats[side][2] = a + b + c;
        pStats[side][3] = a;
        pStats[side][4] = b;
        pStats[side][5] = c;
        pStats[side][7] = fn_80055F24(pHandles[index], 0x74737374);
        pStats[side][10] = fn_80055F24(pHandles[index], 0x64317374);
        pStats[side][9] = fn_80055F24(pHandles[index], 0x66667374);
        pStats[side][8] = fn_80055F24(pHandles[index], 0x69447374);
        pStats[side][1] = fn_800D41F8(side);
        pStats[side][11] = fn_800A7E40(side);
        pStats[side][12] = fn_800A7E54(side);
        pStats[side][6] = fn_80055F24(pHandles[index], 0x6B737374);
        pStats[side][13] = fn_80055F24(pHandles[index], 0x73687374);
        if (fn_8017F60C()) {
            pStats[side][14] = 0;
        } else {
            pStats[side][14] = fn_80032288(side);
        }
    }
    if (fn_8017F584() == 8) {
        Object_8007A334 cursor;
        unsigned int score1;
        unsigned int score0;

        fn_8018F52C(&cursor, (signed char)fn_8022F384(fn_8022F4BC()));
        if (fn_8007F828(14) == 1) {
            score1 = fn_800D41F8(1);
            score0 = fn_800D41F8(0);
        } else {
            score1 = fn_801787DC(1);
            score0 = fn_801787DC(0);
        }
        if (score1 > score0) {
            fn_8018F6C0(&cursor, 0, 1);
        } else {
            fn_8018F6C0(&cursor, 0, 0);
        }
        fn_8018F6C0(&cursor, 2, pStats[1][1]);
        fn_8018F6C0(&cursor, 3, pStats[1][3]);
        fn_8018F6C0(&cursor, 4, pStats[1][4]);
        fn_8018F6C0(&cursor, 5, pStats[1][5]);
        fn_8018F6C0(&cursor, 6, pStats[1][6]);
        fn_8018F6C0(&cursor, 7, pStats[1][7]);
        fn_8018F6C0(&cursor, 8, pStats[1][8]);
        fn_8018F6C0(&cursor, 9, pStats[1][9]);
        fn_8018F6C0(&cursor, 10, pStats[1][10]);
        fn_8018F6C0(&cursor, 11, pStats[1][11]);
        fn_8018F6C0(&cursor, 12, pStats[1][12]);
        fn_8018F6C0(&cursor, 13, score1);
        fn_8018F584(&cursor);
    }
    *pMode = fn_80178AE0();
    if (*pMode == 2) {
        *pMode = 0;
    }
    fn_801C2D88(pBuffer, size, "%d:%02d", MINUTES_OF(fn_8009D990(2)), SECONDS_OF(fn_8009D990(2)));
}

extern "C" int fn_80056444(unsigned int id, Args_80056444 *pArgs)
{
    switch (id) {
    case 0x80000002:
        fn_80055B2C((unsigned char *)pArgs->mpArray0);
        break;
    case 0x80000003:
        fn_800652A8();
        break;
    case 0x80000004:
        fn_80055E8C(ArgData(pArgs->mpArray0), ArgData(pArgs->mpArray1));
        break;
    case 0x80000001:
        fn_80055F4C(ArgData(pArgs->mpArray0), ArgData(pArgs->mpArray1),
                    ArgData(pArgs->mpArray2), pArgs->mpMode, pArgs->mpText->mpBuffer,
                    pArgs->mpText->mSize);
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80056560(void)
{
    unsigned char anyExceeded;

    fn_80055B2C(&anyExceeded);
}
