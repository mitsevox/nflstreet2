#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/cu_80026BB0.h"
#include "game/Block_800AD634.h"

extern "C" {
int fn_801C6280(int a, int b, void *p);

extern Block_800AD634 *lbl_803EAAD4;
}

extern "C" void fn_800AD774(void)
{
    if (lbl_803EAAD4 != 0) {
        void (*pExit)(float) = lbl_80297FC8[lbl_803EAAD4->mUnknown0].mpExit;

        if (pExit != 0) {
            pExit(1.0f);
        }
    }
    lbl_803EAB90->vfn_02();
    lbl_803EABA4->vfn_03();
    lbl_803EAB38->vfn_02();
    lbl_803EA9E4->vfn_02();
    lbl_803EAB84->vfn_02();
    lbl_803EAA8C->vfn_02();
    fn_801C6280(-1, 2, (void *)fn_80026DD4);
}
