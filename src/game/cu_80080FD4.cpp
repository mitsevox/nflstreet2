#include "game/Object_8007A334.h"

extern "C" {

extern const int lbl_80293968[];

void fn_80080FD4(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x52414850, value);
}

void fn_80081000(Object_8007A334 *pObject, int index)
{
    fn_8007ABA4(pObject, 0x54425950, index);
    fn_8007AA90(pObject, 0x544C4650, lbl_80293968[index]);
}

void fn_8008105C(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x494B5350, value);
}

void fn_80081088(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x58454C50, value);
}

void fn_800810B4(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x31414850, value);
}

int fn_800810E0(void *pObject)
{
    return fn_8007A98C(pObject, 0x31414850);
}

void fn_80081108(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x43484650, value);
}

int fn_80081134(void *pObject)
{
    return fn_8007A98C(pObject, 0x43484650);
}

void fn_8008115C(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x54475750, value - 160);
}

int fn_80081188(void *pObject)
{
    return fn_8007A98C(pObject, 0x54475750) + 160;
}

void fn_800811B4(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x54474850, value);
}

int fn_800811E0(void *pObject)
{
    return fn_8007A98C(pObject, 0x54474850);
}

int fn_80081208(void *pObject)
{
    return fn_8007A98C(pObject, 0x4E414850);
}

void fn_80081230(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E414850, value);
}

int fn_8008125C(void *pObject)
{
    return fn_8007A98C(pObject, 0x4E454A50);
}

void fn_80081284(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E454A50, value);
}
}
