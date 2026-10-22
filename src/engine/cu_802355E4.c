/* Partial source for the engine range 0x802355E4-0x8023873C (neutral file name). */

#include <dolphin/gx/GXLighting.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/cu_80227F14.h"
#include "engine/cu_801D03D0.h"
#include "engine/Render_802353F8.h"
#include "engine/vec.h"
#include "game/fn_80238174.h"

typedef struct Shader_80235630 {
    char mUnknown0[16];
    unsigned int mUnknown16;
} Shader_80235630;

typedef struct Library_80235B6C {
    unsigned int mUnknown0;
} Library_80235B6C;

typedef struct Element_80235B6C {
    char mUnknown0[40];
    int mUnknown40;
    Library_80235B6C *mpUnknown44;
} Element_80235B6C;

typedef struct Light_802362C4 {
    unsigned int mUnknown0;
    float mUnknown4[3];
    float mUnknown16[4];
    void (*mpUnknown32)(struct Light_802362C4 *pLight);
    float mUnknown36[3];
} Light_802362C4;

typedef struct Scene_8023609C {
    unsigned int mUnknown0;
    Light_802362C4 *mpUnknown4;
    unsigned int mUnknown8;
    char *mpUnknown12;
} Scene_8023609C;

typedef struct LightSet_80236368 {
    unsigned int mUnknown0;
    GXColor mUnknown4;
    GXLightObj mUnknown8[4];
} LightSet_80236368;

typedef struct Lights_803A2868 {
    Scene_8023609C *mpUnknown0;
    GXLightObj mUnknown4[4];
    unsigned int mUnknown260[4];
    LightSet_80236368 mUnknown276[1];
} Lights_803A2868;

typedef struct Random_80236F78 {
    unsigned char mUnknown0;
    signed char mUnknown1;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    char mUnknown16[4];
    void **mpUnknown20;
} Random_80236F78;

typedef struct Bits_80237438 {
    unsigned int mUnknown0;
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8[1];
} Bits_80237438;

typedef struct Counter_80237934 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Counter_80237934;

typedef struct Timer_80237780 {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    Counter_80237934 *mpUnknown12;
} Timer_80237780;

extern char lbl_802B71A0[];
extern float lbl_802FB458[3];
extern Lights_803A2868 lbl_803A2868;
extern LightSet_80236368 *lbl_803EC108;
extern Object_80228224 *lbl_803EC110;
extern float lbl_803EC114;
extern float lbl_803EC118;
extern GXColor lbl_803EC11C;
extern unsigned char lbl_803EC120;
extern unsigned char lbl_803EC128;
extern unsigned char lbl_803EC129;
extern Random_80236F78 *lbl_803EC130;
extern int lbl_803EC134;
extern Timer_80237780 *lbl_803EC138;
extern int lbl_803EC13C;
extern int lbl_803ED028;
extern int lbl_803ED02C;

extern void *fn_801CF5BC(int type, int seed);
extern int fn_801CF60C(void *pDst, void *pSrc);
extern int fn_801CF664(void *pStream);
extern int fn_801CF67C(void *pStream);
extern unsigned int fn_801CF6D4(void *pStream, unsigned int range);
extern void *fn_801D2B7C(int size, int a, int b);
extern int fn_801D2BD0(void *p);
extern void fn_8020EBB0(void *p);
extern void fn_8020F28C(void *p);
extern void fn_8020F4D0(void *p, void *pData);
extern void fn_8020F96C(void *p, void *q, int a, int b);
extern void fn_80210054(void *p, int a);
extern void fn_80210114(void *p);
extern void fn_80210214(void *p, void *q);
extern int fn_80211984(const char *pName);
extern void fn_80211FF0(void);
extern void fn_80212018(const char *pName, void *p);
extern void fn_802144AC(void *p);
extern void *fn_8023816C(void *pHandle);
extern int fn_80238278(const void *p, int size, int seed);

