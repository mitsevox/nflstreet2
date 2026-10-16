#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/cu_80026BB0.h"

/* Game-mode block allocated under the id 'gply' (see cu_8008E978.cpp). */
struct Block_800AD634 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9[3];
    float mUnknownC;
};

/* Enter, update and exit handlers of each game mode. */
struct Mode_80297FC8 {
    void (*mpEnter)(float dt);
    void (*mpUpdate)(float dt);
    void (*mpExit)(float dt);
};

extern "C" {
int fn_801C6280(int a, int b, void *p);

extern Block_800AD634 *lbl_803EAAD4;
extern Mode_80297FC8 lbl_80297FC8[9];
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
