#include "game/Item_80097440.h"
#include <string.h>
#include "engine/cu_801D03D0.h"
#include "engine/vec.h"

extern "C" {
int fn_801C4E98(void *p, const char *pName);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pAngles);
void fn_8009CE88(Object_80039F5C *p, Block_8009C6F4 *pBlock, int a);
int fn_8023790C(void);
Entry_8009C684 *fn_8009C6F4(Entry_800AF82C *pEntries, Block_8009C6F4 *pBlock,
                            void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, void *),
                            Vector_80039F5C *pVec, int c, int b, int d);
}

extern float lbl_803EA934;
extern float lbl_803EA938;

/* fn_8009CD00 callback: puts pOut at the wrist joint of the side pData
   names (1 = right), raised by lbl_803EA938, and once pData's end time has
   passed calls fn_8009CE88 on that side's +200 (right) or +108 block. The
   clamped progress t is computed but never used. */


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

extern "C" unsigned char *fn_8009CD00(Object_80039F5C *p,
                                      void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, void *), int right,
                                      int a, int b)
{
    Vector_80039F5C pos = {0.0f};
    Quat_801EB488 angles;
    Entry_800AF82C *pEntries;
    Block_8009C6F4 *pBlock;
    const char *pName;
    int side;
    Entry_8009C684 *pEntry;

    pEntries = (Entry_800AF82C *)p->mUnknown816;
    if (right == 0) {
        pBlock = (Block_8009C6F4 *)&p->mUnknown108;
        pName = "lwrist";
        side = 1;
    } else {
        pBlock = (Block_8009C6F4 *)&p->mUnknown200;
        pName = "rwrist";
        side = 2;
    }
    fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, pName), &pos, &angles);
    fn_801D04C4();
    fn_801D06D4(p->mUnknown704[0]);
    fn_80227CC0(&pos, &pos);
    fn_801D0544();
    pEntry = fn_8009C6F4(pEntries, pBlock, pCallback, &pos, a, side, b);
    if (pEntry) {
        return pEntry->mUnknown10;
    }
    return 0;
}