void fn_80235788(Render_802353F8 *p, int handle, int a);
Light_802362C4 *fn_802362C4(Scene_8023609C *pScene, int index);
void fn_80236164(Scene_8023609C *pScene, GXLightObj *pLights, unsigned int *pColors);
int fn_802365E8(LightSet_80236368 *pSet, float r, float g, float b);
void fn_802368D0(Scene_8023609C *pScene, void *pEntry, LightSet_80236368 *pSet);
void fn_80236C04(void);
void fn_80236E3C(void);
int fn_802370E8(void *p, void *pBuffer);
int fn_80237138(void *p, void *pBuffer);
int fn_802376D8(void *p, void *pBuffer);
void fn_80237888(unsigned int time);
void fn_8023792C(void);
void fn_80237930(void);
Counter_80237934 *fn_80237934(int a, int b);
void fn_8023799C(Counter_80237934 *p);
void fn_802379BC(Counter_80237934 *p, int value);
void fn_802379C4(Counter_80237934 *p, int value);
void fn_802379CC(Counter_80237934 *p, int delta);
int fn_802379DC(Counter_80237934 *p);
int fn_80237A28(Counter_80237934 *p);

void fn_802355E4(Render_802353F8 *p)
{
    if (p->mpUnknown88 != 0) {
        fn_80210114(p->mUnknown92);
        p->mpUnknown88 = 0;
    }
    fn_8020F28C(p->mUnknown100);
}

void fn_80235630(Render_802353F8 *p, void *pData)
{
    if (p->mpUnknown84 != pData) {
        p->mpUnknown84 = pData;
        fn_8020F28C(p->mUnknown100);
        if (pData != 0) {
            fn_8020F4D0(p->mUnknown100, pData);
        }
        fn_802353E8(p, 0x8000);
        fn_802353E8(p, 0x10000);
        if (p->mpUnknown108 != 0) {
            if (p->mpUnknown108->mUnknown16 & 2) {
                fn_802353D8(p, 0x8000);
            }
            if (p->mpUnknown108->mUnknown16 & 4) {
                fn_802353D8(p, 0x10000);
            }
            fn_802144AC(p->mUnknown152);
            fn_8020F96C(p->mUnknown100, p->mUnknown152, -1, -1);
        }
    }
}

void fn_8023570C(Render_802353F8 *p, const char *pName)
{
    p->mUnknown184 = fn_80211984(pName);
}

void fn_80235740(Render_802353F8 *p, int handle)
{
    fn_801D0F80(p->mUnknown8[0]);
}

void fn_80235764(Render_802353F8 *p, int handle)
{
    fn_80235788(p, handle, 1);
}

void fn_80235B6C(Render_802353F8 *p, Element_80235B6C *pElement, int a)
{
    Library_80235B6C *pLibrary;

    if (p->mpUnknown88 != pElement) {
        if (p->mpUnknown88 != 0) {
            fn_80210114(p->mUnknown92);
        }
        if (pElement != 0) {
            fn_80211FF0();
            if (pElement->mUnknown40 != 0) {
                fn_80212018(lbl_802B71A0, pElement);
            }
            pLibrary = pElement->mpUnknown44;
            if (pLibrary != 0) {
                fn_80210054(p->mUnknown92, pLibrary->mUnknown0);
                fn_80210214(p->mUnknown92, pLibrary);
            } else {
                fn_80210054(p->mUnknown92, 0);
            }
        }
        p->mpUnknown88 = pElement;
        fn_802353D4(p, 8);
    }
}

void fn_80235C24(Render_802353F8 *p, Element_80235B6C *pElement)
{
    fn_80235B6C(p, pElement, 0);
}

void fn_80235C48(Render_802353F8 *p, int a)
{
}

void fn_80235C4C(int a, Render_802353F8 *p, float value)
{
    fn_802353D8(p, 0x80000);
    p->mUnknown72 = value;
}

void fn_80235D0C(Render_802353F8 *p, int a)
{
}

void fn_80235D74(Render_802353F8 *p, int a)
{
}

void fn_80235D78(float *p)
{
    lbl_802FB458[0] = p[0];
    lbl_802FB458[1] = p[1];
    lbl_802FB458[2] = p[2];
}

int fn_80235D9C(unsigned int *p)
{
    return *p == 0x544D646C;
}

void fn_80235DB8(void *p)
{
    fn_8020EBB0(p);
}

void *fn_8023608C(Scene_8023609C *pScene, int index)
{
    return pScene->mpUnknown12 + index * 100;
}

