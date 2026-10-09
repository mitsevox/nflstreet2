#include "engine/cu_80227F14.h"
#include "engine/vptmanager.h"
#include "game/GameVpt.h"
#include "game/InGame.h"
#include "game/Object_80039F5C.h"
#include "game/Instance_801614D0.h"
#include "game/Entry_802F394C.h"


/* Item of the type-6 pool of src/game/cu_80046340.cpp. */
struct Object_80046340 {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown10[4];
    int mUnknown14;
    char mUnknown18[8];
    int mUnknown20;
    Object_80235588 mUnknown24[9];
    Object_80235588 mUnknown6E4[10];
    char mUnknownE64[0x30];
};

/* Item of the type-25 pool of src/game/cu_80046340.cpp. */
struct Object_800463D8 {
    char mUnknown0[0x14];
    Object_80046340 *mpUnknown14;
};

struct View_8002B550 {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
};

extern "C" {
unsigned char fn_80147E80(int index);
void fn_801985FC(void);
void fn_801A5780(void);
void fn_801987F4(void);
int fn_800A262C(void);
int fn_800A26C4(void);
int fn_800A34B0(void);
int fn_800A34BC(void);
int fn_801C657C(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *p);
void fn_80210388(void);
void fn_802353D8(Object_80235588 *p, int flags);
void fn_802353F8(Object_80235588 *p, int flags);
void fn_80235510(Object_80235588 *p, int a);
void fn_80235588(Object_80235588 *p, int a);
void fn_802355E4(Object_80235588 *p);
void fn_80235630(Object_80235588 *p, int handle);
void fn_80235740(Object_80235588 *p, int handle);
void fn_80235764(Object_80235588 *p, int handle);
void fn_80235B6C(Object_80235588 *p, void *pElement, int a);
void fn_80235C48(Object_80235588 *p, int a);
void fn_80235C90(Object_80235588 *p, int a, float b, float c, float d, float e);
void fn_80235D0C(Object_80235588 *p, int a);
void fn_80235D10(Object_80235588 *p, float a);
void fn_80235D78(Vector_80039F5C *p);
void fn_80236DD8(Object_80228224 *p);
void fn_80236DE0(int a);
void fn_80236E04(float a, float b);
void fn_80236E2C(int r, int g, int b);
int fn_80236EC0(int a);
void fn_80236EFC(float a);
}

static Entry_802F394C lbl_802F394C[12] = {
    { 350.0f, 4000.0f, 4, 0.45f, 0xBEA0A0 },
    { 55.0f, 600.0f, 4, 0.12f, 0x453D3D },
    { 350.0f, 4000.0f, 4, 0.6f, 0xD2CC60 },
    { 45.0f, 7000.0f, 4, 0.6f, 0xB89584 },
    { 50.0f, 7000.0f, 4, 0.2f, 0xAA7444 },
    { 40.0f, 3500.0f, 4, 0.75f, 0x4C9C73 },
    { 90.0f, 5000.0f, 4, 0.25f, 0x5082C8 },
    { 350.0f, 1500.0f, 4, 0.1f, 0x453D3D },
    { 5.0f, 7500.0f, 4, 0.25f, 0x846039 },
    { 280.0f, 5500.0f, 4, 0.13f, 0x4B9FC8 },
    { 35.0f, 2000.0f, 5, 0.4f, 0xD4A895 },
    { 30.0f, 1600.0f, 5, 0.3f, 0x846039 },
};
static float lbl_803EB840 = 0.0001f;

