#include "game/Object_8015C244.h"

extern "C" {
void fn_8003F66C(void *p);
void fn_8003F6B0(void *p);
void fn_8003F6B4(void *p, float (*pData)[3], int a);
void fn_8003F6C8(void *p, unsigned char a, unsigned char b, unsigned char c);
void fn_8003F6D8(void *p, float value);
void fn_8003F6E0(void *p, float value);
void fn_8003F6E8(void *p, float value);
int fn_801784C4(void);

void fn_8015A248(Object_8015C244 *p, float *pOut)
{
    Object_80039F5C *pObject = p->mpUnknown208;

    pOut[0] = pObject->mMotion.mPos.mX;
    pOut[1] = pObject->mMotion.mPos.mY;
    p->mUnknown68 = pOut[0];
    p->mUnknown72 = pOut[1];
    if (fn_801784C4()) {
        pOut[1] = -pOut[1];
        pOut[0] = -pOut[0];
    }
}

void fn_8015A2B4(Object_8015C244 *p)
{
    p->mpUnknown208 = 0;
    fn_8003F66C(p->mUnknown20);
    fn_8003F6B4(p->mUnknown20, p->mUnknown88, 10);
    fn_8003F6D8(p->mUnknown20, 0.1f);
    fn_8003F6C8(p->mUnknown20, 0x80, 0x80, 0);
    fn_8003F6E0(p->mUnknown20, 4.0f);
    fn_8003F6E8(p->mUnknown20, 1.0f);
    p->mUnknown80 = 0;
    p->mUnknown81 = 0;
    p->mUnknown84 = 10;
}

void fn_8015A354(Object_8015C244 *p)
{
    fn_8003F6B0(p->mUnknown20);
    p->mpUnknown208 = 0;
    p->mUnknown80 = 0;
    p->mUnknown81 = 0;
    p->mUnknown84 = 10;
}
}
