#include "game/Class_8018FD64Inline.h"

extern "C" {
void fn_80060458(signed char db, int index);
void fn_8006059C(signed char db);
void fn_80060674(signed char db);
void fn_80061D64(int index);
void fn_80061DA0(int index);
unsigned int fn_80078800(void);
void fn_80078844(int value);
void fn_80078C04(signed char db, int value);
void fn_8007B5A8(int index, int id, int value);
void fn_8007B5FC(int index);
void fn_8007B640(int index);
void fn_8007E3D4(signed char db);
void fn_8007E474(signed char db);
void fn_8007E954(signed char db, int index);
void fn_8007EA04(signed char db, int index);
void fn_8007ECBC(int db, int id);
void fn_8007ED50(int db, int id);
void fn_8007EDE4(int db);
void fn_8007EE70(int db);
void fn_80082688(int db);
void fn_8008274C(int db);
int fn_800881B8(void);
void fn_80088638(int db);
void fn_8008879C(int handle, int value);
int fn_80186B38(int db);
void fn_8018E428(int index, int value);
void fn_8018F340(int a, int b);
int fn_8018F3D8(int a);
void fn_8018F41C(int a);
void fn_8018F4C4(int a);
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_8022F478(int value);
int fn_8022F4BC(void);

void fn_80054628(signed char db, int id)
{
    switch (id) {
    case 1:
        fn_8007B5FC(db);
        break;
    case 2:
        fn_80082688(db);
        break;
    case 3:
        fn_8007E3D4(db);
        break;
    case 4:
        fn_8007EDE4(db);
        break;
    case 5:
        fn_8007E954(db, 0);
        fn_8007E954(db, 1);
        break;
    case 9:
        fn_8007ECBC(db, 43);
        break;
    case 10:
        fn_8007ECBC(db, 40);
        break;
    case 11:
        fn_8007ECBC(db, 41);
        break;
    case 12:
        fn_8007ECBC(db, 42);
        break;
    case 13:
        fn_8007ECBC(db, 39);
        break;
    case 14:
        fn_8007ECBC(db, 36);
        break;
    case 15:
        fn_8007ECBC(db, 37);
        break;
    case 16:
        fn_8007ECBC(db, 38);
        break;
    case 19:
        fn_8007ECBC(db, 33);
        break;
    case 20:
        fn_8007ECBC(db, 44);
        break;
    case 18:
        fn_8007ECBC(db, 34);
        fn_8007B5A8(db, 11, 0);
        break;
    case 21:
        fn_8007B5A8(db, 10, 0);
        break;
    case 6:
        fn_8018E428(db, 999999);
        fn_80078C04(db, 999999);
        break;
    case 7:
        fn_8008879C(fn_8022F358(db), 9999999);
        break;
    case 8: {
        int saved = fn_8022F4BC();
        fn_8022F478(fn_8022F358(db));
        fn_8006059C(db);
        fn_80061D64(db);
        fn_8022F478(saved);
        break;
    }
    case 51:
        fn_80060458(db, 0);
        break;
    case 52:
        fn_80060458(db, 1);
        break;
    case 53:
        fn_80060458(db, 2);
        break;
    case 54:
        fn_80060458(db, 3);
        break;
    case 50:
        fn_8006059C(db);
        break;
    case 49: {
        unsigned int value = fn_80078800();
        if (value) {
            fn_80078844(-value);
        } else {
            fn_80078844(1);
        }
        break;
    }
    case 48:
        for (int i = 1; i <= 32; i++) {
            if (i != 19 && i != 22) {
                fn_8018F340(fn_80186B38(fn_8022F4BC()), i);
                fn_8018F4C4(fn_80186B38(fn_8022F4BC()));
            }
        }
        break;
    case 17:
    case 47:
        break;
    }
}

void fn_80054964(signed char db, int id)
{
    switch (id) {
    case 1:
        fn_8007B640(db);
        break;
    case 2:
        fn_8008274C(db);
        break;
    case 3:
        fn_8007E474(db);
        break;
    case 4:
        fn_8007EE70(db);
        break;
    case 5:
        fn_8007EA04(db, 0);
        fn_8007EA04(db, 1);
        break;
    case 9:
        fn_8007ED50(db, 43);
        break;
    case 10:
        fn_8007ED50(db, 40);
        break;
    case 11:
        fn_8007ED50(db, 41);
        break;
    case 12:
        fn_8007ED50(db, 42);
        break;
    case 13:
        fn_8007ED50(db, 39);
        break;
    case 14:
        fn_8007ED50(db, 36);
        break;
    case 15:
        fn_8007ED50(db, 37);
        break;
    case 16:
        fn_8007ED50(db, 38);
        break;
    case 18: {
        int handle = fn_8022F3D4(fn_8022F358(db));
        Class_8018FD64 cursor;
        cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
        if (cursor.Class_8018FD64::fn_8018FF9C(0x504C5555) != 0x3FF) {
            fn_8007ED50(db, 34);
        }
        if (fn_8018F3D8(db) != -1) {
            fn_8007B5A8(db, 11, 1);
        }
        break;
    }
    case 19:
        fn_80088638(fn_8022F358(db));
        if (fn_800881B8() == 0) {
            fn_8007ED50(db, 33);
        }
        fn_80088638(-1);
        break;
    case 20:
        fn_8007ED50(db, 44);
        break;
    case 21:
        fn_8007B5A8(db, 10, 1);
        break;
    case 6:
        fn_8018E428(db, 0);
        fn_80078C04(db, 0);
        break;
    case 7:
        fn_8008879C(fn_8022F358(db), 0);
        break;
    case 8:
        fn_80060674(db);
    case 50:
        fn_80061DA0(db);
        break;
    case 48:
        fn_8018F41C(db);
        break;
    case 51:
    case 52:
    case 53:
    case 54:
        fn_80060674(db);
        fn_80061DA0(db);
        break;    case 17:
    case 47:
        break;
    }
}
}