extern "C" {
void fn_801A5478(Instance_801614D0 *pInstance)
{
    Object_80235588 *pLayer = &pInstance->mUnknown48;
    int handle = pInstance->mUnknown14;
    char *pElement = pInstance->mUnknown18;

    fn_80235588(pLayer, 0);
    fn_80235630(pLayer, handle);
    fn_80235B6C(pLayer, pElement, 1);
    fn_802353F8(pLayer, 0);
    fn_802353D8(pLayer, 0x400008);
    fn_80235588(&pInstance->mUnknown108, 0);
    fn_80235630(&pInstance->mUnknown108, handle);
    fn_80235B6C(&pInstance->mUnknown108, pElement, 1);
    fn_802353F8(&pInstance->mUnknown108, 0x2000000);
    fn_802353D8(&pInstance->mUnknown108, 0x40020A);
    fn_801A5780();
}

void fn_801A553C(Instance_801614D0 *pInstance)
{
    fn_80236DE0(0);
    fn_80236EC0(0);
}

void fn_801A5568(Instance_801614D0 *pInstance, int unused)
{
    int handle = fn_801C657C();

    fn_80210388();
    fn_80235C90(&pInstance->mUnknown48, 0, 0.5f, 0.5f, 0.5f, 0.51f);
    fn_80235C90(&pInstance->mUnknown48, 1, 0.5f, 0.5f, 0.5f, 0.51f);
    fn_80235C90(&pInstance->mUnknown108, 0, 0.5f, 0.5f, 0.5f, 0.51f);
    fn_80235C90(&pInstance->mUnknown108, 1, 0.5f, 0.5f, 0.5f, 0.51f);
    fn_801D0470(fn_80228668());
    fn_801D04C4();
    fn_801D0C58(&pInstance->mUnknown4);
    fn_80235740(&pInstance->mUnknown48, handle);
    fn_80235764(&pInstance->mUnknown48, handle);
    fn_80235740(&pInstance->mUnknown108, handle);
    fn_80235764(&pInstance->mUnknown108, handle);
    fn_801D0470(fn_80228668());
    fn_801D0544();
}

Entry_802F394C *fn_801A566C(int index)
{
    Entry_802F394C *pEntry;

    switch (index) {
    case 0:
        pEntry = &lbl_802F394C[0];
        break;
    case 2:
        pEntry = &lbl_802F394C[1];
        break;
    case 3:
        pEntry = &lbl_802F394C[2];
        break;
    case 1:
        pEntry = &lbl_802F394C[3];
        break;
    case 7:
        pEntry = &lbl_802F394C[4];
        break;
    case 6:
        pEntry = &lbl_802F394C[5];
        break;
    case 8:
        pEntry = &lbl_802F394C[6];
        break;
    case 9:
        pEntry = &lbl_802F394C[7];
        break;
    case 4:
        pEntry = &lbl_802F394C[9];
        break;
    case 5:
        pEntry = &lbl_802F394C[8];
        break;
    case 10:
        pEntry = &lbl_802F394C[10];
        break;
    case 11:
        pEntry = &lbl_802F394C[11];
        break;
    default:
        pEntry = &lbl_802F394C[0];
        break;
    }
    return pEntry;
}

void fn_801A5780(void)
{
    Entry_802F394C *pEntry = fn_800A34EC();
    unsigned int color = fn_800A3410() & 0xFFFFFF;
    float density = fn_800A3400();

    if (density > 0.0f) {
        fn_80236DE0(pEntry->mUnknown8);
    } else {
        fn_80236DE0(0);
    }
    if (fn_8002894C()) {
        fn_80236DD8(GameVpt::fn_800293A8());
    }
    fn_80236E2C(color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF);
    fn_80236E04(pEntry->mUnknown0, pEntry->mUnknown4);
    fn_80236EFC(density);
    fn_80236EC0(1);
}

void fn_801A582C(Object_80046340 *pObject)
{
    unsigned int i;

    fn_80235588(&pObject->mUnknown24[2], 6);
    fn_80235630(&pObject->mUnknown24[2], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[2], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[2], 4);
    fn_802353D8(&pObject->mUnknown24[2], 0x303);
    fn_80235D0C(&pObject->mUnknown24[2], 0x60);
    fn_802353F8(&pObject->mUnknown24[2], 0);

    fn_80235588(&pObject->mUnknown24[5], 6);
    fn_80235630(&pObject->mUnknown24[5], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[5], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[5], 4);
    fn_802353D8(&pObject->mUnknown24[5], 0x303);
    fn_80235D0C(&pObject->mUnknown24[5], 0x60);
    fn_802353F8(&pObject->mUnknown24[5], 0x200);

    fn_80235588(&pObject->mUnknown24[6], 6);
    fn_80235630(&pObject->mUnknown24[6], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[6], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[6], 4);
    fn_802353D8(&pObject->mUnknown24[6], 0x303);
    fn_80235D0C(&pObject->mUnknown24[6], 0x60);
    fn_802353F8(&pObject->mUnknown24[6], 0x400);

    fn_80235588(&pObject->mUnknown24[3], 6);
    fn_80235630(&pObject->mUnknown24[3], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[3], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[3], 4);
    fn_80235D0C(&pObject->mUnknown24[3], 0x10);
    fn_802353F8(&pObject->mUnknown24[3], 1);
    fn_80235D10(&pObject->mUnknown24[3], 1.0f);
    fn_802353D8(&pObject->mUnknown24[3], 0x303);

    fn_80235588(&pObject->mUnknown24[0], 6);
    fn_80235630(&pObject->mUnknown24[0], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[0], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[0], 4);
    fn_80235D0C(&pObject->mUnknown24[0], 0x60);
    fn_802353F8(&pObject->mUnknown24[0], 0x2000000);
    fn_802353D8(&pObject->mUnknown24[0], 0x303);

    fn_80235588(&pObject->mUnknown24[4], 6);
    fn_80235630(&pObject->mUnknown24[4], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[4], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[4], 4);
    fn_80235D0C(&pObject->mUnknown24[4], 0x60);
    fn_802353F8(&pObject->mUnknown24[4], 0x4000000);
    fn_802353D8(&pObject->mUnknown24[4], 0x303);

    fn_80235588(&pObject->mUnknown24[1], 6);
    fn_80235630(&pObject->mUnknown24[1], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[1], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[1], 4);
    fn_80235D0C(&pObject->mUnknown24[1], 0x60);
    fn_802353F8(&pObject->mUnknown24[1], 0x2000);
    fn_802353D8(&pObject->mUnknown24[1], 0x800303);

    fn_80235588(&pObject->mUnknown24[7], 6);
    fn_80235630(&pObject->mUnknown24[7], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[7], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[7], 4);
    fn_802353F8(&pObject->mUnknown24[7], 0x10000000);
    fn_802353D8(&pObject->mUnknown24[7], 0x100502);

    fn_80235588(&pObject->mUnknown24[8], 6);
    fn_80235630(&pObject->mUnknown24[8], pObject->mUnknown20);
    fn_80235B6C(&pObject->mUnknown24[8], pObject->mUnknownE64, 1);
    fn_80235C48(&pObject->mUnknown24[8], 4);
    fn_802353F8(&pObject->mUnknown24[8], 0x20000000);
    fn_802353D8(&pObject->mUnknown24[8], 0x20050A);

    for (i = 0; i < 9; i++) {
        fn_80235C90(&pObject->mUnknown24[i], 0, 1.0f, 1.0f, 1.0f, 0.51f);
        fn_80235C90(&pObject->mUnknown24[i], 1, 1.0f, 1.0f, 1.0f, 0.51f);
    }
    for (i = 0; i < 10; i++) {
        fn_80235588(&pObject->mUnknown6E4[i], 6);
        fn_80235630(&pObject->mUnknown6E4[i], pObject->mUnknown20);
        fn_80235B6C(&pObject->mUnknown6E4[i], pObject->mUnknownE64, 1);
        fn_80235C48(&pObject->mUnknown6E4[i], 4);
        fn_80235510(&pObject->mUnknown6E4[i], i + 7);
        fn_802353D8(&pObject->mUnknown6E4[i], 0x24050A);
        fn_80235C90(&pObject->mUnknown6E4[i], 0, 1.0f, 1.0f, 1.0f, 0.51f);
        fn_80235C90(&pObject->mUnknown6E4[i], 1, 1.0f, 1.0f, 1.0f, 0.51f);
    }
    pObject->mUnknown14 = 0;
}

void fn_801A5CA4(Object_80046340 *pObject)
{
    unsigned int i;

    for (i = 0; i < 9; i++) {
        fn_802355E4(&pObject->mUnknown24[i]);
    }
    for (i = 0; i < 10; i++) {
        fn_802355E4(&pObject->mUnknown6E4[i]);
    }
}

int fn_801A5D0C(Object_800463D8 *pOwner)
{
    Object_80046340 *pObject = pOwner->mpUnknown14;
    int handle = fn_801C657C();
    float alpha = 0.1f;

    fn_801D0470(fn_80228668());
    fn_801D04C4();
    fn_801D0C58(&pObject->mUnknown4);
    fn_80235D78(&((View_8002B550 *)fn_8002B550(0))->mUnknown4);
    if (fn_80147E80(1) == 0) {
        fn_80235740(&pObject->mUnknown24[0], handle);
        fn_80235764(&pObject->mUnknown24[0], handle);
        fn_80235740(&pObject->mUnknown24[8], handle);
        fn_80235764(&pObject->mUnknown24[8], handle);
    }
    if (fn_800A262C()) {
        fn_80235C90(&pObject->mUnknown24[6], 0, 1.0f, 1.0f, 1.0f, alpha);
        fn_80235C90(&pObject->mUnknown24[6], 1, 1.0f, 1.0f, 1.0f, alpha);
        fn_80235740(&pObject->mUnknown24[6], handle);
        fn_80235764(&pObject->mUnknown24[6], handle);
    }
    if (fn_800A26C4()) {
        fn_80235C90(&pObject->mUnknown24[5], 0, 1.0f, 1.0f, 1.0f, alpha);
        fn_80235C90(&pObject->mUnknown24[5], 1, 1.0f, 1.0f, 1.0f, alpha);
        fn_80235740(&pObject->mUnknown24[5], handle);
        fn_80235764(&pObject->mUnknown24[5], handle);
    }
    fn_801D0470(fn_80228668());
    fn_801D0544();
    return 0;
}

int fn_801A5E90(Object_80046340 *pObject)
{
    int handle = fn_801C657C();
    unsigned int i;

    fn_801D0470(fn_80228668());
    fn_801D04C4();
    fn_801D0C58(&pObject->mUnknown4);
    fn_80235D78(&((View_8002B550 *)fn_8002B550(0))->mUnknown4);
    fn_80235740(&pObject->mUnknown24[4], handle);
    fn_80235764(&pObject->mUnknown24[4], handle);
    fn_80235740(&pObject->mUnknown24[1], handle);
    fn_80235764(&pObject->mUnknown24[1], handle);
    fn_80235740(&pObject->mUnknown24[2], handle);
    fn_80235764(&pObject->mUnknown24[2], handle);
    fn_80235D10(&pObject->mUnknown24[3], lbl_803EB840);
    fn_80235740(&pObject->mUnknown24[3], handle);
    fn_80235764(&pObject->mUnknown24[3], handle);
    if (!fn_800A262C()) {
        fn_80235C90(&pObject->mUnknown24[6], 0, 1.0f, 1.0f, 1.0f, 0.51f);
        fn_80235C90(&pObject->mUnknown24[6], 1, 1.0f, 1.0f, 1.0f, 0.51f);
        fn_80235740(&pObject->mUnknown24[6], handle);
        fn_80235764(&pObject->mUnknown24[6], handle);
    }
    if (!fn_800A26C4()) {
        fn_80235C90(&pObject->mUnknown24[5], 0, 1.0f, 1.0f, 1.0f, 0.51f);
        fn_80235C90(&pObject->mUnknown24[5], 1, 1.0f, 1.0f, 1.0f, 0.51f);
        fn_80235740(&pObject->mUnknown24[5], handle);
        fn_80235764(&pObject->mUnknown24[5], handle);
    }
    if (fn_80147E80(1) != 0) {
        fn_80235740(&pObject->mUnknown24[0], handle);
        fn_80235764(&pObject->mUnknown24[0], handle);
        fn_80235740(&pObject->mUnknown24[8], handle);
        fn_80235764(&pObject->mUnknown24[8], handle);
    }
    for (i = 0; i < 10; i++) {
        fn_80235740(&pObject->mUnknown6E4[i], handle);
        fn_80235764(&pObject->mUnknown6E4[i], handle);
    }
    fn_801D0470(fn_80228668());
    fn_801D0544();
    if (fn_800A34B0()) {
        fn_801985FC();
    }
    if (fn_800A34BC()) {
        fn_801987F4();
    }
    return 0;
}
}
