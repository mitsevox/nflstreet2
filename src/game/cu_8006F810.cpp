#include "game/Object_80039F5C.h"

extern "C" {

void fn_8006CA18(int index, int value, unsigned char volume);
int fn_8006C854(int index, Vector_80039F5C *p);

extern unsigned char lbl_803EA6CC;
extern unsigned char lbl_803EA6CD;
extern unsigned char lbl_803EA6CE;
extern unsigned char lbl_803EA6F9;
extern unsigned char lbl_803EA6D9;
extern unsigned char lbl_803EA6DA;

void fn_8006F810(void)
{
    lbl_803EA6CC = lbl_803EA6CD = 1;
}

void fn_8006F820(void)
{
}

void fn_8006F824(int value)
{
    fn_8006CA18(5, value, 0);
}

void fn_800711DC(int value)
{
}

void fn_80071344(void)
{
}

void fn_80071348(void)
{
}

void fn_80071790(void)
{
}

int fn_80071974(Vector_80039F5C *p)
{
    lbl_803EA6D9 = 0;
    return fn_8006C854(34, p);
}

int fn_800719A4(Vector_80039F5C *p)
{
    lbl_803EA6DA = 0;
    return fn_8006C854(35, p);
}

void fn_800719D4(void)
{
    fn_8006CA18(lbl_803EA6D9 + 34, 100, 0);
}

int fn_80071BA0(int a, int value)
{
    switch (value) {
    case 3:
        return 105;
    case 9:
        return 111;
    case 10:
        return 108;
    default:
        return 105;
    }
}

int fn_80071BDC(int value)
{
    int result = 42;
    switch (value) {
    case 0:
    case 1:
    case 8:
        result = 44;
        break;
    case 2:
    case 3:
        break;
    case 4:
    case 6:
        result = 43;
        break;
    default:
        result = 44;
        break;
    }
    return result;
}

void fn_80071C2C(int value)
{
    lbl_803EA6CE = value;
}

void fn_80071C34(int value)
{
    lbl_803EA6F9 = value;
}

}
