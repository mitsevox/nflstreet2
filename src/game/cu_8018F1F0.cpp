#include "game/Object_8007A334.h"
#include "game/fn_801FCE10.h"

struct Record_8018FC1C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
    int mUnknown28;
    int mUnknown32;
    unsigned char mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
};

extern "C" {
int fn_8018EB20(unsigned int index, int *pLglt, char *pEtnr, int size);
int fn_8022F358(int index);
int fn_8022F3D4(int a);

int fn_8018F1F0(unsigned int index, char *pEtnr, int size);
int fn_8018F228(int a);
int fn_8018F288(int a, int b);
int fn_8018F2F4(int a, int b);
void fn_8018F340(int a, int b);
void fn_8018F38C(int a, int b);
int fn_8018F3D8(int a);
void fn_8018F41C(int a);
void fn_8018F488(int a);
void fn_8018F4C4(int a);
void fn_8018F52C(Object_8007A334 *pObject, int a);
void fn_8018F584(Object_8007A334 *pObject);
int fn_8018F5A4(Object_8007A334 *pObject, int index);
void fn_8018F6C0(Object_8007A334 *pObject, int index, int delta);
void fn_8018F9B4(int a);
void fn_8018FB4C(Object_8007A334 *pObject, int type);
void fn_8018FBC8(Object_8007A334 *pObject);
int fn_8018FBE8(Object_8007A334 *pObject, int id);
void fn_8018FC1C(Object_8007A334 *pObject, Record_8018FC1C *pRecord);

int fn_8018F1F0(unsigned int index, char *pEtnr, int size)
{
    int lglt = -1;

    fn_8018EB20(index, &lglt, pEtnr, size);
    return lglt;
}

int fn_8018F228(int a)
{
    int digt;
    int lttg = fn_8018F3D8(a);

    fn_801FCE10(0, "use \x8c select 'DIGT' into \x85 from 'MTTG' where 'LTTG' = \x82\n",
                fn_8022F3D4(fn_8022F358(a)), &digt, lttg);
    return digt;
}

int fn_8018F288(int a, int b)
{
    int fdtg;

    if (fn_801FCE10(0, "use \x8c select 'FDTG' into \x82 from 'NUAG' where 'DIGT' = \x85\n",
                    fn_8022F3D4(fn_8022F358(a)), &fdtg, b) == 0 && fdtg == 1) {
        return 1;
    }
    return 0;
}

int fn_8018F2F4(int a, int b)
{
    return fn_801FCE10(0, "use \x8c update 'MTTG' set 'DIGT' = \x85\n", fn_8022F3D4(fn_8022F358(a)), b);
}

void fn_8018F340(int a, int b)
{
    fn_801FCE10(0, "use \x8c update 'NUAG' set 'FDTG' = 1 where 'DIGT' = \x85\n", fn_8022F3D4(fn_8022F358(a)), b);
}

void fn_8018F38C(int a, int b)
{
    fn_801FCE10(0, "use \x8c update 'NUAG' set 'FDTG' = 0 where 'DIGT' = \x85\n", fn_8022F3D4(fn_8022F358(a)), b);
}

int fn_8018F3D8(int a)
{
    int lttg;

    fn_801FCE10(0, "use \x8c select 'LTTG' into \x82 from 'MTTG'\n", fn_8022F3D4(fn_8022F358(a)), &lttg);
    return lttg;
}

void fn_8018F41C(int a)
{
    int i;

    for (i = 1; i <= 32; i++) {
        fn_8018F38C(a, i);
    }
    fn_8018F488(a);
    fn_8018F38C(a, 34);
    fn_8018F2F4(a, 1023);
    fn_8018F9B4(a);
}

void fn_8018F488(int a)
{
    fn_801FCE10(0, "use \x8c update 'MTTG' set 'LTTG' = 32\n", fn_8022F3D4(fn_8022F358(a)));
}

void fn_8018F4C4(int a)
{
    int lttg = fn_8018F3D8(a) - 1;
    int digt = fn_8018F228(a);

    fn_801FCE10(0, "use \x8c update 'MTTG' set 'LTTG' = \x82 where 'DIGT' = \x85\n",
                fn_8022F3D4(fn_8022F358(a)), lttg, digt);
}

void fn_8018F52C(Object_8007A334 *pObject, int a)
{
    fn_8007A334(pObject, 0x41545347, 0x4E575347, 0, 0, fn_8022F3D4(fn_8022F358(a)));
}

void fn_8018F584(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_8018F5A4(Object_8007A334 *pObject, int index)
{
    switch (index) {
    case 0:
        return fn_8007A98C(pObject, 0x4E575347);
    case 1:
        return fn_8007A98C(pObject, 0x534C5347);
    case 14:
        return fn_8007A934(pObject, 0x54535347);
    case 13:
        return fn_8007A98C(pObject, 0x46505347);
    case 2:
        return fn_8007A98C(pObject, 0x50545347);
    case 3:
        return fn_8007A98C(pObject, 0x54525347);
    case 4:
        return fn_8007A98C(pObject, 0x54505347);
    case 5:
        return fn_8007A98C(pObject, 0x54445347);
    case 6:
        return fn_8007A98C(pObject, 0x53445347);
    case 7:
        return fn_8007A98C(pObject, 0x41535347);
    case 8:
        return fn_8007A98C(pObject, 0x49445347);
    case 9:
        return fn_8007A98C(pObject, 0x46465347);
    case 11:
        return fn_8007A98C(pObject, 0x42475347);
    case 12:
        return fn_8007A98C(pObject, 0x32475347);
    case 10:
        return fn_8007A98C(pObject, 0x44465347);
    }
    return -1;
}

void fn_8018F6C0(Object_8007A334 *pObject, int index, int delta)
{
    switch (index) {
    case 0:
        if (delta) {
            fn_8007ABA4(pObject, 0x4E575347, fn_8007A98C(pObject, 0x4E575347) + 1);
            if (fn_8007A934(pObject, 0x54535347) < 0) {
                fn_8007AA90(pObject, 0x54535347, 1);
            } else {
                fn_8007AA90(pObject, 0x54535347, fn_8007A934(pObject, 0x54535347) + 1);
            }
        } else {
            fn_8007ABA4(pObject, 0x534C5347, fn_8007A98C(pObject, 0x534C5347) + 1);
            if (fn_8007A934(pObject, 0x54535347) > 0) {
                fn_8007AA90(pObject, 0x54535347, -1);
            } else {
                fn_8007AA90(pObject, 0x54535347, fn_8007A934(pObject, 0x54535347) - 1);
            }
        }
        break;
    case 13:
        fn_8007ABA4(pObject, 0x46505347, fn_8007A98C(pObject, 0x46505347) + delta);
        break;
    case 2:
        fn_8007ABA4(pObject, 0x50545347, fn_8007A98C(pObject, 0x50545347) + delta);
        break;
    case 3:
        fn_8007ABA4(pObject, 0x54525347, fn_8007A98C(pObject, 0x54525347) + delta);
        break;
    case 4:
        fn_8007ABA4(pObject, 0x54505347, fn_8007A98C(pObject, 0x54505347) + delta);
        break;
    case 5:
        fn_8007ABA4(pObject, 0x54445347, fn_8007A98C(pObject, 0x54445347) + delta);
        break;
    case 6:
        fn_8007ABA4(pObject, 0x53445347, fn_8007A98C(pObject, 0x53445347) + delta);
        break;
    case 7:
        fn_8007ABA4(pObject, 0x41535347, fn_8007A98C(pObject, 0x41535347) + delta);
        break;
    case 8:
        fn_8007ABA4(pObject, 0x49445347, fn_8007A98C(pObject, 0x49445347) + delta);
        break;
    case 9:
        fn_8007ABA4(pObject, 0x46465347, fn_8007A98C(pObject, 0x46465347) + delta);
        break;
    case 11:
        fn_8007ABA4(pObject, 0x42475347, fn_8007A98C(pObject, 0x42475347) + delta);
        break;
    case 12:
        fn_8007ABA4(pObject, 0x32475347, fn_8007A98C(pObject, 0x32475347) + delta);
        break;
    case 10:
        fn_8007ABA4(pObject, 0x44465347, fn_8007A98C(pObject, 0x44465347) + delta);
        break;
    }
}

void fn_8018F9B4(int a)
{
    Object_8007A334 object;

    fn_8018F52C(&object, a);
    fn_8007ABA4(&object, 0x4E575347, 0);
    fn_8007AA90(&object, 0x54535347, 0);
    fn_8007ABA4(&object, 0x534C5347, 0);
    fn_8007AA90(&object, 0x54535347, 0);
    fn_8007ABA4(&object, 0x46505347, 0);
    fn_8007ABA4(&object, 0x50545347, 0);
    fn_8007ABA4(&object, 0x54525347, 0);
    fn_8007ABA4(&object, 0x54505347, 0);
    fn_8007ABA4(&object, 0x54445347, 0);
    fn_8007ABA4(&object, 0x53445347, 0);
    fn_8007ABA4(&object, 0x41535347, 0);
    fn_8007ABA4(&object, 0x49445347, 0);
    fn_8007ABA4(&object, 0x46465347, 0);
    fn_8007ABA4(&object, 0x42475347, 0);
    fn_8007ABA4(&object, 0x32475347, 0);
    fn_8007ABA4(&object, 0x44465347, 0);
    fn_8018F584(&object);
}

void fn_8018FB4C(Object_8007A334 *pObject, int type)
{
    switch (type) {
    case 0:
        fn_8007A334(pObject, 0x54504B54, 0x44494B54, 0, 0, 0x54415453);
        break;
    case 1:
        fn_8007A334(pObject, 0x43435054, 0x44494B54, 0, 0, 0x54415453);
        break;
    }
}

void fn_8018FBC8(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_8018FBE8(Object_8007A334 *pObject, int id)
{
    return fn_8007A7F4(pObject, 0x44494B54, id, 0, 0);
}

void fn_8018FC1C(Object_8007A334 *pObject, Record_8018FC1C *pRecord)
{
    pRecord->mUnknown0 = 1;
    pRecord->mUnknown1 = fn_8007A98C(pObject, 0x50554B54);
    pRecord->mUnknown2 = fn_8007A98C(pObject, 0x565A4B54);
    pRecord->mUnknown4 = fn_8007A98C(pObject, 0x54504B54);
    pRecord->mUnknown8 = fn_8007A98C(pObject, 0x42474B54);
    pRecord->mUnknown12 = fn_8007A98C(pObject, 0x47534B54);
    pRecord->mUnknown16 = fn_8007A934(pObject, 0x43534B54);
    pRecord->mUnknown20 = fn_8007A98C(pObject, 0x54534B54);
    pRecord->mUnknown24 = fn_8007A9E4(pObject, 0x49444B54);
    pRecord->mUnknown28 = fn_8007A98C(pObject, 0x4E414B54);
    pRecord->mUnknown32 = fn_8007A98C(pObject, 0x4F434B54);
    pRecord->mUnknown36 = fn_8007A98C(pObject, 0x4C424B54);
    pRecord->mUnknown40 = fn_8007A98C(pObject, 0x59544B54);
    pRecord->mUnknown44 = fn_8007A98C(pObject, 0x4E534B54);
    pRecord->mUnknown48 = fn_8007A98C(pObject, 0x4E4C4B54);
}
}
