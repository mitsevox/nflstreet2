#include "game/Object_80039F5C.h"
#include "game/Camera_8013F738.h"
#include "game/fn_80178D18.h"
#include "engine/cu_80227F14.h"

struct Record_800BAE7C;

/* Block allocated by 0x800BC538 (entry 1 of the Class_80297BF8 vtable)
   through fn_80238174 under the id 'preg' (52 bytes); only the fields
   accessed here are declared. */
struct Block_800BC538 {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    Record_800BAE7C *mpUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    int mUnknown24;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    signed char mUnknown2A;
    unsigned char mUnknown2B;
    int mUnknown2C;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
};

extern "C" {
void fn_80093410(int handle);
void fn_800940F0(int handle);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8009BD60(Object_80039F5C *p);
int fn_801BE068(void *, void *, void *, unsigned short, void *, float);
void fn_801BE67C(void *pA, void *pB, void *pC, Object_80039F5C *p);
void fn_800A3B5C(Object_80039F5C *p);
int fn_801F0F18(int a);

extern Block_800BC538 *lbl_803EC98C;
}

extern "C" void fn_800BB458(void)
{
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        unsigned int count = fn_80178D18(team);
        unsigned int i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);

            fn_8009BD60(p);
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, p, 1.0f);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            fn_800A3B5C(p);
        }
    }
}

extern "C" void fn_800BB504(void)
{
    Camera_8013F738 *pCamera;

    fn_801F0F18(0);
    if (lbl_803EC98C->mUnknown20 != -1) {
        fn_800940F0(lbl_803EC98C->mUnknown20);
        fn_80093410(lbl_803EC98C->mUnknown20);
        lbl_803EC98C->mUnknown20 = -1;
    }
    if (lbl_803EC98C->mUnknown18 != -1) {
        fn_800940F0(lbl_803EC98C->mUnknown18);
        fn_80093410(lbl_803EC98C->mUnknown18);
        lbl_803EC98C->mUnknown18 = -1;
    }
    if (lbl_803EC98C->mUnknown1C != -1) {
        fn_80093410(lbl_803EC98C->mUnknown1C);
        lbl_803EC98C->mUnknown1C = -1;
    }
    fn_800BB458();
    pCamera = fn_8013FA04(2);
    if (pCamera->mUnknown28 != 0) {
        fn_802286D8((Object_80228224 *)pCamera->mUnknown28, 45.0f, 4.0f / 3.0f, 0.1f, 750.0f);
    }
}
