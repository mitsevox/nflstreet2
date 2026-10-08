/* Partial comparison source for the inferred grouping 0x8003F66C-0x8003FE90.
   Not a recovered original file. The original assembly stays linked; only the
   bodies below are compiled and measured. */

/* Record reached through the first argument of fn_8003F66C-fn_8003F754.
   Only the accessed fields are declared; the size is unknown. */
struct Object_8003F66C {
    int mUnknown0;
    int mUnknown4;
    float (*mpUnknown8)[3];
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    float mUnknown28;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    unsigned char mUnknown34;
    char mUnknown35[1];
    float mUnknown36;
    float mUnknown40;
    unsigned char mUnknown44;
};

/* Object passed to fn_8003F91C (also the r3 of fn_8003F768 and fn_8003FBF0,
   which test and set the same word +20). Only the accessed field is
   declared; the size is unknown. */
struct Object_8003F768 {
    char mUnknown0[20];
    int mUnknown20;
};

extern "C" {
void fn_8019CEE8(Object_8003F768 *p);
void fn_8019CFD0(Object_8003F768 *p);
void fn_801DCF8C(int type);
void fn_801DD320(int handle, int item);
}

#include "engine/cu_80227F14.h"

extern "C" void fn_8003F6B0(Object_8003F66C *p)
{
}

extern "C" void fn_8003F6B4(Object_8003F66C *p, float (*pData)[3], int a)
{
    p->mpUnknown8 = pData;
    p->mUnknown0 = 0;
    p->mUnknown4 = a;
}

extern "C" void fn_8003F6C8(Object_8003F66C *p, unsigned char a, unsigned char b, unsigned char c)
{
    p->mUnknown32 = a;
    p->mUnknown33 = b;
    p->mUnknown34 = c;
}

extern "C" void fn_8003F6D8(Object_8003F66C *p, float value)
{
    p->mUnknown28 = value;
}

extern "C" void fn_8003F6E0(Object_8003F66C *p, float value)
{
    p->mUnknown36 = value;
}

extern "C" void fn_8003F6E8(Object_8003F66C *p, float value)
{
    p->mUnknown40 = value;
}

extern "C" void fn_8003F6F0(Object_8003F66C *p, float *pValue)
{
    p->mpUnknown8[p->mUnknown0][0] = pValue[0];
    p->mpUnknown8[p->mUnknown0][1] = pValue[1];
    p->mpUnknown8[p->mUnknown0][2] = pValue[2];
    p->mUnknown0++;
}

extern "C" void fn_8003F744(Object_8003F66C *p)
{
    p->mUnknown0 = 0;
    p->mUnknown44 = 0;
}

extern "C" void fn_8003F754(Object_8003F66C *p, int a, int b, float c, float d)
{
    p->mUnknown12 = a;
    p->mUnknown16 = c;
    p->mUnknown20 = d;
    p->mUnknown24 = b;
}

extern "C" void fn_8003F91C(Object_8003F768 *p)
{
    fn_8019CFD0(p);
    if (!(p->mUnknown20 & 4)) {
        fn_8019CEE8(p);
    }
}

extern "C" void fn_8003FB2C(void)
{
    fn_80228E18();
    fn_801DCF8C(3);
}

extern "C" void fn_8003FBB4(int handle, int item)
{
    if (item) {
        fn_801DD320(handle, item);
        fn_80228D58(item);
    }
}

extern "C" int fn_8003FC68(void)
{
    return 212;
}
