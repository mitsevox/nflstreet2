#include "game/fn_801FCE10.h"
#include "game/fn_8022F478.h"

extern "C" {
int fn_80178AE0(void);
int fn_801486A0(void);
int fn_80178EA0(int a);
int fn_80178EE0(int a);
int fn_800D41F8(int a);
int fn_800A7E40(unsigned char a);
int fn_800A7E54(unsigned char a);
int fn_8022F34C(void);
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_8022F4BC(void);
int fn_80187400(int kind, int key, int first, int last);
}

extern "C" {

int fn_801864E0(unsigned char value)
{
    return value == fn_80178AE0();
}

int fn_80186518(int kind, int a, int b, int c, int d)
{
    int result = 0;

    switch (fn_801486A0()) {
    case 5:
        switch (kind) {
        case 6:
            result = fn_801864E0(c) ? 1 : 0;
            break;
        }
        break;
    case 2:
        switch (kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            result = fn_801864E0(c) ? 1 : 0;
            break;
        case 9:
            result = fn_801864E0(c) == 0;
            break;
        case 10:
            result = fn_80178EA0(c == 0) - fn_80178EE0(c == 0);
            break;
        case 11:
            result = fn_80178EA0(c == 0);
            break;
        case 12:
            break;
        }
        break;
    default:
        switch (kind) {
        case 3:
            c = d;
        case 2:
            result = fn_801864E0(c) ? 1 : 0;
            break;
        case 4:
            result = fn_800D41F8(c);
            break;
        case 5:
            result = fn_800A7E40(c);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            break;
        case 12:
            result = fn_800A7E54(c);
            break;
        case 0:
            if (fn_801FCE10(0, "select \x8c into \x82 from \x8c where 'DIGT' = \x82\n", b, &result, a, c) != 0) {
                return result;
            }
            break;
        case 1:
            if (c == 1) {
                fn_801FCE10(0, "select 'CSAG' into \x82 from 'FNIG'\n", &result);
            } else {
                fn_801FCE10(0, "select 'CSHG' into \x82 from 'FNIG'\n", &result);
            }
            break;
        }
        break;
    }
    return result;
}

void fn_80186714(int index, int a, int b)
{
    int value;

    fn_8022F478(index);
    if (fn_801FCE10(0, "use \x8c select 'swSU' into \x82 from 'TSPU'\n", fn_8022F3D4(fn_8022F4BC()), &value) == 0) {
        int up = fn_80186518(2, 0, 0, a, b);
        int down = fn_80186518(3, 0, 0, a, b);
        if (up) {
            if (value < 0) {
                value = 1;
            } else {
                value++;
            }
        } else if (down) {
            if (value > 0) {
                value = -1;
            } else {
                value--;
            }
        }
        fn_801FCE10(0, "use \x8c update 'TSPU' set 'swSU' = \x82\n", fn_8022F3D4(fn_8022F4BC()), value);
    }
}

void fn_80186808(int index, int key, int delta)
{
    int value;

    fn_8022F478(index);
    if (fn_801FCE10(0, "use \x8c select \x8c into \x82 from 'TSPU'\n", fn_8022F3D4(fn_8022F4BC()), key, &value) == 0) {
        value += delta;
        fn_801FCE10(0, "use \x8c update 'TSPU' set \x8c = \x82\n", fn_8022F3D4(fn_8022F4BC()), key, value);
    }
}

void fn_8018689C(int key)
{
    int value;
    int status;
    int code = 0;

    status = fn_801FCE10(0, "use 'EVAS' select 'KPCH' into \x82 from 'HCSH' where 'KUCH' = \x82\n", &value, key);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status == 23) {
        value = fn_80187400(0x48435348, 0x4B504348, 0, 15);
        if (value != -1) {
            if (value > 10) {
                signed char i;

                fn_801FCE10(0, "use 'EVAS' delete from 'HCSH' where 'KPCH' = \x82\n", 1);
                for (i = 2; i <= 10; i++) {
                    fn_801FCE10(0, "use 'EVAS' update 'HCSH' set 'KPCH' = \x82 where 'KPCH' = \x82\n", i - 1, i);
                }
                value = 10;
            }
            fn_801FCE10(0, "use 'EVAS' insert into 'HCSH' set 'KPCH' = \x82 and 'KUCH' = \x82\n", value, key);
        }
    }
}

extern const char lbl_802A6E14[] = "use \x8c select \x8c into \x82 from \x8c\n";

int fn_80186994(int index, int table, int column, char *pText)
{
    return fn_801FCE10(0, "use \x8c select \x8c into \x88 from \x8c\n", fn_8022F3D4(fn_8022F358(index)), column, pText, table);
}

extern const char lbl_802A6E54[] = "use \x8c select \x8c into \x89 from \x8c\n";
extern const char lbl_802A6E74[] = "use \x8c update \x8c set \x8c = \x82\n";
extern const char lbl_802A6E90[] = "use \x8c update \x8c set \x8c = \x88\n";
extern const char lbl_802A6EAC[] = "use \x8c update \x8c set \x8c = \x89\n";

int fn_801869F0(void)
{
    return fn_8022F34C();
}

int fn_80186A10(int index, char *pText)
{
    return fn_80186994(index, 0x464E4955, 0x6E755350, pText);
}

}
