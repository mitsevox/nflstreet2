#include "game/Class_8018FD64.h"
#include "game/Class_802938C0.h"

Class_8018FD64::Class_8018FD64() {}

Class_8018FD64::~Class_8018FD64()
{
    if (mObject.mUnknown0 != 0) {
        fn_8018FE10();
    }
}

void Class_8018FD64::fn_8018FDEC(int a, int b, void *c, void *d, int e)
{
    fn_8007A334(&mObject, a, b, c, d, e);
}

void Class_8018FD64::fn_8018FE10()
{
    fn_8007A3C4(&mObject);
}

int Class_8018FD64::fn_8018FE34()
{
    return fn_8007A410(&mObject);
}

int Class_8018FD64::fn_8018FE58()
{
    return fn_8007A43C(&mObject);
}

int Class_8018FD64::fn_8018FE7C()
{
    return fn_8007A444(&mObject);
}

int Class_8018FD64::fn_8018FEA0()
{
    return fn_8007A4A4(&mObject);
}

int Class_8018FD64::fn_8018FEC4()
{
    return fn_8007A510(&mObject);
}

int Class_8018FD64::fn_8018FEE8()
{
    return fn_8007A588(&mObject);
}

int Class_8018FD64::fn_8018FF0C(int a)
{
    return fn_8007A600(&mObject, a);
}

int Class_8018FD64::fn_8018FF30(int a, int b, int c, int *pResult)
{
    return fn_8007A7F4(&mObject, a, b, c, pResult);
}

int Class_8018FD64::fn_8018FF54(int a, int b, int c, int *pResult)
{
    return fn_8007A894(&mObject, a, b, c, pResult);
}

int Class_8018FD64::fn_8018FF78(int column)
{
    return fn_8007A934(&mObject, column);
}

int Class_8018FD64::fn_8018FF9C(int column)
{
    return fn_8007A98C(&mObject, column);
}

float Class_8018FD64::fn_8018FFC0(int column)
{
    return fn_8007A9E4(&mObject, column);
}

void Class_8018FD64::fn_8018FFE4(int a, int b, int c)
{
    fn_8007AA3C(&mObject, a, b, c);
}

void Class_8018FD64::fn_80190008(int column, int value)
{
    fn_8007AA90(&mObject, column, value);
}

void Class_8018FD64::fn_8019002C(int column, int value)
{
    fn_8007ABA4(&mObject, column, value);
}

void Class_8018FD64::fn_80190050(int column, float value)
{
    fn_8007ACB8(&mObject, column, value);
}

void Class_8018FD64::fn_80190074(int column, char *pText, int length)
{
    fn_8007ADD4(&mObject, column, pText, length);
}

void Class_802938C0::fn_80190098()
{
    fn_8018FDEC(0x52484346, -1, 0, 0, 0x54415453);
}

int Class_802938C0::fn_801900D4(int id, int *pResult)
{
    return fn_8018FF54(0x48464650, id, 0, pResult);
}

int Class_802938C0::fn_80190120()
{
    return fn_8018FF78(0x48464650);
}

void Class_802938C0::fn_8019015C(char *pBuffer, int size)
{
    fn_8018FFE4(0x43444846, (int)pBuffer, size);
}

int Class_802938C0::fn_801901A4()
{
    switch (fn_8018FF78(0x54534846)) {
    case 0:
        return 106;
    case 1:
        return 107;
    default:
        return 105;
    }
}