void fn_8023609C(Scene_8023609C *pScene)
{
    unsigned int i;
    Light_802362C4 *pLight;

    for (i = 0; i < pScene->mUnknown0; i++) {
        pLight = fn_802362C4(pScene, i);
        if (pLight->mpUnknown32 != 0) {
            pLight->mpUnknown32(pLight);
        }
        fn_802271F0(pLight->mUnknown4, pLight->mUnknown4);
        switch (pLight->mUnknown0) {
        case 0:
        case 1:
            break;
        case 2:
        case 4:
            fn_80227C2C(pLight->mUnknown36, pLight->mUnknown4);
            break;
        case 3:
            pLight->mUnknown36[0] = pLight->mUnknown4[0];
            pLight->mUnknown36[1] = pLight->mUnknown4[1];
            pLight->mUnknown36[2] = pLight->mUnknown4[2];
            break;
        }
    }
}

void fn_80236258(Scene_8023609C *pScene, LightSet_80236368 *pSets)
{
    unsigned int i;

    for (i = 0; i < pScene->mUnknown8; i++) {
        fn_802368D0(pScene, fn_8023608C(pScene, i), &pSets[i]);
    }
}

Light_802362C4 *fn_802362C4(Scene_8023609C *pScene, int index)
{
    return &pScene->mpUnknown4[index];
}

void fn_802362D4(Object_80228224 *pObject)
{
    if (lbl_803A2868.mpUnknown0 != 0) {
        fn_801D0470(fn_80228668());
        fn_8023609C(lbl_803A2868.mpUnknown0);
        fn_80236258(lbl_803A2868.mpUnknown0, lbl_803A2868.mUnknown276);
        fn_80236164(lbl_803A2868.mpUnknown0, lbl_803A2868.mUnknown4, lbl_803A2868.mUnknown260);
        fn_80236C04();
    }
}

void fn_8023633C(Scene_8023609C *pScene)
{
    lbl_803A2868.mpUnknown0 = pScene;
    fn_802362D4(0);
}

LightSet_80236368 *fn_80236368(int index)
{
    return &lbl_803A2868.mUnknown276[index];
}

GXLightObj *fn_80236384(int index)
{
    return &lbl_803A2868.mUnknown4[index];
}

unsigned int fn_80236398(int index)
{
    return lbl_803A2868.mUnknown260[index];
}

void fn_802363B0(Object_80228224 *pObject)
{
    fn_80228474(pObject, 1, fn_802362D4, 0);
}

void fn_802363E0(Object_80228224 *pObject)
{
    fn_802284EC(pObject, fn_802362D4);
}

int fn_80236B98(int index, float r, float g, float b)
{
    LightSet_80236368 *pSet = fn_80236368(index);
    int mask = fn_802365E8(pSet, r, g, b);

    lbl_803EC108 = pSet;
    lbl_803ED028 = mask;
    return mask;
}

void fn_80236C04(void)
{
    lbl_803EC108 = 0;
}

void fn_80236DD8(Object_80228224 *pObject)
{
    lbl_803EC110 = pObject;
}

void fn_80236DE0(int value)
{
    lbl_803ED02C = value;
    fn_80236E3C();
}

void fn_80236E04(float a, float b)
{
    lbl_803EC114 = a;
    lbl_803EC118 = b;
    fn_80236E3C();
}

void fn_80236E2C(int r, int g, int b)
{
    lbl_803EC11C.r = r;
    lbl_803EC11C.g = g;
    lbl_803EC11C.b = b;
}

int fn_80236EC0(int enable)
{
    if (lbl_803EC120 != enable) {
        lbl_803EC120 = enable;
        fn_80236E3C();
        return lbl_803EC120 == 0;
    }
    return enable;
}

void fn_80236EFC(float a)
{
}

void fn_80236F00(void)
{
    if (lbl_803EC128 == 0) {
        LCEnable();
        lbl_803EC128 = 1;
    }
}

void fn_80236F34(void)
{
    if (lbl_803EC128 != 0 && lbl_803EC129 == 0) {
        LCDisable();
        lbl_803EC128 = 0;
    }
}

int fn_80236F78(void *p, int value)
{
    Random_80236F78 *pRandom = p;
    int i;
    int seed;

    pRandom->mpUnknown20 = fn_801D2B7C(pRandom->mUnknown0 * 4, 0, 0);
    pRandom->mUnknown8 = 0;
    pRandom->mUnknown12 = 0;
    seed = pRandom->mUnknown4;
    for (i = 0; i < pRandom->mUnknown0; i++) {
        pRandom->mpUnknown20[i] = fn_801CF5BC(0, seed);
        seed = fn_801CF6D4(pRandom->mpUnknown20[i], 0x7FFFFFFF);
    }
    return 0;
}

