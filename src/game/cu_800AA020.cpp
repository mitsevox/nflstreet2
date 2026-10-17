#include "game/Object_80039F5C.h"
#include "game/fn_80178D18.h"

extern "C" void fn_8004A230(unsigned char value);

extern "C" void fn_800AA020(void)
{
    unsigned short i;
    unsigned int count;

    count = fn_80178D18(0);
    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(0, i);
        Block_80170E64 *pBlock;

        p->mMotion.mPos.mX = 55.0f;
        p->mMotion.mPos.mY = -100.0f;
        pBlock = p->mpUnknown4;
        pBlock->mUnknown4.mY = -100.0f;
        pBlock->mUnknown4.mX = 55.0f;
        pBlock->mUnknown20 &= ~1;
    }
    count = fn_80178D18(1);
    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(1, i);
        Block_80170E64 *pBlock;

        p->mMotion.mPos.mX = 55.0f;
        p->mMotion.mPos.mY = -100.0f;
        pBlock = p->mpUnknown4;
        pBlock->mUnknown4.mY = -100.0f;
        pBlock->mUnknown4.mX = 55.0f;
        pBlock->mUnknown20 &= ~1;
    }
    fn_8004A230(1);
}
