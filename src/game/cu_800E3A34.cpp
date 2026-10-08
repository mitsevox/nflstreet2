#include "game/Object_80039F5C.h"

struct Block_800E3B8C {
    char mUnknown0[50];
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned short mUnknown52;
};

extern "C" {
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
}

extern "C" void fn_800E3B8C(Object_80039F5C *p)
{
    Block_800E3B8C *pBlock = (Block_800E3B8C *)&p->mUnknown336;
    if (pBlock->mUnknown50 == 1 && (p->mFlags & 0x80)) {
        p->mFlags &= ~0x80;
        fn_8009CE88(p, &p->mUnknown16, 10);
        pBlock->mUnknown50 = 0;
        if (pBlock->mUnknown51 == 1) {
            if (pBlock->mUnknown52 == 0) {
                fn_8009CE88(p, &p->mUnknown108, 20);
            } else {
                fn_8009CE88(p, &p->mUnknown200, 20);
            }
            pBlock->mUnknown51 = 0;
        }
    }
}

extern "C" void fn_800E3C30(Object_80039F5C *p)
{
    Block_800E3B8C *pBlock = (Block_800E3B8C *)&p->mUnknown336;
    if (pBlock->mUnknown50 == 1) {
        fn_8009CE88(p, &p->mUnknown16, 10);
        pBlock->mUnknown50 = 0;
    }
    if (pBlock->mUnknown51 == 1) {
        if (pBlock->mUnknown52 == 0) {
            fn_8009CE88(p, &p->mUnknown108, 20);
        } else {
            fn_8009CE88(p, &p->mUnknown200, 20);
        }
        pBlock->mUnknown51 = 0;
    }
}