int fn_8023701C(void *p, int value)
{
    Random_80236F78 *pRandom = p;

    while (pRandom->mUnknown0-- != 0) {
        fn_801CF67C(pRandom->mpUnknown20[pRandom->mUnknown0]);
    }
    fn_801D2BD0(pRandom->mpUnknown20);
    return 0;
}

int fn_80237080(void *p, void *q)
{
    Random_80236F78 *pA = p;
    Random_80236F78 *pB = q;

    int result;

    if (pB != 0) {
        result = pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
        return result;
    }
    return pA->mUnknown12;
}

int fn_80237180(void *p)
{
    return fn_801CF664(lbl_803EC130->mpUnknown20[0]) + sizeof(Random_80236F78);
}

void fn_802371B0(int count, int seed)
{
    void *pHandle;
    Random_80236F78 *pRandom;

    pHandle = fn_80238174(0, (void **)&lbl_803EC130, sizeof(Random_80236F78), 0, 0x72616E64);
    fn_80238234(pHandle, fn_80236F78, fn_8023701C, 0, fn_80237080);
    fn_80238248(pHandle, fn_802370E8, fn_80237180, fn_80237138);
    pRandom = fn_8023816C(pHandle);
    pRandom->mUnknown0 = count;
    pRandom->mUnknown4 = seed;
    pRandom->mUnknown12 = seed;
    fn_802381E0(pHandle);
}

void fn_8023725C(void)
{
}

unsigned int fn_802372EC(int stream, unsigned int count)
{
    unsigned int value;

    value = fn_801CF6D4(lbl_803EC130->mpUnknown20[stream], count);
    if (stream == 0) {
        lbl_803EC130->mUnknown8++;
        lbl_803EC130->mUnknown12 = (lbl_803EC130->mUnknown12 ^ count) + 7;
    } else if (lbl_803EC130->mUnknown1 != 0 && count > 1) {
        lbl_803EC134 = value = 1 - lbl_803EC134;
        if (!(lbl_803EC130->mUnknown1 & 0x80)) {
                value = count - 1 - value;
        }
    }
    return value;
}

int fn_80237390(int stream, int low, int high)
{
    return fn_802372EC(stream, high - low + 1) + low;
}

void fn_80237438(Bits_80237438 *pBits)
{
    unsigned int i;
    unsigned char *pData = pBits->mUnknown8;
    unsigned int count = (pBits->mUnknown0 + 7) >> 3;

    for (i = 0; i < count; i++) {
        *pData++ = 0;
    }
}

Bits_80237438 *fn_80237470(int stream, unsigned int count)
{
    Bits_80237438 *pBits = fn_801D2B7C(((count + 7) >> 3) + 8, 0, 0);

    pBits->mUnknown0 = count;
    pBits->mUnknown4 = stream;
    fn_80237438(pBits);
    return pBits;
}

int fn_802374C8(Bits_80237438 *pBits)
{
    unsigned int i;
    unsigned int index;
    int bit;
    unsigned int start;
    unsigned char *pData = pBits->mUnknown8;

    i = fn_802372EC(pBits->mUnknown4, pBits->mUnknown0);
    index = i >> 3;
    bit = i & 7;
    start = i;
    while ((pData[index] >> bit) & 1) {
        i = (i + 1) % pBits->mUnknown0;
        index = i >> 3;
        bit = i & 7;
        if (i == start) {
            fn_80237438(pBits);
        }
    }
    pData[index] |= 1 << bit;
    return i;
}

void fn_8023756C(Bits_80237438 *pBits)
{
    fn_801D2BD0(pBits);
}

int fn_8023758C(void *p, int value)
{
    Timer_80237780 *pTimer = p;

    pTimer->mUnknown8 = pTimer->mUnknown0;
    pTimer->mUnknown4 = pTimer->mUnknown0;
    pTimer->mpUnknown12 = fn_80237934(0, lbl_803EC13C);
    return 0;
}

int fn_802375D4(void *p, int value)
{
    Timer_80237780 *pTimer = p;

    fn_8023799C(pTimer->mpUnknown12);
    return 0;
}

