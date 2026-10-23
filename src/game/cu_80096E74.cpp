#include "game/Item_80097440.h"
#include <string.h>

extern "C" {
int fn_801C4E98(void *p, const char *pName);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pAngles);
void fn_8009CE88(Object_80039F5C *p, Block_8009C6F4 *pBlock, int a);
int fn_8023790C(void);
}

extern float lbl_803EA934;
extern float lbl_803EA938;

/* fn_8009CD00 callback: puts pOut at the wrist joint of the side pData
   names (1 = right), raised by lbl_803EA938, and once pData's end time has
   passed calls fn_8009CE88 on that side's +200 (right) or +108 block. The
   clamped progress t is computed but never used. Partial: the target's
   literal slice starts with an unreferenced zero word at 0x80296158 that
   this unit does not emit, so the joint-name strings land 4 bytes early. */
extern "C" void fn_80096E74(Object_80039F5C *p, Vector_80039F5C *pOut, Data_80096E74 *pData)
{
    int done = 0;
    char shoulder[10];
    char wrist[7];
    Vector_80039F5C shoulderPos;
    Vector_80039F5C wristPos;
    Quat_801EB488 angles;
    float t;
    unsigned int now;

    if (pData->mUnknown4 == 1) {
        strcpy(shoulder, "rshoulder");
        strcpy(wrist, "rwrist");
    } else {
        strcpy(shoulder, "lshoulder");
        strcpy(wrist, "lwrist");
    }
    fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, wrist), &wristPos, &angles);
    fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, shoulder), &shoulderPos, &angles);
    now = fn_8023790C() + 2;
    t = (float)(pData->mUnknown0 - now) / lbl_803EA934;
    t = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
    *pOut = wristPos;
    pOut->mZ += lbl_803EA938;
    if (pData->mUnknown0 <= fn_8023790C()) {
        done = 1;
    }
    if (done != 0) {
        fn_8009CE88(p, pData->mUnknown4 == 1 ? (Block_8009C6F4 *)&p->mUnknown200 : (Block_8009C6F4 *)&p->mUnknown108, 12);
    }
}
