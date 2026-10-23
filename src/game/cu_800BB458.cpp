#include "game/Object_80039F5C.h"
#include "game/Camera_8013F738.h"
#include "game/fn_80178D18.h"
#include "engine/cu_80227F14.h"
#include "game/Class_80148A58.h"
#include "game/Object_80040818.h"
#include "game/cu_80064864.h"
#include "game/fn_800B65A0.h"

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
void fn_8004A230(unsigned char value);
int fn_80040F10(void);
void fn_80053B4C(Object_80040818 *pObject, int index, int apply);
int fn_800655F8(void);
void fn_80074358(int index);
void fn_800941B8(void);
int fn_800B6644(int index);
int fn_800BA6F8(void);
void fn_800BB9A4(int team, int value);
void fn_800BBE98(void);
void fn_8013F3FC(void);
void fn_80162780(int a, int b);

extern unsigned char lbl_803EAB94;
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

extern "C" void fn_800BB694(int index, unsigned int kind, float value)
{
    Class_80148A58 *pMode;
    int i;

    if (value == 0.0f || lbl_803EC98C->mUnknown4 <= 20) {
        return;
    }
    if (fn_800B6644(index) != 0 && fn_800B6644(index) != 1
        && (fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF)) {
        return;
    }
    switch (kind) {
    case 0:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    default:
        return;
    }
    if (lbl_803EC98C->mUnknown0 > 1 || lbl_803EC98C->mUnknownC != -1 || lbl_803EC98C->mUnknown32 == 1) {
        return;
    }
    fn_8004A230(1);
    fn_8013F3FC();
    fn_800BB9A4(1, 1);
    fn_80162780(1, 1);
    fn_80074358(0);
    fn_80074358(1);
    if (fn_800BA6F8() == 0) {
        fn_800BBE98();
        if (fn_800655F8() == 0) {
            fn_800655D0();
        }
    } else {
        lbl_803EAB94 = 1;
    }
    if ((pMode = fn_80148A58()) == 0 || pMode->vfn_21() != 0) {
        for (i = 0; i < fn_80040F10(); i++) {
            Object_80040818 *pObject = fn_80040F18(i);

            if (pObject->mUnknown472->mUnknown188 == 7) {
                fn_80053B4C(pObject, 2, 0);
            }
        }
    }
    fn_800941B8();
}