int fn_802375FC(void *p, void *q)
{
    Timer_80237780 *pA = p;
    Timer_80237780 *pB = q;
    int result;

    if (pB != 0) {
        result = pA->mUnknown0 != pB->mUnknown0;
        result |= pA->mUnknown4 != pB->mUnknown4;
        result |= pA->mUnknown8 != pB->mUnknown8;
        result |= fn_80237A28(pA->mpUnknown12) != fn_80237A28(pB->mpUnknown12);
    } else {
        result = fn_80238278(pA, sizeof(Timer_80237780), 0);
        result = fn_80238278(pA->mpUnknown12, sizeof(Counter_80237934), result);
    }
    return result;
}

int fn_80237728(void *p, void *pBuffer)
{
    Timer_80237780 *pTimer = p;
    Timer_80237780 *pIn = pBuffer;

    *pTimer = pIn[0];
    *pTimer->mpUnknown12 = *(Counter_80237934 *)&pIn[1];
    return 1;
}

int fn_80237778(void *p)
{
    return 32;
}

void fn_80237780(int a)
{
    void *pHandle;
    Timer_80237780 *pTimer;

    fn_8023792C();
    lbl_803EC13C = a;
    pHandle = fn_80238174(0, (void **)&lbl_803EC138, sizeof(Timer_80237780), 0, 0x74696D67);
    fn_80238234(pHandle, fn_8023758C, fn_802375D4, 0, fn_802375FC);
    fn_80238248(pHandle, fn_802376D8, fn_80237778, fn_80237728);
    pTimer = fn_8023816C(pHandle);
    pTimer->mUnknown4 = 0;
    pTimer->mUnknown0 = 0;
    fn_802381E0(pHandle);
}

void fn_80237830(int delta)
{
    if (lbl_803EC138 != 0) {
        fn_80237888(lbl_803EC138->mUnknown8 + delta);
    }
}

void fn_80237868(void)
{
    fn_80237930();
}

void fn_80237888(unsigned int time)
{
    Timer_80237780 *pTimer = lbl_803EC138;
    unsigned int old = pTimer->mUnknown8;

    if (time > old) {
        pTimer->mUnknown8 = time;
        fn_802379CC(pTimer->mpUnknown12, time - old);
    }
}

unsigned int fn_802378C8(void)
{
    unsigned int value = 0;

    if (lbl_803EC138 != 0) {
        value = fn_802379DC(lbl_803EC138->mpUnknown12);
        lbl_803EC138->mUnknown4 += value;
    }
    return value;
}

int fn_8023790C(void)
{
    int value = 0;

    if (lbl_803EC138 != 0) {
        value = lbl_803EC138->mUnknown4 - lbl_803EC138->mUnknown0;
    }
    return value;
}

void fn_8023792C(void)
{
}

void fn_80237930(void)
{
}

Counter_80237934 *fn_80237934(int a, int b)
{
    Counter_80237934 *p = fn_801D2B7C(sizeof(Counter_80237934), 0, 0);

    memset(p, 0, sizeof(Counter_80237934));
    fn_802379BC(p, a);
    fn_802379C4(p, b);
    return p;
}

void fn_8023799C(Counter_80237934 *p)
{
    fn_801D2BD0(p);
}

void fn_802379BC(Counter_80237934 *p, int value)
{
    p->mUnknown0 = value;
}

void fn_802379C4(Counter_80237934 *p, int value)
{
    p->mUnknown4 = value;
}

void fn_802379CC(Counter_80237934 *p, int delta)
{
    p->mUnknown12 += delta;
}

int fn_802379DC(Counter_80237934 *p)
{
    int value = 0;

    if (p->mUnknown0 == 0) {
        if (p->mUnknown12 >= p->mUnknown4) {
            value = p->mUnknown4;
            p->mUnknown12 -= value;
        }
    } else if (p->mUnknown0 == 1) {
        value = p->mUnknown12;
        p->mUnknown12 = 0;
    }
    p->mUnknown8 = value;
    return value;
}

int fn_80237A28(Counter_80237934 *p)
{
    return p->mUnknown8;
}

int fn_80237A30(Counter_80237934 *pA, Counter_80237934 *pB)
{
    return pB->mUnknown8 - pA->mUnknown8;
}
