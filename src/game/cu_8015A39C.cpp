#include "game/Object_8015C244.h"

extern "C" {
extern unsigned char lbl_803ECA68;
extern unsigned int lbl_803ECA64;

void fn_8015C218(Object_8015C244 *p)
{
    p->mUnknown80 = 0;
    p->mUnknown81 = 0;
    p->mUnknown84 = 10;
    p->mpUnknown208 = 0;
    --lbl_803ECA64;
}

void fn_8015C244(Object_8015C244 *p)
{
    p->mUnknown48 = 0.6f;
}

void fn_8015C254(int value)
{
    lbl_803ECA68 = value;
}
}
