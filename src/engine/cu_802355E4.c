#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
#include "engine/fn_80238680.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct Library_80235B6C {
    unsigned int mUnknown0;
} Library_80235B6C;

typedef struct Element_80235B6C {
    char mUnknown0[40];
    int mUnknown40;
    Library_80235B6C *mpUnknown44;
} Element_80235B6C;

extern char lbl_802B71A0[];
extern float lbl_802FB458[3];
extern void TMModelResRelocate(void *p);
extern void TMModelReset(void *p);
extern void TMModelBindModelRes(void *p, void *pData);
extern void TMModelAddExtent(void *p, void *q, int a, int b);
extern void TMMaterialListAlloc(void *p, int a);
extern void TMMaterialListFree(void *p);
extern void TMMaterialListSetMatDefs(void *p, void *q);
extern int TMShaderLibGetShader(const char *pName);
extern void TMTexLibRegistryReset(void);
extern void TMTexLibRegister(const char *pName, void *p);
extern void TMClipResetExtent(void *p);
void fn_802353D4(Object_80235588 *p, int flags);
void fn_802353D8(Object_80235588 *p, int flags);
void fn_802353E8(Object_80235588 *p, int flags);
void fn_80235788(Object_80235588 *p, int handle, int a);

void fn_802355E4(Object_80235588 *p)
{
    if (p->mpUnknown88 != 0) {
        TMMaterialListFree(p->mUnknown92);
        p->mpUnknown88 = 0;
    }
    TMModelReset(&p->mUnknown100);
}

void fn_80235630(Object_80235588 *p, void *pData)
{
    if (p->mpUnknown84 != pData) {
        p->mpUnknown84 = pData;
        TMModelReset(&p->mUnknown100);
        if (pData != 0) {
            TMModelBindModelRes(&p->mUnknown100, pData);
        }
        fn_802353E8(p, 0x8000);
        fn_802353E8(p, 0x10000);
        if (p->mUnknown100.mpUnknown8 != 0) {
            if (p->mUnknown100.mpUnknown8->mUnknown16 & 2) {
                fn_802353D8(p, 0x8000);
            }
            if (p->mUnknown100.mpUnknown8->mUnknown16 & 4) {
                fn_802353D8(p, 0x10000);
            }
            TMClipResetExtent(p->mUnknown152);
            TMModelAddExtent(&p->mUnknown100, p->mUnknown152, -1, -1);
        }
    }
}

void fn_8023570C(Object_80235588 *p, const char *pName)
{
    p->mUnknown184 = TMShaderLibGetShader(pName);
}

void fn_80235740(Object_80235588 *p, int handle)
{
    MatStore(p->mUnknown8[0]);
}

void fn_80235764(Object_80235588 *p, int handle)
{
    fn_80235788(p, handle, 1);
}

void fn_80235B6C(Object_80235588 *p, Element_80235B6C *pElement, int a)
{
    Library_80235B6C *pLibrary;

    if (p->mpUnknown88 != pElement) {
        if (p->mpUnknown88 != 0) {
            TMMaterialListFree(p->mUnknown92);
        }
        if (pElement != 0) {
            TMTexLibRegistryReset();
            if (pElement->mUnknown40 != 0) {
                TMTexLibRegister(lbl_802B71A0, pElement);
            }
            pLibrary = pElement->mpUnknown44;
            if (pLibrary != 0) {
                TMMaterialListAlloc(p->mUnknown92, pLibrary->mUnknown0);
                TMMaterialListSetMatDefs(p->mUnknown92, pLibrary);
            } else {
                TMMaterialListAlloc(p->mUnknown92, 0);
            }
        }
        p->mpUnknown88 = pElement;
        fn_802353D4(p, 8);
    }
}

void fn_80235C24(Object_80235588 *p, Element_80235B6C *pElement)
{
    fn_80235B6C(p, pElement, 0);
}

void fn_80235C48(Object_80235588 *p, int a)
{
}

void fn_80235C4C(int a, Object_80235588 *p, float value)
{
    fn_802353D8(p, 0x80000);
    p->mUnknown72 = value;
}

void fn_80235C90(Object_80235588 *p, int unused, float r, float g, float b, float a)
{
    p->mUnknown0 |= 0x20000;
    p->mUnknown76[0] = (unsigned char)(r * 255.0f);
    p->mUnknown76[1] = (unsigned char)(g * 255.0f);
    p->mUnknown76[2] = (unsigned char)(b * 255.0f);
    p->mUnknown76[3] = (unsigned char)(a * 255.0f);
}

void fn_80235D0C(Object_80235588 *p, int a)
{
}

void fn_80235D10(Object_80235588 *p, float value)
{
    if (!(value <= 0.0f)) {
        fn_802353D8(p, 0x40000);
        p->mUnknown188 = value;
    } else {
        fn_802353E8(p, 0x40000);
    }
}

void fn_80235D74(Object_80235588 *p, int a)
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
    TMModelResRelocate(p);
}
