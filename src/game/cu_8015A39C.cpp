#include "game/Object_80039F5C.h"

struct Object_8015C244 {
    char mUnknown0[48];
    float mUnknown48;
    char mUnknown52[28];
    unsigned char mUnknown80;
    unsigned char mUnknown81;
    char mUnknown82[2];
    unsigned int mUnknown84;
    char mUnknown88[120];
    Object_80039F5C *mpUnknown208;
};

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
