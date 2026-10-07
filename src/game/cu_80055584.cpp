#include "game/fn_801FCE10.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8017F584.h"
#include "game/fn_8022F478.h"
#include "game/cu_80190208.h"

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
extern unsigned char lbl_803EC7EC[];
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
    int unavailable = 0;
    if (!fn_8017F584()) {
        if (fn_80186F7C(0) != -1) {
            fn_80190280(fn_80186F7C(0));
            unavailable = (unsigned char)(fn_80190394() == 0);
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
    int index = 0;
    int remaining = 16;
    do {
        int row;
        if (lbl_802D4B14[index].type == 6)
            row = fn_800A3444();
        else
            row = 0;
        fn_8007DB74(lbl_802D4B14[index].type, row);
        values[index] = fn_8007DBB4(lbl_802D4B14[index].column);
        exceeded[index] = lbl_802D4B14[index].exceeded;
        ++index;
    } while (--remaining);
    fn_8007D52C();
}
