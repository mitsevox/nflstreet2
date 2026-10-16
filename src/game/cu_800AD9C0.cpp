#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"

/* Game-mode block allocated under the id 'gply' (see cu_8008E978.cpp). */
struct Block_800AD634 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9[3];
    float mUnknownC;
};

extern "C" {
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);

extern Block_800AD634 *lbl_803EAAD4;
}

extern "C" void fn_800AD9C0(float value)
{
    Block_800AD634 *p = lbl_803EAAD4;

    if (p != 0 && value > 0.0f) {
        p->mUnknownC = value;
        p->mUnknown8 = 1;
        fn_800655B8();
        fn_8002C9A8(lbl_803EA368, 4, 0);
    }
}
