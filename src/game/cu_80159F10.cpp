#include <math.h>
#include "engine/cu_80227F14.h"
#include "game/Camera_8013F738.h"
#include "game/Object_80039F5C.h"

struct Init_80159F10 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
};

struct Instance_80159F10 {
    char mPad00[4];
    Vector_80039F5C mUnknown04;
    char mPad10[4];
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C;
    unsigned char mUnknown1D;
    char mPad1E[2];
    float mUnknown20;
};

extern "C" {
int fn_8002B5A8(void);
int fn_8006560C(void);
int fn_8013F9F8(void);
Camera_8013F738 *fn_8013FA04(int index);
int fn_801481B0(void);
int fn_8014830C(int index, Vector_80039F5C *pOut);
int fn_801483F8(void);
float fn_80178A44(void);
void fn_8019FBEC(void);
void fn_8019FD38(void);
void fn_8019FD80(Instance_80159F10 *pInstance);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0CFC(float a);
int fn_801DCF0C(int a, int b, int c, void (*pA)(Instance_80159F10 *, const Init_80159F10 *), void (*pB)(void));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(Instance_80159F10 *));
int fn_801DD268(int handle, int a, int b, Init_80159F10 *pInit);
void fn_801DD320(int handle, int a);
void fn_801DD3AC(int handle, int a, int b);
void fn_8015A240(Instance_80159F10 *pInstance, unsigned char value);
}

static unsigned char lbl_803ECA5C;

extern "C" void fn_80159F10(Instance_80159F10 *pInstance, const Init_80159F10 *pInit)
{
    pInstance->mUnknown04.mX = 0.0f;
    pInstance->mUnknown04.mY = 0.0f;
    pInstance->mUnknown04.mZ = 0.01f;
    pInstance->mUnknown14 = pInit->mUnknown0;
    pInstance->mUnknown18 = pInit->mUnknown4;
    pInstance->mUnknown1C = pInit->mUnknown8;
    fn_8015A240(pInstance, 2);
}

extern "C" void fn_80159F70(void) {}

extern "C" int fn_80159F74(Instance_80159F10 *pInstance)
{
    if ((fn_801481B0() == 1 || fn_801483F8() == 1) && lbl_803ECA5C == 1 && fn_8006560C() == 0) {
        Vector_80039F5C *pPos = &pInstance->mUnknown04;
        if (fn_8014830C(pInstance->mUnknown1C, pPos) == 1) {
            Camera_8013F738 *pCamera;
            float scale = 1.0f;
            Vector_80039F5C pos;

            pCamera = fn_8013FA04(fn_8013F9F8());
            scale = fabsf(pInstance->mUnknown04.mY - pCamera->mHeader.mUnknown04[1]) / (fn_80178A44() * 2.0f) * 2.0f + 0.3f;
            fn_801D0470(fn_80228668());
            fn_801D04C4();
            pos = *pPos;
            pos.mZ += scale * 0.5;
            fn_801D0C58(&pos);
            fn_801D0ADC(-pCamera->mHeader.mUnknown1C);
            fn_801D08FC(0xC00000 - pCamera->mHeader.mUnknown14);
            pInstance->mUnknown20 = fn_801481B0() ? 1.0f : 0.4f;
            fn_801D0CFC(scale);
            fn_8019FD80(pInstance);
            fn_801D0470(fn_80228668());
            fn_801D0544();
        }
    }
    return 0;
}

extern "C" void fn_8015A0D0(int value)
{
    if (fn_8002B5A8()) {
        lbl_803ECA5C = value;
    } else {
        lbl_803ECA5C = 0;
    }
}

extern "C" void fn_8015A110(int handle)
{
    fn_801DCF0C(12, 36, 3, fn_80159F10, fn_80159F70);
    fn_801DD0C8(handle, 12, 0, fn_80159F74);
    fn_8019FBEC();
    lbl_803ECA5C = 1;
}

extern "C" void fn_8015A17C(void)
{
    fn_80228E18();
    fn_8019FD38();
    fn_801DCF8C(12);
}

extern "C" int fn_8015A1A8(int handle, unsigned char c, int a, int b)
{
    Init_80159F10 init;
    int id;

    init.mUnknown0 = a;
    init.mUnknown4 = b;
    init.mUnknown8 = c;
    id = fn_801DD268(handle, 12, 0, &init);
    fn_801DD3AC(handle, id, 11);
    return id;
}

extern "C" void fn_8015A204(int handle, int id)
{
    if (id != 0) {
        fn_801DD320(handle, id);
        fn_80228D58(id);
    }
}

extern "C" void fn_8015A240(Instance_80159F10 *pInstance, unsigned char value)
{
    pInstance->mUnknown1D = value;
}
