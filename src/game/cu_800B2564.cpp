#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Step_800C4460.h"
#include "game/Class_80297C60.h"
#include "game/Block_800B21D0.h"

extern "C" {
int fn_800B1A30(void *p);
int fn_800B1AAC(void *p);
void fn_800B1BF8(void *p);
void *fn_800B9A44(Class_80297C60 *p);
void fn_800B9A6C(Class_80297C60 *p, void *q);

extern Block_800B21D0 *lbl_803EAB20;
}

extern "C" void fn_800B2564(Object_8017886C *pFirst, Object_8017886C *pSecond)
{
    Step_800C4460 *pDelay = (Step_800C4460 *)fn_800B9A44(lbl_803EAB84);
    Step_800C4460 *pStep;

    pDelay->mUnknownC = 60.0f;
    fn_800B9A6C(lbl_803EAB84, pDelay);
    pStep = (Step_800C4460 *)fn_800B9A44(lbl_803EAB84);
    pStep->mpCallback0 = fn_800B1A30;
    pStep->mpCallback4 = fn_800B1AAC;
    pStep->mpCallback8 = fn_800B1BF8;
    pStep->mContext.mpFirst = pFirst;
    pStep->mContext.mpSecond = pSecond;
    fn_800B9A6C(lbl_803EAB84, pStep);
    lbl_803EAB20->mpUnknown0 = pStep;
}

extern "C" int fn_800B2600(void)
{
    return lbl_803EAB20->mUnknown4.mUnknown4C;
}

extern "C" void fn_800B260C(short value)
{
    lbl_803EAB20->mUnknown4.mUnknown4C = value;
}

extern "C" float fn_800B2618(int type)
{
    return 0.0f;
}
